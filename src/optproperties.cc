/* Copyright (C)  Claudia Emde <claudia@sat.physik.uni-bremen.de>

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
  \file   optproperties.cc
  \author Claudia Emde <claudia@sat.physik.uni-bremen.de>
  \date   Thu Mar  6 11:29:59 2003
  
  \brief  This file contains definitions and functions related to the
          optical properties of particles.
  
  
 */


/*===========================================================================
  === External declarations
  ===========================================================================*/

#include <cmath>
#include <stdexcept>
#include "arts.h"
#include "matpackVII.h"
#include "array.h"
#include "math_funcs.h"
#include "messages.h"
#include "logic.h"
#include "interpolation.h"
#include "optproperties.h"
#include "xml_io.h"
extern const Numeric DEG2RAD;
extern const Numeric RAD2DEG;
extern const Numeric PI;


#define F11 pha_mat_int[0]
#define F12 pha_mat_int[1]
#define F22 pha_mat_int[2]
#define F33 pha_mat_int[3]
#define F34 pha_mat_int[4]
#define F44 pha_mat_int[5]

//! Transformation of absorption vector.
/*! 
  In the single scattering database the data of the absorption vector is 
  stored in different coordinate systems, depending on the type of 
  hydrometeor species.

  See AUG for information about different classifications of 
  the hydrometeor species. 

  Output and Input:
  \param abs_vec_lab Absorption vector in Laboratory frame.
  Input:
  \param abs_vec_data Absorption vector in database.
  \param za_datagrid Zenith angle grid in the database.
  \param aa_datagrid Zenith angle grid in the database.
  \param ptype Clasiification of the hydometeor species.
  \param za_sca Zenith angle of scattered direction.
  \param aa_sca Azimuth angle of scattered direction.
     
  \author Claudia Emde
  \date   2003-05-24 
*/
void abs_vecTransform(//Output and Input
                      VectorView abs_vec_lab,
                      //Input
                      ConstTensor3View abs_vec_data,
                      ConstVectorView za_datagrid,
                      ConstVectorView aa_datagrid,
                      const PType& ptype,
                      const Numeric& za_sca,
                      const Numeric& aa_sca)
{
 const Index stokes_dim = abs_vec_lab.nelem();
    
  if (stokes_dim > 4 || stokes_dim < 1){
    throw runtime_error("The dimension of the stokes vector \n"
                         "must be 1,2,3 or 4");
  }

  switch (ptype){

  case PTYPE_GENERAL:
    // This is only included to remove warnings about unused variables 
    // during compilation
    Numeric x;
    x = za_datagrid[0];
    x = aa_datagrid[0];
    x = za_sca;
    x = aa_sca;
        
    cout << "Case PTYPE_GENERAL not yet implemented. \n"; 
    break;
    
  case PTYPE_MACROS_ISO:
    {
      // The first element of the vector corresponds to the absorption 
      // coefficient which is stored in the database, the others are 0.
      
      abs_vec_lab = 0;

      abs_vec_lab[0] = abs_vec_data(0,0,0);
      break;
    }

case PTYPE_HORIZ_AL://Added by Cory Davis 9/12/03
    {
      assert (abs_vec_data.ncols() == 2);
      
      // In the case of horizontally oriented particles the absorption
      // coefficient vector only the first two elements are non-zero.
      // These values are dependent on the zenith angle of propagation. The 
      // data storage format also makes use of the fact that in this case
      //K_abs(za_sca)=K_abs(180-za_sca). 

      // 1st interpolate data by za_sca
      GridPos gp;
      Vector itw(2);
      if (za_sca>90)
        {
          gridpos(gp,za_datagrid,180-za_sca);
        }
      else
        {
          gridpos(gp,za_datagrid,za_sca);
        }
      interpweights(itw,gp);
      abs_vec_lab = 0;
      abs_vec_lab[0] = interp(itw,abs_vec_data(Range(joker),0,0),gp);

      if( stokes_dim == 1 ){
        break;
      }
      abs_vec_lab[1] = interp(itw,abs_vec_data(Range(joker),0,1),gp);
      break;
    }

   default:
    cout << "Not all particle type cases are implemented\n";
    
  }  
    
}


//! Transformation of extinction matrix.
/*! 
  In the single scattering database the data of the extinction matrix is 
  stored in different coordinate systems, depending on the type of 
  hydrometeor species.

  See AUG for information about different classifications of 
  the hydrometeor species. 

  Output and Input:
  \param ext_mat_lab Absorption vector in Laboratory frame.
  Input:
  \param ext_mat_data Absorption vector in database.
  \param za_datagrid Zenith angle grid in the database.
  \param aa_datagrid Zenith angle grid in the database.
  \param ptype Clasiification of the hydometeor species.
  \param za_sca Zenith angle of scattered direction.
  \param aa_sca Azimuth angle of scattered direction.

  \author Claudia Emde
  \date   2003-05-24 
*/
void ext_matTransform(//Output and Input
                      MatrixView ext_mat_lab,
                      //Input
                      ConstTensor3View ext_mat_data,
                      ConstVectorView za_datagrid,
                      ConstVectorView aa_datagrid,
                      const PType& ptype,
                      const Numeric& za_sca,
                      const Numeric& aa_sca)
{
 const Index stokes_dim = ext_mat_lab.ncols();
    
  if (stokes_dim > 4 || stokes_dim < 1){
    throw runtime_error("The dimension of the stokes vector \n"
                         "must be 1,2,3 or 4");
  }

  switch (ptype){

  case PTYPE_GENERAL:
    // This is only included to remove warnings about unused variables 
    // during compilation
    Numeric x;
    x = za_datagrid[0];
    x = aa_datagrid[0];
    x = za_sca;
    x = aa_sca;

    cout << "Case PTYPE_GENERAL not yet implemented. \n"; 
    break;
    
  case PTYPE_MACROS_ISO:
    {
      assert (ext_mat_data.ncols() == 1);
      
      // In the case of randomly oriented particles the extinction matrix is 
      // diagonal. The value of each element of the diagonal is the
      // extinction cross section, which is stored in the database.
     
      ext_mat_lab = 0.;
      
      ext_mat_lab(0,0) = ext_mat_data(0,0,0);
      
      
      if( stokes_dim == 1 ){
        break;
      }
      
      ext_mat_lab(1,1) = ext_mat_data(0,0,0);
      
      if( stokes_dim == 2 ){
        break;
      }
      
      ext_mat_lab(2,2) = ext_mat_data(0,0,0);
      
      if( stokes_dim == 3 ){
        break;
      }
      
      ext_mat_lab(3,3) = ext_mat_data(0,0,0);
      break;
    }

  case PTYPE_HORIZ_AL://Added by Cory Davis 9/12/03
    {
      assert (ext_mat_data.ncols() == 3);
      
      // In the case of horizontally oriented particles the extinction matrix
      // has only 3 independent non-zero elements Kjj, K12=K21, and K34=-K43.
      // These values are dependent on the zenith angle of propagation. The 
      // data storage format also makes use of the fact that in this case
      //K(za_sca)=K(180-za_sca). 

      // 1st interpolate data by za_sca
      GridPos gp;
      Vector itw(2);
      Numeric Kjj;
      Numeric K12;
      Numeric K34;
      
      if (za_sca>90)
        {
          gridpos(gp,za_datagrid,180-za_sca);
        }
      else
        {
          gridpos(gp,za_datagrid,za_sca);
        }

      interpweights(itw,gp);
      
      ext_mat_lab=0.0;
      Kjj=interp(itw,ext_mat_data(Range(joker),0,0),gp);
      ext_mat_lab(0,0)=Kjj;

      if( stokes_dim == 1 ){
        break;
      }
      
      K12=interp(itw,ext_mat_data(Range(joker),0,1),gp);
      ext_mat_lab(1,1)=Kjj;
      ext_mat_lab(0,1)=K12;
      ext_mat_lab(1,0)=K12;

      if( stokes_dim == 2 ){
        break;
      }
      
      ext_mat_lab(2,2)=Kjj;
      
      if( stokes_dim == 3 ){
        break;
      }
      
      K34=interp(itw,ext_mat_data(Range(joker),0,2),gp);
      ext_mat_lab(2,3)=K34;
      ext_mat_lab(3,2)=-K34;
      ext_mat_lab(3,3)=Kjj;
      break;

    }
  default:
    cout << "Not all particle type cases are implemented\n";
    
  }
}  
 

//! Transformation of phase matrix.
/*! 
  In the single scattering database the data of the phase matrix is 
  stored in different coordinate systems, depending on the type of 
  hydrometeor  species.

  See AUG for information about different classifications of 
  the hydrometeor species. 

  Output and Input:
  \param pha_mat_lab Absorption vector in Laboratory frame.
  Input:
  \param pha_mat_data Absorption vector in database.
  \param za_datagrid Zenith angle grid in the database.
  \param aa_datagrid Zenith angle grid in the database.
  \param ptype Clasiification of the hydometeor species.
  \param za_sca Zenith angle of scattered direction.
  \param aa_sca Azimuth angle of scattered direction.
  \param za_inc Zenith angle of incoming direction.
  \param aa_inc Azimuth angle of incoming direction.
  \param scat_theta Scattering angles.
  \param scat_theta_gps Grid positions of scattering angles.
  \param scat_theta_itws Interpolation weights of scattering angles.

  \author Claudia Emde
  \date   2003-08-19
*/
void pha_matTransform(//Output
                      MatrixView pha_mat_lab,
                      //Input
                      ConstTensor5View pha_mat_data,
                      ConstVectorView za_datagrid,
                      ConstVectorView aa_datagrid,
                      const PType& ptype,
                      const Index& za_sca_idx,
                      const Index& aa_sca_idx,
                      const Index& za_inc_idx,
                      const Index& aa_inc_idx,
                      ConstVectorView scat_za_grid,
                      ConstVectorView scat_aa_grid, 
                      ConstTensor4View scat_theta,
                      const ArrayOfArrayOfArrayOfArrayOfGridPos&
                         scat_theta_gps,
                      ConstTensor5View scat_theta_itws)
{

  
  const Index stokes_dim = pha_mat_lab.ncols();
  
  Numeric za_sca = scat_za_grid[za_sca_idx]; 
  Numeric aa_sca = scat_aa_grid[aa_sca_idx];
  Numeric za_inc = scat_za_grid[za_inc_idx]; 
  Numeric aa_inc = scat_aa_grid[aa_inc_idx];
               
  if (stokes_dim > 4 || stokes_dim < 1){
    throw runtime_error("The dimension of the stokes vector \n"
                         "must be 1,2,3 or 4");
  }

  switch (ptype){

  case PTYPE_GENERAL:
    // to remove warnings during compilation. 
    Numeric x;
    x = aa_datagrid[0];

    cout << "Case PTYPE_GENERAL not yet implemented. \n"; 
    break;
    
  case PTYPE_MACROS_ISO:
    {
      // Calculate the scattering and interpolate the data on the scattering
      // angle:
      
      Vector pha_mat_int(6);
      Numeric theta_rad;
      
      if ( is_size(scat_theta, 0, 0, 0, 0))
        {

          // Interpolation of the data on the scattering angle:
          interpolate_scat_angle(pha_mat_int, theta_rad, pha_mat_data,
                                 za_datagrid, za_sca, aa_sca,
                                 za_inc, aa_inc);
               
        }
      
      else
        {
          // Interpolation of the data on the scattering angle. Use 
          // precalculated interpolation weights.
          interpolate_scat_angleDOIT(pha_mat_int, pha_mat_data,
                                 za_sca_idx, aa_sca_idx,
                                 za_inc_idx, aa_inc_idx,  
                                 scat_theta_gps, scat_theta_itws);
        }

      // Caclulate the phase matrix in the laboratory frame:
      pha_mat_labCalc(pha_mat_lab, pha_mat_int, za_sca, aa_sca, za_inc, 
                      aa_inc, theta_rad);
      
      break;
    }
  case PTYPE_HORIZ_AL://Added by Cory Davis
    //Data is already stored in the laboratory frame, but it is compressed
    //a little.  Details elsewhere
    {
      assert (pha_mat_data.ncols()==16);
      Numeric delta_aa=aa_sca-aa_inc+(aa_sca-aa_inc<-180)*360-
        (aa_sca-aa_inc>180)*360;//delta_aa corresponds to the "pages" 
                                //dimension of pha_mat_data
      GridPos za_sca_gp;
      GridPos delta_aa_gp;
      GridPos za_inc_gp;
      Vector itw(8);

      gridpos(delta_aa_gp,aa_datagrid,abs(delta_aa));
      if (za_inc>90)
        {
          gridpos(za_inc_gp,za_datagrid,180-za_inc);
          gridpos(za_sca_gp,za_datagrid,180-za_sca);
        }
      else
        {
          gridpos(za_inc_gp,za_datagrid,za_inc);
          gridpos(za_sca_gp,za_datagrid,za_sca);
        }

      interpweights(itw,za_sca_gp,delta_aa_gp,za_inc_gp);

      pha_mat_lab(0,0)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                               Range(joker),0,0),
                              za_sca_gp,delta_aa_gp,za_inc_gp);
      if( stokes_dim == 1 ){
        break;
      }
      pha_mat_lab(0,1)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                               Range(joker),0,1),
                              za_sca_gp,delta_aa_gp,za_inc_gp);
      pha_mat_lab(1,0)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                               Range(joker),0,4),
                              za_sca_gp,delta_aa_gp,za_inc_gp);
      pha_mat_lab(1,1)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                               Range(joker),0,5),
                              za_sca_gp,delta_aa_gp,za_inc_gp);
      if( stokes_dim == 2 ){
        break;
      }
      if ((za_inc<=90 && delta_aa>=0)||(za_inc>90 && delta_aa<0))
        {
          pha_mat_lab(0,2)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,2),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(1,2)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,6),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(2,0)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,8),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(2,1)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,9),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
        }
      else
        {
          pha_mat_lab(0,2)=-interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,2),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(1,2)=-interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,6),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(2,0)=-interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,8),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(2,1)=-interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,9),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
        }                             
      pha_mat_lab(2,2)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                               Range(joker),0,10),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
      if( stokes_dim == 3 ){
        break;
      }
      if ((za_inc<=90 && delta_aa>=0)||(za_inc>90 && delta_aa<0))
        {
          pha_mat_lab(0,3)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,3),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(1,3)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,7),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(3,0)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,12),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(3,1)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,13),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
        }
      else
        {
          pha_mat_lab(0,3)=-interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,3),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(1,3)=-interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,7),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(3,0)=-interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,12),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
          pha_mat_lab(3,1)=-interp(itw,pha_mat_data(Range(joker),Range(joker),
                                                   Range(joker),0,13),
                                  za_sca_gp,delta_aa_gp,za_inc_gp);
        }
      pha_mat_lab(2,3)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                               Range(joker),0,11),
                              za_sca_gp,delta_aa_gp,za_inc_gp);
      pha_mat_lab(3,2)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                               Range(joker),0,14),
                              za_sca_gp,delta_aa_gp,za_inc_gp);
      pha_mat_lab(3,3)=interp(itw,pha_mat_data(Range(joker),Range(joker),
                                               Range(joker),0,15),
                              za_sca_gp,delta_aa_gp,za_inc_gp);
      break;
      
    }  
  default:
    cout << "Not all particle type cases are implemented\n";
    
  }
}




//! Interpolate data on the scattering angle.
/*! 
  This function is used for the transformation of the phase matrix 
  from scattering frame to the laboratory frame for randomly oriented
  scattering media (case PTYPE_MACRO_ISO).

  The scattering angle is calculated from the angles defining
  the directions of the incoming and scattered radiation.
  After that the data (which is stored in the data files as a function
  of the scattering angle) is interpolated on the calculated 
  scattering angle.

  Output:
  \param pha_mat_int Interpolated phase matrix.
  \param theta_rad Scattering angle [rad].
  Input:
  \param pha_mat_data Phase matrix in database.
  \param za_datagrid Zenith angle grid in the database.
  \param aa_datagrid Zenith angle grid in the database.
  \param za_sca_rad Zenith angle of scattered direction [rad].
  \param aa_sca_rad Azimuth angle of scattered direction [rad].
  \param za_inc_rad Zenith angle of incoming direction [rad].
  \param aa_inc_rad Azimuth angle of incoming direction [rad].
  \param scat_theta Scattering angles.
  \param scat_theta_gps Array of gridposizions for scattering angle.
  \param scat_theta_itws Interpolation weights belonging to the scattering angles.
     
  \author Claudia Emde
  \date   2003-05-13 
*/
void interpolate_scat_angleDOIT(//Output:
                            VectorView pha_mat_int,
                            //Input:
                            ConstTensor5View pha_mat_data,
                            const Index& za_sca_idx,
                            const Index& aa_sca_idx,
                            const Index& za_inc_idx,
                            const Index& aa_inc_idx,
                            const ArrayOfArrayOfArrayOfArrayOfGridPos&
                                scat_theta_gps,
                            ConstTensor5View scat_theta_itws
                            )
{
  
  ConstVectorView itw = scat_theta_itws(za_sca_idx, aa_sca_idx, za_inc_idx, aa_inc_idx, joker);
  
  for (Index i = 0; i < 6; i++)
    {
      pha_mat_int[i] = interp(itw, pha_mat_data(joker, 0, 0, 0, i), 
                             scat_theta_gps[za_sca_idx][aa_sca_idx][za_inc_idx][aa_inc_idx]);
    }
  
} 


//! Interpolate data on the scattering angle.
/*! 
  This function is used for the transformation of the phase matrix 
  from scattering frame to the laboratory frame for randomly oriented
  scattering media (case PTYPE_MACRO_ISO).

  The scattering angle is calculated from the angles defining
  the directions of the incoming and scattered radiation.
  After that the data (which is stored in the data files as a function
  of the scattering angle) is interpolated on the calculated 
  scattering angle.

  Output:
  \param pha_mat_int Interpolated phase matrix.
  \param theta_rad Scattering angle [rad].
  Input:
  \param pha_mat_data Phase matrix in database.
  \param za_datagrid Zenith angle grid in the database.
  \param aa_datagrid Zenith angle grid in the database.
  \param za_sca Zenith angle of scattered direction [rad].
  \param aa_sca Azimuth angle of scattered direction [rad].
  \param za_inc Zenith angle of incoming direction [rad].
  \param aa_inc Azimuth angle of incoming direction [rad].
     
  \author Claudia Emde
  \date   2003-081-19
*/
void interpolate_scat_angle(//Output:
                            VectorView pha_mat_int,
                            Numeric& theta_rad,
                            //Input:
                            ConstTensor5View pha_mat_data,
                            ConstVectorView za_datagrid,
                            const Numeric& za_sca,
                            const Numeric& aa_sca,
                            const Numeric& za_inc,
                            const Numeric& aa_inc
                            )
{
  Numeric ANG_TOL=1e-7;
  //Calculate scattering angle from incident and scattered directions.
  //The two special cases are implemented here to avoid NaNs that can 
  //sometimes occur in in the acos... formula in forward and backscatter
  //cases. CPD 5/10/03.  
  if(abs(aa_sca-aa_inc)<ANG_TOL)
    {
      theta_rad=DEG2RAD*abs(za_sca-za_inc);
    }
  else if (abs(abs(aa_sca-aa_inc)-180)<ANG_TOL)
    {
      theta_rad=DEG2RAD*(za_sca+za_inc);
      if (theta_rad>PI){theta_rad=2*PI-theta_rad;}
    }
  else
    {
      const Numeric za_sca_rad = za_sca * DEG2RAD;
      const Numeric za_inc_rad = za_inc * DEG2RAD;
      const Numeric aa_sca_rad = aa_sca * DEG2RAD;
      const Numeric aa_inc_rad = aa_inc * DEG2RAD;
      
      // cout << "Interpolation on scattering angle" << endl;
      assert (pha_mat_data.ncols() == 6);
      // Calculation of the scattering angle:
      theta_rad = acos(cos(za_sca_rad) * cos(za_inc_rad) + 
                       sin(za_sca_rad) * sin(za_inc_rad) * 
                       cos(aa_sca_rad - aa_inc_rad));
   }
      const Numeric theta = RAD2DEG * theta_rad;
      
  // Interpolation of the data on the scattering angle:
 
  GridPos thet_gp;
  gridpos(thet_gp, za_datagrid, theta);
  
  Vector itw(2);
  interpweights(itw, thet_gp);

  for (Index i = 0; i < 6; i++)
    {
      pha_mat_int[i] = interp(itw, pha_mat_data(joker, 0, 0, 0, i), 
                              thet_gp);
    }
} 




//! Calculate phase matrix in laboratory coordinate system.
/*! 
  Transformation function for the phase matrix for the case of
  randomly oriented particles (case PTYPE_MACRO_ISO).
  
  Some of the formulas can be found in 

  Mishchenkho: "Scattering, Absorption and Emission of Light 
  by Small Particles", Cambridge University Press, 2002
  Capter 4

  The full set of formulas will be documented in AUG.

  Output and Input:
  \param pha_mat_lab Phase matrix in laboratory frame.
  Input: 
  \param pha_mat_int Interpolated phase matrix.
  \param za_sca Zenith angle of scattered direction.
  \param aa_sca Azimuth angle of scattered direction.
  \param za_inc Zenith angle of incoming direction.
  \param aa_inc Azimuth angle of incoming direction.
  \param theta_rad Scattering angle [rad].
  
  \author Claudia Emde
  \date   2003-05-13 
*/
void pha_mat_labCalc(//Output:
                      MatrixView pha_mat_lab,
                      //Input:
                      ConstVectorView pha_mat_int,
                      const Numeric& za_sca,
                      const Numeric& aa_sca,
                      const Numeric& za_inc,
                      const Numeric& aa_inc,
                      const Numeric& theta_rad)
{
  Numeric za_sca_rad = za_sca * DEG2RAD;
  Numeric za_inc_rad = za_inc * DEG2RAD;
  Numeric aa_sca_rad = aa_sca * DEG2RAD;
  Numeric aa_inc_rad = aa_inc * DEG2RAD;

  const Numeric theta = RAD2DEG * theta_rad;
  const Index stokes_dim = pha_mat_lab.ncols();

  // cout << "Transformation of phase matrix:" <<endl; 
  
 
  
  // For stokes_dim = 1, we only need Z11=F11:
  pha_mat_lab(0,0) = F11;
  
  if( stokes_dim > 1 ){
    //
    // Several cases have to be considered:
    //
    const Numeric ANGTOL = 1e-6; //CPD: this constant is used to adjust zenith angles 
                               //close to 0 and PI.  This is also used to avoid
                               //float == float statements.  

   if(
        // Forward scattering
        ((theta > -.01) && (theta < .01) ) ||
        // Backward scattering
        ((theta > 179.99) && (theta < 180.01)) ||
        // "Grosskreis" through poles: no rotation required
        ((aa_sca == aa_inc) || (aa_sca == 360-aa_inc) || (aa_inc == 360-aa_sca) ||
         (aa_sca == 180-aa_inc) || (aa_inc == 180-aa_sca) )  
        )
      {
        pha_mat_lab(0,1) = F12;
        pha_mat_lab(1,0) = F12;
        pha_mat_lab(1,1) = F22;
        
        if( stokes_dim > 2 ){
          pha_mat_lab(0,2) = 0;
          pha_mat_lab(1,2) = 0;
          pha_mat_lab(2,0) = 0;
          pha_mat_lab(2,1) = 0;
          pha_mat_lab(2,2) = F33;
          
          if( stokes_dim > 3 ){
            pha_mat_lab(0,3) = 0;
            pha_mat_lab(1,3) = 0;
            pha_mat_lab(2,3) = F34;
            pha_mat_lab(3,0) = 0;
            pha_mat_lab(3,1) = 0;
            pha_mat_lab(3,2) = -F34;
            pha_mat_lab(3,3) = F44;
          }
        }
      }
   
   else 
     {
       Numeric sigma1;
       Numeric sigma2;


       // In these cases we have to take limiting values.
 
       if (za_inc_rad < ANGTOL)
         {
           sigma1 = PI + aa_sca_rad - aa_inc_rad;
           sigma2 = 0;
         }
       else if (za_inc_rad > PI-ANGTOL)
         {
           sigma1 = aa_sca_rad - aa_inc_rad;
           sigma2 = PI; 
         }
       else if (za_sca_rad < ANGTOL)
         {
           sigma1 = 0;
           sigma2 = PI + aa_sca_rad - aa_inc_rad;
         }
       else if (za_sca_rad > PI - ANGTOL)
         {
           sigma1 = PI;
           sigma2 = aa_sca_rad - aa_inc_rad; 
         }
       else
         {
           sigma1 =  acos((cos(za_sca_rad) - cos(za_inc_rad)
                                    * cos(theta_rad))/
                                    (sin(za_inc_rad)*sin(theta_rad)));
           sigma2 =  acos((cos(za_inc_rad) - cos(za_sca_rad)
                                    *cos(theta_rad))/
                                    (sin(za_sca_rad)*sin(theta_rad)));
         }
               
       const Numeric C1 = cos(2*sigma1);
       const Numeric C2 = cos(2*sigma2);
        
       const Numeric S1 = sin(2*sigma1);
       const Numeric S2 = sin(2*sigma2);
        
        pha_mat_lab(0,1) = C1 * F12;
        pha_mat_lab(1,0) = C2 * F12;
        pha_mat_lab(1,1) = C1 * C2 * F22 - S1 * S2 * F33;

         if( isnan(pha_mat_lab(0,1)) || isnan(pha_mat_lab(1,0)) || isnan(pha_mat_lab(1,1)))
        {
          cout << "pha_mat_lab(0,1) = " << pha_mat_lab(0,1) << endl
               << "pha_mat_lab(1,0) = " << pha_mat_lab(1,0) << endl
               << "pha_mat_lab(1,1) = " << pha_mat_lab(1,1) << endl
               << "za_sca = " << za_sca << endl
               << "aa_sca = " << aa_sca << endl
               << "za_inc = " << za_inc << endl
               << "aa_inc = " << aa_inc << endl
               << "theta_rad = " << theta << endl
               << "sigma1 = " << sigma1 << endl
               << "sigma2 = " << sigma2 << endl ;
           }
            //  assert(!isnan(pha_mat_lab(0,1)));        
            //assert(!isnan(pha_mat_lab(1,0)));
            //assert(!isnan(pha_mat_lab(1,1)));

        if( stokes_dim > 2 ){
	  /*CPD: For skokes_dim > 2 some of the transformation formula 
	  for each element have a different sign depending on whether or
	  not 0<aa_scat-aa_inc<180.  For details see pages 94 and 95 of 
	  Mishchenkos chapter in : 
	  Mishchenko, M. I., and L. D. Travis, 2003: Electromagnetic 
	  scattering by nonspherical particles. In Exploring the Atmosphere 
	  by Remote Sensing Techniques (R. Guzzi, Ed.), Springer-Verlag, 
	  Berlin, pp. 77-127. 
	  This is available at http://www.giss.nasa.gov/~crmim/publications/*/
	  Numeric delta_aa=aa_sca-aa_inc+(aa_sca-aa_inc<-180)*360-
	    (aa_sca-aa_inc>180)*360;
	  if(delta_aa>=0)
	    {
	      pha_mat_lab(0,2) = S1 * F12;
	      pha_mat_lab(1,2) = S1 * C2 * F22 + C1 * S2 * F33;
	      pha_mat_lab(2,0) = -S2 * F12;
	      pha_mat_lab(2,1) = -C1 * S2 * F22 - S1 * C2 * F33;
	    }
	  else
	    {
	      pha_mat_lab(0,2) = -S1 * F12;
	      pha_mat_lab(1,2) = -S1 * C2 * F22 - C1 * S2 * F33;
	      pha_mat_lab(2,0) = S2 * F12;
	      pha_mat_lab(2,1) = C1 * S2 * F22 + S1 * C2 * F33;
	    }
          pha_mat_lab(2,2) = -S1 * S2 * F22 + C1 * C2 * F33;
          
          if( stokes_dim > 3 ){
            if(delta_aa>=0)
	      {
		pha_mat_lab(1,3) = S2 * F34;
		pha_mat_lab(3,1) = S1 * F34;
	      }
	    else
	      {
		pha_mat_lab(1,3) = -S2 * F34;
		pha_mat_lab(3,1) = -S1 * F34;
	      }
            pha_mat_lab(0,3) = 0;
            pha_mat_lab(2,3) = C2 * F34;
            pha_mat_lab(3,0) = 0;
            pha_mat_lab(3,2) = -C1 * F34;
            pha_mat_lab(3,3) = F44;
          }
        }     
     }
   }
}
     

ostream& operator<< (ostream &os, const SingleScatteringData &/*ssd*/)
{
  os << "SingleScatteringData: Output operator not implemented";
  return os;
}


ostream& operator<< (ostream &os, const ArrayOfSingleScatteringData &/*assd*/)
{
  os << "ArrayOfSingleScatteringData: Output operator not implemented";
  return os;
}

