#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "estructuras.h"

std::fstream arch_init;
std::fstream arch_config;
std::fstream arch_capa;

/*Declaración de funciones*/
void leerArchivo(std::string);

/*Construcción de funciones*/
void leerArchivo(std::string ruta) {
    arch_init.open(ruta,std::ios::in);
}