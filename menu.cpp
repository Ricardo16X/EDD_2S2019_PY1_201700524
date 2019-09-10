#include <iostream>
#include <string>
#include <fstream>

#include "ESTRUCTURAS.h"
#include "manejo_CSV.h"
#include "mensajitos.h"

int main(int argc, char const *argv[]) {
   /*Variables a utilizar globalmente en el main.*/
   ARBOL raiz = 0;
   cubo* nuevoElemento;
   cubo* elemento_paraTrabajo;


   std::string nombreArchivo = "";  // Nombre general del archivo.
   std::string grafico = "";

   std::ofstream archivoDOT;
   /*Men� Inicial*/
   int op = 0;
   while (op != 7) {
      menuINIT();
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
               proceder� a almacenarlo en el arbol*/
               if(nuevoElemento != NULL && noExiste(raiz, nuevoElemento->nombre)) {
                  insertar(raiz, nuevoElemento);
               } else {
                  std::cout << "No he encontrado ninguna carpeta/archivo.csv con el nombre " << nombreArchivo;
                  std::cout << std::endl;
                  std::cout << "O quizas ya haya una imagen cargada, con el mismo nombre." << std::endl;
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
                  // Aqui pondr� el m�todo que me devolver� el cubo con el cual pretendo trabajar
                  // en los pasos 3, 4, 5;
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
                     std::cout << "\n***HA OCURRIDO UN ERROR EN LA RECUPERACION DE LA IMAGEN&&&\n";
                     std::cout << "\n***VERIFICA EL NOMBRE DE LA IMAGEN QUE SEA CORRECTO...&&&\n";
                  }
               }
               system("pause");
               break;
            case 3:
               if(elemento_paraTrabajo != NULL) {
                  /**MENU DE FILTROS**/
                  menuFILTROS();
               } else {
                  std::cout << "**SIN IMAGEN CARGADA&&" << std::endl;
               }
               system("pause");
               break;
            case 4:  // Edicion Manual
               break;
            case 5:  // Exportar Imagen
               break;
            case 6:  // Reportes
               // Men� de reportes
               if(raiz != NULL) {
                  while(op != 0) {
                        /**
   std::cout << "1. IMAGENES IMPORTADAS" << std::endl;
   std::cout << "2. IMAGE LAYER REPORT" << std::endl;
   std::cout << "3. LINEAR MATRIX REPORT" << std::endl;
   std::cout << "4. TRAVERSAL REPORT" << std::endl;
   std::cout << "5. FILTERS REPORT" << std::endl;
   std::cout << "0. Salir" << std::endl;**/
                     menuREPORTS();
                     std::cin >> op;
                     switch (op) {
                        case 1:
                           graficar_arbol_General(raiz);
                           break;
                        case 2:
                           // REPORTE DE CAPAS DEL CUBO
                           op = 9;
                           grafico = "";
                           while(op != 3) {
                              menuMATRIZ();
                              std::cin >> op;
                              switch (op)
                              {
                              case 1:
                                 // MATRIZ POR CAPA INDIVIDUAL
                                  break;
                              case 2:  // MATRIZ COMPLETA
                                 break;
                              }
                           }
                        case 4:
                           op = 9;
                           grafico = "";
                           while(op != 4) {
                              system("cls");
                              std::cout << "/tMENU DE TRANSVERSAS" << std::endl;
                              std::cout << "1. Transversa En Orden" << std::endl;
                              std::cout << "2. Transversa Post Orden" << std::endl;
                              std::cout << "3. Transversa Pre Orden" << std::endl;
                              std::cout << "4. Salir" << std::endl;
                              std::cin >> op;
                              switch (op) {  // switch de reportes de transversas.
                                 case 1:
                                    grafico = "digraph G{\n rankdir=\"LR\"\n";
                                    graficar_arbol_InOrder(raiz, &grafico);
                                    grafico = grafico.substr(0, grafico.length() - 3);
                                    grafico += "}\n";
                                    archivoDOT.open("reportes\\inOrder.dot");
                                    archivoDOT << grafico << std::endl;
                                    archivoDOT.close();
                                    system("dot -Tpng reportes\\inOrder.dot -o reportes\\inOrder.png");
                                    system("reportes\\inOrder.png");
                                    break;
                                 case 2:
                                    grafico = "digraph G{\n rankdir=\"LR\"\n";
                                    graficar_arbol_PostOrder(raiz, &grafico);
                                    grafico = grafico.substr(0, grafico.length() - 3);
                                    grafico += "}\n";
                                    archivoDOT.open("reportes\\postOrder.dot");
                                    archivoDOT << grafico << std::endl;
                                    archivoDOT.close();
                                    system("dot -Tpng reportes\\postOrder.dot -o reportes\\postOrder.png");
                                    system("reportes\\postOrder.png");
                                    break;
                                 case 3:
                                    grafico = "digraph G{\n rankdir = \"LR\"";
                                    graficar_arbol_PreOrder(raiz, &grafico);
                                    grafico = grafico.substr(0, grafico.length() - 3);
                                    grafico += "}\n";
                                    archivoDOT.open("reportes\\preOrder.dot");
                                    archivoDOT << grafico << std::endl;
                                    archivoDOT.close();
                                    system("dot -Tpng reportes\\preOrder.dot -o reportes\\preOrder.png");
                                    system("reportes\\preOrder.png");
                                    break;
                                 default:
                                    break;
                              }
                           }
                           break;
                        default:
                           break;
                     }
                  }
               }else{
                  std::cout << "\n\n**SIN IMAGENES CARGADAS&&\n" << std::endl;
               }
               system("pause");
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
