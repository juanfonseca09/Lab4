#ifndef ICONTROLADOR_CALIFICACION_H
#define ICONTROLADOR_CALIFICACION_H

class IControladorCalificacion() {
public:
  virtual void listarUsuarios() = 0;
  virtual void listarViajes() = 0;
  virtual void listarUsuariosViaje() = 0;
  virtual void calificarUsuario() = 0;
};

#endif