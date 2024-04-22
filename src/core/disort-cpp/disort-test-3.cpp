#include <disort-test.h>

void test_3a() try {
  const Vector tau_arr{1};
  const Vector omega_arr{1 - 1e-6};
  const Index NQuad = 16;
  Matrix Leg_coeffs_all(1, 32, 1);
  for (Index i = 1; i < 32; i++) {
    Leg_coeffs_all(0, i) = std::pow(0.75, i);
  }

  const Numeric mu0 = 1;
  const Numeric I0 = Constant::pi / mu0;
  const Numeric phi0 = 0;

  // Optional (unused)
  const Index NLeg = NQuad;
  const Index NFourier = NQuad;
  const Matrix b_pos(1, 1, 0);
  const Matrix b_neg(1, 1, 0);
  const Vector f_arr{Leg_coeffs_all(0, NQuad)};
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

  disort::u_data u_data;
  disort::ims_data ims_data;
  disort::tms_data tms_data;

  const Vector taus{
      0.007943282347242814,
      0.07943282347242814,
      0.7943282347242815,
  };
  const Vector phis{
      0.0,
      1.5705463267948965,
      3.141092653589793,
      4.71163898038469,
      6.282185307179586,
  };
  const Tensor3 u{Vector{
      0.13455469626877659,   0.15340075232471495,   0.1509247458325332,
      0.1192777388484733,    0.08455683928844487,   0.06053018175549202,
      0.046680879871980656,  0.04013148105205446,   0.039718122593107016,
      0.00876268935345695,   0.0038664482588762782, 0.0027104886997448554,
      0.0028376514563899615, 0.004313880188683403,  0.009741179107792278,
      0.031474615220649996,  0.155087085539672,     0.1652523635566904,
      0.1541354408570559,    0.1170106542521147,    0.08086801679997874,
      0.05707383314109061,   0.0437019901614933,    0.03744016087506008,
      0.14144254083449917,   0.07327403248180661,   0.038190429516853454,
      0.027411152028971854,  0.028358332500205828,  0.042366393192414,
      0.09386755423530906,   0.2979510271284589,    0.19473491888230593,
      0.14288200608498655,   0.07297270850891245,   0.036007758720096164,
      0.01961643423080539,   0.01232647421256477,   0.008966656369568669,
      0.0075055324470330136, 0.20735043469598155,   0.22450232194000988,
      0.2294231072984284,    0.22397116554710758,   0.2440869029826386,
      0.3379254133593642,    0.6469979911184675,    1.7398905494958883,
      0.13455469626877659,   0.15340075232471495,   0.1509247458325332,
      0.1192777388484733,    0.08455683928844487,   0.06053018175549202,
      0.046680879871980656,  0.04013148105205446,   0.039718122593107016,
      0.00876268935345695,   0.0038664482588762782, 0.0027104886997448554,
      0.0028376514563899615, 0.004313880188683403,  0.009741179107792278,
      0.031474615220649996,  0.155087085539672,     0.1652523635566904,
      0.1541354408570559,    0.1170106542521147,    0.08086801679997874,
      0.05707383314109061,   0.0437019901614933,    0.03744016087506008,
      0.14144254083449917,   0.07327403248180661,   0.038190429516853454,
      0.027411152028971854,  0.028358332500205828,  0.042366393192414,
      0.09386755423530906,   0.2979510271284589,    0.19473491888230593,
      0.14288200608498655,   0.07297270850891245,   0.036007758720096164,
      0.01961643423080539,   0.01232647421256477,   0.008966656369568669,
      0.0075055324470330136, 0.20735043469598155,   0.22450232194000988,
      0.2294231072984284,    0.22397116554710758,   0.2440869029826386,
      0.3379254133593642,    0.6469979911184675,    1.7398905494958883,
      0.13455469626877659,   0.15340075232471495,   0.1509247458325332,
      0.1192777388484733,    0.08455683928844487,   0.06053018175549202,
      0.046680879871980656,  0.04013148105205446,   0.039718122593107016,
      0.00876268935345695,   0.0038664482588762782, 0.0027104886997448554,
      0.0028376514563899615, 0.004313880188683403,  0.009741179107792278,
      0.031474615220649996,  0.155087085539672,     0.1652523635566904,
      0.1541354408570559,    0.1170106542521147,    0.08086801679997874,
      0.05707383314109061,   0.0437019901614933,    0.03744016087506008,
      0.14144254083449917,   0.07327403248180661,   0.038190429516853454,
      0.027411152028971854,  0.028358332500205828,  0.042366393192414,
      0.09386755423530906,   0.2979510271284589,    0.19473491888230593,
      0.14288200608498655,   0.07297270850891245,   0.036007758720096164,
      0.01961643423080539,   0.01232647421256477,   0.008966656369568669,
      0.0075055324470330136, 0.20735043469598155,   0.22450232194000988,
      0.2294231072984284,    0.22397116554710758,   0.2440869029826386,
      0.3379254133593642,    0.6469979911184675,    1.7398905494958883,
      0.13455469626877659,   0.15340075232471495,   0.1509247458325332,
      0.1192777388484733,    0.08455683928844487,   0.06053018175549202,
      0.046680879871980656,  0.04013148105205446,   0.039718122593107016,
      0.00876268935345695,   0.0038664482588762782, 0.0027104886997448554,
      0.0028376514563899615, 0.004313880188683403,  0.009741179107792278,
      0.031474615220649996,  0.155087085539672,     0.1652523635566904,
      0.1541354408570559,    0.1170106542521147,    0.08086801679997874,
      0.05707383314109061,   0.0437019901614933,    0.03744016087506008,
      0.14144254083449917,   0.07327403248180661,   0.038190429516853454,
      0.027411152028971854,  0.028358332500205828,  0.042366393192414,
      0.09386755423530906,   0.2979510271284589,    0.19473491888230593,
      0.14288200608498655,   0.07297270850891245,   0.036007758720096164,
      0.01961643423080539,   0.01232647421256477,   0.008966656369568669,
      0.0075055324470330136, 0.20735043469598155,   0.22450232194000988,
      0.2294231072984284,    0.22397116554710758,   0.2440869029826386,
      0.3379254133593642,    0.6469979911184675,    1.7398905494958883,
      0.13455469626877659,   0.15340075232471495,   0.1509247458325332,
      0.1192777388484733,    0.08455683928844487,   0.06053018175549202,
      0.046680879871980656,  0.04013148105205446,   0.039718122593107016,
      0.00876268935345695,   0.0038664482588762782, 0.0027104886997448554,
      0.0028376514563899615, 0.004313880188683403,  0.009741179107792278,
      0.031474615220649996,  0.155087085539672,     0.1652523635566904,
      0.1541354408570559,    0.1170106542521147,    0.08086801679997874,
      0.05707383314109061,   0.0437019901614933,    0.03744016087506008,
      0.14144254083449917,   0.07327403248180661,   0.038190429516853454,
      0.027411152028971854,  0.028358332500205828,  0.042366393192414,
      0.09386755423530906,   0.2979510271284589,    0.19473491888230593,
      0.14288200608498655,   0.07297270850891245,   0.036007758720096164,
      0.01961643423080539,   0.01232647421256477,   0.008966656369568669,
      0.0075055324470330136, 0.20735043469598155,   0.22450232194000988,
      0.2294231072984284,    0.22397116554710758,   0.2440869029826386,
      0.3379254133593642,    0.6469979911184675,    1.7398905494958883,
  }
                      .reshape(5, 3, 16)};
  const Matrix u0{Vector{
      0.13243047456988777,   0.15330499515714974,  0.15200722791048482,
      0.11828852034249983,   0.08504258414523708,  0.0605659593383779,
      0.04594365761225005,   0.0411366070703416,   0.03907831997269459,
      0.008795058260298692,  0.003929322733625589, 0.0026626922490130475,
      0.00286624765448012,   0.004366846168477721, 0.009470146700949101,
      0.031637912515872106,  0.15310800483786965,  0.16516315161480152,
      0.15514125910952925,   0.11609793738066886,  0.08131329414592806,
      0.05710648349218884,   0.04303104235206085,  0.03835366306589945,
      0.1396278334583453,    0.07349884809497273,  0.03871473274777007,
      0.026987811444629674,  0.028618507140303062, 0.04285435918539161,
      0.09135191022740383,   0.29947328780070537,  0.19375973240859637,
      0.1428428840512037,    0.07329976745170096,  0.035770602644904385,
      0.019717692746411507,  0.012333349809154055, 0.00883132681263714,
      0.0076859604779390715, 0.20643699459077375,  0.22472021671494835,
      0.23049099572615553,   0.222651550785061,    0.2451096338523472,
      0.34007938513763253,   0.6350562640253886,   1.7474337247112006,
  }
                      .reshape(3, 16)};
  const Vector flux_down_diffuse{
      0.02429728050846811,
      0.23220927219320694,
      1.5502291075062795,
  };
  const Vector flux_down_direct{
      3.1167369447694853,
      2.901700842189926,
      1.419637633150657,
  };
  const Vector flux_up{
      0.2468151608072521,
      0.23969132740450858,
      0.07565090375938323,
  };

  //    flat_print(u, compute_u(dis, taus, phis, true) );
  //  const auto [flux_up_, flux_down_diffuse_, flux_down_direct_] =  compute_flux(dis, taus);
  //  flat_print(flux_down_diffuse, flux_down_diffuse_);

  compare("test_3a",
          dis,
          taus,
          phis,
          u,
          u0,
          flux_down_diffuse,
          flux_down_direct,
          flux_up,
          true);
} catch (std::exception& e) {
  throw std::runtime_error(var_string("Error in test-3a:\n", e.what()));
}

void test_3b() try {
  const Vector tau_arr{8};
  const Vector omega_arr{1 - 1e-6};
  const Index NQuad = 16;
  Matrix Leg_coeffs_all(1, 32, 1);
  for (Index i = 1; i < 32; i++) {
    Leg_coeffs_all(0, i) = std::pow(0.75, i);
  }

  const Numeric mu0 = 1;
  const Numeric I0 = Constant::pi / mu0;
  const Numeric phi0 = 0;

  // Optional (unused)
  const Index NLeg = NQuad;
  const Index NFourier = NQuad;
  const Matrix b_pos(1, 1, 0);
  const Matrix b_neg(1, 1, 0);
  const Vector f_arr{Leg_coeffs_all(0, NQuad)};
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

  disort::u_data u_data;
  disort::ims_data ims_data;
  disort::tms_data tms_data;

  const Vector taus{
      0.06354625877794251,
      0.6354625877794251,
      6.354625877794252,
  };
  const Vector phis{
      0.0,
      1.5705463267948965,
      3.141092653589793,
      4.71163898038469,
      6.282185307179586,
  };
  const Tensor3 u{Vector{
      0.34985261479707475,  0.4092492193484002,  0.47355139159111,
      0.5163906187994899,   0.5308960108883128,  0.5240923177142547,
      0.5085698067346742,   0.49598211935404385, 0.2985427829544931,
      0.1252230740377075,   0.05400548465549751, 0.03162739571172639,
      0.027555912508999626, 0.03693969291042282, 0.07777511152729144,
      0.2429886994472791,   0.5139684146725895,  0.5363923103588818,
      0.5588352168056376,   0.5662666895353798,  0.5545160206827432,
      0.5302241920281526,   0.5043017451382026,  0.4865100955502514,
      0.5002431210705266,   0.46504475756562946, 0.38177333763250865,
      0.29654678642810456,  0.2669199362215482,  0.32571123523771395,
      0.5912483613705791,   1.5902107446381004,  0.3897780748023898,
      0.35894605580647426,  0.30643740821838794, 0.23901386967151741,
      0.17471096333382868,  0.12813425081848256, 0.10017592381682253,
      0.08653877644783468,  0.40454436561914714, 0.4345854738860353,
      0.4833560179078944,   0.5435676168386174,  0.6083692466510299,
      0.6763928387563797,   0.7555023536402925,  0.8582900668989706,
      0.34985261479707475,  0.4092492193484002,  0.47355139159111,
      0.5163906187994899,   0.5308960108883128,  0.5240923177142547,
      0.5085698067346742,   0.49598211935404385, 0.2985427829544931,
      0.1252230740377075,   0.05400548465549751, 0.03162739571172639,
      0.027555912508999626, 0.03693969291042282, 0.07777511152729144,
      0.2429886994472791,   0.5139684146725895,  0.5363923103588818,
      0.5588352168056376,   0.5662666895353798,  0.5545160206827432,
      0.5302241920281526,   0.5043017451382026,  0.4865100955502514,
      0.5002431210705266,   0.46504475756562946, 0.38177333763250865,
      0.29654678642810456,  0.2669199362215482,  0.32571123523771395,
      0.5912483613705791,   1.5902107446381004,  0.3897780748023898,
      0.35894605580647426,  0.30643740821838794, 0.23901386967151741,
      0.17471096333382868,  0.12813425081848256, 0.10017592381682253,
      0.08653877644783468,  0.40454436561914714, 0.4345854738860353,
      0.4833560179078944,   0.5435676168386174,  0.6083692466510299,
      0.6763928387563797,   0.7555023536402925,  0.8582900668989706,
      0.34985261479707475,  0.4092492193484002,  0.47355139159111,
      0.5163906187994899,   0.5308960108883128,  0.5240923177142547,
      0.5085698067346742,   0.49598211935404385, 0.2985427829544931,
      0.1252230740377075,   0.05400548465549751, 0.03162739571172639,
      0.027555912508999626, 0.03693969291042282, 0.07777511152729144,
      0.2429886994472791,   0.5139684146725895,  0.5363923103588818,
      0.5588352168056376,   0.5662666895353798,  0.5545160206827432,
      0.5302241920281526,   0.5043017451382026,  0.4865100955502514,
      0.5002431210705266,   0.46504475756562946, 0.38177333763250865,
      0.29654678642810456,  0.2669199362215482,  0.32571123523771395,
      0.5912483613705791,   1.5902107446381004,  0.3897780748023898,
      0.35894605580647426,  0.30643740821838794, 0.23901386967151741,
      0.17471096333382868,  0.12813425081848256, 0.10017592381682253,
      0.08653877644783468,  0.40454436561914714, 0.4345854738860353,
      0.4833560179078944,   0.5435676168386174,  0.6083692466510299,
      0.6763928387563797,   0.7555023536402925,  0.8582900668989706,
      0.34985261479707475,  0.4092492193484002,  0.47355139159111,
      0.5163906187994899,   0.5308960108883128,  0.5240923177142547,
      0.5085698067346742,   0.49598211935404385, 0.2985427829544931,
      0.1252230740377075,   0.05400548465549751, 0.03162739571172639,
      0.027555912508999626, 0.03693969291042282, 0.07777511152729144,
      0.2429886994472791,   0.5139684146725895,  0.5363923103588818,
      0.5588352168056376,   0.5662666895353798,  0.5545160206827432,
      0.5302241920281526,   0.5043017451382026,  0.4865100955502514,
      0.5002431210705266,   0.46504475756562946, 0.38177333763250865,
      0.29654678642810456,  0.2669199362215482,  0.32571123523771395,
      0.5912483613705791,   1.5902107446381004,  0.3897780748023898,
      0.35894605580647426,  0.30643740821838794, 0.23901386967151741,
      0.17471096333382868,  0.12813425081848256, 0.10017592381682253,
      0.08653877644783468,  0.40454436561914714, 0.4345854738860353,
      0.4833560179078944,   0.5435676168386174,  0.6083692466510299,
      0.6763928387563797,   0.7555023536402925,  0.8582900668989706,
      0.34985261479707475,  0.4092492193484002,  0.47355139159111,
      0.5163906187994899,   0.5308960108883128,  0.5240923177142547,
      0.5085698067346742,   0.49598211935404385, 0.2985427829544931,
      0.1252230740377075,   0.05400548465549751, 0.03162739571172639,
      0.027555912508999626, 0.03693969291042282, 0.07777511152729144,
      0.2429886994472791,   0.5139684146725895,  0.5363923103588818,
      0.5588352168056376,   0.5662666895353798,  0.5545160206827432,
      0.5302241920281526,   0.5043017451382026,  0.4865100955502514,
      0.5002431210705266,   0.46504475756562946, 0.38177333763250865,
      0.29654678642810456,  0.2669199362215482,  0.32571123523771395,
      0.5912483613705791,   1.5902107446381004,  0.3897780748023898,
      0.35894605580647426,  0.30643740821838794, 0.23901386967151741,
      0.17471096333382868,  0.12813425081848256, 0.10017592381682253,
      0.08653877644783468,  0.40454436561914714, 0.4345854738860353,
      0.4833560179078944,   0.5435676168386174,  0.6083692466510299,
      0.6763928387563797,   0.7555023536402925,  0.8582900668989706,
  }
                      .reshape(5, 3, 16)};
  const Matrix u0{Vector{
      0.3478421623694593,   0.40915858858772125,  0.4745820450780542,
      0.5154216390728968,   0.5313909965585761,   0.5241300818528298,
      0.5077719275275838,   0.4970850696297733,   0.29674485709003356,
      0.12541756087565273,  0.054442042337236804, 0.03127949189996618,
      0.027768465842765898, 0.03733724208556767,  0.07572898380565064,
      0.24422565649072475,  0.512827106029526,    0.5363408604120592,
      0.5594203058714098,   0.5657166118903125,   0.5547970178426671,
      0.5302456302555124,   0.5038487991777651,   0.4871362264256957,
      0.49917421303910003,  0.4652999110137037,   0.3829507357914532,
      0.29518904349596925,  0.2679249957895643,   0.3277771238190773,
      0.5799752832280145,   1.5972643792467087,   0.3897741074922043,
      0.3589458769609929,   0.30643944163430614,  0.23901196448446235,
      0.1747119278960189,   0.12813432361248284,  0.10017439970718266,
      0.0865408719251152,   0.4045406368269854,   0.43458625176571664,
      0.48336091559119687,  0.5435595441653663,   0.6083797294823216,
      0.6764266853780864,   0.755205913248498,    0.8585452951991266,
  }
                      .reshape(3, 16)};
  const Vector flux_down_diffuse{
      0.21038339121422697,
      1.56259707806109,
      2.05990482272991,
  };
  const Vector flux_down_direct{
      2.948167017021337,
      1.6640714797716942,
      0.0054622417752412155,
  };
  const Vector flux_up{
      1.6078871678716244,
      1.6760094708169004,
      0.5147506317968269,
  };

  //    flat_print(u, compute_u(dis, taus, phis, true) );
  //  const auto [flux_up_, flux_down_diffuse_, flux_down_direct_] =  compute_flux(dis, taus);
  //  flat_print(flux_down_diffuse, flux_down_diffuse_);

  compare("test_3b",
          dis,
          taus,
          phis,
          u,
          u0,
          flux_down_diffuse,
          flux_down_direct,
          flux_up,
          true);
} catch (std::exception& e) {
  throw std::runtime_error(var_string("Error in test-3b:\n", e.what()));
}

int main() try {
  std::cout << std::setprecision(16);
  test_3a();
  test_3b();
} catch (std::exception& e) {
  std::cerr << "Error in main:\n" << e.what() << '\n';
  return EXIT_FAILURE;
}
