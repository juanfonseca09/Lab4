#ifndef ICONTROLADOR_RESERVA_H
#define ICONTROLADOR_RESERVA_H

class IControladorReserva() {
  public:
  virtual void listarPasajeros() = 0;
  virtual void consultarViajes() = 0;
  virtual void generarReserva() = 0;
  virtual void listarVehiculosConductor() = 0;
  virtual bool altaViaje() = 0;
};

#endif