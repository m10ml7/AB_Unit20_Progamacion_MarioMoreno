#include "CitaMedica.h"
#include <iostream>

using namespace std;

CitaMedica::CitaMedica(string id, string fechaHora, string especialidad,
    Medico* medico, Paciente* paciente, short int nivelUrgencia, string estado)
    : id(id), fechaHora(fechaHora), especialidad(especialidad),
    medico(medico), paciente(paciente), nivelUrgencia(nivelUrgencia), estado(estado) {
}

void CitaMedica::modificarCita() {
    cout << "Nueva fecha y hora: ";
    cin.ignore();
    getline(cin, fechaHora);
    cout << "Nuevo nivel de urgencia: ";
    cin >> nivelUrgencia;
    cin.ignore();  // Limpiar buffer
    cout << "Nuevo estado: ";
    getline(cin, estado);
}

