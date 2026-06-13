#include "../include/Menu.h"
#include "../include/Fabrica.h"
#include "../include/IControladorFechaActual.h"
#include "../include/IControladorUsuario.h"
#include "../include/IControladorReserva.h"
#include "../include/IControladorCalificacion.h"
#include "../include/CargaDatos.h"
#include "../include/DTFecha.h"
#include "../include/TipoLibreta.h"
#include "../include/TipoVehiculo.h"
#include "../include/TipoUsuario.h"
#include "../include/DTVehiculosConductor.h"
#include "../include/DTConsultaViaje.h"
#include "../include/DTListarViaje.h"
#include "../include/DTDetalleViaje.h"
#include "../include/DTDetalleVehiculo.h"
#include "../include/DTDetalleReserva.h"
#include "../include/DTUsuario.h"
#include "../include/DTUsuarioViaje.h"

#include <iostream>
#include <limits>
#include <string>
#include <set>
#include <vector>

static TipoVehiculo intATipoVehiculo(int tipo) {
    if (tipo == 0) {
        return Auto;
    }

    return Moto;
}

static std::string tipoVehiculoATexto(TipoVehiculo tipo) {
    if (tipo == Auto) {
        return "Auto";
    }

    return "Moto";
}

static std::string tipoUsuarioATexto(TipoUsuario tipo) {
    if (tipo == UsuarioConductor) {
        return "Conductor";
    }

    return "Pasajero";
}

static bool leerEntero(int& valor) {
    if (!(std::cin >> valor)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

static bool leerFloat(float& valor) {
    if (!(std::cin >> valor)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

/*
 * Esto evita el problema que vimos:
 * si queda una linea vacia antes de la matricula, no dejamos que capacidad lea la matricula.
 */
static void leerLineaNoVacia(std::string& valor) {
    std::getline(std::cin, valor);

    while (valor == "" && std::cin.good()) {
        std::getline(std::cin, valor);
    }
}

void Menu::altaUsuario() {
    Fabrica* fabrica = Fabrica::getInstance();
    IControladorUsuario* controlador = fabrica->getIControladorUsuario();

    int tipoUsuario;

    std::cout << "1. Alta Pasajero\n";
    std::cout << "2. Alta Conductor\n";
    std::cout << "Seleccione: ";

    if (!leerEntero(tipoUsuario)) {
        std::cout << "Opcion invalida.\n";
        return;
    }

    if (tipoUsuario != 1 && tipoUsuario != 2) {
        std::cout << "Opcion invalida.\n";
        return;
    }

    std::string nickname, nombre, contrasena, email;

    std::cout << "Ingrese nickname: ";
    std::getline(std::cin, nickname);

    std::cout << "Ingrese nombre: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese contrasena: ";
    std::getline(std::cin, contrasena);

    std::cout << "Ingrese email: ";
    std::getline(std::cin, email);

    if (tipoUsuario == 1) {
        std::string ci;

        std::cout << "Ingrese CI: ";
        std::getline(std::cin, ci);

        bool usuarioOk = controlador->altaPasajero(nickname, nombre, contrasena, email, ci);

        if (!usuarioOk) {
            std::cout << "Error al registrar pasajero.\n";
        }

        return;
    }

    bool tieneMotoProfesional = false;
    bool tieneMotoAmateur = false;
    bool tieneAutoProfesional = false;
    bool tieneAutoAmateur = false;

    int cantLibretas = 0;
    int agregarLibreta = 1;

    while (agregarLibreta == 1 && cantLibretas < 4) {
        int tipoLibreta;

        std::cout << "\n=== Registrar Libreta ===\n";
        std::cout << "0. Moto (Profesional)\n";
        std::cout << "1. Moto (Amateur)\n";
        std::cout << "2. Auto (Profesional)\n";
        std::cout << "3. Auto (Amateur)\n";
        std::cout << "Seleccione el tipo de libreta: ";

        if (!leerEntero(tipoLibreta)) {
            std::cout << "Opcion invalida.\n";
            continue;
        }

        bool yaExiste = false;

        if (tipoLibreta == 0) {
            if (tieneMotoProfesional) {
                yaExiste = true;
            } else {
                tieneMotoProfesional = true;
                cantLibretas++;
            }
        } else if (tipoLibreta == 1) {
            if (tieneMotoAmateur) {
                yaExiste = true;
            } else {
                tieneMotoAmateur = true;
                cantLibretas++;
            }
        } else if (tipoLibreta == 2) {
            if (tieneAutoProfesional) {
                yaExiste = true;
            } else {
                tieneAutoProfesional = true;
                cantLibretas++;
            }
        } else if (tipoLibreta == 3) {
            if (tieneAutoAmateur) {
                yaExiste = true;
            } else {
                tieneAutoAmateur = true;
                cantLibretas++;
            }
        } else {
            std::cout << "Opcion invalida.\n";
            continue;
        }

        if (yaExiste) {
            std::cout << "Esa libreta ya fue ingresada.\n";
        } else {
            std::cout << "Libreta agregada.\n";
        }

        if (cantLibretas < 4) {
            std::cout << "¿Desea agregar otra libreta? (1: Si, 0: No): ";

            if (!leerEntero(agregarLibreta)) {
                agregarLibreta = 0;
            }
        } else {
            std::cout << "Se ha alcanzado el limite maximo de libretas.\n";
        }
    }

    if (cantLibretas == 0) {
        std::cout << "Debe ingresar al menos una libreta para registrar un conductor.\n";
        return;
    }

    std::set<TipoLibreta> libretas;

    if (tieneMotoProfesional) {
        libretas.insert(MotoProfesional);
    }

    if (tieneMotoAmateur) {
        libretas.insert(MotoAmateur);
    }

    if (tieneAutoProfesional) {
        libretas.insert(AutoProfesional);
    }

    if (tieneAutoAmateur) {
        libretas.insert(AutoAmateur);
    }

    bool usuarioOk = controlador->altaConductor(nickname, nombre, contrasena, email, libretas);

    if (!usuarioOk) {
        std::cout << "Error al registrar conductor.\n";
        return;
    }

    int agregarVehiculo = 1;

while (agregarVehiculo == 1) {
    std::string matricula, marca, modelo;
    int capacidad;
    int tipo;

    std::cout << "\n=== Registrar Vehiculo ===\n";

    std::cout << "Ingrese matricula: ";
    std::cin >> matricula;

/*
 * En la entrada de prueba aparecen ceros antes de la matricula.
 * Los salteamos para no desacomodar la lectura del vehiculo.
 */
    while (matricula == "0" && std::cin.good()) {
        std::cin >> matricula;
    }   

    std::cout << "Ingrese capacidad: ";
    std::cin >> capacidad;

    std::cout << "Ingrese marca: ";
    std::cin >> marca;

    std::cout << "Ingrese modelo: ";
    std::cin >> modelo;

    std::cout << "Ingrese tipo (0: Auto, 1: Moto): ";

    if (!(std::cin >> tipo)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Datos invalidos para registrar el vehiculo.\n";
        agregarVehiculo = 0;
        continue;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tipo != 0 && tipo != 1) {
        std::cout << "Tipo de vehiculo invalido.\n";
    } else {
        int resultadoRegistrarVehiculo = controlador->registrarVehiculo(
            nickname,
            matricula,
            capacidad,
            marca,
            modelo,
            intATipoVehiculo(tipo)
        );

        if (resultadoRegistrarVehiculo == -1) {
            std::cout << "Ya existe un vehiculo con esa matricula.\n";
        } else if (resultadoRegistrarVehiculo == -2) {
            std::cout << "El conductor no tiene la libreta necesaria para registrar ese vehiculo.\n";
        } else if (resultadoRegistrarVehiculo == -3) {
            std::cout << "Datos invalidos para registrar el vehiculo.\n";
        } else if (resultadoRegistrarVehiculo == 0) {
            std::cout << "Vehiculo registrado exitosamente.\n";
        }
    }

    std::cout << "¿Desea agregar otro vehiculo? (1: Si, 0: No): ";

    if (!(std::cin >> agregarVehiculo)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        agregarVehiculo = 0;
    } else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
}

void Menu::altaViaje() {
    Fabrica* fabrica = Fabrica::getInstance();
    IControladorReserva* controlador = fabrica->getIControladorReserva();

    std::string nickname, matricula, origen, destino;
    int dia, mes, anio, asientos;
    float precio;

    std::cout << "Ingrese nickname del conductor: ";
    std::getline(std::cin, nickname);

    std::vector<DTVehiculosConductor> vehiculos = controlador->listarVehiculosConductor(nickname);

    for (unsigned int i = 0; i < vehiculos.size(); i++) {
        std::cout << "> Matricula: " << vehiculos[i].getMatricula()
                  << ", Marca: " << vehiculos[i].getMarca()
                  << ", Capacidad: " << vehiculos[i].getCapacidad() << "\n";
    }

    std::cout << "Ingrese matricula del vehiculo a utilizar: ";
    std::getline(std::cin, matricula);

    bool matriculaValida = false;

    for (unsigned int i = 0; i < vehiculos.size(); i++) {
        if (vehiculos[i].getMatricula() == matricula) {
            matriculaValida = true;
        }
    }

    if (!matriculaValida) {
        std::cout << "Matricula invalida.\n";
        return;
    }

    std::cout << "Ingrese fecha del viaje (dia mes anio): ";
    if (!(std::cin >> dia >> mes >> anio)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Fecha invalida.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Ingrese origen: ";
    std::getline(std::cin, origen);

    std::cout << "Ingrese destino: ";
    std::getline(std::cin, destino);

    std::cout << "Ingrese cantidad de asientos: ";
    if (!leerEntero(asientos)) {
        std::cout << "Cantidad de asientos invalida.\n";
        return;
    }

    std::cout << "Ingrese precio por asiento: ";
    if (!leerFloat(precio)) {
        std::cout << "Precio invalido.\n";
        return;
    }

    bool viajeOk = controlador->altaViaje(matricula, DTFecha(dia, mes, anio), origen, destino, asientos, precio);

    if (viajeOk) {
        std::cout << "Viaje registrado exitosamente.\n";
    } else {
        std::cout << "Error al registrar el viaje.\n";
    }
}

void Menu::generarReserva() {
    Fabrica* fabrica = Fabrica::getInstance();
    IControladorReserva* controlador = fabrica->getIControladorReserva();

    std::set<std::string> pasajeros = controlador->listarPasajeros();

    std::set<std::string>::iterator itPas;

    for (itPas = pasajeros.begin(); itPas != pasajeros.end(); ++itPas) {
        std::cout << "> " << *itPas << "\n";
    }

    std::string nickname;

    std::cout << "Ingrese nickname del pasajero: ";
    std::getline(std::cin, nickname);

    bool nicknameValido = pasajeros.find(nickname) != pasajeros.end();

    if (!nicknameValido) {
        std::cout << "Nickname invalido.\n";
        return;
    }

    int dia, mes, anio, asientos;
    std::string origen, destino;

    std::cout << "Ingrese fecha del viaje a consultar (dia mes anio): ";
    if (!(std::cin >> dia >> mes >> anio)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Fecha invalida.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Ingrese origen: ";
    std::getline(std::cin, origen);

    std::cout << "Ingrese destino: ";
    std::getline(std::cin, destino);

    std::cout << "Ingrese cantidad de asientos a reservar: ";
    if (!leerEntero(asientos)) {
        std::cout << "Cantidad de asientos invalida.\n";
        return;
    }

    std::vector<DTConsultaViaje> viajes = controlador->consultarViajes(
        DTFecha(dia, mes, anio),
        origen,
        destino,
        asientos
    );

    for (unsigned int i = 0; i < viajes.size(); i++) {
        std::cout << "> Codigo: " << viajes[i].getCodigo()
                  << ", Marca: " << viajes[i].getMarca()
                  << ", Modelo: " << viajes[i].getModelo()
                  << ", Conductor: " << viajes[i].getConductor()
                  << ", CalificacionPromedio: " << viajes[i].getCalificacionProm()
                  << ", PrecioTotal: " << viajes[i].getPrecioTotal() << "\n";
    }

    if (viajes.empty()) {
        std::cout << "No hay viajes disponibles.\n";
        return;
    }

    int codigo;

    std::cout << "Ingrese codigo del viaje a reservar: ";
    if (!leerEntero(codigo)) {
        std::cout << "Codigo invalido.\n";
        return;
    }

    bool codigoValido = false;

    for (unsigned int i = 0; i < viajes.size(); i++) {
        if (viajes[i].getCodigo() == codigo) {
            codigoValido = true;
        }
    }

    if (!codigoValido) {
        std::cout << "Codigo invalido.\n";
        return;
    }

    bool reservaOk = controlador->generarReserva(nickname, codigo, asientos);

    if (reservaOk) {
        std::cout << "Reserva realizada exitosamente.\n";
    } else {
        std::cout << "Error al realizar la reserva.\n";
    }
}

void Menu::calificarUsuario() {
    Fabrica* fabrica = Fabrica::getInstance();
    IControladorCalificacion* controlador = fabrica->getIControladorCalificacion();

    std::vector<DTUsuario> usuarios = controlador->listarUsuarios();

    for (unsigned int i = 0; i < usuarios.size(); i++) {
        std::cout << "> Nickname: " << usuarios[i].getNickname()
                  << ", Nombre: " << usuarios[i].getNombre() << "\n";
    }

    std::string nickname;

    std::cout << "Ingrese su nickname: ";
    std::getline(std::cin, nickname);

    bool nicknameValido = false;

    for (unsigned int i = 0; i < usuarios.size(); i++) {
        if (usuarios[i].getNickname() == nickname) {
            nicknameValido = true;
        }
    }

    if (!nicknameValido) {
        std::cout << "Nickname invalido.\n";
        return;
    }

    std::vector<DTListarViaje> viajes = controlador->listarViajes(nickname);

    for (unsigned int i = 0; i < viajes.size(); i++) {
        std::cout << "> Codigo: " << viajes[i].getCodigo()
                  << ", Fecha: " << viajes[i].getFecha()
                  << ", Origen: " << viajes[i].getOrigen()
                  << ", Destino: " << viajes[i].getDestino()
                  << ", Conductor: " << viajes[i].getConductor() << "\n";
    }

    if (viajes.empty()) {
        std::cout << "No hay viajes para calificar.\n";
        return;
    }

    int codigo;

    std::cout << "Ingrese codigo del viaje: ";
    if (!leerEntero(codigo)) {
        std::cout << "Codigo invalido.\n";
        return;
    }

    bool codigoValido = false;

    for (unsigned int i = 0; i < viajes.size(); i++) {
        if (viajes[i].getCodigo() == codigo) {
            codigoValido = true;
        }
    }

    if (!codigoValido) {
        std::cout << "Codigo invalido.\n";
        return;
    }

    std::vector<DTUsuarioViaje> usuariosViaje = controlador->listarUsuariosViaje(codigo);

    for (unsigned int i = 0; i < usuariosViaje.size(); i++) {
        std::cout << "> Nickname: " << usuariosViaje[i].getNickname()
                  << ", Tipo: " << tipoUsuarioATexto(usuariosViaje[i].getTipo()) << "\n";
    }

    if (usuariosViaje.empty()) {
        std::cout << "No hay usuarios para calificar.\n";
        return;
    }

    std::string nicknameCalificado;
    int calificacion;

    std::cout << "Ingrese nickname del usuario a calificar: ";
    std::getline(std::cin, nicknameCalificado);

    std::cout << "Ingrese calificacion (1-5): ";
    if (!leerEntero(calificacion)) {
        std::cout << "Calificacion invalida.\n";
        return;
    }

    bool nicknameCalificadoValido = false;

    for (unsigned int i = 0; i < usuariosViaje.size(); i++) {
        if (usuariosViaje[i].getNickname() == nicknameCalificado) {
            nicknameCalificadoValido = true;
        }
    }

    if (!nicknameCalificadoValido) {
        std::cout << "Nickname invalido.\n";
        return;
    }

    bool calificacionOk = controlador->calificarUsuario(nicknameCalificado, calificacion);

    if (calificacionOk) {
        std::cout << "Calificacion exitosa.\n";
    } else {
        std::cout << "Error al calificar.\n";
    }
}

void Menu::eliminarViaje() {
    Fabrica* fabrica = Fabrica::getInstance();
    IControladorReserva* controlador = fabrica->getIControladorReserva();

    std::vector<DTListarViaje> viajes = controlador->listarViajes();

    for (unsigned int i = 0; i < viajes.size(); i++) {
        std::cout << "> Codigo: " << viajes[i].getCodigo()
                  << ", Fecha: " << viajes[i].getFecha()
                  << ", Origen: " << viajes[i].getOrigen()
                  << ", Destino: " << viajes[i].getDestino()
                  << ", Conductor: " << viajes[i].getConductor() << "\n";
    }

    if (viajes.empty()) {
        std::cout << "No hay viajes registrados.\n";
        return;
    }

    int codigo;

    std::cout << "Ingrese codigo del viaje a eliminar: ";
    if (!leerEntero(codigo)) {
        std::cout << "Codigo invalido.\n";
        return;
    }

    bool codigoValido = false;

    for (unsigned int i = 0; i < viajes.size(); i++) {
        if (viajes[i].getCodigo() == codigo) {
            codigoValido = true;
        }
    }

    if (!codigoValido) {
        std::cout << "Codigo invalido.\n";
        return;
    }

    DTDetalleViaje detalle = controlador->detalleViaje(codigo);
    DTDetalleVehiculo vehiculo = detalle.getVehiculo();
    std::vector<DTDetalleReserva> reservas = detalle.getReservas();

    std::cout << ">> Viaje <<\n";
    std::cout << "--- Codigo: " << detalle.getCodigo()
              << ", Fecha: " << detalle.getFecha()
              << ", Origen: " << detalle.getOrigen()
              << ", Destino: " << detalle.getDestino()
              << ", AsientosPublicados: " << detalle.getAsientosPublicados()
              << ", Precio por asiento: " << detalle.getPrecio() << "\n";

    std::cout << ">> Vehiculo <<\n";
    std::cout << "--- Matricula: " << vehiculo.getMatricula()
              << ", Capacidad: " << vehiculo.getCapacidad()
              << ", Marca: " << vehiculo.getMarca()
              << ", Modelo: " << vehiculo.getModelo()
              << ", Tipo: " << tipoVehiculoATexto(vehiculo.getTipo()) << "\n";

    std::cout << ">> Reservas <<\n";

    for (unsigned int i = 0; i < reservas.size(); i++) {
        std::cout << "--- AsientosReservados: " << reservas[i].getAsientosReservados()
                  << ", Fecha: " << reservas[i].getFecha()
                  << ", Pasajero: " << reservas[i].getPasajero() << "\n";
    }

    int confirmar;

    std::cout << "¿Confirmar eliminacion? (1: Si, 0: No): ";
    if (!leerEntero(confirmar)) {
        controlador->cancelarEliminarViaje();
        std::cout << "Eliminacion cancelada.\n";
        return;
    }

    if (confirmar == 1) {
        controlador->eliminarViaje();
        std::cout << "Viaje eliminado exitosamente.\n";
    } else {
        controlador->cancelarEliminarViaje();
        std::cout << "Eliminacion cancelada.\n";
    }
}

void Menu::administrarFechaActual() {
    int opFecha;

    std::cout << "1. Ver fecha actual\n";
    std::cout << "2. Modificar fecha actual\n";
    std::cout << "Seleccione: ";

    if (!leerEntero(opFecha)) {
        std::cout << "Opcion invalida.\n";
        return;
    }

    Fabrica* fabrica = Fabrica::getInstance();
    IControladorFechaActual* controladorFecha = fabrica->getIControladorFechaActual();

    if (opFecha == 1) {
        DTFecha fecha = controladorFecha->getFecha();
        std::cout << "Fecha actual: " << fecha << "\n";
    } else if (opFecha == 2) {
        int dia, mes, anio;

        std::cout << "Ingrese dia: ";
        if (!leerEntero(dia)) {
            std::cout << "Fecha invalida.\n";
            return;
        }

        std::cout << "Ingrese mes: ";
        if (!leerEntero(mes)) {
            std::cout << "Fecha invalida.\n";
            return;
        }

        std::cout << "Ingrese anio: ";
        if (!leerEntero(anio)) {
            std::cout << "Fecha invalida.\n";
            return;
        }

        controladorFecha->setFecha(DTFecha(dia, mes, anio));

        std::cout << "Fecha modificada exitosamente a " << controladorFecha->getFecha() << "\n";
    } else {
        std::cout << "Opcion invalida.\n";
    }
}

void Menu::cargarDatos() {
    CargaDatos::getInstance()->cargarDatos();
}

void Menu::mostrarMenu() {
    int opcion = -1;

    while (opcion != 8) {
        std::cout << "\n=== MENU PRINCIPAL ===\n";
        std::cout << "1. Alta de Usuario\n";
        std::cout << "2. Alta de Viaje\n";
        std::cout << "3. Generar Reserva\n";
        std::cout << "4. Calificar Usuario\n";
        std::cout << "5. Eliminar Viaje\n";
        std::cout << "6. Administrar Fecha Actual\n";
        std::cout << "7. Cargar Datos\n";
        std::cout << "8. Salir\n";
        std::cout << "Ingrese una opcion: ";

        if (!leerEntero(opcion)) {
            return;
        }

        switch (opcion) {
            case 1:
                altaUsuario();
                break;
            case 2:
                altaViaje();
                break;
            case 3:
                generarReserva();
                break;
            case 4:
                calificarUsuario();
                break;
            case 5:
                eliminarViaje();
                break;
            case 6:
                administrarFechaActual();
                break;
            case 7:
                cargarDatos();
                break;
            case 8:
                std::cout << "Saliendo del sistema...\n";
                break;
            default:
                std::cout << "Opcion invalida.\n";
        }
    }
}