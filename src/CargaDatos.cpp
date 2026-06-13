#include "../include/CargaDatos.h"
#include "../include/Fabrica.h"
#include "../include/IControladorUsuario.h"
#include "../include/IControladorReserva.h"
#include "../include/IControladorCalificacion.h"
#include "../include/IControladorFechaActual.h"
#include "../include/DTFecha.h"
#include <iostream>
#include <set>

CargaDatos* CargaDatos::instancia = NULL;

CargaDatos::CargaDatos() {
    datosCargados = false;
}

CargaDatos* CargaDatos::getInstance() {
    if (instancia == NULL) {
        instancia = new CargaDatos();
    }
    return instancia;
}

void CargaDatos::cargarDatos() {
    if (datosCargados) {
        std::cout << "Error: Los datos ya han sido cargados anteriormente.\n";
        return;
    }

    std::cout << "Cargando datos harcodeados del sistema...\n";

    Fabrica* fabrica = Fabrica::getInstance();
    IControladorUsuario* ctrlUsuario = fabrica->getIControladorUsuario();
    IControladorReserva* ctrlReserva = fabrica->getIControladorReserva();
    IControladorCalificacion* ctrlCal = fabrica->getIControladorCalificacion();
    IControladorFechaActual* ctrlFecha = fabrica->getIControladorFechaActual();

    // Establecer una fecha inicial (se puede modificar luego desde el menú)
    ctrlFecha->setFecha(DTFecha(1,1,2026));

    // Alta de pasajeros (nickname, nombre, contrasena, email, ci)
    // Nota: no crear `juan_p` ni `pedro_c` aquí para evitar duplicados cuando se
    // crean en el flujo de prueba en `entrada.txt`.
    ctrlUsuario->altaPasajero("mari_b", "Maria Noel Barreto", "maribarreto6", "mb@fing.edu.uy", "4.103.859-1");
    ctrlUsuario->altaPasajero("nacho_f", "Ignacio Figueroa", "ifigueroa26", "if@fing.edu.uy", "3.847.112-5");
    ctrlUsuario->altaPasajero("santi_90", "Santiago Acosta", "sacosta90", "sa@fing.edu.uy", "1.492.304-2");
    ctrlUsuario->altaPasajero("valen_uy", "Valentina Mendez", "vmendezQ2", "vm@fing.edu.uy", "2.956.403-0");
    ctrlUsuario->altaPasajero("joaco_r", "Joaquin Rivero", "jrivero99x", "joaquin_rivero@hotmail.com", "5.021.784-3");

    // Alta de conductores (nickname, nombre, contrasena, email, libretas)

    // matil92 - AutoAmateur
    std::set<TipoLibreta> lib2;
    lib2.insert(AutoAmateur);
    ctrlUsuario->altaConductor(
        "matil92",
        "Matias Lopez",
        "m4t14s92",
        "matias.lopez.92@gmail.com",
        lib2
    );

    // ana_silva - AutoProfesional
    std::set<TipoLibreta> lib3;
    lib3.insert(AutoProfesional);
    ctrlUsuario->altaConductor(
        "ana_silva",
        "Ana Silva",
        "asilva2026",
        "anasilva.m@outlook.com",
        lib3
    );

    // greg_m - MotoAmateur
    std::set<TipoLibreta> lib4;
    lib4.insert(MotoAmateur);
    ctrlUsuario->altaConductor(
        "greg_m",
        "Diego Rodriguez",
        "drodriguez88",
        "diegodriguez@fing.edu.uy",
        lib4
    );

    // lau_vaz - MotoProfesional
    std::set<TipoLibreta> lib5;
    lib5.insert(MotoProfesional);
    ctrlUsuario->altaConductor(
        "lau_vaz",
        "Laura Vazquez",
        "lvazquezQ7",
        "laura.vazquez@fing.edu.uy",
        lib5
    );

    // carlos_r - AutoProfesional + MotoAmateur
    std::set<TipoLibreta> lib6;
    lib6.insert(AutoProfesional);
    lib6.insert(MotoAmateur);
    ctrlUsuario->altaConductor(
        "carlos_r",
        "Carlos Rossi",
        "crossi99x",
        "carlos.rossi.uy@gmail.com",
        lib6
    );

    // Registrar vehículos para conductores (no registrar qtr1515 aquí)

    // matil92
    ctrlUsuario->registrarVehiculo(
        "matil92",
        "ABJ4586",
        4,
        "Chevrolet",
        "Onix",
        Auto
    );

    ctrlUsuario->registrarVehiculo(
        "matil92",
        "ACM4455",
        6,
        "Toyota",
        "Rush",
        Auto
    );


    // ana_silva
    ctrlUsuario->registrarVehiculo(
        "ana_silva",
        "BAS7895",
        4,
        "Fiat",
        "Argo",
        Auto
    );

    ctrlUsuario->registrarVehiculo(
        "ana_silva",
        "BCS4105",
        9,
        "Hyundai",
        "H1",
        Auto
    );


    // greg_m
    ctrlUsuario->registrarVehiculo(
        "greg_m",
        "LDA4875",
        1,
        "Honda",
        "CB Twist",
        Moto
    );


    // lau_vaz
    ctrlUsuario->registrarVehiculo(
        "lau_vaz",
        "PDB1205",
        1,
        "Yumbo",
        "Max 110",
        Moto
    );


    // carlos_r
    ctrlUsuario->registrarVehiculo(
        "carlos_r",
        "SBJ4874",
        4,
        "Volkswagen",
        "Gol",
        Auto
    );

    ctrlUsuario->registrarVehiculo(
        "carlos_r",
        "SCF2469",
        1,
        "Yamaha",
        "FZ S",
        Moto
    );

    // Crear viajes (matricula, fecha, origen, destino, asientos, precio)

    // Código 1
    ctrlReserva->altaViaje(
        "ABJ4586",
        DTFecha(21,10,2026),
        "montevideo",
        "mercedes",
        4,
        200.0f
    );

    // Código 2
    ctrlReserva->altaViaje(
        "ACM4455",
        DTFecha(20,10,2026),
        "young",
        "montevideo",
        5,
        250.0f
    );

    // Código 3
    ctrlReserva->altaViaje(
        "BAS7895",
        DTFecha(20,10,2026),
        "young",
        "montevideo",
        4,
        200.0f
    );

    // Código 4
    ctrlReserva->altaViaje(
        "BCS4105",
        DTFecha(21,10,2026),
        "montevideo",
        "mercedes",
        9,
        200.0f
    );

    // Código 5
    ctrlReserva->altaViaje(
        "LDA4875",
        DTFecha(21,10,2026),
        "montevideo",
        "mercedes",
        1,
        300.0f
    );

    // Código 6
    ctrlReserva->altaViaje(
        "PDB1205",
        DTFecha(21,10,2026),
        "montevideo",
        "mercedes",
        1,
        350.0f
    );

    // Código 7
    ctrlReserva->altaViaje(
        "SBJ4874",
        DTFecha(21,10,2026),
        "montevideo",
        "mercedes",
        4,
        260.0f
    );

    // Código 8
    ctrlReserva->altaViaje(
        "SCF2469",
        DTFecha(20,10,2026),
        "montevideo",
        "cerro chato",
        1,
        150.0f
    );

    // Código 9
    ctrlReserva->altaViaje(
        "ABJ4586",
        DTFecha(15,3,2026),
        "montevideo",
        "colonia",
        4,
        140.0f
    );

    // Código 10
    ctrlReserva->altaViaje(
        "BCS4105",
        DTFecha(15,3,2026),
        "montevideo",
        "colonia",
        9,
        180.0f
    );

    // Código 11
    ctrlReserva->altaViaje(
        "SBJ4874",
        DTFecha(15,3,2026),
        "montevideo",
        "colonia",
        1,
        100.0f
    );

    // Código 12
    ctrlReserva->altaViaje(
        "SBJ4874",
        DTFecha(14,3,2026),
        "montevideo",
        "colonia",
        4,
        600.0f
    );

    // Código 13
    ctrlReserva->altaViaje(
        "LDA4875",
        DTFecha(20,10,2026),
        "young",
        "montevideo",
        1,
        250.0f
    );

    // Generar reservas (nickname, codigo, asientos)
    // Note: códigos de viaje se asignan internamente; asumiendo orden de inserción, utilizamos aproximaciones.
    // Generar reservas (nickname, codigo, asientos)

    // Viaje 9 - ABJ4586 - 14/3/2026
    ctrlReserva->generarReserva(
        "santi_90",
        9,
        2
    );

    ctrlReserva->generarReserva(
        "mari_b",
        9,
        1
    );

    // Viaje 10 - BCS4105 - 14/3/2026
    ctrlReserva->generarReserva(
        "nacho_f",
        10,
        5
    );

    ctrlReserva->generarReserva(
        "valen_uy",
        10,
        3
    );

    ctrlReserva->generarReserva(
        "joaco_r",
        10,
        1
    );

    // Viaje 12 - SBJ4874 - 14/3/2026
    ctrlReserva->generarReserva(
        "mari_b",
        12,
        1
    );

    ctrlReserva->generarReserva(
        "nacho_f",
        12,
        1
    );

    // Viaje 1 - ABJ4586 - 21/10/2026
    ctrlReserva->generarReserva(
        "mari_b",
        1,
        2
    );

    // Viaje 9 - ABJ4586 - 15/3/2026
    ctrlReserva->generarReserva(
        "nacho_f",
        9,
        1
    );

    // Realizar calificaciones (nickname, codigo, nicknameCalificado, calificacion)

    // Viaje 9
    ctrlCal->recordarUsuarioCalificador("santi_90");
    ctrlCal->recordarCodigoViaje(9);
    ctrlCal->listarUsuariosViaje(9);
    ctrlCal->calificarUsuario("matil92", 4);

    ctrlCal->recordarUsuarioCalificador("mari_b");
    ctrlCal->recordarCodigoViaje(9);
    ctrlCal->listarUsuariosViaje(9);
    ctrlCal->calificarUsuario("matil92", 4);

    ctrlCal->recordarUsuarioCalificador("matil92");
    ctrlCal->recordarCodigoViaje(9);
    ctrlCal->listarUsuariosViaje(9);
    ctrlCal->calificarUsuario("mari_b", 3);


    // Viaje 10
    ctrlCal->recordarUsuarioCalificador("ana_silva");
    ctrlCal->recordarCodigoViaje(10);
    ctrlCal->listarUsuariosViaje(10);
    ctrlCal->calificarUsuario("valen_uy", 5);

    ctrlCal->recordarUsuarioCalificador("ana_silva");
    ctrlCal->recordarCodigoViaje(10);
    ctrlCal->listarUsuariosViaje(10);
    ctrlCal->calificarUsuario("joaco_r", 5);


    // Viaje 12
    ctrlCal->recordarUsuarioCalificador("mari_b");
    ctrlCal->recordarCodigoViaje(12);
    ctrlCal->listarUsuariosViaje(12);
    ctrlCal->calificarUsuario("carlos_r", 5);

    ctrlCal->recordarUsuarioCalificador("carlos_r");
    ctrlCal->recordarCodigoViaje(12);
    ctrlCal->listarUsuariosViaje(12);
    ctrlCal->calificarUsuario("nacho_f", 5);

    datosCargados = true;
    std::cout << "Datos cargados exitosamente.\n";
}
