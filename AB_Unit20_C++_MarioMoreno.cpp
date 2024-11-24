// AB_Unit20_C++_MarioMoreno.cpp: define el punto de entrada de la aplicación.
//

#include "AB_Unit20_C++_MarioMoreno.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Clases
class Paciente {
public:
    string nombre;
    string apellidos;
    string dni;
    string enfermedad;
    string fechaIngreso;
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

int main() {

    return 0;
}

