#pragma once
#include<SFML/Graphics.hpp>
#include "Entidades.h"

using namespace Entidades;

namespace Listas{

template <class TL>
class Lista{

    template<class TE>
    class Elemento{

        private:
            Elemento<TE>* pProx;
            TE* pinfo;

        public:
            Elemento();
            ~Elemento();

            void incluir(TE* p);
            setProx(Elemento<TE>* pE);
            Elemento<TE>* getProximo() const;
    };


private:
    Elemento<TL>* pPrimeiro;
    Elemento<TL>* pUltimo;

public:
    Lista();
    ~Lista();

    void incluir(TL* p);
    void limpar();



};

class ListaEntidades : public Lista<Entidade>{

private:
    Lista<Entidade> LEs;

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidade* pE);
    void percorrer();
};



}
