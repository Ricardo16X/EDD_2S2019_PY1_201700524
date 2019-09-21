#include <iostream>
#include <string>
#include <fstream>

#include "crearImagen.h"
#include "ESTRUCTURAS.h"
#include "manejo_CSV.h"
#include "filtros.h"
#include "mensajitos.h"

void mensajeError();
void print(std::string);

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

   /*VARIABLE GLOBAL PARA EL USO DE FILTROS*/
   cubo *nuevoFiltro = 0;
   std::string nombreCapa = "";

   capa *copia = 0;
   capa *original = 0;

   int numeroFiltroCreado = 0;
   filtros *raizFiltros = 0;
   filtros *copia_filtro = 0;
   std::string nombreFiltro = "";
   cubo *cuboTemporal = 0;

   /*Variables para el collage*/
   int x = 0, y = 0;
   /*Variables para la modificacion de colores*/
   int rojo = 0, verde = 0, azul = 0;

   /*Men� Inicial*/
   int op = 0;
   while (op != 7)
   {
      menuINIT();
      try
      {
         std::cout << "\nESCOGE UNA OPCION: ";
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
               std::cout << "\t\t###  SELECTOR DE IMAGENES  ###" << std::endl;
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
                            << "\tSe ha elegido la imagen: " << elemento_paraTrabajo->nombre << std::endl;
                  std::cout << "\tInformacion de Imagen: " << std::endl;
                  std::cout << "\tANCHO IMAGEN : " << elemento_paraTrabajo->wImg << std::endl;
                  std::cout << "\tALTO IMAGEN : " << elemento_paraTrabajo->hImg << std::endl;
                  std::cout << "\tANCHO PIXEL : " << elemento_paraTrabajo->wPix << std::endl;
                  std::cout << "\tALTO PIXEL : " << elemento_paraTrabajo->hPix << std::endl
                            << std::endl;
                  if (raizFiltros != NULL)
                  {
                     borrarFiltros(raizFiltros);
                     raizFiltros = nullptr;
                     numeroFiltroCreado = 0;
                  }
               }
               else
               {
                  // UY UN ERRORCITO
                  std::cout << "\n###  HA OCURRIDO UN ERROR EN LA RECUPERACION DE LA IMAGEN  ###\n";
                  std::cout << "\n###  VERIFICA EL NOMBRE DE LA IMAGEN QUE SEA CORRECTO...  ###\n";
               }
            }
            system("pause");
            break;
         case 3: // Filtros TODO
            if (elemento_paraTrabajo != NULL)
            {
               op = 0;
               while (op != 5)
               {
                  menuFILTROS();
                  std::cout << "\tSELECCIONA UN FILTRO: ";
                  fflush(stdin);
                  std::cin >> op;
                  switch (op)
                  {
                  case 1: // NEGATIVO
                     op = 0;
                     while (op != 3)
                     {
                        menu_opcionFiltro();
                        std::cout << "\tSELECCIONA UN FILTRO: ";
                        fflush(stdin);
                        std::cin >> op;
                        switch (op)
                        {
                        case 1: // FILTRO COMPLETO NEGATIVO
                           nuevoFiltro = new cubo();
                           copiarCubo(elemento_paraTrabajo, nuevoFiltro);
                           // Filtro negativo Completo
                           original = elemento_paraTrabajo->primerCapa;
                           copia = nuevoFiltro->primerCapa;
                           while (original != NULL)
                           {
                              filtroNegativo(original, copia);
                              original = original->siguiente;
                              copia = copia->siguiente;
                           }
                           numeroFiltroCreado++;
                           registrarFiltro(raizFiltros, nuevoFiltro, std::to_string(numeroFiltroCreado) + ":Negativo");
                           break;
                        case 2: // FILTRO NEGATIVO POR CAPAS
                           nuevoFiltro = new cubo();
                           copiarCubo(elemento_paraTrabajo, nuevoFiltro);

                           mostrarCapas(elemento_paraTrabajo);
                           std::cout << "Escribe el nombre EXACTO de la capa: ";
                           fflush(stdin);
                           std::getline(std::cin, nombreCapa, '\n');
                           /*aqui solamente obtengo las capas de ambos cubos para modificarlos nada mas*/
                           if (obtenerCapa(elemento_paraTrabajo, nombreCapa) != NULL)
                           {
                              numeroFiltroCreado++;
                              filtroNegativo(obtenerCapa(elemento_paraTrabajo, nombreCapa), obtenerCapa(nuevoFiltro, nombreCapa));
                              registrarFiltro(raizFiltros, nuevoFiltro, std::to_string(numeroFiltroCreado) + ":Negativo:" + nombreCapa);
                           }
                           else
                           {
                              free(nuevoFiltro);
                              std::cout << "El nombre de la capa esta incorrecto, repite el proceso..." << std::endl;
                              system("pause");
                           }
                           break;
                        case 3:
                           break;
                        default:
                           mensajeError();
                           break;
                        }
                     }
                     break;
                  case 2: // GRAYSCALE
                     op = 0;
                     while (op != 3)
                     {
                        menu_opcionFiltro();
                        fflush(stdin);
                        std::cin >> op;
                        switch (op)
                        {
                        case 1:
                           /* Filtro grayscale completo */
                           nuevoFiltro = new cubo();
                           copiarCubo(elemento_paraTrabajo, nuevoFiltro);
                           // Filtro negativo Completo
                           original = elemento_paraTrabajo->primerCapa;
                           copia = nuevoFiltro->primerCapa;
                           while (original != NULL)
                           {
                              filtroGrayScale(original, copia);
                              original = original->siguiente;
                              copia = copia->siguiente;
                           }
                           numeroFiltroCreado++;
                           registrarFiltro(raizFiltros, nuevoFiltro, std::to_string(numeroFiltroCreado) + ":Grayscale");
                           break;
                        case 2:
                           /*Filtro grayscale por capas*/
                           nuevoFiltro = new cubo();
                           copiarCubo(elemento_paraTrabajo, nuevoFiltro);
                           mostrarCapas(elemento_paraTrabajo);
                           std::cout << "Escribe el nombre EXACTO de la capa: ";
                           fflush(stdin);
                           std::getline(std::cin, nombreCapa, '\n');
                           /*aqui solamente obtengo las capas de ambos cubos para modificarlos nada mas*/
                           if (obtenerCapa(elemento_paraTrabajo, nombreCapa) != NULL)
                           {
                              numeroFiltroCreado++;
                              filtroGrayScale(obtenerCapa(elemento_paraTrabajo, nombreCapa), obtenerCapa(nuevoFiltro, nombreCapa));
                              registrarFiltro(raizFiltros, nuevoFiltro, std::to_string(numeroFiltroCreado) + ":Grayscale:" + nombreCapa);
                           }
                           else
                           {
                              free(nuevoFiltro);
                              std::cout << "El nombre de la capa esta incorrecto, repite el proceso" << std::endl;
                              system("pause");
                           }
                           break;
                        default:
                           mensajeError();
                           break;
                        }
                     }
                     break;
                  case 3: // MIRROR
                     op = 0;
                     while (op != 4)
                     {
                        menuFiltrosMirror();
                        std::cout << "Elige una opcion : ";
                        fflush(stdin);
                        std::cin >> op;
                        switch (op)
                        {
                        case 1: // Mirror Eje X
                           op = 0;
                           while (op != 3)
                           {
                              menu_opcionFiltro();
                              std::cout << "Elige una opcion: ";
                              fflush(stdin);
                              std::cin >> op;
                              switch (op)
                              {
                              case 1: // Mirror Eje X a imagen completa
                                 nuevoFiltro = new cubo();
                                 filtro_ejeX(elemento_paraTrabajo, nuevoFiltro);
                                 numeroFiltroCreado++;
                                 registrarFiltro(raizFiltros, nuevoFiltro, std::to_string(numeroFiltroCreado) + ":XMirror" );
                                 break;
                              case 2: // Mirror Eje X a capa individual
                                 nuevoFiltro = new cubo();
                                 copiarCubo(elemento_paraTrabajo, nuevoFiltro);
                                 mostrarCapas(elemento_paraTrabajo);
                                 std::cout << "Escribe el nombre EXACTO de la capa: ";
                                 fflush(stdin);
                                 std::getline(std::cin, nombreCapa, '\n');
                                 /*aqui solamente obtengo las capas de ambos cubos para modificarlos nada mas*/
                                 if (obtenerCapa(elemento_paraTrabajo, nombreCapa) != NULL)
                                 {
                                    numeroFiltroCreado++;
                                    filtro_ejeX_capa(obtenerCapa(elemento_paraTrabajo, nombreCapa), obtenerCapa(nuevoFiltro, nombreCapa));
                                    registrarFiltro(raizFiltros, nuevoFiltro, std::to_string(numeroFiltroCreado) + ":XMirror:" + nombreCapa );
                                 }
                                 else
                                 {
                                    free(nuevoFiltro);
                                    std::cout << "El nombre de la capa esta incorrecto, repite el proceso" << std::endl;
                                    system("pause");
                                 }
                                 break;
                              case 3:
                                 break;
                              default:
                                 mensajeError();
                                 break;
                              }
                           }
                           break;
                        case 2: // Mirror Eje Y
                           op = 0;
                           while (op != 3)
                           {
                              menu_opcionFiltro();
                              std::cout << "Elige una opcion: ";
                              fflush(stdin);
                              std::cin >> op;
                              switch (op)
                              {
                              case 1: // Mirror Eje Y imagen completa
                                 nuevoFiltro = new cubo();
                                 filtro_ejeY(elemento_paraTrabajo, nuevoFiltro);
                                 numeroFiltroCreado++;
                                 registrarFiltro(raizFiltros, nuevoFiltro, std::to_string(numeroFiltroCreado) + ":YMirror");
                                 break;
                              case 2: // Mirror Eje Y a capa
                                 nuevoFiltro = new cubo();
                                 copiarCubo(elemento_paraTrabajo, nuevoFiltro);
                                 mostrarCapas(elemento_paraTrabajo);
                                 std::cout << "Escribe el nombre EXACTO de la capa: ";
                                 fflush(stdin);
                                 std::getline(std::cin, nombreCapa, '\n');
                                 /*aqui solamente obtengo las capas de ambos cubos para modificarlos nada mas*/
                                 if (obtenerCapa(elemento_paraTrabajo, nombreCapa) != NULL)
                                 {
                                    numeroFiltroCreado++;
                                    filtro_ejeY_capa(obtenerCapa(elemento_paraTrabajo, nombreCapa), obtenerCapa(nuevoFiltro, nombreCapa));
                                    registrarFiltro(raizFiltros, nuevoFiltro, std::to_string(numeroFiltroCreado) + ":YMirror:" + nombreCapa);
                                 }
                                 else
                                 {
                                    free(nuevoFiltro);
                                    std::cout << "El nombre de la capa esta incorrecto, repite el proceso" << std::endl;
                                    system("pause");
                                 }
                                 break;
                              case 3:
                                 break;
                              default:
                                 mensajeError();
                                 break;
                              }
                           }
                           break;
                        case 3: // Mirror Eje X; Eje Y
                           op = 0;
                           while (op != 3)
                           {
                              menu_opcionFiltro();
                              std::cout << "Elige una opcion: ";
                              fflush(stdin);
                              std::cin >> op;
                              switch (op)
                              {
                              case 1: // Mirror a imagen completa
                                 nuevoFiltro = new cubo();
                                 mirror_EjeX_EjeY(elemento_paraTrabajo, nuevoFiltro);
                                 numeroFiltroCreado++;
                                 registrarFiltro(raizFiltros, nuevoFiltro, std::to_string(numeroFiltroCreado) +  ":Mirror");
                                 break;
                              case 2: // Mirror a capa n
                                 nuevoFiltro = new cubo();
                                 copiarCubo(elemento_paraTrabajo, nuevoFiltro);
                                 mostrarCapas(elemento_paraTrabajo);
                                 std::cout << "Escribe el nombre EXACTO de la capa: ";
                                 fflush(stdin);
                                 std::getline(std::cin, nombreCapa, '\n');
                                 /*aqui solamente obtengo las capas de ambos cubos para modificarlos nada mas*/
                                 if (obtenerCapa(elemento_paraTrabajo, nombreCapa) != NULL)
                                 {
                                    numeroFiltroCreado++;
                                    mirror_capa(obtenerCapa(elemento_paraTrabajo, nombreCapa), obtenerCapa(nuevoFiltro, nombreCapa));
                                    registrarFiltro(raizFiltros, nuevoFiltro, std::to_string(numeroFiltroCreado) + ":Mirror:" + nombreCapa);
                                 }
                                 else
                                 {
                                    free(nuevoFiltro);
                                    std::cout << "El nombre de la capa esta incorrecto, repite el proceso" << std::endl;
                                    system("pause");
                                 }
                                 break;
                              case 3:
                                 break;
                              default:
                                 mensajeError();
                                 break;
                              }
                           }
                           break;
                        case 4: // Salida del while
                           break;
                        default:
                           mensajeError();
                           break;
                        }
                     }
                     break;
                  case 4: // COLLAGE
                     system("cls");
                     try
                     {
                        print("Ingrese el numero de repeticiones en X");
                        fflush(stdin);
                        std::cin >> x;
                        if (x <= 0)
                        {
                           x = 1;
                        }
                        print("Ingrese el numero de repeticiones en Y");
                        fflush(stdin);
                        std::cin >> y;
                        if (x <= 0)
                        {
                           x = 1;
                        }
                        nuevoFiltro = new cubo();
                        if (x == 1 && y == 1)
                        {
                           copiarCubo(elemento_paraTrabajo, nuevoFiltro);
                           numeroFiltroCreado++;
                           registrarFiltro(raizFiltros, nuevoFiltro, "\t" + std::to_string(numeroFiltroCreado) + ". Collage");
                        }
                        else if(x > 1 && y > 1)
                        {
                           collage(elemento_paraTrabajo, nuevoFiltro, x, y);
                           numeroFiltroCreado++;
                           registrarFiltro(raizFiltros, nuevoFiltro, "\t" + std::to_string(numeroFiltroCreado) + ". Collage");
                        }else{
                           print("Solo acepto valores mayores a 0");
                           system("pause");
                        }
                     }
                     catch (const std::exception &e)
                     {
                        std::cerr << e.what() << '\n';
                        mensajeError();
                     }
                     break;
                  case 5:
                  break;
                  default:
                     mensajeError();
                     break;
                  }
               }
            }
            else
            {
               std::cout << "###  SIN IMAGEN CARGADA  ###" << std::endl;
               system("pause");
            }
            break;
         case 4: // Edicion Manual
            system("cls");
            if (elemento_paraTrabajo == NULL)
            {
               print("NO HAY IMAGEN SELECCIONADA");
               system("pause");
            }
            else
            {
               op = 0;
               while (op != 3)
               {
                  print("\t###  EDICION MANUAL  ###");
                  print("1. Imagen Original");
                  print("2. Filtros");
                  print("3. Salir");
                  std::cout << "Elige una opcion: ";
                  fflush(stdin);
                  std::cin >> op;
                  switch (op)
                  {
                  case 1:
                     capaGraficada = 0;
                     mostrarCapas(elemento_paraTrabajo);
                     print("Ingrese el nombre de la capa: ");
                     fflush(stdin);
                     std::getline(std::cin, nombreCapa, '\n');
                     capaGraficada = obtenerCapa(elemento_paraTrabajo, nombreCapa);
                     if (capaGraficada != NULL)
                     {
                        print("");
                        print("Ingrese el valor de la coordenada X: ");
                        fflush(stdin);
                        std::cin >> x;
                        print("Ingrese el valor de la coordenada Y: ");
                        fflush(stdin);
                        std::cin >> y;
                        print("Ingrese un valor para Rojo (0-255): ");
                        fflush(stdin);
                        std::cin >> rojo;
                        print("Ingrese un valor para Verde (0-255): ");
                        fflush(stdin);
                        std::cin >> verde;
                        print("Ingrese un valor para Azul (0-255): ");
                        fflush(stdin);
                        std::cin >> azul;
                        modificar(x, y, capaGraficada, rojo, azul, verde);
                     }
                     else
                     {
                        print("NO ENCONTRE LA CAPA SELECCIONADA " + nombreCapa);
                        system("pause");
                     }
                     break;
                  case 2:
                     capaGraficada = 0;
                     mostrarFiltros(raizFiltros);
                     print("Ingrese el nombre del filtro: ");
                     fflush(stdin);
                     std::getline(std::cin, nombreFiltro, '\n');
                     copia_filtro = obtenerFiltro(raizFiltros, nombreFiltro);
                     if (copia_filtro != NULL)
                     {
                        mostrarCapas(copia_filtro->imagen);
                        print("Escriba el nombre de la capa a modificar: ");
                        fflush(stdin);
                        std::getline(std::cin, nombreCapa, '\n');
                        capaGraficada = obtenerCapa(copia_filtro->imagen, nombreCapa);
                        if (capaGraficada != NULL)
                        {
                           print("");
                           print("Ingrese el valor de la coordenada X: ");
                           fflush(stdin);
                           std::cin >> x;
                           print("ingrese el valor de la coordenada Y: ");
                           fflush(stdin);
                           std::cin >> y;
                           print("Ingrese un valor para Rojo (0-255): ");
                           fflush(stdin);
                           std::cin >> rojo;
                           print("Ingrese un valor para Verde (0-255): ");
                           fflush(stdin);
                           std::cin >> verde;
                           print("Ingrese un valor para Azul (0-255): ");
                           fflush(stdin);
                           std::cin >> azul;
                           if (x > 0 && y > 0 && rojo >= 0 && rojo <= 255 && verde >= 0 && verde <= 255 && azul >= 0 && azul <= 255)
                           {
                              modificar(x, y, capaGraficada, rojo, azul, verde);
                           }else{
                              print("Verifica que las coordenadas y los colores sean valores mayores a 0");
                              print("Verifica que los colores tengan un valor menor o igual a 255");
                              system("pause");
                           }
                        }
                        else
                        {
                           print("NO ENCONTRE LA CAPA SELECCIONADA " + nombreCapa);
                           system("pause");
                        }
                     }
                     break;
                  case 3:
                     // Salir
                     break;
                  default:
                     mensajeError();
                     break;
                  }
               }
            }
            break;
         case 5: // Exportar Imagen
            if (elemento_paraTrabajo == NULL)
            {
               system("cls");
               std::cout << "NO HAY IMAGEN SELECCIONADA" << std::endl;
               system("pause");
            }
            else
            {
               if (raizFiltros == NULL)
               {
                  generarImagen(elemento_paraTrabajo);
               }
               else
               {
                  op = 0;
                  while (op != 3)
                  {
                     system("cls");
                     std::cout << "EXPORTAR IMAGEN---\n";
                     std::cout << "1. ORIGINAL\n";
                     std::cout << "2. FILTROS\n";
                     std::cout << "3. Salir\n";
                     std::cout << "Elige una opcion: ";
                     fflush(stdin);
                     std::cin >> op;
                     filtros *imagen = 0;
                     switch (op)
                     {
                     case 1:
                        generarImagen(elemento_paraTrabajo);
                        break;
                     case 2:
                        if (raizFiltros != NULL)
                        {
                           std::cout << "\tEXPORTAR FILTRO\n";
                           mostrarFiltros(raizFiltros);
                           std::cout << "ESCRIBE EL NOMBRE COMPLETO DEL FILTRO: ";
                           fflush(stdin);
                           std::getline(std::cin, nombreArchivo, '\n');
                           imagen = obtenerFiltro(raizFiltros, nombreArchivo);
                           if (imagen != NULL)
                           {
                              generarImagen(imagen->imagen);
                           }
                           else
                           {
                              std::cout << "VUELVE A ESCRIBIR EL NOMBRE DEL FILTRO...\n";
                              system("pause");
                           }
                        }
                        else
                        {
                           std::cout << "NO HAS APLICADO NINGUN FILTRO DISPONIBLE" << std::endl;
                           system("pause");
                        }
                        break;
                     case 3:
                        break;
                     default:
                        break;
                     }
                  }
               }
            }
            break;
         case 6: // REPORTES
            if (raiz != NULL)
            {
               op = 1;
               while (op != 0)
               {
                  try
                  {
                     menuREPORTS();
                     fflush(stdin);
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
                              op = 0;
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
                              std::cout << "\n###  HA OCURRIDO UN ERROR EN LA RECUPERACION DE LA IMAGEN  ###\n";
                              std::cout << "\n###  VERIFICA EL NOMBRE DE LA IMAGEN QUE SEA CORRECTO...  ###\n";
                           }
                        }
                        break;
                     case 3: // 3. LINEAR MATRIX REPORT
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
                                          fflush(stdin);
                                          scanf("%i", &op);
                                          switch (op)
                                          {
                                          case 1:
                                             grafica_linealColumn(capaGraficada);
                                             break;
                                          case 2: //Grafica Lineal Row
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
                                 }
                                 else
                                 {
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
                              std::cout << "\t\t###  MENU DE TRANSVERSAS  ###" << std::endl;
                              std::cout << "\t1. Transversa En Orden" << std::endl;
                              std::cout << "\t2. Transversa Post Orden" << std::endl;
                              std::cout << "\t3. Transversa Pre Orden" << std::endl;
                              std::cout << "\t4. Salir" << std::endl;
                              fflush(stdin);
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
                              case 4:
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
                        op = 0;
                        while (op != 3)
                        {
                           system("cls");
                           print("\t###  TIPO DE REPORTE  ###");
                           std::cout << "1. Reporte Todos los Filtros Aplicados" << std::endl;
                           std::cout << "2. Reporte de filtro Invidual" << std::endl;
                           std::cout << "3. Regresar....\n";
                           std::cout << "Elige una opcion: ";
                           fflush(stdin);
                           std::cin >> op;
                           switch (op)
                           {
                           case 1:
                              graficarFiltros(raizFiltros);
                              break;
                           case 2:
                              system("cls");
                              mostrarFiltros(raizFiltros);
                              std::cout << "INGRESA EL NOMBRE COMPLETO DEL FILTRO APLICADO: ";
                              fflush(stdin);
                              std::getline(std::cin, nombreFiltro, '\n');
                              if (obtenerFiltro(raizFiltros, nombreFiltro) != NULL)
                              {
                                 /*PREGUNTAR SI LO QUIERE COMPLETO O POR CAPAS*/
                                 op = 0;
                                 while (op != 3)
                                 {
                                    system("cls");
                                    print("\t###  MODO DE REPORTE DE FILTRO  ###");
                                    std::cout << "1. Imagen Completa" << std::endl;
                                    std::cout << "2. Por capas" << std::endl;
                                    std::cout << "3. Salir" << std::endl;
                                    std::cout << "Escoge una opcion: ";
                                    fflush(stdin);
                                    std::cin >> op;
                                    switch (op)
                                    {
                                    case 1: // GRAFICAR FILTRO COMPLETO
                                       temp = obtenerFiltro(raizFiltros, nombreFiltro)->imagen->primerCapa;
                                       while (temp != NULL)
                                       {
                                          graficar_capaIndividual(temp);
                                          temp = temp->siguiente;
                                       }
                                       break;
                                    case 2: // GRAFICAR FILTRO POR CAPAS
                                       cuboTemporal = obtenerFiltro(raizFiltros, nombreFiltro)->imagen;
                                       mostrarCapas(cuboTemporal);
                                       std::cout << "INGRESA EL NOMBRE COMPLETO DE LA CAPA --> ";
                                       fflush(stdin);
                                       std::getline(std::cin, nombreCapa, '\n');
                                       if (obtenerCapa(cuboTemporal, nombreCapa) != NULL)
                                       {
                                          graficar_capaIndividual(obtenerCapa(cuboTemporal, nombreCapa));
                                       }
                                       else
                                       {
                                          std::cout << "\nNO ENCUENTRO UNA CAPA QUE SE LLAME DE ESTA MANERA " << nombreCapa << std::endl;
                                          system("pause");
                                       }
                                       break;
                                    case 3:
                                       break;
                                    default:
                                       mensajeError();
                                       break;
                                    }
                                 }
                              }
                              break;
                           default:
                              mensajeError();
                              break;
                           }
                        }
                        break;
                     case 0:
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
   std::cout << "\t\nHa ocurrido una operacion incorrecta\n";
   std::cin.clear();
   std::cin.ignore(1000, '\n');
   system("pause");
}

void print(std::string message)
{
   std::cout << message << std::endl;
}
