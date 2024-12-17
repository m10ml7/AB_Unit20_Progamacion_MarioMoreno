// Paciente.cpp
#include "Paciente.h"
#include <iostream>
using namespace std;

Paciente::Paciente(string nombre, string apellidos, string dni, string fechaIngreso, string enfermedad)
    : nombre(nombre), apellidos(apellidos), dni(dni), fechaIngreso(fechaIngreso), enfermedad(enfermedad) {
}

void Paciente::altaPaciente() {
    cout << "El paciente " << nombre << " ha recibido el alta medica.\n";
}

void Paciente::bajaPaciente() {
    cout << "El paciente " << nombre << " ha sido dado de baja.\n";
}

void Paciente::modificarDatos() {
    cout << "Nuevo nombre: ";
    cin >> nombre;
    cout << "Nuevos apellidos: ";
    cin >> apellidos;
    cout << "Nuevo DNI: ";
    cin >> dni;
    cout << "Nueva enfermedad: ";
    cin.ignore();
    getline(cin, enfermedad);
}

void Paciente::registrarHistorial(string registro) {
    historialClinico.push_back(registro);
}

void Paciente::mostrarHistorial() {
    cout << "Historial clinico de " << nombre << ":\n";
    for (const auto& registro : historialClinico) {
        cout << "- " << registro << "\n";
    }
}
