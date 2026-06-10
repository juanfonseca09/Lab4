#ifndef MENU_H
#define MENU_H
#include "IControladorUsuario.h"
#include "IControladorFechaActual.h"
#include "IControladorReserva.h"
#include "IControladorCalificacion.h"

class Menu {
private:
    IControladorUsuario* controladorUsuario;
    IControladorFechaActual* controladorFecha;
    IControladorReserva* controladorReserva;
    IControladorCalificacion* controladorCalificacion;

    void altaUsuario();
    void altaViaje();
    void generarReserva();
    void calificarUsuario();
    void eliminarViaje();
    void administrarFechaActual();
    void cargarDatos();

public:
    Menu(IControladorUsuario* ctrlUsuario, IControladorFechaActual* ctrlFecha, IControladorReserva* ctrlReserva, IControladorCalificacion* ctrlCalificacion);
    ~Menu();
    void mostrarMenu();
};

#endif
