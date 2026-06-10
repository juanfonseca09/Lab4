#include "../include/Menu.h"
#include "../include/Fabrica.h"
#include "../include/IControladorFechaActual.h"
#include "../include/CargaDatos.h"
#include "../include/DTFecha.h"
#include "../include/TipoLibreta.h"
#include "../include/ManejadorUsuario.h"
#include "../include/Vehiculo.h"
#include "../include/Conductor.h"
#include <iostream>
#include <limits>
#include <string>
#include <map>
#include <set>

Menu::Menu(IControladorUsuario* ctrlUsuario, IControladorFechaActual* ctrlFecha, IControladorReserva* ctrlReserva, IControladorCalificacion* ctrlCalificacion) {
    controladorUsuario = ctrlUsuario;
    controladorFecha = ctrlFecha;
    controladorReserva = ctrlReserva;
    controladorCalificacion = ctrlCalificacion;
}

Menu::~Menu() {
}

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

    // usar los controladores centralizados inicializados en el constructor

    if (tipoUsuario == 1) {
        std::string ci;
        std::cout << "Ingrese CI: "; std::getline(std::cin, ci);
        usuarioOk = controladorUsuario->altaPasajero(nickname, nombre, contrasena, email, ci);
    } else if (tipoUsuario == 2) {
        std::set<TipoLibreta> libretas;
        std::cout << "\n=== Registrar Libretas ===\n";
        std::cout << "Indique cuales libretas posee (1: Si, 0: No)\n";
        
        int tieneMotoAm, tieneMotoProf, tieneAutoAm, tieneAutoProf;
        
        std::cout << "¿Posee libreta Moto Amateur? (1: Si, 0: No): "; std::cin >> tieneMotoAm;
        if (tieneMotoAm == 1) libretas.insert(MotoAmateur);
        
        std::cout << "¿Posee libreta Moto Profesional? (1: Si, 0: No): "; std::cin >> tieneMotoProf;
        if (tieneMotoProf == 1) libretas.insert(MotoProfesional);
        
        std::cout << "¿Posee libreta Auto Amateur? (1: Si, 0: No): "; std::cin >> tieneAutoAm;
        if (tieneAutoAm == 1) libretas.insert(AutoAmateur);
        
        std::cout << "¿Posee libreta Auto Profesional? (1: Si, 0: No): "; std::cin >> tieneAutoProf;
        if (tieneAutoProf == 1) libretas.insert(AutoProfesional);
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        usuarioOk = controladorUsuario->altaConductor(nickname, nombre, contrasena, email, libretas);
        
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
            resultadoRegistrarVehiculo = controladorUsuario->registrarVehiculo(nickname, matricula, capacidad, marca, modelo, (TipoVehiculo)tipo);
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

    if (usuarioOk) {
        if (tipoUsuario == 1) {
            std::cout << "\nPasajero registrado exitosamente.\n";
        } else {
            std::cout << "\nConductor registrado exitosamente.\n";
        }
    } else {
        std::cout << "\nError al registrar el usuario.\n";
    }
}

void Menu::altaViaje() {
    std::string nickname, matricula, origen, destino;
    int dia, mes, anio, asientos;
    float precio;

    std::cout << "Ingrese nickname del conductor: "; std::getline(std::cin, nickname);

    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    std::map<std::string, Vehiculo*> todos = mu->getVehiculos();
    std::vector<std::string> disponibles;
    std::map<std::string, Vehiculo*>::iterator it;
    std::cout << "\nVehiculos del conductor " << nickname << ":\n";
    for (it = todos.begin(); it != todos.end(); ++it) {
        Vehiculo* v = it->second;
        if (v == NULL) continue;
        Conductor* c = v->getConductor();
        if (c == NULL) continue;
        if (c->getNickname() == nickname) {
            disponibles.push_back(v->getMatricula());
            std::cout << "> Matricula: " << v->getMatricula() << ", Capacidad: " << v->getCapacidad() << ", Marca: " << v->getMarca() << ", Modelo: " << v->getModelo() << ", Tipo: " << (v->getTipo() == Auto ? "Auto" : "Moto") << "\n";
        }
    }
    if (disponibles.empty()) {
        std::cout << "El conductor no tiene vehiculos registrados.\n";
        return;
    }

    std::cout << "Ingrese matricula del vehiculo a utilizar: "; std::getline(std::cin, matricula);
    bool matriculaValida = false;
    for (size_t i = 0; i < disponibles.size(); ++i) {
        if (disponibles[i] == matricula) {
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

    bool viajeOk = controladorReserva->altaViaje(matricula, DTFecha(dia, mes, anio), origen, destino, asientos, precio);
    if (viajeOk) {
        std::cout << "Viaje registrado exitosamente.\n";
    } else {
        std::cout << "Error al registrar el viaje.\n";
    }
}

void Menu::generarReserva() {
    //TODO: Colecion de String = controlador->listarPasajeros()
    //TODO: Recorrer la colección y mostrar "> xx"
    std::string nickname;
    std::cout << "Ingrese nickname del pasajero: "; std::getline(std::cin, nickname);

    bool nicknameValido = false;
    //TODO: Validar nickname en listado
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

    //TODO: Coleccion de DTConsultaViaje = controlador->consultarViajes(DTFecha(dia, mes, anio), origen, destino, asientos)
    //TODO: Recorrer la coleccion y mostrar: "> Codigo: xx, Marca: yy, Modelo: zzz, Conductor: aaa, CalificacionPromedio: qqq, PrecioTotal: eee"

    bool hayViajes = false;//TODO: Validar coleccion vacía
    if (!hayViajes) {
        std::cout << "No hay viajes disponibles.\n";
        return;
    }

    int codigo;
    std::cout << "Ingrese codigo del viaje a reservar: "; std::cin >> codigo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool codigoValido = false;
    //TODO: Validar codigo en listado
    if (!codigoValido) {
        std::cout << "Codigo invalido.\n";
        return;
    }

    bool reservaOk = false;
    //TODO: reservaOk = controlador->generarReserva(nickname, codigo, asientos)
    if (reservaOk) {
        std::cout << "Reserva realizada exitosamente.\n";
    } else {
        std::cout << "Error al realizar la reserva.\n";
    }
}

void Menu::calificarUsuario() {
    //TODO: Coleccion de DTUsuario = controlador->listarUsuarios()
    //TODO: Recorrer la coleccion y mostrar "> Nickname: xx, Nombre: yyy"
    std::string nickname;
    std::cout << "Ingrese su nickname: "; std::getline(std::cin, nickname);
    bool nicknameValido = false;
    //TODO: Validar nickname en listado
    if (!nicknameValido) {
        std::cout << "Nickname invalido.\n";
        return;
    }

    //TODO: Coleccion de DTListarViaje = controlador->listarViajes(nickname)
    //TODO: Recorrer la coleccion y mostrar "> Codigo: xx, Fecha: dd/mm/aaaa, Origen: zzz, Destino: www, Conductor: aaa"
    int codigo;
    std::cout << "Ingrese codigo del viaje: "; std::cin >> codigo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool codigoValido = false;
    //TODO: Validar codigo en listado
    if (!codigoValido) {
        std::cout << "Codigo invalido.\n";
        return;
    }

    //TODO: Coleccion de DTUsuarioViaje = Controlador->listarUsuariosViaje(codigo)
    //TODO: Recorrer la coleccion y mostrar "> Nickname: xx, Tipo: yyy"
    std::string nicknameCalificado;
    int calificacion;
    std::cout << "Ingrese nickname del usuario a calificar: "; std::getline(std::cin, nicknameCalificado);
    std::cout << "Ingrese calificacion (1-5): "; std::cin >> calificacion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool nicknameCalificadoValido = false;
    //TODO: Validar nickname en listado
    if (!nicknameCalificadoValido) {
        std::cout << "Nickname invalido.\n";
        return;
    }

    bool calificacionOk = false;
    //TODO: calificacionOk = Controlador->calificarUsuario(nicknameCalificado, calificacion)
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
