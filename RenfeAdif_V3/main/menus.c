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
#include "../Trayectos/ListaTrayectos.h"
#include "../Trayectos/Trayecto.h"
#include "../Paradas/ListaParadas.h"
#include "../Paradas/Parada.h"

#include "config.h"
#include "menus.h"

void gestionMenuPrincipal(void)
{
    int n;

    do
    {
        /*Llama a la funcion menuPrincipal()*/
        n = menuPrincipal();

        switch(n)
        {
        case '1':
            /*Llama a la funcion mantenimientoEstaciones()*/
            mantenimientoEstaciones();
            break;

        case '2':
            /*Llama a la funcion mantenimientoTrayectos()*/
            mantenimientoTrayectos();
            break;

        case '0':
            /*Finaliza el programa*/
            system("cls");
            system("exit");
            system("mode con cols=60 lines=5");
            return;

        default:
            n=5;
            break;

        }
    }   while (n !='0');

}


int menuPrincipal(void)
{
    int n;
    /*Llamamos a la funcion interfaz para volver a pintarla*/
    inicInterfaz();

    /*Escribimos por pantalla*/
    gotoxy(35,2);
    printf("Sistema De Planificación de viajes");

    gotoxy(45,5);
    printf("Menu Principal");

    gotoxy(2,8);
    printf("1.Mantenimiento de Estaciones");

    gotoxy(2,10);
    printf("2.Mantenimiento de trayectos");

    gotoxy(2,12);
    printf("0.Fin del programa");

    gotoxy(2,28);
    printf("Selecciona una de las opciones: ");

    n = getch();

    return n;
}

