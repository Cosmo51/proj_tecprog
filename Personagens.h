#pragma once
#include<SFML/Graphics.hpp>
#include "Entidades.h"
using namespace Entidades;


namespace Personagens
{

class Personagem : public Entidade
{

protected:
    int num_vidas;

public:
    Personagem();
    virtual ~Personagem();

    void salvarDataBuffer();
    virtual void executar() = 0;
    virtual void salvar() = 0;
    virtual void mover() = 0;//deltaTime para a logica da gravidade a ser implementada

};

class Inimigo;

class Jogador : public Personagem
{

private:
    float velX;
    float velY;
    bool noChao;
    void inicializa();

protected:
    int pontos;

public:
    Jogador();
    ~Jogador();

    void colidir(Inimigo* pIn);
    void executar();
    void salvar();
    void mover();
    void pararQueda();
    float getVelY() const;
    void pular();

};

class Inimigo : public Personagem
{

protected:

    int nivel_maldade;

public:

    Inimigo();
    virtual ~Inimigo();

    void salvarDataBuffer();

    virtual void executar() = 0;
    virtual void danificar (Jogador* p) = 0;
    virtual void salvar() = 0;

};

class Inim_Facil : public Inimigo
{

private:
    float raio;

public:
    Inim_Facil();
    ~Inim_Facil();

    void danificar(Jogador* p);
    void executar();
    void salvar();
    void mover();
};

class Inim_Medio : public Inimigo
{

private:
    int tamanho;

public:
    Inim_Medio();
    ~Inim_Medio();
    void danificar(Jogador* p);
    void executar();
    void salvar();
    void mover();
};

class Chefao : public Inimigo
{

private:
    short int forca;

public:
    Chefao();
    ~Chefao();
    void executar();

};
}
