#ifndef MENSAJITOS_H_INCLUDED
#define MENSAJITOS_H_INCLUDED

#include <iostream>
#include <string>

void menuINIT() {
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

void menuFILTROS() {
   system("cls");
   std::cout << "\t**MENU DE FILTROS&&" <<std::endl;
   std::cout << "1. Escala de Grises" << std::endl;
   // EC = r*0.4 + g*0.89 + b*0.11
   // rgb(EC,EC,EC);
   std::cout << "2. Negativo" << std::endl;
   // rgb(255-r,255-g,255-b);
}

void menuREPORTS() {
   system("cls");
   std::cout << "\t**MENU DE REPORTES&&" << std::endl;
   std::cout << "1. IMAGENES IMPORTADAS" << std::endl;
   std::cout << "2. IMAGE LAYER REPORT" << std::endl;
   std::cout << "3. LINEAR MATRIX REPORT" << std::endl;
   std::cout << "4. TRAVERSAL REPORT" << std::endl;
   std::cout << "5. FILTERS REPORT" << std::endl;
   std::cout << "0. Salir" << std::endl;
}

void menuMATRIZ() {
   system("cls");
   std::cout << "/tREPORTES DE MATRIZ" << std::endl;
   std::cout << "1. Capa Individual" << std::endl;
   std::cout << "2. Cubo Completo" << std::endl;
   std::cout << "3. SALIR" << std::endl;
}
#endif // MENSAJITOS_H_INCLUDED
