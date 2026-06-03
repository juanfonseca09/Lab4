#ifndef CONTROLADOR_USUARIO_H
#define CONTROLADOR_USUARIO_H

#include "IControladorUsuario.h"

class ControladorUsuario : public IControladorUsuario {
public:
  static ControladorUsuario* getInstance();
  
  void altaPasajero();
  void altaConductor();
  void registrarVehiculo();
};

#endif