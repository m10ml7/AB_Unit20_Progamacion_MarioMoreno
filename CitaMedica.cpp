// CitaMedica.cpp
#include "CitaMedica.h"
#include <iostream>
using namespace std;

CitaMedica::CitaMedica(string id, string fechaHora, string especialidad, Medico* medico, Paciente* paciente, short int nivelUrgencia)
    : id(id), fechaHora(fechaHora), especialidad(especialidad), medico(medico), paciente(paciente), nivelUrgencia(nivelUrgencia) {
}

void CitaMedica::modificarCita() {
    cout << "Nueva fecha y hora: ";
    cin.ignore();
    getline(cin, fechaHora);
    cout << "Nuevo nivel de urgencia: ";
    cin >> nivelUrgencia;
}
