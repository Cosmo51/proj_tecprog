
#pragma once
#include <SFML/Graphics.hpp>
#include "Listas.h"
#include "Gerenciadores.h"

using namespace Listas;
using namespace Gerenciadores;

namespace Fases
{

class Fase : public Ente
{
protected:
    ListaEntidades lista_ents;
    Gerenciador_Colisoes GC;
    Jogador* pJogador;

public:
    Fase();
    ~Fase();

    virtual void executar();
    void setJogador(Jogador* pJ);

protected:
    void criarInimFaceis();
    void criarPlataformas();
    virtual void criarInimgos() = 0;
    virtual void criarObstaculo() = 0;
    void criarCenario();
};

class FasePrimeira : public Fase
{
private:
    Aranha aranha;
    Galinha galinha;

    Plataforma plat1;
    Plataforma plat2;

    LimitesGeograficos limitedireita;
    LimitesGeograficos limiteesquerda;

public:
    FasePrimeira();
    ~FasePrimeira();

    void executar();

protected:
    void criarInimMedios();
    void criarObstMedios();

    void criarInimgos();
    void criarObstaculo();
};

class FaseSegunda : public Fase
{
private:
    //const int maxChefoes;

public:
    FaseSegunda();
    ~FaseSegunda();

protected:
    void criarChefoes();
    void criarObstMedios();
    void criarProjeteis();
};

}

