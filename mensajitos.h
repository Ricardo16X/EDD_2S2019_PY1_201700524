#ifndef MENSAJITOS_H_INCLUDED
#define MENSAJITOS_H_INCLUDED

#include <iostream>
#include <string>

void menuINIT()
{
   system("cls");
   std::cout << "\t\t ###  Menu  ###" << std::endl;
   std::cout << "\t1. Insertar Imagen" << std::endl;
   std::cout << "\t2. Seleccionar Imagen" << std::endl;
   std::cout << "\t3. Aplicar Filtros" << std::endl;
   std::cout << "\t4. Edicion Manual" << std::endl;
   std::cout << "\t5. Exportar Imagen" << std::endl;
   std::cout << "\t6. Reportes" << std::endl;
   std::cout << "\t7. Salir" << std::endl;
}

void menuFILTROS()
{
   system("cls");
   std::cout << "\t\t###  MENU DE FILTROS  ###" << std::endl;
   std::cout << "\t1. NEGATIVO" << std::endl;
   std::cout << "\t2. ESCALA DE GRISES" << std::endl;
   std::cout << "\t3. ESPEJO" << std::endl;
   std::cout << "\t4. COLLAGE\n";
   std::cout << "\t5. REGRESAR" << std::endl;
   /*pronto nuevos filtros*/
}

void menuREPORTS()
{
   system("cls");
   std::cout << "\t\t###  MENU DE REPORTES  ###" << std::endl;
   std::cout << "\t1. IMAGENES IMPORTADAS" << std::endl;
   std::cout << "\t2. IMAGE LAYER REPORT" << std::endl;
   std::cout << "\t3. LINEAR MATRIX REPORT" << std::endl;
   std::cout << "\t4. TRAVERSAL REPORT" << std::endl;
   std::cout << "\t5. FILTERS REPORT" << std::endl;
   std::cout << "\t0. Salir" << std::endl;
}

void menuMATRIZ()
{
   system("cls");
   std::cout << "\t\t###  REPORTES DE MATRIZ  ###" << std::endl;
   std::cout << "\t1. Capa Individual" << std::endl;
   std::cout << "\t2. Cubo Completo" << std::endl;
   std::cout << "\t3. SALIR" << std::endl;
}

void menuFiltrosMirror()
{
   system("cls");
   std::cout << "\t\t###  MENU DE FILTROS DE ESPEJO  ###" << std::endl;
   std::cout << "\t1.Espejo - Eje X " << std::endl;
   std::cout << "\t2.Espejo - Eje Y" << std::endl;
   std::cout << "\t3.Espejo - Ambos Ejes" << std::endl;
   std::cout << "\t4.Regresar" << std::endl;
}

void menu_opcionFiltro()
{
   system("cls");
   std::cout << "\t\t###  SELECCIONA EL MODO DE FILTRO  ###" << std::endl;
   std::cout << "\t1. FILTRO A IMAGEN COMPLETA" << std::endl;
   std::cout << "\t2. FILTRO A CAPA" << std::endl;
   std::cout << "\t3. Salir" << std::endl;
}
#endif // MENSAJITOS_H_INCLUDED
