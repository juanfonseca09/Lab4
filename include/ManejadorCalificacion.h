#ifndef MANEJADOR_CALIFICACION_H
#define MANEJADOR_CALIFICACION_H

#include <vector>

class Calificacion;

class ManejadorCalificacion {
private:
    static ManejadorCalificacion* instancia;
    std::vector<Calificacion*> calificaciones;
    ManejadorCalificacion();
public:
    static ManejadorCalificacion* getInstance();
    void agregarCalificacion(Calificacion* c);
    std::vector<Calificacion*> getCalificaciones();
};

#endif