﻿# CMakeList.txt: proyecto de CMake para AB_Unit20_C++_MarioMoreno, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("AB_Unit20_C++_MarioMoreno")

# Agregue un origen al ejecutable de este proyecto.
add_executable (AB_Unit20_C++_MarioMoreno "AB_Unit20_C++_MarioMoreno.cpp" "AB_Unit20_C++_MarioMoreno.h" "Paciente.cpp" "Paciente.h" "Medico.cpp" "Medico.h" "CitaMedica.cpp" "CitaMedica.h" "Servicios.cpp" "Servicios.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AB_Unit20_C++_MarioMoreno PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
