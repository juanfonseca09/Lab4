#ifndef DT_FECHA_H
#define DT_FECHA_H

#include <iostream>

class DTFecha {
private:
    int dia;
    int mes;
    int anio;

public:
    DTFecha();
    DTFecha(int dia, int mes, int anio);

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    bool operator==(const DTFecha& other) const;
    bool operator<(const DTFecha& other) const;
};

std::ostream& operator<<(std::ostream& os, const DTFecha& f);

#endif