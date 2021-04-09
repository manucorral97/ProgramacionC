#ifndef __ListaEstaciones_h__
    #define __ListaEstaciones_h__

    #include "../main/config.h"
    #include <stdbool.h>

    struct sListaEstaciones
    {
        int num;
        struct sEstacion *lista;
    };

    void mantenimientoEstaciones(void);
    int menuMantenimientoEstaciones(void);
    void muestraListaEstaciones(void);
    void cargaListaEstaciones(struct sListaEstaciones *plEstaciones);
    void muestraGrupoEstaciones(struct sListaEstaciones lEstaciones, int inic, int num);
    void eliminaEstacionesBD(void);
    void inicListaEstaciones(struct sListaEstaciones *plEstaciones);

#endif

