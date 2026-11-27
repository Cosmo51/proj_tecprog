#include "Fases.h"
#include <stdlib.h>
#include<fstream>

using namespace std;

using namespace Fases;

FasePrimeira::FasePrimeira() : venceu(false), maxAranhas(5), maxGalinhas(5), maxLamas(5), maxPlataformas(10)
{
    caminhoCenario = "assets/fundo_fase1.png";
    criarCenario();

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
    vector<Galinha*>::iterator it = galinhas.begin();
    while (it != galinhas.end())
    {
        if (*it == NULL || !(*it)->getAtivo())
            it = galinhas.erase(it);
        else
            it++;
    }

    GC.removerInimigosInativos(lista_ents);

    GC.tratarColisoesJogsObstacs();
    GC.tratarColisoesProjeteisObstacs();
    GC.tratarColisoesJogsProjeteis();

    if (chegouAoQueijo(queijo))
    {
        venceu = true;
    }

    GC.removerProjeteisInativos(lista_ents);

    desenhar();
    lista_ents.desenhar();
}

void FasePrimeira::criarInimFaceis()
{
    const float posicoes[][4] = {
        {435.f, 445.f, 380.f, 530.f},
        {320.f, 705.f, 0.f, 1000.f},
        {650.f, 705.f, 0.f, 1000.f},
        {240.f, 575.f, 190.f, 330.f},
        {780.f, 705.f, 0.f, 1000.f}
    };

    int quantidadeAranhas = 0;

    for (int i = 0; i < 5; i++)
    {
        if (quantidadeAranhas < maxAranhas &&
            (i < 3 || rand() % 100 < 50))
        {
            Aranha* aranha = new Aranha();

            aranha->setPosicao(posicoes[i][0], posicoes[i][1]);
            aranha->configurarPatrulha(
                posicoes[i][2],
                posicoes[i][3]
            );

            lista_ents.incluir(aranha);
            GC.incluirInimigo(aranha);

            quantidadeAranhas++;
        }
    }

    // Plataforma central superior: aranha OU galinha opcional
    if (rand() % 100 < 50)
    {
        if (rand() % 2 == 0)
        {
            if (quantidadeAranhas < maxAranhas)
            {
                Aranha* aranha = new Aranha();

                aranha->setPosicao(610.f, 315.f);
                aranha->configurarPatrulha(555.f, 695.f);

                lista_ents.incluir(aranha);
                GC.incluirInimigo(aranha);

                quantidadeAranhas++;
            }
        }
        else if (static_cast<int>(galinhas.size()) < maxGalinhas)
        {
            Galinha* g = new Galinha();

            g->setPosicao(610.f, 301.f);
            g->configurarPatrulha(555.f, 695.f);

            if (pJogador != NULL)
                g->setJogador(pJogador);

            galinhas.push_back(g);
            lista_ents.incluir(g);
            GC.incluirInimigo(g);
        }
    }
}

void FasePrimeira::criarInimMedios()
{
    const float posicoes[][4] = {
        {175.f, 411.f, 60.f, 230.f},
        {745.f, 421.f, 720.f, 815.f},
        {525.f, 691.f, 0.f, 1000.f},
        {95.f, 411.f, 60.f, 230.f},
        {850.f, 691.f, 0.f, 1000.f}
    };

    for (int i = 0; i < 5; i++)
    {
        if (i < 3 || (static_cast<int>(galinhas.size()) < maxGalinhas &&
                      rand() % 100 < 50))
        {
            Galinha* g = new Galinha();

            g->setPosicao(posicoes[i][0], posicoes[i][1]);
            g->configurarPatrulha(posicoes[i][2], posicoes[i][3]);

            galinhas.push_back(g);
            lista_ents.incluir(g);
            GC.incluirInimigo(g);
        }
    }
}

void FasePrimeira::criarObstMedios()
{
    const float posicoes[][2] = {
        {90.f, 732.f},
        {410.f, 472.f},
        {885.f, 732.f},
        {555.f, 732.f},
        {85.f, 452.f},
        {760.f, 732.f}
    };

    int quantidadeLamas = 0;

    for (int i = 0; i < 6; i++)
    {
        if (quantidadeLamas < maxLamas &&
            (i < 3 || rand() % 100 < 50))
        {
            Obst_Medio* lama = new Obst_Medio();

            lama->configurar(posicoes[i][0], posicoes[i][1]);

            lista_ents.incluir(lama);
            GC.incluirObstaculo(lama);

            quantidadeLamas++;
        }
    }
}

void FasePrimeira::criarPlataformas()
{
    // Chao obrigatorio
    Plataforma* chao = new Plataforma(1);

    chao->configurar(0.f, 740.f, 1000.f, 10.f);

    lista_ents.incluir(chao);
    GC.incluirObstaculo(chao);

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
        Plataforma* p = new Plataforma(2);

        p->configurar(posicoes[i][0], posicoes[i][1],
                     posicoes[i][2], posicoes[i][3]);

        lista_ents.incluir(p);
        GC.incluirObstaculo(p);
    }

    // Parede vertical obrigatoria no chao
    Plataforma* parede = new Plataforma(3);

    parede->configurar(465.f, 610.f, 10.f, 130.f);

    lista_ents.incluir(parede);
    GC.incluirObstaculo(parede);

    int quantidadePlataformas = 8;

    // Paredes opcionais
    const float opcionais[][4] = {
        {740.f, 610.f, 10.f, 130.f},
        {850.f, 245.f, 10.f, 225.f},
        {680.f, 610.f, 10.f, 130.f}
    };

    for (int i = 0; i < 3; i++)
    {
        if (quantidadePlataformas < maxPlataformas &&
            rand() % 100 < 50)
        {
            Plataforma* p = new Plataforma(3);

            p->configurar(opcionais[i][0], opcionais[i][1],
                         opcionais[i][2], opcionais[i][3]);

            lista_ents.incluir(p);
            GC.incluirObstaculo(p);

            quantidadePlataformas++;
        }
    }
}

void FasePrimeira::criarInimgos()
{
    criarInimMedios();
    criarInimFaceis();
}

void FasePrimeira::criarObstaculo()
{
    criarPlataformas();
    criarObstMedios();
}

void FasePrimeira::setJogador(Jogador* pJ)
{
    Fase::setJogador(pJ);

    for (vector<Galinha*>::iterator it = galinhas.begin();
         it != galinhas.end(); it++)
    {
        if (*it != NULL)
            (*it)->setJogador(pJ);
    }
}

void FasePrimeira::criarProjeteis()
{
    criarOvo();
}

void FasePrimeira::criarOvo()
{
    if (pJogador != NULL)
    {
        for (vector<Galinha*>::iterator it = galinhas.begin();
             it != galinhas.end(); it++)
        {
            Galinha* g = *it;
            if (g == NULL || !g->getAtivo())
                continue;

            Jogador* alvo = escolherAlvo(g);
            g->setJogador(alvo);

            if (alvo == NULL || !g->verificarAtaque())
                continue;

            Ovo* ovo = new Ovo();
            float xGalinha = g->getPosicao().x;
            float yGalinha = g->getPosicao().y;
            float xJogador = alvo->getPosicao().x;

            float direcao = 1.f;
            if (xJogador < xGalinha)
                direcao = -1.f;

            ovo->configurar(xGalinha + g->getTamanho().x / 2.f, yGalinha + g->getTamanho().y / 2.f - 10.f, direcao);
            lista_ents.incluir(ovo);
            GC.incluirProjetil(ovo);
        }
    }
}

bool FasePrimeira::getVenceu() const
{
    return venceu;
}

void FasePrimeira::pausar(bool pausa)
{
    for (vector<Galinha*>::iterator it = galinhas.begin();
         it != galinhas.end(); it++)
    {
        if (*it != NULL)
            (*it)->pausar(pausa);
    }
}

void FasePrimeira::reiniciar()
{
    galinhas.clear();
    GC.limpar();
    lista_ents.limpar();

    venceu = false;

    criarObstaculo();
    criarInimgos();

    queijo = new Queijo();
    queijo->setPosicao(925.f, 580.f);
    lista_ents.incluir(queijo);

    setJogador(pJogador);
}

bool FasePrimeira::carregar()
{
    ifstream arquivo("inimigos.txt");

    if (!arquivo.is_open())
        return false;

    galinhas.clear();
    GC.limpar();
    lista_ents.limpar();

    venceu = false;

    if (!carregarObstaculos())
    {
        reiniciar();
        return false;
    }

    string tipo;
    bool sucesso = true;

    while (sucesso && arquivo >> tipo)
    {
        if (tipo == "Aranha")
        {
            Aranha* aranha = new Aranha();

            if (aranha->carregar(arquivo))
            {
                lista_ents.incluir(aranha);
                GC.incluirInimigo(aranha);
            }
            else
            {
                delete aranha;
                sucesso = false;
            }
        }
        else if (tipo == "Galinha")
        {
            Galinha* g = new Galinha();

            if (g->carregar(arquivo))
            {
                galinhas.push_back(g);
                lista_ents.incluir(g);
                GC.incluirInimigo(g);
            }
            else
            {
                delete g;
                sucesso = false;
            }
        }
        else
        {
            sucesso = false;
        }
    }

    arquivo.close();

    if (!sucesso || !carregarProjeteis())
    {
        reiniciar();
        return false;
    }

    queijo = new Queijo();
    lista_ents.incluir(queijo);

    if (!queijo->carregar())
    {
        reiniciar();
        return false;
    }

    setJogador(pJogador);

    return true;
}
