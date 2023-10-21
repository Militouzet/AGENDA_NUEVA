#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include "agenda.h"
#include "contacto.h"
int main(int argc, char** argv) {

    return Catch::Session().run(argc, argv);

    sAgenda miAgenda;
    miAgenda.CantMaxima = 100;
    miAgenda.CantContactos = 0;
    miAgenda.misContactos = new sContacto[miAgenda.CantMaxima];

    sContacto contacto1 = {"Juan", "Perez", "Calle 123", "juan@example.com", "123-456-7890", {5, 3, 1985}, eGrupo::AMIGO};
    sContacto contacto2 = {"Maria", "Gonzalez", "Avenida 456", "maria@example.com", "987-654-3210", {15, 11, 1992}, eGrupo::FAMILIA};

    eAgrContacto resultadoAgregado1 = agregarContacto(&miAgenda, contacto1);
    eAgrContacto resultadoAgregado2 = agregarContacto(&miAgenda, contacto2);

    if (resultadoAgregado1 == eAgrContacto::ExitoAgregar && resultadoAgregado2 == eAgrContacto::ExitoAgregar) {
        std::cout << "Contactos agregados con éxito." << std::endl;
    } else {
        std::cout << "Error al agregar contactos." << std::endl;
    }

    std::fstream archivoSalida("agenda.dat", std::ios::out | std::ios::binary);



    delete[] miAgenda.misContactos;

    return 0;


}
