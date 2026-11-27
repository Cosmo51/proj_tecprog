#pragma once
#include<SFML/Graphics.hpp>
#include "Ente.h"
#include<fstream>

namespace Entidades{

    class Entidade : public Ente
    {
    protected:
        //ostream buffer;



    public:
        Entidade(float x = 0.f, float y = 0.f);
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
        int dano;

    public:
        Projetil(float x = 0.f, float y = 0.f);
        ~Projetil();
        virtual void executar() = 0;
        virtual void salvar() = 0;
        bool getAtivo() const;
        void desativar();
        int getDano() const;
        void setDano(int quantidade);
    };

    class Ovo : public Projetil
    {
    private:
        float velocidadeX;

    public:
        Ovo(float x = 0.f, float y = 0.f, float direcao = 1.f);
        ~Ovo();

        void executar();
        void salvar();
        bool carregar(std::ifstream& arquivo);
    };

    class Novelo : public Projetil
    {
    private:
        float velocidadeX;
        float velocidadeY;
        float gravidade;

    public:
        Novelo(float x = 0.f, float y = 0.f, float direcao = 1.f);
        ~Novelo();

        void executar();
        void salvar();
        bool carregar(std::ifstream& arquivo);
    };

    class Queijo : public Entidade
    {
    private:
        sf::Clock relogioBrilho;
    public:
        Queijo(float x = 0.f, float y = 0.f);
        ~Queijo();

        void executar();
        void salvar();
        bool carregar();
    };
}

