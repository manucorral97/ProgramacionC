#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "../auxiliar/auxiliar.h"
#include "../Interfaz/interfaz.h"
#include "../LibroClaves/Panel.h"
#include "../Trayectos/ListaTrayectos.h"
#include "../Trayectos/Trayecto.h"
#include "../main/menus.h"
#include "../Paradas/ListaParadas.h"
#include "../Paradas/Parada.h"
#include "../main/config.h"

#include "Estacion.h"
#include "ListaEstaciones.h"
#include "EstacionesCercanas.h"

void buscaEstacionesCercanas()
{
    struct sListaEstaciones listaEstaciones;
    struct sListaEstacionesCercanas listaEstacionesCercanas;

    struct sEstacion estacion;

    float distanciaIntroducida;
    float distancia;

    int i=0, j=0, k=0;

    cargaListaEstaciones(&listaEstaciones);
    inicListaEstacionesCercanas(&listaEstacionesCercanas);

    gotoxy(2,30);
    printf("Introduce una latitud: ");
    scanf("%lf", &estacion.latitud);

    gotoxy(2,30);
    printf("                                    ");

    gotoxy(2,30);
    printf("Introduce una longitud: ");
    scanf("%lf", &estacion.longitud);


    gotoxy(2,30);
    printf("                                    ");

    gotoxy(2,30);
    printf("Introduce la distancia maxima: ");
    scanf("%f", &distanciaIntroducida);

    for(i=0; i<listaEstaciones.num; i++)
    {
        distancia=distanciaEntreEstaciones(estacion, listaEstaciones.lista[i]);
        if(distancia<distanciaIntroducida)
        {
            j++;
            if(j==1)
            {
                /*Asignamos memoria*/
                listaEstacionesCercanas.lista = calloc(sizeof(struct sEstacion),1);
            }
            else
            {
                listaEstacionesCercanas.lista=realloc(listaEstacionesCercanas.lista, sizeof(struct sEstacion)*j);

            }
            /*Si la asignacion ha sido correcta*/
            strcpy(listaEstacionesCercanas.lista[k].nombreEstacion,listaEstaciones.lista[i].nombre);
            strcpy(listaEstacionesCercanas.lista[k].nombreProvincia,listaEstaciones.lista[i].provincia);
            listaEstacionesCercanas.lista[k].distancia=distancia;
            k++;

        }
    }
    listaEstacionesCercanas.numeroElementos=k;
    if(k!=0)
    {
        grabaListaEstacionesCercanas(listaEstacionesCercanas);
        gotoxy(2,30);
        printf("Se ha escrito correctamente en los ficheros de texto.");
        gotoxy(2,31);
        system("pause");

    }
    else
    {
        gotoxy(2,30);
        printf("No se ha encontrado ninguna estacion para escribir en los ficheros.");
        gotoxy(2,31);
        system("pause");
    }



}

void grabaListaEstacionesCercanas(struct sListaEstacionesCercanas listaEstacionesCercanas)
{
    FILE* ptr;
    FILE* fb;
    int i=0;

    ptr=fopen("BASEDATOS/Activos/EstacionesCercanas.txt", "at");
    fb=fopen("BASEDATOS/Activos/EstacionesCercanas.bin", "ab");
    if(ptr==NULL)
    {
        gotoxy(2,32);
        printf("ERROR FIHCERO DE TEXTO");
    }
    else
    {
        for(i=0; i<listaEstacionesCercanas.numeroElementos; i++)
        {
            fprintf(ptr, "%s;%s;%f\n",listaEstacionesCercanas.lista[i].nombreEstacion, listaEstacionesCercanas.lista[i].nombreProvincia, listaEstacionesCercanas.lista[i].distancia);
        }
    }

    if(fb==NULL)
    {
        gotoxy(2,32);
        printf("ERROR FIHCERO BINARIO");
    }
    else
    {
        for(i=0; i<listaEstacionesCercanas.numeroElementos; i++)
        {
            fwrite(&listaEstacionesCercanas.lista[i],sizeof(struct sEstacionCercana),1, fb);
        }
    }

    fclose(ptr);
    fclose(fb);
}

float distanciaEntreEstaciones(struct sEstacion estacion1, struct sEstacion estacion2)
{
    float distancia=0;
    distancia=(((estacion1.latitud-estacion2.latitud)*(estacion1.latitud-estacion2.latitud))+((estacion1.longitud-estacion2.longitud)*(estacion1.longitud-estacion2.longitud)));
    distancia=111*sqrt(distancia);

    return distancia;
}


void inicListaEstacionesCercanas(struct sListaEstacionesCercanas *plEstaciones)
{
    /*Inicializamos los valores de la estructura*/
    plEstaciones->numeroElementos=0;
    plEstaciones->lista=NULL;
}
