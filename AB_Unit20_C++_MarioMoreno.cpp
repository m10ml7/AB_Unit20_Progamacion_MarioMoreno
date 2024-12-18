// AB_Unit20_C++_MarioMoreno.cpp
#include "AB_Unit20_C++_MarioMoreno.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

GestionHospital::GestionHospital() : servicios() {}

void GestionHospital::menuPacientes() {
    short int opcion;
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
            cin.ignore();
            cout << "Ingrese apellidos: ";
            getline(cin, apellidos);
            cout << "Ingrese DNI: ";
            cin >> dni;
            cout << "Ingrese fecha de ingreso (si hay): ";
            cin.ignore();
            getline(cin, fechaIngreso);
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

void GestionHospital::menuMedicos() {
    short int opcion;
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

// Almacenamientos de ID y que sean únicos
set<string> idGenerar;

string generarIDCita(Paciente* paciente) {
    // Obtener iniciales del paciente
    string iniciales;
    if (!paciente->nombre.empty())
        iniciales += toupper(paciente->nombre[0]);
    if (!paciente->apellidos.empty()) {
        auto espacio = paciente->apellidos.find(' ');
        iniciales += toupper(paciente->apellidos[0]);
        if (espacio != string::npos && espacio + 1 < paciente->apellidos.length())
            iniciales += toupper(paciente->apellidos[espacio + 1]);
    }

    // Generar número aleatorio
    string idCita;
    srand(time(nullptr));
    do {
        int numero = rand() % 10000; // Generar número aleatorio de 4 cifras
        char numeroStr[5];
        snprintf(numeroStr, sizeof(numeroStr), "%04d", numero);
        idCita = string(numeroStr) + " " + iniciales;
    } while (idGenerar.count(idCita)); // Repetir si el ID ya existe

    idGenerar.insert(idCita);
    return idCita;
}

void GestionHospital::menuCitas() {
    short int opcion;
    do {
        cout << "--- Menu citas ---\n";
        cout << "1. Asignar cita\n";
        cout << "2. Modificar datos de la cita\n";
        cout << "3. Cancelar cita\n";
        cout << "4. Citas ordenadas por fecha o nivel de urgencia\n";
        cout << "5. Registro de citas completo\n";
        cout << "6. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string id;
            string fechaHora, especialidad;
            short int nivelUrgencia;
            Medico* medico = nullptr;
            Paciente* paciente = nullptr;

            cout << "Asignar una nueva cita\n";
            cout << "Fecha y hora (YYYY-MM-DD HH:MM): ";
            cin.ignore();
            getline(cin, fechaHora);

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

            cout << "Elija una especialidad:\n";
            for (size_t i = 0; i < especialidades.size(); ++i) {
                cout << i + 1 << ". " << especialidades[i] << endl;
            }

            short int especialidadSeleccion;
            cout << "Seleccione el numero de la especialidad (0 para cancelar): ";
            cin >> especialidadSeleccion;

            if (especialidadSeleccion < 1 || especialidadSeleccion > especialidades.size()) {
                cout << "Especialidad invalida. Operacion cancelada.\n";
                break;
            }

            especialidad = especialidades[especialidadSeleccion - 1];

            // Seleccionar médico
            cout << "Medicos disponibles de la especialidad " << especialidad << ":\n";
            vector<Medico*> medicosEspecialidad;
            for (auto& medicoIter : medicos) {
                if (medicoIter.especialidad == especialidad && medicoIter.disponible) {
                    medicosEspecialidad.push_back(&medicoIter);
                }
            }

            if (medicosEspecialidad.empty()) {
                cout << "No hay medicos disponibles para esta especialidad.\n";
                break;
            }

            for (size_t i = 0; i < medicosEspecialidad.size(); ++i) {
                cout << i + 1 << ". " << medicosEspecialidad[i]->nombre << " " << medicosEspecialidad[i]->apellidos << endl;
            }

            int medicoSeleccion;
            cout << "Seleccione el numero del medico (0 para cancelar): ";
            cin >> medicoSeleccion;

            if (medicoSeleccion > 0 && medicoSeleccion <= medicosEspecialidad.size()) {
                medico = medicosEspecialidad[medicoSeleccion - 1];
            }
            else {
                cout << "Selección invalida. Operacion cancelada.\n";
                break;
            }

            // Seleccionar paciente
            cout << "Lista de pacientes registrados:\n";
            for (size_t i = 0; i < pacientes.size(); ++i) {
                cout << i + 1 << ". " << pacientes[i].nombre << " " << pacientes[i].apellidos << " - DNI: " << pacientes[i].dni << endl;
            }

            int pacienteSeleccion;
            cout << "Seleccione el numero del paciente (0 para cancelar): ";
            cin >> pacienteSeleccion;

            if (pacienteSeleccion > 0 && pacienteSeleccion <= pacientes.size()) {
                paciente = &pacientes[pacienteSeleccion - 1];
            }
            else {
                cout << "Seleccion invalida. Operacion cancelada.\n";
                break;
            }

            // Generar ID único dependiendo de las inciales del paciente
            id = generarIDCita(paciente);

            cout << "Nivel de urgencia (1-5, siendo 5 el mas urgente): ";
            cin >> nivelUrgencia;

            if (nivelUrgencia < 1 || nivelUrgencia > 5) {
                cout << "Nivel de urgencia invalido. Operacion cancelada.\n";
                break;
            }

            // Crear la cita y agregarla a la lista
            citas.emplace_back(id, fechaHora, especialidad, medico, paciente, nivelUrgencia);
            cout << "Cita asignada exitosamente.\n";
            cout << "ID: " << id << ", Fecha: " << fechaHora << ", Especialidad: " << especialidad;
            cout << ", Medico: " << medico->nombre << " " << medico->apellidos;
            cout << ", Paciente: " << paciente->nombre << " " << paciente->apellidos;
            cout << ", Nivel de urgencia: " << nivelUrgencia << endl;
            break;
        }
        case 2: {
            string id;
            cout << "Ingrese el ID de la cita a modificar: ";
            cin >> id;
            for (auto& cita : citas) {
                if (cita.id == id) {
                    cita.modificarCita();
                    cout << "Cita modificada con exito.\n";
                    break;
                }
            }
            break;
        }
        case 3: {
            string nombre, apellidos;
            cout << "Ingrese el nombre y apellidos del paciente o medico: ";
            cin >> nombre >> apellidos;

            vector<CitaMedica*> coincidencias;
            for (auto& cita : citas) {
                if (cita.medico->nombre == nombre && cita.medico->apellidos == apellidos ||
                    cita.paciente->nombre == nombre && cita.paciente->apellidos == apellidos) {
                    coincidencias.push_back(&cita);
                }
            }

            if (coincidencias.empty()) {
                cout << "No se encontraron coincidencias.\n";
                break;
            }

            for (size_t i = 0; i < coincidencias.size(); ++i) {
                cout << i + 1 << ". Cita ID: " << coincidencias[i]->id << " - Fecha: " << coincidencias[i]->fechaHora
                    << " - Medico: " << coincidencias[i]->medico->nombre << " " << coincidencias[i]->medico->apellidos
                    << " - Paciente: " << coincidencias[i]->paciente->nombre << " " << coincidencias[i]->paciente->apellidos << endl;
            }

            int seleccion;
            cout << "Seleccione el numero de la cita a cancelar: ";
            cin >> seleccion;

            if (seleccion > 0 && seleccion <= coincidencias.size()) {
                auto it = remove_if(citas.begin(), citas.end(), [&](CitaMedica& cita) {
                    return &cita == coincidencias[seleccion - 1];
                    });
                citas.erase(it, citas.end());
                cout << "Cita cancelada con exito.\n";
            }
            else {
                cout << "Seleccion invalida.\n";
            }
            break;
        }
        case 4: {
            short int subopciones;
            cout << "Elige una opcion para ordenar las citas:\n";
            cout << "1. Ordenar por fecha\n";
            cout << "2. Ordenar por nivel de urgencia\n";
            cout << "Opcion: ";
            cin >> subopciones;

            time_t t = time(nullptr);
            tm* now = localtime(&t);
            char currentDate[20];
            strftime(currentDate, sizeof(currentDate), "%Y-%m-%d %H:%M", now);

            if (subopciones == 1) {
                sort(citas.begin(), citas.end(), [](const CitaMedica& a, const CitaMedica& b) {
                    return a.fechaHora < b.fechaHora;
                    });

                cout << "Citas ordenadas por fecha (solo futuras):\n";
                for (const auto& cita : citas) {
                    if (cita.fechaHora >= currentDate) { // Filtrar citas futuras
                        cout << "ID: " << cita.id
                            << " - Fecha: " << cita.fechaHora
                            << " - Paciente: " << cita.paciente->nombre << " " << cita.paciente->apellidos
                            << " - Medico: " << cita.medico->nombre << " " << cita.medico->apellidos
                            << " - Nivel de urgencia: " << cita.nivelUrgencia << endl;
                    }
                }
            }
            else if (subopciones == 2) {
                sort(citas.begin(), citas.end(), [](const CitaMedica& a, const CitaMedica& b) {
                    return a.nivelUrgencia > b.nivelUrgencia;
                    });

                cout << "Citas ordenadas por nivel de urgencia (más urgentes primero, solo futuras):\n";
                for (const auto& cita : citas) {
                    if (cita.fechaHora >= currentDate) {
                        cout << "ID: " << cita.id
                            << " - Fecha: " << cita.fechaHora
                            << " - Nivel de urgencia: " << cita.nivelUrgencia
                            << " - Paciente: " << cita.paciente->nombre << " " << cita.paciente->apellidos
                            << " - Medico: " << cita.medico->nombre << " " << cita.medico->apellidos << endl;
                    }
                }
            }
            else {
                cout << "Opcion invalida.\n";
            }
            break;
        }
        case 5: {
            time_t t = time(nullptr);
            tm* now = localtime(&t);
            char currentDate[20];
            strftime(currentDate, sizeof(currentDate), "%Y-%m-%d %H:%M", now);

            short int subopciones;
            cout << "Elige una opcion:\n1. Citas pasadas\n2. Citas futuras\nOpcion: ";
            cin >> subopciones;

            if (subopciones == 1) {
                cout << "Citas pasadas:\n";
                for (const auto& cita : citas) {
                    if (cita.fechaHora < currentDate)
                        cout << "ID: " << cita.id << " - Fecha: " << cita.fechaHora << " - Paciente: " << cita.paciente->nombre << endl;
                }
            }
            else if (subopciones == 2) {
                cout << "Citas futuras:\n";
                for (const auto& cita : citas) {
                    if (cita.fechaHora >= currentDate)
                        cout << "ID: " << cita.id << " - Fecha: " << cita.fechaHora << " - Paciente: " << cita.paciente->nombre << " - Medico: " << cita.medico->nombre << endl;
                }
            }
            else {
                cout << "Opcion invalida.\n";
            }
            break;
        }
        case 6:
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 6);
}

void GestionHospital::menuServicios() {
    Servicios servicios;
    int opcion;
    do {
        cout << "--- Menu Servicios ---\n";
        cout << "1. Listar citas pendientes por especialidad\n";
        cout << "2. Listar pacientes atendidos por rango de fechas\n";
        cout << "3. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            // Listar citas pendientes por especialidad
            servicios.listarCitasPendientesPorEspecialidad();
            break;
        case 2: {
            // Listar pacientes atendidos por rango de fechas
            string fechaInicio, fechaFin;
            cout << "Ingrese la fecha de inicio (YYYY-MM-DD): ";
            cin >> fechaInicio;
            cout << "Ingrese la fecha de fin (YYYY-MM-DD): ";
            cin >> fechaFin;
            servicios.listarPacientesAtendidosPorFechas(fechaInicio, fechaFin);
            break;
        }
        case 3:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 3);
}

void GestionHospital::menuPrincipal() {
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
    GestionHospital hospital;
    hospital.menuPrincipal();
    return 0;
}
