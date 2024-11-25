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

    void altaPaciente() {
        cout << "El paciente " << nombre << " ha recibido el alta medica.\n";
    }

    void bajaPaciente() {
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

    Medico(string nombre, string apellidos, string dni, bool disponible)
        : nombre(nombre), apellidos(apellidos), dni(dni), disponible(disponible) {}

    void altaMedico() {
        if (!disponible) {
            disponible = true;
            cout << "El medico " << nombre << apellidos << " ha sido dado de alta y ahora está disponible.\n";
        }
        else {
            cout << "El medico " << nombre << apellidos << " ha sido dado de alta.\n";
        }
    }

    void bajaMedico() {
        if (disponible) {
            disponible = false;
            cout << "El medico " << nombre << apellidos << " ha sido dado de baja y ahora no esta disponible.\n";
        }
        else {
            cout << "El médico " << nombre << apellidos << " ha sido dado de baja.\n";
        }
    }

    void modificarDatos() {
        cout << "Modificar datos del medico.\n";
        cout << "Nuevo nombre: ";
        cin >> nombre;
        cout << "Nuevos apellidos: ";
        cin >> apellidos;
        cout << "Nuevo DNI: ";
        cin >> dni;
        cout << "Medico disponible (1 para si, 0 para no): ";
        cin >> disponible;
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
                it->altaPaciente();
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
                it->bajaPaciente();
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

void menuMedicos(vector<Medico>& medicos) {
    int opcion;
    do {
        cout << "--- Menu Medicos ---\n";
        cout << "1. Registrar medico\n";
        cout << "2. Modificar datos del medico\n";
        cout << "3. Asignar especialidad\n";
        cout << "4. Listado medicos disponibles\n";
        cout << "5. Listado medicos no disponibles\n";
        cout << "6. Dar de alta\n";
        cout << "7. Dar de baja\n";
        cout << "8. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre, apellidos, dni, especialidad;
            bool disponible;
            cout << "Ingrese nombre: ";
            cin >> nombre;
            cout << "Ingrese apellidos: ";
            cin >> apellidos;
            cout << "Ingrese DNI: ";
            cin >> dni;
            cout << "Medico disponible (1 para si, 0 para no): ";
            cin >> disponible;
            medicos.emplace_back(nombre, apellidos, dni, disponible);
            cout << "Medico registrado.\n";
            break;
        }
        case 2: {
            string dni;
            cout << "Ingrese el DNI del medico a modificar: ";
            cin >> dni;
            auto it = find_if(medicos.begin(), medicos.end(), [&dni](Medico& m) { return m.dni == dni; });
            if (it != medicos.end()) {
                it->modificarDatos();
            }
            else {
                cout << "Medico no encontrado.\n";
            }
            break;
        }
        case 3: {
            string dni;
            cout << "Ingrese el DNI del medico para asignar especialidad: ";
            cin >> dni;
            auto it = find_if(medicos.begin(), medicos.end(), [&dni](Medico& m) { return m.dni == dni; });
            if (it != medicos.end()) {
                cout << "Seleccione la especialidad:\n";
                vector<string> especialidades = {
                    "Alergologia", "Anatomia Patologica", "Anestesiologia y Reanimacion",
                    "Angiologia y Cirugia Vascular", "Aparato Digestivo", "Cardiologia",
                    "Cirugia Cardiovascular", "Cirugia General y del Aparato Digestivo",
                    "Cirugia Oral y Maxilofacial", "Cirugia Ortopedica y Traumatologia",
                    "Cirugia Pediatrica", "Cirugia Plastica, Estetica y Reparadora",
                    "Cirugía Toracica", "Dermatologia Medico-Quirurgica y Venereologia",
                    "Endocrinologia y Nutricion", "Farmacologia Clinica", "Geriatria",
                    "Hematologia y Hemoterapia", "Inmunologia", "Medicina del Trabajo",
                    "Medicina Familiar y Comunitaria", "Medicina Fisica y Rehabilitacion",
                    "Medicina Intensiva", "Medicina Interna", "Medicina Nuclear",
                    "Medicina Preventiva y Salud Publica", "Nefrologia", "Neumologia",
                    "Neurocirugia", "Neurofisiologia Clinica", "Neurologia",
                    "Obstetricia y Ginecologia", "Oftalmologia", "Oncologia Medica",
                    "Oncología Radioterapica", "Otorrinolaringologia",
                    "Pediatria y sus Areas Especificas", "Psiquiatria", "Radiodiagnostico",
                    "Reumatologia", "Urologia"
                };
                for (size_t i = 0; i < especialidades.size(); ++i) {
                    cout << i + 1 << ". " << especialidades[i] << '\n';
                }
                int seleccion;
                cout << "Seleccione una opcion (1-" << especialidades.size() << "): ";
                cin >> seleccion;
                if (seleccion >= 1 && seleccion <= especialidades.size()) {
                    it->especialidad = especialidades[seleccion - 1];
                    cout << "Especialidad asignada: " << it->especialidad << '\n';
                }
                else {
                    cout << "Opcion no valida.\n";
                }
            }
            else {
                cout << "Medico no registrado.\n";
            }
            break;
        }
        case 4: {
            vector<Medico*> disponibles;
            for (auto& medico : medicos) {
                if (medico.disponible) {
                    disponibles.push_back(&medico);
                }
            }
            sort(disponibles.begin(), disponibles.end(),
                [](Medico* a, Medico* b) { return a->especialidad < b->especialidad; });
            cout << "--- Lista de medicos disponibles ---\n";
            for (auto* medico : disponibles) {
                cout << medico->nombre << " " << medico->apellidos
                    << " - Especialidad: " << medico->especialidad << '\n';
            }
            break;
        }
        case 5: {
            vector<Medico*> noDisponibles;
            for (auto& medico : medicos) {
                if (!medico.disponible) {
                    noDisponibles.push_back(&medico);
                }
            }
            sort(noDisponibles.begin(), noDisponibles.end(),
                [](Medico* a, Medico* b) { return a->especialidad < b->especialidad; });
            cout << "--- Lista de Medicos No Disponibles ---\n";
            for (auto* medico : noDisponibles) {
                cout << medico->nombre << " " << medico->apellidos
                    << " - Especialidad: " << medico->especialidad << '\n';
            }
            break;
        }

        case 6: {
            string dni;
            cout << "Ingrese el DNI del medico para dar de alta: ";
            cin >> dni;
            auto it = find_if(medicos.begin(), medicos.end(), [&dni](Medico& m) { return m.dni == dni; });
            if (it != medicos.end()) {
                it->altaMedico();
            }
            else {
                cout << "Medico no encontrado.\n";
            }
            break;
        }
        case 7: {
            string dni;
            cout << "Ingrese el DNI del medico para dar de baja: ";
            cin >> dni;
            auto it = find_if(medicos.begin(), medicos.end(), [&dni](Medico& m) { return m.dni == dni; });
            if (it != medicos.end()) {
                it->bajaMedico();
            }
            else {
                cout << "Medico no encontrado.\n";
            }
            break;
        }
        case 8:
            break;
        default:
            cout << "Opción no valida.\n";
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
            menuMedicos(medicos);
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