#pragma once
#include<SFML/Graphics.hpp>
#include "Ente.h"
#include<fstream>

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
        virtual void executar() = 0;
        virtual void salvar() = 0;
        bool getAtivo() const;
        void desativar();
    };

    class Ovo : public Projetil
    {
    private:
        float velocidadeX;

    public:
        Ovo();
        ~Ovo();

        void executar();
        void salvar();
        bool carregar(std::ifstream& arquivo);
        void configurar(float x, float y, float direcao);
    };

    class Novelo : public Projetil
    {
    private:
        float velocidadeX;
        float velocidadeY;
        float gravidade;

    public:
        Novelo();
        ~Novelo();

        void executar();
        void salvar();
        bool carregar(std::ifstream& arquivo);
        void configurar(float x, float y, float direcao);
    };

    class Queijo : public Entidade
    {
    public:
        Queijo();
        ~Queijo();

        void executar();
        void salvar();
    };
}

