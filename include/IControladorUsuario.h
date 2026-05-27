#ifndef ICONTROLADOR_USUARIO_H
#define ICONTROLADOR_USUARIO_H

class IControladorUsuario() {
  public:
  virtual void altaPasajero() = 0;
  virtual void altaConductor() = 0;
  virtual void registrarVehiculo() = 0;
};

#endif