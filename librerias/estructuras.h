#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

/*  Definición de Estructuras   */
struct elementoCabecera {
  // Valores de estructura
  std::string color;
  int fila;
  // apuntadores
  elementoCabecera *sig_elementoCabecera;
};

struct cabecera {
  // datos
  int column;
  // apuntadores
  elementoCabecera *primerElementoCabecera = new elementoCabecera();
  cabecera *sigCabecera;
};

struct capa {
  std::string nombreCapa;
  cabecera *primer_Cabecera = new cabecera();
  // apuntadores
  capa *sigCapa;
};

struct cubo {
  // datos del cubo
  std::string nombre;
  int wImg, hImg;
  int wPix, hPix;
  // enlace a la primera capa
  capa *primerCapa = new capa();
  // punteros para arbol binario
  cubo *izq_Cubo;
  cubo *der_Cubo;
} * primerCubito;

/*Definición de métodos*/
/*Arbol*/
void agregarCubo(cubo *, cubo *);
void desplegarImagenes(cubo);
/*Lista Simple*/
void agregarCapa(cubo *, capa *);
void agregarCabecera(capa *, cabecera *);
void agregarFila(cabecera *, elementoCabecera *);

/*Estructura de árbol para el manejo del cubo*/
void agregarCubo(cubo *raizArbol, cubo *nuevoCubo) {
  if (nuevoCubo->nombre.compare(raizArbol->nombre) <
      0) {  // Si el nombre de la nueva imagen es < al de la raiz, se coloca a
            // la izquierda de la raiz.
    agregarCubo(raizArbol->izq_Cubo, nuevoCubo);
  } else if (nuevoCubo->nombre.compare(raizArbol->nombre) >
             0) {  // Si el nombre de la nueva imagen es > al de la raiz, se
                   // coloca a la derecha de la raiz.
    agregarCubo(raizArbol->der_Cubo, nuevoCubo);
  } else if (raizArbol ==
             NULL) {  // Si se llega al punto en dónde el nodo del arbol no
                      // apunta a nada, allí se colocará la nueva imagen.
    if (primerCubito == NULL) {
      primerCubito = nuevoCubo;
    }
    raizArbol = nuevoCubo;
  }
}

void desplegarImagenes(cubo *raizArbol) {
  // In Order
  if (raizArbol != NULL) {
    desplegarImagenes(raizArbol->izq_Cubo);
    std::cout << "* " << raizArbol->nombre << " " << std::endl;
    desplegarImagenes(raizArbol->der_Cubo);
  }
}

/*Agregar capas al cubo actual*/
void agregarCapa(cubo *cubito, capa *capita) {
  if (cubito->primerCapa == NULL) {
    cubito->primerCapa = capita;
  } else {
    capa *temp = cubito->primerCapa;
    while (temp->sigCapa != NULL) {
      temp = temp->sigCapa;
    }
    temp->sigCapa = capita;
  }
}

capa obtenerCapa(cubo *cubito, std::string nombreCapa){
  capa *temp = cubito->primerCapa;
  while (temp->sigCapa != NULL && temp->nombreCapa != nombreCapa)
  {
    temp = temp->sigCapa;
  }
  return *temp;
}

/*Agregar cabecera a capa*/
void agregarCabecera(capa *capita, cabecera *cabecera_chiquita) {
  if (capita->primer_Cabecera == NULL) {
    capita->primer_Cabecera = cabecera_chiquita;
  } else {
    cabecera *temp = capita->primer_Cabecera;
    while(temp->sigCabecera != NULL){
      temp = temp->sigCabecera;
    }
    temp = cabecera_chiquita;
  }
}

/*Agregar un elemento de fila a la cabecera hecha*/
void agregarFila(cabecera *cabecera_chiquita, elementoCabecera *elemento){
  if (cabecera_chiquita->primerElementoCabecera == NULL)
  {
    cabecera_chiquita->primerElementoCabecera = elemento;
  }else{
    elementoCabecera *temp = cabecera_chiquita->primerElementoCabecera;
    while (temp->sig_elementoCabecera != NULL)
    {
      temp = temp->sig_elementoCabecera;
    }
    temp = elemento;
  }
}