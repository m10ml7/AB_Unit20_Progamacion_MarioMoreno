// AB_Unit20_C++_MarioMoreno.cpp: define el punto de entrada de la aplicación.
//

#include "AB_Unit20_C++_MarioMoreno.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Clases
class Paciente {
public:
    string nombre;
    string apellidos;
    string dni;
    string fechaIngreso;
    string enfermedad;
    vector<string> historialClinico;

    Paciente(string nombre, string apellidos, string dni, string fechaIngreso, string enfermedad = "")
        : nombre(nombre), apellidos(apellidos), dni(dni), fechaIngreso(fechaIngreso), enfermedad(enfermedad) {}

    void altaMedica() {
        cout << "El paciente " << nombre << " ha recibido el alta medica.\n";
    }

    void bajaMedica() {
        cout << "El paciente " << nombre << " ha sido dado de baja.\n";
    }
 
    void modificarDatos() {
        cout << "Modificar datos del paciente.\n";
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

    void registrarHistorial(string registro) {
        historialClinico.push_back(registro);
    }

    void mostrarHistorial() {
        cout << "Historial clinico de " << nombre << ":\n";
        for (const auto& registro : historialClinico)
            cout << "- " << registro << "\n";
    }
};

class Medico {
public:
    string nombre;
    string apellidos;
    string dni;
    string especialidad;
    bool disponible;
    vector<Paciente*> pacientesAsignados;

    Medico(string nombre, string apellidos, string dni, string especialidad, bool disponible)
        : nombre(nombre), apellidos(apellidos), dni(dni), especialidad(especialidad), disponible(disponible) {}

    void modificarDatos() {
        cout << "Modificar datos del medico.\n";
        cout << "Nuevo nombre: ";
        cin >> nombre;
        cout << "Nuevos apellidos: ";
        cin >> apellidos;
        cout << "Nuevo DNI: ";
        cin >> dni;
        cout << "Nueva especialidad: ";
        cin >> especialidad;
        cout << "¿Está disponible? (1 para si, 0 para no): ";
        cin >> disponible;
    }

    void listarPacientes() {
        cout << "Pacientes asignados a " << nombre << ":\n";
        for (const auto& paciente : pacientesAsignados)
            cout << "- " << paciente->nombre << "\n";
    }
};

class CitaMedica {
public:
    string fechaHora;
    string especialidad;
    Medico* medico;
    Paciente* paciente;
    int nivelUrgencia;

    CitaMedica(string fechaHora, string especialidad, Medico* medico, Paciente* paciente, int nivelUrgencia)
        : fechaHora(fechaHora), especialidad(especialidad), medico(medico), paciente(paciente), nivelUrgencia(nivelUrgencia) {}

    void modificarCita() {
        cout << "Modificar datos de la cita.\n";
        cout << "Nueva fecha y hora: ";
        cin.ignore();
        getline(cin, fechaHora);
        cout << "Nuevo nivel de urgencia (1-5): ";
        cin >> nivelUrgencia;
    }

    static void ordenarCitas(vector<CitaMedica>& citas) {
        sort(citas.begin(), citas.end(), [](CitaMedica& a, CitaMedica& b) {
            if (a.fechaHora != b.fechaHora)
                return a.fechaHora < b.fechaHora;
            return a.nivelUrgencia > b.nivelUrgencia;
            });
    }
};

class Servicios {
public:
    string nombre;
    bool disponibilidad;
    vector<CitaMedica> citas;

    Servicios(string nombre, bool disponibilidad) : nombre(nombre), disponibilidad(disponibilidad) {}

    void reportarCitasPendientes() {
        cout << "Citas pendientes: \n";
        for (const auto& cita : citas) {
            if (cita.medico->disponible) {
                cout << "- Fecha: " << cita.fechaHora << ", Paciente: " << cita.paciente->nombre << ", Médico: " << cita.medico->nombre << "\n";
            }
        }
    }

    void pacientesAtendidos(string fechaInicio, string fechaFin) {
        cout << "Pacientes atendidos entre " << fechaInicio << " y " << fechaFin << ":\n";
        for (const auto& cita : citas) {
            if (cita.fechaHora >= fechaInicio && cita.fechaHora <= fechaFin) {
                cout << "- " << cita.paciente->nombre << "\n";
            }
        }
    }
};

// Submenús
// Menú paciente
void menuPacientes(vector<Paciente>& pacientes) {
    int opcion;
    do {
        cout << "--- Menu Pacientes ---\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Modificar datos del paciente\n";
        cout << "3. Dar de alta medica\n";
        cout << "4. Dar de baja medica\n";
        cout << "5. Registrar historial clinico\n";
        cout << "6. Mostrar historial clinico\n";
        cout << "7. Reporte enfermedad cronica\n";
        cout << "8. Volver al menu principal\n";
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
            cout << "Ingrese enfermedad (opcional): ";
            cin.ignore();
            getline(cin, enfermedad);
            pacientes.emplace_back(nombre, apellidos, dni, fechaIngreso, enfermedad);
            cout << "Paciente registrado.\n";
            break;
        }
        case 2: {
            string dni;
            cout << "Ingrese el DNI del paciente a modificar: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                it->modificarDatos();
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 3: {
            string dni;
            cout << "Ingrese el DNI del paciente para dar de alta medica: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                it->altaMedica();
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 4: {
            string dni;
            cout << "Ingrese el DNI del paciente para dar de baja medica: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                it->bajaMedica();
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 5: {
            string dni, registro;
            cout << "Ingrese el DNI del paciente: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                cout << "Ingrese el registro para el historial clinico: ";
                cin.ignore();
                getline(cin, registro);
                it->registrarHistorial(registro);
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 6: {
            string dni;
            cout << "Ingrese el DNI del paciente: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                it->mostrarHistorial();
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }   
        case 7: { 
            string dni, enfermedadCronica, descripcion;
            cout << "Ingrese el DNI del paciente: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                cout << "Paciente encontrado: " << it->nombre << " " << it->apellidos << "\n";

                if (it->enfermedad.empty()) {
                    cout << "El paciente no tiene una enfermedad registrada.\n";
                    break;
                }
                cout << "Enfermedad actual registrada: " << it->enfermedad << "\n";
                cout << "¿Desea modificar esta enfermedad? (S/N): ";
                char opcionEnfermedad;
                cin >> opcionEnfermedad;
                if (toupper(opcionEnfermedad) == 'S') {
                    cout << "Ingrese el nuevo nombre de la enfermedad cronica: ";
                    cin.ignore();
                    getline(cin, enfermedadCronica);
                    it->enfermedad = enfermedadCronica;
                }
                else {
                    enfermedadCronica = it->enfermedad; 
                }

                bool descripcionExistente = false;
                for (auto& registro : it->historialClinico) {
                    if (registro.find("Enfermedad cronica registrada: " + it->enfermedad) != string::npos) {
                        cout << "Descripcion actual encontrada en el historial:\n" << registro << "\n";
                        descripcionExistente = true;
                        cout << "¿Desea modificar la descripcion? (S/N): ";
                        char opcionModificarDescripcion;
                        cin >> opcionModificarDescripcion;
                        if (toupper(opcionModificarDescripcion) == 'S') {
                            cout << "Ingrese la nueva descripcion de la enfermedad: ";
                            cin.ignore();
                            getline(cin, descripcion);
                            registro = "Enfermedad cronica registrada: " + enfermedadCronica + " - " + descripcion; // Modifica el historial directamente
                            cout << "Nueva descripcion registrada exitosamente.\n";
                            cout << "Nueva descripcion: " << registro << "\n";
                        }
                        else {
                            cout << "Manteniendo la descripcion actual.\n";
                        }
                        break;
                    }
                }

                if (!descripcionExistente) {
                    cout << "No hay descripcion actual de la enfermedad.\n";
                    cout << "¿Desea agregar una descripcion? (S/N): ";
                    char opcionDescripcion;
                    cin >> opcionDescripcion;
                    if (toupper(opcionDescripcion) == 'S') {
                        cout << "Ingrese la descripcion de la enfermedad: ";
                        cin.ignore();
                        getline(cin, descripcion);
                        it->registrarHistorial("Enfermedad cronica registrada: " + enfermedadCronica + " - " + descripcion);
                        cout << "Descripción registrada.\n";
                        cout << "Nueva descripción: enfermedad cronica" << enfermedadCronica << " : " << descripcion << "\n";
                    }
                    else {
                        it->registrarHistorial("Enfermedad cronica registrada: " + enfermedadCronica);
                        cout << "Enfermedad registrada sin descripción adicional.\n";
                        break;
                    }
                }
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }

        case 8:
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 8);
}


// Menú opciones
void menuPrincipal() {
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<CitaMedica> citas;
    Servicios servicios("Hospital central", true);

    int opcion;
    do {
        cout << "--- Menu Principal ---\n";
        cout << "1. Gestionar pacientes\n";
        cout << "2. Gestionar medicos\n";
        cout << "3. Gestionar citas medicas\n";
        cout << "4. Servicios\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuPacientes(pacientes);
            break;
        case 2:
           // menuMedicos(medicos);
            break;
        case 3:
           // menuCitas(citas);
            break;
        case 4:
           // menuServicios(servicios);
            break;
        case 5:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 5);
}

// Main
int main() {
    menuPrincipal();
    return 0;
}
