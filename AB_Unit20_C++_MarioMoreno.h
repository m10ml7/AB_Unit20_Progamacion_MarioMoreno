// AB_Unit20_C++_MarioMoreno.h
#ifndef HOSPITAL_CONTROLLER_H
#define HOSPITAL_CONTROLLER_H

#include "Paciente.h"
#include "Medico.h"
#include "CitaMedica.h"
#include "Servicios.h"
#include <vector>

class HospitalController {
private:
    std::vector<Paciente> pacientes;
    std::vector<Medico> medicos;
    std::vector<CitaMedica> citas;
    Servicios servicios;

    void menuPacientes();
    void menuMedicos();
    void menuCitas();
    void menuServicios();

public:
    HospitalController();
    void menuPrincipal();
};

#endif // HOSPITAL_CONTROLLER_H