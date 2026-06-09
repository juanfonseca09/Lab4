#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>

class Calificacion;

class Usuario {
//para q las clases hijas puedan acceder directamente a los atributos
protected:
    std::string nickname;
    std::string nombre;
    std::string contrasena;
    std::string email; 
    std::vector<Calificacion*> realizadas;
    std::vector<Calificacion*> recibidas;
    // califprom se calcula luego 
public:
    Usuario(std::string nickname, std::string nombre, std::string contrasena, std::string email);
    virtual ~Usuario();
    std::string getNickname() const;
    std::string getNombre() const;
    std::string getContrasena() const;
    std::string getEmail() const;
    float getCalifProm() const;
    void agregarCalificacionRealizada(Calificacion* c);
    void agregarCalificacionRecibida(Calificacion* c);
    std::vector<Calificacion*> getRealizadas() const;
    std::vector<Calificacion*> getRecibidas() const;
};

#endif