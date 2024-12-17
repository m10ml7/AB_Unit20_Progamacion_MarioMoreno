// AB_Unit20_C++_MarioMoreno.cpp
#include "AB_Unit20_C++_MarioMoreno.h"
#include <iostream>

using namespace std;

HospitalController::HospitalController() : servicios("Hospital Central", true) {}

void HospitalController::menuPacientes() {
    short int opcion;
    do {
        cout << "--- Menu Pacientes ---\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Modificar datos del paciente\n";
        cout << "3. Dar de alta medica\n";
        cout << "4. Dar de baja medica\n";
        cout << "5. Registrar historial clinico\n";
        cout << "6. Mostrar historial clinico\n";
        cout << "7. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre, apellidos, dni, fechaIngreso, enfermedad;
            cout << "Ingrese nombre: ";
            cin >> nombre;
            cout << "Ingrese apellidos: ";
            cin >> apellidos;
            cout << "Ingrese DNI: ";
            cin >> dni;
            cout << "Ingrese fecha de ingreso: ";
            cin >> fechaIngreso;
            cout << "Ingrese enfermedad: ";
            cin.ignore();
            getline(cin, enfermedad);
            pacientes.emplace_back(nombre, apellidos, dni, fechaIngreso, enfermedad);
            cout << "Paciente registrado.\n";
            break;
        }
        case 2: {
            string dni;
            cout << "Ingrese DNI: ";
            cin >> dni;
            for (auto& paciente : pacientes) {
                if (paciente.dni == dni) {
                    paciente.modificarDatos();
                    break;
                }
            }
            break;
        }
        case 7:
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 7);
}

void HospitalController::menuMedicos() {
    cout << "--- Menu Medicos ---\n";
    // Similar to menuPacientes, implement options for Medico management.
}

void HospitalController::menuCitas() {
    cout << "--- Menu Citas Medicas ---\n";
    // Similar to menuPacientes, implement options for CitaMedica management.
}

void HospitalController::menuServicios() {
    cout << "--- Menu Servicios ---\n";
    // Implement options for managing hospital services.
}

void HospitalController::menuPrincipal() {
    int opcion;
    do {
        cout << "--- Menu Principal ---\n";
        cout << "1. Gestionar pacientes\n";
        cout << "2. Gestionar medicos\n";
        cout << "3. Gestionar citas medicas\n";
        cout << "4. Gestionar servicios\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuPacientes();
            break;
        case 2:
            menuMedicos();
            break;
        case 3:
            menuCitas();
            break;
        case 4:
            menuServicios();
            break;
        case 5:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);
}

int main() {
    HospitalController hospital;
    hospital.menuPrincipal();
    return 0;
}
