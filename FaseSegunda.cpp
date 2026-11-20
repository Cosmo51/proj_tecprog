#include "Fases.h"

using namespace Fases;

FaseSegunda::FaseSegunda() : venceu(false), maxGatos(6), maxPlataformas(16), maxAranhas(5), maxRatoeiras(5)
{
    criarObstaculo();
    criarInimgos();

    queijo = new Queijo();
    queijo->setPosicao(915.f, 70.f);
    lista_ents.incluir(queijo);
}

FaseSegunda::~FaseSegunda(){

}

void FaseSegunda::executar()
{
    lista_ents.percorrer();

    criarProjeteis();

    GC.tratarColisoesInimgsObstacs();
    GC.tratarColisoesInimgsInimgs();
    GC.tratarColisoesJogsInimgs();

    // Descarta os ponteiros dos gatos ANTES de apagar os objetos.
    std::vector<Gato*>::iterator it = gatos.begin();
    while (it != gatos.end())
    {
        if (*it == nullptr || !(*it)->getAtivo())
            it = gatos.erase(it);
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

void FaseSegunda::criarChefoes()
{
    const float posicoes[][4] = {
        {385.f, 695.f, 0.f, 1000.f},
        {175.f, 330.f, 140.f, 280.f},
        {750.f, 160.f, 700.f, 840.f},
        {390.f, 175.f, 330.f, 470.f}
    };

    for (int i = 0; i < 4; i++)
    {
        Gato* gato = new Gato();

        gato->setPosicao(posicoes[i][0], posicoes[i][1]);
        gato->configurarPatrulha(posicoes[i][2], posicoes[i][3]);

        gatos.push_back(gato);
        lista_ents.incluir(gato);
        GC.incluirInimigo(gato);
    }

    // Gatos opcionais
    const float opcionais[][4] = {
        {815.f, 695.f, 0.f, 1000.f},
        {250.f, 695.f, 0.f, 1000.f}
    };

    for (int i = 0; i < 2; i++)
    {
        if (static_cast<int>(gatos.size()) < maxGatos &&
            std::rand() % 100 < 50)
        {
            Gato* gato = new Gato();

            gato->setPosicao(opcionais[i][0], opcionais[i][1]);
            gato->configurarPatrulha(opcionais[i][2], opcionais[i][3]);

            gatos.push_back(gato);
            lista_ents.incluir(gato);
            GC.incluirInimigo(gato);
        }
    }
}

void FaseSegunda::criarPlataformas()
{
    Fase::criarPlataformas();

    const float posicoes[][4] = {
        {110.f, 640.f, 10.f, 100.f},
        {235.f, 625.f, 140.f, 10.f},
        {140.f, 375.f, 140.f, 10.f},
        {330.f, 420.f, 10.f, 105.f},
        {330.f, 220.f, 140.f, 10.f},
        {485.f, 295.f, 140.f, 10.f},
        {550.f, 65.f, 140.f, 10.f},
        {700.f, 205.f, 140.f, 10.f},
        {860.f, 100.f, 140.f, 10.f},
        {445.f, 550.f, 140.f, 10.f},
        {705.f, 370.f, 10.f, 75.f},
        {805.f, 505.f, 140.f, 10.f}
    };

    for (int i = 0; i < 12; i++)
    {
        Plataforma* p = new Plataforma();

        p->configurar(posicoes[i][0], posicoes[i][1],
                     posicoes[i][2], posicoes[i][3]);

        lista_ents.incluir(p);
        GC.incluirObstaculo(p);
    }

    int quantidadePlataformas = 13;

    // Paredes opcionais
    const float opcionais[][4] = {
        {575.f, 305.f, 10.f, 245.f},
        {830.f, 25.f, 10.f, 180.f},
        {700.f, 640.f, 10.f, 100.f},
        {420.f, 640.f, 10.f, 100.f}
    };

    for (int i = 0; i < 4; i++)
    {
        if (quantidadePlataformas < maxPlataformas &&
            std::rand() % 100 < 50)
        {
            Plataforma* p = new Plataforma();

            p->configurar(opcionais[i][0], opcionais[i][1],
                         opcionais[i][2], opcionais[i][3]);

            lista_ents.incluir(p);
            GC.incluirObstaculo(p);

            quantidadePlataformas++;
        }
    }
}

void FaseSegunda::criarObstDificeis()
{
    const float posicoes[][2] = {
        {175.f, 730.f},  // Obrigatoria
        {475.f, 540.f},  // Obrigatoria
        {875.f, 495.f},  // Obrigatoria
        {600.f, 730.f},  // Opcional
        {260.f, 615.f},  // Opcional
        {920.f, 730.f}   // Nova opcional
    };

    int quantidadeRatoeiras = 0;

    for (int i = 0; i < 6; i++)
    {
        if (quantidadeRatoeiras < maxRatoeiras &&
            (i < 3 || std::rand() % 100 < 50))
        {
            Obst_Dificil* ratoeira = new Obst_Dificil();

            ratoeira->configurar(posicoes[i][0], posicoes[i][1]);

            lista_ents.incluir(ratoeira);
            GC.incluirObstaculo(ratoeira);

            quantidadeRatoeiras++;
        }
    }
}

void FaseSegunda::criarProjeteis()
{
    criarNovelo();
}

void FaseSegunda::criarNovelo()
{
    if (pJogador == nullptr)
        return;

    for (std::vector<Gato*>::iterator it = gatos.begin();
         it != gatos.end(); it++)
    {
        Gato* g = *it;

        if (g == nullptr || !g->getAtivo() || !g->verificarAtaque())
            continue;

        Novelo* novelo = new Novelo();

        float xGato = g->getPosicao().x;
        float yGato = g->getPosicao().y;
        float xJogador = pJogador->getPosicao().x;

        float direcao = 1.f;
        if (xJogador < xGato)
            direcao = -1.f;

        novelo->configurar(xGato + g->getTamanho().x / 2.f, yGato + g->getTamanho().y / 2.f, direcao);
        lista_ents.incluir(novelo);
        GC.incluirProjetil(novelo);
    }
}

void FaseSegunda::criarInimgos()
{
    // Aranhas obrigatorias
    Fase::criarInimFaceis(165.f, 705.f, 0.f, 1000.f);
    Fase::criarInimFaceis(305.f, 590.f, 235.f, 375.f);
    Fase::criarInimFaceis(575.f, 30.f, 550.f, 690.f);

    int quantidadeAranhas = 3;

    // Aranhas opcionais
    const float opcionais[][4] = {
        {585.f, 260.f, 485.f, 625.f},
        {535.f, 515.f, 445.f, 585.f}
    };

    for (int i = 0; i < 2; i++)
    {
        if (quantidadeAranhas < maxAranhas &&
            std::rand() % 100 < 50)
        {
            Fase::criarInimFaceis(
                opcionais[i][0],
                opcionais[i][1],
                opcionais[i][2],
                opcionais[i][3]
            );

            quantidadeAranhas++;
        }
    }

    criarChefoes();

    // Inimigo XOR na plataforma direita
    if (std::rand() % 2 == 0)
    {
        if (quantidadeAranhas < maxAranhas)
        {
            Fase::criarInimFaceis(855.f, 470.f, 805.f, 945.f);
            quantidadeAranhas++;
        }
    }
    else
    {
        if (static_cast<int>(gatos.size()) < maxGatos)
        {
            Gato* gato = new Gato();

            gato->setPosicao(845.f, 460.f);
            gato->configurarPatrulha(805.f, 945.f);

            gatos.push_back(gato);
            lista_ents.incluir(gato);
            GC.incluirInimigo(gato);
        }
    }
}

void FaseSegunda::criarObstaculo()
{
    criarPlataformas();
    criarObstDificeis();
}

void FaseSegunda::setJogador(Jogador* pJ)
{
    Fase::setJogador(pJ);

    for (std::vector<Gato*>::iterator it = gatos.begin();
         it != gatos.end(); it++)
    {
        if (*it != nullptr)
            (*it)->setJogador(pJ);
    }
}

bool FaseSegunda::getVenceu() const
{
    return venceu;
}
