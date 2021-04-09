#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

#include "../auxiliar/auxiliar.h"
#include "../Estaciones/Estacion.h"
#include "../Estaciones/ListaEstaciones.h"
#include "../Interfaz/interfaz.h"
#include "../LibroClaves/Panel.h"
#include "../main/menus.h"
#include "../Paradas/ListaParadas.h"
#include "../Paradas/Parada.h"

#include "ListaTrayectos.h"
#include "Trayecto.h"
#include "TrayectosDiarios.h"

void buscaTrayectosDiarios()
{
    struct sListaTrayectos listaTrayectosActivos;
    struct sListaTrayectos listaTrayectosDiarios;
    char diaIntroducido;
    char estacionIntroducida[100];

    cargaListaTrayectos(&listaTrayectosActivos, "BASEDATOS/Activos/trayectos.activos.bin");
    system("cls");
    inicInterfaz();
    muestraListaTrayectos("BASEDATOS/Activos/trayectos.activos.bin");

    inicListaTrayectos(&listaTrayectosDiarios);

    gotoxy(2,30);
    printf("Introduce un dia de la semana(LMXJVSD): ");
    scanf("%c", &diaIntroducido);

    gotoxy(2,30);
    printf("                                                   ");

    gotoxy(2,30);
    printf("Introduce una estacion: ");
    scanf("%s", estacionIntroducida);

    if(generaTrayectosDiarios(listaTrayectosActivos, &listaTrayectosDiarios, diaIntroducido, estacionIntroducida)!=0)
    {
        grabaListaTrayectos(listaTrayectosDiarios, "BASEDATOS/Activos/trayectos.diarios.bin");

        muestraListaTrayectos("BASEDATOS/Activos/trayectos.diarios.bin");
    }
    else
    {
        gotoxy(2,30);
        printf("No se han encontrado estaciones para ese dia.");
        gotoxy(2,31);
        system("pause");
    }


    free(listaTrayectosDiarios.lista);


}

int generaTrayectosDiarios(struct sListaTrayectos listaTrayectosActivos, struct sListaTrayectos *listaTrayectosDiarios, char diaSemana, char estacionIntroducida[])
{
    int i=0;
    int j=0;
    int k=0;
    for(i=0; i<listaTrayectosActivos.num; i++)
    {
        if((strcmp(listaTrayectosActivos.lista[i].e_destino, estacionIntroducida)==0) || (strcmp(listaTrayectosActivos.lista[i].e_origen, estacionIntroducida)==0))
        {
            if(buscaDiaEnFrecuencia(listaTrayectosActivos.lista[i].frecuencia, diaSemana)==true)
            {
                j++;
                if(j==1)
                {
                    /*Asignamos memoria*/
                    listaTrayectosDiarios->lista=calloc(sizeof(struct sTrayecto),1);
                }
                else
                {
                    listaTrayectosDiarios->lista=realloc(listaTrayectosDiarios->lista, sizeof(struct sTrayecto)*j);

                }
                if(listaTrayectosDiarios!=NULL)
                {

                    strcpy(listaTrayectosDiarios->lista[k].e_destino, listaTrayectosActivos.lista[i].e_destino);
                    strcpy(listaTrayectosDiarios->lista[k].e_origen, listaTrayectosActivos.lista[i].e_origen);
                    strcpy(listaTrayectosDiarios->lista[k].frecuencia, listaTrayectosActivos.lista[i].frecuencia);
                    strcpy(listaTrayectosDiarios->lista[k].h_llegada, listaTrayectosActivos.lista[i].h_llegada);
                    strcpy(listaTrayectosDiarios->lista[k].h_salida, listaTrayectosActivos.lista[i].h_salida);
                    strcpy(listaTrayectosDiarios->lista[k].id, listaTrayectosActivos.lista[i].id);
                    strcpy(listaTrayectosDiarios->lista[k].tipo, listaTrayectosActivos.lista[i].tipo);

                    listaTrayectosDiarios->lista[k].duracion=listaTrayectosActivos.lista[i].duracion;
                    listaTrayectosDiarios->lista[k].precio=listaTrayectosActivos.lista[i].precio;
                    k++;
                }

            }
        }
    }
    listaTrayectosDiarios->num=k;

    return k;
}

bool buscaDiaEnFrecuencia(char frecuencia[], char diaSemana)
{
    bool retorno=false;
    int i=0;
    for(i=0; i<8; i++)
    {
        if(frecuencia[i]==diaSemana)
        {
            retorno=true;
        }
    }
    return retorno;
}
