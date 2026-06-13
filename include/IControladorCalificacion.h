#ifndef ICONTROLADOR_CALIFICACION_H
#define ICONTROLADOR_CALIFICACION_H

#include <vector>
#include <string>

#include "DTUsuario.h"
#include "DTListarViaje.h"
#include "DTUsuarioViaje.h"

class IControladorCalificacion {
public:
    virtual ~IControladorCalificacion() {}

    virtual std::vector<DTUsuario> listarUsuarios() = 0;

    virtual std::vector<DTListarViaje> listarViajes(
        std::string nickname
    ) = 0;

    virtual std::vector<DTUsuarioViaje> listarUsuariosViaje(
        int codigo
    ) = 0;

    virtual bool calificarUsuario(
        std::string nicknameCalificado,
        int puntaje
    ) = 0;

    virtual void recordarCodigoViaje(
        int codigo
    ) = 0;

    virtual void recordarUsuarioCalificador(
        std::string nickname
    ) = 0;
};

#endif