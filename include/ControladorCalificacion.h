#ifndef CONTROLADOR_CALIFICACION_H
#define CONTROLADOR_CALIFICACION_H

#include "IControladorCalificacion.h"

class ControladorCalificacion : public IControladorCalificacion {
public:
  void listarUsuarios();
  void listarViajes();
  void listarUsuariosViaje();
  void calificarUsuario();
};

#endif