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
#include "../main/config.h"
#include "../Estaciones/Estacion.h"
#include "../Estaciones/ListaEstaciones.h"

#include "Parada.h"
#include "ListaParadas.h"

/*Muestra las num paradas que se encuentra a partir de la posicion inic*/
void muestraGrupoParadas(struct sListaParadas listaParadas, int inic, int num)
{
    int i;
    /*Mostramos las paradas*/
    for (i=0; i<num; i++)
    {
        gotoxy(12,12+i);
        printf("%s         %-25s                            %-6s  %-6s ", listaParadas.lista[inic+i].id, listaParadas.lista[inic+i].estacion,
               listaParadas.lista[inic+i].h_salida, listaParadas.lista[inic+i].h_llegada);
    }

}

void navegaListaParadas(struct sListaParadas listaParadas)
{
    int inic=0;
    int posicion=0;
    int num=12;
    bool salidaBucle=false;
    int b;


    /*Pintamos por pantalla*/
    gotoxy(40,2);
    printf("Listado de trayectos");

    gotoxy(2,4);
    printf("ID     Tren        Origen               Destino               Sale    Llega    Min    Precio  Frecuencia");
    gotoxy(12,9);
    printf("ID               Estación                                            Llegada  Salida");

    /*Si el numero de paradas es menor que num*/
    if (listaParadas.num<num)
    {
        /*Igualamos a num el numero de pardas para enviarlo a la funcion*/
        num=listaParadas.num;
    }

    /*Llamamos a muestraGrupoParadas para mostrar las primeras n paradas*/
    muestraGrupoParadas(listaParadas, inic, num);

    /*Cambiamos color*/
    setColorTexto(160);
    gotoxy(12,12+posicion);
    /*Llamamos a muestraParada para escrbir los datos de la primera parada en colores invertidos*/
    muestraParada(listaParadas.lista[inic+posicion]);

    /*Bucle para mover el cursor y salir con escape*/
    while (!salidaBucle)
    {
        b=getch();
        switch(b)
        {
        /*Escape*/
        case 27:
            salidaBucle = true;
            break;
        /*Tecla especial*/
        case 224:
            b=getch();
            switch(b)
            {
            /*Flecha de arriba*/
            case 72:
                gotoxy(12,12+posicion);
                if (inic > 0 && posicion == 0)
                    inic--;
                else if (posicion > 0)
                    posicion--;
                break;
            /*Flecha de abajo*/
            case 80:
                gotoxy(12,12+posicion);
                if (inic < (listaParadas.num-num) && posicion == num-1)
                    inic++;
                else if (posicion < num-1)
                    posicion++;
                break;
            }

        }
        setColorTexto(10);
        /*Llamamos a muestraGrupoParadas para mostrar las n paradas*/
        muestraGrupoParadas(listaParadas, inic, num);

        setColorTexto(160);
        gotoxy(12,12+posicion);
        /*Llamamos a muestraParada para escrbir los datos de la parada en colores invertidos*/
        muestraParada(listaParadas.lista[inic+posicion]);


    }
    setColorTexto(10);

}

/*Invoca a leeItem las veces necesarias para leer todas las paradas que aparecen en el archivo de un trayecto*/
void scanParadaEnTrayecto(char IDTray[], struct sListaParadas *plParadas, FILE* ptr)
{
    int i=0;
    struct sParada *asignacion;
    char estacion[DIM_NOM_ESTACION];
    /*Mientramos leamos items*/

    while (leeItem(estacion,';', ptr))
    {
        if(i==0)
        {
            /*Asignamos memoria*/
            asignacion = calloc(sizeof(struct sParada), 1);
        }
        else
        {
            asignacion=realloc(plParadas->lista,sizeof(struct sParada)*(i+1));
        }

        if(asignacion!=NULL)
        {
            plParadas->lista = asignacion;
            strcpy(plParadas->lista[i].estacion, estacion);

            /*Metemos en IDParada el IDTray mas el numero de parada*/
            sprintf(plParadas->lista[i].id, "%s.%02d", IDTray, i);
            leeItem(plParadas->lista[i].h_salida,';', ptr);
            leeItem(plParadas->lista[i].h_llegada,';', ptr);

            i++;
        }

    }
    /*Guardamos el numero de paradas*/
    plParadas->num=i;

}

/*Recibe una lista de paradas y genera un archivo binario*/
void grabaParadasTrayecto(struct sListaParadas lParadas)
{
    char archivo[100];
    int i=0;
    char IDTray[6];
    FILE* ptr;
    /*Concatenamos en archivo la ruta completa al archivo*/
    copiarNPosiciones(IDTray, lParadas.lista[0].id,5);
    sprintf(archivo, "BASEDATOS/Activos/Paradas/paradas.%s.bin", IDTray);
    /*Abrimos el archvio en modo escritura*/
    ptr = fopen(archivo,"wb");
    /*Si es erroneo*/
    if (ptr==NULL)
    {
        printf("Error al abrir el archivo %s", archivo);
    }
    else
    {

        for(i=0; i<lParadas.num; i++)
        {
            /*Concatenamos en IDParada el IDTray mas el nuero de parada*/
            sprintf(lParadas.lista[i].id, "%s.%02d", IDTray, i);
            /*Escribimos en el archivo*/
            fwrite(&lParadas.lista[i], sizeof(struct sParada),1,ptr);
        }
        /*Cerramos el archivo de texto*/
        fclose(ptr);
    }

}

/*Recibe una lista de paradas y las agrega al archivo bianrio*/
void agregaAListaParadasBin(struct sListaParadas listaParadas)
{
    int i=0;
    FILE* ptr;

    /*Abrimos el archivo binario*/
    ptr = fopen("BASEDATOS/Activos/Paradas/listaParadas.bin","ab");
    /*Si es erroneo*/
    if (ptr==NULL)
    {
        printf("Error al abrir el archivo BASEDATOS/Activos/Paradas/listaParadas.bin");
    }
    else
    {
        for(i=0; i<listaParadas.num; i++)
        {
            /*Escribimos en el archivo*/
            fwrite(&listaParadas.lista[i], sizeof(struct sParada),1,ptr);
        }
        /*Cerramos el archivo de texto*/
        fclose(ptr);
    }

}

/*Recibe el nombre de una estacion, y comprueba si alguna de las paradas tiene el nombre recibido.
Devuelve true si lo encuentra*/
bool existeEstacionListaParadas (char nombreEstacion[])
{
    struct sParada parada;
    bool retorno=false;
    FILE*ptr;

    /*Abrimos el archivo binario en modo lectura*/
    ptr=fopen("BASEDATOS/Activos/Paradas/listaParadas.bin", "rb");
    /*Si es erroneo*/
    if(ptr==NULL)
    {
        retorno=false;
    }
    else
    {
        /*Mientras sea final de fichero y retorno siga siendo falso*/
        while(!feof(ptr)&&retorno==false)
        {
            /*Si la lectura es correcta*/
            if(fread(&parada,sizeof(struct sParada),1,ptr)!=0)
            {
                /*Si los nombre son iguales, cambiamos la variable retorno a verdadera*/
                if(strcmp(parada.estacion, nombreEstacion)==0)
                {
                    retorno=true;
                }
            }
        }

        /*Cerramos el archivo de texto*/
        fclose(ptr);
    }
    /*Devolvemos retorno*/
    return retorno;
}


void muestraParadasTrayectos(const char IDTray[])
{
    struct sListaParadas plParadas;
    char archivo[200];

    /*Pintamos la ventana pequeña*/
    gotoxy(0,8);
    ventanaPequena();

    gotoxy(2,28);
    printf("[ESC]: Abandonar - [Flechas]: Mover");

    sprintf(archivo, "BASEDATOS/Activos/Paradas/paradas.%s.bin",IDTray);

    /*Cargamos las paradas*/
    cargaListaParadas(&plParadas, archivo);
    /*Si el numero de paradas es mayor que cero*/
    if (plParadas.num>0)
    {
        /*Llamamos a navegaListaParadas para visualizar por pantalla*/
        navegaListaParadas(plParadas);
    }
    /*Liberamos la memoria*/ /*.*/
    free(plParadas.lista);
}

/*Recibe una lista de paradas y la escribe en un archivo binario*/
void grabaListaParadas(struct sListaParadas plParadas, char archivo[])
{
    FILE*ptr;
    int i=0;

    /*Abrimos el archivo de texto en modo escritura*/
    ptr=fopen(archivo,"wb");
    /*Si es erroneo*/
    if(ptr==NULL)
    {
        printf("No se ha podido abrir el fichero");
    }
    else
    {
        /*Escribimos en el fichero*/
        for (i=0; i<plParadas.num; i++)
        {
            fwrite(&plParadas.lista[i], sizeof(struct sParada),1,ptr);
        }
        /*Cerramos el archivo de texto*/
        fclose(ptr);
    }
}

void eliminaParadasTrayecto (const char IDTray[])
{
    int i=0,j=0;
    struct sListaParadas plParadas;
    char archivo[100]="BASEDATOS/Activos/Paradas/listaParadas.bin";

    /*Cargamos la lista de paradas*/
    cargaListaParadas(&plParadas, archivo);

    /*Mientras no sea el ultimo, y no sean iguales el IDTray y el IDParada*/
    while(i<plParadas.num && !comparaNPosiciones(IDTray, plParadas.lista[i].id, 5))
    {
        i++;
    }
    /*Si es el ultimo*/
    if(i<plParadas.num)
    {
        j=i;
        /*Si es el ultimo, y son iguales el IDTray y el IDParada*/
        while(j<plParadas.num && comparaNPosiciones(IDTray, plParadas.lista[j].id, 5))
        {
            j++;
        }

        if(j==plParadas.num)
        {
            plParadas.num=i;
        }
        else
        {
            while(j<plParadas.num)
            {
                /*Copiamos*/
                strcpy(plParadas.lista[i].id, plParadas.lista[j].id);
                strcpy(plParadas.lista[i].estacion, plParadas.lista[j].estacion);
                strcpy(plParadas.lista[i].h_salida, plParadas.lista[j].h_salida);
                strcpy(plParadas.lista[i].h_llegada, plParadas.lista[j].h_llegada);

                i++;
                j++;
            }
            plParadas.num=i;
        }
        /*Llamamos a grabaListaParadas y le enviamos la lista de paradas*/
        grabaListaParadas(plParadas, archivo);
    }
    /*Liberamos la memoria reservada*/
    free(plParadas.lista);

}

/*Carga una lista de paradas activas*/
void cargaListaParadas(struct sListaParadas *plParadas, char archivo[])
{
    int i=0;
    struct sParada parada;
    struct sParada *asignacion;
    FILE* ptr;

    /*inicializamos*/
    inicListaParadas(plParadas);

    /*Abirmos el fichero*/
    ptr=fopen(archivo,"rb");
    /*Si es erroneo*/
    if(ptr==NULL)
    {

    }
    else
    {
        /*Mientras no sea final de fichero*/
        while(!feof(ptr))
        {
            /*Si la lectura es correcta*/
            if(fread(&parada,sizeof(struct sParada), 1, ptr)!=0)
            {
                i++;
                if(i==1)
                {
                    /*Asignamos memoria*/
                    asignacion=calloc(sizeof(struct sParada),1);

                }
                else
                {
                    asignacion=realloc(plParadas->lista, sizeof(struct sParada)*i);


                }
                if(asignacion!=NULL)
                {

                    plParadas->lista=asignacion;
                    strcpy(plParadas->lista[i-1].id, parada.id);
                    strcpy(plParadas->lista[i-1].estacion, parada.estacion);
                    strcpy(plParadas->lista[i-1].h_salida, parada.h_salida);
                    strcpy(plParadas->lista[i-1].h_llegada, parada.h_llegada);

                }
                else
                {
                    i--;
                }
            }
        }
        /*Guardamos el numero de paradas*/
        plParadas->num=i;

    }
    /*Cerramos el archivo de tetxo*/
    fclose(ptr);
}

/*Recibe una lista de paradas e inicializa sus atributos*/
void inicListaParadas(struct sListaParadas *plParadas)
{
    /*Inicializamos la estructura*/
    plParadas->lista=NULL;
    plParadas->num=0;
}

