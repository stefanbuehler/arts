2002-01-12  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-77

	* ami/hmatrix/h_antenna.m: Allowed the antenna movement to be a 
	vector. 

2002-01-10  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-76

	* ami/retrieval/loggrid.m: The obtained spacing could be poorer than 
	the specified spacing. Fixed.

2002-01-09  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-75

	* ami/arts/tag2mo.m: A function to convert a tag string to the molecule
	name.

	* ami/path/subfolders.m: New function.

2002-01-08  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-74

	* src/partition_function_data.cc: Updated doxygen documentation
	for H2O. Added another source code 3, to indicate "wild guess or
	copied from main isotope". Updated source and error code
	description accordingly.

2002-01-07  Nikolay Koulev  <nkoulev@bremen.de>

	* arts-0-1-73

	* doc/uguide/absorption.tex: Editted the Line Catalogs subchapter(3.1.3).      

2002-01-07  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-72

	* ami/file/read_linefile.m: String inside " " were not read properly.
	This is now fixed. 

	* ami/hmatrix/h_mixer.m: Major revision of the function and approach
	for the mixer. The output frequencies now include image frequencies
	projected to the primary band. See the function for further 
	specifications.

	* ami/hmatrix/gaussian_response.m: Created and added this function that
	can be used to simply create a gaussian response for any sensor part.

	* ami/hmatrix/hBackendGauss.m: The function now uses 
	gaussian_response to set up the antenna pattern.

	* ami/hmatrix/hAntennaGaussAdv.m: The function now uses 
	gaussian_response to set up the antenna pattern.

2002-01-04  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-71

	* ami/file/filter_lines.m: Created and added this function that is an
	enviroment for filter line arrays (a set of lines read from a file).
	Two filters implemented so far, one that removes transitions for an
	isoptope below an intensity threshold, and another one that removes all
	transitions found in the water vapour absorption model by Rosenkrantz
	1998. 

	* ami/file/read_linefile.m: Created and added this file. It reads a 
	line-file in ARTS format (ASCII). With this function and write_linefile
	ARTS line files can now be read into Matlab, be modified and be written
	back to a file.

	* ami/math/isscalar.m: Created and added this functions that checks if
	a Matlab variable is a scalar.

	* ami/math/isinteger.m: Included more stringent check of the input.
	Only numeric input is now allowed.

2001-12-18  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-70

	* src/math_funcs.cc (interp_lin_vector): Put in an assertion to
	check that no two x values are the same.

2001-12-17  Viju O.-J.  <vojohn@uni-bremen.de>

	* arts-0-1-69

	* Makefile.in: included the dependency for methods.cc and species_data.cc.

	* src/m_batch.cc (ybatchFromRadiosondeGlobal): Created a new
	workspace method to calculate brightness temperature for global
	radiosonde profiles. This methid is almost similar to
	ybatchFromRadiosonde. This is created because the pressure grid in
	the profiles is course so that it is to be interpolated into a
	fine grid. 

		The p_abs grid is created using the first and last values
	of pressure grids spaced logrithmically over 100 steps.

2001-12-15  Patrick Eriksson  <patrick@rss.chalmers.se>

	* doc/examples/fullmodels_example.arts: The O2 and N2 examples
	were wrong. The model names all ended with Continuum.

	* src/m_los.cc (zaFromZtan): The statement: if (z_tan[i]>z_plat)
	was before wrongly: if (za[i]>z_plat)

2001-12-14  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-1-68

	* H2O Rosenkranz center frequencies updated with more decimals
	by checking with JPL.

2001-12-13  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-67

	* ami/arts/write_datafile.m: Changed the default precision for
	ASCII from 6 to 9. The old number was not sufficient for writing
	frequencies. With a precision of 9 decimals, a precision of 1 kHz is
	obtained up to 10 THz.

	* ami/physics/vmr2nd.m: Added this function. Calculates the number
	density for a given VMR.

	* ami/physics/nd2vmr.m: Added this function. Calculates the VMR
	for a given number density.

2001-12-10  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-66

	* ami/hmatrix/hFreqSwitch.m: Made this function for creating the
	transfer matrix to inclide the effect of frequency switching. 
	Please note that frequency switching is not included in Qpack.

	* ami/arts/write_datafile.m: The conflict between the local
	variable heading and a file with the same name was not fixed
	properly. That should hopefully be the case now.

2001-12-10  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-1-65

	* ami/hmatrix/hBinView: small bug in line 55 1:f --> 1:nf

2001-12-05  Nikolay Koulev  <nkoulev@uni-bremen.de>
   
	* arts-0-1-64

	* doc/uguide/absorption.tex: Editted some parts. 
	
2001-12-05  Thomas Kuhn  <tkuhn@uni-bremen.de>

	* arts-0-1-63

	* src/continua.cc: Update MPM93 N2 continuum, now no 
                           underflow is possible due to zero vmr.

2001-12-05  Thomas Kuhn  <tkuhn@uni-bremen.de>

	* arts-0-1-62

	* src/continua.cc: Update the H2O continuum parameter n_s of MPM 
                           from 7.5 to 7.8.

	* doc/uguide/absorption.tex: Update the uiguide for the 
	                             isotopic ratio introduced 
                                     in the MPm93 lines at 547 and 556 GHz
                                     in the line strength.

	* aii/aii_color_table.pro: update the IDL procedures.
        
	* aii/aii_plot_file.pro:    update the IDL procedures.

2001-11-28  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-61

	* ami/arts/write_artsvar.m: There could ba a clash between the local
	variable "heading" and a function somewhere in the search path.

2001-11-28  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-60

	* doc/uguide/main.tex: Added to list of authors: Wolfram Haas, Nikolay
	Koulev, Thomas Kuhn, Oliver Lemke.

2001-11-28  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-59

	* ami/hmatrix/h_backend.m: The frequency unit in an error message was 
	wrong. GHz is now changed to MHz.

2001-11-27  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-58

	* ami/hmatrix/hAntennaGaussAdv.m: The width of the produced
	antenna pattern did not match the specified width. Fixed.
	
	* ami/hmatrix/hAntennaGaussAdv.m: The width of the produced
	channel response did not match the specified width. Fixed.

2001-11-26  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-1-57

	* doc/uguide/absorption.tex: Some changes done.

2001-11-23  Stefan Buehler  <sbuehler@uni-bremen.de>

        * arts-0-1-56

	* src/matpackIII.h: First implementation of Tensor3 is
	ready. Development time: 1 day! But it works. (At least I believe
	in it.) Check out the impressive demonstration by running
	test_matpack. 

	* src/test_matpack.cc (test31): Added examples for Tensor3 usage.

	* src/Makefile.am (test_matpack_SOURCES): Added matpackIII.h.

	* src/matpackI.h: Fixed	bug in the range checking for generating
	matrix views. (Replaced mrr.mstart+(mrr.mextent-1)*mrr.mstride and
	similar expressions by simple mrr.mextent.)

	* src/notes.txt: Some more notes here.

2001-11-22  Stefan Buehler  <sbuehler@uni-bremen.de>

        * arts-0-1-55

	* src/notes.txt: Added some rough notes here.

	* src/matpackIII.h: Started this file, which will contain the
	implementation of Tensor3.

2001-11-22  Nikolay Koulev  <nkoulev@uni-bremen.de>
	
        * arts-0-1-54

	* doc/uguide/absorption.tex: Removed undefined labels.

2001-11-22  Thomas Kuhn  <tkuhn@uni-bremen.de>
	
        * arts-0-1-53

	* changes:
	   - update /src/continua.cc online description
	   - set back the example /doc/examples/batch_example.arts.in 
	     back to original version so it works again.
	* added:
	   - figures
	        doc/uguide/Figs/cloud_description_page1.eps
	        doc/uguide/Figs/cloud_description_page2.eps
		doc/uguide/Figs/cloud_description_page3.eps
		doc/uguide/Figs/cont_description_page1.eps
		doc/uguide/Figs/cont_description_page2.eps
		doc/uguide/Figs/cont_description_page3.eps
		doc/uguide/Figs/fullmodel_description_page1.eps
		doc/uguide/Figs/fullmodel_description_page2.eps
		doc/uguide/Figs/fullmodel_description_page3.eps

2001-11-22  Oliver Lemke  <olemke@uni-bremen.de>

        * arts-0-1-52
	
	* doc/uguide/absorption.tex: Removed .ps endings from figures.

	* doc/uguide/Figs:
	- Removed files:
		doc/uguide/Figs/cloud_description_page1.ps
		doc/uguide/Figs/cloud_description_page2.ps
		doc/uguide/Figs/cloud_description_page3.ps
		doc/uguide/Figs/cont_description_page1.ps
		doc/uguide/Figs/cont_description_page2.ps
		doc/uguide/Figs/cont_description_page3.ps
		doc/uguide/Figs/fullmodel_description_page1.ps
		doc/uguide/Figs/fullmodel_description_page2.ps
		doc/uguide/Figs/fullmodel_description_page3.ps
	- Added files:
		doc/uguide/Figs/cloud_description_page1.pdf
		doc/uguide/Figs/cloud_description_page2.pdf
		doc/uguide/Figs/cloud_description_page3.pdf
		doc/uguide/Figs/cont_description_page1.pdf
		doc/uguide/Figs/cont_description_page2.pdf
		doc/uguide/Figs/cont_description_page3.pdf
		doc/uguide/Figs/cont_example.arts_page1.pdf
		doc/uguide/Figs/cont_example.arts_page2.pdf
		doc/uguide/Figs/cont_example.arts_page3.pdf
		doc/uguide/Figs/fullmodel_description_page1.pdf
		doc/uguide/Figs/fullmodel_description_page2.pdf
		doc/uguide/Figs/fullmodel_description_page3.pdf
	
2001-11-21  Thomas Kuhn  <tkuhn@uni-bremen.de>
	
        * arts-0-1-51

	* changes: 
	  - file src/continua.cc:
	    Online documentation changed.

2001-11-21  Thomas Kuhn  <tkuhn@uni-bremen.de>
	
        * arts-0-1-50

	* changes: 
	  - Added files: 
		doc/uguide/Figs/cloud_description_page1.fig
		doc/uguide/Figs/cloud_description_page2.fig
		doc/uguide/Figs/cloud_description_page3.fig
		doc/uguide/Figs/cloud_description_page1.ps
		doc/uguide/Figs/cloud_description_page2.ps
		doc/uguide/Figs/cloud_description_page3.ps
		doc/uguide/Figs/clouds_example.arts_page1.ps
		doc/uguide/Figs/clouds_example.arts_page2.ps
		doc/uguide/Figs/clouds_example.arts_page3.ps
		doc/uguide/Figs/cont_description_page1.fig
		doc/uguide/Figs/cont_description_page2.fig
		doc/uguide/Figs/cont_description_page3.fig
		doc/uguide/Figs/cont_description_page1.ps
		doc/uguide/Figs/cont_description_page2.ps
		doc/uguide/Figs/cont_description_page3.ps
		doc/uguide/Figs/cont_example.arts_page1.ps
		doc/uguide/Figs/cont_example.arts_page2.ps
		doc/uguide/Figs/cont_example.arts_page3.ps
		doc/uguide/Figs/fullmodel_description_page1.fig
		doc/uguide/Figs/fullmodel_description_page2.fig
		doc/uguide/Figs/fullmodel_description_page3.fig
		doc/uguide/Figs/fullmodel_description_page1.ps
		doc/uguide/Figs/fullmodel_description_page2.ps
		doc/uguide/Figs/fullmodel_description_page3.ps
		doc/uguide/Figs/fullmodels_example.arts_page1.ps
		doc/uguide/Figs/fullmodels_example.arts_page2.ps
		doc/uguide/Figs/fullmodels_example.arts_page3.ps
		doc/uguide/app_units.tex
		doc/examples/clouds_example.arts.in
		doc/examples/cont_example.arts.in
		doc/examples/fullmodels_example.arts.in
	  - changes in files:
	        src/constants.cc:
	          added the constants Euler's number, 
	          log of Euler's number
	        src/workspace.cc:
	          added ws cont_description_models for methods
	          "cont_descriptionInit" and "cont_descriptionAppend".
	          Also description is added for the ws
	          cont_description_names, cont_description_models, 
	          and cont_description_parameters.
	        src/methods.cc:
	          added ws cont_description_models to methods
	          "cont_descriptionInit" and "cont_descriptionAppend".
	          Also the keywords for "cont_descriptionAppend" are 
	          changed/added to be now tagname, model, and userparameters.
	          All the other methods, like "absCalc", which 
	          use the ws cont_description_names and 
	          cont_description_parameters already were updated
	          to have also cont_description_models as input.
	          The new method "WaterVaporSaturationInClouds" is 
	          implemented to set the water vapor partial pressure 
	          to the saturation pressure in clouds.
	          In "AtmFromRaw" the flag for setting saturation in
		  clouds is taken away. 
	          Also in "AtmFromRaw", linear interpolation in 
	          ln of pressure is valid for clouds now.
	        src/continua.cc:
	          Detailed online documentation implemented.
	          Synthesis of the tags "O2-SelfContPWR93" and 
	          "O2-SelfContMPM93" to tag "O2-SelfContStandardType" 
	          since both models are essentially the same.
	          Also the tag "N2-SelfContPWR93" is now named 
	          "N2-SelfContStandardType".
	          Change in the calling function "xsec_per_tgAddConts" 
	          to check input variables "tagname", "model", and 
	          "userparameters" for consistency.
	          Some internal conversion coefficients are stated 
	          now as global constants of the file continua.cc 
	          to be more homogeneous in all the functions.
                src/partition_function_data.cc:
	          Adjustments of the tag names for O2 and N2.
	        src/species_data.cc:
	          Adjustments of the tag names for O2 and N2.
	        src/m_abs.cc:
	          Adjustent for the additional ws cont_description_models
	          to the functions "absCalc" and "xsec_per_tgAddConts".
	          Revision of the functions "cont_descriptionInit" and 
	          "cont_descriptionAppend" according to the new input 
	          parameters defined in methods.cc. 
	          Adjustment of "AtmFromRaw" to cancel the saturation
	          flag.
	          Creation of the function "WaterVaporSaturationInClouds" 
	          which corresponds to the method 
	          "WaterVaporSaturationInClouds".
	        doc/uguide/absorption.tex:
	          major revision of the chapters describing the 
	          continua, the full models and the cloud absorption.
	          Also a detailed description of the implementation 
	          and usage in arts is added.
	        doc/uguide/app_units.tex:
	          Table with the arts units and unit conversion
	          coefficients.
	
2001-11-21  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-49

	* doc/uguide/concept.tex: Added practical
	information about useful command line parameters and such things.

	* doc/examples/.cvsignore: Cleaned up, using the new naming
	convention. Ignored are now:
	"*.arts", "*.rep", "*_example.*.aa", "*_example.*.ab".

	* doc/examples/amsu_example.arts.in: Fixed name of output file
	from _y_mono to .y_mono

2001-11-20  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-1-48
	
	* src/m_io.cc (Exit): Return 0 on exit.

	* doc/examples/radiosonde_example.arts.in: Changed f_mono.out to
	f_mono.aa.

	* doc/examples/amsu_example.arts.in: Renamed output file.
	Changed f_mono.out to f_mono.aa.

	* doc/examples/f_mono.aa: Renamed from f_mono.out.

2001-11-20  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-1-47
	
	* doc/examples/batch_example.arts.in: Renamed batch_test to
	batch_input.

	* doc/examples/batch_test.*.ab: Renamed to batch_input.*.ab.

	* doc/uguide/development.tex: Added section about creating example
	files.

	* doc/examples/amsu.arts: Renamed to amsu_example.arts.in.

	* doc/examples/auto_example1.arts: Renamed to
	absorption_example.arts.in.

	* doc/examples/auto_full.arts.in: Renamed to rt_example.arts.in.

	* configure.in: Added new examples.

2001-11-19  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-46

	* src/methods.cc (define_md_data): Added method MethodListDefine,
	which sets up a method list from method names given by the
	ArrayOfString keyword parameter.

	* src/m_method_list.cc: Added this file, which will contain
	methods related to method lists.
	(MethodListDefine): Added implementation of this method here.

	* src/method_list.h: Added this file, which might contain
	declarations related to method lists in the future. At the moment
	it is empty.

	* src/Makefile.am (arts_SOURCES): Added m_method_list.cc, but not
	method_list.h, since the latter is not yet used.

	* src/workspace.cc (define_wsv_data): Added WSV method_list, which
	can hold a generic method list, as the name says.

2001-11-16  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-1-45
	
	* doc/examples/Makefile.am: Added check target. Call make check to
	see if the example files are working.
	
	* doc/examples/cont.arts: Quick fix to get it running. Name will
	change to cont_example.arts when Thomas updates it.
	
2001-11-16  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-44

	* src/m_los.cc (yCalc): Removed check between f_mono and trans and
	between f_mon and source as those gave an incorrect error message
	when zenith angles are outside the atmosphere.

	* am/hmatrix: Fixed a bug regarding re-allocation of matrix sizes
	when this was done for the last zenith angle in h_mixer and for
	the last frequency in h_backend. 

2001-11-14  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-43

	* There was a bug in the AMI function h_mixer.m. The function only
	worked when the upper sideband was considered to be the primary
	band. This should have been fixed now.

2001-11-13  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-1-42

	* src/methods.cc (lineshapeDefine): Edited the entry.

	* src/methods.cc (lineshape_per_tgDefine): Edited the entry.
	
2001-11-13  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-1-41

	* src/methods.cc (lineshapeDefine): Edited the entry.

	* src/methods.cc (lineshape_per_tgDefine): Edited the entry.
	
2001-11-09  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-1-40

	* src/methods.cc (lineshapeDefine): Edited the entry.

	* src/methods.cc (lineshape_per_tgDefine): Edited the entry.
	
2001-11-09  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-1-39

	* src/methods.cc (lineshapeDefine): Edited the entry.

	* src/methods.cc (lineshape_per_tgDefine): Edited the entry.
	
2001-11-09  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-1-38

	* src/methods.cc (lineshapeDefine): Edited the entry.

	* src/methods.cc (lineshape_per_tgDefine): Edited the entry. 
	
2001-11-09  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-1-37

	* src/methods.cc (lineshapeDefine): Erased the non-functioning
	lineshapes from the documentation with the Drayson approximation
	and added the only one functioning - Voigt_Drayson.

	* src/methods.cc (lineshape_per_tgDefine): The same as above.
		
2001-11-09  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-36

	* src/file.cc (read_array_of_matrix_from_stream): Allow comments
	also in the middle of the file.
	(skip_comments): Made a separate function out of this,

2001-11-06  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-35

	* General: Added a new method, `ybatchFromRadiosonde', which can
	be used to calculate radiances for a whole bunch of radiosonde
	launches. ybatchCalc could not be used for this, because it needs
	all input on the same pressure grid.

	* src/workspace.cc (define_wsv_data): Added variable radiosonde_data.

	* src/methods.cc (define_md_data): Added method ybatchFromRadiosonde.

	* src/m_batch.cc (ybatchFromRadiosonde): Added this method.

	* configure.in: Added radiosonde_example.arts.in.

	* doc/examples/radiosonde_example.arts.in: Added this example,
	explaining the use of the new method ybatchFromRadiosonde.

	* doc/examples/radiosondes.aa: Added this file. It contains 3
	radiosonde launches. See online documentation of the workspace
	variable `radiosonde_data' for an explanation of the
	format/contents. 

	* doc/examples/.cvsignore: Added batch_example output. Added
	radiosonde_example output.

2001-11-02  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-34

	* src/methods_as_wsv.h: Started this file.

	* src/Makefile.am (arts_SOURCES): Included methods_as_wsv_h.

	* src/parser.h: Updated doxygen docu for class MRecord.

2001-11-01  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-33

	* doc/uguide/matrix_vector.tex: Fixed some typos.

	* Changelog: Removed all the extra blank lines between log
	entries. From now on, let's have only one blank line.

2001-10-31  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-32

	* src/matpackI.h: Cosmetic changes to doxygen comments.

	* doc/uguide/matrix_vector.tex: Finished the first draft of this
	chapter. Now it contains a description of Vector, Matrix, and
	Array. 

	* README: Removed one outdated sentence about arts-data.
	
2001-10-31  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-1-31

	* All of the following changes belong to the effort to compile
	ARTS on marvin.

	* configure.in: First check for libjpeg. Otherwise static linking
	does not work when the libraries are added in the wrong order
	(libdf depends on libjpeg).

	* src/parser.cc: Moved #include "arts.h" to top.

	* src/main.cc: Moved #include "arts.h" to top.

	* src/absorption.cc: Moved #include "arts.h" to top.

	* src/workspace_aux.cc: Moved #include "arts.h" to top.

	* src/globals_2.cc: Moved #include "arts.h" to top.

	* src/arts.h: Added #include <cstddef> on top which contains
	definition of size_t required to compile on marvin with HP's
	broken gcc.
	
2001-10-31  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-1-30
	
	* reconf: Added option --copy to automake
	
2001-10-31  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-1-29
	
	* README: Added documentation for configure options.

	* configure.in: Changed configure option name for warnings to
	--enable-more-warnings.

	Removed option --enable-docs. Now the docs are only generated in
	maintainer-mode.
	
2001-10-30  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-28

	* General: Fixed the bug in copying VectorViews, that was
	discovered by Carlos.
	
	* src/matpackI.h (VectorView VectorView::operator=(const
	VectorView& v)): Added. This is a tricky one. The problem is that
	since VectorView is derived from ConstVectorView, a default =
	operator is generated by the compiler, which does not do what we
	want. So we need this one to override the default.
	(MatrixView& MatrixView::operator=(const MatrixView& m)): Added this
	also for the same reason.
	
	* src/m_batch.cc (ybatchCalc): Removed the bug workaround, since
	it is no longer necessary.

2001-10-30  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-1-27

	* something wrong when tagging previous version, let's see now.

2001-10-30  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-1-26

	* cleaning and moving of some mscripts in /ami

	* adding /doc/examples/batch_example.arts.in as an example
	of ybatchCalc, input files needed are listed there and 
	have also been added in the same directory.

2001-10-24  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-25

	* doc/uguide/matrix_vector.tex: Started Matrix part.
	
2001-10-23  Carmen Verdes  <cverdes@uni-bremen.de>

	* arts-0-1-24

	* ami/physics/za2geomtan.m: added. This function converts the
	zenith angles to tangent altitudes

2001-10-18  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-1-23

	* doc/uguide/absrption.tex: editing and resolving warnings in the Tex
	code.

2001-10-18  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-22

	* doc/uguide/matrix_vector.tex: Added this file. Wrote the section
	about Vector. Still missing: Matrix, Array.

	* doc/uguide/main.tex: Included the new file.

	* doc/uguide/Makefile.am (texfiles): Added the new file.

2001-10-16  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-21

	* Small change for ground emission WFs. The ground emission (as a 
	function of freqeuncy) should be treated as a "profile" and not as 
	a number of seperate variables. The k_names are changed for ground 
	emission to reflect this.
	
2001-10-16  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-1-20

	* Committing to test.

2001-10-16  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-1-19

	* /ami/physiscs/za2geomtan.m added again, this time
	for real.

2001-10-15  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-1-18

	* /ami/physiscs/za2geomtan.m added

2001-10-15  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-1-17

	* /ami/hmatrix/hRedKx.m and hRedLimb.m removed, they
	are now part of Qpack.

2001-10-16  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-1-6

	* forgot to add hseCalc.m, added now!

2001-10-16  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-1-5

	* BUG in m_batch line 301 temporarily fixed, Stefan please
	have a look

	* /ami/hmatrix/hRedLimb updated
	
	* new mscript /ami/physics/hseCalc.m resembling the hseCalc
	function of arts, to be used for instance in Qpack/Main/qp_
	rnd_atm.

2001-10-15  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-1-4

	* Absorption was not interpolated using log(p) as altitude coordinate.
	Fixed.
	
2001-10-12  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-3

	* src/absorption.cc (ReadFromJplStream): Here also set sgam to
	agam (was zero).

2001-10-12  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-1-2

	* src/absorption.cc (xsec_species): Added pressure shift. It
	remains to be verified that this works correctly. Hopefully the
	intercomparison with Moliere for HCl can show that.
	(ReadFromHitranStream): If sgam==0, set it equal to agam.

	* src/absorption.h: Moved doxygen header for xsec_species to
	absorption.cc. 

2001-10-08  Nikolay Koulev  <nkoulev@uni-bremen.de>
        
	* arts-0-1-1
	
	* doc/uguide/absorption.tex: completed my section of line by line
	absorption coefficients calculation

	* src/absorption.h: changed in ARTS documentation cm-1 to J

2001-10-07  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-1-0

	* This is pre-release 1.
	
	* doc/uguide/Figs/Makefile.am (EXTRA_DIST): Removed *calerror*.
	
2001-10-07  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-267
	
	* src/Makefile.am (methods.o): Added -I.. to be compatible with
	the latest automake version.
	(species_data.o): Added -I.. to be compatible with the latest
	automake version.

	* src/methods.cc: Changed #include "config.h" to #include <config.h>.

	* src/arts.h: Changed #include "config.h" to #include <config.h>.

2001-10-05  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-266

	* doc/uguide/Makefile.am: Remove app_math.txt.

	* doc/examples/Makefile.am: Changed example1.arts to auto_example1.arts.

2001-10-05  Stefan Buehler  <sbuehler@uni-bremen.de>

	* doc/uguide/Makefile.am: Remove app_math.txt.

	* doc/examples/Makefile.am: Changed example1.arts to auto_example1.arts.

	* arts-0-0-265

	* doc/index.html: Changed names of example1.arts and full.arts to
	auto_ 
	Replaced h2o.arts by cont.arts.

	* doc/examples/auto_example1.arts.in: Created from example1.arts.

	* doc/examples/example1.arts: Removed.

	* doc/uguide/development.tex: Fixed TeX warnings and updated.

	* doc/uguide/app_math.tex: Removed.

	* doc/uguide/main.tex: Removed appendix with math
	operations. Commented out app_units. What was this appendix? Who
	removed it? There is no ChangeLog entry.
	
2001-10-05  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-264

	* Further work on AUG. I have now quickly gone through "my" parts and
	removed the worst problems. The text should now be more or less correct
	but not everything is described (far from).

	* Made sure that the analytical version of kTemp is not used with
	emission=0.
	
2001-10-05  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-263

	* The example auto_full is now up to date and runs. Good work Oliver
	to set the path to data dirs automatically.

	* There were a lot of old files in .cvsignore for the examples folder.
	You should remove the old files. The following can be removed full.*
	h2o.* sparse.* uwe.* *.am 
	
	* Fixed a bug for n2_absSet and h2o_absSet. For example, n2_abs_Set
	searched for the first tag group where the tag string starts with N2
	and instead of finding the N2 tag group, N2O could be found. The
	functions now search for N2- and H2O-.

2001-10-04  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-262

	* Removed some old control files in doc/example. The remaining examples
	are: auto_full, example1 and amsu. (I will update auto_full ASAP).

	* Worked on the sensor, data reduction and utility chapters in AUG.
	The calibration section is removed as the calibration can be done
	in a better way than I realised. It is possible to do the inversions 
	with Rayleigh-Jean temperatures if the calibration is performed
	correctly. 
	
2001-10-04  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-261

	* src/methods.cc (define_md_data): Added tgsDefineAllInScenario.

	* src/m_abs.cc (tgsDefineAllInScenario): Added this method.

	* doc/examples/example1.arts: Quick fix so that this file runs
	now, using the new method to select all species. Now there is a
	runtime error in absCalc, because the partiton function for one
	OCS isotope is not set.

	* src/species_data.cc (define_basic_species_data): Set degfr=0 for
	cloud species. This has no effect since it is not used.

2001-09-25  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-0-260

	* doc/uguide/absoption.tex: Continued to work on this.
	Edited the whole Line Section.
 
2001-10-04  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-259
	
	* doc/doxygen/doxygen.css: Added stylesheet definitions for
	doxygen documentation to match the style of our satpage.
	
	* doc/doxygen/Doxyfile.in: Added default stylesheet.

2001-10-04  Viju O.-J.  <vojohn@uni-bremen.de>

	* arts-0-0-258
	
	* doc/examples/amsu.arts: Minor changes in amsu.arts

2001-10-04  Viju O.-J.  <vojohn@uni-bremen.de>	

	* arts-0-0-257
	
	* doc/examples/f_mono.out: Included monochromatic frequency file
	for AMSU

	* doc/examples/amsu.arts: Included a control file for AMSU

2001-10-02  Oliver Lemke  <olemke@uni-bremen.de>

        * arts-0-0-256
	
	* doc/doxygen/Makefile.am: Made the generation depending on
	ARTS_GENDOCS. If ARTS_GENDOCS is not defined then skip the doxygen
	run.

	* doc/uguide/Makefile.am: Made the generation of uguide.ps and
	uguide_pdf.pdf depending on ARTS_GENDOCS. If ARTS_GENDOCS is not
	defined the dummy targets are used.

	Added auto_version.tex to target dependencies.

	* Makefile.am: Added doc permanently to subdirs. Otherwise the
	documentation is only installed in maintainer-mode. But what we
	want is to only re-generate the docs in maintainer mode but
	install it always.

	* configure.in: Added -g to CXXFLAGS_FIXED when debug is enabled.
	Corrected CXXFLAGS_FIXED in maintainer mode (warning flags where
	added twice).

2001-10-02  Stefan Buehler  <sbuehler@uni-bremen.de>

        * arts-0-0-255

	* src/math_funcs.cc (check_ncol_nrow): Added this check function.
	All check functions: Removed newline at end of message.

	* src/workspace.cc (define_wsv_data): Added h.

	* src/methods.cc (define_md_data): Added methods
	VectorMatrixMultiply and MatrixMatrixMultiply.

	* src/m_io.cc (VectorMatrixMultiply): Added this method.
	(MatrixMatrixMultiply): Added this method.

2001-10-02  Oliver Lemke  <olemke@uni-bremen.de>

        * arts-0-0-254
	
	* configure.in: Added default sizes for cross-compiling to all
	AC_CHECK_SIZEOF calls to avoid the autoconf warnings (AC_TRY_RUN
	called without ....).

2001-10-02  Oliver Lemke  <olemke@uni-bremen.de>

        * arts-0-0-253
	
	* doc/uguide/absorption.tex: Removed ending .eps for
	refractive_water_comp_T.eps, LWCcloud.eps and IWCcloud.eps.

	* doc/examples/.cvsignore: Added all auto_full.* files except
	auto_full.arts.in.

2001-10-02  Stefan Buehler  <sbuehler@uni-bremen.de>

        * arts-0-0-252

	* src/methods.cc (define_md_data): Added method lines_per_tgSetEmpty.

	* src/m_abs.cc (lines_per_tgSetEmpty): Added this method.

2001-10-01  Oliver Lemke  <olemke@uni-bremen.de>

        * arts-0-0-251
	
	* doc/uguide/Makefile.am (uguide_pdf.pdf): Pipe the output of the
	first two latex runs into /dev/null.
	(uguide.dvi): Pipe the output of the first two latex runs into
	/dev/null.

	* configure.in: auto_full.arts is now always generated, even if
	arts-data is not installed. Because the optional generation
	does not work on older autoconf versions :-(
	
2001-09-25  Thomas Kuhn  <tkuhn@uni-bremen.de>
 
        * arts-0-0-250
 
        * corrections since the version arts-0-0-249 didn't worked!

2001-09-25  Thomas Kuhn  <tkuhn@uni-bremen.de>
 
        * arts-0-0-249
 
        * doc/uguide/absoption.tex: Continued to work on this.
        Edited the continuum and full model description.

2001-09-25  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-0-248

	* doc/uguide/absoption.tex: Continued to work on this.
	Edited the Line Shape Section.

2001-10-01  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-247

	* Worked on the on-line information for vector and matrix math 
	functions (such as VectorSet). Removed VectorSetFromArrayofVector
	as the selection was done by index and we have decided that such
	functions shall be removed (not safe with selection by index).

	* Wrote a section on the scope of ARTS fof chapter 1 of AUG

	* Work on chapters 2, 4 and 5 of AUG. Some text removed, some text 
	added. Control file examples added for los/rte calculations. 
	  
	* Removed tex-ing warnings in "my" part of the ps-version of AUG 
	(just 2, out of a large number warnings).
	
2001-09-28  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-246

	* An incorrect assert fixed in kContAbs

	* auto_wsv.txt now used in AMI instead of wsv.txt.

	* wsv.txt removed from /src (again?)

	* Fixed an incorrect error message when a variable of incorrect type
	is selected as global input or output. 

	* Updated read_datafile to handle ArrayOfIndex (instead of 
	ArrayOfSizet).
	
2001-09-28  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-245

	* Due to a problem in the HDF part, I couldn't easily check what I did
	yeasterday. There were plenty of bugs in the input checks. These
	are removed. My test case is at least running.

	* On-line info for kTemp written.

	* Conversion to brightness temperatures moved to functions invplanck
	and invrayjean (placed in atm_funcs). This mainly to avoid repeated
	output when converting a WF-matrix.

2001-09-28  Claudia Emde  <emde@uni-bremen.de>

	* arts-0-0-244	
	
	* src/methods.cc : changed absorption methods again

2001-09-27  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-243
	
	* src/main.cc (main): Added info about HDF support to --version
	option.

	* configure.in: Removed LF_SET_WARNINGS.
	Bug fix in HDF stuff.

	Added option --enable-warnings which appends -W -Wall to CFLAGS and
	CXXFLAGS. Disabled by default.

2001-09-27  Sreerekha T.R.  <rekha@uni-bremen.de>
	
	* arts-0-0-242
	
	* TODO: Added a new TODO.

	* src/methods.cc (define_md_data):  Changed the online
	documentation of the following methods:
	- linesWriteAscii
	- lines_per_tgWriteAscii
	- lines_per_tgReadFromCatalogues
	- linesReadFromHitran
	- linesReadFromMytran2
	- linesReadFromJpl
	- linesReadFromArts
	- linesElowToJoule
	- lines_per_tgCreateFromLines
	- lines_per_tgAddMirrorLines
	- lines_per_tgCompact
	
2001-09-27  Viju O.-J.  <vojohn@uni-bremen.de>

	* arts-0-0-241
	
	* src/methods.cc (define_md_data): Changed the online
	documentation of the following methods:
	- raw_vmrsReadFromFiles
	- raw_vmrsReadFromScenario
	- AtmFromRaw
	- h2o_absSet
	- n2_absSet
	- vmrsScale
	
2001-09-27  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-240

	* Revised the weighting function functions. Some function names
	and some keyword input have been changed. The aim has been to have
	a single function for each retrieval type. However, there are two
	versions for species. On-line information updated and check of
	function input is added.

	* kSpeciesAll is now called kSpecies as this should be the standard
	function for species. The old kSpecies is now called kSpeciesSingle.

	* There is a problem with kSpecies and vmrs. It is now assumed
	that vmrs has the same length as abs_per_tgs, but this is now not
	the case. I will fix this later.
	
	* There is now only a single kContAbs function. See the on-line info.

	* There is now only a single kTemp function. See the on-line info.
	
	* No bigger bug checks. Will be done.
	
2001-09-27  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-239
	
	* src/Makefile.am (species_data.o): Added dependencies.
	(methods.o): Added dependencies.

2001-09-27  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-238
	
	* src/methods.cc (define_md_data): Updated the docs of the Ascii
	methods to match the style guide.

	* src/Makefile.am: Removed LDADD. No longer needed because the
	libraries are automatically detected and set by configure.

	Added special targets for methods.cc and species_data.cc.

	* configure.in: Added library checks for libjpeg, libdf and libz
	(needed by HDF).

	Introduced an extra compiler flag variable CXXFLAGS_FIXED which is
	used to compile methods.cc and species_data.cc to avoid the
	exorbitant compilation time.

	Added a new configure flag called --enable-debug /
	--disable-debug. By default debugging is enabled.
	
2001-09-27  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-237

	* Revised the following parts: refraction, ground, emission, and hse.
	Improved on-line information and more checks of input.

	* Moved everything connected generation of random data to a file
	called rand.old. The random functions are not used now. As I don't
	like to have larger pieces of old code hanging around (even if 
	commented out), I moved it to a special file. Maybe not the best
	solution, but what to do?

	* Removed special functions for transmission calcultions (xxxTau).
	I did this as there is no cost to call sourceCalc when emission=0
	(source is set to be empty).
	
2001-09-26  Nikolay Koulev  <nkoulev@uni-bremen.de>
	
	* arts-0-0-236

	* doc/uguide/absoption.tex: Continued to work on this.
	Edited the Partition Function subsection
	
2001-09-26  Claudia Emde  <emde@uni-bremen.de>
	
	* arts-0-0-235

	* src/methods.cc: format of absorption methods changed

2001-09-26  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-234
	
	* configure.in: Added debugging switch.
	
	* src/Makefile.am: Corrected LD_ADD. Quick fix, needs further work.

	* src/methods.cc:  Added include config.h.
	
	* src/m_batch.cc: Added include config.h.
	
	* src/m_hdf.cc: Added include config.h.

2001-09-26  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-233

	* I didn't manage to link the program after Oliver's last commit, but 
	I must commit to move changes to the laptop.

	* Improved text for WSV in workspace.cc for "my" variables. Can someone
	elso look at the remaining variables.

	* Some WSV are removed: f_sensor, za_sensor, i_cal...

	* I did this as the sensor is totally removed from ARTS. 

	* The TB and TRJ functions changed to take f_mono and za_pencil as 
	input. 

	* The function yLoadCalibration removed (I know think this function
	is not needed. It is possible to make the load switching smarter than
	I realised. The corresponding part in AUG will be removed.)

2001-09-26  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-232

	* src/Makefile.am: Set the appropriate LD_FLAGS depending on
	HDF_SUPPORT.

	* src/wsv.txt: Renamed to auto_wsv.txt and removed from
	repository.

	* src/make_auto_wsv_h.cc (main): Renamed output file wsv.txt to
	auto_wsv.txt.

	* src/m_batch.cc: Put an #ifdef / #endif block around the whole file.

	* src/m_hdf.cc: Put an #ifdef / #endif block around the whole file.

	* configure.in: Added AM_CONDITIONAL for HDF_SUPPORT.

	* src/methods.cc (define_md_data): Added #ifdef / #endif block
	around all HDF requiring functions incl. ybatchCalc.

2001-09-26  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-231

	* Changed the LOS type name from LOS to Los (but the acronym for the
	line-of-sight is still LOS).

	* Moved everything connected to the binary HDF files to m_hdf.cc.
	
2001-09-25  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-230
	
	* src/Makefile.am: Completely rewritten to get rid of the
	BUILT_SOURCES stuff. Now also the clean targets work properly.

	* Makefile.am (DEFAULT_SUBDIRS): Added aii directory.

	* ami/Makefile.am (SUBDIRS): Added general directory.

2001-09-25  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-0-229

	* doc/uguide/absoption.tex: Continued to work on this.
	Edited the Partition Function subsection
	
2001-09-25  Nikolay Koulev  <nkoulev@uni-bremen.de>

	* arts-0-0-228

	* doc/uguide/absoption.tex: Continued to work on this.
	Included the Partition Function subsection

2001-09-25  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-227

	* src/m_abs.cc (linesReadFromArts): Reset lines at the start of
	the function. 
	(linesReadFromHitran): Reset lines at the start of
	the function. 
	(linesReadFromJpl): Reset lines at the start of
	the function. 
	(linesReadFromMytran2): Reset lines at the start of
	the function. 

	* doc/uguide/formats.tex: Continued to work on this.

2001-09-24  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-226

	* src/Makefile.am: Removed outdated comment about doxygen docu.

	* doc/uguide/formats.tex: Worked a bit on this section of AUG. 

	* TODO: Cleaned up a bit.

2001-09-24  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-225

	* First cleanup of all Makefile.am files (all except src dir).
	
	NOTE: Please remember to add your new files also to the
	Makefile.am files. It is a real mess when you have to go through
	all directories and search for Makefile.am files which are not in
	sync with the files in the corresponding directory.
	
	* doc/uguide/Figs/Makefile.am (EXTRA_DIST): Added a whole bunch of
	missing graphic files: fig_bendingangle.eps, fig_bendingangle.pdf,
	fig_bendingangle.m, fig_calerror.m, fig_calerror_tb_1.eps,
	fig_calerror_tb_1.pdf, fig_calerror_tb_2.eps,
	fig_calerror_tb_2.pdf, fig_calerror_trj_1.eps,
	fig_calerror_trj_1.pdf, fig_calerror_trj_2.eps,
	fig_calerror_trj_2.pdf.

	* doc/uguide/Makefile.am (uguidedocdir): Renamed from thisdocdir.
	
	* doc/uguide/Makefile.am: Cosmetics. 
	
	* configure.in: Added AM_CONDITIONAL for ARTS_MAINTAINER_MODE and
	ARTS_DATA_PATH.

	* doc/examples/Makefile.am: Install examples depending on arts-data
	packages only when arts-data was found during configure.
	(examplesdoc_DATA): Renamed from thisdoc_DATA.
	(examplesdocdir): Renamed from thisdocdir.

	* aii/Makefile.am (aii_DATA): Renamed from this_DATA.
	
	* aii/Makefile.am (aiidir): Renamed from thisdir.

	* aii/Makefile.am (aii_DATA): Added aii_color_table.pro,
	aii_epilogue.pro, aii_klegend_d.pro, aii_plot_file.pro,
	aii_plot_legend.pro, aii_plotsymbols.pro, aii_prologue_l.pro,
	plot_abs_per_tg.pro, plot_vmr_per_tg.pro, read_tag_groups.pro,
	showme.pro, sort_abs.pro.

	* ami/Makefile.am (ami_DATA): Added README.

	* ami/plot/Makefile.am (EXTRA_DIST): Added axes_1xn.m, axes_nx1.m,
	text3.m, title2.m, xlabel2.m, ylabel2.m, zlabel2.m.

	* ami/math/Makefile.am (EXTRA_DIST): Added sFromFile.m.

	* ami/hmatrix/Makefile.am (EXTRA_DIST): Added hRedKx.m, hRedLimb.m.

	* ami/general/Makefile.am (EXTRA_DIST): Added amenu.m, whoami.m.

	* ami/file/Makefile.am (EXTRA_DIST): Added write_linefile.m.

	* ami/arts/Makefile.am (EXTRA_DIST): Removed out.m.

	* src/Makefile.am (make_auto_wsv_h_SOURCES): Removed hmatrix.
	(make_auto_md_h_SOURCES): Removed hmatrix.
	(make_auto_md_cc_SOURCES): Removed hmatrix.

	* src/methods.cc (define_md_data): Fixed typo.
	
2001-09-24  Mashrab  <kmashrab@uni-bremen.de>

	* arts-0-0-224
	
	* src/methods.cc: Updated online docs for binary
	read-write methods.

2001-09-24  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-223

	* src/methods.cc (define_md_data): Updated online doc for Exit,
	Test, cont_descriptionInit, and cont_descriptionAppend.
	
2001-09-24  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-222
	
	* src/methods.cc (define_md_data): Updated online docs for ASCII
	read-write methods.

2001-09-21  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-221
	
	* configure.in: Added new options:

	  --with-arts-data=ARG: This should be set to the location where
	  the arts-data package is installed. Per default it is set to
	  $PREFIX/share/arts-data. If you run configure on a smiles pc it
	  is set to /pool/lookup2/arts-data.

	  The data path can now be automatically inserted into the example
	  files.

	  There's also a define called ARTS_DATA_PATH in config.h.

	  --without-arts-data: Force arts to not use the arts-data package
	  even if it is installed.

	  --with-hdf, --without-hdf: As default, if hdf is installed on
	  the system, support for reading/writing binary files is
	  automatically compiled in. --without-hdf forces the deactivation
	  of HDF support.

	  NOTE: This is a dummy at the moment. The option is there but has
	  no effect on compilation.

	* doc/examples/auto_full.arts.in: Example control file with
	automatic data path expansion.

2001-09-21  Mashrab  <kmashrab@uni-bremen.de>

	* arts-0-0-220

	* src/methods.cc (define_md_data): Updated online docs for binary
	read-write methods.
	
2001-09-21  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-219
	
	* src/m_abs.cc (tgsDefine): Fixed bug: Use resize function!

2001-09-21  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-218

	* General: Bux fixes.
	
	* src/matpackI.h (Range::Range): Allow zero stride in Range
	constructor. This means that (0,0) matrices can be created. 
	(Matrix::resize): Put in some assertions that arguments are >=0.
	(Matrix::Matrix): Removed the special case that the original
	matrix is zero. This is no longer necessary, because of the change
	of Range::Range.
	(Matrix::operator=): Added MatrixView = Matrix operator. This is
	important, otherwise default assignment operator is used. That's
	exactly similar to the VectorView = Vector case.

	* src/m_wfs.cc (k_append): Initialize temp. copies of Kx data
	directly, instead of copying. Makes the code a bit shorter.

2001-09-21  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-217
	
	* src/methods.cc, src/m_abs.cc, src/workspace.cc:
	Renamed the following methods and variables:
	
	  - raw_ptz_1d to raw_ptz
	  - raw_vmrs_1d to raw_vmrs
	  - raw_vmrs_1dReadFromFiles to raw_vmrsReadFromFiles
	  - raw_vmrs_1dReadFromScenario to raw_vmrsReadFromScenario
	  - AtmFromRaw1D to AtmFromRaw

	* src/methods.cc (define_md_data): Removed Atm2dFromRaw1D

	* src/m_abs.cc: Removed Atm2dFromRaw1D

	* src/workspace.cc (define_wsv_data): Removed t_abs_2d, z_abs_2d,
	vmrs_2d and abs_2d

	* doc/uguide/.cvsignore: Changed version.tex to auto_version.tex

	* TODO: Added thoughts about making HDF support optional.
	
2001-09-21  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-216

	* configure.in: Removed the O0 flags for the end user
	mode. Beware, with optimization not all files compile. But I want
	to test how much faster the program has got...
	
2001-09-21  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-215

	* General: Changed default ascii file extensions from .am to .aa.
	Fixed bug that lead to spectra being zero. (Hopefully)

	* src/methods.cc (define_md_data): Changed default ascii file
	extensions from .am to .aa. 

	* src/m_abs.cc (raw_vmrs_1dReadFromFiles): Changed default ascii
	file extensions from .am to .aa. 

	* src/matpackI.h (operator=): Added an assignment operator for
	VectorView = Vector. In that case only the reference was copied
	before. Assignment operators have proven so far the biggest bug
	source in Matpack! There could be more...

2001-09-21  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-214
	
	* doc/uguide/Makefile.am (MAINTAINERCLEANFILES): Changed
	version.tex to auto_version.tex

	* configure.in: Changed version.tex to auto_version.tex

	* doc/uguide/main.tex: Changed version.tex to auto_version.tex

	* doc/uguide/auto_version.tex.in: Renamed version.tex.in
	
2001-09-20  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-213

	* src/species_data.cc (define_basic_species_data): Rearranged the
	order of the isotopes for CH3CN. Now the program runs
	again. (There is an assertion to ensure that the isotopes of each
	species are sorted according to decreasing isotopic ratio.)

	* src/partition_function_data.cc (define_partition_species_data):
	Rearranged the order also here. Order in both files must be the
	same! 

2001-09-20  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-212

	* WARNING: This version does not run.
	
	* Large parts of ARTS are removed. Everything connected with the
	covariance and H matrices is removed. Of the batch part, only the
	core calculation function remains, that is now called ybatchCalc.

	* The math_funcs files cleaned up a bit. 

	* The assert_xxx functions renemed to check_xxx. They are found at
	the end of math_funcs. (I have not got time to more of these 
	functions).
	
2001-09-20  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-211

	* General: Fixed Bug related to linspace/nlinspace. A return
	version makes no sense anymore, since the target in Matpack has to
	have the right dimension. So you would have to resize the target
	before calling. But then the non-return version is more
	convenient, because it can adjust the size of the output vector
	itself.
	
	* src/math_funcs.cc (linspace): Removed return version.
	(nlinspace): Removed return version.

	* src/m_wfs.cc (LinAltsFromPres): Use non-return version of linspace.

	* src/m_los.cc (los_1za): Use non-return version of linspace.

	* src/m_io.cc (VectorLinSpace): Use non-return version of linspace.
	(VectorNLinSpace): Use non-return version of nlinspace.

	* src/m_covmatrix.cc (sSimple): Use non-return version of linspace.

	* doc/uguide/version.tex: Removed this file from CVS, it is
	automatically generated by configure.

2001-09-20  Axel von Engeln  <engeln@uni-bremen.de>

	* arts-0-0-210

	* partition_function_data.cc: added species CH3CN, HNC there is no
	vibrational correction to these species, if they are know,
	part. fct. can be recalculated.
		
	* species_data.cc: added species CH3CN, HNC

2001-09-20  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-209
	
	* configure.in: Changed AC_VERBOSE to AC_MSG_RESULT.
	
2001-09-20  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-208

	* reconf: Pass --enable-maintainer-mode and all options given to
	reconf to configure.

	* src/file.cc: Added cfloat to includes for compatibility with glibc 2.2.x
	
	* configure.in: Added several configure options
	
	  --enable-maintainer-mode: For arts developers. Activates debug
	  compiler flags and documentation generation.

	  --enable-docs: Same as before. Used to regenerate the documentian
	  even without activating maintainer-mode.

	  --with-numeric-type=ARG: The default floating-point type is
	  double. You can change this by giving float as ARG.

	  --with-integer-type=ARG: The default integer type in arts is
	  long. You can give short, int, long or size_t as ARG. WARNING: Only
	  change this if you know what you're doing because not every type
	  may work. Depends on the operating system.

	Added a check for HDF4 header files and libraries.

	Added check for doxygen, latex and pdflatex if documentation
	generation is activated.

	Added a configuration summary output after the configure script
	run is complete.

	Re-ordered the test sequence. Basic tests first, higher level tests
	at the end.

	* src/arts.h: Changed typedefs for Numeric and Index to be set to
	the types specified in config.h.

2001-09-20  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-207

	* doc/uguide/main.tex (paragraph{#1}}): Moved setting of tocdepth
	counter to uguide_pdf.tex and uguide.tex.

	* doc/uguide/uguide.tex: Added the tocdepth counter.

	* doc/uguide/uguide_pdf.tex: Increase the depth of the table of
	contents to three for the pdf version. That means, that also minor
	headings will be displayed. This is useful, because one can jump
	directly to the subsection by mouseclick with the Acrobat reader.

	* src/make_auto_wsv_pointers_cc.cc (main): Corrected program name
	in doxygen header and output file.

	* src/make_auto_wsv_h.cc (main): Corrected program name
	in doxygen header and output file.

	* src/make_auto_wsv_groups_h.cc (main): Corrected program name
	in doxygen header and output file.

	* src/make_auto_md_h.cc (main): Corrected program name
	in doxygen header and output file.

	* src/make_auto_md_cc.cc (main): Corrected program name
	in doxygen header and output file.

	* *.cc, *.h: Added GPL to files where it was missing. Updated JPL
	(year and authors).

2001-09-19  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-206

	* Major Change: The entire version number is now set in
	configure.in. Important: YOU HAVE TO DO A reconf AFTER YOU CHANGED
	THE VERSION NUMBER!

	* Major Change: Adapted ARTS to the homegrown atomic types. We
	have now:

	Index, Numeric, String
	Vector, Matrix, Array<>

	Predefined Array types are called, e.g., ArrayOfString. Note the
	capital O!

	These data types behave more or less as one should
	expect. Important: The = operator copies the contents, not the
	entire thing. Therefore, you must be certain that dimensions agree
	(or use the .resize functions before using the = operator). There
	are assertions built in the data type that should catch that kind
	of error. Documentation will follow in the near future.

	* doc/examples/cont.arts: Verified that we still get the same
	absorption coefficients. None of the other example files are
	working, so I had no easy way to verify that other methods still
	run. 
	
	* src/methods.cc (define_md_data): A part of the documentation of
	method linesReadFromMytran2 has been deleted by Patrick apparently
	by accident. Put this back in. 

	* src/m_abs.cc (raw_vmrs_1dReadFromFiles): Rewritten this. Use the
	standard function get_tagindex_for_Strings to get tag indices!

	* reconf: Now also runs configure automatically.

2001-09-19  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-205

	* !!!! Corrected a bug in sFRomFile.m for gaussian correlation 
	function. If you have used this option in Qpack, your results have
	been wrong. 

	* WF(s) for ground emission is now implemented. The function is 
	called kEground. See the online help.

	* The file methods.cc now includes (at the top) templates for writing
	the information for the online help. Please comment this suggestion
	to format. The information for the function zaFromDelta is in this
	format. 

	* I have tried to make the output for the online help a bit clearer
	and nicer by putting in some space and lines.

	* Started a series of assert functions to be used to check the input
	to functions. These functions are for the moment found at the end of
	math_funcs.cc. Please add more similar functions. An example:

	   assert_lengths( f_mono, "F_MONO", e_ground, "E_GROUND" );

	will check if the ground emission vector has the correct length and
	issue an informative error message if this is not the case.
	
2001-09-17  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-204

	* Stefan had changed the data type coding used for the binary files.
	This is changed back (sorry Stefan). The aim of being 100% consistent
	is good but in this case it would have just caused problems. As the
	binary file format is just a temporary solution I didn't see the point
	to spend a lot of time to convey Stefan's changes to AMI (this would
	have taken a lot of time, made old data files useless etc). 

	* Minor changes in out.m and sFromFile.m
	
2001-09-13  Nikolay Koulev <nkoulev@uni-bremen.de>

	* arts-0-0-203

	* doc/uguide/absorption.tex: Started to update 
	
	* doc/uguide/main.tex, doc/uguide/uguide.tex: Corrected some bugs.
	
2001-09-05  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-202

	* doc/uguide/formats.tex: Started to update this part of the User
	Guide to the new math package and data types.

	* src/arts.h: Added typedef for String.

	* globally: Replaced string by String, so that all atomic types
	have consistent notation.

2001-09-04  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-201

	* Major change: Globally replaced:
	INDEX  by Index
	VECTOR by Vector
	MATRIX by Matrix
	ARRAY  by Array

	This is the first step toward putting in the new Vector/Matrix
	data types.

	WARNING: I will try to do this work in the next two weeks. This
	means there will be changes all over the code. I have to start
	now, otherwise it will be too late to meet the deadline given by
	the HWK workshop in October. Keep your fingers crossed...

	* src/matpackI.h: Added

	* src/matpackII.h: Added

	* src/test_matpack.cc: Added

2001-09-03  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-200

	* Added function sFromFile.m in /ami/math, equivalent
	to the obsolete -one day- sFromFile arts method, see
	the mscript help.

2001-09-03  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-199

	* Added function hRedLimb to ami/hmatrix to make a
	reduction of a limb spectral space optimized for
	each retrieval point and species, obviously only
	to be used with an inversion method doing individual
	retrievals for each retrieval point, e.g. an ensemble
	of neural nests. Just implemented, ergo no bugs free,
	use with caution.

2001-08-24  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-198

	* Added functions axes_1xn/nx1 to ami/plot

2001-08-22  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-197

	* Included a Matlab script to produce a figure testing the
	refraction ray tracing scheme by plotting the bending angle. This
	will be described AUG later when I will make the writing for the first
	release.

	* I did not spend any time on it, but it seems that there are teching
	errors in AUG. Fix please.
	
2001-08-22  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-196

	* partition_function_data.cc, species_data.cc,
	continua.cc and continua.h, adding a new N2 continua 
	parameterization called N2-SelfCont following
	Rosenkranz 93 but with the strength constant C and 
	all exponents ( Xt temp, Xp pres, Xf freq) as parameters.
	Implemented to have at least a continua term where the
	frequency dependence can be suppressed so one can
	play around. So far used e.g. to simulate the defocusing
	effect on a satellite-satellite transmission link at
	low altitudes, that seems to correspond to an attenuation
	in the signal independent of frequency.

2001-08-22  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-195

	* fixing bug in method zaFromDeltat after
	validation of refaction calculations by Patrick
	
2001-08-15  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-194

	* Added some functions to ami/plot to easily set font size and
	weights in figures. These functions have the same name as the
	standard Matlab functions with 2 appended, e.g. xlabel2.

2001-08-15  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-193

	* whoami.m and amenu.m added to ami/general

	* write_linefile.m updated to ARTSCAT-3. 
	
2001-08-08  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-192

	* Commenting out a line printing out O2ABS, kind of 
	bothering

2001-08-07  Thomas Kuhn  <tkuhn@uni-bremen.de>
	
        * arts-0-0-191

	* changes: 
	  - Aded O2-MPM93 oxygen absorption model of Liebe et al.
	  - implemented a linear extrapolation of the cloud LWC/IWC 
	    profile.
	  - Added the possibility to set the water vapor VMR to the 
	    saturation value over water/ice within a water/ice cloud.
	    This is implemented in AtmFromRaw1D, hwere one has now 
	    the option of AtmFromRaw1D{CloudSatWV = "yes"} to do this
	    VMP profile modification.

2001-07-30  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-190

	* commenting out a line printing out za angles in m_batch.cc
	left after some debugging ... guessing

	* adding workspace method SymmetricCopy in /src/m_io.cc

	* adding /ami/hmatrix/hRedKx to do reduction based on 
	weighting functions

2001-07-26  Oliver Lemke  <olemke@core-dump.net>

	* arts-0-0-189

	* doc/doxygen/Makefile.am: Renamed make_* source files to make_auto_*.
	
2001-07-24  Oliver Lemke  <olemke@core-dump.net>

	* arts-0-0-188

	* src/Makefile.am: Renamed make_* source files to make_auto_*.
	
	* src/.cvsignore: Renamed make_* files to make_auto_*.

	* src/make_md_cc.cc: Renamed to make_auto_md_cc.cc.

	* src/make_md_h.cc: Renamed to make_auto_md_h.cc.

	* src/make_wsv_groups_h.cc: Renamed to make_auto_wsv_groups_h.cc.

	* src/make_wsv_h.cc: Renamed to make_auto_wsv_h.cc.

	* src/make_wsv_pointers_cc.cc: Renamed to make_auto_wsv_pointers_cc.cc.
	
2001-07-24  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-187

	* Major Change: Added a new command line parameter --input
	(-i). This is complementary to the --methods switch. It must be
	given the name of a variable (or group). Then it lists all methods
	that take this variable (or group) as input.
	
	* src/main.cc (main): Added command line parameter -i/--input.
	(option_input): Added this function, to take care of the new
	command line parameter.

	* src/parameters.h: Added command line parameter -i/--input.

	* src/parameters.cc (get_parameters): Added command line parameter
	-i/--input.

	* src/.cvsignore: Updated and cleaned up a bit.

2001-07-23  Oliver Lemke  <olemke@core-dump.net>

	* arts-0-0-186

	* src/make_md_h.cc: Renamed md.h to auto_md.h and md.cc to auto_md.cc.
 	Moved auto_md.cc creation to src/make_md_cc.cc.
	
	* src/make_md_cc.cc: Moved creation of auto_md.cc to this file.
	
	* src/Makefile.am: Changed names for auto-generated files. And added
	make_md_cc.

	* src/make_wsv_pointers_cc.cc: Renamed wsv_pointers.cc to
	auto_wsv_pointers.cc.

	* src/make_wsv_h.cc: Renamed wsv.h to auto_wsv.h.

	* src/make_wsv_groups_h.cc: Renamed wsv_groups.h to auto_wsv_groups.h.

2001-07-11  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-185

	* data: Data directory and all subdirectories removed.
	Use package arts-data!!!!

	* configure.in: Removed Makefile entries for data dir and subdirs.
	
	* Makefile.am: Removed data from subdirectories.
	
2001-07-05  Stefan Buehler  <sbuehler@uni-bremen.de>

        * arts-0-0-184

	* doc/uguide/absorption.tex: Added this file, which should contain
	documentation for the absorption part of ARTS.

2001-06-26  Thomas Kuhn  <tkuhn@uni-bremen.de>

        * arts-0-0-183

	* changes: 
	change of the H2O absorption model calculation.The models 
	"H2O-CP98",
        "H2O-MPM87",
        "H2O-MPM89",
        "H2O-MPM93",
        "H2O-PWR98",
	have now no input parameters.
	The naming convention has changed for the ordinary
	H2O continuum, they are now called "H2O-SelfContStandardType" and 
        "H2O-ForeignContStandardType". They need two input parameters
	each. Typical values can be found in the xample control file
	doc/example/cont.arts.
	Also no input parameters have now:
	"H2O-ContMPM93", 
	"O2-PWR93",
	"CO2-SelfContPWR93",
	"CO2-ForeignContPWR93",
        "liquidcloud-MPM93",
        "icecloud-MPM93".
	Additionally the name of "O2-PWR93O2" is changed to "O2-PWR93".
	The temperature constraint in "icecloud-MPM93" is removed, one 
	can calculate ice particle clouds at all temperatures, as for 
	for liquid water clouds.
	* src/continuum.cc: implementation of the O2 and N2 continuum
	absorption model of MPM93. They are called  "O2-SelfContMPM93" and
	"N2-SelfContMPM93". The broadening is calculated with dry air 
	(= all species minus water vapor).

2001-06-26  Stefan Buehler  <sbuehler@uni-bremen.de>

        * arts-0-0-182

	* Major change: Changed unit of lower state energy in LineRecord
	and ARTS catalogue file from cm^-1 to Joule (ARTSCAT-3). Verified
	that the absorption coefficients are still the same for:
	1. H2O calculation from HITRAN catalogue.
	2. O2 calculation, using one of Axel's line files with overlap.

	* src/absorption.cc (xsec_species): Lower state energy does not
	have to be converted to Joule anymore.
	(wavenumber_to_joule): Added this little helper function, which
	converts energy from wavenumber to Joule.
	(ReadFromHitranStream): Convert lower state energy to Joule, using
	the helper function wavenumber_to_joule().
	(ReadFromJplStream): Convert lower state energy to Joule, using
	the helper function wavenumber_to_joule().
	(ReadFromMytran2Stream): Convert lower state energy to Joule, using
	the helper function wavenumber_to_joule().

	* src/absorption.h: Made linesElowToJoule a friend of LineRecord.
	(class LineRecord): Changed mversion from 2 to 3.
	
	* src/methods.cc (define_md_data): Added method linesElowToJoule.

	* src/m_abs.cc (linesElowToJoule): This is just a helper method
	for the catalogue conversion. Can be removed, as soon as we are
	sure there are no more old files around. It uses the conversion
	function wavenumber_to_joule().

	* data/spectroscopy/arts/o2_spin_rot.aa: Converted lower state energy to Joule.

	* data/spectroscopy/arts/o2_spin_rot_hit.aa: Converted lower state energy to Joule.

	* data/spectroscopy/arts/o2_spin_rot_jpl.aa: Converted lower state energy to Joule.

	* data/spectroscopy/arts/o2_spin_rot_pwr.aa: Converted lower state energy to Joule.

	* data/spectroscopy/arts/o2_spin_rot_pwr_1.aa: Converted lower state energy to Joule.

	* data/spectroscopy/arts/o2_spin_rot_pwr_2.aa: Converted lower state energy to Joule.

	* data/spectroscopy/arts/o2_spin_rot_pwr_3.aa: Converted lower state energy to Joule.

2001-06-25  Stefan Buehler  <sbuehler@uni-bremen.de>

        * arts-0-0-181

	* Major changes: Changed ARRAY implementation back to STL. This
	fixed the bug with the AUX parameters for lineshape with
	overlap. Renamed line files to .aa. Details below.
	
	* data/spectroscopy/arts: Renamed line files to `.aa' instead of `.al'.

	* src/methods.cc (define_md_data): Changed name of
	linesWriteToFile to linesWriteAscii and name of
	lines_per_tgWriteToFile to lines_per_tgWriteAscii.

	* src/vecmat.h (ARRAY): ARRAY is now once more STL based. 

	* src/make_md_h.cc (main): Adapted to ARRAY change. The removal of
	WSVs that are both input and output used the erase_vector_element
	function. Now it uses std::vector<>::erase. This task occurs in
	two places, for md.h and md.cc.

	* src/absorption.cc (get_tag_group_index_for_tag_group): Updated
	documentation. Cleaned up.
	(xsec_species): Verified that now the AUX parameters for the
	overlap are getting there. So it was indeed an MTL bug that lead
	to the AUX parameters getting lost. I don't know how the oxygen
	spectrum could have been correct last week, it remains a
	mystery. My suspicion is that it never worked since the ARRAY
	implementation was set to MTL.

	The absorption calculation using explcit lines still has to be
	compared to the original Rosenkranz function. Thomas will do this
	when he is back from Lindau.

	* src/m_abs.cc (lines_per_tgAddMirrorLines): Adapted to ARRAY
	change. Cleaned up the function and made it much simpler. Now the
	mirror lines are simply appended after the original lines. That
	way, no copying of the lines is needed.
	(lines_per_tgCompact): Adapted to ARRAY change. Added safety check
	that f_mono is sorted. Cleaned up a bit. Replaced
	erase_vector_element by std::vector<>::erase.
	(abs_per_tgReduce): Adapted to ARRAY change. No more use of erase
	function. Cleaned up.  
	(linesWriteAscii): This is the new name of linesWriteToFile. 
	Changed default name extension to `.aa' instead of `.al'.
	(lines_per_tgWriteAscii): This is the new name of lines_per_tgWriteToFile. 
	Changed default name extension to `.aa' instead of `.al'.
	(xsec_per_tgAddLines): Completed the work started
	by Thomas. Two checks are now performed:
	1. a. Is the species oxygen?
	   b. Are there aux parameters?
	   c. Is the apropriate Rosenkranz lineshape used?
	2. a. Is the Rosenkranz lineshape used?
	   b. Is the species oxygen?
           c. Are there aux parameters?

	The absorption part is getting more and more messy. But at least,
	now it should be a bit safer than before.

2001-06-22  Thomas Kuhn  <tkuhn@uni-bremen.de>

	* arts-0-0-180

	* src/m_abs.cc (xsec_per_tgAddLines): Introduction of a control
	structure for the auxiliary lineshape function parameters.  This
	structure is only very preliminary and contains up to now only a
	print statement and no real control - this has to be implemented!

2001-06-22  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-179

	* Spectra are now also obtained when standing on the ground and
	looking downwards which not was the case before. So now spectra
	shall be obtained for all observation cases.

	* When observing from a point inside the atmosphere and the distance
	between the sensor and the tangent point, or the ground, is less
	than l_step/10, the part of the LOS from the sensor and the tangent
	point, or the ground, is neglected. For these cases, l_step is set to 
	the value given in the control file, i.e. no adjustment is done as when
	the distance discussed is > l_step/10.

	* Fixed a bug when calculating the angle of the beam after a
	ground reflection, when considering refraction. The angle was
	calculated as asin(c/(Re+z_ground)*n(z_ground)) while the
	correct expression is asin(c/(Re+z_ground)/n(z_ground))

	* Updated the full.arts control file in examples.

2001-06-22  Thomas Kuhn  <tkuhn@uni-bremen.de>

	* arts-0-0-178

	* changes/corrections in the continuum abs calculation.
	
2001-06-21  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-177

	* src/make_wsv_h.cc (main): Fixed bug that prevented the correct
	generation of Doxygen headers for WSVs from online documentation.

	* src/make_md_h.cc (main): Do no longer generate Doxygen headers
	from the online documentation of workspace methods. Doxygen
	headers have to be created manually!

	Also removed doxygen header for the array getaways in md.cc, which
	holds the pointers to the getaway functions, because this lead to
	a Doxygen error message.
	
2001-06-20  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-176

	* .cvsignore: Added arts.spec.

	* src/absorption.h: Made the intensity to mean intensity per
	molecule, i.e., not containing the isotopic ratio. This could
	create errors when older ARTS catalogues are used, because there
	the intensity included the isotope ratio, similar to HITRAN. To
	avoid this error, I've introduced a format tag, which should
	now be first in every ARTS catalogue file. It looks like this:
	ARTSCAT-2. There is a member function Version() to line_data that
	returns this version string.

	See doxygen documentation for LineRecord for a (hopefully precise
	enough) description of the format.

	* doc/examples/example1.arts: This file didn't run anymore. Kicked
	out the continua to make it run. There is a bug in the continuum
	tags. For some reason, none of the continua is accepted, although
	the tag specified is among the valid tags suggested by the error
	message. 

	* src/absorption.cc
	(write_lines_to_stream): Added output of version tag. Also output
	number of lines.
	(LineRecord::ReadFromHitranStream): Divide by isotopic ratio when
	reading HITRAN intensity.
	(LineRecord::ReadFromJplStream): Leave intensities as they are, do
	not any longer multiply with isotopic ratio
	(LineRecord::ReadFromMytran2Stream): Leave intensities as they
	are, do not any longer multiply with isotopic ratio
	(xsec_species): Apply isotopic ratio. This is done in the final
	loop, where xsec is summed up for all lines.
	(xsec_species): Also removed a try catch block around the
	partition function ratio calculation. This means that now the
	program will stop with an error message if partition functions can
	not be calculated. Before, it just gave a warning.

	* src/m_abs.cc (lines_per_tgWriteToFile): Do not any longer write
	the number of lines in each tag (since this is now added
	automatically after the format tag).
	(linesReadFromArts): Added check for correct version tag.

2001-06-13  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-175

	* Made a function to flip vectors (VectorFlip).
	
2001-06-05  Thomas Kuhn  <tkuhn@uni-bremen.de>

	* arts-0-0-174

	* change in methods.cc to allow profile read in from files
	directly (see function raw_vmrs_1dReadFromFiles)
	new tags defined for cloud liquid water (liquidcloud) and
	cloud ice particles (icecloud). For these tags also profiles can
	be read in now.
	
2001-05-30  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-173

	* data/atmosphere/fascod/midlatidude-summer.HO2.am: Added this
	file by hand from the 45n file in the RAL scenario used for the
	ESTEC studies (/pool/esa/maso/in/atm_scen). 

2001-05-30  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-172

	* continua.cc: Removed `^' character.

	* species_data.cc: Added isotope 172 (HITRAN 2000 tag 16)

	* species_data.cc: Gave HITRAN tag 15 to isotope 182, which was
	already in ARTS, but previously not in HITRAN. Changed isotopic
	ratio of this one to the HITRAN value, which is 6.23e-7, instead
	of the previous value of 6.11e-7.

	* partition_function_data.cc: Added isotope 172 (HITRAN 2000 tag 16)
        The Q coefficients for this are just copied from the main isotope!!

2001-05-25  Thomas Kuhn  <tkuhn@uni-bremen.de>

	* arts-0-0-171

	* Fixed wrong parameters in continua.cc

2001-05-16  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-170

	* When running Carmen's SMILES example we got NaNs in Kx. The reason
	to this was that the optical thicknesses when looking down to the 
	ground were very high which results in division with zero.
	I have not changed the equations, instead absloswfs is checked for
	NaNs and Inf and those values are set to zero. This should be perfectly
	alright as those values shall be very, very small anyhow.

2001-05-16  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-169

	* Fixed a size check in yCalc that gave wrong error message when a LOS
	is outside the atmosphere.

	* Off-sets in the batch part are now stored as a vector of off-sets. 
	Before the full new grid (e.g. za_pencil) with the off-set applied was
	stored.
	
2001-05-15  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-168

	* Fixed bugs in groundSet, groundAtBottom, and rand_gaussian.

	* Some crap code had got into qtool.
	
2001-05-14  Stefan Buehler  <sbuehler@uni-bremen.de>

        * arts-0-0-167

	* m_abs.cc: Switched interpolation in AtmFromRaw1d from linear
	interpolation to log pressure interpolation using interpp. Because
	adaptors and submatrices are not accepted by interpp, some
	temporary copies have to be made. This is horrible, we need a
	better matrix/vector implementation!

	* The reason for the change was that nadir weighting functions
	showed some strange wiggles. The change did reduce the wiggles
	considerably, but they are still visible.

2001-05-10  Stefan Buehler  <sbuehler@uni-bremen.de>

        * arts-0-0-166

	* configure.in: Added -O0 to CXXFLAGS. For some weird reason,
	configure on Kenny insisted on calling the C++ compiler with -O6,
	which lead to memory exhaustion. On the Smiles maschines this
	problem did not occur...
	
2001-05-02  Stefan Buehler  <sbuehler@uni-bremen.de>

        * arts-0-0-165

	* data/atmosphere/tstrad: Added this directory. It contains a test
	case for comparison with RTTOV-6.
	
2001-05-02  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-164

	* m_los.cc: Added method MatrixTRJ which calls yTRJ for all rows
	of a weighting function matrix. This is exactly the same
	as the specific method ybatchTRJ. Therefore I have removed this
	specific method. Replace in control files by
	MatrixTRJ(ybatch,ybatch){}. Similar, I added MatrixTB.

	* m_batch.cc: Removed ybatchTRJ and ybatchTB.

2001-04-30  Thomas Kuhn  <tkuhn@uni-bremen.de>

	* arts-0-0-163

	* add additional O2 absorption model of Rosenkranz in
	  continua.cc and continua.h

2001-04-27  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-162

	* methods.cc, md.h,M_wfs.cc: added a worspace method called
	linAltsFromPres to calculate a set of pressures 
	corresponding to a set of altitudes equally spaced. A
	possible application is to define a k_grid with equally
	spaced altitudes.

	* constants.cc: the Earth's gravitational constant
	(mu=3.98601E14 m3/s2) added to allow calculation of
	orbital parameters, named as EARTH_GRAV_CONST.
	
	* methods.cc, md.h, m_loc.cc: zaFromDeltat updated
	with EARTH_GRAV_CONST

2001-04-27  Thomas Kuhn  <tkuhn@uni-bremen.de>

	* arts-0-0-161

	* add additional H2O absorption models: 
	MPM85/87, MPM89, MPM93, Cruz-Pol98, and Rosenkranz98
	added. Preliminary stored in continua.cc, but this will be
	changed in future.

2001-04-25  Oliver Lemke  <oliver@uni-bremen.de>

	* arts-0-0-160

	* configure.in, arts.spec.in: Added a spec file for rpm creation.
	This would make the installation process for the release version
	much easier and guarantees a clean deinstallation of arts.

	I will added some more information about building arts rpms.

2001-04-24  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-159

        * New function to set the emission flah: emissionOn and emissinOff.

        * Some new functions to set the ground variables (groundSet,
        groundOff and groundAtBottom).

        * The hydrostatic equilibrium is revised. Check out the functions
        hseSet, hseOff, hseFromBottom and hseCalc).

        * Temperature WFs with hydrostatic eq. now implemented. Two versions
        exist, kTemp and kTempFast. Use the fast one!

2001-04-20  Thomas Kuhn  <tkuhn@uni-bremen.de>

	* arts-0-0-158
	
	* add cloud/fog and ice absorption continua 

2001-04-18  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-157

	* ami/arts/.cvsignore: Added wsv.txt.

	* h_matrix.cc: Fixed bug in VectorApplyH and MatrixApplyH
	(dimension of output variable was not set). Also added safety
	check of output variable dimension to h_apply functions. Probably,
	there should be similar checks in h_diff, but I did not touch
	this.  

2001-04-11  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-156

	* Fixed a bug in qtool. The line feed was included when calling
	inline functions.
	
2001-04-11  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-155

	* methods.cc, md.h, m_loc.cc: added a workspace method called
	zaFromDeltat to calculate the zenith angles for a LEO-LEO cross
	-link geometry corresponding to a given increment in time in 
	the motion of the LEOs. The LEOs are supposed to be moving in
	opposite directions in nearly identical orbits (but not \n"
        "colliding!).

2001-04-09  Thomas Kuhn  <tkuhn@uni-bremen.de>

	* arts-0-0-154
	
	* add continua 
	* add some IDL functions and update of plot_abs_per_tg.pro 

2001-04-04  Carmen Verdes  <cverdes@uni-bremen.de>

	* arts-0-0-153
	
	* Initialize output to zero! This is important, because otherwise
          the output variable could `remember' old values.

2001-04-04  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-152

	* NaNs were obtained when using float and a conversion to brightness
	temperatures was performed. Some scalars have been hardcoded to be
	double to avoid this problem.

	* A similar problem was found in the vector version of planck.

	* A warning, when using very large or small values, as the Planck and
	Boltzman constants, I would recomment to hard-code double to avoid 
	these disturbing problems.
	
2001-04-04  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-151
	
	* Deleted wsv.txt in ami/arts from CVS. This function is auto-generated
	when compliling ARTS and is copied to ami when running the init script.
	Axel had some problems with this function and I hope it is best to keep
	it outside CVS (and I must added it to CVS by mistake).

	* (Sorry, for the problem with yCalc. I will check "my" functions for
	this kind of problems when the optional input variables are ready and
	we know the consequencies of this. I put this in TODO.)

2001-04-03  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-150

	* plot_abs_per_tg.pro updated

	* partition_function.pro updated

	* TODO list updated

2001-04-03  Stefan Buehler  <sbuehler@uni-bremen.de>  

	* arts-0-0-149

	* m_los.cc: Added safety check to yCalc to make sure that the
	number of frequencies in trans and f_mono is the same. This,
	because it took some time to track down a core dump resulting from
	reading absorption from a file with the wrong number of
	frequencies. There should probably be more consistency checks in
	this method.

2001-04-03  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-148

	* Fixed some bugs for downward looking observations. The first problem
	was associated with the indexing of the ground where there still were
	problems from the change from 1-based to 0-based indexing. Further,
	some vectors where not given any length before copying data.

	* Made the variables a and b in the planck functions static again
	and introduced the variable c for the vector version.
	For the matrix version there were no problem before (or?). The bug
	was in the vector version where the temperature was included in the
	static variable b which of course is a stupid thing. 
	The static variables a and b should now only contains constants.
	
2001-04-03  Stefan Buehler  <sbuehler@uni-bremen.de>  

	* arts-0-0-147

	* atm_funcs.cc: Fixed bug in vector and matrix version of function
	`planck': Variables a and b must not be declared as static,
        otherwise they are only computed for the first function
	call. Because of this, we got identical results for subsequent
	calls of the function with different temperature.
	
2001-04-02  Stefan Buehler  <sbuehler@uni-bremen.de>  

	* arts-0-0-146

	* los.h: Cosmetic changes in doxygen header of struct LOS:
	  - Used html tags in the enumerated list because LaTeX constructs
  	    do not work.
          - Replaced index of stop by 0 at one place.

	* There seems to be a problem in the setup of los for uplooking cases.
	 	
2001-04-02  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-145

	* The power of ARTS! I love ARTS, it is so good. It is now possible 
	to make retrieval species for pure absorption measurements.
	I don't want to lessen my fine effort ;-), but this was rather easy to
	implement due to the excellent structure of ARTS.

	* There is now a WSV called emission that you must set. For "normal"
	simulation it should be set to 1, while 0 means that emission shall be
	neglected. For the latter case (pure absorption calculations) the 
	output unit is changed from transmission to optical thickness. This as
	optical thicknesses are normally used during the inversion.

	* The WSFs yRte and YBl are removed. The general function to get 
	spectra is yCalc. This function uses the WSV emission to determine what
	kind of spectrum to return. For pure absorption calculations there 
	exist a special function called yTau. However, note that there is no
	direct overhead involved bu using yCalc as sourceCalc just returns
	a empty array if emission=0.

	* The function absloswfsCalc takes now also emission as input. There
	is also a function called absloswfsTau to match yTau. Then you use
	the kSpecies functions as usual. Great or?

	* The WSF losCalc now also returns z_tan.

	* A warning, I haven't got time for any larger bug controls for these
	changes, so take care.

2001-03-30  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-144

	* m_loss.cc: Fixing a small bug

2001-03-28  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-143

	* methods.cc, md.h, m_loc.cc: added a workspace method called
	zaFromZtan to calculate the zenith angles from a given set of
	tangent altitudes in z_tan

	* atm_funcs.cc, atm_func.h, m_loc.cc : functions n_for_z and
	refr_constant moved from m_loc.cc to atm_func.cc

	* atm_funcs.cc: ztan_refrac modified to do calculations using
	n_for_z.

2001-03-28  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-142

	* First a comment to z_tan just be totally clear. The los
	function will still only take zenith angles as argument, but
	there will be a function to convert a set of tangent altitudes
	to corresponding zenith angles. The z_tan vector will be an 
	output of losCalc.

	* Made some smaller changes to the definition on the ARTS line
	format found in absorption.h. Read it give comments.
	Stefan, can really ARTS read line files (in the ARTS formats)
	with line breaks inside the definition of a transition? I tried
	this and it didn't work.

	* New WSF NumericCopyFirstOfVector. I plan to use this to set 
	the ground temperature to the first value of t_abs.

	* New function in AMI (in file/) to create ARTS line file from
	data in Matlab. Will be used to convert Verdandi to the ARTS
	line catalog.

2001-03-27  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-141

	* workspace.cc: added a new workspace variable z_tan so a set
	of tangent altitudes can be specified as input for a given 
	LOS geometry. Now both z_tan and za_pencil can be used to 
	define the geometry. Requires changes in LOS functions, 
	to follow.

2001-03-16  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-140

	* Added Makefile and Makefile.in files in the ami tree to the
	.cvsignore files. (I had forgotten to do this for version 139.) 
	
2001-03-13  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-139

	* configure.in: Added missing Makefiles:
      	ami/arts/Makefile
      	ami/file/Makefile
      	ami/math/Makefile
      	ami/path/Makefile
      	ami/physics/Makefile
      	ami/plot/Makefile
      	ami/retrieval/Makefile

	This is necessary for the reconf script to work.
	
2001-03-13  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-138

	* Implemented the new continuum concept, as decided in the meeting
	last Friday. I made only a slight change compared to what was
	discussed in the meeting, by using two independend WSVs for the
	coninuum description. These are:
	- cont_description_names
	- cont_description_parameters

	I did it this way, because I have in mind a quite simple mechanism
	for combining WSVs to `conglomerate WSVs', which could then be
	used to bind the two together. However, when I will find the time
	to implement this is an open question. For now, working with the
	two individual variables should be fine. 

	* workspace.cc: Added WSVs cont_description_names and
	cont_description_parameters.  

	* methods.cc: Added WSMs cont_descriptionInit and
	cont_descriptionAppend. Also WSMs xsec_per_tgInit and
	xsec_per_tgAddConts. 

	* m_abs.cc: Added WSMs cont_descriptionInit and
	cont_descriptionAppend. 

	Renamed xsec_per_tgCalc to xsec_per_tgAddLines and adapted.

	Introduced xsec_per_tgAddConts.

	Introduced xsec_per_tgInit.

	Adapted absCalc.

	* continua.cc: Added the function `check_continuum_model', which
	checks if a string matches a continuum model. Continuum model
	names must look like this: `H2O-ContRosenkranzSelf'. At the
	beginning must be the species name.

	* absorption.cc: Added the function get_tag_group_name which
	returns a tag group name from an ARRAY of OneTag. This is just
	handy for informational output messages.

	* doc/examples/cont.arts: This is an example file for calculating
	continua. 
	
2001-03-13  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-137

	* The function to create control files from templates is now
	called qtool and is found in ami/arts. There is now some better
	instructions and an example on how this tool can be used.

2001-03-13  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-136

	* I have added a number of handy Matlab scripts to AMI. All functions
	are of rather general character and can be of use in many cases. The
	functions are sorted into a number of sub-folders.
	
2001-03-07  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-135
	
	* math_funcs.cc: incluiding the Choleski decomposition in rand_data_
        gaussian so a Choleski decomposition s=l'*l is done and l is used to 
        generate the random data.

	* methods.cc, m_covmatrix.cc: new worskpace method BatchdataGaussian
        NoiseNoCorrelation to generate noise without inter-channel correlation. 

	* m_batch.cc: BatchdataGaussianSpeciesProfiles updated for tgs

2001-03-07  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-134

	* Fixed a small bug in the H-matrix part of AMI.
	
2001-03-01  Wolfram Haas  <wolhaas@hermes.fho-emden.de>

	* arts-0-0-133

	* read_datafile.pro: Keyword changed ('check' instead of
	                                      'optimize').
	* read_artsvar.pro: Keyword changed ('check' instead of
	                                     'optimize').
	* write_datafile.pro: Unnecessary 'print'-command removed.

	* utilities.tex: Upgrading of the description.
	
2001-02-26  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-132

	* /ami/read_datafile.m: matlab read and write functions modified to
	include SYMMETRIC type

	* m_batch.cc, m_covmatrix.cc: functions with covariance matrices
	updated so covariance matrices are now SYMMETRIC

2001-02-26  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-131

	* The text for continuum absorption changed.

2001-02-23  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-130

	* A new try to commit my latest changes.

2001-02-22  Axel von Engeln  <engeln@uni-bremen.de>

	* version-0-0-129

	* two new species implemented, which are new in Hitran 2000, 
	additionally put some more species into the partition function
	calculation, and the abundance calculation. These additional
	species are not implemented in arts yet.

	* math_funcs.h: output error corrected

	* aii_klegend_d.pro: klegend_d file, needed in plot_abs_per_tg.pro

2001-02-22  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-128

	* There were some problems around the last commit, so this another
	one just in case.
	
2001-02-21  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-127

	* The story about LOS seems to never end. Before last commit I only did
	changes with 1 zenith angle. When I now used refraction for a full
	scale simulation I noted that the LOS calculation was very slow. The
	problem turned out to be the interpolation. The interpolation is now
	done locally in the function where the interpolation index is stored
	from one interpolation to next and this saves a lot of time. I also
	did some other changes to improve the speed but with much less impact
	on the final computational time.
	The function is now about 50 times faster then before
	
2001-02-19  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-126

	* Yet another bigger revision of the LOS part. 
	The core calculations are now performed by a single function for
	all observation geometries (one function for refrcation and one
	function for geometrical calculations). This should ensure a high
	consistency for the calculations. Some preparation for the 2D
	calculations have been performed.

	* Refraction is now handled by a more traditional ray tracing scheme,
	using the geometrical term as starting point. The refractive index
	is assumed to be constant over each ray tracing step. See further
	AUG. As I wanted an integer ray tracing step for each LOS step,
	the wsv l_step_refr is exchanged with refr_lfac (an integer). This
	factor gives how many ray tracing steps that shall be performed for
	each LOS step (the ray tracing step length is accordingly
	l_step/refr_lfac). The calculations with refraction are now a bit 
	slower and too small steps should be avoided. The ray tracing works 
	both with float and double.

	* I have tested the ray tracing scheme and the results were good.
	First of all, if n is set to 1 at all altitudes, the geometrical LOS
	is obtained exactly (the deviations are around 1e-6 m). A suitable 
	value for the ray tracing step length seem to be about 5 km. 

	* The LOS structure is extended and holds now also the geometrical
	altitudes of the LOS points not only the pressures). These altitudes
	should not be used inside ARTS but are intended for plotting and bug
	checking.

	* The angles between the vectors going from the Earth's center and
	the sensor and the LOS points are now also calculated. These angles
	are called psi in lack of a better name (any suggestion?).
	The psi angles were included as a preperation for 2D. If horisontal
	structures are neglected for the LOS calculations (the effects should
	be negliable according to RAL and Rodgers), it is now a simple thing
	to get the whole LOS for 2D (as soon we define what coordinate system
	to use).

	* Axel, I got your thesis in my hand more or less in the same minute
	as I finished my ray tracing scheme. I saw that you have written quite
	a lot about refraction. You should have done this work!
	
2001-02-16  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-125

	* version.h, version.cc: Added resize function for SPARSE and
	SYMMETRIC. Note that resize really replaces the object by a new
	one of the right size. Maybe the name should be changed to
	`replace' one day. Furthermore, note that for SYMMETRIC
	resize(a,i,j) generates a new SYMMETRIC matrix by calling
	SYMMETRIC(i,j), which should generate a ixi symmetric matrix with
	j offdiagonal bands.
	
2001-02-15  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-124

	* lines_per_tgCompact workspace method included, it just cycles
	through all lines per tag groop and looks whether they are in or
	outside the defined cutoff frequency of the lineshape. All lines
	outside are removed. This should save some computational time, but
	something similar is done in the absorption calculation when a
	cutoff frequency is present.

	* lineshape cutoff seems to work
	
2001-02-14  Carlos Jimenez  <jimenez@rss.chalmers.se>

	* arts-0-0-123

	* maths_func.h, maths_func.cc: Added the function *chol* to do a
	Choleski factorization

	* demonstrate_vecmat.cc: Included a test case running *chol* 

2001-02-13  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-122

	* vecmat.h, vecmat.cc: Added matrix type SYMMETRIC. This should be
	both banded and symmetric. (Having just symmetric is a special
	case of this.) 

	SYMMETRIC A(5);   // generates 5x5 symmetric matrix
	SYMMETRIC A(5,1); // generates 5x5 banded symmetric matrix like this:
	                  // xx000
	                  // xxx00
	                  // 0xxx0
	                  // 00xxx
	                  // 000xx

	However, the latter case seems not to work and I don't understand
	why. Best would be to write email about this to the MTL people.

	* demonstrate_vecmat.cc: Included test cases for the SYMMETRIC type.

2001-02-13  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-121

	* Simplified the WF information somewhat. Now the length of each
	identity is stored instead of start and stop index. This to avoid
	storing INDEX in a matrix. Column 3 of the aux variables removed.

	* The species WF functions now use wfs_tgs.

	* Changed names on the workspace variables tgs and wfs_tgs to match
	the names used in function names.
	
2001-02-12  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-120

	* Hard-coded double in some places in m_los.cc where the earth
	radius (maybe + something) is squared to improve the precision.

	* With double and setting n=1, the same result is obtained with and 
	without refraction (which should indicate that everything is OK).
        The option float/refraction is still not working (see more below).

	* Fixed a bug in planck when using float. This expression:
	a = 2.0*PLANCK_CONST/(SPEED_OF_LIGHT*SPEED_OF_LIGHT);
	becomes 0 if a is set to be float. Now hardcoded to be double.

	* I will not bother you about the details, but I recommend you
	to NOT use refraction before we have validated my new scheme. Carlos
	will implement some other scheme so we get an oppertunity to check
	the results.

	* ARTS seems to run now when using float (if not refraction is switched
	on). So let's use float for some time to look for other bugs
	connected with using float. OK?
	
2001-02-08  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-119

	* lineshapeDefine help extended

	* lineshape_per_tgDefine help extended

2001-02-07  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-118

	* lineshapeDefine additional keyword cutoff added, which defines
	the cutoff frequency [Hz], -1 no cutoff

	* lineshape_per_tgDefine additional keyword cutoff added, which
	defines the cutoff frequency [Hz], -1 no cutoff

	* lineshape is a workspace variable now that contains the index
	to the lineshape, normalization function, and cutoff.

	* Validation has only been performed with the no cutoff option.

2001-02-07  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-117

	* abs_per_tgReduce workspace method and little bug removed.

2001-02-02  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-116

	* tag_groupsDefine workspace method has now been changed to
	tgsDefine

	* wfs_tgsDefine workspace method introduced, this gives the
	tag groups out of tgsDefine, for which weighting function shall
	be calculated

	* abs_per_tgReduce workspace method introduced, this reduces the
	abs_per_tg variable to the size of the tag groups given in
	wfs_tgsDefine. The order in wfs_tgsDefine does not has to be kept.

2001-01-30  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-115

	* aii_prologue_l.pro: Arts IDL Interface plot prologue, landscape
	
	* aii_epilogue.pro: Arts IDL Interface plot epilogue, landscape

	* plot_abs_per_tg.pro: makes a nice color plot of the absorption
	per tag group

	* read_datafile.pro: indicees changed from 1 to 0

	* read_tag_groups.pro: reads the tag group names out of a
	controlfile, is for example used by plot_abs_per_tg

	* sort_abs.pro: sorts the absorption per tag group according to
	magnitude at a certain altitude level, is used by plot_abs_per_tg

	* arts/o2_spin_rot_pwr_3.al: arts catalogue file of the oxygen
	spin rot spectrum, see file for more info

	* methods.cc: updated some info.

2001-01-26  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-114

	* vecmat.h: Fixed bug in transf() function. The type of the
	mathematical function is now double (&my_func)(double). Numeric
	does not work here, since mathematical functions for float do not
	exist.

2001-01-26  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-113

	* Changes in reading and writing of binary files. There were some 
	really bad bugs that now should be fixed. The reading and writing
	of matrices shall now be somewhat faster.
	
2001-01-24  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-112

	* vecmat.h: Changed ARRAY implementation back to MTL.

	* make_md_h.cc: Adapted to ARRAY implementation change.
	
2001-01-23  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-111

	* Removed special functions for no ground and no refraction. It became
	messy to make several versions at so many places. Instead I have made
	two small functions called NoGround and NoRefraction to set dummy 
	values for the ground and refraction variables (however the ground 
	altitude must be specified). This solution makes the functions assuming
	a special calculation order, that is functions calling workspace 
	methods as absCalc and losCalc, more general.

	* Added functions to calculate WFs for pointing off-set and a 
	proportional calibration error. It is now also possible to calculate
	WFs for continuum absorption fit for portions of the total frequency
	range. This can be used to make seperate fits in primary and image
	frequency band.
	
2001-01-19  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-110

	* m_abs.cc: Added method lines_per_tgReadFromCatalogues. This
	reads lines from catalogues and assigns them to lines_per_tg in
	one go. Different catalogues can be specified for different
	tags. This will be handy for the water vapor absorption
	spectrum. Now we can use a special line file for water vapor,
	with continuum parameters to match.

	* token.h, parser.cc: Renamed the type ARRAY_Numeric_t to
	VECTOR_t. Also changed the definition accordingly, so this type is
	now a vector.

	* doc/examples/example1.arts: Adapted to demonstrate the new
	catalogue reading features.

2001-01-19  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-109

	* Made the function h2o_absSet.

	* Fixed a bug in rte. The step just above the tangent point was just
	looped once, instead of two as is correct. A bug from the MTL switch.

	*So finally, I managed to get consistency between the spectra and
	the internal calculation to get absloswfs. This does not guarentee
	that the WFs are OK, but so far everything seems correct.
	
2001-01-18  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-108

	* m_abs.cc: Fixed bug in the continuum switch in
	xsec_per_tgCalc(). Also renamed xsec_per_tgCalc() from previous
	name xsec_per_tgCal().
	
2001-01-18  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-107

	* Added the function refr_indexBoudouris, i.e. this function takes into
	account water and not only dry air.

	* Added the functions VectorAdd, VectorScaled and MatrixScaled that can
	be used for simpler tests. VectorAdd can be used to add 2 K to t_abs
	at all altitudes to test the influence of the temperature for some
	measurement (used e.g. for the WATS proposal).

	* I have gone through the los, rte and bl functions for all geometries
	with and without refraction. There was some bugs, both old ones and 
	from the MTL switch. At least there are now no errors (in my test 
	cases) and the results are reasonable.

	* I have started to check the species WFs. The WFs for upward 
	observations seem to be OK now. One smaller bug found for limb WFs, but
	I have not yet made a final test. I will continue this work.

	* An interesting thing. For the WATS proposal I created a line file
	with the strongest H2O lines up to 560 GHz. I also added these lines
	with a negative centre frequency, and it worked. So the solution
	for van Vleck-Weiskopf should be OK.
	
2001-01-17  Wolfram Haas  <wolhaas@hermes.fho-emden.de>

	* arts-0-0-106

	* Added the IDL interface functions.

	* read_artsvar.pro: Reads an ARTS variable (uses read_datafile). 

	* read_datafile.pro: The real implementation of the reading
	routine. 

	* write_artsvar.pro: Writes an ARTS variable to a file in ARTS
	format (uses write_datafile).

	* write_datafile.pro: The real implementation of the writing
	routine. 
	
2001-01-17  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-105

	* Put in continuum stubs. Also did the implementation for a self
	continuum, although the coefficients (C and x) are at the moment
	just dummy numbers. Thomas should put in the correct ones that
	result from his fits to lab data. Also, the function for the
	foreign continua needs to be added, which should be simple
	following my self continuum example. Interesting places for this
	work are marked with `FIXME' and/or `Thomas' in comments.

	The continuum at the moment is bullshit, without the correct
	coefficients and the foreign part. Probably many orders of
	magnitude wrong.

	* continua.h: Header file for continua.cc.

	* continua.cc: Implementation of continuum functions.
	
2001-01-15  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-104

	* tag groups: we went back to the definition of tag and tag
	groups. Therefore some WSM are called differently, e.g.,
	lineshape_per_tgDefine instead of lineshape_per_tagDefine
	Sorry, but you have to change your controlfiles again :-(
	Hope we stay with this definition now.

	* Oxygen: absorption is now always calculated with the
	normalization factor given in the controlfile. this was formerly
	treated differently to find agreement with the old iup forward
	model.

	* Cross Sections: now implemented differently, so that absCalc
	just calls the cross section WSMs xsec_per_tgCal and
	absCalcFromXsec. 
	
2001-01-15  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-103

	* Spectra have been wrong for some time. I discovered yeasterday (after
	a lot of investigating) that the spectra just grow for each zenith
	angle. This was a problem after the switch to MTL, due to the shallow
	copying with the =-operator. Spectra are now again reasonable for limb
	sounding. I habe not done any tests for other geometries.

	* The species WFs are incorrect. I will look for that bug.

	* Cleaned up the integration routine mess. Now the two template
	functions of SB are used together with an old function returning
	only a scalar.

	* Removed some other old code in math_funcs.

	* Fixed bug in AMI when reading and writing binary files caused by
	the switch from 1 to 0 based indexing. This bug only affected arrays.

2001-01-11  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-102

	* xsec_per_tagCal WSM implememted, calculates the cross section
	per defined absorption tag

	* absCalcFromXsec WSM implemented, calculates the absorption and
	the absorption per tag from the cross sections calculated by
	xsec_per_tagCal.

	* Agreement with the 2. Bredbeck book arts description should now be
	archieved in principle. Still we have to rename the tg to tag, and
	somebody should put all the stuff into the AUG.

2001-01-10  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-101

	* had to check in again my changes, because I just updated to
	Stefans MTL version arts-0-0-99. This does not work, because
	directories are not removed (e.g., I checked in tnt again). I
	don't know what else could go wrong, so I checked out Stefans
	version and redid my version 100.

2001-01-08  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-100

	* yes, I did the 100 version. I am proud.

	* and I did some work on the partition functions, included now the
	vibrational levels. more info will be available in the arts
	proceedings (hope I make it in time).

	* updated lineshape infos

2001-01-08  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-99

	* This is a working commit. Everything needs still a lot of
	tidying up. Sorry for this. However, I have made massive changes,
	and I don't want to get completely out of sync with the rest of
	ARTS development. Merging was tough enough as it was.

	* vecmat.h: Contains now the complete matrix/vector declaration
	(linalg.h has vanished). 

	* vecmat.cc: Contains now the complete matrix/vector implementation
	(linalg.cc has vanished). 
	
	* vecmat.h: Changed implementation of ARRAY from MTL
	to STL. This also required some small changes all over the place. 

        * vecmat.h: Changed implementation of VECTOR and MATRIX to
	MTL. This required massive changes all over ARTS.

	* math_func.cc: Changed from 1-based to 0-based. Shitty work, I
	hope I have not introduced too many bugs. Patrick, could you
	please look at the places marked by FIXME?

	Important change: Non-return versions of math functions no longer
	resize their output vector. This makes them more useful, because
	now you can apply them directly on rows or columns of a matrix
	without any copying. The same is true for output
	matrices. Instead, the return version sets the size before calling
	the non-return version. So, if you want to create and resize at
	the same time, simply use the return version. Anyway, because of
	the shallow MTL copies, return versions should be as efficient as
	non-return versions.

	This also has the consequence that non-return versions no longer
	need arguments specifying the size of things to generate, instead
	the size is taken from the given output vector/matrix.

	* rand_gaussian: Is this algorithm correct? - See FIXME.
		
        * rand_uniform: There is a problem with setting the random seed
	here. It has the opposite of the desired effect. See FIXME comment
	inside the function! I commented the line out for now.

	* Philosophical remark: There is a conflict between 2 important
	C++ paradigms, function overloading and templates. The first says
	that it would be nice to always give the same name to similar
	functions, even if they act on different data types (for example
	interp_lin for vectors and matrices). The second says that it
	would be nice to formulate algorithms such that they work for
	several (similar) data types (for example the copy() algorithm
	from MTL). As it turns out, having both is very difficult. For
	example, there are the algorithms print_vector() and
	print_all_matrix() which do the same thing, once for vectors and
	once for matrices. Both are template functions. If we give them
	the same name (for example simply `print') the compiler can no
	longer distinguish between the two functions and we get an
	error. I can see no elegant solution to this problem. 

	* Math functions: I think there are now too many math functions
	(for example interpolation routines). This should be generalized
	more. For example one linear interpolation routine for vectors and
	one for matrices is probably sufficient. Also, is it really
	necessary to have also return versions for all functions?

	* m_wfs.cc, k_temp_nohydro: I don't understand why 1 K is added at
	all levels. This does not give the derivative, does it? Wouldn't
	one have to do this separately for each level? (See FIXME in the
	code.) 

	* Transf(): Arithmetic functions like sqrt() and also the new
	log10() for vectors and matrices are no longer necessary, since
	the transf() algorithm can apply any mathematical function to a
	vector or matrix. Transf() exists as parameter and return version,
	hence has exactly the same functionality as the old functions.

	* demonstrate_vecmat.cc: A sample program demonstrating matrix,
	vector, and mathematical features. Is compiled automatically if
	you do a `make'. Run as `demonstrate_vecmat'. 

	* example1.arts: Runs and gives same result as before
	(with arts-0-0-98). 

	* full.arts: I get an error in method ybatchAbsAndRte that I don't
	understand. This also with the old version of ARTS. Patrick, could
	you look into this?

	I quickly compared the Kx matrix with arts-0-0-98. Unfortunately,
	the result is not identical (now about 50% smaller than before). I
	have no idea what's going wrong. Sorry for committing it like this,
	but since you developed this part, maybe you have better ways of
	verifying individual calculation steps.

	* A common bug: Assigning a scalar to a vector as in:
	VECTOR a;
	a = 1;
	At runtime this will lead to a segmentation fault later on in the
	program. Unfortunately this bug is hard to locate. There could be
	still a few instances of it creeping through ARTS.

	* src/docu.txt: See this file for more common bugs. If you have
	problems, look here first. Anyway, I recommend reading this file
	to everybody (it's quite short). The stuff will eventually go into
	the Uguide, just I found it useful to have a simple ASCII file to
	enter things as I implemented and checked them. If things are
	unclear here, look also in the demonstrate_vecmat.cc file, there
	probably is an example there for the feature you need. 

2001-01-06  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-98

	* o2 spin rot absorption included. 2 lineshapes are available for
	this species:
	Rosenkranz_Voigt_Kuntz6
	Rosenkranz_Voigt_Drayson

	added a directory o2_spin_rot to the iup comparision one, where
	controlfiles, etc are located

	The o2 absorption is calculated as all other species, with 2 major
	differences:
	
	1. 2 overlap aux parameter are required in the spectroscopic
	database. I compiled a few catalogues in the arts format, they are
	located under spectroscopy/arts. 
	2. the o2 absorption requires a water vapor vmr. consequently
	abscalc requires now always a h2o vmr (I couldn't think of another
	way to implement this). this vmr is only needed for the rosenkranz
	lineshapes and can be set to any dummy value for other
	calculations. I followed the arts convention and called it
	h20_abs, which can be generated from the vmrs by:

	# define the h2o_abs vector, containing the total wv vmr
	VectorCopyFromArrayOfVector (h2o_abs, vmrs) {index=0}

	this has to be done after the call to AtmFromRaw1D{}.

	* Lorentz lineshape problem solved.

	* hope that's it. More in the mailing list.
                 
2001-01-03  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-97

	* Bugs in absloswfsCalc and sFromFile due to index change fixed.

	* A function to calaulate the base 10 logarithm exists 
	(VectorCalcLog10). This function is handy when setting up Sx when
	using pressure as altitude coordinate.
	
2001-01-02  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-96

	* Version 0-95 did not compile due to a missing ) in math_funcs.cc. 

	* An out-function added to AMI. 
	
2000-12-20  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-95

	* The seed is now reset for each call to a function that generates 
	random data (thanks Oliver).

	* Some functions added to AMI/general.
	
2000-12-19  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-94

	* optimization stuff.

2000-12-15  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-93

	* Voigt_Kuntz1 is now called Voigt_Kuntz6, done some speeding up
	in linesphape (with no great success)

2000-12-15  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-92

	* arts can now read its own catalogue files.

2000-12-15  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-91

	* Fixed some smaller bugs caused by the index change.

	* Updated full.arts in doc/examples. The control file runs OK, spectra 
	lokk OK (including the batch run) but WFs are not checked if correct.

	* Changed the text for the out-streams in calcAbs. Now all lines 
	listed for level 3 (but not pressures) and the main sizes for the 
	calculations are showed for level 2.
	
2000-12-13  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-90

	* m_abs.cc, tag_groupsDefine: Fixed bug: Initialization does not
	work correctly with MTL based ARRAY<ARRAY>. If you just create
	such a biest, all elements of the outer ARRAY will point to the
	same data. There is an easy fix though, now I simply initialize
	the outer ARRAY elements explicitly. This bug had caused the bug
	in get_tagindex_for_strings that Patrick has reported.

	* m_abs.cc, lines_per_tgCreateFromLines: Fixed same bug.

	* absorption.cc, LineRecord::ReadFromMytran2Stream: Fixed same
	bug. In LineRecord::ReadFromMytran2Stream I had already fixed it
	before. 

	* src/docu.txt: Added description of this bug and how to avoid it
	to the documentation.
	
2000-12-13  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-89

	* lineshapes include now: 3 Voigt Kuntz algorithms, Voigt Drayson,
	Doppler.

2000-12-13  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-88

	* Changed indexing from 1-based to 0-based in the following files:
	    m_wfs.cc
	    m_los.cc
	    m_hmatrix.cc
	    m_covmatrix.cc
	    m_batch.cc
	    atm_funcs.cc
	I did not change math_funcs.cc as there could be side effects. For 
	example, the function col causes problems.
	(This was heavy work, it took 5-6 hours despite I did it basically
	as quyickly as possible).
	Some changes were needed. The ground flags are now int's instead of 
	INDEX. No ground is now flagged as -1. When storing in file, the ground
	flags are increased with the value 1, so the falgs can be stored as
	INDEX (ints are not handled in binary files so far).
	The program compiles but I have not made any more detailed bug search.
	I wait with this until the switch to MTL is complete. The WFs have now
	probably a lot of bugs as those functions have a lot of indexing (and
	I that had tested that so carefully -:( ).

	* First version of batch and covariance parts ready. However, they
	cannot be completed before sprse matrices and Cholesky function are
	aviliable. I have done rather carefully function descriptions so have a
	look in methods.cc.
	
2000-Dec-12  Oliver Lemke  <oliver@uni-bremen.de>

	* arts-0-0-87

	* src/vecmat.h: Changed type of MATRIX from Fortran_Matrix to Matrix.

2000-12-09  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-86

	* All ARRAYs are based on MTL now. This was a tough bit because
	of the indexing problems. The absorption part seems to run the
	same as before. For the RT part I had no way to check. It is
	possible or even likely that I have introduced bugs. Please
	check. 

	* It's not so good changing other people's code. However, I see no
	other way for MATRIX/VECTOR than doing it in the same way: All at
	once for all files. It is not possible to do it gradually, since
	TNT and MTL matrices are incompatible.

	* The indexing scheme must be changed beforehand from x(1) to x[0]
	for VECTORs and from A(1,1) to A[0][0] for matrices. This is the
	only more or less safe way for the transition. Round brackets will
	work for MTL, but mean 0-based indices!

	* src/docu.txt: Documentation on MTL and ARRAY
	implementation. This should go in the Uguide eventually.

	* linalg.h: MTL interface. Probably eventually I will put
	everything back in vecmat.h again, so this file will vanish. At
	the moment vecmat.h includes linalg.h.

2000-12-08  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-85

	* In the middle of changing ARRAY implementation to MTL (including
	changing from 1-based to 0-based indexing)

	* Don't update to this version!
	
2000-12-07  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-84

	* Panic backup. (The power contact had slipped out and the computer 
	died. After restart, not all letters on the keyboard did not work and
	I managed to login just by being a smart. After 1-2 minutes the 
	keyboard was suddently OK again, but God knows what can happen)
	As I don't trust the computer, I want to backup my work.

	* I am working on generating random data and doing batch calculations.
	Please, have a look and give comments.

2000-12-04  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-83

	* r_geoid is now made to a workspace variable. Type r_geoidStd{}
        to set it to EARTH_RADIUS.

	* Functions now exist to generate random data with uniform and gaussian
	PDFs. No correlation. VectorRandNormal is an example on workspace
	method. The generation of random data can be checked by rand_test in
	AMI.

	* Made up a format to simply define covariance matrices and made 
	functions to create cov. matrices based on such definition data.
        See sSimple and sFromFile.
	
	* The function z_absHydrostatic gives a vertical grid fulfilling
	hydrostatic eq. The workspace variable h2o_abs must be set.
	
2000-12-01  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-82

	* lineshape selection in controlfile implemented

	* lineshape and lineshape_norm are 2 new workspace variables, they
	  contain the index of the selected lineshape and normalization
	  function of the lineshape_data and lineshape_norm_data records.

	* lineshapeDefine and lineshape_per_abs_tagDefine are 2 new
	  workspace methods, they allow the selection of the lineshape and
      	  the lineshape normalization in the controlfile. Currently
	  implemented: shape: Lorentz, Voigt_Kuntz1
	               norm:  no_norm (1), linear (f/f0), quadratic (f/f0)^2
	  Consequently, they both need tag_groups (tags) as input

2000-11-30  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-81

	* Test version

2000-11-23  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-80

	* Writing about calibration and conversion to brightness temperature
	in AUG.

2000-11-16  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-79

	* Some very small changes in AUG.

	* Allowed cubic treatment between abscissa points of spectra and 
	sensor characteristics when setting up the H matrix (image sideband 
	spectra still only linear treatment). Before all quantities were 
	assumed to be piecewise linear functions, but now piecewise cubic
 	functions can be assumed which could improve the accuracy in some
	cases (needs to be tested).

	* Please note that the sensor part is not yet validated and testet
 	in detail (however, the values look OK). When I am happy with the
	design of the sensor functions, I will do some comparisons with Skuld
	(but I trust ARTS more) and set up some examples for you.
	
2000-11-13  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-78

	* The writing and reading functions for binary files handle now
	empty data (both ARTS and AMI). (Does this work for ASCII files?)

	* The binary data files are now described in AUG.

	* Put in parts in AUG (just parts pages, no move of chapters was 
	needed). AUG is divided into 3 parts.

2000-11-10  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-77

	* Very small changes to documentation in several places.

	* Sample control file in AUG still needs to be adapted to new
	method and WSV names.
	
2000-11-10  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-76

	* The way to store binary files modified as the prevoius version did
	not work for matrices. The storage scheme will be described in AUG.

	* AMI includes now reading and writing of binary files. The function
	variables for the read and write functions are changed. 

	* I have written and read data back and forth between ARTS and Matlab,
	and between ASCII and binary. Everything seems OK. Even conversion
	between double and float. But there are so many combinations, so
	no guarantees. Tell me if you find any bugs.

	* make_wsv_h.cc produces now also a text file, wsv.txt, with the
	information from workspace.cc. This file is used both for AGU and AMI.
        Feel free to fix an alphabetical order of the variables in wsv.txt.
	This would look better in AUG.
	
	* The file wsv.txt is copied to ami when running init.m. This file
	is then used by read/write_artsvar to determine to type of the 
	varaibles for e.g. consisteny reasosns. The type is also needed when
	reading and writing binary files.

	* Two appendices introduced in AUG, consisting basically of wsv.txt
	and math_test.cc respectively.
	
2000-11-09  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-75

	* species_data corrected, a O2-snglt-delta tag number 32005 of the
	JPL catalog was included with the main O2 isotope, even though
	this tag is only present in very small abundance. This tag shows
	very strong absorptions, and it should be checked whether a
	detection from a satellite instrument in possible.

	* example1.arts and other arts controlfiles modified, since
	Patrick renamed some of the workspace methods.

2000-11-09  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-74

	* src/m_hmatrix.cc file had still hdf5 included, removed.

2000-11-08  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-73

	* Changed from HDF 5 to HDF 4. More precisly, HDF 4.1r3 is used.

	* String (including arrays) can now be read and written as binary.

	* Default extensions for ASCII files changed. Both numeric and
	string files have now the extension .aa (ARTS ASCII). I did
	not see any strong reason to have different extensions. 

	* The binary files are now displayed using hdp or vshow. See further
	AUG.

2000-11-07  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-72

	* JPL catalogs can now be read, they have to be frequency sorted.
	A merged catalog is now included in the arts distribution at:
	data/spectroscopy/jpl00/jpl00.cat, it contains only species know
	to arts. The script merge_and_sort_jpl does the merging and
	sorting, for more info refer to the script.

	* MYTRAN catalogs can now be read, they do not have to be
	frequency sorted. A slightly modified version of the mytran
	catalog of the ESTEC Spectroscopy Study is now included in the
	distribution, it can be found at:
	data/spectroscopy/mytran/mytran98.my2. This catalog is slightly
	modified, since the original included a HO2 species not know to
	arts.

	* comparisons scenarios are now sorted according to the chosen
	scenario:
	aux/iup_forward_comp/H2O_183GHz : contains the water vapor
	                                  comparison at 183GHz
	aux/iup_forward_comp/master_b   : contains some comparisons for
                              	          the master B band
	aux/iup_forward_comp/fascod     : the fascod files in the old iup
	                                  forward format.

	* abundance: Information on the source and calculation of the
	abundance used in arts is located at: aux/abundances/

2000-11-06  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-71

	* Introduced a file format for ARRAYofSTRINGS. The extension is .as.
        See ArrayOfStringWriteAscii for the file format.
	When reading, blanks (white space) is for the moment not allowed.
	Is this accapteble? My answer is no. If anyone can fix this, please
	go ahead.

	* There should now be a full set of functions for the .am format. 
	For example, the function NumericWriteAscii exists now.

	* There is also a full set of functions for numeric binary files using
	HDF 5. But it was probably a mistake of me to pick HDF5 instead of HDF4
	(I just wanted to use the freshest version). This as it turned out 
	that there are only functions in Matlab to handle HDF4. In addition,
	Frank Merino has never told me what version he uses for Odin, but an
	old e-mail indicates that he uses HDF4 (I how now sent an e-mail to 
	confirm this).
	So I am afraid that I have to take one step backward and change the
	core functions to use HDF4.
	
2000-11-02  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-70

	* Included some files to read and write binary files for arrays. 
	Turned off HDF error messages. Improved ARTS error messages.
	(I wanted mainly to commit before leaving for today as I will work at
	home tomorrow. Can read e-mail, but not do cvs commits).
	
2000-11-02  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-69

	* Sorry, but I think that I did the last commit in src. This is mainly
	to fix this error, and to give you the last version of thr ChangeLog
	and TODO. (Some extra in TODO compared to my e-mail).

	* The LOS structure uses now ARRAYofsizet instead of ARRAY<int>

2000-11-02  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-68

	* First version handling binary data files. For the moment there are
	function to read and write binary files for NUMERIC, VECTOR and MATRIX.
	To add functions for other data types (beside strings) should be 
	straightforward, using the general interface functions to HDF.

	* To test the binary-IO, make a control file called test.arts as:
	     VectorNLinSpace (z_abs)     { start = 1.1
                                           stop  = 13.65
                                           n     = 15 }
             VectorWriteBinary (z_abs) {""}
             VectorReadBinary (z_abs)  {""}
             VectorWriteAscii (z_abs) {""}
        The binary files can be displayed by the HDF tool h5dump:
	   h5dump test.z_abs.ab
	If everything is OK, the ASCII file shall have the same content, check
	by
	   more test.z_abs.am
	Note the different extensions.
	Another HDF tool function is h5ls that showes the structure of the data
	(without displaying any data values, in contrast to h5dump).
	
	* To make a distinction between ASCII and binary files, the ASCII
	functions have changed name as:
	  WriteToFile  -> WriteAscii
	  ReadFromFile -> ReadAscii
	The binary functions are denoted correspondingly:
	                  WriteBinary
	                  ReadBinary

	* Cleaned up the IO parts in methods.cc (the functions are now ordered
	after data type). Did the same in m_io.cc. Corrected some function 
	descriptions in methods.cc.

2000-11-01  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-67

	* aii: Added this directory for the ARTS-IDL interface and set up
	Makefile.am. 

	* configure.in: Added aii/Makefile.am here.

	* uguide: Added a new section `Utilities'. This should contain a
	description of the Matlab and IDL interface.

	* uguide/utilities.tex: Started this file as a template for
	Wolfram to use. No contents yet.

	* uguide/Makefile.am: Updated this (added formats.tex and
	utilities.tex). 
	
2000-10-30  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-66

	* AGU has now a new chapter describing data and file formats, and 
	allowed math operations. The chapter is however not finished. Please,
	give comments. The file src/test_math.cc is added and is compilied with
	ARTS. This file should contain examples on all allowed basic math
	operations and is read into AUG. As the file must pass the compiler,
	AUG can only include allowed math operations (at least formaly).

	* Some first test functions for HDF are found in file.cc and 
	m_hmatrix.cc.

2000-10-27  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-65

	* file.cc: Included a function open_hdf that illustrates the use
	of HDF. This is one of the HDF examples. Other modifications:
	Added #include <hdf5.h> in top of file

	* Makefile.am: Added a line to include the necessary libraries for
	HDF (quite a few). 

	* If HDF is correctly installed, this should work.

2000-10-25  Oliver Lemke  <oliver@uni-bremen.de>

	* arts-0-0-64

	* configure.in: Disabled documentation generation by default.
	Activate it by invoking configure with the option --enable-docs.

2000-10-23  Oliver Lemke  <oliver@uni-bremen.de>

	* arts-0-0-63

	* doc/uguide/.cvsignore updated.

2000-10-23  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-62

	* ARTS can now produce spectra and WFs including sensor effects and
	data reduction. Some new WF functions and copy functions implemented.

	* H matrices are read as: 
   	    HmatrixReadFromFile(h1){""}
	There are two H matrices to use, h1 and h2.

	* The functions to calculate WFs now only return the matrix for the 
	retrieval identity of interest. A WF function can return the common
 	matrix for several identities if they all have a retrieval grid of the
	same length (the variable k_index is removed).
	The variables kx and kb are introduced (following Rodgers). WF data are
	appended to these variables as
	   kSomeFunction...
	   kxInit{}
	   kxAppend{}
	   kxAppendUsingH(h1){}
	     or
	   kbInit{}
	   kbAppend{}
	   kbAppendUsingH(h1){}
	If kxAppend and kbAppend are used, when the WFs calculations ar ready,
	a H matrix can be applied as
	   MatrixApplyH(kx,h1,kx){}
	This latter approach should be the fastest, while applying H when 
	appending (kxAppendUsingH) saves memory.

	* A second spectrum vector, y0, has been introduced.
	H matrices are applied on spectra as
	   VectorApplyH(y,h1,y){}
	   VectorApplyH(y0,h1,y){}
	Note that it is best to do this last in the control file as some 
	functions need the pencil beam monochromatic spectrum (e.g. absloswfs).
	Y can be copied to y0 as
	   VectorCopy(y0,y){}
	There is also a function to copy matrices (MatrixCopy).

	* The WF for a sensor variable can be obtained as follows. Calcualte
 	h1 for the nominal state, change the variable of interest and calculate
	h2. The WF is then calculated using the kDiffH functions:
	   kDiffHFast{ name    = "Proportional"
                       delta   = 0.01
                       grid    = 0
                       apriori = 0}
	There are two functions, Fast and Small, trying to optimize calculation
	spped and memory usage, respectively. Note that these functions give 
	the WF including the effects of h1 (i.e. kxAppendUsingH should not be
	used).
	There is a function kManual that uses y and y0 to calculate a WF:
	   kManual{ name    = "CBGR"
                    delta   = 2.73
                    grid    = 0
                    apriori = 2.73}
        The WF is calculated as: k = (y-y0)/delta
	As a test, I calculated the WF for cosmic background radiation, but
	there should be better applications for this function.

2000-10-22  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-61

	* I primarily wanted to commit a version to backup my work as I have 
	not made a commit for some time. I am working on the WFs and the
	H matrix stuff. See TODO for my plans. I will give the details at
 	next commit.

	* Some bugs fixed in ami.

2000-10-21  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-60

	* make_md_h.cc: There was a bug in the generic input/output
	WSVs. For example, if a method had a vector as generic input and a
	vector as generic output, the input vector was removed from the
	list of arguments, similar to the case of specif WSV. In the case
	of specific WSVs this is the correct behaviour. However, in the
	case of generic arguments, the two vectors can be different! Fixed
	this.

2000-10-10  Oliver Lemke  <olemke@uni-bremen.de>

	* arts-0-0-59

	* doc/uguide/los1d.tex: Removed .eps endings which broke the
	pdf output. It's IMPORTANT to avoid the endings because they
	are now autodetermined.

2000-10-09  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-58

	* lineshape voigt approximation of kuntz implemented, currently
	only one accuracy level, others will follow. this lineshape is
	hard wired in absorption.cc, will be a controlfile input soon.

	* partition function coefficients reorganized, they are now part
	of IsotopeRecord

	* comparison with old forward model performed, using the kuntz
	lineshape. Results are within 1% error in the absorption
	coefficients for the specific calculation H2O_183GHz where only
	this line was considered. Larger errors up to 10 % are found at
	higher altitudes, guess that is an interpolation problem of the
	input vmr profiles. Controlfiles, etc can be found in a new
	directory: arts/aux/iup_forward_comp

	* errors with the documentation, guess that is caused by a
	previous check in, since I did not do anything over there.

2000-10-05  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-57

	* Extended TODO list to have a base for discussion.
	
2000-10-02  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-56

	* Refraction included. All observation geometries are treated.

	* The refraction is included in a totally new way (to my best 
	knowledge). A "prolongation factor" is used that gives the ratio
	between the length of the refracted and the length of a corresponding 
	geometrical LOS between two vertical altitudes. This approach avoids 
	the singularity at tangent points and does not need any integral 
	approximations etc. This results also in fast calculations.
	See further AUG.
	
	* If n is set to 1, the refractive functions and the geometrical ones
	give basically identical results, the difference is on the dm level
	at the top of the atmosphere. This should indicate that the refractive
	functions should give very accurate results.

	* A function to get the refractive index for totally dry air is 
	implemented.
	
2000-09-27  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-55

	* Voigt lineshape included, Kuntz approximation to it. 

	* Doppler parameter calculation included.

	* Constants required included.

2000-09-26  Oliver Lemke  <oliver@uni-bremen.de>

	* arts-0-0-54

	* UserGuide: Added pdf output. Divided main.tex in uguide.tex and
	uguide_pdf.tex. Changed the makefile to generate pdf and ps output
	by default. The pdf version requires all figures in pdf-format.
	The conversion from eps to pdf should be done with the epstopdf
	command.

	epstopdf <figure.eps>

	Remember to convert new figures to pdf and do a cvs add.

	* Added default graphics extension in uguide.tex and uguide_pdf.tex
	Now eps and pdf extension in includegraphics commands are no longer
	necessary. LaTeX and PDFTeX will pick the right file automatically.

	* Fixed bug in uguide/Makefile.am: dvips' output on some systems
	is send to lpr by default. Added -f option.
	
2000-09-22  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-53

	* src/Makefile.am: Fixed small bug. (Removed wsv_pointers.h form
	the source list because this file does not exist.) The bug caused
	an error message in make dist.
	
2000-09-22  Axel von_Engeln  <engeln@uni-bremen.de>

	* more TODO stuff, some comments in partion_function_data.cc

2000-09-20  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-52

	* main.cc, make_wsv_pointers_cc.cc: Changed the define_wsv_pointer
	to make local workspaces possible. (So far it was only possible to
	have one global workspace. Now multiple workspaces can coexist,
	each with their own pointers arrays.)
	
2000-09-19  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-51

	* absorption.cc: Corrected the internal unit of line intensity
	S. It is now Hz * m^2, consistent with the simple formula
	
	alpha = n * x * S * F,
	
	where alpha is the absorption coefficient (1/m), n is the total
	number density (1/m^3), x is the volume mixing ratio
	(dimensionless), and F is the line shape function (1/Hz). 

	The intensity also already includes the isotope ratio, since this
	is computationally more efficient. 

	* Verified that we still get the same absorption results.

	* Moved some doxygen headers from absorption.h to absorption.cc

2000-09-19  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-50

	* Stefan and I decided that doxygen headers should be placed in .cc
	instead of .h files (when appropiate). This partly to make it easier
 	to put in histories. 

	* Following this decision, I moved doxy headers from atm_funcs.h and
	math_funcs.h to corresponding .cc files.
	
2000-09-18  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-49

	* Doxygenified, and cleaned up existing documentation, for files:
	m_wfs.cc, m_los.cc, atm_funcs.h,cc, math_funcs.h.cc, vecmat.h,cc
	and los.h.

2000-09-14  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-48

	* Removed 1D from function and variable names for LOS, RTE and WF
	parts. We have decided that 1D is default, and 1D should not be 
	included in the names. However, 2D shall be included.

	* The variable klos is renamed to absloswfs (uh, long name, I know).
	This to follow AUG closer. There is also source LOS WFs, but these
	WFs are so far only used by kTEmpNoHydro and are not a workspace 
	variable.
	
2000-09-14  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-47

	* Adapted the doxygen emacs macros for ARTS. Most notably, we want
	to use the /** style to mark comments rather than the /*!
	style. With the /** style the first sentence is taken
	automatically as the short description. I find this
	convenient. Also, this way the comments are less comlicated and
	verbose. 

	* Added documentation about the header format in the Development /
	Conventions section of the user guide. Patrick, can you check this
	please? The emacs macros now should generate exactly the same
	thing as defined there.

	* I have not yet gone through the code making things consistent with
	the new standard, but of course this should be done. First I want
	your ok to this standard. 

2000-09-13  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-46

	* Cosmetic changes to doxygen comments all over the place.

2000-09-13  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-45

	* doc/emacs: Added makros for inserting documentation
	headers. There is some html documentation, check out
	doc/index.html. 

2000-09-12  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-44

	* The definition of the source function along the LOS is changed.
	The source function is now defined following the absorption.
	The source functions values are now determined at the LOS points.
	The source functions for a LOS step is calculated as the mean
	of the values at the end points of the step. 
        This change was made to get a similar treatment of the absorption and
	the source function. This is of great help for the analytical WFs.
	See further AUG.

	* Analytical WFs for species, continuum absorption and temperature
	(without hydrostatic eq.) are now ready. See some examples
 	on how to use the function in:
           arts/doc/examples/full.arts
	I have made some quick tests of the WFs. The agreement when disturbing
	the absorption and the temperature with the WFs was excellent. However,
	I have only tested a single upward looking case and there could be 
	bugs. I prefer to wait to do further testing until I am sure that this
	is the final version. 

	* Ground reflections now handled for correctly (hopefully), both for
	1D and 2D cases. Ground reflections also included in the analytical
	WFs.
	
	* AUG (ARTS user guide) is updated and extended to reflect the 
	changes above and several minor errors fixed.

	* WFs are now appended to the total K matrix. Before starting WF 
	calculations, the function kInit shall be called. As a help for
	non-linear inversions and to display results, there are now some
	help variables for the K matrix, giving index, names, a priori value,
	and retrieval grid for the different retrieval identities (e.g. a 
	species profile). However, the k_names cannot be stored as this is
	an ARRAYofstring. This is so far not included in AUG.

	* New workspace variable type: ARRAYofstring

2000-08-31  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-43

        * Put in a check command in z2p to handle limb observations
        outside the atmosphere.

	* Changed name on the workspace variables f_abs and view1 to
	f_mono and za_pencil, respectively.
       Za stands for zenith angle. I think this is a better name than 
       viewing angle 1. Zenith angle is a clearer description and I guess
       that there never will be a view2 (it could for example be called orbit
       angle).
       F_abs or f_mono (i.e. monochromatic frequencies) doesn't really matter.
       I just think f_mono fits za_pencil better.

        * AMI functions for reading and writing data renamed. To read
        any file having ARTS data format, use read_datafile. To read
        a ARTS variable, where the last extension is .am, use read_artsvar.
        Corresponding write functions exist. 

        * read_tb removed. Conversion to brightness temperature now treated
        as part of H (see below).

       * A first set of functions to set up the sensor and data reduction
       transfer matrices. These functions are found in ami/hmatrix.
       Some simple tests have been performed but final debugging is not yet 
       done.
       
       Basic facts:
       - A single frequency grid is valid for all zenith angles if no data 
       reduction is performed.
       - With data reduction, all combinations of frequencies and angles
       are allowed.
       - To apply a possible data reduction on covariance matrix for thermal
       noise and weighting functions for baseline ripple terms, the data
       reduction transfer matrix must be known. To set up baseline ripple WFs,
       the final zenith angles and frequencies of the sensor must also be
       known. 

       To handle these facts, there are 6 main variables:
         H         Total transfer matrix. Conversion from monchromatic pencil
                   beam spectra to final, possibly data reduced, measurement
                   vector.
         Hd        Transfer matrix for data reduction. Conversion from sensor
                   output to final measurement vector.
         f_sensor  Centre frequency of the spectrometer channels (assumed to
                   be identical for all angles).
         za_angles Zenith angles observed by the sensor.
         f_y       The frequency of each element of the measurement vector, y
                   (has the same length as y in contrast to f_sensor)
         za_y      The zenith angle of each element of the measurement 
                   vector, y (has the same length as y).

       * Some example file to use these functions will be delivered.

       * To do: the widths of the channels must be included in some way for
       correct calculation of thermal noise.

2000-08-21  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-42

	* lineshapes.cc: Added this file. It contains the definition of
	the available lineshape functions (at the moment only a quick hack
	of Lorentz), as well as the lineshape function lookup data
	(initialized by define_lineshape_data). The lookup data contains
	one record for each lineshape. The record contains name and
	description (as usual), the cutoff frequency (-1 if none), and a
	pointer to the actual function. So, if you have the index of the
	lineshape you want to use, you can call the apropriate
	function. No need for any if or switch statements anywhere.

	* workspace.cc: Added WSV lineshapes, an ARRAY of size_t. This
	will hold one index for each abs_tag. If you have several abs_tags
	for different isotopes or transitions of a species, you may use
	different lineshapes.

	* Missing: A WS method to set lineshapes; use lineshapes in
	absorption calculation.

2000-08-16  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-41

	* Had a go at implementing sparse matrices with TNT. This is only
	a quick fix, I don't think it works satisfactorily. In fact, I
	think TNT is crap and we should switch to MTL as soon as
	possible. There is an example method hTest that initializes a
	sparse matrix. It works, but the TNT sparse matrices lack
	basically all functionality. Also I had to fix a number of bugs
	inside TNT to make it work at all!

	* sparse.arts: Added this example in doc/examples. It calls just
	the hTest method.

	* vecmat.cc: Added this file. It contains some stuff that used to
	be in vecmat.h.
	
2000-08-10  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-40

	* Rearranged almost everything. :-)

	* Automatic sources include now also workspace variable groups and
	the workspace itself. This makes adding new variables (and groups)
	easier. See Howto in Uguide how it's done now. There are quite a
	few new files:

	* goups.cc: NEW: Contains the lookup data for WSV groups. Here you can
	add new groups if you want to.

	* wsv_groups_h.cc: NEW: Automatically generates wsv_groups.

	* wsv_groups.h: NEW: Declares the enum type that is used to identify
	WSV groups. Also some other stuff related groups. AUTOMATIC FILE.

	* wsv_pointers_cc.cc: NEW: Automatically generates wsv_pointers.cc.

	* wsv_pointers.cc: NEW: Generates WSV pointers which are
	used by the engine. Now these pointers don't have to be specified
	with the wsv_data anymore, which makes the wsv_data
	nicer. AUTOMATIC FILE.

	* species_data.cc: NEW: Species specific lookup information (for
	example isotope ratios).

	* wsv.h: Now contains also the workspace itself.

	* workspace.h: REMOVED.

	* globals_1.cc: REMOVED.

	* make_wsv_group_h.cc: Renamed to make_wsv_groups_h.cc

	* make_wsv_groups_h.cc: Renamed from make_wsv_group_h.cc

2000-08-08  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-39

	* absorption.cc: hitran/mytran tags were wrong

	* absorption.h: several checks that tried to 
			estimate the molecular weight 
			from the isotope name did not
			work properly, commented

	* example1.arts: was empty in last check in

2000-08-08  Axel von_Engeln  <engeln@uni-bremen.de>

	* arts-0-0-38

	* absorption.cc: Included all molecules from JPL/HITRAN.

2000-08-05  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-37

	* This is still an intermediate version. I'm in the process of
	re-designing the automatic generation of header files. Basically,
	the workspace itself should also be generated automatically from
	the information in define_wsv_data.

	* Achieved so far: Wsv group handles (file wsv_group.h) are now
	generated automatically from information in function
	define_wsv_group_names in file groups.cc.

2000-07-30  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-36

	* Come a long way to making a first release. The physics of the
	release will be the same as in the Bredbeck version. In other
	words, still no realistic absorption coefficients. Took a lot of
	fiddling to make the right things go into the release. Now I'm
	almost there, but there is still an overall check lacking.

	* Switched from DOC++ to Doxygen, which is really much much
	better. In particular, the generated HTML document can optionally
	include the source code, in which case it is really good for
	source code browsing.

	* Put all the documentation neatly under `doc'. Also, made a HTML
	page in doc that references all the documentation. IMPORTANT:
	NEVER EDIT THE FILE index.html DIRECTLY. Instead, edit
	index.html.in. 
	
	* Todo: Doxygen is more or less compatible with DOC++, but a lot
	of minor changes still need to be made. In particular, next I will
	fix the \verbatim parts in documentation headers, which seem to
	not come out right.

2000-07-26  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-35

	* Moved user guide to doc/uguide.

2000-06-17  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-34

	* absCalc: Tested this method.

	* full.arts: I wanted to preserve Patricks example, so this one is a
	combination of my absorption and your example h2o.arts.
	I have taken the midlatitude-winter atmospheric scenario of
	data/atmosphere/fascod, since it is the only one for which
	Patrick's p_grid and k_grid are inside the pressure range. Also,
	k_grid had to be slightly changed. The spectrum y looks
	reasonable, but the k matrix looks strange (ragged).

2000-06-16  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-33

	* Added section `The ARTS concept' to user guide.

	* Filled in section development/organization
	
	* Added prototype for method absCalc{} which will calculate
	absorption in a rather simplified way for demonstration.

	* example1.arts: Made this file a lot nicer with comments and
	such. 

	* Added GNU license everywhere in arts and arts/src.

2000-06-15  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-32

	* Now compilation without optimization is the default. In fact,
	for now it is impossible to turn optiomization on. :-)

	* Merged notes.txt with the uguide. Removed notes.txt.

	* doc/examples: Added this directory. Inside is my example file
	example1.arts. Output files of this example are listed in
	.cvsignore. 

	* doc/examples/arts: A script that calls the built arts
	executable. 

	* data/spectrocopy/hitran96: Added this directory. It contains a
	section of the Hitran catalogue up to about 900 GHz. Also contains
	a smaller file with just H2O lines.
	
2000-06-15  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-31

	* A first version of species WFs is ready. All observation geometries
 	are handled, but ground intersections are not yet considered. 
        The function cover so far only the case when all the absorption is 
	created by a single species. The WFs are returned normalised to the 
	a priori profile. Other units will be implemented when the absorption
	part is ready.
	Some first tests have been performed but no extensive bug checks have
	been done. So be aware.

	* New workspace variables: k_grid, k
	  New methods: kSpecies1d

	* My AUG parts are also updated and do now match the source code (for 
	the implemented parts). 

	* The RTE and BL core iteration is now found in seperate functions. 
	This should faciliate the future use, for single scattering etc.

	* INTERPP now also in matrix-row version.

2000-06-12  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-30
	
	* lines_per_tgCreateFromLines: This method splits up the line list
	into sub-lists for each tag group. This is the place where the tag
	groups are applied to divide the line list!

	* lines_per_tg (type ARRAYofARRAYofLineRecord ): This stores the
	line lists for the individual tag groups. This will be input the
	absortion coefficient calculation. 

2000-06-11  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-29
	
	* Input Atmosphere stuff is 1D (so is RTE). Only the absorption
	coefficient calculation itself is already 2D, since this is
	practically no extra effort.

	Reason for 1D input: It is not enough to just read a list of
	profiles. They could be on different horizontal grids. In fact one
	must somehow specify the horizontal coordinate to do proper horizontal
	interpolation. 

	* Added row and col functions which extract a row (or column) from
	a matrix. The output can be a vector or a matrix. For a matrix the
	first and the last row (or column) to extract have to be
	specified. I was really missing this, many times you have a
	function that can act on a vector, so you want to apply it to a
	row or column of your matrix.

	* Atm2dFromRaw1D: This method interpolates the raw atmospheric
	inputs onto the absorption grid.

2000-06-10  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-28

	* The new compiler (g++-2.95.2) is more fuzzy about redeclaration
  	of variables. Therefore all global variables had to be moved to
	two separate files.

	* Rearranged workspace and methods data, so that workspace.h,
	workspace.cc, and methods.cc contain only the data itself.
	
	* globals_1.cc: Global variables that do NOT depend on wsv.h.

        * globals_2.cc: Global variables that DO depend on wsv.h.

	* workspace_aux.cc: Auxiliary stuff that used to be in workspace.cc.

        * methods_aux.cc: Auxiliary stuff that used to be in methods.cc.

	* los.h: Declaration of the Los data type. Moved there from
	workspace.h 

	* wsv_groups.h: Everything related to WSV groups.

	* wsv_aux.h: Auxiliary stuff for the workspace.
	
	* I do not get any warning messages. Patrick, do you still get
	them? 
	
2000-06-09  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-27

	* Cleaned up the LOS functions and the corresponding parts of the
	user guide. Included functions to calculate total atmospheric 
	transmisioion.

	* The compilation gives some warning messages.
	
	* The LOS starts now always in space. The case with the blackbody
 	ground is not considered anymore. This made the functions simpler.

	* The LOS and RTE functions renamed (sorry about that). 
	Functions giving spectra are now called yRte, and functions giving
	transmisiion yBl (Beer-Lambert). Made some functions for special cases
	where less workspace variables must be set. Some functions name:
	- los1d
	- los1dNoRefraction
	- los1dUpward
	- source1d
	- trans1d
	- yRte
	- yRteNoGround
	- yBl
	- yBlNoGround                          

	* The function startup added to AMI.

2000-06-01  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-26

	* Added workspace variables: 
	n_profiles, 
	ptz, 
	raw_vmr_profiles,
	t_and_all_vmrs 

	* raw_vmr_profilesReadFromScenario: Added this method. It does
	just what the name says.
	
	* Changed standart data file extension from .a to .am (you can
	read this as `arts matrix' or as `array of matrix', as you
	like). The single a seems to be already in use by other programs. 

	* Removed the WriteToNamedFile and ReadFromNamedFile methods. Now,
	there are only ReadFromFile and WriteToFile methods, which take a
	filename as a keyword parameter. You can give an empty string as
	the name, then the default name is chosen. It was simply too
	nerve-wracking to have to duplicate each and every IO function for
	these two cases.

2000-05-30  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-25

	* What was version 24?

	* parser.cc: Fixed bug in SourceText::AdvanceChar(), which lead to
	the last line of the controlfile not being correctly
	parsed. Correctly treating the end of the file seems to be the
	biggest problem for the parser! Hope this works correctly now.

	* tag_groupsDefine: Added this workspace method. It sets the
	contents of the workspace variable tag_groups, which contains the
	available tag groups. A tag group can consist of several tag
	definitions, but contrary to the Bredbeck definition, they must
	all relate to the same species. The reason for this is that there
	will be one VMR profile associated with each tag group. 

	The drawback is that there must be a tag group for each molecule
	you want to calculate absorption for. But I don't see another
	solution, somewhere it has to be defined which input data to
	use. I think one tag group = one input profile is the cleanest
	solution. 
	
	* Discovered a nasty problem with strstream. Essentially, it does
	not work as I thought it did. Replaced by the future standard
	stringstream. Since stringstream is not yet part of EGCS, I have
	added the necessary files to the ARTS source code. The files are:

	sstream.h (contains also the contents of the original file sstream.cc)
	iotraits.h

	I got these files off the web:
	ftp://ftp.fmi.uni-konstanz.de/pub/algo/personal/kuehl/sstream-egcs.tgz. 
	They are written by Dietmar Kuehl.

	* Replaced strstream by stringstream everywhere. Pure stringstream
	also seems to work not so well, so I always use either
	ostringstream or istringstream.
	
2000-05-23  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-23

	* Included present versions of the ARTS Matlab interface (AMI) and
	the user guide to the CVS distribution.

	* Updated AMI to handle new data format
	Present functionality of AMI
	Read and write files basic data files
	Call ARTS from Matlab
	Setting the MAtlab search path

	* Please note that the user guide is not up to data and does
	not match the present version of ARTS

2000-05-22  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-22

	* ARTS can now read HITRAN catalogue files!

	* Methods: linesReadFromHitran, linesWriteToNamedFile
	These methods are rather preliminary, because how they should act
	eventually depends on the rest of the absorption module. Anyway,
	I've tried to rather cleanly implement the capability to
	understand HITRAN in the utility function 

	LineRecord::ReadFromHitranStream(istream& is)

	Yes, this is a member function of LineRecord, the data structure
	that stores spectro data for a single line. In the future, similar
	member functions can be added to read from JPL (setting widths to
	default values) and of course eventually from the native ARTS
	format. 

	Of course, the program does not depend internally on any
	particular catalogue at all. In particular not on HITRAN. Rather,
	during the read-in, the HITRAN data is right away converted to the
	ARTS internal format. 

	For now, this stuff seems to work fine. Ah yes, the line data is
	according to the recommendations given in the Bredbeck book. I've
	tried to document all formats and units as best as I can in the
	code directly.

2000-05-20  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-21

	* Added species lookup data. I filled in the data only for H2O and
	O3, because I'm too lazy right now. 

	Molecular masses: From looking at the table in forward_4_96,
	glob_def.c, the relative difference between the actual mass and
	the mass simply estimated from the Atom number is only 0.001. This
	seems not worth the trouble. Anyway, the field for the mass is
	there. Should anybody feel like adding the true numbers, just go
	ahead.

2000-05-15  Stefan Buehler  <sbuehler@uni-bremen.de>

	* math_funcs.cc: Bug fix in
	void to_vector(VECTOR& x, const MATRIX& W)

2000-05-12  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-20

	* Added implementation of --workspacevariables (-w) command line
	option. 

	* Put the handling of the more complex command line options
	(-r,-d,-m,-w) in subroutines.

	* Added command line option --groups (-g) which simply lists all
	wsv groups.

	* This means the command line options are complete for now.

2000-05-11  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-19

	* Added the implementation of the --methods (-m) dommand line
	option. Seems to work beautifully!

2000-05-08  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-18

	* Added the implementation of the --describe (-d) command line
	option. 

2000-04-30  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-17

	* Added the command line parameter --reporting (-r).
	This should be a two digit integer. The first digit specifies
      	the output level for stdout (stderr for error messages), the
      	second digit the output level for the report file. The levels
      	can reach from 0 (show only error messages) to 3 (show
      	everything). Example:
  
      	03 = only errors to the screen, everything to the file.

	* Added some other cool command line parameters. However,
	currently they only produce a message that the implementation is
	still lacking. These are:

	string methods:    
	If this is given the argument `all', it simply prints a list of
 	all methods. If it is given the name of a variable, it prints all
 	methods that produce this variable as output.
        
	string workspacevariables:
       	If this is given the argument `all', it simply prints a list of
 	all workspace variables. If it is given the name of a method, it
 	prints all variables needed by that method.

        string describe:
  	Print the description string of the given workspace variable or
 	method.

2000-04-29  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-16

	* vecmat.h: Small changes to the text defining the allowed
	matrix/vector operations. (In one instance it said `MATRIX' where
	it probably should say `VECTOR'.)

	* file.h: Fixed a strange bug: When the last line of a textfile
	was not terminated by a newline character, it was read twice by
	read_text_from_stream. Learned the following: If the end of stream 
	s is reached, first s.eof() becomes true, but s is still
	false. Only if one tries to read past the end does s become true. 

	* Implemented ARRAYofMATRIX and ARRAYofVECTOR as standard
	types. In particular, these are also now types of workspace
	variables. Implemented IO functions for these:

	Output:
	ArrayOfMatrixWriteToFile,
  	ArrayOfMatrixWriteToNamedFile,
  	ArrayOfVectorWriteToFile,
  	ArrayOfVectorWriteToNamedFile,

	Input:
	ArrayOfMatrixReadFromFile,
  	ArrayOfVectorReadFromFile,

	The file format is now always that of ArrayOfMatrix. All other
	variables are treated as special cases with apropriate dimensions
	set to 1. Only a single real output and only a single real input
	function are used (that for ArrayOfMatrix). This means that other
	types have to be converted to this type before writing or after
	reading. This is not terribly efficient. Should there be
	performance or memory problems later on, then we have to write
	dedicated IO functions. The amount of code is probably about the
	same, just to me the real IO seemed more difficult than the
	conversions, hence I did it the way I did it.
		
2000-04-12  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-15

	* This version can produce spectra (without refraction).
	  General functions to determine the LOS, to get transmission and
	  the source function along the LOS and to solving the RTE along
	  LOS are ready.
 	
	* A first list on vector and matrix functionality written. It is
	  found in vecmat.h. Some functions changed and added to match
	  the stated functionality.

	* Some workspace variables added and some renamed. The variables 
	  are now
	    VECTOR     p_abs;
	    VECTOR     t_abs;
	    VECTOR     z_abs;
	    VECTOR     f_abs;
	    MATRIX     abs;
	    VECTOR     view1;
	    Numeric    z_plat;
	    Numeric    l_step;
	    int        refr;
	    Numeric    l_step_refr;
	    VECTOR     refr_index;
	    Numeric    z_ground;
	    Numeric    t_ground;
	    VECTOR     e_ground;
	    Los        los; 
	    MATARRAY   source;
	    MATARRAY   trans;
	    VECTOR     y_space;
	    VECTOR     y;

	* Example on new method calls:
	    y_spaceStd{1}
            y_spacePlanck{300}
            losBasic{}
            sourceBasic{}
            transBasic{}
            yGeneral{}

2000-04-10  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-14

	* token.cc: Fixed small bug in definition of TokValTypeName.

	* reconf: Remove links before trying to re-configure.
	
	
	* arts-0-0-13

	* Renamed token types to 
	enum TokValType { string_t,    int_t,    Numeric_t,
	                  ARRAY_string_t, ARRAY_int_t, ARRAY_Numeric_t,
                          undefined_t };
	This is now consistent with the token type names in token.cc.

	* Removed Integer type, since it is no longer necessary.

	* notes.txt: Updated with respect to global constants.

	* notes.txt: Added howto about switching off optimization.

	* Everywhere: Changed const extern to extern const. This is just
	for nicety, the two are the same thing.

	* vecmat.h: Moved Patricks vector/scalar operations here from
	tnt/vec.h.

	* Compiling without optimization is really much much faster. I
	wish I had realized this before!
	
2000-04-06  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0-0-12

        * Some methods are commented out due to compilation problems

	* Changed definitions of constant to e.g.
    	    extern const Numeric EARTH_RADIUS   = 6.378e6;
	To use the constant, type
	    extern const Numeric EARTH_RADIUS;
	I had to add extern also at the definition to get it to work.
	Stefan, is the text in notes.txt really correct?

	* Added doc++ text and file header to constants.cc and math_funcs.cc
	
	* Workspace types added (as temporary solution):
	    Integer
	
	* Workspace variables added (or renamed):
	    VECTOR  z_abs;
	    VECTOR  view1;
	    Numeric z_plat;
	    Numeric l_step;
	    Integer refr;
	    Numeric l_step_refr;
	    Integer cbgr;
	    Numeric z_ground;
	    Numeric t_ground;
	    VECTOR  e_ground;
	    Los     los; 

	* Methods added:
	    IntSet
	    VectorSet
	    VectorLinSpace
	    VectorNLinSpace
	    VectorNLogSpace
	    losGeneral

	* Files included:
	    m_los.cc 
	    atm_funcs.cc
	    atm_funcs.h
	  
2000-04-05  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0-0-11

	* Fixed the bugs reported by Patrick. This is not a running
	version of the program, because the file src/m_los.cc is missing!

	* parser.cc: Fixed bugs 1:

	The case with the optionally missing keyword for one parameter
	methods was not handled correctly. Now the current character is
	used to recognize this case. THIS MEANS THAT KEYWORD NAMES
	STARTING WITH A NUMBER WILL BREAK THE PARSER! I don't know a
	better solution without look-ahead.

	* parser.cc: Fixed bugs 2:

	The last method was executed twice in some cases, due to incorrect
	flagging of Eof in function SourceText::AdvanceChar.

2000-04-04  Patrick Eriksson  <patrick@rss.chalmers.se>

	* arts-0.0.10

	* Set the ground to include los1d. Included the file m_los.cc.
	  Introduced the workspace variables plat_z and view1 for test
	  purposes. There will be more variables connected to los.
	  Some bugs mailed to Stefan.

2000-04-04  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0.0.9

	* Added method losTest just to see if we can access los. This does
	not initialize los, just change the value. For a real method, this
	would be very bad style, it should re-set los completely, unless
	los is also specified as INPUT variable in methods.cc. 
	

	* arts-0.0.8

	* Added workspace variable group Los and workspace variable los on
	Patrick's request. The declaration of Los is now in file
	workspace.h, but it could be moved somewhere else in the future.

	
	* arts-0.0.7

	* parser.cc:
	In void read_name(string& name, SourceText& text): Changed isalpha
	to isalnum, so that names may now also include numbers. 

	This was a request of Patrick. I don't remember if I had a good
	reason to allow only alphabetic characters and underscores. Let's
	just see if we get any problems with this.


	* arts-0.0.6

	* Quickly implemented NumericSet for Patrick

	* workspace.h:
	- Added Numeric_ in WsvGroup 
	- Changed N_WSV_GROUPS to 3
	- Added   Numeric dummy to class WorkSpace
	- Added
	  virtual operator Numeric*() { safety(); return NULL; };
	  in class WsvP

	* notes.txt
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	The last point above was missing in notes.txt. I have added it
	now. Sorry for that.  
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	* workspace.cc:
	- Added: wsv_group_names.push_back("Numeric");
	- Added:
 	  {
	  static WsvPointer<Numeric> p(&workspace.dummy);
	  wsv_data.push_back
	  (WsvRecord
	  ("dummy",
	  "This is just to test Numeric WSVs.",
	  Numeric_,
	  &p));
	  }

	* methods.cc:
	- Added:
	  md_data.push_back
	  ( MdRecord
	  ( NAME("NumericSet"),
	  DESCRIPTION("Sets a workspace variable of type Numeric to a value."),
	  OUTPUT(),
	  INPUT(),
	  GOUTPUT(Numeric_),
	  GINPUT(),
	  KEYWORDS("value"),
	  TYPES(num_)));

	* m_io.cc:
	- Added the implementation of NumericSet

2000-03-30  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0.0.5

	* ARTS has now the following methods:
        AllAbsExample
	VectorWriteToFile
	MatrixWriteToFile
	VectorWriteToNamedFile
	MatrixWriteToNamedFile
	VectorReadFromFile
	MatrixReadFromFile

	which all do the obvious. Parsing and executing of methods seems
	to work, but yet has to be tested for a wider variety of
	methods. Also, the executor already checks if all input workspace
	data is present, before it executes a method.

	* Added some more HowTos in file src/notes.txt
	
2000-03-29  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0.0.4
	* Now we can parse and execute specific and generic
  	methods. However, I want to re-structure the method lookup data
	(add explicit fields for generic I/O, so that a method can have
	both generic and specific I/O). So this commit is mainly to save
	the state of the work before I start with this complicated task.

2000-03-24  Stefan Buehler  <sbuehler@uni-bremen.de>

	* arts-0.0.3.
	* Arts can now parse specific (i.e., not generic) methods. There
	so far is only a single method, AllAbsExample, which sets the
	absorption parameters.

	
	* arts-0.0.2.
	* make_md_h.cc: Added.
	* math_funcs.h: Added.
	* math_funcs.cc: Added. 
	* absorption.cc: Added. 

2000-03-14  Stefan Buehler  <sbuehler@uni-bremen.de>

	* This file contains  SAB 14.03.2000.

	* arts-0.0.1.
	* .cvsignore files added everywhere.
	* Started this file, the Arts history. ALWAYS add a note to this
	file, no matter how small your change. Also, always update the
	running version number. Newest change log entries first!
	  
	You can very easily add an entry with emacs by typing either M-x
	add-change-log-entry or C-x 4 a.
	  
	Remark about version numbers: Arts has a 3 digit version number,
	like for example Arts 1.2.3. For user releases the third digit is
	zero.  The first two digits are set in configure.in. Update these
	only when you cut a user release. In that case you also have to
	set the third digit to zero.  The third digit is set in
	src/version.cc. Always update this, no matter how small your
	change!
