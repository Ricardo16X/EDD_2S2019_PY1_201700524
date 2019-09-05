#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

/*  Definición de Estructuras   */
struct nodoCabecera{
    // Valores de estructura
    std::string color;
    int fila;
    // apuntadores
    nodoCabecera *sig;
}primerNodo;

struct cabecera{
    // datos
    int column;
    // apuntadores
    nodoCabecera primer_nodoCabecera;
}primerCabecera;

struct capa{
    cabecera primer_Cabecera;
}primerCapa;

struct cubo
{
    // datos del cubo
    std::string nombre;
    // enlace a la primera capa
    capa primer_Capa;
    // punteros para arbol binario
    cubo *izq;
    cubo *der;
};

/*  Definición de Métodos   */

/*Construcción de Métodos*/
