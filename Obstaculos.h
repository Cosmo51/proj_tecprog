#pragma once
#include<SFML/Graphics.hpp>
#include "Entidades.h"
#include "Personagens.h"

using namespace Entidades;
using namespace Personagens;

namespace Obstaculos
{
    class Obstaculo : public Entidade
    {

    protected:
        bool danoso;

    public:
        Obstaculo();
        ~Obstaculo();

        void salvarDataBuffer();
        virtual void executar() = 0;
        virtual void salvar() = 0;
        //    virtual void obstaculizar(Jogador* p) = 0;

    };

    class Plataforma : public Obstaculo
    {
    private:
        int altura;

    public:
        Plataforma();
        ~Plataforma();

        void executar();
        void salvar();
        void obstaculizar(Jogador* p);
        void configurar(float x, float y, float largura, float altura);
    };

    class Obst_Dificil : public Obstaculo{

    private:
    short int danosidade;

    public:
    Obst_Dificil();
    ~Obst_Dificil();

    void salvarDataBuffer();
    void executar();
    void obstaculizar(Jogador* p);

    };

    class Obst_Medio : public Obstaculo{

    private:
    float largura;

    public:
    Obst_Medio();
    ~Obst_Medio();

    void executar();
    void obstaculizar(Jogador* p);

    };

    class LimitesGeograficos : public Entidade{

    public:
        LimitesGeograficos();
        ~LimitesGeograficos();

        void executar();
        void salvar();
        void direita();
        void esquerda();

    };
}
