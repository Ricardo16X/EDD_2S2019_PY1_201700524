#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

/*Funciones internas*/
void cargarArchivo()
{
    system("cls");
    std::string nombre;
    std::cout << "\tIngresa la ruta relativa del archivo .csv\n\t";
    std::cin >> nombre;

    try
    {
        std::ifstream ip(nombre);
        if (ip.is_open())
        {
            std::cout << "ERROR: Intento fallido de lectura..\n";
            system("pause");
            return;
        }
        // Variables contenedores
        std::string layer;
        std::string file;
        // Lectura del archivo y recorrido y llenado de los distintos archivos que están vinculados al archivo .csv original leido.
        ip.open(nombre,std::ios::in);
        while (ip.good())
        {
            std::getline(ip,layer,',');
            std::getline(ip,file,'\n');

            std::cout << "Layer = " << layer << '\n';
            std::cout << "File = " << file << '\n';
            std::cout << std::endl;
        }
        system("pause");
        ip.close();
    }
    catch(...)
    {
        std::cout << "\nArchivo inexistente.\n";
    }
}
