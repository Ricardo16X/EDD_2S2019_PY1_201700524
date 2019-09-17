#ifndef MENSAJITOS_H_INCLUDED
#define MENSAJITOS_H_INCLUDED

#include <iostream>
#include <string>

void menuINIT()
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
}

void menuFILTROS()
{
   system("cls");
   std::cout << "\t**MENU DE FILTROS&&" << std::endl;
   std::cout << "1. NEGATIVO" << std::endl;
   std::cout << "2. ESCALA DE GRISES" << std::endl;
   std::cout << "3. ESPEJO" << std::endl;
   std::cout << "4. COLLAGE\n";
   std::cout << "5. REGRESAR" << std::endl;
   /*pronto nuevos filtros*/
}

void menuREPORTS()
{
   system("cls");
   std::cout << "\t**MENU DE REPORTES&&" << std::endl;
   std::cout << "1. IMAGENES IMPORTADAS" << std::endl;
   std::cout << "2. IMAGE LAYER REPORT" << std::endl;
   std::cout << "3. LINEAR MATRIX REPORT" << std::endl;
   std::cout << "4. TRAVERSAL REPORT" << std::endl;
   std::cout << "5. FILTERS REPORT" << std::endl;
   std::cout << "0. Salir" << std::endl;
}

void menuMATRIZ()
{
   system("cls");
   std::cout << "\tREPORTES DE MATRIZ" << std::endl;
   std::cout << "1. Capa Individual" << std::endl;
   std::cout << "2. Cubo Completo" << std::endl;
   std::cout << "3. SALIR" << std::endl;
}

void menuFiltrosMirror()
{
   system("cls");
   std::cout << "\tMENU DE FILTROS DE ESPEJO" << std::endl;
   std::cout << "\t1.Espejo - Eje X " << std::endl;
   std::cout << "\t2.Espejo - Eje Y" << std::endl;
   std::cout << "\t3.Espejo - Ambos Ejes" << std::endl;
   std::cout << "\t4.Regresar" << std::endl;
}

void menu_opcionFiltro()
{
   system("cls");
   std::cout << "1. FILTRO A IMAGEN COMPLETA" << std::endl;
   std::cout << "2. FILTRO A CAPA" << std::endl;
   std::cout << "3. Salir" << std::endl;
}
#endif // MENSAJITOS_H_INCLUDED
