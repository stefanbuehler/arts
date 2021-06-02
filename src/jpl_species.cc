#include <map>

#include "jpl_species.h"

#include "species_tags.h"

using JplMap = std::map<Index, const char * const>;

const JplMap catdir2arts {
  {18003, "H2O-161"},
  {18005, "H2O-161"},
  {20003, "H2O-181"},
  {19003, "H2O-171"},
  {19002, "H2O-162"},
  {21001, "H2O-182"},
  {20001, "H2O-262"},
  
  {46013, "CO2-628"},
  {45012, "CO2-627"},
  
  {48004, "O3-666"},
  {48005, "O3-666"},
  {48006, "O3-666"},
  {48007, "O3-666"},
  {48008, "O3-666"},
  {50004, "O3-668"},
  {50006, "O3-668"},
  {50003, "O3-686"},
  {50005, "O3-686"},
  {49002, "O3-667"},
  {49001, "O3-676"},
  
  {44004, "N2O-676"},
  {44009, "N2O-676"},
  {44012, "N2O-676"},
  {45007, "N2O-456"},
  {45008, "N2O-546"},
  {46007, "N2O-448"},
  
  {28001, "CO-26"},
  {29001, "CO-36"},
  {30001, "CO-28"},
  {29006, "CO-27"},
  
  {17003, "CH4-212"},
  
  {32001, "O2-66"},
  {32002, "O2-66"},
  {34001, "O2-68"},
  {33002, "O2-67"},
  
  {30008, "NO-46"},
  
  {64002, "SO2-626"},
  {64005, "SO2-626"},
  {66002, "SO2-646"},
  {65001, "SO2-636"},
  {66004, "SO2-628"},
  
  {46006, "NO2-646"},
  
  {17002, "NH3-4111"},
  {17004, "NH3-4111"},
  {18002, "NH3-5111"},
  {18004, "NH3-4112"},
  
  {63001, "HNO3-146"},
  {63002, "HNO3-146"},
  {63003, "HNO3-146"},
  {63004, "HNO3-146"},
  {63005, "HNO3-146"},
  {63006, "HNO3-146"},
  
  {17001, "OH-61"},
  {19001, "OH-81"},
  {18001, "OH-62"},
  
  {20002, "HF-19"},
  {21002, "HF-29"},
  
  {36001, "HCl-15"},
  {38001, "HCl-17"},
  {37001, "HCl-25"},
  {39004, "HCl-27"},
  
  {80001, "HBr-19"},
  {82001, "HBr-11"},
  
  {51002, "ClO-56"},
  {51003, "ClO-56"},
  {53002, "ClO-76"},
  {53006, "ClO-76"},
  
  {60001, "OCS-622"},
  {62001, "OCS-624"},
  {61001, "OCS-632"},
  {62002, "OCS-822"},
  
  {30004, "H2CO-126"},
  {31002, "H2CO-136"},
  {32004, "H2CO-128"},
  
  {31003, "HDCO-26"},
  
  {32006, "D2CO-26"},
  
  {52006, "HOCl-165"},
  {54005, "HOCl-167"},
  
  {27001, "HCN-124"},
  {27003, "HCN-124"},
  {28002, "HCN-134"},
  {28003, "HCN-125"},
  {28004, "HCN-224"},
  
  {50007, "CH3Cl-215"},
  {52009, "CH3Cl-217"},
  
  {34004, "H2O2-1661"},
  
  {34003, "PH3-1111"},
  
  {66001, "COF2-269"},
  
  {34002, "H2S-121"},
  {35001, "H2S-122"},
  
  {46005, "HCOOH-126"},
  {47002, "HCOOH-136"},
  
  {47003, "DCOOH-266"},
  
  {47004, "HCOOD-266"},
  
  {33001, "HO2-166"},
  
  {16001, "O-6"},
  
  {97002, "ClONO2-5646"},
  {99001, "ClONO2-7646"},
  
  {30011, "NO+-46"},
  
  {67001, "OClO-656"},
  {69001, "OClO-676"},
  
  {95001, "BrO-96"},
  {97001, "BrO-16"},
  
  {98001, "H2SO4-126"},
  
  {102001, "Cl2O2-565"},
  {104001, "Cl2O2-765"},
  
  {96001, "HOBr-169"},
  {98002, "HOBr-161"},
  
  {32003, "CH3OH-2161"},
  
  {41001, "CH3CN-2124"},
  {41010, "CH3CN-2124"},
  {42006, "CH3CN-3124"},
  {42007, "CH3CN-2134"},
  {42001, "CH3CN-2125"},
  {42008, "CH2DCN-224"},
  
  {51001, "HC3N-12224"},
  {52001, "HC3N-12234"},
  {52002, "HC3N-12324"},
  {52003, "HC3N-13224"},
  {52004, "HC3N-12225"},
  {52005, "HC3N-22224"},
  
  {44001, "CS-22"},
  {46001, "CS-24"},
  {45001, "CS-32"},
  
  {27002, "HNC-142"},
  {27003, "HNC-142"},
  {28005, "HNC-143"},
  {28006, "HNC-152"},
  {28007, "HNC-242"},
  
  {48001, "SO-26"},
  {48002, "SO-26"},
  {50001, "SO-46"},
  {50002, "SO-28"},
  
  {44013, "C3H8-21"},
  
  {3001, "H2-12"},
};

using ArtsMap = std::map<Index, SpeciesTag>;

ArtsMap to_species_map(const JplMap& jplmap) {
  ArtsMap out;
  for (auto& x: jplmap) {
    out[x.first] = SpeciesTag(x.second);
  }
  return out;
}

QuantumIdentifier Jpl::id_from_lookup(Index tag) {
  static ArtsMap data = to_species_map(catdir2arts);
  auto ptr = data.find(tag);
  ARTS_USER_ERROR_IF(ptr == data.cend(), "Cannot find the tag: ", tag, " in ARTS")
  return QuantumIdentifier(ptr -> second.Isotopologue(), Quantum::IdentifierType::Transition);
}
