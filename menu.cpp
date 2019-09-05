#include <iostream>
#include "librerias/estructuras.h"

int main(int argc, char const *argv[])
{
    cubo raiz = cubo();
    /*Menú Inicial*/
    int op = 0;
    while (op != 7)
    {
        system("cls");
        std::cout << "\t Menu" << std::endl;
        std::cout << "1. Insertar Imagen" << std::endl;
        std::cout << "2. Seleccionar Imagen" << std::endl;
        std::cout << "3. Aplicar Filtros" << std::endl;
        std::cout << "4. Edicion Manual" << std::endl;
        std::cout << "5. Exportar Imagen" << std::endl;
        std::cout << "6. Reportes" << std::endl;
        std::cout << "7. Salir" << std::endl;

        try
        {
            scanf("%i", &op);
            switch (op)
            {
            case 1:
                /*Cargar Imagen*/
                cargarImagen(&raiz);
                break;
            case 2:
                // Seleccionar Imagen
            	break;
            case 3:
                // Aplicar filtros
                break;
            case 4:  // Edicion Manual
                break;
            case 5:  // Exportar Imagen
                break;
            case 6:  // Reportes
                break;
            case 7:  // Salir
                system("cls");
                std::cout << "\n\n#########################################" << std::endl;
                std::cout << "#\tPHOTOGEN++ - 201700524\t\t#" << std::endl;
                std::cout << "#########################################\n\n" << std::endl;
                system("pause");
                break;
            default:
                std::cout << "\t\nOpcion Incorrecta, Elige una opcion del menu.\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                system("pause");
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "\t\nOpcion Incorrecta, Elige una opcion del menu.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            system("pause");
            op = 0;
        }
    }
    return 0;
}