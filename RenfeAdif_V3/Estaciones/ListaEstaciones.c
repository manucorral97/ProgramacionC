#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

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

void mantenimientoEstaciones(void)
{
    int n;
    do
    {
        /*Llama a la funcion menuMantenimientoEstaciones()*/
        n = menuMantenimientoEstaciones();

        switch(n)
        {
        case '1':
            /*Llama a la funcion muestraListaEstaciones()*/
            muestraListaEstaciones();
            break;

        case '2':
            /*Llama a la funcion eliminaEstacionesBD()*/
            eliminaEstacionesBD();
            break;

        case '3':
            buscaEstacionesCercanas();
            break;


        case '0':
            /*Finaliza la funcion y vuelve al menu anterior*/
            system("cls");
            return;

        default:
            n=5;
            break;

        }

    }
    while (n !='0');
}

int menuMantenimientoEstaciones(void)
{
    int n;

    /*Limpiamos la pantalla*/
    system("cls");

    /*Llamamos a la funcion interfaz para volver a pintarla*/
    inicInterfaz();

    /*Escribimos por pantalla*/
    gotoxy(35,2);
    printf("Sistema De Planificación de viajes");

    gotoxy(40,5);
    printf("Mantenimiento de Estaciones");

    gotoxy(2,8);
    printf("1.Listar todas las estaciones.");

    gotoxy(2,10);
    printf("2.Eliminar estaciones.");

    gotoxy(2,12);
    printf("3.Buscar Estaciones Cercanas");

    gotoxy(2,14);
    printf("0.Menu anterior.");

    gotoxy(2,28);
    printf("Introduzca una opción: ");
    n = getch();

    return n;
}

/*Invoca a cargaListaEstacion para obtener la lista de estaciones activas y muestra la lista*/
void muestraListaEstaciones(void)
{
    int i;
    int j;

    struct sListaEstaciones listaEstaciones;

    int numeroEstacionesPorPagina=18;
    int pos;

    /*Iniciamos la interfaz*/
    inicInterfaz();

    /*Llama a cargaListaEstaciones*/
    cargaListaEstaciones(&listaEstaciones);


    /*Bucle para mostrar todas las listas de las estaciones*/
    for (j=0; j<=(listaEstaciones.num/18); j++)
    {
        gotoxy(39,2);
        printf("Listado de Estaciones");

        gotoxy(2,5);
        printf("ID          Nombre                         Provincia                     Latitud            Longitud");
        printf("\n");

        if(j==listaEstaciones.num/18 && listaEstaciones.num<18)
        {
            numeroEstacionesPorPagina = listaEstaciones.num;
        }
        /*Bucle para mostrar una lista de Estaciones*/
        for (i=0; i<numeroEstacionesPorPagina; i++)
        {
            pos = 18*j + i;
            /*Llamo a muestraEstacion para que me imprima las estaciones una a una*/
            muestraEstacion(listaEstaciones.lista[pos]);

        }

        /*liberamos la memoria reservada*/
        free(listaEstaciones.lista);

        gotoxy(2,32);
        printf("Pulsa [return] para ver mas estaciones...");
        /*Limpiamos el buffer de entrada*/
        fflush(stdin);
        getchar();

        system ("cls");
        inicInterfaz();
    }

}

/*Inicializa los valores de la lista, y depsues de los datos del archivo binario y los almacena en la lista dinamica*/
void cargaListaEstaciones(struct sListaEstaciones *plEstaciones)
{
    int i=0;
    struct sEstacion estacion;
    struct sEstacion *asignacion;

    /*Lee del archivo Estaciones.activas.bin*/
    FILE* ptr;
    inicListaEstaciones(plEstaciones);

    ptr = fopen("BASEDATOS/Activos/Estaciones.activas.bin", "rb");
    /*Si no abre bien el archivo*/
    if (ptr==NULL)
    {
        gotoxy(39,2);
        printf("Listado de Estaciones");
        gotoxy(2,31);
        printf("El fichero Estaciones.activas.bin está vacio");

    }
    /*Si abre bien el archivo*/
    else
    {
        /*Entramos mientras no sea final de fichero*/
        while(!feof(ptr))
        {
            /*Si la lectura es correcta*/
            if(fread(&estacion,sizeof(struct sEstacion), 1, ptr)!=0)
            {
                i++;
                if(i==1)
                {
                    /*Asignamos memoria*/
                    asignacion = calloc(sizeof(struct sEstacion),1);
                }
                else
                {
                    asignacion=realloc(plEstaciones->lista, sizeof(struct sEstacion)*i);

                }
                /*Si la asignacion ha sido correcta*/
                if(asignacion!=NULL)
                {

                    plEstaciones->lista=asignacion;
                    strcpy(plEstaciones->lista[i-1].id, estacion.id);
                    strcpy(plEstaciones->lista[i-1].nombre, estacion.nombre);
                    strcpy(plEstaciones->lista[i-1].provincia, estacion.provincia);
                    plEstaciones->lista[i-1].latitud = estacion.latitud;
                    plEstaciones->lista[i-1].longitud = estacion.longitud;

                }
                else
                {
                    i--;
                }
            }


        }
        /*Guardamos el numero de estaciones*/
        plEstaciones->num=i;
        /*Cerramos el archivo*/
        fclose(ptr);
    }

}

/*Muestra por pantalla un grupo de estaciones, llamando a muestraEstacion*/
void muestraGrupoEstaciones(struct sListaEstaciones lEstaciones, int inic, int num)
{
    int i;
    for (i=0; i<num; i++)
    {
        /*Llamamos a muestra Estacion para mostrar por pantalla*/
        muestraEstacion(lEstaciones.lista[inic+i]);
    }

}


void eliminaEstacionesBD(void)
{
    struct sListaEstaciones listaEstaciones;
    int i=0;

    FILE* ptr;
    /*Llamamos a cargaListaEstaciones para cargar las listas, y obtener el numero de estaciones*/
    cargaListaEstaciones(&listaEstaciones);
    /*Si el numero de estaciones es cero, mostramos por pantalla*/
    if (listaEstaciones.num==0)
    {
        gotoxy(2,31);
        printf("No hay estaciones para borrar.                                               ");
        gotoxy(2,32);
        system("pause");
    }
    else
    {
        /*Abrimos el archivo en modo escritura*/
        ptr=fopen("BASEDATOS/Activos/Estaciones.activas.bin","wb");
        /*Si el archivo es erroneo*/
        if(ptr==NULL)
        {
            gotoxy(2,31);
            printf("No se ha podido abrir el archivo de estaciones activas");
            gotoxy(2,32);
            system("pause");
        }
        else
        {
            for (i=0; i<listaEstaciones.num; i++)
            {
                /*Compueba si dicha estacion no esta en ningun trayecto activo*/
                /*Si existeEstacionListaParadas escribimos en el archivo de texto*/
                if(existeEstacionListaParadas(listaEstaciones.lista[i].nombre))
                {
                    fwrite(&listaEstaciones.lista[i],sizeof(struct sEstacion),1,ptr);
                    gotoxy(2,29);
                    printf("La estacion %s existe. No se puede eliminar.                                          ", listaEstaciones.lista[i].nombre);
                    gotoxy(2,31);
                    system("pause");

                }
                else
                {

                }
            }
            /*Liberamos la memoria reservada*/
            free(listaEstaciones.lista);

            /*Cerramos el archivo de texto*/
            fclose(ptr);
        }
    }

}

/*Inicializamos la lista de estaciones*/
void inicListaEstaciones(struct sListaEstaciones *plEstaciones)
{
    /*Inicializamos los valores de la estructura*/
    plEstaciones->num=0;
    plEstaciones->lista=NULL;
}






