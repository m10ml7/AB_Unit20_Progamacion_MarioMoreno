// Servicios.cpp
#include "Servicios.h"
#include <iostream>
using namespace std;

Servicios::Servicios(string nombre, bool disponibilidad)
    : nombre(nombre), disponibilidad(disponibilidad) {
}

void Servicios::reportarServicios() {
    cout << "Reportando servicio: " << nombre << endl;
}