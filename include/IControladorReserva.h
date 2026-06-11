#ifndef ICONTROLADOR_RESERVA_H
#define ICONTROLADOR_RESERVA_H

#include <string>
#include <vector>
#include <set>

#include "DTFecha.h"
#include "DTConsultaViaje.h"
#include "DTListarViaje.h"
#include "DTDetalleViaje.h"
#include "DTVehiculosConductor.h"

class IControladorReserva {
public:
    virtual ~IControladorReserva() {}
    virtual bool generarReserva(std::string nickname,int codigo,int asientos)=0;
    virtual bool altaViaje(std::string matricula, DTFecha fecha, std::string origen ,std::string destino, int asientos, float precio)=0;
    virtual std::set<std::string> listarPasajeros()=0;
    virtual std::vector<DTConsultaViaje> consultarViajes(DTFecha fecha, std::string origen, std::string destino, int asientos)=0;
    virtual std::vector<DTListarViaje> listarViajes()=0;
    virtual DTDetalleViaje detalleViaje(int codigo)=0;
    virtual void eliminarViaje()=0;
    virtual void cancelarEliminarViaje()=0;
    virtual DTVehiculosConductor listarVehiculosConductor(std::string nickname)=0;
};

#endif