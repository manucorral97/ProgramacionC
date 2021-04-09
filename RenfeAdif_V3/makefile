all: RenfeAdif_V3.exe

RenfeAdif_V3.exe: auxiliar.o Estacion.o ListaEstaciones.o EstacionesCercanas.o interfaz.o Panel.o mainRenfeAdif.o menus.o ListaTrayectos.o Trayecto.o TrayectosDiarios.o ListaParadas.o Parada.o
	gcc -o RenfeAdif_V3.exe auxiliar.o Estacion.o ListaEstaciones.o EstacionesCercanas.o interfaz.o panel.o mainRenfeAdif.o menus.o ListaTrayectos.o Trayecto.o TrayectosDiarios.o ListaParadas.o Parada.o

auxiliar.o: auxiliar/auxiliar.c auxiliar/auxiliar.h
	gcc -c -Wall -pedantic -ansi auxiliar/auxiliar.c

Estacion.o: Estaciones/Estacion.c Estaciones/Estacion.h
	gcc -c -Wall -pedantic -ansi Estaciones/Estacion.c

ListaEstaciones.o: Estaciones/ListaEstaciones.c Estaciones/ListaEstaciones.h
	gcc -c -Wall -pedantic -ansi Estaciones/ListaEstaciones.c

EstacionesCercanas.o: Estaciones/EstacionesCercanas.c Estaciones/EstacionesCercanas.h
	gcc -c -Wall -pedantic -ansi Estaciones/EstacionesCercanas.c

interfaz.o: Interfaz/interfaz.c Interfaz/interfaz.h
	gcc -c -Wall -pedantic -ansi Interfaz/interfaz.c

Panel.o: LibroClaves/Panel.c LibroClaves/Panel.h
	gcc -c -Wall -pedantic -ansi LibroClaves/Panel.c

mainRenfeAdif.o : main/mainRenfeAdif.c main/config.h
	gcc -c -Wall -pedantic -ansi main/mainRenfeAdif.c

menus.o : main/menus.c main/menus.h main/config.h
	gcc -c -Wall -pedantic -ansi main/menus.c

ListaTrayectos.o: Trayectos/ListaTrayectos.c Trayectos/ListaTrayectos.h
	gcc -c -Wall -pedantic -ansi Trayectos/ListaTrayectos.c

Trayecto.o: Trayectos/Trayecto.c Trayectos/Trayecto.h
	gcc -c -Wall -pedantic -ansi Trayectos/Trayecto.c

TrayectosDiarios.o: Trayectos/TrayectosDiarios.c Trayectos/TrayectosDiarios.h
	gcc -c -Wall -pedantic -ansi Trayectos/TrayectosDiarios.c

ListaParadas.o: Paradas/ListaParadas.c Paradas/ListaParadas.h
	gcc -c -Wall -pedantic -ansi Paradas/ListaParadas.c

Parada.o: Paradas/Parada.c Paradas/Parada.h
	gcc -c -Wall -pedantic -ansi Paradas/Parada.c

clean:
	del RenfeAdif_V3.exe auxiliar.o Estacion.o ListaEstaciones.o EstacionesCercanas.o interfaz.o Panel.o mainRenfeAdif.o menus.o ListaTrayectos.o Trayecto.o TrayectosDiarios.o ListaParadas.o Parada.o