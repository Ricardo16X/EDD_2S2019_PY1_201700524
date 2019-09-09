#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

/**LISTA DE FILAS DE CABECERAS**/
struct elementoCabecera
{
    // Valores de estructura
    std::string color;
    int fila;
    // apuntadores
    elementoCabecera *siguiente = 0;
    elementoCabecera(std::string _color, int _fila)
    {
        color = _color;
        fila = _fila;
    }
    elementoCabecera()
    {
    }
};
/**LISTA DE CABECERAS**/
struct cabecera
{
    // datos
    int column;
    elementoCabecera *primerElementoCabecera = 0;
    // apuntadores
    cabecera *siguiente = 0;
    cabecera(int _column)
    {
        column = _column;
    }
    cabecera()
    {
    }
};
/**LISTA DE CAPAS**/
struct capa
{
    std::string nombreCapa;
    cabecera *primer_Cabecera = 0;
    // apuntadores
    capa *siguiente = 0;
    capa(std::string _nombreCapa)
    {
        nombreCapa = _nombreCapa;
    }
    capa()
    {
    }
};
/**ARBOL DE CUBOS**/
struct cubo
{
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
    cubo(std::string _nombre, int _wImg, int _hImg, int _wPix, int _hPix)
    {
        nombre = _nombre;
        wImg = _wImg;
        hImg = _hImg;
        wPix = _wPix;
        hPix = _hPix;
    }
    cubo()
    {
    }
};
typedef struct cubo* ARBOL;


/************************************************/
void graficarExtra(ARBOL raiz, std::string* dotArchivo);

/**M�TODOS PARA EL MANEJO DE ARBOL DE LOS CUBOS**/
void insertar(ARBOL &arbol, ARBOL nuevoCubo)
{
    // Mostrar los nombres de ambos archivos para ver cual es cual.

    if (arbol == NULL)
    {
        // Si se llega al punto en d�nde el nodo del arbol no
        // apunta a nada, all� se colocar� la nueva imagen.
        arbol = nuevoCubo;
    }
    else if (nuevoCubo->nombre.compare(arbol->nombre) < 0)
    {
        // Si el nombre de la nueva imagen es < al de la raiz, se coloca a
        // la izquierda de la raiz.
        insertar(arbol->izq_Cubo, nuevoCubo);
    }
    else if (nuevoCubo->nombre.compare(arbol->nombre) > 0)
    {
        // Si el nombre de la nueva imagen es > al de la raiz, se
        // coloca a la derecha de la raiz.
        insertar(arbol->der_Cubo, nuevoCubo);
    }
}

void desplegarImagenes(ARBOL raizArbol)
{
    // In Order
    if (raizArbol != NULL)
    {
        desplegarImagenes(raizArbol->izq_Cubo);
        std::cout << "* " << raizArbol->nombre << " " << std::endl;
        desplegarImagenes(raizArbol->der_Cubo);
    }
}

ARBOL obtenerCopia(ARBOL &raiz, std::string nombre){
    ARBOL temporal = 0;
    if(raiz == NULL) return temporal;
    if(raiz->nombre.compare(nombre) == 0){
        temporal = raiz;
        return temporal;
    }
    if(raiz->izq_Cubo != NULL){
        temporal = obtenerCopia(raiz->izq_Cubo, nombre);
        if (temporal != NULL) return temporal;
    }
    if(raiz->der_Cubo != NULL){
        temporal = obtenerCopia(raiz->der_Cubo, nombre);
        if (temporal != NULL) return temporal;
    }
    return temporal;
}

void graficar_arbol_General(ARBOL raizArbol){
    std::string dot = "digraph G{\n\n node [shape = ellipse, height = 0.1];\n splines=\"line\";\n\n";
    graficarExtra(raizArbol, &dot);
    dot += "}";
    // Alli ir�a la ruta donde se encuentra el cubo para generar all� todas las im�genes X necesarias.
    // para los repotes.
    std::ofstream archivoDOT("archivo.dot");
    archivoDOT << dot << std::endl;
    archivoDOT.close();
    system("dot -Tpng archivo.dot -o Arbol_Cubos.png");
    //system("nohup display \\graphviz_result\\Arbol_Cubos.png &" );
}

void graficarExtra(ARBOL raiz, std::string* dotArchivo){
    if(raiz != NULL){
        *dotArchivo += "nodo" + raiz->nombre + "[label = \" <f2>|<f1> " + raiz->nombre + " |<f0> \"];\n";
        graficarExtra(raiz->izq_Cubo, dotArchivo);
        graficarExtra(raiz->der_Cubo, dotArchivo);

        if (raiz->izq_Cubo != NULL){
            *dotArchivo += "\"nodo" + raiz->nombre + "\":f2 -> \"nodo" + raiz->izq_Cubo->nombre + "\":f1;\n";
        }
        if(raiz->der_Cubo != NULL){
            *dotArchivo += "\"nodo" + raiz->nombre + "\":f0 -> \"nodo" + raiz->der_Cubo->nombre + "\":f1;\n";
        }
    }
}

void graficar_arbol_PreOrder(ARBOL raizArbol){

}

void graficar_arbol_InOrder(ARBOL raizArbol){

}

void graficar_arbol_PostOrder(ARBOL raizArbol){

}
/**M�TODOS PARA EL MANEJO DE LA LISTA DE CAPAS DEL CUBO**/
void agregarCapa(cubo *cubito, capa *capita)
{
    if (cubito->primerCapa == NULL)
    {
        cubito->primerCapa = capita;
    }
    else
    {
        capa *temp = cubito->primerCapa;
        while (temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = capita;
    }
}
capa* obtenerCapa(cubo *cubito, std::string nombreCapa)
{
    capa *temp = cubito->primerCapa;
    while (temp->siguiente != NULL && temp->nombreCapa != nombreCapa)
    {
        temp = temp->siguiente;
    }
    return temp;
}

/**M�TODOS PARA EL MANEJO DE LA LISTA DE CABECERAS DE LA CAPA**/
void agregarCabecera(capa *capita, cabecera *cabecera_chiquita)
{
    if (capita->primer_Cabecera == NULL)
    {
        capita->primer_Cabecera = cabecera_chiquita;
    }
    else
    {
        cabecera *temp = capita->primer_Cabecera;
        while(temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = cabecera_chiquita;
    }
}
cabecera* obtenerCabecera(capa* capita, int numeroCabecera)
{
    cabecera* temporal = capita->primer_Cabecera;
    while(temporal != NULL)
    {
        if(temporal->column == numeroCabecera)
        {
            break;
        }
        temporal = temporal->siguiente;
    }
    return temporal;
}
/**M�TODOS PARA EL MANEJO DE LA LISTA DE FILAS DE LA CABECERA**/
void agregarFila(cabecera *cabecera_chiquita, elementoCabecera *elemento)
{
    if (cabecera_chiquita->primerElementoCabecera == NULL)
    {
        cabecera_chiquita->primerElementoCabecera = elemento;
    }
    else
    {
        elementoCabecera *temp = cabecera_chiquita->primerElementoCabecera;
        while (temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = elemento;
    }
}
#endif // ESTRUCTURAS_H_INCLUDED