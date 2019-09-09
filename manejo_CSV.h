#ifndef MANEJO_CSV_H_INCLUDED
#define MANEJO_CSV_H_INCLUDED

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "ESTRUCTURAS.h"

std::fstream arch_init;
std::fstream arch_config;
std::fstream arch_capa;

/**DECLARACION DE FUNCIONES EXTERNAS**/
void cargarConfig(std::string rutaConfig, cubo* nuevaImagen);
void cargarCapa(std::string rutaCapa, std::string nombreCapa, cubo* nuevaImagen);

ARBOL leerArchivo(std::string ruta)
{
    /*Aqui tengo que "configurar" la ruta de inicio para darle "validez"*/
    std::string rutaInit = "csv\\" + ruta + "\\" + ruta + ".csv";
    arch_init.open(rutaInit,std::ios::in);
    if(arch_init.is_open())
    {
        std::string layer;
        std::string file;
        // Leeré el archivo inicial
        int numArchivo = 0;

        cubo* nuevaImagen = new cubo(); // Creación de un nuevo cubo, que será el que se retornará.

        while(arch_init.good())
        {

            std::getline(arch_init,layer,',');
            std::getline(arch_init,file,'\n');
            if (numArchivo == 1)
            {
                /*Eso me dice que es el primer archivo, por lo tanto es el de
                configuración*/
                nuevaImagen->nombre = ruta;
                nuevaImagen->ruta = "csv\\" + ruta + "\\";
                rutaInit = "csv\\" + ruta + "\\" + file;
                cargarConfig(rutaInit, nuevaImagen);
            }
            else if(numArchivo > 1)
            {
                /*Esto me dice que el numero de archivo es mayor a 1 por lo
                tanto son archivos de capas...*/
                rutaInit = "csv\\" + ruta + "\\" + file;
                // El nombre de la capa será la del archivo sin su extension .csv
                cargarCapa(rutaInit, file.substr(0,file.length() - 4), nuevaImagen);
            }
            numArchivo++;
        }
        std::cout << "La imagen " << ruta << " se ha insertado correctamente. " << std::endl;
        arch_init.close();
        return nuevaImagen;
    }
    else
    {
        std::cout << "No hay ningun archivo/carpeta con este nombre = " + ruta << std::endl;
        return NULL;
    }
}

void cargarConfig(std::string rutaConfig, cubo* nuevaImagen)
{
    arch_config.open(rutaConfig,std::ios::in);
    if(arch_config.is_open())
    {

        // Configuracion contiene 2 columnas
        /* Config, Value
        */
        std::string config;
        std::string value;
        int cont_config = 0;
        /*Fin de esas variables*/

        while(arch_config.good())
        {
            std::getline(arch_config, config, ',');
            std::getline(arch_config,value,'\n');
            if(cont_config == 1)
            {
                /*Primero image_width*/
                nuevaImagen->wImg = std::stoi(value);
            }
            else if(cont_config == 2)
            {
                // Segundo image_height
                nuevaImagen->hImg = std::stoi(value);
            }
            else if(cont_config == 3)
            {
                // Tercero pixel_width
                nuevaImagen->wPix = std::stoi(value);
            }
            else if(cont_config == 4)
            {
                // por ultimo pixel_height
                nuevaImagen->hPix = std::stoi(value);
            }
            cont_config++;
        }

    }
    else
    {
        std::cout << "Error al leer el archivo " + rutaConfig;
    }
    arch_config.close();
}

void cargarCapa(std::string rutaCapa, std::string nombreCapa, cubo* nuevaImagen)
{
    arch_capa.open(rutaCapa,std::ios::in);
    if(arch_capa.is_open())
    {
        capa* nuevaCapa = new capa();
        nuevaCapa->nombreCapa = nombreCapa;
        // Coordenadas Iniciales de la matriz.
        int columna = 1, fila = 1;

        /*Crearé dos ciclos while
            1. Recorrerá para conocer el numero de columnas que tiene el archivo
            para poder crear por cada columna una cabecera.
            2. Recorrerá cada fila y columna después de haber creado las cabeceras correspondientes.
        */

        std::string color = "";

        /*Inicio del primer ciclo while*/
        while(std::getline(arch_capa,color))
        {
            std::stringstream strstr(color);
            std::string w_color = "";
            while(std::getline(strstr,w_color,','))
            {
                cabecera *nuevaCabecera = new cabecera();
                nuevaCabecera->column = columna;
                agregarCabecera(nuevaCapa, nuevaCabecera);
                columna++;
            }
            columna = 1;
            break;
        }

        /*Inicio del segundo ciclo while para leer cada elemento del archivo.*/
        arch_capa.close();
        color = "";
        arch_capa.open(rutaCapa, std::ios::in);
        while(std::getline(arch_capa,color))
        {

            std::stringstream strstr(color);
            std::string w_color = "";

            while(std::getline(strstr,w_color,','))
            {
                elementoCabecera* colorRGB = new elementoCabecera(w_color,fila);
                agregarFila(obtenerCabecera(nuevaCapa, columna),colorRGB);
                columna++;
            }
            fila++;
            columna = 1;
        }
        arch_capa.close();
        agregarCapa(nuevaImagen,nuevaCapa);
    }
    else
    {
        std::cout << "No se pudo cargar la capa " + rutaCapa;
    }
}

#endif // MANEJO_CSV_H_INCLUDED
