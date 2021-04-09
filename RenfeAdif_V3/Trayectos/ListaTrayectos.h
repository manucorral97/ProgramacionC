#ifndef __ListaTrayectos_h__

    #define __ListaTrayectos_h__
    #include <stdbool.h>
    #include "../main/config.h"
    struct sListaTrayectos
    {
        int num;
        struct sTrayecto *lista;
    };

    void cargaListaTrayectos(struct sListaTrayectos *plTrayectos, char nombreArchivo[]);
    void muestraListaTrayectos(char nombreArchivo[]);
    void mantenimientoTrayectos(void);
    int menuMantenimientoTrayectos(void);
    void muestraTrayectoConParadas(const char IDSelec[]);
    void muestraGrupoTrayectos(struct sListaTrayectos listaTrayectos, int inic, int num);
    bool seleccionaTrayecto(char *ID_tray);
    void eliminaTrayectosBD(void);
    bool eliminaTrayectoLista(char IDSelec[], struct sListaTrayectos *plTrayectos);
    void grabaListaTrayectos(struct sListaTrayectos lTrayectos, char nombreArchivo[]);
    void inicListaTrayectos(struct sListaTrayectos *plTrayectos);

#endif

