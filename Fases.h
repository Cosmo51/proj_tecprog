
#pragma once
#include <SFML/Graphics.hpp>
#include "Listas.h"
#include "Gerenciadores.h"
#include <vector>

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
    virtual void pausar(bool pausa) = 0;
    virtual void reiniciar() = 0;
    void salvar();
    virtual bool carregar() = 0;

protected:
    virtual void criarInimFaceis() = 0;
    virtual void criarPlataformas() = 0;
    virtual void criarInimgos() = 0;
    virtual void criarObstaculo() = 0;
    void criarCenario();
    bool carregarObstaculos();
    bool carregarProjeteis();
};

class FasePrimeira : public Fase
{
private:
    std::vector<Galinha*> galinhas;
    Queijo* queijo;
    bool venceu;
    const int maxAranhas;
    const int maxGalinhas;
    const int maxLamas;
    const int maxPlataformas;

public:
    FasePrimeira();
    ~FasePrimeira();

    void executar();
    void setJogador(Jogador* pJ);
    bool getVenceu() const;
    void pausar(bool pausa);
    void reiniciar();
    bool carregar();

protected:
    void criarInimMedios();
    void criarInimFaceis();
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
    std::vector<Gato*> gatos;
    Queijo* queijo;
    bool venceu;
    const int maxGatos;
    const int maxPlataformas;
    const int maxAranhas;
    const int maxRatoeiras;

public:
    FaseSegunda();
    ~FaseSegunda();

    void executar();
    void setJogador(Jogador* pJ);
    bool getVenceu() const;
    void pausar(bool pausa);
    void reiniciar();
    bool carregar();

protected:
    void criarChefoes();
    void criarInimFaceis();
    void criarObstDificeis();
    void criarPlataformas();

    void criarInimgos();
    void criarObstaculo();
    void criarProjeteis();
    void criarNovelo();
};

}

