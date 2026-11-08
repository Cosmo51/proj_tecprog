#pragma once
#include<SFML/Graphics.hpp>
#include "Listas.h"
#include "Gerenciadores.h"

using namespace Listas;
using namespace Gerenciadores;

namespace Fases{

class Fase : public Ente{

protected:
    ListaEntidades lista_ents;
    Gerenciador_Colisoes GC;

public:
    Fase();
    ~Fase();

    virtual void executar();

protected:
    void criarInimFaceis();
    void criarPlataformas();
    virtual void criarInimgos() = 0;
    virtual void criarObstaculo() = 0;
    void criarCenario();

};

class FasePrimeira : public Fase{

private:
    //const int maxInimMedios;

public:
    FasePrimeira();
    ~FasePrimeira();

protected:
    void criarInimMedios();
    void criarObstMedios();

};

class FaseSegunda : public Fase{

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
