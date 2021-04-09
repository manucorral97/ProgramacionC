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

void muestraParada(struct sParada parada)
{
    /*Escribimos por pantalla*/
    printf("%s         %-25s                            %-6s  %-6s ", parada.id, parada.estacion, parada.h_salida, parada.h_llegada);

}

