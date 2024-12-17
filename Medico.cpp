// Medico.cpp
#include "Medico.h"
#include <iostream>
using namespace std;

Medico::Medico(string nombre, string apellidos, string dni, bool disponible)
    : nombre(nombre), apellidos(apellidos), dni(dni), disponible(disponible) {
}

void Medico::altaMedico() {
    disponible = true;
    cout << "El medico " << nombre << " ha sido dado de alta y ahora esta disponible.\n";
}

void Medico::bajaMedico() {
    disponible = false;
    cout << "El medico " << nombre << " ha sido dado de baja y no esta disponible.\n";
}

void Medico::modificarDatos() {
    cout << "Nuevo nombre: ";
    cin >> nombre;
    cout << "Nuevos apellidos: ";
    cin >> apellidos;
    cout << "Nuevo DNI: ";
    cin >> dni;
    cout << "Disponible (1=Si, 0=No): ";
    cin >> disponible;
}