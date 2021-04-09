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

int main (void)
{

    /*Nombre de la ventana */
    system("title RenfeAdif");

    /*Color de la ventana*/
    setColorTexto(10);

    /*Llamamos a la funcion inicInterfaz*/
    inicInterfaz();

    /*Idioma del programa*/
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "C");

    /*Llamamos a la funcion gestionMenuPrincipal*/
    gestionMenuPrincipal();

    return 0;
}


