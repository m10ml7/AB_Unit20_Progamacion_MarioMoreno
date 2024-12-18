#ifndef SERVICIOS_H
#define SERVICIOS_H

#include <vector>
#include "CitaMedica.h"

class Servicios {
public:
    std::vector<CitaMedica> citas; // Lista de citas médicas

    Servicios(); // Constructor por defecto

    void listarCitasPendientesPorEspecialidad();
    void listarPacientesAtendidosPorFechas(const std::string& fechaInicio, const std::string& fechaFin);
};

#endif // SERVICIOS_H
