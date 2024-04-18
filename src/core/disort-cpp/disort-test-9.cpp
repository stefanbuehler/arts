#include <disort.h>

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "artstime/artstime.h"
#include "debug.h"
#include "matpack_data.h"

bool is_good(const auto& a, const auto& b) {
  if (a.shape() != b.shape()) {
    std::cerr << "!!!\n\nBad shapes\n\n!!!\n";
    return false;
  }

  return std::transform_reduce(
      a.elem_begin(),
      a.elem_end(),
      b.elem_begin(),
      true,
      [](bool first, bool second) { return first and second; },
      [](Numeric first, Numeric second) {
        if (first == 0.0 or second == 0.0) return true;
        const Numeric ratio = std::abs(first / second - 1);
        return ratio < 1e-6;
      });
}

Tensor3 compute_u(const disort::main_data& dis,
                  const Vector& taus,
                  const Vector& phis,
                  const bool nt_corr) {
  Tensor3 u(phis.size(), taus.size(), dis.quads());
  disort::u_data u_data;
  disort::ims_data ims_data;
  disort::tms_data tms_data;

  for (Index j = 0; j < taus.size(); j++) {
    for (Index i = 0; i < phis.size(); i++) {
      if (nt_corr) {
        dis.u_corr(u_data, ims_data, tms_data, taus[j], phis[i]);
      } else {
        dis.u(u_data, taus[j], phis[i]);
      }
      u(i, j, joker) = u_data.intensities;
    }
  }
  return u;
}

Matrix compute_u0(const disort::main_data& dis, const Vector& taus) {
  Matrix u0(taus.size(), dis.quads());
  disort::u0_data u0_data;

  for (Index j = 0; j < taus.size(); j++) {
    dis.u0(u0_data, taus[j]);
    u0[j] = u0_data.u0;
  }
  return u0;
}

std::tuple<Vector, Vector, Vector> compute_flux(const disort::main_data& dis,
                                                const Vector& taus) {
  Vector flux_up(taus.size()), flux_down_diffuse(taus.size()),
      flux_down_direct(taus.size());
  disort::flux_data flux_data;

  for (Index j = 0; j < taus.size(); j++) {
    auto [ds, dr] = dis.flux_down(flux_data, taus[j]);
    flux_up[j] = dis.flux_up(flux_data, taus[j]);
    flux_down_diffuse[j] = ds;
    flux_down_direct[j] = dr;
  }
  return {flux_up, flux_down_diffuse, flux_down_direct};
}

void compare(const std::string_view name,
             const disort::main_data& dis,
             const Vector& taus,
             const Vector& phis,
             const Tensor3& u,
             const Matrix& u0,
             const Vector& flux_down_diffuse,
             const Vector& flux_down_direct,
             const Vector& flux_up,
             const bool nt_corr) {
  const auto u_arts = compute_u(dis, taus, phis, nt_corr);
  const auto u0_arts = compute_u0(dis, taus);
  const auto [flux_up_arts, flux_down_diffuse_arts, flux_down_direct_arts] =
      compute_flux(dis, taus);

  ARTS_USER_ERROR_IF(not is_good(u_arts, u), "Failed u in test ", name);
  ARTS_USER_ERROR_IF(not is_good(u0_arts, u0), "Failed u0 in test ", name);
  ARTS_USER_ERROR_IF(
      not is_good(flux_up_arts, flux_up), "Failed flux_up in test ", name);
  ARTS_USER_ERROR_IF(not is_good(flux_down_diffuse_arts, flux_down_diffuse),
                     "Failed flux_down_diffuse in test ",
                     name);
  ARTS_USER_ERROR_IF(not is_good(flux_down_direct_arts, flux_down_direct),
                     "Failed flux_down_direct in test ",
                     name);
};

void flat_print(const auto& a, const auto& b) {
  ARTS_USER_ERROR_IF(a.shape() != b.shape(), "Failed shape comparison");
  const auto av = a.flat_view();
  const auto bv = b.flat_view();

  for (Index i = 0; i < a.size(); i++) {
    std::cout << i << ' ' << av[i] << ' ' << bv[i] << ' ' << (bv[i] / av[i] - 1)
              << '\n';
  }
}

void test_9a() try {
  const Vector tau_arr{1., 3., 6., 10., 15., 21.};
  const Vector omega_arr{0.65, 0.7, 0.75, 0.8, 0.85, 0.9};
  const Index NQuad = 8;
  Matrix Leg_coeffs_all(6, 9, 0);
  Leg_coeffs_all(joker, 0) = 1;

  const Numeric mu0 = 0;
  const Numeric I0 = 0;
  const Numeric phi0 = 0;
  const Matrix b_neg(1, 1, Constant::inv_pi);

  // Optional (unused)
  const Index NLeg = NQuad;
  const Index NFourier = NQuad;
  const Matrix b_pos(1, 1, 0);
  const Vector f_arr{};
  const std::vector<disort::BDRF> BDRF_Fourier_modes{};
  const Matrix s_poly_coeffs(0, 0);

  const disort::main_data dis(NQuad,
                              NLeg,
                              NFourier,
                              tau_arr,
                              omega_arr,
                              Leg_coeffs_all,
                              b_pos,
                              b_neg,
                              f_arr,
                              s_poly_coeffs,
                              BDRF_Fourier_modes,
                              mu0,
                              I0,
                              phi0);

  const Vector taus{
      0.1668089292920991,
      1.668089292920991,
      16.68089292920991,
  };
  const Vector phis{
      0.0,
      1.5705463267948965,
      3.141092653589793,
      4.71163898038469,
      6.282185307179586,
  };
  const Tensor3 u{Vector{
      0.09137897666466127,    0.07263540372561034,    0.05842681725462224,
      0.05100970716395051,    0.12627612222748036,    0.23618027723927698,
      0.27283034110386223,    0.2844749357990595,     0.023673688591422215,
      0.01958669669674322,    0.016093220605736435,   0.014192333905213038,
      0.02670416266658929,    0.036057703565695855,   0.0651045249990603,
      0.09108448827093873,    1.4741864156584059e-06, 1.3008127794181713e-06,
      1.1258085591905933e-06, 1.0187102800583721e-06, 1.5860981977035825e-06,
      1.845167072356589e-06,  2.339173634231932e-06,  3.051927560799844e-06,
      0.09137897666466127,    0.07263540372561034,    0.05842681725462224,
      0.05100970716395051,    0.12627612222748036,    0.23618027723927698,
      0.27283034110386223,    0.2844749357990595,     0.023673688591422215,
      0.01958669669674322,    0.016093220605736435,   0.014192333905213038,
      0.02670416266658929,    0.036057703565695855,   0.0651045249990603,
      0.09108448827093873,    1.4741864156584059e-06, 1.3008127794181713e-06,
      1.1258085591905933e-06, 1.0187102800583721e-06, 1.5860981977035825e-06,
      1.845167072356589e-06,  2.339173634231932e-06,  3.051927560799844e-06,
      0.09137897666466127,    0.07263540372561034,    0.05842681725462224,
      0.05100970716395051,    0.12627612222748036,    0.23618027723927698,
      0.27283034110386223,    0.2844749357990595,     0.023673688591422215,
      0.01958669669674322,    0.016093220605736435,   0.014192333905213038,
      0.02670416266658929,    0.036057703565695855,   0.0651045249990603,
      0.09108448827093873,    1.4741864156584059e-06, 1.3008127794181713e-06,
      1.1258085591905933e-06, 1.0187102800583721e-06, 1.5860981977035825e-06,
      1.845167072356589e-06,  2.339173634231932e-06,  3.051927560799844e-06,
      0.09137897666466127,    0.07263540372561034,    0.05842681725462224,
      0.05100970716395051,    0.12627612222748036,    0.23618027723927698,
      0.27283034110386223,    0.2844749357990595,     0.023673688591422215,
      0.01958669669674322,    0.016093220605736435,   0.014192333905213038,
      0.02670416266658929,    0.036057703565695855,   0.0651045249990603,
      0.09108448827093873,    1.4741864156584059e-06, 1.3008127794181713e-06,
      1.1258085591905933e-06, 1.0187102800583721e-06, 1.5860981977035825e-06,
      1.845167072356589e-06,  2.339173634231932e-06,  3.051927560799844e-06,
      0.09137897666466127,    0.07263540372561034,    0.05842681725462224,
      0.05100970716395051,    0.12627612222748036,    0.23618027723927698,
      0.27283034110386223,    0.2844749357990595,     0.023673688591422215,
      0.01958669669674322,    0.016093220605736435,   0.014192333905213038,
      0.02670416266658929,    0.036057703565695855,   0.0651045249990603,
      0.09108448827093873,    1.4741864156584059e-06, 1.3008127794181713e-06,
      1.1258085591905933e-06, 1.0187102800583721e-06, 1.5860981977035825e-06,
      1.845167072356589e-06,  2.339173634231932e-06,  3.051927560799844e-06,
  }
                      .reshape(5, 3, 8)};
  const Matrix u0{Vector{
      0.09137897666466127,    0.07263540372561034,    0.05842681725462224,
      0.05100970716395051,    0.12627612222748036,    0.23618027723927698,
      0.27283034110386223,    0.2844749357990595,     0.023673688591422215,
      0.01958669669674322,    0.016093220605736435,   0.014192333905213038,
      0.02670416266658929,    0.036057703565695855,   0.0651045249990603,
      0.09108448827093873,    1.4741864156584059e-06, 1.3008127794181713e-06,
      1.1258085591905933e-06, 1.0187102800583721e-06, 1.5860981977035825e-06,
      1.845167072356589e-06,  2.339173634231932e-06,  3.051927560799844e-06,
  }
                      .reshape(3, 8)};
  const Vector flux_down_diffuse{
      0.8330640093605841,
      0.20839933737998897,
      7.682414116949928e-06,
  };
  const Vector flux_down_direct{
      0,
      0,
      0,
  };
  const Vector flux_up{
      0.18811741915056832,
      0.05156242242913035,
      3.5726758048558163e-06,
  };

  //flat_print(u, compute_u(dis, taus, phis, false) );
  //  const auto [flux_up_, flux_down_diffuse_, flux_down_direct_] =  compute_flux(dis, taus);
  //  flat_print(flux_down_diffuse, flux_down_diffuse_);

  compare("test_9a",
          dis,
          taus,
          phis,
          u,
          u0,
          flux_down_diffuse,
          flux_down_direct,
          flux_up,
          false);
} catch (std::exception& e) {
  throw std::runtime_error(var_string("Error in test-9a:\n", e.what()));
}

void test_9b() try {
  const Vector tau_arr{1., 3., 6., 10., 15., 21.};
  const Vector omega_arr{0.65, 0.7, 0.75, 0.8, 0.85, 0.9};
  const Index NQuad = 8;
  const Matrix Leg_coeffs_all{
      Vector{1.00000000e+00, 6.69720000e-01, 3.12678000e-01, 9.62957143e-02,
             2.46833333e-02, 4.29545455e-03, 5.16153846e-04, 4.53333333e-05,
             2.94117647e-06, 1.00000000e+00, 6.69720000e-01, 3.12678000e-01,
             9.62957143e-02, 2.46833333e-02, 4.29545455e-03, 5.16153846e-04,
             4.53333333e-05, 2.94117647e-06, 1.00000000e+00, 6.69720000e-01,
             3.12678000e-01, 9.62957143e-02, 2.46833333e-02, 4.29545455e-03,
             5.16153846e-04, 4.53333333e-05, 2.94117647e-06, 1.00000000e+00,
             6.69720000e-01, 3.12678000e-01, 9.62957143e-02, 2.46833333e-02,
             4.29545455e-03, 5.16153846e-04, 4.53333333e-05, 2.94117647e-06,
             1.00000000e+00, 6.69720000e-01, 3.12678000e-01, 9.62957143e-02,
             2.46833333e-02, 4.29545455e-03, 5.16153846e-04, 4.53333333e-05,
             2.94117647e-06, 1.00000000e+00, 6.69720000e-01, 3.12678000e-01,
             9.62957143e-02, 2.46833333e-02, 4.29545455e-03, 5.16153846e-04,
             4.53333333e-05, 2.94117647e-06}
          .reshape(6, 9)};

  const Numeric mu0 = 0;
  const Numeric I0 = 0;
  const Numeric phi0 = 0;
  const Matrix b_neg(1, 1, Constant::inv_pi);

  // Optional (unused)
  const Index NLeg = NQuad;
  const Index NFourier = NQuad;
  const Matrix b_pos(1, 1, 0);
  const Vector f_arr{};
  const std::vector<disort::BDRF> BDRF_Fourier_modes{};
  const Matrix s_poly_coeffs(0, 0);

  const disort::main_data dis(NQuad,
                              NLeg,
                              NFourier,
                              tau_arr,
                              omega_arr,
                              Leg_coeffs_all,
                              b_pos,
                              b_neg,
                              f_arr,
                              s_poly_coeffs,
                              BDRF_Fourier_modes,
                              mu0,
                              I0,
                              phi0);

  const Vector taus{
      0.1668089292920991,
      1.668089292920991,
      16.68089292920991,
  };
  const Vector phis{
      0.0,
      1.5705463267948965,
      3.141092653589793,
      4.71163898038469,
      6.282185307179586,
  };
  const Tensor3 u{Vector{
      0.07640678608077112,   0.04546995255325092,    0.023359728563220578,
      0.013511928961435847,  0.12281350188567326,    0.24451933958414696,
      0.2840411497773857,    0.29597615515023,       0.024970618982491963,
      0.016010823546418012,  0.008986271079143033,   0.005694192900395393,
      0.03174347405096442,   0.05116061257258858,    0.09724790710381352,
      0.1352063895749706,    4.940151067789312e-05,  3.801797066873187e-05,
      2.649990745860616e-05, 1.9593158426335707e-05, 5.664068525963678e-05,
      7.296484917232546e-05, 0.00010187928999982998, 0.00013493611225217985,
      0.07640678608077112,   0.04546995255325092,    0.023359728563220578,
      0.013511928961435847,  0.12281350188567326,    0.24451933958414696,
      0.2840411497773857,    0.29597615515023,       0.024970618982491963,
      0.016010823546418012,  0.008986271079143033,   0.005694192900395393,
      0.03174347405096442,   0.05116061257258858,    0.09724790710381352,
      0.1352063895749706,    4.940151067789312e-05,  3.801797066873187e-05,
      2.649990745860616e-05, 1.9593158426335707e-05, 5.664068525963678e-05,
      7.296484917232546e-05, 0.00010187928999982998, 0.00013493611225217985,
      0.07640678608077112,   0.04546995255325092,    0.023359728563220578,
      0.013511928961435847,  0.12281350188567326,    0.24451933958414696,
      0.2840411497773857,    0.29597615515023,       0.024970618982491963,
      0.016010823546418012,  0.008986271079143033,   0.005694192900395393,
      0.03174347405096442,   0.05116061257258858,    0.09724790710381352,
      0.1352063895749706,    4.940151067789312e-05,  3.801797066873187e-05,
      2.649990745860616e-05, 1.9593158426335707e-05, 5.664068525963678e-05,
      7.296484917232546e-05, 0.00010187928999982998, 0.00013493611225217985,
      0.07640678608077112,   0.04546995255325092,    0.023359728563220578,
      0.013511928961435847,  0.12281350188567326,    0.24451933958414696,
      0.2840411497773857,    0.29597615515023,       0.024970618982491963,
      0.016010823546418012,  0.008986271079143033,   0.005694192900395393,
      0.03174347405096442,   0.05116061257258858,    0.09724790710381352,
      0.1352063895749706,    4.940151067789312e-05,  3.801797066873187e-05,
      2.649990745860616e-05, 1.9593158426335707e-05, 5.664068525963678e-05,
      7.296484917232546e-05, 0.00010187928999982998, 0.00013493611225217985,
      0.07640678608077112,   0.04546995255325092,    0.023359728563220578,
      0.013511928961435847,  0.12281350188567326,    0.24451933958414696,
      0.2840411497773857,    0.29597615515023,       0.024970618982491963,
      0.016010823546418012,  0.008986271079143033,   0.005694192900395393,
      0.03174347405096442,   0.05116061257258858,    0.09724790710381352,
      0.1352063895749706,    4.940151067789312e-05,  3.801797066873187e-05,
      2.649990745860616e-05, 1.9593158426335707e-05, 5.664068525963678e-05,
      7.296484917232546e-05, 0.00010187928999982998, 0.00013493611225217985,
  }
                      .reshape(5, 3, 8)};
  const Matrix u0{Vector{
      0.07640678608077112,   0.04546995255325092,    0.023359728563220578,
      0.013511928961435847,  0.12281350188567326,    0.24451933958414696,
      0.2840411497773857,    0.29597615515023,       0.024970618982491963,
      0.016010823546418012,  0.008986271079143033,   0.005694192900395393,
      0.03174347405096442,   0.05116061257258858,    0.09724790710381352,
      0.1352063895749706,    4.940151067789312e-05,  3.801797066873187e-05,
      2.649990745860616e-05, 1.9593158426335707e-05, 5.664068525963678e-05,
      7.296484917232546e-05, 0.00010187928999982998, 0.00013493611225217985,
  }
                      .reshape(3, 8)};
  const Vector flux_down_diffuse{
      0.8655241368418789,
      0.3079843298065784,
      0.0003306980663436464,
  };
  const Vector flux_down_direct{
      0,
      0,
      0,
  };
  const Vector flux_up{
      0.08234618478129163,
      0.03084559084302861,
      8.575337844869327e-05,
  };

  //flat_print(u, compute_u(dis, taus, phis, false) );
  //  const auto [flux_up_, flux_down_diffuse_, flux_down_direct_] =  compute_flux(dis, taus);
  //  flat_print(flux_down_diffuse, flux_down_diffuse_);

  compare("test_9b",
          dis,
          taus,
          phis,
          u,
          u0,
          flux_down_diffuse,
          flux_down_direct,
          flux_up,
          false);
} catch (std::exception& e) {
  throw std::runtime_error(var_string("Error in test-9b:\n", e.what()));
}

int main() try {
  std::cout << std::setprecision(16);
  test_9a();
  test_9b();
} catch (std::exception& e) {
  std::cerr << "Error in main:\n" << e.what() << '\n';
  return EXIT_FAILURE;
}
