#include <iostream>
#include <string>
#include <fstream>

#include "ESTRUCTURAS.h"
#include "manejo_CSV.h"
#include "mensajitos.h"

void mensajeError();

int main(int argc, char const *argv[])
{
   /*Variables a utilizar globalmente en el main.*/
   ARBOL raiz = 0;
   cubo *nuevoElemento;
   cubo *elemento_paraTrabajo = 0;

   cubo *reporteMatrices = 0;
   capa *capaGraficada = 0;

   capa *temp = 0;

   std::string nombreArchivo = ""; // Nombre general del archivo.
   std::string grafico = "";

   std::ofstream archivoDOT;
   /*Men� Inicial*/
   int op = 0;
   while (op != 7)
   {
      menuINIT();
      try
      {
         fflush(stdin);
         scanf("%i", &op);
         switch (op)
         {
         case 1: // INSERCION DE IMAGENES
            system("cls");
            std::cout << " Ingrese el nombre del archivo con extension '.csv' \n";
            std::cout << " Asegurese que: " << std::endl;
            std::cout << " La carpeta se llame igual al archivo de carga inicial. >>> ";
            fflush(stdin);
            std::cin >> nombreArchivo;
            nuevoElemento = new cubo();
            nuevoElemento = leerArchivo(nombreArchivo.substr(0, nombreArchivo.length() - 4));
            /*Ya que en el paso anterior tengo el nuevo cubo recien creado,
               proceder� a almacenarlo en el arbol*/
            if (nuevoElemento != NULL && noExiste(raiz, nuevoElemento->nombre))
            {
               insertar(raiz, nuevoElemento);
            }
            else
            {
               std::cout << "No he encontrado ninguna carpeta/archivo.csv con el nombre " << nombreArchivo;
               std::cout << std::endl;
               std::cout << "O quizas ya haya una imagen cargada, con el mismo nombre." << std::endl;
            }
            system("pause");
            break;
         case 2: // SELECCION DE IMAGENES
            if (raiz == NULL)
            {
               system("cls");
               std::cout << "\tNo hay elementos para mostrar !!!" << std::endl;
            }
            else
            {
               system("cls");
               elemento_paraTrabajo = 0;
               std::cout << "\tSELECTOR DE IMAGENES" << std::endl;
               desplegarImagenes(raiz);
               std::cout << "\tINGRESA EL NOMBRE EXACTO DE LA IMAGEN: ";
               fflush(stdin);
               std::cin >> nombreArchivo;
               // Aqui pondr� el m�todo que me devolver� el cubo con el cual pretendo trabajar
               // en los pasos 3, 4, 5;
               elemento_paraTrabajo = obtenerCopia(raiz, nombreArchivo);
               if (elemento_paraTrabajo != NULL)
               {
                  std::cout << std::endl
                            << "Se ha elegido la imagen: " << elemento_paraTrabajo->nombre << std::endl;
                  std::cout << "Informacion de Imagen: " << std::endl;
                  std::cout << "ANCHO IMAGEN : " << elemento_paraTrabajo->wImg << std::endl;
                  std::cout << "ALTO IMAGEN : " << elemento_paraTrabajo->hImg << std::endl;
                  std::cout << "ANCHO PIXEL : " << elemento_paraTrabajo->wPix << std::endl;
                  std::cout << "ALTO PIXEL : " << elemento_paraTrabajo->hPix << std::endl
                            << std::endl;
               }
               else
               {
                  // UY UN ERRORCITO
                  std::cout << "\n***HA OCURRIDO UN ERROR EN LA RECUPERACION DE LA IMAGEN&&&\n";
                  std::cout << "\n***VERIFICA EL NOMBRE DE LA IMAGEN QUE SEA CORRECTO...&&&\n";
               }
            }
            system("pause");
            break;
         case 3: // Filtros TODO
            if (elemento_paraTrabajo != NULL)
            {
               /**MENU DE FILTROS**/
               menuFILTROS();
            }
            else
            {
               std::cout << "**SIN IMAGEN CARGADA&&" << std::endl;
            }
            system("pause");
            break;
         case 4: // Edicion Manual TODO
            break;
         case 5: // Exportar Imagen TODO
            break;
         case 6: // REPORTES
            if (raiz != NULL)
            {
               while (op != 0)
               {
                  try
                  {
                     menuREPORTS();
                     scanf("%i", &op);
                     switch (op)
                     {
                     case 1: // 1. IMPORTED IMAGES
                        graficar_arbol_General(raiz);
                        break;
                     case 2: // 2. IMAGE LAYER REPORT
                        reporteMatrices = 0;
                        while (reporteMatrices == NULL)
                        {
                           system("cls");
                           std::cout << "\tSELECTOR DE IMAGENES" << std::endl;
                           desplegarImagenes(raiz);
                           std::cout << "\tINGRESA EL NOMBRE EXACTO DE LA IMAGEN: ";
                           fflush(stdin);
                           std::cin >> nombreArchivo;
                           reporteMatrices = obtenerCopia(raiz, nombreArchivo);
                           if (reporteMatrices != NULL)
                           {
                              op = 1;
                              while (op != 3)
                              {
                                 try
                                 {
                                    system("cls");
                                    std::cout << std::endl
                                              << std::endl;
                                    std::cout << ":::ELIGE UNA OPCION:::" << std::endl;
                                    std::cout << "1. REPORTE POR CAPA INDIVIDUAL" << std::endl;
                                    std::cout << "2. REPORTE DE IMAGEN COMPLETO" << std::endl;
                                    std::cout << "3. SALIR" << std::endl;
                                    fflush(stdin);
                                    scanf("%i", &op);
                                    switch (op)
                                    {
                                    case 1: // REPORTE CAPA INDIVIDUAL
                                       system("cls");
                                       mostrarCapas(reporteMatrices);
                                       std::cout << "Por favor, ingresa el nombre exacto de la capa" << std::endl;
                                       fflush(stdin);
                                       std::cin >> nombreArchivo;
                                       capaGraficada = obtenerCapa(reporteMatrices, nombreArchivo);
                                       if (capaGraficada != NULL)
                                       {
                                          graficar_capaIndividual(capaGraficada);
                                       }
                                       else
                                       {
                                          std::cout << "____NOMBRE INEXISTENTE___" << std::endl;
                                       }
                                       break;
                                    case 2: // REPORTE DE CUBO COMPLETO
                                       temp = reporteMatrices->primerCapa;
                                       while (temp != NULL)
                                       {
                                          graficar_capaIndividual(temp);
                                          temp = temp->siguiente;
                                       }
                                       break;
                                       case 3:
                                       break;
                                    default:
                                       mensajeError();
                                       break;
                                    }
                                 }
                                 catch (const std::exception &e)
                                 {
                                    std::cerr << e.what() << '\n';
                                    mensajeError();
                                 }
                              }
                           }
                           else
                           {
                              // UY UN ERRORCITO
                              std::cout << "\n***HA OCURRIDO UN ERROR EN LA RECUPERACION DE LA IMAGEN&&&\n";
                              std::cout << "\n***VERIFICA EL NOMBRE DE LA IMAGEN QUE SEA CORRECTO...&&&\n";
                           }
                        }
                        break;
                     case 3: // 3. LINEAR MATRIX REPORT *IMPLEMENTAR
                        reporteMatrices = 0;
                        while (reporteMatrices == NULL)
                        {
                           system("cls");
                           std::cout << "\tSELECTOR DE IMAGENES" << std::endl;
                           desplegarImagenes(raiz);
                           std::cout << "\tINGRESA EL NOMBRE EXACTO DE LA IMAGEN: ";
                           std::cin >> nombreArchivo;
                           reporteMatrices = obtenerCopia(raiz, nombreArchivo);
                           if (reporteMatrices != NULL)
                           {
                              capaGraficada = 0;
                              while (capaGraficada == 0)
                              {
                                 std::cout << "\n\n";
                                 mostrarCapas(reporteMatrices);
                                 std::cout << "Por favor, ingresa el nombre exacto de la capa" << std::endl;
                                 fflush(stdin);
                                 std::cin >> nombreArchivo;
                                 capaGraficada = obtenerCapa(reporteMatrices, nombreArchivo);
                                 if (capaGraficada != NULL)
                                 {
                                    op = 0;
                                    try
                                    {
                                       while (op != 3)
                                       {
                                          system("cls");
                                          std::cout << "\tESCOGE UNA OPERACION" << std::endl;
                                          std::cout << "1. LINEALIZAR POR COLUMNA" << std::endl;
                                          std::cout << "2. LINEALIZAR POR FILA" << std::endl;
                                          std::cout << "3. SALIR" << std::endl;
                                          scanf("%i", &op);
                                          switch (op)
                                          {
                                          case 1:
                                             grafica_linealColumn(capaGraficada);
                                             break;
                                          case 2: //Grafica Lineal Row TODO
                                             grafica_linealRow(capaGraficada);
                                             break;
                                             case 3:
                                             break;
                                          default:
                                             mensajeError();
                                             break;
                                          }
                                       }
                                       op = 0;
                                    }
                                    catch (const std::exception &e)
                                    {
                                       std::cerr << e.what() << '\n';
                                       mensajeError();
                                    }
                                 }else{
                                    std::cout << "VUELVA A ESCRIBIR EL NOMBRE DE LA CAPA " << std::endl;
                                    system("pause");
                                 }
                              }
                           }
                           else
                           {
                              // UY UN ERRORCITO
                              std::cout << "\n***HA OCURRIDO UN ERROR EN LA RECUPERACION DE LA IMAGEN&&&\n";
                              std::cout << "\n***VERIFICA EL NOMBRE DE LA IMAGEN QUE SEA CORRECTO...&&&\n";
                              system("pause");
                           }
                        }
                        break;
                     case 4: // 4. TRAVERSAL REPORT
                        try
                        {
                           grafico = "";
                           op = 0;
                           while (op != 4)
                           {
                              system("cls");
                              std::cout << "\tMENU DE TRANSVERSAS" << std::endl;
                              std::cout << "1. Transversa En Orden" << std::endl;
                              std::cout << "2. Transversa Post Orden" << std::endl;
                              std::cout << "3. Transversa Pre Orden" << std::endl;
                              std::cout << "4. Salir" << std::endl;
                              std::cin >> op;
                              switch (op)
                              { // switch de reportes de transversas.
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
                                 mensajeError();
                                 break;
                              }
                           }
                        }
                        catch (const std::exception &e)
                        {
                           std::cerr << e.what() << '\n';
                           mensajeError();
                        }
                        break;
                     case 5: // 5. FILTER REPORT
                        break;
                     default:
                        mensajeError();
                        break;
                     }
                  }
                  catch (const std::exception &e)
                  {
                     std::cerr << e.what() << '\n';
                     mensajeError();
                  }
               }
            }
            else
            {
               std::cout << "\n\n**SIN IMAGENES CARGADAS&&\n"
                         << std::endl;
            }
            system("pause");
            break;
         case 7: // Salir
            system("cls");
            std::cout << "\n\n#########################################"
                      << std::endl;
            std::cout << "#\tPHOTOGEN++ - 201700524\t\t#" << std::endl;
            std::cout << "#########################################\n\n"
                      << std::endl;
            system("pause");
            break;
         default:
            mensajeError();
            break;
         }
      }
      catch (const std::exception &e)
      {
         mensajeError();
         op = 0;
      }
   }
   return 0;
}

void mensajeError()
{
   std::cout << "\t\nOpcion Incorrecta, Elige una opcion del menu.\n";
   std::cin.clear();
   std::cin.ignore(1000, '\n');
   system("pause");
}
