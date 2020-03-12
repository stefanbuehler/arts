#
# 2014-03-21 Jana Mendrok
#
################################################################################
#                                                                              #
# This is a demo/template file. The USER is supposed to MODIFY it according    #
# to his/her needs. However, MAKE A COPY of this template and store in a       #
# separate folder BEFORE starting to modify.                                   #
#                                                                              #
################################################################################
#                                                                              #
# This is a template file for "full" radiative transfer simulations, i.e.,     #
# providing synthetic sensor measurements. The demo case covers following      #
# conditions/capabilities:                                                     #
#  - passive sensor                                                            #
#  - 3D calculations (allowing all 3 wind components to be used)               #
#  - monochromatic pencilbeam simulation (no FOV/antenna pattern convolution,  #
#     no bandwidth/instrumental line shape/... convolution)                    #
#  - non-particle (i.e., "clearsky") calculations                              #
#  - no magnetic field effects (Zeeman, Faraday)                               #
#                                                                              #
#  + scalar to full polarisation RT possible (limitations might apply in       #
#     combination with, e.g., certain surface property settings)               #
#  + multiple viewing directions (allowing their specification by viewing      #
#     angles and tangent altitudes in parallel) from fixed platform altitude   #
#  + selection of atmospheric scenario and abs_species from toolbox data       #
#     (handled by INCLUDE file)                                                #
#  + consideration of wind Doppler shifts (by switching on winds in            #
#     atmospheric scenario INCLUDE file) considering ALL three wind components #
#  + consideration Doppler shifts from planet rotation                         #
#  + selection of absorption calculation approach (on-the-fly, lookup table    #
#     calculation, pre-calculated lookup table from file)                      #
#  + consideration of refraction selectable                                    #
#  + selection of surface properties (handled by INCLUDE file)                 #
#                                                                              #
#                                                                              #
# The user is supposed to set certain parameters or select from a choice of    #
# settings. Details of setting rules are given at the place of the settings.   #
#                                                                              #
# Selections and settings to be done are between the flags START USER SETTINGS #
# and END USER SETTINGS. The rest of the file shall not be modified,           #
# particularly settings marked with 'do NOT modify'.                           #
#                                                                              #
#                                                                              #
# The file provides following OUTPUT (written to file):                        #
#   iy         as the WSV                                                      #
#               radiance; units selectable                                     #
#               one file per pencilbeam (i.e., per pointing direction =        #
#                 per viewing angle/tangent altitude)                          #
#               name of output file is DEMONAME.iy.LOS-ID.xml, where DEMONAME  #
#                 is the name of this controlfile (ripped off the .arts        #
#                 extension; i.e., DEMONAME changes/adapts when you save the   #
#                 template under a different name) and LOS-ID is the running   #
#                 index of the pointing direction. Will be located in the      #
#                 directory, from where the controlfile is executed.           #
#   iy_aux     as the WSV                                                      #
#               auxiliary output parameters (particularly of along-the-path    #
#               type), selectable variety                                      #
#               one file per pencilbeam (i.e., viewing angle)                  #
#               all different output parameters per pencilbeam in one file     #
#               name of output file is DEMONAME.iy_aux.LOS-ID.xml              #
#                                                                              #
#   Further variables can be output (actually, ANY workspace variable) to file #
#   using WriteXML( in=VARIABLENAME ). The demo is setup to also provide:      #
#     f_grid         as the WSV                                                #
#     abs_species    as the WSV                                                #
#                                                                              #
#   Files tmp*.xml* are intermediate data needed within the calculation. They  #
#   remain in your execution directory afterwards, but can safely be deleted.  #
#                                                                              #
#                                                                              #
# This template is set up to make use of the following include files           #
# (internally they might use further includes. See their respective headers    #
# for details):                                                                #
#   demos/common/DemoMarsAtmo3D.arts                                           #
#   demos/common/DemoMarsSurface3D.arts                                        #
#   includes/common/createvars.arts                                            #
#   includes/common/makegeometry1D_unrefracted.arts                            #
#   includes/common/makegeometry1D_refracted-air_effectivetanh.arts            #
#   includes/common/makegeometry1D_refracted-air_geometrictanh.arts            #
#   includes/common/makegeometry1D_refracted-air+electrons_effectivetanh.arts  #
#   includes/common/makegeometry1D_refracted-air+electrons_geometrictanh.arts  #
#   includes/common/use-absOnTheFly.arts                                       #
#   includes/common/make-and-use-absLUT.arts                                   #
#                                                                              #
################################################################################

import numpy as np
import arts
from arts.workspace import Workspace, arts_agenda

ws = Workspace(verbosity=0)
# do NOT modify
ws.execute_controlfile("general/general.arts")
ws.execute_controlfile("general/continua.arts")
ws.execute_controlfile("general/agendas.arts")
ws.execute_controlfile("general/planet_mars.arts")
# do NOT modify
# prepare some variable containers we will need for later INCLUDE file executions.
# this INCLUDE has to appear at the beginning. DO NOT include it more than ONCE
# in a full ARTS run.
ws.execute_controlfile("planetary_toolbox/includes/common/createvars.arts")
# do NOT modify
ws.NumericCreate("obsh")
ws.NumericCreate("obslat")
ws.NumericCreate("obslon")
ws.VectorCreate("viewang_zen")
ws.VectorCreate("viewang_azi")
ws.VectorCreate("tanh")
ws.VectorCreate("tanh_azi")
################################################################################
# START USER SETTINGS - Modify settings according to you wishes                #
################################################################################
# unit of intensity output( "PlanckBT" or "RJBT" or "1" )
ws.StringSet(ws.iy_unit, "PlanckBT")
# monochromatic frequency grid
ws.VectorLinSpace(ws.f_grid, 595070000000.0, 595090000000.0, 100000.0)
# number of Stokes parameters to consider ( 1: scalarRT, 4: fully polarised )
ws.IndexSet(ws.stokes_dim, 1)
# ok to use extrapolation of partition functions (i.e. fitting range of
#  partition function paameterization does not cover the actual atmospheric
#  temperatures)?
# ( 0: not ok, 1: ok )
ws.IndexSet(ws.bad_partition_functions_ok, 1)
# ---
# Definition of atmosphere
# ---
# which scenario, which absorption species, ...
#  - use a COPY of DemoMarsAtmo3D.arts adapted to your needs/wishes
#  - provides as output: atmosphere_dim (1D), abs_species , p_grid, z/t/vmr_field,
#     wind_w_field (if switched on in adaptation of DemoMarsAtmo1D.arts)
#####
ws.execute_controlfile("planetary_toolbox/demos/common/DemoMarsAtmo3D.arts")
ws.WriteXML(ws.output_file_format, ws.abs_species, "", 0)
# ---
# Planet parameters
# ---
# planet size and shape
# Uncomment the one you want (when all are outcommented, settings from
#  planet_mars.arts include will be used, which sets a spherical planet). When
#  selecting the general *refellipsoidSet* method, also adapt equatorial radius
#  *re* and excentricity *e* according to your need. Check out the online
#  documentation of *refellipsoid* for more options.
#
# a) spherical Mars (re=3389.5km)
# refellipsoidMars( refellipsoid, "Sphere" )
# b) ellipsoidal Mars (re=3396.19km, e=0.1083)
ws.refellipsoidMars(ws.refellipsoid, "Ellipsoid")
# c) ellipsoidal planet with freely selected *re* and *e*
# refellipsoidSet( refellipsoid=refellipsoid, re=3396.19e3, e=0.1083 )
# planet rotation
# Uncomment if you want to consider Doppler shifts from planet rotation
ws.wind_u_fieldIncludePlanetRotation()
# ---
# Sensor parameters: viewing geometry
# ---
# platform altitude [m]
# note: will be identical for all viewing directions
ws.NumericSet(ws.obsh, 450000.0)
# platform geographical position [degree]
# note: will be identical for all viewing directions
ws.NumericSet(ws.obslat, 0.0)
ws.NumericSet(ws.obslon, 0.0)
# pointing direction
# note: You can specify line of sight (LOS) in terms of zenith angle AND tangent
#  altitude. Both can be used within one ARTS run. For that, tangent altitude
#  LOS, after being converted to LOS zenith angles, are appended to zenith angle
#  LOS, and both together are stored in WSV allang_zen (viewang directions are
#  first! if you want allang_zen as output, use WriteXML to write it to file).
#  That is, RT calculations for n_LOS = n_viewang + n_tanh pencilbeam LOS
#  directions will be performed.
#  Azimuth angles (viewang_azi and tanh_azi) are equivalently appended, too, and
#  stored in allang_azi. Number of azimuths has to be equal n_LOS as resulting
#  from zenith viewing angles and tangent altitudes (==n_LOS).
#
# (a) viewing angles (e.g., for slantlooking; but working for ALL geometries)
# - can be empty
# (a-1) the zenith angles [degree]
ws.VectorSet(ws.viewang_zen, np.array([180.0, 150.0, 120.0]))
# (a-2) the corresponding azimuth angles [degree] (0=North, counting clockwise)
ws.VectorSet(ws.viewang_azi, np.array([90.0, 90.0, 90.0]))
# (b) tangent altitudes for limb views
# - can be empty
# - depending on your choice of type of geometry/refraction below, specified
#    tangent altitudes will either be "theoretical" tangent altitudes (as would
#    be without refraction) or "true" tangent altitudes (the true tangent
#    altitude of a refracted ray)
# - specified tanh are allowed to be negative. In case of theoretical tangent
#    altitudes (but not for true ones!), they can even be "false" tangent
#    altitudes, i.e., pointing BELOW the actual surface level.
# (b-1) the tangent altitudes [m]
ws.VectorSet(
    ws.tanh,
    np.array([5.0e00, 4.0e03, 4.0e03, 4.0e03, 4.0e03, 1.0e04, 2.0e04, 4.0e04, 6.0e04]),
)
# (b-2) the corresponding azimuth angles [degree] (0=North, counting clockwise)
ws.VectorSet(
    ws.tanh_azi, np.array([90.0, -90.0, 0.0, 90.0, 180.0, 90.0, 90.0, 90.0, 90.0])
)
# ---
# Type of geometry/refraction
# ---
#  Prepares the viewing angles for the RT calculation from the above
#   specified viewang and tanh. Select proper INCLUDE for the type/level of
#   refraction that shall be considered.
#  NOTE: uncomment the ONE(!) you want. If more than one uncommented, the run
#   will crash.
#  NOTE: Cases b-1 and c-1 only are correct if the refracting atmosphere (i.e.,
#   the atmospheric parameters that affect refraction in the model: z(p), T, N2,
#   O2, CO2, H2, H2, H2O) is horizontally homogeneous.
#  Note: Calculated zenith angles exactly correspond to the given tangent
#   altitudes only if the planet is spherical (i.e., refellipsoid[1]=e==0), else
#   local planet curvature, which is effected by latitude and azimuthal viewing
#   direction, might cause some deviations. However, we correct for that to a
#   wide extent, such that the output zenith angles are a very good
#   approximation.
#  No problems occur for the lines-of-sight that are specified via zenith
#   viewing angles. That is, in case of doubt EXCLUSIVELY USE zenith VIEWING
#   ANGLES!
# ---
# a) no refraction at all
# INCLUDE "planetary_toolbox/includes/common/makegeometry3D_unrefracted.arts"
# b) refraction (by "air" only)
# b-1) tanh => true tangent altitudes of refracted rays
ws.execute_controlfile(
    "planetary_toolbox/includes/common/makegeometry3D_refracted-air_truetanh.arts"
)
# b-2) tanh => theoretical tangent altitudes of unrefracted rays
#  (true tangent altitudes will be lower)
# INCLUDE "planetary_toolbox/includes/common/makegeometry3D_refracted-air_geometrictanh.arts"
# c) refraction (by "air" and free electrons)
#  These require abs=species to contain "free_electrons".
# c-1) tanh => true tangent altitudes of refracted rays
# INCLUDE "planetary_toolbox/includes/common/makegeometry3D_refracted-air+electrons_truetanh.arts"
# c-2) tangent altitudes = theoretical tangent altitudes of unrefracted rays
#  (true ones will be lower)
# INCLUDE "planetary_toolbox/includes/common/makegeometry3D_refracted-air+electrons_geometrictanh.arts"
# ---
# Absorption calculation approach
# ---
#  NOTE: uncomment the ONE(!) you want. If more than one uncommented, the LATEST
#   RULES, but you might waste time with in-the-end-not-applied calculations.
# ---
# a) use on-the-fly absorption
#  (time consuming! but recommended when doing calculations with winds or other
#  Doppler shifts.)
ws.execute_controlfile("planetary_toolbox/includes/common/use-absOnTheFly.arts")
# b) calculate and use absorption lookup table
# Note: Either of the 2 includes below is ok to use. make-and-use-absLUT.arts is
#  the more general solution, also working for REAL 3D data (while, here we have
#  only homogeneous 3D created from 1D). make-and-use-absLUT_1Dfor3D.arts is
#  faster as it only calculates the LUT for a 1D case (assuming the given
#  atmosphere is homogeneous).
# INCLUDE "planetary_toolbox/includes/common/make-and-use-absLUT_1Dfor3D.arts"
# INCLUDE "planetary_toolbox/includes/common/make-and-use-absLUT.arts"
# b-1) if you want to keep the absLUT data for later use or analysis, uncomment:
# WriteXML( in=abs_lookup )
# c) use a previously calculated absorption lookup table
#  if you want to use an absLUT created earlier, uncomment the following 3 lines
#  (you might also have to specify the name. check online-doc of ReadXML)
# Copy( propmat_clearsky_agenda, propmat_clearsky_agenda__LookUpTable )
# ReadXML( out=abs_lookup )
# abs_lookupAdapt
# ---
# Surface settings
# ---
# definition of surface (altitude, reflection model, temperature)
#  - use a copy of DemoMarsSurface1D.arts adapted to your needs/wishes
#  - provides as output: z_surface, surface_rtprop_agenda (additionally:
#     surface_skin_t (cases B-1: manually set (scalar) surface temperature) or
#     t_surface (cases B-3: surface temperature field from file))
#####
ws.execute_controlfile("planetary_toolbox/demos/common/DemoMarsSurface3D.arts")
# ---
# Define (auxiliary) data output
# ---
# Uncomment all parameters you want as auxiliary output (i.e., in addition to
#  total radiance/brigthness temperature). For meaning of each paramters see
#  online-doc of the WSM selected for iy_main_agenda (here: iyEmissionStandard).
# NOTE: Last element NOT to be followed by comma.
# NOTE: Only use "Absorption, species X" up to the number of entries in
#  abs_species (clearsky calculations in Mars have at maximum 20 abs_species
#  entries, i.e. highest valid index is 19).
ws.ArrayOfStringSet(
    ws.iy_aux_vars,
    ["Pressure", "Temperature", "Absorption, summed", "iy", "Optical depth"],
)
################################################################################
# END USER SETTINGS                                                            #
################################################################################
# setting agendas needed for RT calc (there are alternative settings, though)
#####
ws.Copy(ws.iy_main_agenda, ws.iy_main_agenda__Emission)
ws.Copy(ws.iy_space_agenda, ws.iy_space_agenda__CosmicBackground)
ws.Copy(ws.iy_surface_agenda, ws.iy_surface_agenda__UseSurfaceRtprop)
# no scattering, no jacobian
#####
ws.jacobianOff()
ws.cloudboxOff()
# the checks necessary for full RT calc
#####
ws.atmfields_checkedCalc(bad_partition_functions_ok=ws.bad_partition_functions_ok)
ws.atmgeom_checkedCalc()
ws.cloudbox_checkedCalc()
ws.propmat_clearsky_agenda_checkedCalc()
# and the (clearsky) RT calc
#####
ws.NumericCreate("za")
ws.NumericCreate("aa")
ws.AgendaCreate("forloop_agenda_angles")


@arts_agenda
def forloop_agenda_angles(ws):
    ws.Extract(ws.za, ws.allang_zen, ws.forloop_index)
    ws.Extract(ws.aa, ws.allang_azi, ws.forloop_index)
    ws.rte_losSet(za=ws.za, aa=ws.aa)
    ws.Print(ws.rte_los, 0)
    ws.iyCalc()
    ws.WriteXMLIndexed(ws.output_file_format, ws.forloop_index, ws.iy, "", 0)
    ws.WriteXMLIndexed(ws.output_file_format, ws.forloop_index, ws.iy_aux, "", 0)


ws.forloop_agenda_angles = forloop_agenda_angles

ws.WriteXML(ws.output_file_format, ws.f_grid, "", 0)
ws.IndexCreate("nangles")
ws.nelemGet(ws.nangles, ws.allang_zen)
ws.IndexStepDown(ws.nangles, ws.nangles)
ws.Copy(ws.forloop_agenda, ws.forloop_agenda_angles)
ws.ForLoop(ws.forloop_agenda, 0, ws.nangles, 1)
