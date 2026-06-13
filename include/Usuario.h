#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>

class Calificacion;
class Viaje;

class Usuario {
protected:
    std::string nickname;
    std::string nombre;
    std::string contrasena;
    std::string email;

    std::vector<Calificacion*> calificacionesRealizadas;
    std::vector<Calificacion*> calificacionesRecibidas;

public:
    Usuario(std::string nickname, std::string nombre, std::string contrasena, std::string email);
    virtual ~Usuario();

    std::string getNickname();
    std::string getNombre();
    std::string getContrasena();
    std::string getEmail();

    void agregarCalificacionRealizada(Calificacion* calificacion);
    void agregarCalificacionRecibida(Calificacion* calificacion);

    std::vector<Calificacion*> getCalificacionesRealizadas();
    std::vector<Calificacion*> getCalificacionesRecibidas();

    void eliminarReferenciasCalificacionesDeViaje(Viaje* viaje);

    float getCalifProm();
};

#endif