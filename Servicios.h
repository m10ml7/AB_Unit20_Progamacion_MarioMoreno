// Servicios.h
#ifndef SERVICIOS_H
#define SERVICIOS_H
#include <string>
#include <vector>
#include "CitaMedica.h"

class Servicios {
public:
    std::string nombre;
    bool disponibilidad;
    std::vector<CitaMedica> citas;

    Servicios(std::string nombre, bool disponibilidad);
    void reportarServicios();
};

#endif // SERVICIOS_H
