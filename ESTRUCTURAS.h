#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

/**LISTA DE FILAS DE CABECERAS**/
struct elementoCabecera {
   // Valores de estructura
   std::string color;
   int fila;
   // apuntadores
   elementoCabecera *siguiente = 0;
   elementoCabecera(std::string _color, int _fila) {
      color = _color;
      fila = _fila;
   }
   elementoCabecera() {
   }
};
/**LISTA DE CABECERAS**/
struct cabecera {
   // datos
   int column;
   elementoCabecera *primerElementoCabecera = 0;
   // apuntadores
   cabecera *siguiente = 0;
   cabecera(int _column) {
      column = _column;
   }
   cabecera() {
   }
};
/**LISTA DE CAPAS**/
struct capa {
   std::string nombreCapa;
   cabecera *primer_Cabecera = 0;
   // apuntadores
   capa *siguiente = 0;
   capa(std::string _nombreCapa) {
      nombreCapa = _nombreCapa;
   }
   capa() {
   }
};
/**ARBOL DE CUBOS**/
struct cubo {
   // datos del cubo
   std::string nombre = "";
   std::string ruta = "";
   int wImg = 0, hImg = 0;
   int wPix = 0, hPix = 0;
   // enlace a la primera capa
   capa *primerCapa = 0;
   // punteros para arbol binario
   cubo *izq_Cubo = 0;
   cubo *der_Cubo = 0;
   cubo(std::string _nombre, int _wImg, int _hImg, int _wPix, int _hPix) {
      nombre = _nombre;
      wImg = _wImg;
      hImg = _hImg;
      wPix = _wPix;
      hPix = _hPix;
   }
   cubo() {
   }
};
typedef struct cubo* ARBOL;

/**VARIABLES GLOBALES**/
bool repetido = true;

/************************************************/
void graficarExtra(ARBOL raiz, std::string* dotArchivo);

/**MÉTODOS PARA EL MANEJO DE ARBOL DE LOS CUBOS**/
void insertar(ARBOL &arbol, ARBOL nuevoCubo) {
   // Mostrar los nombres de ambos archivos para ver cual es cual.

   if (arbol == NULL) {
      // Si se llega al punto en dónde el nodo del arbol no
      // apunta a nada, allí se colocará la nueva imagen.
      arbol = nuevoCubo;
      std::cout << "\nIMAGEN " << nuevoCubo->nombre << " INSERTADA CORRECTAMENTE\n" << std::endl;
   } else if (nuevoCubo->nombre.compare(arbol->nombre) < 0) {
      // Si el nombre de la nueva imagen es < al de la raiz, se coloca a
      // la izquierda de la raiz.
      insertar(arbol->izq_Cubo, nuevoCubo);
   } else if (nuevoCubo->nombre.compare(arbol->nombre) > 0) {
      // Si el nombre de la nueva imagen es > al de la raiz, se
      // coloca a la derecha de la raiz.
      insertar(arbol->der_Cubo, nuevoCubo);
   }
}

void desplegarImagenes(ARBOL raizArbol) {
   // In Order
   if (raizArbol != NULL) {
      desplegarImagenes(raizArbol->izq_Cubo);
      std::cout << "* " << raizArbol->nombre << " " << std::endl;
      desplegarImagenes(raizArbol->der_Cubo);
   }
}

ARBOL obtenerCopia(ARBOL &raiz, std::string nombre) {
   ARBOL temporal = 0;
   if(raiz == NULL)
      return temporal;
   if(raiz->nombre.compare(nombre) == 0) {
      temporal = raiz;
      return temporal;
   }
   if(raiz->izq_Cubo != NULL) {
      temporal = obtenerCopia(raiz->izq_Cubo, nombre);
      if (temporal != NULL)
         return temporal;
   }
   if(raiz->der_Cubo != NULL) {
      temporal = obtenerCopia(raiz->der_Cubo, nombre);
      if (temporal != NULL)
         return temporal;
   }
   return temporal;
}

void graficar_arbol_General(ARBOL raizArbol) {
   std::string dot = "digraph G{\n";
   graficarExtra(raizArbol, &dot);
   dot += "}";
   // Alli iría la ruta donde se encuentra el cubo para generar allí todas las imágenes X necesarias.
   // para los repotes.
   std::ofstream archivoDOT("reportes\\archivo.dot");
   archivoDOT << dot << std::endl;
   archivoDOT.close();
   system("dot -Tpng reportes\\archivo.dot -o reportes\\Arbol_Cubos.png");
   system("reportes\\Arbol_Cubos.png");
}

void graficarExtra(ARBOL raiz, std::string* dotArchivo) {
   if(raiz != NULL) {
      /**VARIABLES PARA CONCATENARLAS EN *dotArchivo**/
      std::string ANCHOIMAGEN = std::to_string(raiz->wImg);
      std::string ALTOIMAGEN = std::to_string(raiz->hImg);
      std::string ANCHOPIXEL = std::to_string(raiz->wPix);
      std::string ALTOPIXEL = std::to_string(raiz->hPix);
      *dotArchivo += "nodo" + raiz->nombre +  "[label = \"  " + raiz->nombre + "\\n Dimensiones: \\nAncho Imagen: " + ANCHOIMAGEN + "\\nAlto Imagen: " + ALTOIMAGEN + "\\nDimensiones Pixel:\\nAncho Pixel: " + ANCHOPIXEL + "\\nAlto Pixel: " + ALTOPIXEL + " \"];\n";
      graficarExtra(raiz->izq_Cubo, dotArchivo);
      graficarExtra(raiz->der_Cubo, dotArchivo);

      if (raiz->izq_Cubo != NULL) {
         *dotArchivo += "\"nodo" + raiz->nombre + "\" -> \"nodo" + raiz->izq_Cubo->nombre + "\";\n";
      }
      if(raiz->der_Cubo != NULL) {
         *dotArchivo += "\"nodo" + raiz->nombre + "\" -> \"nodo" + raiz->der_Cubo->nombre + "\";\n";
      }
   }
}

void graficar_arbol_PreOrder(ARBOL raizArbol, std::string* dotArchivo) {   //FUNCIONA BIEN
   if(raizArbol != NULL) {
      *dotArchivo += "\"" + raizArbol->nombre + "\" -> ";
      graficar_arbol_PreOrder(raizArbol->izq_Cubo, dotArchivo);
      graficar_arbol_PreOrder(raizArbol->der_Cubo, dotArchivo);
   }
}

void graficar_arbol_InOrder(ARBOL raizArbol, std::string* dotArchivo) {    //FUNCIONA BIEN
   if(raizArbol != NULL) {
      graficar_arbol_PreOrder(raizArbol->izq_Cubo, dotArchivo);
      *dotArchivo += "\"" + raizArbol->nombre + "\" -> ";
      graficar_arbol_PreOrder(raizArbol->der_Cubo, dotArchivo);
   }
}

void graficar_arbol_PostOrder(ARBOL raizArbol, std::string* dotArchivo) {
   if(raizArbol != NULL) {
      graficar_arbol_PreOrder(raizArbol->izq_Cubo, dotArchivo);
      graficar_arbol_PreOrder(raizArbol->der_Cubo, dotArchivo);
      *dotArchivo += "\"" + raizArbol->nombre + "\" -> ";
   }
}

bool noExiste(ARBOL raiz, std::string comparado) {
   if(raiz != NULL) {
      if(comparado.compare(raiz->nombre) == 0) {
         repetido = false;
         return false;
      } else {
         repetido = true;
      }
      noExiste(raiz->izq_Cubo, comparado);
      noExiste(raiz->der_Cubo, comparado);
   }
   return repetido;
}

/**MÉTODOS PARA EL MANEJO DE LA LISTA DE CAPAS DEL CUBO**/
void agregarCapa(cubo *cubito, capa *capita) {
   if (cubito->primerCapa == NULL) {
      cubito->primerCapa = capita;
   } else {
      capa *temp = cubito->primerCapa;
      while (temp->siguiente != NULL) {
         temp = temp->siguiente;
      }
      temp->siguiente = capita;
   }
}

capa* obtenerCapa(cubo *cubito, std::string nombreCapa) {
   capa *temp = cubito->primerCapa;
   while (temp->siguiente != NULL && temp->nombreCapa != nombreCapa) {
      temp = temp->siguiente;
   }
   return temp;
}

void graficar_capaIndividual(capa* capita) {
   std::string rank_same_columnas = "";
   std::string rank_same_filas = "";
   // Variables auxiliares
   std::string identificador = "";
   std::string identificadorContenido = "";
   std::string antiguoIdentificador = "";
   std::string antiguoIdentificadorContenido = "";

   std::string dot = "digraph G{\n rankdir=TB;\n node[shape=record];\n graph[nodesep=0.6];\n";
   dot += "CAPA[label=\"" + capita->nombreCapa + "\"];\n";
   identificador = "CAPA";
   // la variable ranksame solo me servirá para colocarlo de ultimo al .dot para posicionar a la misma altura
   // anchura todas las demas variables a crear.
   rank_same_columnas = "{rank=same; CAPA ";

   /**RECORRIDO DE COLUMNAS VERTICALES**/
   cabecera* columnas = capita->primer_Cabecera;
   elementoCabecera* filas;

   while(columnas != NULL) {
      /*AGREGO UNA NUEVA COLUMNA AL RANK_SAME_COLUMNAS*/
      rank_same_columnas += "C" + std::to_string(columnas->column) + " ";
      /*LA COLUMNA ACTUAL SERÁ LA COLUMNA ANTIGUA*/
      antiguoIdentificador = identificador;
      /*SE CREA UN NUEVO IDENTIFICADOR DE COLUMNA*/
      identificador = "C" + std::to_string(columnas->column);
      /*AHORA COLOCAMOS ESE IDENTIFICADOR EN EL .DOT*/
      dot+= identificador + "[label=\""+ identificador  +"\"];\n";
      /*AHORA NUESTRO IDENTIFICADOR ANTIGUO >"APUNTARA"> NUEVO IDENTIFICADOR PARA EL MOMENTO DE COLOCARLO
      EN NUESTRO .DOT*/
      dot+= antiguoIdentificador + "--" + identificador + "[dir=both];\n";
      // ESTE PASO SOLO ME VERIFICA QUE LA VARIABLE FILAS APUNTE AL INICIO DE LA CABECERA QUE PUEDE SER
      // LA PRIMER CELDA SIN IMPORTAR SI TIENE COLOR O NO.
      filas = columnas->primerElementoCabecera;
      // ANTES DE INICIAR POR LAS FILAS, COMIENZA UNA COLUMNA, ENTONCES
      // ESE SERÁ MI PUNTO DE INICIO CON LAS COMPARACIONES DE FILAS
      identificadorContenido = identificador;
      while(filas != NULL) {
         if(!((filas->color.compare("x") == 0) || (filas->color.compare("X") == 0))) {
            antiguoIdentificadorContenido = identificadorContenido;
            identificadorContenido = "C" + std::to_string(columnas->column) + "F" + std::to_string(filas->fila);
            dot += identificadorContenido + "[label=\"" + filas->color  + "\"];\n";
            dot += antiguoIdentificadorContenido + "--" + identificadorContenido + "[dir=both];\n";
         }
         filas = filas->siguiente;
      }
      columnas = columnas->siguiente;
   }
   rank_same_columnas += "}\n";

   /**RECORRIDO DE FILA HORIZONTAL**/
   int filaStop = 1;
   identificador = "CAPA";
   bool salir = true;

   while(salir) { // Me indicará cuando salir, media vez alcance el punto máximo de filas permitidas.
      columnas = capita->primer_Cabecera;
      /**SEGUIRÉ LA MISMA DINÁMICA DE COMO SI ESTUVIERA RECORRIENDO EN VERTICAL**/
      antiguoIdentificador = identificador;
      identificador = "F" + std::to_string(filaStop);
      dot += identificador + "[label=\"" + identificador  + "\"];\n";
      /*MODIFICANDO MI RANK_SAME_FILAS PARA QUE CASEN LOS VALORES Y ASÍ PUEDA ESTAR ORDENADO AL MOMENTO DE GRAFICAR*/
      rank_same_filas += "{rank=same; " + identificador;
      identificadorContenido = identificador;
      while(columnas != NULL) {  // Recorreré todas las columnas en busca del valor distinto de X en la fila N
         filas = columnas->primerElementoCabecera;
         while(filas != NULL) {  // Recorreré hasta la fila n de stop
            if(filas->fila == filaStop) { // Si he llegado a la fila actual, entonces procederé a evaluar el valor en dicha columna y fila.
               // Conectar el punto anterior, con el actual...
               if(!((filas->color.compare("x") == 0) || (filas->color.compare("X") == 0))) {
                  antiguoIdentificadorContenido = identificadorContenido;
                  identificadorContenido = "C" + std::to_string(columnas->column) + "F" + std::to_string(filas->fila);
                  rank_same_filas += identificadorContenido + " ";
                  dot += antiguoIdentificadorContenido + "--" + identificadorContenido + "[dir=both];\n";
               }
               break;
            }
            filas = filas->siguiente;
         }
         columnas = columnas->siguiente;
      }
      if(filas->siguiente != NULL) {
         /**AL MOMENTO DE ACABAR LOS ENLACES DE LAS FILAS, ENTONCES CIERRO EL RANK_SAME_FILAS PARA QUE SOLO ME QUEDEN SEPARADAS
         LAS FILAS QUE DESEO GRAFICAR.**/
         filaStop++;
      } else {
         salir = false;
      }
      rank_same_filas += "}\n";
   }

   dot += rank_same_columnas;
   dot += rank_same_filas;
   dot += "}\n";
   /**PRUEBA DE SYSTEM**/
   std::ofstream archivoDOT("reportes\\"+capita->nombreCapa+".dot");
   archivoDOT << dot << std::endl;
   archivoDOT.close();
   /**CONVERSION ENTRE CONST CHAR Y STD::STRING**/
   std::string temp = "dot -Tpng reportes\\"  + capita->nombreCapa  +  ".dot -o reportes\\"+capita->nombreCapa+".png";
   std::string rutaOpen = "reportes\\"+capita->nombreCapa+".png";
   const char* c = temp.c_str();
   const char* open = rutaOpen.c_str();
   system(c);
   system(open);
}

void mostrarCapas(ARBOL cubo){
   capa* temp = cubo->primerCapa;
   while(temp!=NULL){
      std::cout << "*" << temp->nombreCapa << std::endl;
      temp = temp->siguiente;
   }
}
/**MÉTODOS PARA EL MANEJO DE LA LISTA DE CABECERAS DE LA CAPA**/
void agregarCabecera(capa *capita, cabecera *cabecera_chiquita) {
   if (capita->primer_Cabecera == NULL) {
      capita->primer_Cabecera = cabecera_chiquita;
   } else {
      cabecera *temp = capita->primer_Cabecera;
      while(temp->siguiente != NULL) {
         temp = temp->siguiente;
      }
      temp->siguiente = cabecera_chiquita;
   }
}

cabecera* obtenerCabecera(capa* capita, int numeroCabecera) {
   cabecera* temporal = capita->primer_Cabecera;
   while(temporal != NULL) {
      if(temporal->column == numeroCabecera) {
         break;
      }
      temporal = temporal->siguiente;
   }
   return temporal;
}

/**MÉTODOS PARA EL MANEJO DE LA LISTA DE FILAS DE LA CABECERA**/
void agregarFila(cabecera *cabecera_chiquita, elementoCabecera *elemento) {
   if (cabecera_chiquita->primerElementoCabecera == NULL) {
      cabecera_chiquita->primerElementoCabecera = elemento;
   } else {
      elementoCabecera *temp = cabecera_chiquita->primerElementoCabecera;
      while (temp->siguiente != NULL) {
         temp = temp->siguiente;
      }
      temp->siguiente = elemento;
   }
}


#endif // ESTRUCTURAS_H_INCLUDED
