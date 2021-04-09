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

/*Recorre el archivo de estaciones activas buscando una con el mismo nombre que el recibido como parametro*/
/*Devuelve true si lo encuentra*/
bool existeEstacion(char nombreEstacion[])
{
    FILE* ptr;
    struct sEstacion estacion;
    bool retorno=false;

    /*Abrimos el archivo de texto en modo lectura binaria*/
    ptr = fopen("BASEDATOS/Activos/Estaciones.activas.bin","rb");
    /*Si es erroneo*/
    if(ptr==NULL)
    {
        return false;
    }
    else
    {
        /*Mientras no sea final de fichero y el la variable retorno siga siendo falsa entramos*/
        while(!feof(ptr) && retorno==false)
        {
            /*Si la lectura del archivo ha sido correcta, y coinciden los nombre, cambiamos la variable retorno para salir del bucle*/
            if(fread(&estacion,sizeof(struct sEstacion),1,ptr)==1)
            {
                if(strcmp(estacion.nombre,nombreEstacion)==0)
                {
                    retorno=true;
                }
            }
        }
        /*Cerramos el archivo*/
        fclose(ptr);
        return retorno;
    }

}

/*Recorre el archivo general de estaciones(mediante scanEstacionCSV buscando la estacion que recibe como parametro.
                                           Si la encuentra agrega sus datos al archivo binario de estaciones activas*/
/*Devuelve true si la encuentra y la agrega*/
bool agregaEstacionViaArchivo(char *nombreEstacion)
{
    FILE*ptr;
    FILE*ptrw;

    struct sEstacion pEstacion;

    /*Abrimos el archivo binario en modo lectura*/
    ptr=fopen("BASEDATOS/DatosRenfe/Estaciones/TodasEstaciones.csv","rt");
    /*Si es erroneo*/
    if(ptr==NULL)
    {
        return false;
    }
    else
    {
        /*Mientras scanEstacion devuelva true, y el nombre no sea igual al nombreEstacion*/
        while (scanEstacionCSV(&pEstacion, ptr) && strcmp(pEstacion.nombre, nombreEstacion)!=0)
        {

        }
        /*Si el nombre y el nombreEstacion son iguales*/
        if ( strcmp(pEstacion.nombre, nombreEstacion)==0)
        {
            /*Cerramos el primer archivo*/
            fclose(ptr);
            /*Abrimos el otro archivo binraio en modo escritura al final del archivo*/
            ptrw=fopen("BASEDATOS/Activos/Estaciones.activas.bin", "ab");
            if(ptrw==NULL)
            {
                return false;
            }
            else
            {
                /*Escribimos en el archivo los datos de la nueva estacion*/
                fwrite(&pEstacion, sizeof(struct sEstacion),1,ptr);
                /*Cerramos el archivo*/
                fclose(ptrw);
                return true;
            }

        }
        else
        {
            /*Cerramos el archivo*/
            fclose(ptr);
            return false;
        }
    }


}

/*Muentra en una linea los datos de la estacion que recibe*/
void muestraEstacion(struct sEstacion estacion)
{
    /*Encontramos la y del cursor*/
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;

    /*Cambiamos el idioma a ASCII para escribir la barra de la pared*/
    setlocale(LC_ALL, "C");
    printf("\n%c %.10s ",179, estacion.id);

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&SBInfo);

    /*Cambiamos el idioma a español*/
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "C");
    printf("      %.50s", estacion.nombre);
    gotox(45);
    printf("%s", estacion.provincia);

    gotox(75);
    printf("%0.2f", estacion.latitud);
    gotox(94);
    printf("%0.2f", estacion.longitud);

}

/*Invoca a leeItem las veces necesarias para leer todos los datos correspondientes a una estacion*/
bool scanEstacionCSV(struct sEstacion *pEstacion, FILE *ptr)
{
    /*Invoca a leeItem las veces necesarias para leer todos los datos correspondientes a una estacion*/
    char cadena[100];
    char separador=';';

    bool finalfichero;

    finalfichero=!leeItem(cadena, separador, ptr);

    if (!finalfichero)  /*Si no es el final del fichero entramos*/
    {
        /*Copiamos la cadena obteida mediante leeItem a id*/
        strcpy(pEstacion->id,cadena);
        leeItem(cadena, separador, ptr);
        /*Copiamos la cadena obteida mediante leeItem a nombre*/
        strcpy(pEstacion->nombre, cadena);
        leeItem(cadena, separador, ptr);
        /*Copiamos la cadena obteida mediante leeItem a provincia*/
        strcpy(pEstacion->provincia, cadena);
        leeItem(cadena, separador, ptr);
        /*Como cogemos una cadena, tenemos que pasarlo a float*/
        pEstacion->latitud=atof(cadena);
        leeItem(cadena, separador, ptr);
        /*Como cogemos una cadena, tenemos que pasarlo a float*/
        pEstacion->longitud=atof(cadena);

    }

    if(!finalfichero)
        return true;
    else
        return false;

    /*Devuelve true si se han leido bien los datos*/
    /*False si no*/

}

