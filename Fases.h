
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
    Galinha* galinha;

    LimitesGeograficos* limitedireita;
    LimitesGeograficos* limiteesquerda;

public:
    FasePrimeira();
    ~FasePrimeira();

    void executar();
    void setJogador(Jogador* pJ);

protected:
    void criarInimMedios();
    void criarPlataformas();
    void criarObstMedios();

    void criarInimgos();
    void criarObstaculo();
    void criarProjeteis();
    void criarOvo();
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
    void criarObstDificeis();
    void criarProjeteis();

    void criarInimgos();
    void criarObstaculo();
};

}

