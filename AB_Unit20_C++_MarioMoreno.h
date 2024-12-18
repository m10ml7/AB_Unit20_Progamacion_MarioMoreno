// AB_Unit20_C++_MarioMoreno.h
#ifndef GESTION_HOSPITAL_H
#define GESTION_HOSPITAL_H

#include "Paciente.h"
#include "Medico.h"
#include "CitaMedica.h"
#include "Servicios.h"
#include <vector>

class GestionHospital {
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
    GestionHospital();
    void menuPrincipal();
};

#endif // GESTION_HOSPITAL_H

