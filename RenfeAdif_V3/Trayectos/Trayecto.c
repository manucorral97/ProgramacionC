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

/*Invoca a leeItem las veces necesarias para leer los datos correspondientes a un trayecto*/
/*Devuelve true si se han leido bien los datos*/
bool scanTrayectoCSV(struct sTrayecto *pTrayecto, FILE *ptr)
{
    char numero[20];
    bool retorno;

    retorno = leeItem(pTrayecto->id, ';', ptr);
    retorno &= leeItem(pTrayecto->tipo, ';', ptr);
    retorno &= leeItem(pTrayecto->e_origen, ';', ptr);
    retorno &= leeItem(pTrayecto->e_destino, ';', ptr);
    retorno &= leeItem(pTrayecto->h_salida, ';', ptr);
    retorno &= leeItem(pTrayecto->h_llegada, ';', ptr);

    /*Como duracion es un int lo convertimos mediante atoi*/
    retorno &= leeItem(numero, ';', ptr);
    pTrayecto->duracion = atoi(numero);

    /*Como los numeros vienen con puntos en vez de con comas, cambiamos el "idioma"*/
    retorno &= leeItem(numero, ';', ptr);
    /*Como cogemos una cadena, tenemos que pasarlo a float*/
    pTrayecto->precio=atof(numero);
    /*Volvemos al idioma original*/

    retorno &= leeItem(pTrayecto->frecuencia, ';', ptr);

    return retorno;
}

/*Agrega un trayecto a la lista de trayectos activos*/
void agregaTrayecto(void)
{
    int i=0;
    char nombreArchivo[200];
    FILE* ptr;
    char rutaCompleta[200];
    struct sTrayecto trayecto;
    struct sListaParadas listaParadas;
    char id[5];

    system("cls");
    inicInterfaz();
    gotoxy(37,2);
    printf("Listado de archivos de Trayectos");

    gotoxy(2,28);
    printf("[return]: Seleccionar  -  [ESC]: Abandonar  -  [Flechas]: Mover");

    /*Llama a selecionaArchivoTrayecto para obtener el nombre del archivo que contiene los datos del nuevo trayecto*/
    /*Si seleccionaArchivoTrayecto devuelve true*/
    if (seleccionaArchivoTrayecto(nombreArchivo))
    {
        /*Pintamos en pantalla*/
        gotoxy(2,31);
        printf("Ha selecionado el archivo %s", nombreArchivo);
        gotoxy(2,32);
        system("pause");
        /*Copiamos en id el nombreArchivo*/
        strcpy(id, nombreArchivo);
        id[5]='\0';

        /*Comprueba que el trayecto seleccionado ya esta en la lista de trayectos activos*/
        /*Si existe trayecto devuelve true*/
        if (existeTrayecto(id))
        {
            /*Pintamos en pantalla*/
            gotoxy(2,31);
            printf("El trayecto con Identificador %s ya está activado", id);
            gotoxy(2,32);
            system("pause");
        }
        /*Si no esta incluido*/
        else
        {
            /*Copiamos la ruta del archivo a rutaCompleta*/
            strcpy(rutaCompleta, "BASEDATOS/DatosRenfe/Trayectos/");
            /*Concatenamos la ruta completa y el nombre del archivo*/
            strcat(rutaCompleta, nombreArchivo);
            /*Abrimos el archivo*/
            ptr = fopen(rutaCompleta, "rt");
            if (ptr == NULL)
            {
                /*Pintamos por pantalla*/
                gotoxy(2,31);
                printf("Error al abrir el fichero %s", rutaCompleta);
                gotoxy(2,32);
                system("pause");
            }
            else
            {
                /*Si scanTrayecto devuelve false*/
                if (!scanTrayectoCSV(&trayecto, ptr))
                {
                    /*Pintamos por pantalla*/
                    gotoxy(2,31);
                    printf("Error al leer el fichero %s", rutaCompleta);
                    gotoxy(2,32);
                    system("pause");
                }
                else
                {
                    /*Obetenemos los datos del trayecto y sus correspondientes paradas*/
                    scanParadaEnTrayecto(id, &listaParadas, ptr);

                    for(i=0; i<listaParadas.num; i++)
                    {
                        /*Llamamos a existeEstacion para obtener el id de la estacion a partir de su nombre y
                        para saber si la estacion ya existe en el archivo de estaciones activas*/
                        if (!existeEstacion(listaParadas.lista[i].estacion))
                        {
                            /*Llamamos a la funcion agregaEstacionViaArchivo para agergar la estacion al archivo
                            de estaciones activas*/
                            agregaEstacionViaArchivo(listaParadas.lista[i].estacion);
                        }
                    }

                    system("cls");
                    inicInterfaz();
                    gotoxy(0,8);
                    ventanaPequena();
                    gotoxy(2,7);

                    /*Llamamos a muestraTrayecto para mostrar los datos del nuevo trayecto en pantalla*/
                    muestraTrayecto(trayecto);
                    /*Escribimos por panatalla*/
                    gotoxy(2,29);
                    printf("[ESC]: Abandonar - [Flechas]: Mover");

                    /*Llamamos a navegaListaParadas para mostrar una lista navegable de las paradas correspondientes al nuevo trayecto*/
                    navegaListaParadas(listaParadas);

                    /*Agergamos el trayecto al archivo binario*/
                    agregaTrayectoABin(trayecto);

                    /*Llamamos a grabaParadasTrayecto para gabrar la lista de paradas del nuevo trayecto en un archivo binario*/
                    grabaParadasTrayecto(listaParadas);

                    /*Llamamos a agregaAListaParadasBin para agregar las paradas del nuevo trayecto al archivo bianrio*/
                    agregaAListaParadasBin(listaParadas);
                }

            }

        }

    }
    else
    {
        gotoxy(2,31);
        printf("Error al abrir el fichero");
        gotoxy(2,32);
        system("pause");
    }

}

/*Recorre el archivo de trayectos activos para ver si el trayecto con el id que recibe ya esta registrado
Devuelve true si esta registrado*/
bool existeTrayecto(char *id)
{
    bool retorno = false;
    struct sTrayecto trayecto;
    FILE* ptr;

    /*Abrimos el archivo binario en modo lectura*/
    ptr = fopen("BASEDATOS/Activos/trayectos.activos.bin", "rb");
    /*Si es erroneo*/
    if (ptr == NULL)
        return false;

    else
    {
        /*Mientras no sea final de fichero*/
        while(!feof(ptr))
        {
            /*Leemos del archivo binario*/
            fread(&trayecto, sizeof(struct sTrayecto),1,ptr);
            /*Si los ids son los mismos, cambiamos retorno a true*/
            if(strcmp(trayecto.id, id)==0)
            {
                retorno = true;
            }
        }

        /*Cerramos el archivo*/
        fclose(ptr);
    }

    /*Devolvemos el valor de retorno*/
    return retorno;

}

/*Muestra en una linea los datos que recibe como parametros*/
void muestraTrayecto(struct sTrayecto trayecto)
{
    /*Escribimos por pantalla*/
    gotox(2);
    printf("%5s  %-5s       %-21s%-21s %s   %s    %-3d    %0.2f   %s\n", trayecto.id, trayecto.tipo, trayecto.e_origen, trayecto.e_destino, trayecto.h_salida, trayecto.h_llegada,
           trayecto.duracion, trayecto.precio, trayecto.frecuencia);

}

/*Recibe una lista de nombres de archivos de trayectos y muestra en la ventana de listados los num nombres de archivos que se encuentra
a partir de la posicion inic*/
void muestraGrupoArchivosTrayecto(char listaArchivos[][10], int inic, int num)
{
    int i;
    /*Escribimos por pantalla*/
    for (i=0; i<num; i++)
    {
        gotoxy(2,7+i);
        printf("%s", listaArchivos[inic+i]);
    }

}

bool seleccionaArchivoTrayecto(char* nombreArchivo)
{
    char archivos[100][10];
    int numArchivos;
    int num=18;
    int inic=0;
    int posicion=0;
    int b;
    bool salir = false;
    bool retorno = false;

    /*Obetenemos la lista de archivos de trayectos de la base de datos mediante scanCarpeta*/
    numArchivos=scanCarpeta(archivos,"BASEDATOS/DatosRenfe/Trayectos");
    /*Doble switch para las flechas
        Tecla especial 224. Luego:
            - 80 abajo
            - 77 derecha
            - 72 arriba
            - 75 izquierda
        27 escape
        13 return*/

    do
    {
        /*Mostramos en pantalla los n primeros nombres de archivos*/
        muestraGrupoArchivosTrayecto(archivos, inic, num);

        gotoxy(2,7+posicion);
        /*Fondo verde sobre texto negro*/
        setColorTexto(160);
        printf("%s", archivos[inic+posicion]);

        b = getch();
        switch(b)
        {
        case 224:
            b = getch();
            switch(b)
            {
            /*Flecha de arriba*/
            case 72:
                gotoxy(2,7+posicion);
                setColorTexto(10);
                printf("%s", archivos[inic+posicion]);
                if (inic > 0 && posicion == 0)
                    inic--;
                else if (posicion > 0)
                    posicion--;
                break;
            /*Flecha de abajo*/
            case 80:
                gotoxy(2,7+posicion);
                setColorTexto(10);
                printf("%s", archivos[inic+posicion]);
                if (inic < (numArchivos-num) && posicion == num-1)
                    inic++;
                else if (posicion < num-1)
                    posicion++;
                break;
            }

            break;
        /*Escape*/
        case 27:
            retorno = false;
            nombreArchivo[0] = '\0';
            salir = true;
            break;
        /*Return*/
        case 13:
            strcpy(nombreArchivo, archivos[inic + posicion]);
            retorno = true;
            salir = true;
            break;
        }


    }while(!salir);

    setColorTexto(10);

    return retorno;
}

/*Agrega los datos del nuevo trayecto al archivo binario de trayectos*/
void agregaTrayectoABin(struct sTrayecto trayecto)
{
    FILE* ptr;

    /*Abrimos el archivo para escribir al final de el*/
    ptr=fopen("BASEDATOS/Activos/trayectos.activos.bin", "ab");
    /*Si es erroneo avisamos*/
    if(ptr==NULL)
    {
        gotoxy(2,31);
        printf("Error al abrir el fichero trayectos.activos.bin");
        gotoxy(2,32);
        system("pause");

    }
    else
    {
        /*Escribimos en el fichero*/
        fwrite(&trayecto,sizeof(struct sTrayecto),1,ptr);
        /*Cerramos el archivo*/
        fclose(ptr);
    }

}

/*Busca un trayecto en el archivo de trayectos activos a partir del IDSelec.
Si lo encuentra copia sus datos en la direccion del trayecto que recibe como parametro y retorna true*/
bool queTrayecto(const char* IDSelec, struct sTrayecto *pTrayecto)
{
    bool retorno = false;
    struct sTrayecto trayecto;
    FILE* ptr;

    /*Abrimos el archivo en modo lectura*/
    ptr=fopen("BASEDATOS/Activos/trayectos.activos.bin", "rb");
    if(ptr==NULL)
    {
        retorno = false;
    }
    else
    {
        /*Mientras no sea final de fichero y retorno sea false*/
        while(!feof(ptr) && retorno == false)
        {
            /*Si la lectura es correcta*/
            if(fread(&trayecto, sizeof(struct sTrayecto),1,ptr)==1)
            {
                /*Si los ids son iguales*/
                if(strcmp(trayecto.id, IDSelec)==0)
                {
                    /*Vamos copiando*/
                    strcpy(pTrayecto->id, trayecto.id);
                    strcpy(pTrayecto->e_destino, trayecto.e_destino);
                    strcpy(pTrayecto->e_origen, trayecto.e_origen);
                    strcpy(pTrayecto->frecuencia, trayecto.frecuencia);
                    strcpy(pTrayecto->h_llegada, trayecto.h_llegada);
                    strcpy(pTrayecto->h_salida, trayecto.h_salida);
                    strcpy(pTrayecto->tipo, trayecto.tipo);

                    pTrayecto->duracion=trayecto.duracion;
                    pTrayecto->precio = trayecto.precio;

                    /*Cambiamos retorno a true*/
                    retorno = true;
                }
            }

        }
        /*Cerramos el archivo*/
        fclose(ptr);
    }
    /*Devolvemos retorno*/
    return retorno;


}
