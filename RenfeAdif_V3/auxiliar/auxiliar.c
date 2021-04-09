#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>

#include "../Interfaz/interfaz.h"
#include "../LibroClaves/Panel.h"
#include "../Trayectos/ListaTrayectos.h"
#include "../Trayectos/Trayecto.h"
#include "../main/menus.h"
#include "../Estaciones/Estacion.h"
#include "../Estaciones/ListaEstaciones.h"
#include "../Paradas/ListaParadas.h"
#include "../Paradas/Parada.h"
#include "../main/config.h"

#include "auxiliar.h"

/*Funcion para colocar el curson en las cordenadas x e y*/
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*Funcion para colocar el curson en la cordenada x*/
void gotox(int x)
{
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    COORD coord;
    coord.X = x;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&SBInfo);
    coord.Y = SBInfo.dwCursorPosition.Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*Funcion para elegir el color*/
void setColorTexto(WORD colors)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colors);
}

/*Funcion que pinta por pantalla la ventana pequeña del cuadro*/
void ventanaPequena()
{
    /*Cambiamos de idioma para que se impriman los caracteres ascii de la interfaz*/
    setlocale(LC_ALL, "C");
    printf("%c         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",179,195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c                                                                                          %c\n",179,179,179);
    printf("%c         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);

    /*Idioma del programa*/
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "C");

    return;
}

bool leeItem(char cadena[], char separador, FILE* ptr)
{
    char caracter;
    int i=0;

    if (feof(ptr) == 0)
    {
        caracter = getc(ptr);
        /*Condiciones: Que no sea el final del archivo.
                       Que el caracter leido no sea el separador(;)
                       Que el caracter leido no sea final de linea(\n)*/

        while (!feof(ptr) && caracter !=separador && caracter !='\n')
        {
            /*Almacenamos en la cadena los caracteres leidos*/
            cadena[i]=caracter;
            i++;
            caracter = getc(ptr);
        }
    }

    cadena[i] = '\0';

    if(feof(ptr)==0)
        return true;
    else
        return false;

}

int scanCarpeta(char lista[][10], char rutaCarpeta[])
{
    /* Puntero a 'carpeta', similar a FILE para archivos */
    DIR *dir;
    /* Estructura de datos para almacenar la información de cada archivo */
    struct dirent *ent;
    int nArch=0; /* Número de archivos */

    /* Abre al carpeta */
    dir = opendir (rutaCarpeta);

    /* Comprueba que se ha abierto correctamente */
    if (dir == NULL)
    {
        printf("Error al abrir la carpeta %s.\n", rutaCarpeta);
        getchar();
        exit(1);
    }

    /* Bucle de lectura que recorre todos los archivos de la carpeta */
    nArch = 0;
    while ((ent = readdir (dir)) != NULL)
    {
        /* No devuelve ni la carpeta actual (.) ni la anterior (..) */
        if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
        {
            strcpy(lista[nArch++], ent->d_name); /* se copia el nombre del archivo a la lista */
        }
    }
    closedir (dir); /* Cierra la carpeta */
    return nArch; /* retorna el número de archivos leídos */
}

/*He creado esta nueva funcion para poder compara dos cadenas un numero de posiciones concretas,
  para poder comparar el IDTray y el id*/
bool comparaNPosiciones(const char cadena1[], char cadena2[], int numeroPosiciones)
{
    bool retorno = true;
    int i=0;

    for (i=0;i<numeroPosiciones;i++)
    {
        if (cadena1[i] != cadena2[i])
        {
            retorno = false;
        }
    }
    return retorno;
}

/*He creado esta nueva funcion para poder copiar dos cadenas un numero de posiciones concretas*/
void copiarNPosiciones(char cadena1[], char cadena2[], int numeroPosiciones)
{

    int i=0;

    for (i=0;i<numeroPosiciones;i++)
    {
        cadena1[i]=cadena2[i];
    }
    cadena1[i]='\0';
}

