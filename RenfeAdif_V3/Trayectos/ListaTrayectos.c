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
#include "../main/config.h"
#include "../Paradas/ListaParadas.h"
#include "../Paradas/Parada.h"

#include "ListaTrayectos.h"
#include "Trayecto.h"
#include "TrayectosDiarios.h"

void cargaListaTrayectos(struct sListaTrayectos *plTrayectos, char nombreArchivo[])
{
    int i=0;
    FILE* ptr;
    struct sTrayecto *asignacion;
    struct sTrayecto trayecto;

    /*Inicializamos*/
    inicListaTrayectos(plTrayectos);
    /*Abrimos el archivo en modo lectura*/
    ptr=fopen(nombreArchivo,"rb"); /*"BASEDATOS/Activos/trayectos.activos.bin"*/
    /*Si es erroneo*/
    if(ptr==NULL)
    {

    }
    else
    {
        /*Mientras no sea final de fichero*/
        while(!feof(ptr))
        {
            /*Leemos los datos del archivo binario de trayectos activos y los almacenamos en la lista dinamica*/
            /*Si la lectura es correcta*/
            if(fread(&trayecto,sizeof(struct sTrayecto), 1, ptr)!=0)
            {
                i++;
                if(i==1)
                {
                    /*Asignamos memoria*/
                    asignacion=calloc(sizeof(struct sTrayecto),1);
                }
                else
                {
                    asignacion=realloc(plTrayectos->lista, sizeof(struct sTrayecto)*i);

                }
                if(asignacion!=NULL)
                {

                    plTrayectos->lista=asignacion;
                    strcpy(plTrayectos->lista[i-1].id, trayecto.id);
                    strcpy(plTrayectos->lista[i-1].tipo, trayecto.tipo);
                    strcpy(plTrayectos->lista[i-1].e_origen, trayecto.e_origen);
                    strcpy(plTrayectos->lista[i-1].e_destino, trayecto.e_destino);
                    strcpy(plTrayectos->lista[i-1].h_llegada, trayecto.h_llegada);
                    strcpy(plTrayectos->lista[i-1].h_salida, trayecto.h_salida);
                    strcpy(plTrayectos->lista[i-1].frecuencia, trayecto.frecuencia);

                    plTrayectos->lista[i-1].duracion = trayecto.duracion;
                    plTrayectos->lista[i-1].precio = trayecto.precio;

                }
                else
                {
                    i--;
                }
            }
        }
        /*Guardamos el numero de trayectos*/
        plTrayectos->num=i;

    }
}

/*Cargamos la lista y mostramos por pantalla*/
void muestraListaTrayectos(char nombreArchivo[])
{
    int i=0;
    int j=0;
    int pos=0;
    struct sListaTrayectos listaTrayectos;
    int totalNumeroPantallas=0;
    int numeroDeLineas=18;

    /*Llamamos a cargaListaTrayetcos para cargar las listas*/
    cargaListaTrayectos(&listaTrayectos, nombreArchivo);

    /*Si hay 0 trayectos avisamos pon pantalla*/
    if (listaTrayectos.num==0)
    {
        gotoxy(2,31);
        printf("La lista de trayectos está vacia.");
        gotoxy(2,32);
        system("pause");
    }
    else
    {
        totalNumeroPantallas = listaTrayectos.num/18;

        /*Iniciamos la interfaz*/
        inicInterfaz();
        gotoxy(45,2);
        printf("Listado de Trayectos");

        gotoxy(2,5);
        printf("ID     Tren        Origen               Destino               Sale    Llega    Min    Precio  Frecuencia");


        /*Bucle para mostrar todas las listas de las estaciones*/
        for (j=0; j<=totalNumeroPantallas; j++)
        {

            if (j==totalNumeroPantallas)
            {
                numeroDeLineas=listaTrayectos.num%18;
            }

            gotoxy(2,7);
            /*Bucle para mostrar una lista de Estaciones*/
            for (i=0; i<numeroDeLineas; i++)
            {
                pos = 18*j + i;
                /*Llamo a muestraEstacion para que me imprima las estaciones una a una*/
                muestraTrayecto(listaTrayectos.lista[pos]);

            }
            gotoxy(2,30);
            printf("Pulsa [return] para ver mas trayectos...");
            fflush(stdin);
            getchar();

        }
    }
    /*Liberamos la memoria reservada*/
    free(listaTrayectos.lista);

}

void mantenimientoTrayectos(void)
{
    int n;
    char nombreArchivo[100]= "BASEDATOS/Activos/trayectos.activos.bin";
    char IDSelec[100];
    do
    {
        /*Llama a la funcion menuMantenimientoTrayectos()*/
        n = menuMantenimientoTrayectos();

        switch(n)
        {
        case '1':
            /*Llama a la funcion agregaTrayecto()*/
            agregaTrayecto();
            break;

        case '2':
            /*Llama a la funcion muestraListaTrayectos()*/
            muestraListaTrayectos(nombreArchivo);
            break;

        case '3':

            if(seleccionaTrayecto(IDSelec))
                /*Llama a la funcion muestraTrayectoConParadas()*/
                muestraTrayectoConParadas(IDSelec);
            break;

        case '4':
            /*Llama a la funcion eliminaTrayectosBD()*/
            eliminaTrayectosBD();
            break;

        case '5':
            buscaTrayectosDiarios();
            break;


        case '0':
            /*Finaliza la funcion, y vuelve al menu anterior*/
            system("cls");
            return;

        default:
            n=6;
            break;

        }

    }
    while (n !='0');

    return;
}

int menuMantenimientoTrayectos(void)
{
    int n;

    /*Limpiamos la pantalla*/
    system("cls");

    /*Llamamos a la funcion interfaz para volver a pintarla*/
    inicInterfaz();

    /*Pintamos por pantalla*/
    gotoxy(35,2);
    printf("Sistema De Planificación de viajes");

    gotoxy(40,5);
    printf("Mantenimiento de Trayectos");

    gotoxy(2,8);
    printf("1.Agregar un nuevo trayecto.");

    gotoxy(2,10);
    printf("2.Listar todas los trayectos.");

    gotoxy(2,12);
    printf("3.Mostrar un trayecto con paradas.");

    gotoxy(2,14);
    printf("4.Eliminar trayectos.");

    gotoxy(2,16);
    printf("5.Busca Trayectos Diarios");

    gotoxy(2,18);
    printf("0.Menu anterior.");

    gotoxy(2,28);
    printf("Introduzca una opción: ");

    fflush(stdin);
    n = getch();

    return n;
}

void muestraTrayectoConParadas(const char IDSelec[])
{

    struct sTrayecto pTrayecto;

    /*Obtenemos los datos del trayecto*/
    /*Si que trayecto devuelve true*/
    if(queTrayecto(IDSelec, &pTrayecto))
    {
        system("cls");
        inicInterfaz();
        gotoxy(2,7);
        /*Mostramos dichos datos por pantalla*/
        muestraTrayecto(pTrayecto);

        /*Mostramos en pantalla las paradas correspondientes al trayecto*/
        muestraParadasTrayectos(IDSelec);
    }

}

/*Recibe una lista de trayectos y muestra los num trayectos que se encuentran a partir de la posicion inic*/
void muestraGrupoTrayectos(struct sListaTrayectos listaTrayectos, int inic, int num)
{
    int i;
    system("cls");
    inicInterfaz();

    gotoxy(45,2);
    printf("Listado de Trayectos");

    gotoxy(2,5);
    printf("ID     Tren        Origen               Destino               Sale    Llega    Min    Precio  Frecuencia");

    gotoxy(2,28);
    printf("[return]: Seleccionar - [ESC]: Abandonar - [Flechas]: Mover");

    /*Escribimos por pantalla*/
    for (i=0; i<num; i++)
    {
        gotoxy(2,7+i);
        printf("%5s  %-5s       %-21s%-21s %s   %s    %-3d    %0.2f   %s", listaTrayectos.lista[inic+i].id, listaTrayectos.lista[inic+i].tipo, listaTrayectos.lista[inic+i].e_origen, listaTrayectos.lista[inic+i].e_destino,
               listaTrayectos.lista[inic+i].h_salida, listaTrayectos.lista[inic+i].h_llegada, listaTrayectos.lista[inic+i].duracion, listaTrayectos.lista[inic+i].precio, listaTrayectos.lista[inic+i].frecuencia);
    }
}

bool seleccionaTrayecto(char *ID_tray)
{
    int posicion=0;
    struct sListaTrayectos listaTrayectos;
    int num=18;
    bool salidaBucle=false;
    bool retorno=false;
    int inic=0;
    int b=0;
    char nombreArchivo[100]= "BASEDATOS/Activos/trayectos.activos.bin";

    /*Llamamos a cragaListaTrayectos para almacenar los trayectos activos*/
    cargaListaTrayectos(&listaTrayectos, nombreArchivo);

    /*Si numero de trayectos es 0 avisamos por pantalla*/
    if (listaTrayectos.num==0)
    {
        gotoxy(2,31);
        printf("La lista de trayectos está vacia.");
        gotoxy(2,32);
        system("pause");
    }
    else
    {

        /*Si numero de trayectos es menor que num, igualamos num a numero de trayectos*/
        if (listaTrayectos.num<num)
        {
            num=listaTrayectos.num;
        }

        /*Llamamos a muestraGrupoTrayectos para mostrar los n primeros trayectos*/
        muestraGrupoTrayectos(listaTrayectos, inic, num);

        /*Cambiamos color*/
        setColorTexto(160);
        gotoxy(2,7+posicion);

        /*Escribimos los datos del primer trayecto con los colores invertidos*/
        muestraTrayecto(listaTrayectos.lista[posicion+inic]);

        /*Bucle para movernos por la lista y salir mediante escape o return*/
        while (!salidaBucle)
        {
            b=getch();
            switch(b)
            {
            /*Escape*/
            case 27:
                salidaBucle = true;
                ID_tray[0]='\0';
                break;

            /*Return*/
            case 13:
                strcpy(ID_tray, listaTrayectos.lista[inic+posicion].id);
                retorno = true;
                salidaBucle = true;
                setColorTexto(10);
                gotoxy(2,31);
                printf("Ha seleccionado el trayecto con ID %s\n", listaTrayectos.lista[posicion+inic].id);
                gotoxy(2,32);
                system("pause");
                break;


            /*Tecla especial*/
            case 224:
                b=getch();
                switch(b)
                {
                /*Flecha de arriba*/
                case 72:
                    gotoxy(2,7+posicion);
                    if (inic > 0 && posicion == 0)
                        inic--;
                    else if (posicion > 0)
                        posicion--;
                    break;
                /*Flecha de abajo*/
                case 80:
                    gotoxy(2,7+posicion);
                    if (inic < (listaTrayectos.num-num) && posicion == num-1)
                        inic++;
                    else if (posicion < num-1)
                        posicion++;
                    break;
                }

            }
            setColorTexto(10);
            /*Llamamos a muestraGrupoTrayectos para mostrar los trayectos*/
            muestraGrupoTrayectos(listaTrayectos, inic, num);

            setColorTexto(160);
            gotoxy(2,7+posicion);
            /*Escribimos los datos del trayecto con los colores invertidos*/
            muestraTrayecto(listaTrayectos.lista[posicion+inic]);

        }
        setColorTexto(10);

        /*Liberamos la memoria*/
        free(listaTrayectos.lista);
    }
    return retorno;
}

void eliminaTrayectosBD(void)
{
    char ID_tray[100];
    char ruta[200];
    struct sListaTrayectos plTrayectos;

    char nombreArchivo[100]= "BASEDATOS/Activos/trayectos.activos.bin";

    /*Obtenemos el id del trayecto que el usuario desea eliminar*/
    /*Si seleccionaTrayecto devuleve true*/
    if(seleccionaTrayecto(ID_tray))
    {
        /*Llamamos a cragaListaTrayectos para cargar las listas*/
        cargaListaTrayectos(&plTrayectos, nombreArchivo);
        /*Si numero de trayectos es mayor que 0*/
        if (plTrayectos.num>0)
        {
            /*Invocamos a eliminaTrayectoLista para eliminar el trayecto seleccionado*/
            /*Si eliminaTrayectoLista devuelve true*/
            if(eliminaTrayectoLista(ID_tray, &plTrayectos))
            {
                /*Actualizamos el archivo de trayectos activos*/
                /*Llamamos a grabaListaTrayecto*/
                grabaListaTrayectos(plTrayectos, nombreArchivo);

                /*Concatenamos en ruta la 'ruta' completa al archivo*/
                sprintf(ruta, "BASEDATOS/Activos/Paradas/paradas.%s.bin",ID_tray);
                /*Le eliminamos*/
                remove(ruta);

                /*Eliminamos las paradas de ese trayecto de la lista general de paradas activas*/
                eliminaParadasTrayecto(ID_tray);
            }
        }
        /*Liberamos la memoria reservada*/
        free(plTrayectos.lista);
    }

}

/*Elimina los elementos del conjunto de vectores paralelos corrspondientes al trayecto seleccionado*/
bool eliminaTrayectoLista(char IDSelec[], struct sListaTrayectos *plTrayectos)
{
    int i=0;
    int j=0;
    bool retorno = false;

    gotoxy(2,31);
    printf("Se va eliminar el trayecto con ID %s         ", IDSelec);
    gotoxy(2,32);
    system("pause");

    /*Eliminamos el archivo siguiendo el algoritmo*/
    while(i<plTrayectos->num && strcmp(IDSelec, plTrayectos->lista[i].id)!=0)
    {
        i++;
    }
    if(i<plTrayectos->num && strcmp(IDSelec, plTrayectos->lista[i].id)==0)
    {
        for (j=i; j<(plTrayectos->num-1); j++)
        {
            strcpy(plTrayectos->lista[j].id, plTrayectos->lista[j+1].id);
            strcpy(plTrayectos->lista[j].tipo, plTrayectos->lista[j+1].tipo);
            strcpy(plTrayectos->lista[j].e_origen, plTrayectos->lista[j+1].e_origen);
            strcpy(plTrayectos->lista[j].e_destino, plTrayectos->lista[j+1].e_destino);
            strcpy(plTrayectos->lista[j].h_salida, plTrayectos->lista[j+1].h_salida);
            strcpy(plTrayectos->lista[j].h_llegada, plTrayectos->lista[j+1].h_llegada);
            plTrayectos->lista[j].duracion= plTrayectos->lista[j+1].duracion;
            plTrayectos->lista[j].precio= plTrayectos->lista[j+1].precio;
            strcpy(plTrayectos->lista[j].frecuencia, plTrayectos->lista[j+1].frecuencia);
        }
        /*El numero de trayectos disminuye despues de eliminar un trayecto*/
        plTrayectos->num--;
        retorno = true;
    }

    return retorno;
}

/*Recibe una lista de trayectos y la escribe en el archivo binario de trayectos activos*/
void grabaListaTrayectos(struct sListaTrayectos lTrayectos, char nombreArchivo[])
{
    int i=0;
    FILE* ptr;

    /*Abrimos el archivo de texto en modo escritura*/
    ptr=fopen(nombreArchivo, "wb"); /*"BASEDATOS/Activos/trayectos.activos.bin"*/
    /*Si es nulo avisamos por pantalla*/
    if(ptr==NULL)
    {
        gotoxy(2,31);
        printf("Error al abrir el fichero trayectos.avtivos.bin");
        gotoxy(2,32);
        system("pause");
    }
    else
    {
        for (i=0; i<lTrayectos.num; i++)
        {
            /*Escribimos en el archivo de texto*/
            fwrite(&lTrayectos.lista[i],sizeof(struct sTrayecto),1,ptr);
        }
        /*Cerramos el archivo de texto*/
        fclose(ptr);
    }
}

/*Recibe una lista de trayectos e inicializa sus atributos*/
void inicListaTrayectos(struct sListaTrayectos *plTrayectos)
{
    /*Inicializamos la estructura*/
    plTrayectos->num=0;
    plTrayectos->lista=NULL;
}




