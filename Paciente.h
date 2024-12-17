// Paciente.h
#ifndef PACIENTE_H
#define PACIENTE_H
#include <string>
#include <vector>

class Paciente {
public:
    std::string nombre;
    std::string apellidos;
    std::string dni;
    std::string fechaIngreso;
    std::string enfermedad;
    std::vector<std::string> historialClinico;

    Paciente(std::string nombre, std::string apellidos, std::string dni, std::string fechaIngreso, std::string enfermedad = "");
    void altaPaciente();
    void bajaPaciente();
    void modificarDatos();
    void registrarHistorial(std::string registro);
    void mostrarHistorial();
};

#endif // PACIENTE_H