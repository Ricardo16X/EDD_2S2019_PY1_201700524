#ifndef CREARIMAGEN_H_INCLUDED
#define CREARIMAGEN_H_INCLUDED

#include <iostream>
#include <string>
#include <algorithm>
#include "ESTRUCTURAS.h"

void generarImagen(cubo *);
int linealizacion(int fila, int columna, int ancho);
std::string rgb(std::string rgb_pre);

void generarImagen(cubo *imagen)
{
    std::string ruta = "exports\\" + imagen->nombre;
    std::string nombreCarpeta = "mkdir " + ruta;
    const char *carpeta = nombreCarpeta.c_str();
    // CREACION DE CARPETA
    system(carpeta);
    /*RECOPILACION DE INFORMACION PARA LA CREACION DEL HTML*/
    std::string html = "<!DOCTYPE html>\n";
    html += "<html>\n";
    html += "<head>\n";
    html += "<link rel=\"stylesheet\" href=\"" + imagen->nombre + ".css\">\n";
    html += "<title>" + imagen->nombre + "</title>\n";
    html += "</head>\n";
    html += "<body>\n";
    html += "<div class=\"canvas\">\n";
    /*Creacion de los diferentes pixeles*/
    int dimension = 0;
    dimension = imagen->wImg * imagen->hImg;
    for (int i = 0; i < dimension; i++)
    {
        html += "<div class=\"pixel\"></div>\n";
    }
    html += "</div>\n";
    html += "</body>\n";
    html += "</html>\n";

    std::ofstream gen_html(ruta + "\\" + imagen->nombre + ".html");
    gen_html << html;
    gen_html.close();

    /*CREACION ARCHIVO CSS*/
    std::string css = "body{\n";
    css += "\tbackground: #333;\n";
    css += "\theight: 100vh;\n";
    css += "\tdisplay: flex;\n";
    css += "\tjustify-content: center;\n";
    css += "\talign-items: center;\n";
    css += "}\n";
    css += ".canvas{\n";
    int ancho = imagen->wImg * imagen->wPix;
    css += "\twidth: " + std::to_string(ancho) + "px;\n";
    int alto = imagen->hImg * imagen->hPix;
    css += "\theight: " + std::to_string(alto) + "px;\n}";

    css += ".pixel{\n";
    css += "\twidth: " + std::to_string(imagen->wPix) + "px;\n";
    css += "\theight: " + std::to_string(imagen->hPix) + "px;\n";
    css += "\tfloat: left;\n";
    css += "}\n";

    capa *capaTemporal = imagen->primerCapa;
    cabecera *columna = 0;
    elementoCabecera *fila = 0;

    std::string nuevo_color = "";
    std::string sig_color = "";

    int row = 1, column = 1;
    while (capaTemporal != NULL)
    {
        css += "\n/**********" + capaTemporal->nombreCapa + "**********/\n\n";
        columna = capaTemporal->primer_Cabecera;
        column = 1;
        while (columna != NULL)
        {
            fila = columna->primerElementoCabecera;
            row = 1;
            while (fila != NULL)
            {
                if (!((fila->color.compare("x") == 0) || (fila->color.compare("X") == 0) || (fila->color.compare("") == 0)))
                {
                    /*Voy a comparar el color anterior, con el nuevo color
                    Si ambos son iguales, solo insertaré una ,
                    
                    Si ambos son distintos, agregaré la línea ya puesta anteriormente.*/
                    nuevo_color = fila->color;
                    if(fila->siguiente != NULL){
                        sig_color = fila->siguiente->color;
                    }else{
                        sig_color = nuevo_color;
                    }
                    if (nuevo_color == sig_color)
                    {
                        css += ".pixel:nth-child(" + std::to_string(linealizacion(row, column, imagen->wImg)) + "),\n";
                    }
                    else
                    {
                        css += ".pixel:nth-child(" + std::to_string(linealizacion(row, column, imagen->wImg)) + ")\n";
                        css += "{\n";
                        css += "\tbackground-color: rgb(" + rgb(fila->color) + ");\n";
                        css += "}\n";
                    }
                }
                row++;
                fila = fila->siguiente;
            }
            column++;
            columna = columna->siguiente;
        }
        capaTemporal = capaTemporal->siguiente;
    }

    std::ofstream gen_css(ruta + "\\" + imagen->nombre + ".css");
    gen_css << css;
    gen_css.close();

    std::string ruta_fin = ruta + "\\" + imagen->nombre + ".html";
    const char *op_html = ruta_fin.c_str();
    system(op_html);
}

int linealizacion(int fila, int columna, int ancho)
{
    return (((fila - 1) * ancho) + columna);
}

std::string rgb(std::string rgb_pre)
{
    std::replace(rgb_pre.begin(), rgb_pre.end(), '-', ',');
    return rgb_pre;
}

#endif // CREARIMAGEN_H_INCLUDED
