#include "Servicios.h"
#include <iostream>
#include <algorithm>

using namespace std;

Servicios::Servicios() {}

void Servicios::listarCitasPendientesPorEspecialidad() {
    // Filtrar citas pendientes
    vector<CitaMedica> citasPendientes;
    for (const auto& cita : citas) {
        if (cita.estado == "pendiente") {
            citasPendientes.push_back(cita);
        }
    }

    // Ordenar por especialidad
    sort(citasPendientes.begin(), citasPendientes.end(), [](const CitaMedica& a, const CitaMedica& b) {
        return a.especialidad < b.especialidad;
        });

    // Mostrar citas pendientes por especialidad
    cout << "Citas pendientes por especialidad (ordenadas A-Z):" << endl;
    for (const auto& cita : citasPendientes) {
        cout << "Fecha: " << cita.fechaHora << ", Paciente: " << cita.paciente
            << ", Medico: " << cita.medico << ", Especialidad: " << cita.especialidad << endl;
    }
}

void Servicios::listarPacientesAtendidosPorFechas(const string& fechaInicio, const string& fechaFin) {
    // Filtrar citas atendidas dentro del rango de fechas
    vector<CitaMedica> citasAtendidas;
    for (const auto& cita : citas) {
        if (cita.estado == "atendida" && cita.fechaHora >= fechaInicio && cita.fechaHora <= fechaFin) {
            citasAtendidas.push_back(cita);
        }
    }

    // Ordenar por fecha (más reciente a más antiguo)
    sort(citasAtendidas.begin(), citasAtendidas.end(), [](const CitaMedica& a, const CitaMedica& b) {
        return a.fechaHora > b.fechaHora;
        });

    // Mostrar pacientes atendidos
    cout << "Pacientes atendidos entre " << fechaInicio << " y " << fechaFin << " (ordenados de más reciente a más antiguo):" << endl;
    for (const auto& cita : citasAtendidas) {
        cout << "Fecha: " << cita.fechaHora << ", Paciente: " << cita.paciente
            << ", Medico: " << cita.medico << ", Especialidad: " << cita.especialidad << endl;
    }
}

   