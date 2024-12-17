// Medico.h
#ifndef MEDICO_H
#define MEDICO_H
#include <string>
#include <vector>
#include "Paciente.h"

class Medico {
public:
    std::string nombre;
    std::string apellidos;
    std::string dni;
    std::string especialidad;
    bool disponible;

    Medico(std::string nombre, std::string apellidos, std::string dni, bool disponible);
    void altaMedico();
    void bajaMedico();
    void modificarDatos();
};

#endif // MEDICO_H