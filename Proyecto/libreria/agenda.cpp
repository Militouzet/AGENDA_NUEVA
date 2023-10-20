 #include "agenda.h"

bool hayEspacio(sAgenda* miAgenda) {
    return (miAgenda->CantMaxima - miAgenda->CantContactos > 0);
}

/**
 * @brief Función agregar contacto a la agenda
 * @return Error: ErrAgrEspacio, sino ExitoAgregar
 */
eAgrContacto agregarContacto(sAgenda* miAgenda, sContacto miContacto) {
    if (!hayEspacio(miAgenda))
        return eAgrContacto::ErrAgrEspacio;

    miAgenda->CantContactos++;
    miAgenda->misContactos[miAgenda->CantContactos - 1] = miContacto;
    // miAgenda->*(misContactos + i )
    return eAgrContacto::ExitoAgregar;
}

/*eAgrContacto agregarContacto(sAgenda* miAgenda, sContacto miContacto) {
    if (!hayEspacio(miAgenda)) {

    }

    miAgenda->CantContactos++;
    miAgenda->misContactos[miAgenda->CantContactos - 1] = miContacto;
    // miAgenda->*(misContactos + i )
    return eAgrContacto::ExitoAgregar;
}

/**
 * @brief Función actualiza el contacto con los datos recibidos dentro de sContacto
 * @return Error: ErrUpdContacto, ErrUpdIndex, sino ExitoModificar
 */
eUpdContacto actualizarContacto(sAgenda* miAgenda, sContacto miContacto) {
    sContacto* aux = miAgenda->misContactos,
             * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;
    while(true) {
        if ((aux->Nombre == miContacto.Nombre && aux->Apellido == miContacto.Apellido) ||
            (aux->Correo == miContacto.Correo)) {
            *aux = miContacto;
            return eUpdContacto::ExitoModificar;
        }
        if (aux == ultimo)
            break;
        aux++; // aux = aux + 1 o aux+= 1
    }
    return eUpdContacto::ErrUpdContacto;
}
/**
 * @brief Función actualiza el contacto en el indice indicado con los datos recibidos dentro de sContacto
 * @return Error: ErrUpdContacto, ErrUpdIndex, sino ExitoModificar
 */
eUpdContacto actualizarContacto(sAgenda* miAgenda, u_int indexContacto, sContacto miContacto) {
    if (indexContacto >= miAgenda->CantMaxima)
        return eUpdContacto::ErrUpdIndex;

    sContacto* aux = miAgenda->misContactos + indexContacto;

    if ((aux->Nombre == miContacto.Nombre && aux->Apellido == miContacto.Apellido) ||
        (aux->Correo == miContacto.Correo)) {
        *aux = miContacto;
        return eUpdContacto::ExitoModificar;
    }

    return eUpdContacto::ErrUpdContacto;
}

/**
 * @brief Función remueve al contacto indicado por nombre y apellido
 * @return Error: ErrSrchValor, ErrSrchIndex, sino ExitoBuscar
 */
eRmContacto removerContacto(sAgenda* miAgenda, str Nombre, str Apellido) {
    sContacto* aux = miAgenda->misContactos,
        * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;
    while(true) {
        if ((aux->Nombre == Nombre && aux->Apellido == Apellido)) {
            *aux = ContactoNulo;
            return eRmContacto::ExitoRemover;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eRmContacto::ErrRmNomApe;
}
/**
 * @brief Función remueve al contacto indicado por sContacto
 * @return Error: ErrSrchValor, ErrSrchIndex, sino ExitoBuscar
 */
eRmContacto removerContacto(sAgenda* miAgenda, sContacto miContacto) {
    sContacto* aux = miAgenda->misContactos,
        * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;
    while(true) {
        if ((aux->Nombre == miContacto.Nombre && aux->Apellido == miContacto.Apellido) ||
            (aux->Correo == miContacto.Correo)) {
            *aux = ContactoNulo;
            return eRmContacto::ExitoRemover;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eRmContacto::ErrRmContacto;
}
/**
 * @brief Función remueve al contacto indicado por indice
 * @return Error: ErrSrchValor, ErrSrchIndex, sino ExitoBuscar
 */
eRmContacto removerContacto(sAgenda* miAgenda, u_int indexContacto) {
    if (indexContacto >= miAgenda->CantMaxima)
        return eRmContacto::ErrRmIndex;

    sContacto* aux = miAgenda->misContactos + indexContacto;
    *aux = ContactoNulo;
    return eRmContacto::ExitoRemover;
}

/**
 * @brief Función de buscar contacto por Nombre Y Apellido o email
 * @return Error: Nullptr, sino Contacto
 */
sContacto buscarContacto(sAgenda* miAgenda, str valorBusqueda) {
    sContacto* aux = miAgenda->misContactos,
        * ultimo = (miAgenda->misContactos) + miAgenda->CantContactos - 1;
    while(true) {
        if (((aux->Nombre + " " + aux->Apellido) == valorBusqueda) ||
            (aux->Correo == valorBusqueda)) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return ContactoNulo;
}
/**
 * @brief Función de buscar contacto por indice
 * @return Error: Nullptr, sino Contacto
 */
sContacto buscarContacto(sAgenda* miAgenda, u_int indexContacto) {
    return indexContacto >= miAgenda->CantContactos - 1 ? ContactoNulo : miAgenda->misContactos[indexContacto];
}

void OrdenarPorApellido(sAgenda* miAgenda) {
    sContacto* ultimoContacto = miAgenda->misContactos + miAgenda->CantContactos - 1;

    for(u_int i = 0; i < miAgenda->CantContactos - 1; i++) {
        sContacto& Actual = miAgenda->misContactos[i]; // *(miAgenda->misContactos + i)
        char Ape1 = (Actual.Apellido[0] >= 'A' && Actual.Apellido[0] <= 'Z') ?
                        Actual.Apellido[0] + ('a' - 'A') : Actual.Apellido[0];
        for(sContacto* miContacto = miAgenda->misContactos; miContacto == ultimoContacto; miContacto++) {
            char Ape2 = (miContacto->Apellido[0] >= 'A' && miContacto->Apellido[0] <= 'Z') ?
                            miContacto->Apellido[0] + ('a' - 'A') : miContacto->Apellido[0];

            if(Ape1 > Ape2) {
                sContacto aux = Actual;
                Actual = *miContacto;
                *miContacto = aux;
            }
        }
    }
}
/**
 * @brief Función Listar por grupo
 */
void ListarPorGrupo(sAgenda miAgenda, sAgrupar*& Agrupados) {
    Agrupados = new sAgrupar[5];
    for(u_int i = 0; i < eGrupo::UNIVERSIDAD; i++) {
        Agrupados[i].contactos = new sContacto[6];
        Agrupados[i].tam = 6;
        Agrupados[i].actual = 0;
        Agrupados[i].Grupito = Grupos[i];
    }
    sContacto* Ultimo = miAgenda.misContactos + miAgenda.CantContactos;

    for(u_int i = 0; i < eGrupo::UNIVERSIDAD; i++) {
        for(sContacto* miContacto = miAgenda.misContactos; miContacto != Ultimo; miContacto++) {
            if(miContacto->Grupo == i) {
                if(Agrupados[i].actual == Agrupados[i].tam) {
                    Agrupados[i].contactos = resizeContactos(Agrupados[i].contactos, Agrupados[i].tam, Agrupados[i].tam + BLK);
                    Agrupados[i].tam += BLK;
                }

                Agrupados[i].contactos[Agrupados[i].actual] = *miContacto;
                Agrupados[i].actual++;
            }
        }
    }
}

/**
 * @brief Función eliminar grupo
 */
void removerGrupo(sAgenda* miAgenda,eGrupo grupo)
{
    sAgenda* aux = miAgenda;

    for (u_int i = 0; i < miAgenda->CantMaxima; i++)
    {
        if (aux->misContactos[i].Grupo == grupo)
        {

            aux->misContactos[i] = ContactoNulo;

        }
    }

}
/**
 * @brief Función de remover contacto por retorno por derecha
 */
eRmContacto removerContacto(sAgenda* miAgenda, u_int indexContacto, sContacto& contactoRemovido) {
    if (indexContacto >= miAgenda->CantMaxima)
        return eRmContacto::ErrRmIndex;

    contactoRemovido = miAgenda->misContactos[indexContacto];
    miAgenda->misContactos[indexContacto] = ContactoNulo;
    return eRmContacto::ExitoRemover;
}
/**
 * @brief Función de imprimir todos los integrantes de un grupo
 */
sContacto DevolverXGrupo(sAgenda* miAgenda,eGrupo Grupo)
{
    int cont=0;
    int i;
    while(true)
    {
        if(miAgenda->misContactos[i].Grupo==Grupo)
        {
            cont++;
        }
        i++;
    }

    sContacto*aux=new sContacto[cont];


    while(true)
    {
        if(miAgenda->misContactos[i].Grupo==Grupo)
        {
            aux[i]=miAgenda->misContactos[i];

        }
        aux++;
    }

    return aux [cont];
}



/**
 * @brief Función de Agregar contacto ordenado por apellido
 *return: ExitoAgregar ErrAgrEspacio
 */

eAgrContacto agregarOrdenadoApellido(sAgenda* miAgenda, sContacto miContacto)
{

    u_int pos;
    pos=0;
    OrdenarPorApellido(miAgenda);
    if(!hayEspacio(miAgenda))
        return eAgrContacto::ErrAgrEspacio;
    miAgenda->CantContactos++;
    while(pos<miAgenda->CantContactos && miAgenda->misContactos[pos].Apellido[0] <= miContacto.Apellido[0])
    {
        for(u_int i=0;i<miAgenda->CantContactos;i++)
            {
                if(miAgenda->misContactos[i].Apellido>miContacto.Apellido && miAgenda->misContactos[i+1].Apellido
                                                                                <miContacto.Apellido)
                {
                    pos=i;
                }
            }
    }

    for(u_int i=pos; i<miAgenda->CantContactos;i++)
    {
        miAgenda->misContactos[i+1]=miAgenda->misContactos[i];
    }
    miAgenda->misContactos[pos]=miContacto;
    return eAgrContacto::ExitoAgregar;
}



