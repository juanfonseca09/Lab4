#include "../include/Menu.h"
#include "../include/Fabrica.h"

int main() {
    Fabrica* fabrica = Fabrica::getInstance();
    IControladorUsuario* ctrlUsuario = fabrica->getIControladorUsuario();
    IControladorFechaActual* ctrlFecha = fabrica->getIControladorFechaActual();
    IControladorReserva* ctrlReserva = fabrica->getIControladorReserva();
    IControladorCalificacion* ctrlCalificacion = fabrica->getIControladorCalificacion();

    Menu menu(ctrlUsuario, ctrlFecha, ctrlReserva, ctrlCalificacion);
    // precargar datos (opcional)
    menu.mostrarMenu();
    return 0;
}
