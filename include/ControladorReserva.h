#ifndef CONTROLADOR_RESERVA_H
#define CONTROLADOR_RESERVA_H

#include "IControladorReserva.h"

class ControladorReserva : public IControladorReserva {
public:
  static ControladorReserva* getInstance();
  
  void listarPasajeros();
  void consultarViajes();
  void generarReserva();
  void listarVehiculosConductor();
  bool altaViaje();
};

#endif