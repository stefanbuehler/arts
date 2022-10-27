import pyarts
import numpy as np

f = np.linspace(1e9, 1500e9, 101)
x_h2o = 5e-3
x_o2 = 0.21

x = pyarts.arts.predef.get_h2o_mpm89(f, 1e4, 250, x_h2o)
y = pyarts.arts.predef.get_o2_mpm89(f, 1e4, 250, x_o2, x_h2o)

x_ref = [9.48319146e-11, 4.76300556e-08, 1.28130628e-07, 1.83165999e-07,
         3.05577078e-07, 4.68430871e-07, 6.71482453e-07, 9.18753325e-07,
         1.24077149e-06, 1.59470925e-06, 2.13933242e-06, 3.50981793e-06,
         7.93040979e-05, 6.60013141e-06, 4.55934360e-06, 4.75178594e-06,
         5.29777841e-06, 6.01630026e-06, 6.89325646e-06, 7.99107780e-06,
         9.60302018e-06, 1.55572718e-05, 2.76951318e-05, 1.70273030e-05,
         2.62201990e-05, 2.54807489e-04, 6.64777957e-05, 3.21491785e-05,
         3.48665877e-05, 7.91203382e-05, 6.33120325e-04, 7.39137119e-05,
         8.83082394e-05, 1.09754423e-04, 1.81280173e-04, 3.90845573e-04,
         1.45713660e-03, 2.18213587e-01, 2.29113371e-03, 5.74433456e-04,
         2.83945987e-04, 2.64546390e-04, 1.59201292e-04, 1.18503630e-04,
         1.15981297e-04, 1.08896402e-04, 1.23091344e-04, 1.63625316e-04,
         2.86452754e-04, 9.09932512e-04, 9.76414597e-02, 1.44623678e-03,
         3.82880218e-04, 2.04775852e-04, 1.44752034e-04, 1.18239052e-04,
         1.08630361e-04, 1.00742083e-04, 9.82816272e-05, 1.02905596e-04,
         1.43987897e-04, 1.02955730e-02, 1.66305707e-04, 1.87178103e-04,
         3.71630389e-04, 1.44872160e-03, 2.99938139e-02, 6.92514216e-04,
         2.65941468e-04, 1.72695358e-04, 1.38318650e-04, 1.22426890e-04,
         1.14225878e-04, 1.09825066e-04, 1.07537145e-04, 1.06530917e-04,
         1.06356712e-04, 1.06753080e-04, 1.07559042e-04, 1.08670732e-04,
         1.10018478e-04, 1.11553976e-04, 1.13242781e-04, 1.15059721e-04,
         1.16986001e-04, 1.19007321e-04, 1.21112616e-04, 1.23293197e-04,
         1.25542143e-04, 1.27853880e-04, 1.30223864e-04, 1.32648357e-04,
         1.35124253e-04, 1.37648949e-04, 1.40220251e-04, 1.42836289e-04,
         1.45495467e-04, 1.48196409e-04, 1.50937922e-04, 1.53718970e-04,
         1.56538645e-04, ]

y_ref = [2.39859370e-08, 3.19864150e-08, 7.10242618e-08, 3.64074184e-07,
         3.97336092e-04, 3.74998549e-07, 1.30869391e-07, 1.51577637e-07,
         3.28979444e-06, 8.52338539e-08, 4.15416318e-08, 2.97457459e-08,
         2.42584233e-08, 2.40595352e-08, 2.40595355e-08, 2.40595358e-08,
         2.40595361e-08, 2.40595363e-08, 2.40595364e-08, 2.40595366e-08,
         2.40595367e-08, 2.40595368e-08, 2.40595369e-08, 2.40595370e-08,
         7.71559806e-08, 9.64927274e-08, 4.97198909e-08, 1.14493471e-07,
         2.33877013e-06, 3.58318992e-07, 8.79314440e-08, 7.23575290e-08,
         3.97701410e-07, 2.61900021e-07, 5.25062241e-08, 3.08240117e-08,
         2.40595375e-08, 2.40595375e-08, 2.40595375e-08, 2.40595375e-08,
         2.40595375e-08, 2.40595375e-08, 2.40595375e-08, 2.40595376e-08,
         2.40595376e-08, 2.44401134e-08, 3.57643313e-08, 1.20267437e-07,
         3.98682196e-07, 8.11097480e-08, 1.42184795e-07, 9.88254096e-07,
         1.61169774e-06, 1.81752938e-07, 1.03150653e-07, 2.99816764e-07,
         5.40050648e-07, 7.12100213e-08, 3.80277046e-08, 2.78591487e-08,
         2.40595377e-08, 2.40595377e-08, 2.40595377e-08, 2.40595377e-08,
         2.40595377e-08, 2.40595377e-08, 2.40595377e-08, 2.40595377e-08,
         2.40595377e-08, 2.40595377e-08, 2.40595377e-08, 2.40595377e-08,
         2.40595377e-08, 2.40595377e-08, 2.40595377e-08, 2.40595377e-08,
         2.40595377e-08, 2.40595377e-08, 2.40595377e-08, 2.40595377e-08,
         2.40595377e-08, 2.40595377e-08, 2.40595377e-08, 2.40595377e-08,
         2.40595377e-08, 2.40595377e-08, 2.40595377e-08, 2.40595377e-08,
         2.40595377e-08, 2.40595377e-08, 2.40595377e-08, 2.40595377e-08,
         2.40595377e-08, 2.40595377e-08, 2.40595377e-08, 2.40595377e-08,
         2.40595377e-08, 2.40595377e-08, 2.40595378e-08, 2.40595378e-08,
         2.40595378e-08, ]

assert np.allclose(x, x_ref), "Error in H2O-MPM89"
assert np.allclose(y, y_ref), "Error in O2-MPM89"