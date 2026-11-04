#pragma once
#include<SFML/Graphics.hpp>
#include "Entidades.h"
using namespace Entidades;


namespace Personagens{

    class Personagem : public Entidade
    {
    protected:
        int num_vidas;

    public:
        Personagem();
        ~Personagem();
    };

    class Jogador : public Personagem
    {
    protected:
        int pontos;

    public:
        Jogador();
        ~Jogador();
    };

    class Inimigo : public Personagem{

    protected:

        int nivel_maldade;

    public:

        Inimigo();
        ~Inimigo();

        void salvarDataBuffer();

        virtual void executar() = 0;
    //    virtual void danificar (Jogador* p) = 0;
        virtual void salvar() = 0;
    };
}
