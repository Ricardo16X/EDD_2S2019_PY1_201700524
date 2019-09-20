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
void fila_PILA(cabecera *cabecera_copia, elementoCabecera *nuevo);
void columna_PILA(capa *capa_copia, cabecera *nuevo);

void filtroNegativo(capa *original, capa *nuevoFiltro)
{
    cabecera *temp_cab = original->primer_Cabecera;
    cabecera *temp_copia = nuevoFiltro->primer_Cabecera;

    elementoCabecera *colorNegativo = 0;
    elementoCabecera *copiaColor = 0;

    while (temp_cab != NULL) // temp_cab contiene la cabecera original que se copiará...
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
    cabecera *temp_copia = nuevoFiltro->primer_Cabecera;

    elementoCabecera *colorGris = 0;
    elementoCabecera *tempColor = 0;
    while (temp_cab != NULL)
    {
        colorGris = temp_cab->primerElementoCabecera;   // original
        tempColor = temp_copia->primerElementoCabecera; // copia
        while (colorGris != NULL)
        {
            if (!((colorGris->color.compare("x") == 0) || (colorGris->color.compare("X") == 0) || (colorGris->color.compare("") == 0)))
            {
                tempColor->color = RGBGrayScale(colorGris->color);
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
        if (color <= 255)
        {
            negativo += std::to_string(255 - color) + "-";
        }else{
            negativo += std::to_string(0) + "-";
        }
        inicio = fin + delim.length();
        fin = s.find(delim, inicio);
    }
    color = std::stoi(s.substr(inicio, fin - inicio));
    if (color <= 255)
    {
        negativo += std::to_string(255 - color);
    }else{
        negativo += std::to_string(0);
    }
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
    color = colores[0] * 0.3 + colores[1] * 0.59 + colores[2] * 0.11;
    std::cout << color << "\n";
    grayScale = std::to_string(color) + "-" + std::to_string(color) + "-" + std::to_string(color);
    return grayScale;
}

void registrarFiltro(filtros *&raiz, cubo *nuevo, std::string modo)
{
    filtros *nuevoFiltro = new filtros();
    nuevoFiltro->nombre = modo;
    nuevoFiltro->imagen = nuevo;
    if (raiz == 0)
    {
        nuevoFiltro->siguiente = nuevoFiltro;
        nuevoFiltro->anterior = nuevoFiltro;
        raiz = nuevoFiltro;
    }
    else
    {
        filtros *ultimo = raiz->anterior;
        ultimo->siguiente = nuevoFiltro;
        nuevoFiltro->anterior = ultimo;

        nuevoFiltro->siguiente = raiz;
        raiz->anterior = nuevoFiltro;
    }
}

void graficarFiltros(filtros *raiz)
{
    filtros *temp = raiz;
    std::string dot = "digraph G{\n";
    dot += "rankdir = LR;\n";
    dot += "node [shape=record];\n";
    int numeroNodo = 1;
    do
    {
        dot += "n" + std::to_string(numeroNodo) + "[shape=record, label=\"{" + temp->nombre + "}\"]\n";
        numeroNodo++;
        temp = temp->siguiente;
    } while (temp != raiz);

    numeroNodo--;
    int i = 1;
    /*RELACIONES*/
    dot += "n1 -> n" + std::to_string(numeroNodo) + " [constraint=false]\n";
    dot += "n" + std::to_string(numeroNodo) + " -> n1 [constraint=false]\n";

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
    system("dot -Tpng reportes\\reporteFiltros.dot -o reportes\\reporteFiltros.png");
    system("reportes\\reporteFiltros.png");
}

void mostrarFiltros(filtros *&raizFiltro)
{
    if (raizFiltro == 0)
    {
        std::cout << "SIN FILTROS APLICADOS" << std::endl;
        return;
    }
    else
    {
        filtros *temp = raizFiltro;
        do
        {
            std::cout << "\t* " << temp->nombre << std::endl;
            temp = temp->siguiente;
        } while (temp != raizFiltro);
    }
}

filtros *obtenerFiltro(filtros *raiz, std::string nombreFiltro)
{
    filtros *temp = raiz;
    filtros *retornado = 0;
    do
    {
        if (temp->nombre.compare(nombreFiltro) == 0)
        {
            retornado = temp;
            break;
        }
        temp = temp->siguiente;
    } while (temp != raiz);
    return retornado;
}

/*este metodo solo me servirá para copiar el contenido de un cubo a otro.*/
void copiarCubo(cubo *original, cubo *copia)
{
    capa *capita = original->primerCapa;

    copia->wImg = original->wImg;
    copia->hImg = original->hImg;
    copia->wPix = original->wPix;
    copia->hPix = original->hPix;
    copia->ruta = original->ruta;
    copia->nombre = original->nombre;

    cabecera *columna = 0;

    elementoCabecera *fila = 0;
    /*ELEMENTOS NUEVOS*/
    while (capita != NULL) //  Comenzamos con las capas de la imagen.
    {
        columna = capita->primer_Cabecera;
        capa *nuevaCapa = new capa();
        nuevaCapa->nombreCapa = capita->nombreCapa;
        nuevaCapa->numeroCapa = capita->numeroCapa;
        while (columna != NULL) //  Comenzamos con las columnas de las capas
        {
            fila = columna->primerElementoCabecera;
            cabecera *nuevaColumna = new cabecera();
            nuevaColumna->column = columna->column;

            while (fila != NULL) // Comenzamos con las filas de las columnas.
            {
                elementoCabecera *nuevaFila = new elementoCabecera();
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

/*FILTRO EJE X*/
/*Filtro eje X a cubo completo
que consistirá en insertar las columnas (cabeceras) en PILA*/
void filtro_ejeX(cubo *original, cubo *copia)
{
    capa *capita = original->primerCapa;

    copia->wImg = original->wImg;
    copia->hImg = original->hImg;
    copia->wPix = original->wPix;
    copia->hPix = original->hPix;
    copia->ruta = original->ruta;
    copia->nombre = original->nombre;

    cabecera *columna = 0;

    elementoCabecera *fila = 0;
    /*ELEMENTOS NUEVOS*/
    while (capita != NULL) //  Comenzamos con las capas de la imagen.
    {
        columna = capita->primer_Cabecera;
        capa *nuevaCapa = new capa();
        nuevaCapa->nombreCapa = capita->nombreCapa;
        nuevaCapa->numeroCapa = capita->numeroCapa;
        while (columna != NULL) //  Comenzamos con las columnas de las capas
        {
            fila = columna->primerElementoCabecera;
            cabecera *nuevaColumna = new cabecera();
            nuevaColumna->column = columna->column;

            while (fila != NULL) // Comenzamos con las filas de las columnas.
            {
                elementoCabecera *nuevaFila = new elementoCabecera();
                nuevaFila->color = fila->color;
                nuevaFila->fila = fila->fila;

                agregarFila(nuevaColumna, nuevaFila);
                fila = fila->siguiente;
            }

            columna_PILA(nuevaCapa, nuevaColumna);
            columna = columna->siguiente;
        }
        agregarCapa(copia, nuevaCapa);
        capita = capita->siguiente;
    }
}

void filtro_ejeX_capa(capa *original, capa *copia)
{
    /*PROCESO DE BORRADO DE CAPA*/
    cabecera *aux = 0;
    elementoCabecera *ec_aux = 0;
    while (copia->primer_Cabecera != NULL)
    {
        aux = copia->primer_Cabecera;
        ec_aux = aux->primerElementoCabecera;
        while (aux->primerElementoCabecera != NULL)
        {
            ec_aux = aux->primerElementoCabecera;
            aux->primerElementoCabecera = ec_aux->siguiente;
            delete ec_aux;
        }
        copia->primer_Cabecera = aux->siguiente;
        delete aux;
    }
    // Reinicio de la primera columna a 0
    copia->primer_Cabecera = nullptr;
    /*PROCESO DE LLENADO DE CAPA CON EL FILTRO APLICADO*/
    cabecera *columna = original->primer_Cabecera;
    elementoCabecera *fila = 0;
    while (columna != NULL) //  Comenzamos con las columnas de las capas
    {
        fila = columna->primerElementoCabecera;
        cabecera *nuevaColumna = new cabecera();
        nuevaColumna->column = columna->column;

        while (fila != NULL) // Comenzamos con las filas de las columnas.
        {
            elementoCabecera *nuevaFila = new elementoCabecera();
            nuevaFila->color = fila->color;
            nuevaFila->fila = fila->fila;

            agregarFila(nuevaColumna, nuevaFila);
            fila = fila->siguiente;
        }
        columna_PILA(copia, nuevaColumna);
        columna = columna->siguiente;
    }
}

void columna_PILA(capa *capa_copia, cabecera *nuevo)
{
    if (capa_copia->primer_Cabecera == NULL)
    {
        capa_copia->primer_Cabecera = nuevo;
    }
    else
    {
        /*EL NUEVO ELEMENTO APUNTA A primer_Cabecera*/
        // |1| -> null
        // (nuevo)2 -> (inicio)|1| -> null
        nuevo->siguiente = capa_copia->primer_Cabecera;
        // (inicio)|2| -> 1 -> null
        capa_copia->primer_Cabecera = nuevo;
    }
}
/*FILTRO EJE Y*/
/*Filtro eje y a cubo completo
que consistirá en insertar las filas (elementosCabecera) en PILA*/
void filtro_ejeY(cubo *original, cubo *copia)
{
    capa *capita = original->primerCapa;

    copia->wImg = original->wImg;
    copia->hImg = original->hImg;
    copia->wPix = original->wPix;
    copia->hPix = original->hPix;
    copia->ruta = original->ruta;
    copia->nombre = original->nombre;

    cabecera *columna = 0;

    elementoCabecera *fila = 0;
    /*ELEMENTOS NUEVOS*/
    while (capita != NULL) //  Comenzamos con las capas de la imagen.
    {
        columna = capita->primer_Cabecera;
        capa *nuevaCapa = new capa();
        nuevaCapa->nombreCapa = capita->nombreCapa;
        nuevaCapa->numeroCapa = capita->numeroCapa;
        while (columna != NULL) //  Comenzamos con las columnas de las capas
        {
            fila = columna->primerElementoCabecera;
            cabecera *nuevaColumna = new cabecera();
            nuevaColumna->column = columna->column;

            while (fila != NULL) // Comenzamos con las filas de las columnas.
            {
                elementoCabecera *nuevaFila = new elementoCabecera();
                nuevaFila->color = fila->color;
                nuevaFila->fila = fila->fila;

                fila_PILA(nuevaColumna, nuevaFila);
                fila = fila->siguiente;
            }

            agregarCabecera(nuevaCapa, nuevaColumna);
            columna = columna->siguiente;
        }
        agregarCapa(copia, nuevaCapa);
        capita = capita->siguiente;
    }
}

void fila_PILA(cabecera *columna_copia, elementoCabecera *nueva_fila)
{
    if (columna_copia->primerElementoCabecera == NULL)
    {
        columna_copia->primerElementoCabecera = nueva_fila;
    }
    else
    {
        /*EL NUEVO ELEMENTO APUNTA A primer_Cabecera*/
        // |1| -> null
        // (nuevo)2 -> (inicio)|1| -> null
        nueva_fila->siguiente = columna_copia->primerElementoCabecera;
        // (inicio)|2| -> 1 -> null
        columna_copia->primerElementoCabecera = nueva_fila;
    }
}

/*FILTRO EJE Y A CAPA*/
/*Este filtro consistirá en borrar toda la capa para luego
llenarlo nuevamente con los valores correspondientes.*/
void filtro_ejeY_capa(capa *original, capa *copia)
{
    /*PROCESO DE BORRADO DE CAPA*/
    cabecera *aux = 0;
    elementoCabecera *ec_aux = 0;
    while (copia->primer_Cabecera != NULL)
    {
        aux = copia->primer_Cabecera;
        ec_aux = aux->primerElementoCabecera;
        while (aux->primerElementoCabecera != NULL)
        {
            ec_aux = aux->primerElementoCabecera;
            aux->primerElementoCabecera = ec_aux->siguiente;
            delete ec_aux;
        }
        copia->primer_Cabecera = aux->siguiente;
        delete aux;
    }
    // Reinicio de la primera columna a 0
    copia->primer_Cabecera = nullptr;
    /*PROCESO DE LLENADO DE CAPA CON EL FILTRO APLICADO*/
    cabecera *columna = original->primer_Cabecera;
    elementoCabecera *fila = 0;
    while (columna != NULL) //  Comenzamos con las columnas de las capas
    {
        fila = columna->primerElementoCabecera; // Original
        cabecera *nuevaColumna = new cabecera();    // Copia
        nuevaColumna->column = columna->column;

        while (fila != NULL) // Comenzamos con las filas de las columnas originales.
        {
            elementoCabecera *nuevaFila = new elementoCabecera();
            nuevaFila->color = fila->color;
            nuevaFila->fila = fila->fila;

            fila_PILA(nuevaColumna, nuevaFila);
            fila = fila->siguiente;
        }
        agregarCabecera(copia, nuevaColumna);
        columna = columna->siguiente;
    }
}
/*FILTRO MIRROR COMPLETO*/
/*Filtro en ambos ejes a cubo completo
que consistirá en insertar las columnas en PILA
y también insertar las filas en PILA*/
void mirror_EjeX_EjeY(cubo *original, cubo *copia)
{
    capa *capita = original->primerCapa;

    copia->wImg = original->wImg;
    copia->hImg = original->hImg;
    copia->wPix = original->wPix;
    copia->hPix = original->hPix;
    copia->ruta = original->ruta;
    copia->nombre = original->nombre;

    cabecera *columna = 0;

    elementoCabecera *fila = 0;
    /*ELEMENTOS NUEVOS*/
    while (capita != NULL) //  Comenzamos con las capas de la imagen.
    {
        columna = capita->primer_Cabecera;
        capa *nuevaCapa = new capa();
        nuevaCapa->nombreCapa = capita->nombreCapa;
        nuevaCapa->numeroCapa = capita->numeroCapa;
        while (columna != NULL) //  Comenzamos con las columnas de las capas
        {
            fila = columna->primerElementoCabecera;
            cabecera *nuevaColumna = new cabecera();
            nuevaColumna->column = columna->column;

            while (fila != NULL) // Comenzamos con las filas de las columnas.
            {
                elementoCabecera *nuevaFila = new elementoCabecera();
                nuevaFila->color = fila->color;
                nuevaFila->fila = fila->fila;

                fila_PILA(nuevaColumna, nuevaFila);
                fila = fila->siguiente;
            }

            columna_PILA(nuevaCapa, nuevaColumna);
            columna = columna->siguiente;
        }
        agregarCapa(copia, nuevaCapa);
        capita = capita->siguiente;
    }
}

/*FILTRO MIRROR A CAPA*/
void mirror_capa(capa *original, capa *copia)
{
    /*PROCESO DE BORRADO DE CAPA*/
    cabecera *aux = 0;
    elementoCabecera *ec_aux = 0;
    while (copia->primer_Cabecera != NULL)
    {
        aux = copia->primer_Cabecera;
        ec_aux = aux->primerElementoCabecera;
        while (aux->primerElementoCabecera != NULL)
        {
            ec_aux = aux->primerElementoCabecera;
            aux->primerElementoCabecera = ec_aux->siguiente;
            delete ec_aux;
        }
        copia->primer_Cabecera = aux->siguiente;
        delete aux;
    }
    // Reinicio de la primera columna a 0
    copia->primer_Cabecera = nullptr;
    /*PROCESO DE LLENADO DE CAPA CON EL FILTRO APLICADO*/
    cabecera *columna = original->primer_Cabecera;
    elementoCabecera *fila = 0;
    while (columna != NULL) //  Comenzamos con las columnas de las capas
    {
        fila = columna->primerElementoCabecera;
        cabecera *nuevaColumna = new cabecera();
        nuevaColumna->column = columna->column;

        while (fila != NULL) // Comenzamos con las filas de las columnas.
        {
            elementoCabecera *nuevaFila = new elementoCabecera();
            nuevaFila->color = fila->color;
            nuevaFila->fila = fila->fila;

            fila_PILA(nuevaColumna, nuevaFila);
            fila = fila->siguiente;
        }
        columna_PILA(copia, nuevaColumna);
        columna = columna->siguiente;
    }
}

void borrarFiltros(filtros *raiz){
    raiz->anterior->siguiente = nullptr;
    raiz->anterior = nullptr;
    filtros* aux = 0;
    while (raiz != NULL)
    {
        aux = raiz;
        raiz = aux->siguiente;
        delete aux;
    }
    raiz = nullptr;
}

void collage(cubo* original, cubo* copia, int rep_columnas, int rep_filas){
    capa* copia_capa = original->primerCapa;
    cabecera* columna_copia = 0;
    elementoCabecera* fila_copia = 0;
    /*PASANDO INFORMACION DE CUBO A CUBO*/
    copia->wImg = original->wImg*rep_columnas;
    copia->hImg = original->hImg*rep_filas;
    copia->wPix = original->wPix;
    copia->hPix = original->hPix;
    copia->nombre = original->nombre;
    copia->ruta = original->ruta;


    /*Estas variables solo me servirán para poder incrementar "manualmente"
    El numero de fila de la nueva fila en el cubo copia.*/
    int index_fila = 0, index_columna = 0;
    capa* nuevaCapa = 0;
    while (copia_capa != NULL)
    {
        nuevaCapa = new capa();
        nuevaCapa->nombreCapa = copia_capa->nombreCapa;
        nuevaCapa->numeroCapa = copia_capa->numeroCapa;
        for (int i = 0; i < rep_columnas; i++) /*ESTE FOR ME AYUDARÁ A REALIZAR LAS REPETICIONES DE LAS COLUMNAS DE MI COLLAGE (EJE X)*/
        {
            columna_copia = copia_capa->primer_Cabecera;
            while (columna_copia != NULL)
            {
                cabecera* nuevaColumna = new cabecera();
                index_columna++;
                nuevaColumna->column = index_columna;
                for (int i = 0; i < rep_filas; i++) /*ESTE FOR ME AYUDARÁ A REALIZAR LAS REPETICIONES DE LAS FILAS DE MI COLLAGE (EJE Y)*/
                {   
                    fila_copia = columna_copia->primerElementoCabecera;
                    while (fila_copia != NULL)
                    {
                        elementoCabecera* nuevaFila = new elementoCabecera();
                        nuevaFila->color = fila_copia->color;
                        /*Aqui uso para el de fila*/
                        index_fila++;
                        nuevaFila->fila = index_fila;
                        
                        agregarFila(nuevaColumna, nuevaFila);

                        fila_copia = fila_copia->siguiente;
                    }
                }
                agregarCabecera(nuevaCapa, nuevaColumna);
                index_fila = 0;
                columna_copia = columna_copia->siguiente;
            }
        }
        agregarCapa(copia, nuevaCapa);
        index_columna = 0;
        copia_capa = copia_capa->siguiente;
    }
}

void modificar(int columna, int fila, cubo* &imagen)
{
    
}

#endif // FILTROS_H_INCLUDED
