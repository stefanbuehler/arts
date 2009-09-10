/* Copyright (C) 2002-2008
   Patrick Eriksson <Patrick.Eriksson@rss.chalmers.se>
   Stefan Buehler   <sbuehler@ltu.se>
                            
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA. */



/*===========================================================================
  === File description 
  ===========================================================================*/

/*!
  \file   m_rte.cc
  \author Patrick Eriksson <Patrick.Eriksson@rss.chalmers.se>
  \date   2002-05-11 

  \brief  Workspace functions for solving clear sky radiative transfer.

  These functions are listed in the doxygen documentation as entries of the
  file auto_md.h.
*/



/*===========================================================================
  === External declarations
  ===========================================================================*/

#include <cmath>
#include <stdexcept>
#include "arts.h"
#include "arts_omp.h"
#include "auto_md.h"
#include "check_input.h"
#include "jacobian.h"
#include "logic.h"
#include "math_funcs.h"
#include "messages.h"
#include "physics_funcs.h"
#include "ppath.h"
#include "rte.h"
#include "special_interp.h"

extern const String ABSSPECIES_MAINTAG;
extern const String TEMPERATURE_MAINTAG;





/*===========================================================================
  === The functions (in alphabetical order)
  ===========================================================================*/


/* Workspace method: Doxygen documentation will be auto-generated */
void RteCalc(
         Workspace&                  ws,
         Vector&                     y,
         Vector&                     y_f,
         ArrayOfIndex&               y_pol,
         Matrix&                     y_pos,
         Matrix&                     y_los,
         Matrix&                     jacobian,
   const Agenda&                     ppath_step_agenda,
   const Agenda&                     rte_agenda,
   const Agenda&                     iy_space_agenda,
   const Agenda&                     surface_prop_agenda,
   const Agenda&                     iy_cloudbox_agenda,
   const Index&                      atmosphere_dim,
   const Vector&                     p_grid,
   const Vector&                     lat_grid,
   const Vector&                     lon_grid,
   const Tensor3&                    z_field,
   const Tensor3&                    t_field,
   const Tensor4&                    vmr_field,
   const ArrayOfArrayOfSpeciesTag&   abs_species,
   const Matrix&                     r_geoid,
   const Matrix&                     z_surface,
   const Index&                      cloudbox_on, 
   const ArrayOfIndex&               cloudbox_limits,
   const Sparse&                     sensor_response,
   const Vector&                     sensor_response_f,
   const ArrayOfIndex&               sensor_response_pol,
   const Vector&                     sensor_response_za,
   const Vector&                     sensor_response_aa,
   const Matrix&                     sensor_pos,
   const Matrix&                     sensor_los,
   const Vector&                     f_grid,
   const Index&                      stokes_dim,
   const Index&                      antenna_dim,
   const Vector&                     mblock_za_grid,
   const Vector&                     mblock_aa_grid,
   const ArrayOfRetrievalQuantity&   jacobian_quantities,
   const ArrayOfArrayOfIndex&        jacobian_indices,
   const String&                     y_unit,
   const String&                     jacobian_unit )
{
  // Consistency checks of input. 
  // Also returning some basic sizes (nblock = length(y) for one mblock)
  //
  Index nf=0, nmblock=0, nza=0, naa=0, nblock=0;  
  //
  rtecalc_check_input( nf, nmblock, nza, naa, nblock, stokes_dim, f_grid, 
                       atmosphere_dim, p_grid, lat_grid, lon_grid, z_field, 
                       t_field, r_geoid, z_surface, sensor_response, 
                       sensor_response_f, sensor_response_pol,
                       sensor_response_za, sensor_pos, sensor_los, antenna_dim, 
                       mblock_za_grid, mblock_aa_grid, cloudbox_on, 
                       cloudbox_limits, y_unit, jacobian_unit );

  // Agendas not checked elsewhere
  //
  chk_not_empty( "ppath_step_agenda", ppath_step_agenda );
  chk_not_empty( "rte_agenda", rte_agenda );


  //--- Init y and ib ---------------------------------------------------------

  // Resize *y* and auxiliary to have correct length.
  y.resize( nmblock*nblock );
  y_f.resize( nmblock*nblock );
  y_pol.resize( nmblock*nblock );
  y_pos.resize( nmblock*nblock, sensor_pos.ncols() );
  y_los.resize( nmblock*nblock, sensor_los.ncols() );

  // Create vector for MPB radiances for 1 measurement block.
  Vector ib( nf*nza*naa*stokes_dim );


  //--- Init Jacobian part ----------------------------------------------------
  //
  ArrayOfIndex     rte_do_vmr_jacs(0);
  Index            rte_do_t_jacs = 0;
  //
  ArrayOfIndex     jqi_vmr(0);      // Index in jacobian_quantities of VMRs
  ArrayOfIndex     ji0_vmr(0);      // Start index in jacobian for analyt. VMRs
  ArrayOfIndex     jin_vmr(0);      // Length of x for anal. VMRs
  Index            jqi_t = 0;       // As above, but for temperature
  Index            ji0_t = 0;       
  Index            jin_t = 0;
  ArrayOfMatrix    ib_vmr_jacs(0);  // Correspondance to *ib* for VMR jac.
  Matrix           ib_t_jacs(0,0);  // Correspondance to *ib* for t jac.
  //
  Index            ppath_array_do = 0;
  //
  String j_unit = jacobian_unit;
  if ( jacobian_unit == "-" )
    { j_unit = y_unit; }
  //
  for( Index i=0; i<jacobian_quantities.nelem(); i++ )
    {
      if ( jacobian_quantities[i].MainTag() == ABSSPECIES_MAINTAG  &&  
                                          jacobian_quantities[i].Analytical() )
        { 
          ppath_array_do = 1;
          jqi_vmr.push_back( i );
          // Find index in *abs_species* of jacobian species
          ArrayOfSpeciesTag   tags;
          array_species_tag_from_string( tags, 
                                             jacobian_quantities[i].Subtag() );
          Index si = chk_contains( "abs_species", abs_species, tags );
          rte_do_vmr_jacs.push_back( si ); 
          // Set size of MPB matrix
          ArrayOfIndex ji = jacobian_indices[i];
          const Index  nx = ji[1]-ji[0]+1;
          ji0_vmr.push_back( ji[0] );
          jin_vmr.push_back( nx );
          ib_vmr_jacs.push_back( Matrix(ib.nelem(),nx,0.0) );
        }
      if ( jacobian_quantities[i].MainTag() == TEMPERATURE_MAINTAG  &&  
                                          jacobian_quantities[i].Analytical() )
        { 
          ppath_array_do = 1;
          jqi_t          = i;
          rte_do_t_jacs  = 1; 
          // Set size of MPB matrix
          ArrayOfIndex ji = jacobian_indices[i];
          const Index  nx = ji[1]-ji[0]+1;
          ji0_t = ji[0];
          jin_t = nx;
          ib_t_jacs = Matrix(ib.nelem(),nx,0.0);
        }
    }

  // We have to make a local copy of the Workspace and the agendas because
  // only non-reference types can be declared firstprivate in OpenMP
  Workspace l_ws (ws);
  Agenda l_iy_space_agenda (iy_space_agenda);
  Agenda l_ppath_step_agenda (ppath_step_agenda);
  Agenda l_rte_agenda (rte_agenda);
  Agenda l_surface_prop_agenda (surface_prop_agenda);
  Agenda l_iy_cloudbox_agenda (iy_cloudbox_agenda);


  //--- Loop:  measurement block / zenith angle / azimuthal angle
  //
  Index    nydone = 0;                 // Number of positions in y done
  //
  for( Index mblock_index=0; mblock_index<nmblock; mblock_index++ )
    {

#pragma omp parallel for                                        \
  if(!arts_omp_in_parallel() && nza>1)                          \
  default(none)                                                 \
  shared(nza, naa, nf, joker, mblock_index, rte_do_t_jacs,      \
         rte_do_vmr_jacs, ppath_array_do, ib, jqi_vmr,          \
         ib_vmr_jacs, j_unit, jqi_t, ib_t_jacs)                 \
  firstprivate(l_ws, l_iy_space_agenda,         \
               l_ppath_step_agenda, l_rte_agenda,               \
               l_surface_prop_agenda, l_iy_cloudbox_agenda)
      for( Index iza=0; iza<nza; iza++ )
        {
          // The try block here is necessary to correctly handle
          // exceptions inside the parallel region. 
          try
            {
              //--- Define *iy* and ppath variables
              Matrix           iy;
              Ppath            ppath;
              ArrayOfPpath     ppath_array;
              Index            ppath_array_index;
              ArrayOfTensor4   diy_dvmr;
              ArrayOfTensor4   diy_dt;

              for( Index iaa=0; iaa<naa; iaa++ )
                {
                  //--- Start index in *ib* for data to include 
                  const Index   nbdone = ( iza*naa + iaa ) * nf * stokes_dim;

                  //--- LOS of interest
                  //
                  Vector los( sensor_los.ncols() );
                  //
                  los     = sensor_los( mblock_index, joker );
                  los[0] += mblock_za_grid[iza];
                  //
                  if( antenna_dim == 2 )
                    { los[1] += mblock_aa_grid[iaa]; }

                  //--- Set *ppath_array* and *diy_dX*-variables to be empty
                  //
                  ppath_array_index = -1;
                  ppath_array.resize(0);
                  //
                  diy_dvmr.resize(0);
                  diy_dt.resize(0);

                  //--- Calculate *iy*
                  iy_calc( l_ws, iy, ppath, ppath_array_index, ppath_array, 
                           diy_dvmr, diy_dt,
                           l_ppath_step_agenda, l_rte_agenda, 
                           l_iy_space_agenda, l_surface_prop_agenda, 
                           l_iy_cloudbox_agenda, atmosphere_dim, p_grid, 
                           lat_grid, lon_grid, z_field, t_field, vmr_field,
                           r_geoid, z_surface, cloudbox_on, cloudbox_limits, 
                           sensor_pos(mblock_index,joker), los, f_grid, 
                           stokes_dim, ppath_array_do, rte_do_vmr_jacs, 
                           rte_do_t_jacs );

                  //--- Unit conversions
                  apply_y_unit( iy, y_unit, f_grid );

                  //--- Copy *iy* to *ib*
                  for( Index is=0; is<stokes_dim; is++ )
                    { ib[Range(nbdone+is,nf,stokes_dim)] = iy(joker,is); }


                  //--- Jacobian part: -----------------------------------------

                  //--- Absorption species ---
                  for( Index ig=0; ig<rte_do_vmr_jacs.nelem(); ig++ )
                    {
                      //- Scale to other species retrieval modes
                      const String mode = 
                                        jacobian_quantities[jqi_vmr[ig]].Mode();
                      if( mode == "vmr" )
                        {}
                      else if( mode == "rel" )
                        {
                          for( Index ia=0; ia<ppath_array.nelem(); ia++ )
                            {
                              if( ppath_array[ia].np > 1 )
                                {
                                  for( Index ip=0; ip<ppath_array[ia].np; ip++ )
                                    diy_dvmr[ia](ig,ip,joker,joker) *= 
                                    ppath_array[ia].vmr(rte_do_vmr_jacs[ig],ip);
                                }
                            }
                        }
                      else if( mode == "nd" )
                        {
                          for( Index ia=0; ia<ppath_array.nelem(); ia++ )
                            {
                              if( ppath_array[ia].np > 1 )
                                {
                                  for( Index ip=0; ip<ppath_array[ia].np; ip++ )
                                    diy_dvmr[ia](ig,ip,joker,joker) /= 
                                        number_density( ppath_array[ia].p[ip],
                                                        ppath_array[ia].t[ip] );
                                }
                            }    
                        }              
                      else
                        { assert(0); }  // Should have been catched before

                      //- Map from ppath to retrieval quantities
                      jacobian_from_path_to_rgrids( ib_vmr_jacs[ig], nbdone,
                                     diy_dvmr, ig, atmosphere_dim, ppath_array,
                                     jacobian_quantities[jqi_vmr[ig]] );

                      //--- Unit conversions
                      apply_y_unit( 
                            ib_vmr_jacs[ig](Range(nbdone,nf*stokes_dim),joker), 
                                                               j_unit, f_grid );
                    }

                  //--- Temperature ---
                  if( rte_do_t_jacs )
                    {
                      //- Map from ppath to retrieval quantities
                      jacobian_from_path_to_rgrids( ib_t_jacs, nbdone, diy_dt,
                                                 0, atmosphere_dim, ppath_array, 
                                                 jacobian_quantities[jqi_t] );

                      //--- Unit conversions
                      apply_y_unit(ib_t_jacs(Range(nbdone,nf*stokes_dim),joker), 
                                                               j_unit, f_grid );
                    }

                  //--- End of jacobian part -----------------------------------

                } // iaa loop

            } // end try block
          catch (runtime_error e)
            {
              exit_or_rethrow(e.what());
            }
        } // iza loop

 
      //--- Apply sensor response matrix on ib
      mult( y[Range(nydone,nblock)], sensor_response, ib );

      //--- Auxiliary variables
      for( Index ii=0; ii<nblock; ii++ )
        { 
          y_f[nydone+ii]         = sensor_response_f[ii];
          y_pol[nydone+ii]       = sensor_response_pol[ii]; 
          y_pos(nydone+ii,joker) = sensor_pos(mblock_index,joker);
          y_los(nydone+ii,0)     = sensor_los(mblock_index,0) +
                                   sensor_response_za[ii];
          if( sensor_response_aa.nelem() )
            { 
              y_los(nydone+ii,1) = sensor_los(mblock_index,0) +
                                   sensor_response_aa[ii]; 
            }
        }

      //--- Apply sensor response matrix on jacobians, and store
      for( Index ig=0; ig<rte_do_vmr_jacs.nelem(); ig++ )
        {
          mult( jacobian(Range(nydone,nblock),Range(ji0_vmr[ig],jin_vmr[ig])),
                                            sensor_response, ib_vmr_jacs[ig] );
        }
      if( rte_do_t_jacs )
        {
          mult( jacobian(Range(nydone,nblock),Range(ji0_t,jin_t)), 
                                                  sensor_response, ib_t_jacs );
        }


      //--- Increase nydone
      nydone += nblock;
    }
}




/* Workspace method: Doxygen documentation will be auto-generated */
void RteCalcNoJacobian(
         Workspace&                  ws,
         Vector&                     y,
         Vector&                     y_f,
         ArrayOfIndex&               y_pol,
         Matrix&                     y_pos,
         Matrix&                     y_los,
   const Agenda&                     ppath_step_agenda,
   const Agenda&                     rte_agenda,
   const Agenda&                     iy_space_agenda,
   const Agenda&                     surface_prop_agenda,
   const Agenda&                     iy_cloudbox_agenda,
   const Index&                      atmosphere_dim,
   const Vector&                     p_grid,
   const Vector&                     lat_grid,
   const Vector&                     lon_grid,
   const Tensor3&                    z_field,
   const Tensor3&                    t_field,
   const Tensor4&                    vmr_field,
   const Matrix&                     r_geoid,
   const Matrix&                     z_surface,
   const Index&                      cloudbox_on, 
   const ArrayOfIndex&               cloudbox_limits,
   const Sparse&                     sensor_response,
   const Vector&                     sensor_response_f,
   const ArrayOfIndex&               sensor_response_pol,
   const Vector&                     sensor_response_za,
   const Vector&                     sensor_response_aa,
   const Matrix&                     sensor_pos,
   const Matrix&                     sensor_los,
   const Vector&                     f_grid,
   const Index&                      stokes_dim,
   const Index&                      antenna_dim,
   const Vector&                     mblock_za_grid,
   const Vector&                     mblock_aa_grid,
   const String&                     y_unit )
{
  Matrix                     jacobian;
  ArrayOfRetrievalQuantity   jacobian_quantities;
  ArrayOfArrayOfIndex        jacobian_indices;
  String                     jacobian_unit;
  ArrayOfArrayOfSpeciesTag   abs_species(0);


  jacobianOff( jacobian, jacobian_quantities, jacobian_indices, jacobian_unit );

  RteCalc( ws, y, y_f, y_pol, y_pos, y_los, jacobian, 
           ppath_step_agenda, rte_agenda, iy_space_agenda, surface_prop_agenda,
           iy_cloudbox_agenda, atmosphere_dim, p_grid, lat_grid, lon_grid, 
           z_field, t_field, vmr_field, abs_species, r_geoid, z_surface, 
           cloudbox_on,  cloudbox_limits, sensor_response, sensor_response_f,
           sensor_response_pol, sensor_response_za, sensor_response_aa,
           sensor_pos, sensor_los, f_grid, stokes_dim, antenna_dim, 
           mblock_za_grid, mblock_aa_grid,
           jacobian_quantities, jacobian_indices,
           y_unit, jacobian_unit );
}


/* Workspace method: Doxygen documentation will be auto-generated */
void RteCalcMC(
         Workspace&                     ws,
         Vector&                        y,
         Vector&                        y_f,
         ArrayOfIndex&                  y_pol,
         Matrix&                        y_pos,
         Matrix&                        y_los,
         Vector&                        mc_error,
   const Agenda&                        iy_space_agenda,
   const Agenda&                        surface_prop_agenda,
   const Agenda&                        opt_prop_gas_agenda,
   const Agenda&                        abs_scalar_gas_agenda, 
   const Index&                         atmosphere_dim,
   const Vector&                        p_grid,
   const Vector&                        lat_grid,
   const Vector&                        lon_grid,
   const Tensor3&                       z_field,
   const Tensor3&                       t_field,
   const Tensor4&                       vmr_field,
   const Matrix&                        r_geoid,
   const Matrix&                        z_surface,
   const Index&                         cloudbox_on, 
   const ArrayOfIndex&                  cloudbox_limits,
   const Tensor4&                       pnd_field,
   const ArrayOfSingleScatteringData&   scat_data_raw,
   const Sparse&                        sensor_response,
   const Vector&                        sensor_response_f,
   const ArrayOfIndex&                  sensor_response_pol,
   const Vector&                        sensor_response_za,
   const Vector&                        sensor_response_aa,
   const Matrix&                        sensor_pos,
   const Matrix&                        sensor_los,
   const Vector&                        f_grid,
   const Index&                         stokes_dim,
   const Index&                         antenna_dim,
   const Vector&                        mblock_za_grid,
   const Vector&                        mblock_aa_grid,
   const String&                        y_unit,
   const Numeric&                       mc_std_err,
   const Index&                         mc_max_time,
   const Index&                         mc_max_iter,
   const Index&                         mc_z_field_is_1D )
{

  // Consistency checks of input. Also returning some basic sizes
  //
  Index nf=0, nmblock=0, nza=0, naa=0, nblock=0;
  //
  if( atmosphere_dim != 3 )
        throw runtime_error( 
          "Monte Carlos calculations require that *atmosphere_dim* is 3." );
  //
  rtecalc_check_input( nf, nmblock, nza, naa, nblock, stokes_dim, f_grid, 
                       atmosphere_dim, p_grid, lat_grid, lon_grid, z_field, 
                       t_field, r_geoid, z_surface, sensor_response, 
                       sensor_response_f, sensor_response_pol,
                       sensor_response_za, sensor_pos, sensor_los, antenna_dim, 
                       mblock_za_grid, mblock_aa_grid, cloudbox_on, 
                       cloudbox_limits, y_unit, "-" );

  // Some MC variables are only local here
  Tensor3  mc_points;
  //
  MCAntenna mc_antenna;
  mc_antenna.set_pencil_beam();


  //--- Init y and ib ---------------------------------------------------------

  // Resize *y*, its aux variables and *mc_error* to have correct length.
  y.resize( nmblock*nblock );
  y_f.resize( nmblock*nblock );
  y_pol.resize( nmblock*nblock );
  y_pos.resize( nmblock*nblock, sensor_pos.ncols() );
  y_los.resize( nmblock*nblock, sensor_los.ncols() );
  mc_error.resize( nmblock*nblock );
  mc_error = 0.0;                     // Needed as values are accumulated below

  // Create vectors for MPB radiances for 1 measurement block.
  Vector ib( nf*nza*naa*stokes_dim );
  Vector ib_error( nf*nza*naa*stokes_dim );


  //--- Loop:  measurement block / zenith angle / azimuthal angle
  //
  Index    nydone = 0;                 // Number of positions in y done
  //

  // We have to make a local copy of the Workspace and the agendas because
  // only non-reference types can be declared firstprivate in OpenMP
  Workspace l_ws (ws);
  Agenda l_iy_space_agenda (iy_space_agenda);
  Agenda l_surface_prop_agenda (surface_prop_agenda);
  Agenda l_opt_prop_gas_agenda (opt_prop_gas_agenda);
  Agenda l_abs_scalar_gas_agenda (abs_scalar_gas_agenda);

  for( Index mblock_index=0; mblock_index<nmblock; mblock_index++ )
    {
#pragma omp parallel for                                        \
  if(!arts_omp_in_parallel() && nza>1)                          \
  default(none)                                                 \
  shared(nza, naa, joker, mblock_index, nf, mc_antenna,         \
         mc_points, ib, ib_error)                               \
  firstprivate(l_ws, l_iy_space_agenda,         \
               l_surface_prop_agenda,l_opt_prop_gas_agenda,     \
               l_abs_scalar_gas_agenda)
      for( Index iza=0; iza<nza; iza++ )
        {
          // The try block here is necessary to correctly handle
          // exceptions inside the parallel region. 
          try
            {
              Matrix   los(1,sensor_los.ncols());  // LOS of interest
              Matrix   pos(1,sensor_pos.ncols());  // POS of interest

              // Vectors for a monochromatic single pencil beam calculation
              Vector iyf;
              Vector iyf_error;

              // Some MC variables
              Index mc_iteration_count;
              Index mc_seed;

              // Loop azimuth angles
              for( Index iaa=0; iaa<naa; iaa++ )
                {
                  //--- POS of interest
                  pos(0,joker)  = sensor_pos( mblock_index, joker );

                  //--- LOS of interest
                  los(0,joker)  = sensor_los( mblock_index, joker );
                  los(0,0)     += mblock_za_grid[iza];
                  if( antenna_dim == 2 )
                    { los(0,1) += mblock_aa_grid[iaa]; }

                  for( Index f_index=0; f_index<nf; f_index++ )
                    {
                      ArrayOfSingleScatteringData   scat_data_mono;

                      scat_data_monoCalc( scat_data_mono, scat_data_raw, 
                                          f_grid, f_index );

                      // Seed reset for each loop. If not done, the errors 
                      // appear to be highly correlated.
                      MCSetSeedFromTime( mc_seed );
                  
                      MCGeneral( l_ws,
                                 iyf, mc_iteration_count, iyf_error, mc_points, 
                                 mc_antenna, f_grid, f_index, pos, los,
                                 stokes_dim, l_iy_space_agenda,
                                 l_surface_prop_agenda, l_opt_prop_gas_agenda,
                                 l_abs_scalar_gas_agenda,
                                 p_grid, lat_grid, lon_grid, 
                                 z_field, r_geoid, z_surface,
                                 t_field, vmr_field, 
                                 cloudbox_limits, pnd_field,
                                 scat_data_mono, mc_seed, 
                                 y_unit, mc_std_err, mc_max_time, mc_max_iter, 
                                 mc_z_field_is_1D ); 
                  
                      //--- Start index in *ib* for data to include 
                      const Index   nbdone = ( ( iza*naa + iaa ) * nf + 
                                               f_index ) * stokes_dim;

                      //--- Copy *iyf* to *ib*
                      for( Index is=0; is<stokes_dim; is++ )
                        { 
                          ib[nbdone+is]       = iyf[is]; 
                          ib_error[nbdone+is] = iyf_error[is]; 
                        } // is loop

                    } // f_index loop
                } // iaa loop

            } // end try block
          catch (runtime_error e)
            {
              exit_or_rethrow(e.what());
            }
        } // iza loop


      //--- Apply sensor response matrix on ib and ib_error
      //
      mult( y[Range(nydone,nblock)], sensor_response, ib );
      //
      for( Index irow=0; irow<nblock; irow++ )
        {
          for( Index icol=0; icol<sensor_response.ncols(); icol++ )
            { mc_error[nydone+irow] += 
               pow( sensor_response(irow,icol)*ib_error[icol], (Numeric)2.0 ); 
            }
        }

      //--- Auxiliary variables
      for( Index ii=0; ii<nblock; ii++ )
        { 
          y_f[nydone+ii]         = sensor_response_f[ii];
          y_pol[nydone+ii]       = sensor_response_pol[ii]; 
          y_pos(nydone+ii,joker) = sensor_pos(mblock_index,joker);
          y_los(nydone+ii,0)     = sensor_los(mblock_index,0) +
                                   sensor_response_za[ii];
          if( sensor_response_aa.nelem() )
            { 
              y_los(nydone+ii,1) = sensor_los(mblock_index,0) +
                                   sensor_response_aa[ii]; 
            }
        }

      //--- Increase nydone
      nydone += nblock;
    }

  // Convert *mc_error* from variances to std. devs.
  transform( mc_error, sqrt, mc_error );
}



/* Workspace method: Doxygen documentation will be auto-generated */
void RteStd( Workspace&               ws,
      // WS Output:
             Matrix&                  iy,
             ArrayOfTensor4&          diy_dvmr,
             ArrayOfTensor4&          diy_dt,
       // WS Input:
       const Ppath&                   ppath,
       const ArrayOfPpath&            ppath_array, 
       const Index&                   ppath_array_index,
       const Vector&                  f_grid,
       const Index&                   stokes_dim,
       const Agenda&                  emission_agenda,
       const Agenda&                  abs_scalar_gas_agenda,
       const ArrayOfIndex&            rte_do_gas_jacs,
       const Index&                   rte_do_t_jacs )
{
  Tensor4 dummy(0,0,0,0);

  rte_std( ws, iy, dummy, diy_dvmr, diy_dt,
           ppath, ppath_array, ppath_array_index, f_grid, stokes_dim, 
           emission_agenda, abs_scalar_gas_agenda,
           rte_do_gas_jacs, rte_do_t_jacs, false );
}



/* Workspace method: Doxygen documentation will be auto-generated */
void RteStdWithTransmissions(
             Workspace&               ws,
      // WS Output:
             Matrix&                  iy,
             Tensor4&                 ppath_transmissions,
             ArrayOfTensor4&          diy_dvmr,
             ArrayOfTensor4&          diy_dt,
       // WS Input:
       const Ppath&                   ppath,
       const ArrayOfPpath&            ppath_array, 
       const Index&                   ppath_array_index,
       const Vector&                  f_grid,
       const Index&                   stokes_dim,
       const Agenda&                  emission_agenda,
       const Agenda&                  abs_scalar_gas_agenda,
       const ArrayOfIndex&            rte_do_gas_jacs,
       const Index&                   rte_do_t_jacs )
{
  rte_std( ws, iy, ppath_transmissions, diy_dvmr, diy_dt,
           ppath, ppath_array, ppath_array_index, f_grid, stokes_dim, 
           emission_agenda, abs_scalar_gas_agenda,
           rte_do_gas_jacs, rte_do_t_jacs, true );
}




/* Workspace method: Doxygen documentation will be auto-generated */
void yUnit(
              Vector&   y,
        const String&   y_unit,
        const Vector&   y_f )
{
  const Index n = y.nelem();

  if( y_f.nelem() != n )
    {
      ostringstream os;
      os << "The length of *y* and *y_f* must be the same";
      throw runtime_error( os.str() );      
    }

  if( y_unit == "1" )
    {}

  else if( y_unit == "RJBT" )
    {
      for( Index i=0; i<n; i++ )
        { 
          y[i] = invrayjean( y[i], y_f[i] ); 
        }
    }

  else if( y_unit == "PlanckBT" )
    {
      for( Index i=0; i<n; i++ )
        { 
          y[i] = invplanck( y[i], y_f[i] ); 
        }
    }
  else
    {
      ostringstream os;
      os << "Unknown option: y_unit = \"" << y_unit << "\"\n"
         << "Recognised choices are: \"1\", \"RJBT\" and \"PlanckBT\"";
      throw runtime_error( os.str() );      
    }
}
