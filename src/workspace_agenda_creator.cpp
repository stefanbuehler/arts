#include "workspace_agenda_creator.h"

#include <auto_wsa_options.h>

#include <string>
#include <unordered_map>

SetWsv::SetWsv(std::string n) : name(std::move(n)) {
  if (auto ind = name.find('='); ind not_eq name.npos) {
    *this = SetWsv(name.substr(0, ind), name.substr(ind + 1));
  }
}

AgendaCreator& AgendaCreator::add(const std::string& name,
                                  std::vector<SetWsv>&& v) {
  std::vector<std::string> args{};
  std::unordered_map<std::string, std::string> kwargs{};

  for (auto& wsv : v) {
    if (wsv.wsv) {
      a.add(Method{named_input_prefix + wsv.name, wsv.wsv.value()});
      kwargs[wsv.name] = named_input_prefix + wsv.name;
    } else if (wsv.other) {
      kwargs[wsv.name] = wsv.other.value();
    } else {
      args.push_back(wsv.name);
    }
  }

  a.add(Method{name, args, kwargs});

  return *this;
}

AgendaCreator& AgendaCreator::ignore(const std::string& name) {
  a.add(Method{"Ignore", {name}, {}});

  return *this;
}

Agenda AgendaCreator::finalize(bool fix) && {
  Agenda ag{std::move(a)};
  ag.finalize(fix);
  return ag;
};

Agenda get_propagation_matrix_scattering_agenda(const std::string& option) {
  AgendaCreator agenda("propagation_matrix_scattering_agenda");

  using enum propagation_matrix_scattering_agendaPredefined;
  switch (to<propagation_matrix_scattering_agendaPredefined>(option)) {
    case AirSimple:
      agenda.add("propagation_matrix_scatteringInit");
      agenda.add("propagation_matrix_scatteringAirSimple");
  }

  return std::move(agenda).finalize(false);
}

Agenda get_propagation_matrix_scattering_spectral_agenda(
    const std::string& option) {
  AgendaCreator agenda("propagation_matrix_scattering_spectral_agenda");

  using enum propagation_matrix_scattering_spectral_agendaPredefined;
  switch (to<propagation_matrix_scattering_spectral_agendaPredefined>(option)) {
    case FromSpeciesTRO:
      agenda.add("propagation_matrix_scatteringSpectralInit");
      agenda.add(
          "propagation_matrix_scatteringAddSpectralScatteringSpeciesTRO");
  }

  return std::move(agenda).finalize(false);
}

Agenda get_propagation_matrix_agenda(const std::string& option) {
  AgendaCreator agenda("propagation_matrix_agenda");

  using enum propagation_matrix_agendaPredefined;
  switch (to<propagation_matrix_agendaPredefined>(option)) {
    case Empty: agenda.add("propagation_matrixInit");
  }

  return std::move(agenda).finalize(true);
}

Agenda get_spectral_radiance_observer_agenda(const std::string& option) {
  AgendaCreator agenda("spectral_radiance_observer_agenda");

  using enum spectral_radiance_observer_agendaPredefined;
  switch (to<spectral_radiance_observer_agendaPredefined>(option)) {
    case Emission:
      agenda.add("ray_path_observer_agendaExecute");
      agenda.add("spectral_radianceClearskyEmission");
      agenda.add("spectral_radiance_jacobianAddSensorJacobianPerturbations");
      break;
  }

  return std::move(agenda).finalize(false);
}

Agenda get_spectral_radiance_space_agenda(const std::string& option) {
  AgendaCreator agenda("spectral_radiance_space_agenda");

  using enum spectral_radiance_space_agendaPredefined;
  switch (to<spectral_radiance_space_agendaPredefined>(option)) {
    case UniformCosmicBackground:
      agenda.add("spectral_radianceUniformCosmicBackground");
      agenda.add("spectral_radiance_jacobianEmpty");
      break;
    case SunOrCosmicBackground:
      agenda.add("spectral_radianceSunsOrCosmicBackground");
      agenda.add("spectral_radiance_jacobianEmpty");
      break;
    case Transmission:
      agenda.add("spectral_radianceDefaultTransmission");
      break;
  }

  return std::move(agenda).finalize(true);
}

Agenda get_spectral_radiance_surface_agenda(const std::string& option) {
  AgendaCreator agenda("spectral_radiance_surface_agenda");

  using enum spectral_radiance_surface_agendaPredefined;
  switch (to<spectral_radiance_surface_agendaPredefined>(option)) {
    case Blackbody: agenda.add("spectral_radianceSurfaceBlackbody"); break;
    case Transmission:
      agenda.add("spectral_radianceDefaultTransmission");
      break;
  }

  return std::move(agenda).finalize(true);
}

Agenda get_ray_path_observer_agenda(const std::string& option) {
  AgendaCreator agenda("ray_path_observer_agenda");

  using enum ray_path_observer_agendaPredefined;
  switch (to<ray_path_observer_agendaPredefined>(option)) {
    case Geometric:
      agenda.add("ray_pathGeometric",
                 SetWsv{"pos", "spectral_radiance_observer_position"},
                 SetWsv{"los", "spectral_radiance_observer_line_of_sight"},
                 SetWsv{"as_observer", Index{1}});
      break;
  }

  return std::move(agenda).finalize(false);
}
