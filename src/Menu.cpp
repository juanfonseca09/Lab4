#include "../include/Menu.h"
#include "../include/Fabrica.h"
#include "../include/IControladorFechaActual.h"
#include "../include/CargaDatos.h"
#include "../include/DTFecha.h"
#include "../include/DTVehiculosConductor.h"
#include <iostream>
#include <limits>
#include <string>

void Menu::altaUsuario() {
    int tipoUsuario;
    std::cout << "1. Alta Pasajero\n";
    std::cout << "2. Alta Conductor\n";
    std::cout << "Seleccione: ";
    std::cin >> tipoUsuario;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tipoUsuario != 1 && tipoUsuario != 2) {
        std::cout << "Opcion invalida.\n";
        return;
    }

    std::string nickname, nombre, contrasena, email;
    std::cout << "Ingrese nickname: "; std::getline(std::cin, nickname);
    std::cout << "Ingrese nombre: "; std::getline(std::cin, nombre);
    std::cout << "Ingrese contrasena: "; std::getline(std::cin, contrasena);
    std::cout << "Ingrese email: "; std::getline(std::cin, email);


    bool usuarioOk = false;

    Fabrica* fabrica = Fabrica::getInstance();
    IControladorUsuario* ctrlUsuario = fabrica->getIControladorUsuario();

    if (tipoUsuario == 1) {
        std::string ci;
        std::cout << "Ingrese CI: "; std::getline(std::cin, ci);
        usuarioOk = ctrlUsuario->altaPasajero(nickname, nombre, contrasena, email, ci);
    } else if (tipoUsuario == 2) {
        std::set<TipoLibreta> libretas;
        std::cout << "\n=== Registrar Libreta ===\n";
        int opcionLibreta = -1;
        int agregarOtra = 0;
        do {
            std::cout << "0. Moto (Profesional)\n";
            std::cout << "1. Moto (Amateur)\n";
            std::cout << "2. Auto (Profesional)\n";
            std::cout << "3. Auto (Amateur)\n";
            std::cout << "Seleccione el tipo de libreta: "; std::cin >> opcionLibreta;
            if (opcionLibreta == 0) {
                libretas.insert(MotoProfesional);
                std::cout << "Libreta agregada.\n";
            } else if (opcionLibreta == 1) {
                libretas.insert(MotoAmateur);
                std::cout << "Libreta agregada.\n";
            } else if (opcionLibreta == 2) {
                libretas.insert(AutoProfesional);
                std::cout << "Libreta agregada.\n";
            } else if (opcionLibreta == 3) {
                libretas.insert(AutoAmateur);
                std::cout << "Libreta agregada.\n";
            } else {
                std::cout << "Opcion invalida.\n";
            }
            std::cout << "¿Desea agregar otra libreta? (1: Si, 0: No): "; std::cin >> agregarOtra;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (agregarOtra == 1);

        usuarioOk = ctrlUsuario->altaConductor(nickname, nombre, contrasena, email, libretas);
        int agregarVehiculo = 1;
        while (usuarioOk == true && agregarVehiculo == 1) {
            std::string matricula, marca, modelo;
            int capacidad, tipo;
            std::cout << "\n=== Registrar Vehiculo ===\n";
            std::cout << "Ingrese matricula: "; std::getline(std::cin, matricula);
            std::cout << "Ingrese capacidad: "; std::cin >> capacidad;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ingrese marca: "; std::getline(std::cin, marca);
            std::cout << "Ingrese modelo: "; std::getline(std::cin, modelo);
            std::cout << "Ingrese tipo (0: Auto, 1: Moto): "; std::cin >> tipo;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            int resultadoRegistrarVehiculo = -3;
            resultadoRegistrarVehiculo = ctrlUsuario->registrarVehiculo (nickname, matricula, capacidad, marca, modelo, (TipoVehiculo)tipo);
            if (resultadoRegistrarVehiculo == -1) {
                std::cout << "Ya existe un vehiculo con esa matricula.\n";
            } else if (resultadoRegistrarVehiculo == -2) {
                std::cout << "El conductor no tiene la libreta necesaria para registrar ese vehiculo.\n";
            } else if (resultadoRegistrarVehiculo == 0) {
                std::cout << "Vehiculo registrado exitosamente.\n";
            }
            std::cout << "¿Desea agregar otro vehiculo? (1: Si, 0: No): ";
            std::cin >> agregarVehiculo;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void Menu::altaViaje() {
    std::string nickname, matricula, origen, destino;
    int dia, mes, anio, asientos;
    float precio;

    Fabrica* fabrica = Fabrica::getInstance();
    IControladorReserva* ctrlReserva = fabrica->getIControladorReserva();

    std::cout << "Ingrese nickname del conductor: "; std::getline(std::cin, nickname);
    DTVehiculosConductor dtVehiculos = ctrlReserva->listarVehiculosConductor(nickname);
    std::vector<DTDetalleVehiculo> vehiculos = dtVehiculos.getVehiculos();
    if (vehiculos.empty()) {
        std::cout << "El conductor no tiene vehiculos.\n";
    } else {
        for (size_t i = 0; i < vehiculos.size(); ++i) {
            DTDetalleVehiculo v = vehiculos[i];
            std::string tipoStr;
            if (v.getTipo() == Auto)
                tipoStr = "Auto";
            else
                tipoStr = "Moto";
            std::cout << "> Matricula: " << v.getMatricula()
                      << ", Capacidad: " << v.getCapacidad()
                      << ", Marca: " << v.getMarca()
                      << ", Modelo: " << v.getModelo()
                      << ", Tipo: " << tipoStr << "\n";
        }
    }
    

    std::cout << "Ingrese matricula del vehiculo a utilizar: "; std::getline(std::cin, matricula);
    bool matriculaValida = false;

    //TODO: Validar matricula en listado
    for (size_t i = 0; i < vehiculos.size(); i++) {
        if (vehiculos[i].getMatricula() == matricula) {
            matriculaValida = true;
            break;
        }
    }

    if (!matriculaValida) {
        std::cout << "Matricula invalida.\n";
        return;
    }

    std::cout << "Ingrese fecha del viaje (dia mes anio): "; std::cin >> dia >> mes >> anio;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ingrese origen: "; std::getline(std::cin, origen);
    std::cout << "Ingrese destino: "; std::getline(std::cin, destino);
    std::cout << "Ingrese cantidad de asientos: "; std::cin >> asientos;
    std::cout << "Ingrese precio por asiento: "; std::cin >> precio;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool viajeOk = false;
    viajeOk = ctrlReserva->altaViaje(matricula, DTFecha(dia, mes, anio), origen, destino, asientos, precio);
    if (viajeOk) {
        std::cout << "Viaje registrado exitosamente.\n";
    } else {
        std::cout << "Error al registrar el viaje.\n";
    }
}

void Menu::generarReserva() {

    Fabrica* fabrica = Fabrica::getInstance();
    IControladorReserva* ctrlReserva = fabrica->getIControladorReserva();

    std::set<std::string> nicknames = ctrlReserva->listarPasajeros();
    //TODO: Recorrer la colección y mostrar "> xx"
    if (nicknames.empty()) {
        std::cout << "No hay usuarios registrados.\n";
    } else {
        for (std::set<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); ++it) {
            std::cout << "> " << *it << "\n";
        }
    }

    std::string nickname;
    std::cout << "Ingrese nickname del pasajero: "; std::getline(std::cin, nickname);

    bool nicknameValido = false;
    //TODO: Validar nickname en listado
    for (std::set<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); ++it) {
        if (*it == nickname){
            nicknameValido = true;
            break;
        }
    }

    if (!nicknameValido) {
        std::cout << "Nickname invalido.\n";
        return;
    }

    int dia, mes, anio, asientos;
    std::string origen, destino;
    std::cout << "Ingrese fecha del viaje a consultar (dia mes anio): "; std::cin >> dia >> mes >> anio;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ingrese origen: "; std::getline(std::cin, origen);
    std::cout << "Ingrese destino: "; std::getline(std::cin, destino);
    std::cout << "Ingrese cantidad de asientos a reservar: "; std::cin >> asientos;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<DTConsultaViaje> viajes = ctrlReserva->consultarViajes(DTFecha(dia, mes, anio), origen, destino, asientos);
    //TODO: Recorrer la coleccion y mostrar: "> Codigo: xx, Marca: yy, Modelo: zzz, Conductor: aaa, CalificacionPromedio: qqq, PrecioTotal: eee"

    for (size_t i = 0; i < viajes.size(); ++i) {
        DTConsultaViaje cv = viajes[i];
        std::cout << "> Codigo: " << cv.getCodigo()
                  << ", Marca: " << cv.getMarca()
                  << ", Modelo: " << cv.getModelo()
                  << ", Conductor: " << cv.getConductor()
                  << ", CalificacionPromedio: " << cv.getCalificacionProm()
                  << ", PrecioTotal: " << cv.getPrecioTotal() << "\n";
    }

    int codigo;
    std::cout << "Ingrese codigo del viaje a reservar: "; std::cin >> codigo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool codigoValido = false;
    //TODO: Validar codigo en listado
    for (size_t i = 0; i < viajes.size(); ++i) {
        if (viajes[i].getCodigo() == codigo) {
            codigoValido = true;
            break;
        }

    }

    if (!codigoValido) {
        std::cout << "Codigo invalido.\n";
        return;
    }

    bool reservaOk = false;
    reservaOk = ctrlReserva->generarReserva(nickname, codigo, asientos);
    if (reservaOk) {
        std::cout << "Reserva realizada exitosamente.\n";
    } else {
        std::cout << "Error al realizar la reserva.\n";
    }
}

void Menu::calificarUsuario() {

    Fabrica* fabrica = Fabrica::getInstance();
    IControladorCalificacion* ctrlCalificacion = fabrica->getIControladorCalificacion();
    std::vector<DTUsuario> usuarios = ctrlCalificacion->listarUsuarios();
    //TODO: Recorrer la coleccion y mostrar "> Nickname: xx, Nombre: yyy"
    for (size_t i = 0; i < usuarios.size(); i++) {
        std::cout << "> Nickname: " << usuarios[i].getNickname()
                    << ", Nombre: " << usuarios[i].getNombre() << "\n";
        
    }

    std::string nickname;
    std::cout << "Ingrese su nickname: "; std::getline(std::cin, nickname);
    bool nicknameValido = false;
    //TODO: Validar nickname en listado

    for (size_t i = 0; i < usuarios.size(); i++) {
        if (usuarios[i].getNickname() == nickname) {
            nicknameValido = true;
            break;
        }
        
    }
    if (!nicknameValido) {
        std::cout << "Nickname invalido.\n";
        return;
    }
    std::vector<DTListarViaje> viajes = ctrlCalificacion->listarViajes(nickname);
    //TODO: Recorrer la coleccion y mostrar "> Codigo: xx, Fecha: dd/mm/aaaa, Origen: zzz, Destino: www, Conductor: aaa"
    for (size_t i = 0; i < viajes.size(); i++){
        std::cout << "> Codigo:" << viajes[i].getCodigo()
                  << ", Fecha:" << viajes[i].getFecha()
                  << ", Origen:" << viajes[i].getOrigen()
                  << ", Destino:" << viajes[i].getDestino()
                  << ", Conductor:" << viajes[i].getConductor() << '\n';
    }

    int codigo;
    std::cout << "Ingrese codigo del viaje: "; std::cin >> codigo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool codigoValido = false;
    //TODO: Validar codigo en listado
    for (size_t i = 0; i < viajes.size(); i++){
        if (viajes[i].getCodigo() == codigo){
            codigoValido = true;
            break;
        }   
    }

    if (!codigoValido) {
        std::cout << "Codigo invalido.\n";
        return;
    }
    std::vector<DTUsuarioViaje> usuariosviaje = ctrlCalificacion->listarUsuariosViaje(codigo);
    //TODO: Recorrer la coleccion y mostrar "> Nickname: xx, Tipo: yyy"
    for (size_t i = 0; i < usuariosviaje.size(); i++) {
            std::cout << "> Nickname: " << usuariosviaje[i].getNickname()
                      << ", Tipo: ";
            if (usuariosviaje[i].getTipo() == UsuarioPasajero)
                std::cout << "Pasajero";
            else
                std::cout << "Conductor";
            std::cout << "\n";
    }
    std::string nicknameCalificado;
    int calificacion;
    std::cout << "Ingrese nickname del usuario a calificar: "; std::getline(std::cin, nicknameCalificado);
    std::cout << "Ingrese calificacion (1-5): "; std::cin >> calificacion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool nicknameCalificadoValido = false;
    //TODO: Validar nickname en listado
    for (size_t i = 0; i < usuariosviaje.size(); i++) {
        if (usuariosviaje[i].getNickname() == nicknameCalificado) {
            nicknameCalificadoValido = true;
            break;
        }
        
    }
    if (!nicknameCalificadoValido) {
        std::cout << "Nickname invalido.\n";
        return;
    }

    bool calificacionOk = false;
    calificacionOk = ctrlCalificacion->calificarUsuario(nicknameCalificado, calificacion);
    if (calificacionOk) {
        std::cout << "Calificacion exitosa.\n";
    } else {
        std::cout << "Error al calificar.\n";
    }
}

void Menu::eliminarViaje() {
    //TODO: Coleccion de DTListarViaje = controlador->listarViajes()
    //TODO: Recorrer la coleccion y mostrar "> Codigo: xx, Fecha: dd/mm/aaaa, Origen: zzz, Destino: www, Conductor: aaa"
    int codigo;
    std::cout << "Ingrese codigo del viaje a eliminar: "; std::cin >> codigo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool codigoValido = false;
    //TODO: Validar codigo en listado
    if (!codigoValido) {
        std::cout << "Codigo invalido.\n";
        return;
    }

    //TODO: DTDetalleViaje = controlador->detalleViaje(codigo)
    //TODO: Mostrar detalle del viaje siguiendo el formato
    //>> Viaje <<
    //--- Matrícula: aa, Fecha: dd/mm/aaaa, Origen: zzz, Destino: www, Capacidad: bbb, Precio por asiento: qqq
    //>> Vehiculo <<
    //--- Matricula: mm, Capacidad: aa, Marca: bbb, Modelo: ccc, Tipo: ddd
    //>> Reservas <<
    //--- AsientosReservados: xx, Fecha: dd/mm/aaaa, Pasajero: aaa
    int confirmar;
    std::cout << "¿Confirmar eliminacion? (1: Si, 0: No): "; std::cin >> confirmar;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (confirmar == 1) {
        //TODO: controlador->eliminarViaje()
        std::cout << "Viaje eliminado exitosamente.\n";
    } else {
        //TODO: controlador->cancelarEliminarViaje()
        std::cout << "Eliminacion cancelada.\n";
    }
}

void Menu::administrarFechaActual() {
    int opFecha;
    std::cout << "1. Ver fecha actual\n";
    std::cout << "2. Modificar fecha actual\n";
    std::cout << "Seleccione: ";
    std::cin >> opFecha;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Fabrica* fabrica = Fabrica::getInstance();
    IControladorFechaActual* controladorFecha = fabrica->getIControladorFechaActual();

    if (opFecha == 1) {
        DTFecha fecha = controladorFecha->getFecha();
        std::cout << "Fecha actual: " << fecha << "\n";
    } else if (opFecha == 2) {
        int dia, mes, anio;
        std::cout << "Ingrese dia: "; std::cin >> dia;
        std::cout << "Ingrese mes: "; std::cin >> mes;
        std::cout << "Ingrese anio: "; std::cin >> anio;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
