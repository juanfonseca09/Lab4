#ifndef CONTROLADOR_CALIFICACION_H
#define CONTROLADOR_CALIFICACION_H

#include <string>
#include <vector>

#include "IControladorCalificacion.h"
#include "DTUsuario.h"
#include "DTListarViaje.h"
#include "DTUsuarioViaje.h"

class ControladorCalificacion : public IControladorCalificacion {
private:
    static ControladorCalificacion* instancia;

    std::string nicknameRecordado;
    int codigoRecordado;

    ControladorCalificacion();

public:
    static ControladorCalificacion* getInstance();

    std::vector<DTUsuario> listarUsuarios();

    std::vector<DTListarViaje> listarViajes(
        std::string nickname
    );

    std::vector<DTUsuarioViaje> listarUsuariosViaje(
        int codigo
    );

    bool calificarUsuario(
        std::string nicknameCalificado,
        int puntaje
    );

    void recordarCodigoViaje(int codigo);
    void recordarUsuarioCalificador(std::string nickname);
};

#endif