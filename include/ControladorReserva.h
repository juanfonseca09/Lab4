#ifndef CONTROLADOR_RESERVA_H
#define CONTROLADOR_RESERVA_H

#include <string>
#include <vector>
#include <set>

#include "IControladorReserva.h"
#include "DTFecha.h"
#include "DTConsultaViaje.h"
#include "DTListarViaje.h"
#include "DTDetalleViaje.h"
#include "DTVehiculosConductor.h"

class ControladorReserva : public IControladorReserva {
private:
    static ControladorReserva* instancia;
    int codigoRecordado;

    ControladorReserva();

public:
    static ControladorReserva* getInstance();

    bool generarReserva(std::string nickname, int codigo, int asientos);
    bool altaViaje(std::string matricula, DTFecha fecha, std::string origen, std::string destino, int asientos, float precio);

    std::set<std::string> listarPasajeros();
    std::vector<DTConsultaViaje> consultarViajes(DTFecha fecha, std::string origen, std::string destino, int asientos);
    std::vector<DTListarViaje> listarViajes();

    DTDetalleViaje detalleViaje(int codigo);
    void eliminarViaje();
    void cancelarEliminarViaje();

    std::vector<DTVehiculosConductor> listarVehiculosConductor(std::string nickname);
};

#endif