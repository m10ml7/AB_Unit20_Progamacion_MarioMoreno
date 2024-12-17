// CitaMedica.h
#ifndef CITAMEDICA_H
#define CITAMEDICA_H
#include "Medico.h"
#include "Paciente.h"
#include <string>
#include <vector>

class CitaMedica {
public:
    std::string id;
    std::string fechaHora;
    std::string especialidad;
    Medico* medico;
    Paciente* paciente;
    short int nivelUrgencia;

    CitaMedica(std::string id, std::string fechaHora, std::string especialidad, Medico* medico, Paciente* paciente, short int nivelUrgencia);
    void modificarCita();
};

#endif // CITAMEDICA_