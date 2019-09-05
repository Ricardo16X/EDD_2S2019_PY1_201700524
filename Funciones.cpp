#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

std::fstream archivo;
std::fstream config;
std::fstream capa;

std::string errores = "";
std::string nombre = "";

// Estructura para almacenar los valores que se guardarán en los nodos del cubo disperso
struct NODO_CABECERA_CAPA
{
    std::string color = "";
    int cor_x = 0;
    int cor_y = 0;
    NODO_CABECERA_CAPA siguiente;
}*primerElemento;

struct CABECERA_CAPA
{
    NODO_CABECERA_CAPA *listaNodos;
    CABECERA_CAPA *siguiente;
    int columna;
};

struct CAPA
{
    NODO_CABECERA_CAPA *primerNodoCapa;
    CAPA siguiente*;
};

/*Funciones internas*/
void agregarCapa(std::string ruta);
void agregarConfiguracion(std::string ruta);
// Funciones "linkeadas"
void cargarArchivo()
{
    system("cls");
    std::cout << "\tIngresa la ruta relativa del archivo .csv\n\t";
    std::cin >> nombre;
    std::string ruta = "";
    ruta = "csv\\" + nombre.substr(0,nombre.length()-4) + "\\" + nombre;
    try
    {
        archivo.open(ruta,std::ios::in);
        if (!archivo.is_open())
        {
            std::cout << "ERROR: Intento fallido de lectura..\n";
            system("pause");
            return;
        }
        else
        {
            // Variables contenedores
            std::string layer;
            std::string file;
            int numArchivo = 0;
            // Lectura del archivo y recorrido y llenado de los distintos archivos que están vinculados al archivo .csv original leido.
            while (archivo.good())
            {
                std::getline(archivo,layer,',');
                std::getline(archivo,file,'\n');
                if (numArchivo > 0 && numArchivo <2)
                {
                    agregarConfiguracion(file);
                }
                else if(numArchivo > 1)
                {
                    agregarCapa(file);
                }
                numArchivo++;
            }
            std::cout << "Ingreso de Imagen correcto!\n";
            system("pause");
            archivo.close();
        }
    }
    catch(...)
    {
        std::cout << "\nArchivo inexistente.\n";
    }
}

void agregarConfiguracion(std::string nombreArchivo)
{
    nombreArchivo = "csv\\" + nombre.substr(0,nombre.length() - 4) + "\\" + nombreArchivo;
    config.open(nombreArchivo,std::ios::in);
    if (!config.is_open())
    {
        errores += "Error: ARCHIVO DE CONFIGURACION\n";
    }
    else
    {
    }
}

void agregarCapa(std::string nombreArchivo)
{
    nombreArchivo = "csv\\" + nombre.substr(0,nombre.length() - 4) + "\\" + nombreArchivo;
    capa.open(nombreArchivo,std::ios::in);
    if (!capa.is_open())
    {
        errores += "Error: ARCHIVO " + nombreArchivo + " \n";
    }
    else
    {
    }
}
