#include "Fases.h"
#include <cstdlib>
#include <ctime>

using namespace Fases;

FasePrimeira::FasePrimeira() : venceu(false)
{
    // Sorteia apenas uma vez, na criacao da fase.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Cria os apoios antes de posicionar os inimigos sobre eles.
    criarObstaculo();
    criarInimgos();

    queijo = new Queijo();
    queijo->setPosicao(925.f, 580.f);
    lista_ents.incluir(queijo);
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

    if (pJogador != nullptr && GC.verificarColisao(pJogador, queijo))
    {
        venceu = true;
    }

    GC.removerProjeteisInativos(lista_ents);

    lista_ents.desenhar();
}


void FasePrimeira::criarInimMedios()
{
    const float posicoes[][4] = {
        {175.f, 415.f, 60.f, 230.f},
        {745.f, 425.f, 720.f, 815.f},
        {525.f, 695.f, 0.f, 1000.f}
    };

    for (int i = 0; i < 3; i++)
    {
        Galinha* g = new Galinha();

        g->setPosicao(posicoes[i][0], posicoes[i][1]);

        g->configurarPatrulha(
            posicoes[i][2],
            posicoes[i][3]
        );

        galinhas.push_back(g);
        lista_ents.incluir(g);
        GC.incluirInimigo(g);
    }
}

void FasePrimeira::criarObstMedios()
{
    const float posicoes[][2] = {
        {90.f, 732.f},   // Chao esquerdo - obrigatoria
        {410.f, 472.f},  // Plataforma central - obrigatoria
        {885.f, 732.f},  // Chao direito - obrigatoria
        {555.f, 732.f},  // Chao central - opcional
        {85.f, 452.f}    // Plataforma superior esquerda - opcional
    };

    for (int i = 0; i < 5; i++)
    {
        if (i < 3 || std::rand() % 100 < 50)
        {
            Obst_Medio* lama = new Obst_Medio();

            lama->setPosicao(posicoes[i][0], posicoes[i][1]);

            lista_ents.incluir(lama);
            GC.incluirObstaculo(lama);
        }
    }
}

void FasePrimeira::criarPlataformas()
{
    Fase::criarPlataformas();

    const float posicoes[][4] = {
        {190.f, 610.f, 140.f, 10.f},
        {60.f, 460.f, 170.f, 10.f},
        {380.f, 480.f, 150.f, 10.f},
        {555.f, 350.f, 140.f, 10.f},
        {720.f, 470.f, 140.f, 10.f},
        {870.f, 610.f, 120.f, 10.f}
    };

    for (int i = 0; i < 6; i++)
    {
        Plataforma* p = new Plataforma();

        p->configurar(posicoes[i][0], posicoes[i][1],
                     posicoes[i][2], posicoes[i][3]);

        lista_ents.incluir(p);
        GC.incluirObstaculo(p);
    }

    // Parede vertical obrigatoria no chao
    Plataforma* parede = new Plataforma();

    parede->configurar(465.f, 610.f, 10.f, 130.f);

    lista_ents.incluir(parede);
    GC.incluirObstaculo(parede);

    // Parede vertical opcional no chao
    if (std::rand() % 100 < 50)
    {
        Plataforma* paredeOpcional = new Plataforma();

        paredeOpcional->configurar(740.f, 610.f, 10.f, 130.f);

        lista_ents.incluir(paredeOpcional);
        GC.incluirObstaculo(paredeOpcional);
    }

    // Pilar vertical opcional na plataforma direita
    if (std::rand() % 100 < 50)
    {
        Plataforma* p = new Plataforma();
        p->configurar(850.f, 245.f, 10.f, 225.f);

        lista_ents.incluir(p);
        GC.incluirObstaculo(p);
    }
}



void FasePrimeira::criarInimgos()
{
    // Aranha obrigatoria na plataforma central superior
    Fase::criarInimFaceis(435.f, 445.f, 380.f, 530.f);

    // Duas aranhas obrigatorias no chao
    Fase::criarInimFaceis(320.f, 705.f, 0.f, 1000.f);
    Fase::criarInimFaceis(650.f, 705.f, 0.f, 1000.f);

    // Aranha opcional na plataforma inferior esquerda
    if (std::rand() % 100 < 50)
    {
        Fase::criarInimFaceis(240.f, 575.f, 190.f, 330.f);
    }

    criarInimMedios();

    // Plataforma central superior: aranha OU galinha opcional
    if (std::rand() % 100 < 50)
    {
        if (std::rand() % 2 == 0)
        {
            Fase::criarInimFaceis(610.f, 315.f, 555.f, 695.f);
        }
        else
        {
            Galinha* g = new Galinha();

            g->setPosicao(610.f, 305.f);
            g->configurarPatrulha(555.f, 695.f);

            galinhas.push_back(g);
            lista_ents.incluir(g);
            GC.incluirInimigo(g);
        }
    }
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

        ovo->configurar(xGalinha + g->getTamanho().x / 2.f, yGalinha + g->getTamanho().y / 2.f, direcao);
        lista_ents.incluir(ovo);
        GC.incluirProjetil(ovo);
    }
}

bool FasePrimeira::getVenceu() const
{
    return venceu;
}
