#ifndef FILTROS_H_INCLUDED
#define FILTROS_H_INCLUDED

#include "ESTRUCTURAS.h"

struct filtros
{
    std::string nombre = "";
    cubo *imagen = 0;

    filtros *siguiente = 0;
    filtros *anterior = 0;
} *primero = 0, *ultimo = 0;

void filtroNegativo(capa *original, capa *nuevoFiltro);
void filtroGrayScale(capa *original, capa *nuevoFiltro);
std::string RGBNegativo(std::string colorRGB);
std::string RGBGrayScale(std::string colorRGB);

void filtroNegativo(capa *original, capa *nuevoFiltro)
{
    cabecera *temp_cab = original->primer_Cabecera;
    cabecera* temp_copia = nuevoFiltro->primer_Cabecera;

    elementoCabecera *colorNegativo = 0;
    elementoCabecera* copiaColor = 0;
    
    while (temp_cab != NULL)    // temp_cab contiene la cabecera original que se copiará...
    {
        colorNegativo = temp_cab->primerElementoCabecera;
        copiaColor = temp_copia->primerElementoCabecera;
        while (colorNegativo != NULL)
        {
            if (!((colorNegativo->color.compare("x") == 0) || (colorNegativo->color.compare("X") == 0) || (colorNegativo->color.compare("") == 0)))
            {
                copiaColor->color = RGBNegativo(colorNegativo->color);
                copiaColor->fila = colorNegativo->fila;
            }
            colorNegativo = colorNegativo->siguiente;
            copiaColor = copiaColor->siguiente;
        }
        temp_cab = temp_cab->siguiente;
        temp_copia = temp_copia->siguiente;
    }
}

void filtroGrayScale(capa *original, capa *nuevoFiltro)
{
    cabecera *temp_cab = original->primer_Cabecera;
    cabecera* temp_copia = nuevoFiltro->primer_Cabecera;

    elementoCabecera *colorGris = 0;
    elementoCabecera* tempColor = 0;
    while (temp_cab != NULL)
    {
        colorGris = temp_cab->primerElementoCabecera;   // original
        tempColor = temp_copia->primerElementoCabecera; // copia
        while (colorGris != NULL)
        {
            if (!((colorGris->color.compare("x") == 0) || (colorGris->color.compare("X") == 0) || (colorGris->color.compare("") == 0)))
            {
                tempColor->color = RGBNegativo(colorGris->color);
                tempColor->fila = colorGris->fila;
            }
            colorGris = colorGris->siguiente;
            tempColor = tempColor->siguiente;
        }
        temp_cab = temp_cab->siguiente;
        temp_copia = temp_copia->siguiente;
    }
}

/*Convertidor de color RGB normal a su equivalencia en Negativo*/
std::string RGBNegativo(std::string colorRGB)
{
    std::string s = colorRGB;
    std::string delim = "-";
    std::string negativo = "";

    auto inicio = 0U;
    auto fin = s.find(delim);
    int color = 0;
    while (fin != std::string::npos)
    {
        color = std::stoi(s.substr(inicio, fin - inicio));
        negativo += std::to_string(255 - color) + "-";

        inicio = fin + delim.length();
        fin = s.find(delim, inicio);
    }
    color = std::stoi(s.substr(inicio, fin - inicio));
    negativo += std::to_string(255 - color);

    return negativo;
}

/*Convertidor de color RGB normal a su equivalencia en Gris*/
std::string RGBGrayScale(std::string colorRGB)
{
    std::string s = colorRGB;
    std::string delim = "-";
    std::string grayScale = "";
    int colores[3];
    auto inicio = 0U;
    auto fin = s.find(delim);
    int color = 0;
    while (fin != std::string::npos)
    {
        colores[color] = std::stoi(s.substr(inicio, fin - inicio));

        inicio = fin + delim.length();
        fin = s.find(delim, inicio);
        color++;
    }
    colores[2] = std::stoi(s.substr(inicio, fin - inicio));
    color = colores[0] * 0.3 + colores[1] * 0.59 + colores[2] * 0.11 + 1;
    grayScale = std::to_string(color) + "-" + std::to_string(color) + "-" + std::to_string(color);
    return grayScale;
}

void registrarFiltro(cubo *nuevo, std::string modo){
    filtros* registro = new filtros();
    if (primero == NULL)
    {
        registro->imagen = nuevo;
        registro->nombre = modo;
        primero = ultimo = registro;
        ultimo->siguiente = primero;
        primero->anterior = ultimo;
    }else{
        ultimo->siguiente = registro;
        registro->anterior = ultimo;
        ultimo = registro;
        ultimo->siguiente = primero;
    }
}

void graficarFiltros(){
    filtros* temp = primero;
    std::string dot = "digraph G{\n";
    dot += "rankdir = LR;\n";
    dot += "node [shape=record];\n";
    int numeroNodo = 1;
    do
    {
        dot += "n" + std::to_string(numeroNodo) + "[shape=record, label=\"{" + temp->nombre + "}\"]\n";
        numeroNodo++;
        temp = temp->siguiente;
    } while (temp != primero);

    numeroNodo--;
    int i = 1;
    /*RELACIONES*/
    dot += "n1 -> n" + std::to_string(numeroNodo) + "\n";
    dot += "n" + std::to_string(numeroNodo) + " -> n1\n";

    while (i < numeroNodo)
    {
        dot += "n" + std::to_string(i) + " -> n" + std::to_string(i + 1) + " \n";
        dot += "n" + std::to_string(i + 1) + " -> n" + std::to_string(i) + " \n";
        i++;
    }
    dot += "}\n";

    std::ofstream archivoDOT("reportes\\reporteFiltros.dot");
    archivoDOT << dot;
    archivoDOT.close();
    system("dot -Tpng reporteFiltros.dot -o reporteFiltros.png");
    system("reporteFiltros.png");
}

/*este metodo solo me servirá para copiar el contenido de un cubo a otro.*/
void copiarCubo(cubo* original, cubo* copia){
    capa* capita = original->primerCapa;

    copia->wImg = original->wImg;
    copia->hImg = original->hImg;
    copia->wPix = original->wPix;
    copia->hPix = original->hPix;
    copia->ruta = original->ruta;

    cabecera* columna = 0;

    elementoCabecera* fila = 0;
    /*ELEMENTOS NUEVOS*/
    while (capita != NULL)  //  Comenzamos con las capas de la imagen.
    {
        columna = capita->primer_Cabecera;
        capa* nuevaCapa = new capa();
        nuevaCapa->nombreCapa = capita->nombreCapa;
        nuevaCapa->numeroCapa = capita->numeroCapa;
        while (columna != NULL) //  Comenzamos con las columnas de las capas
        {
            fila = columna->primerElementoCabecera;
            cabecera* nuevaColumna = new cabecera();
            nuevaColumna->column = columna->column;

            while (fila != NULL)    // Comenzamos con las filas de las columnas.
            {
                elementoCabecera* nuevaFila = new elementoCabecera();
                nuevaFila->color = fila->color;
                nuevaFila->fila = fila->fila;

                agregarFila(nuevaColumna, nuevaFila);
                fila = fila->siguiente;
            }

            agregarCabecera(nuevaCapa, nuevaColumna);
            columna = columna->siguiente;
        }
        agregarCapa(copia, nuevaCapa);
        capita = capita->siguiente;
    }
}

#endif // FILTROS_H_INCLUDED
