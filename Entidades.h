#pragma once
#include<SFML/Graphics.hpp>
#include "Ente.h"

namespace Entidades{

    class Entidade : public Ente
    {
    protected:
        int x;
        int y;
        //ostream buffer; // não sei como isso funciona.



    public:
        Entidade();
        virtual ~Entidade();

    protected:
        void salvarDataBuffer();

    public:
        virtual void executar() = 0;
        virtual void salvar() = 0;

    };

    class Projetil : public Entidade
    {
    protected:
        bool ativo;

    public:
        Projetil();
        ~Projetil();
        void executar();
        void salvar();
    };
}

