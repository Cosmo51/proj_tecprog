#include "Fases.h"
#include <cstdlib>
#include <ctime>

using namespace Fases;

FasePrimeira::FasePrimeira()
{
    // Sorteia apenas uma vez, na criacao da fase.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Cria os apoios antes de posicionar os inimigos sobre eles.
    criarObstaculo();
    criarInimgos();
}

FasePrimeira::~FasePrimeira()
{
}

void FasePrimeira::executar()
{
    lista_ents.percorrer();

    criarProjeteis();

    GC.tratarColisoesInimgsObstacs();
    GC.tratarColisoesInimgsInimgs();
    GC.tratarColisoesJogsInimgs();

    // Descarta os ponteiros das galinhas ANTES de apagar os objetos.
    std::vector<Galinha*>::iterator it = galinhas.begin();
    while (it != galinhas.end())
    {
        if (*it == nullptr || !(*it)->getAtivo())
            it = galinhas.erase(it);
        else
            it++;
    }

    GC.removerInimigosInativos(lista_ents);

    GC.tratarColisoesJogsObstacs();
    GC.tratarColisoesProjeteisObstacs();
    GC.tratarColisoesJogsProjeteis();
    GC.removerProjeteisInativos(lista_ents);

    lista_ents.desenhar();
}

void FasePrimeira::criarInimMedios()
{
    const float posicoes[][4] = {
        {340.f, 265.f, 295.f, 440.f}, // Segunda plataforma
        {670.f, 65.f, 625.f, 770.f},  // Quarta plataforma
        {700.f, 490.f, 650.f, 799.f}  // Chao
    };

    for (int i = 0; i < 3; i++)
    {
        Galinha* g = new Galinha();

        g->setPosicao(posicoes[i][0], posicoes[i][1]);
        g->configurarPatrulha(posicoes[i][2], posicoes[i][3]);

        if (pJogador != nullptr)
            g->setJogador(pJogador);

        galinhas.push_back(g);
        lista_ents.incluir(g);
        GC.incluirInimigo(g);
    }

    // Galinha adicional somente se a plataforma existir
}

void FasePrimeira::criarObstMedios()
{
    const float posicoes[][2] = {
        {230.f, 582.f}, // Chao
        {560.f, 582.f}, // Chao
        {370.f, 357.f}, // Segunda plataforma
        {690.f, 582.f}  // Opcional no chao
    };

    for (int i = 0; i < 4; i++)
    {
        if (i < 3 || std::rand() % 100 < 50)
        {
            Obst_Medio* lama = new Obst_Medio();

            lama->setPosicao(
                posicoes[i][0],
                posicoes[i][1]
            );

            lista_ents.incluir(lama);
            GC.incluirObstaculo(lama);
        }
    }
}

void FasePrimeira::criarPlataformas()
{
    Fase::criarPlataformas();

    const float posicoes[][4] = {
        {130.f, 465.f, 145.f, 10.f}, // Aranha
        {295.f, 365.f, 145.f, 10.f}, // Galinha
        {460.f, 265.f, 145.f, 10.f}, // Aranha
        {625.f, 165.f, 145.f, 10.f}  // Galinha
    };

    for (int i = 0; i < 4; i++)
    {
        Plataforma* plataforma = new Plataforma();

        plataforma->configurar(
            posicoes[i][0],
            posicoes[i][1],
            posicoes[i][2],
            posicoes[i][3]
        );

        lista_ents.incluir(plataforma);
        GC.incluirObstaculo(plataforma);
    }
}

void FasePrimeira::criarInimgos()
{
    // Aranha na primeira plataforma
    Fase::criarInimFaceis(175.f, 365.f, 130.f, 275.f);

    // Aranha na terceira plataforma
    Fase::criarInimFaceis(505.f, 165.f, 460.f, 605.f);

    // Uma aranha obrigatoria no chao
    Fase::criarInimFaceis(465.f, 490.f, 300.f, 600.f);

    // Possibilidade de mais uma aranha no chao
    if (std::rand() % 100 < 50)
        Fase::criarInimFaceis(590.f, 490.f, 450.f, 650.f);

    criarInimMedios();
}

void FasePrimeira::criarObstaculo()
{
    criarPlataformas();
    criarObstMedios();
}

void FasePrimeira::setJogador(Jogador* pJ)
{
    Fase::setJogador(pJ);

    for (std::vector<Galinha*>::iterator it = galinhas.begin();
         it != galinhas.end(); it++)
    {
        if (*it != nullptr)
            (*it)->setJogador(pJ);
    }
}

void FasePrimeira::criarProjeteis()
{
    criarOvo();
}

void FasePrimeira::criarOvo()
{
    if (pJogador == nullptr)
        return;

    for (std::vector<Galinha*>::iterator it = galinhas.begin();
         it != galinhas.end(); it++)
    {
        Galinha* g = *it;
        if (g == nullptr || !g->getAtivo() || !g->verificarAtaque())
            continue;

        Ovo* ovo = new Ovo();
        float xGalinha = g->getPosicao().x;
        float yGalinha = g->getPosicao().y;
        float xJogador = pJogador->getPosicao().x;

        float direcao = 1.f;
        if (xJogador < xGalinha)
            direcao = -1.f;

        ovo->configurar(xGalinha + 10.f, yGalinha + 45.f, direcao);
        lista_ents.incluir(ovo);
        GC.incluirProjetil(ovo);
    }
}
