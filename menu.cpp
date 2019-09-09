#include <iostream>
#include <string>
#include <windows.h>

#include "ESTRUCTURAS.h"
#include "manejo_CSV.h"

int main(int argc, char const *argv[]) {
   /*Variables a utilizar globalmente en el main.*/
   ARBOL raiz = 0;
   cubo* nuevoElemento;
   cubo* elemento_paraTrabajo;

   std::string nombreArchivo = "";  // Nombre general del archivo.
   /*Menú Inicial*/
   int op = 0;
   while (op != 7) {
      system("cls");
      std::cout << "\t Menu" << std::endl;
      std::cout << "1. Insertar Imagen" << std::endl;
      std::cout << "2. Seleccionar Imagen" << std::endl;
      std::cout << "3. Aplicar Filtros" << std::endl;
      std::cout << "4. Edicion Manual" << std::endl;
      std::cout << "5. Exportar Imagen" << std::endl;
      std::cout << "6. Reportes" << std::endl;
      std::cout << "7. Salir" << std::endl;

      try {
         scanf("%i", &op);
         switch (op) {
            case 1:
               system("cls");
               std::cout << " Ingrese el nombre del archivo con extension '.csv' \n";
               std::cout<< " Asegurese que: " <<std::endl;
               std::cout<<" La carpeta se llame igual al archivo de carga inicial. >>> ";
               std::cin >> nombreArchivo;
               std::fflush(stdin);
               nuevoElemento = new cubo();
               nuevoElemento = leerArchivo(nombreArchivo.substr(0,nombreArchivo.length() - 4));
               /*Ya que en el paso anterior tengo el nuevo cubo recien creado,
               procederé a almacenarlo en el arbol*/
               if(nuevoElemento != NULL) {
                  insertar(raiz, nuevoElemento);
               } else {
                  std::cout << "No he encontrado ninguna carpeta/archivo.csv con el nombre " << nombreArchivo;
                  std::cout << std::endl;
               }
               system("pause");
               break;
            case 2:
               if(raiz == NULL) {
                  system("cls");
                  std::cout << "\tNo hay elementos para mostrar !!!" << std::endl;
               } else {
                  system("cls");
                  std::cout << "\tSELECTOR DE IMAGENES" << std::endl;
                  desplegarImagenes(raiz);
                  std::cout << "\tINGRESA EL NOMBRE EXACTO DE LA IMAGEN: ";
                  std::cin >> nombreArchivo;
                  // Aqui pondré el método que me devolverá el cubo con el cual pretendo trabajar
                  // en los pasos 3, 4, 5, 6;
                  elemento_paraTrabajo = obtenerCopia(raiz, nombreArchivo);
                  if(elemento_paraTrabajo != NULL) {
                     std::cout << "Se ha elegido la imagen: " << elemento_paraTrabajo->nombre << std::endl;
                     std::cout << "Informacion de Imagen: " << std::endl;
                     std::cout << "ANCHO IMAGEN : "<< elemento_paraTrabajo ->wImg << std::endl;
                     std::cout << "ALTO IMAGEN : "<< elemento_paraTrabajo ->hImg << std::endl;
                     std::cout << "ANCHO PIXEL : "<< elemento_paraTrabajo ->wPix << std::endl;
                     std::cout << "ALTO PIXEL : "<< elemento_paraTrabajo ->hPix << std::endl << std::endl;
                  } else {
                     // UY UN ERRORCITO
                     std::cout << "\n***HA OCURRIDO UN ERROR EN LA RECUPERACION DE LA IMAGEN\n";
                     std::cout << "\n***VERIFICA EL NOMBRE DE LA IMAGEN QUE SEA CORRECTO...\n";
                  }
               }
               system("pause");
               break;
            case 3:
               if(elemento_paraTrabajo != NULL) {

               }else{
                  std::cout << "SIN IMAGEN CARGADA" << std::endl;

               }
               system("pause");
               break;
            case 4:  // Edicion Manual
               /*if (temporal.nombre.compare("") == 0) {
                 std::cout << "### No hay imagen cargada :( ###" << std::endl;
               } else {
               }*/
               break;
            case 5:  // Exportar Imagen
               /*if (temporal.nombre.compare("") == 0) {
                 std::cout << "### No hay imagen cargada :( ###" << std::endl;
               } else {
               }*/
               break;
            case 6:  // Reportes
               graficar_arbol_General(raiz);
               break;
            case 7:  // Salir
               system("cls");
               std::cout << "\n\n#########################################"
                         << std::endl;
               std::cout << "#\tPHOTOGEN++ - 201700524\t\t#" << std::endl;
               std::cout << "#########################################\n\n"
                         << std::endl;
               system("pause");
               break;
            default:
               std::cout << "\t\nOpcion Incorrecta, Elige una opcion del menu.\n";
               std::cin.clear();
               std::cin.ignore(1000, '\n');
               system("pause");
               break;
         }
      } catch (const std::exception &e) {
         std::cout << "\t\nOpcion Incorrecta, Elige una opcion del menu.\n";
         std::cin.clear();
         std::cin.ignore(1000, '\n');
         system("pause");
         op = 0;
      }
   }
   return 0;
}
