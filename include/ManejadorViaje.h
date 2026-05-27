#ifndef MANEJADOR_VIAJE_H
#define MANEJADOR_VIAJE_H

#include "Viaje.h"

class ManejadorViaje() {
private:
  std::set<Viaje>;
public:
  void agregarViaje(Viaje* v);
};

#endif