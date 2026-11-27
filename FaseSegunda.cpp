#include "Fases.h"
#include <fstream>
#include <stdlib.h>

using namespace std;

using namespace Fases;

FaseSegunda::FaseSegunda() : venceu(false), maxGatos(6), maxPlataformas(16), maxAranhas(5), maxRatoeiras(5)
{

   caminhoCenario = "assets/fundo_fase2.png";
    criarCenario();

    criarObstaculo();
    criarInimgos();

    queijo = new Queijo(915.f, 70.f);
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
    vector<Gato*>::iterator it = gatos.begin();
    while (it != gatos.end())
    {
        if (*it == NULL || !(*it)->getAtivo())
            it = gatos.erase(it);
        else
            it++;
    }

    GC.removerInimigosInativos(lista_ents);

    GC.tratarColisoesJogsObstacs();
    GC.tratarColisoesJogsJogs();
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

void FaseSegunda::criarInimFaceis()
{
    const float posicoes[][4] = {
        {165.f, 705.f, 0.f, 1000.f},
        {305.f, 590.f, 235.f, 375.f},
        {575.f, 30.f, 550.f, 690.f},
        {585.f, 260.f, 485.f, 625.f},
        {535.f, 515.f, 445.f, 585.f}
    };

    int quantidadeAranhas = 0;

    for (int i = 0; i < 5; i++)
    {
        if (quantidadeAranhas < maxAranhas &&
            (i < 3 || rand() % 100 < 50))
        {
            Aranha* aranha = new Aranha(posicoes[i][0], posicoes[i][1]);
            aranha->configurarPatrulha(
                posicoes[i][2],
                posicoes[i][3]
            );

            lista_ents.incluir(aranha);
            GC.incluirInimigo(aranha);

            quantidadeAranhas++;
        }
    }

    // Inimigo XOR na plataforma direita
    if (rand() % 2 == 0)
    {
        if (quantidadeAranhas < maxAranhas)
        {
            Aranha* aranha = new Aranha(855.f, 470.f);
            aranha->configurarPatrulha(805.f, 945.f);

            lista_ents.incluir(aranha);
            GC.incluirInimigo(aranha);

            quantidadeAranhas++;
        }
    }
    else if (static_cast<int>(gatos.size()) < maxGatos)
    {
        Gato* gato = new Gato(845.f, 445.f);
        gato->configurarPatrulha(805.f, 945.f);

        gatos.push_back(gato);
        lista_ents.incluir(gato);
        GC.incluirInimigo(gato);
    }
}

void FaseSegunda::criarChefoes()
{
    const float posicoes[][4] = {
        {385.f, 680.f, 0.f, 1000.f},
        {175.f, 315.f, 140.f, 280.f},
        {750.f, 145.f, 700.f, 840.f},
        {390.f, 160.f, 321.f, 470.f}
    };

    for (int i = 0; i < 4; i++)
    {
        Gato* gato = new Gato(posicoes[i][0], posicoes[i][1]);
        gato->configurarPatrulha(posicoes[i][2], posicoes[i][3]);

        gatos.push_back(gato);
        lista_ents.incluir(gato);
        GC.incluirInimigo(gato);
    }

    // Gatos opcionais
    const float opcionais[][4] = {
        {815.f, 680.f, 0.f, 1000.f},
        {250.f, 680.f, 0.f, 1000.f}
    };

    for (int i = 0; i < 2; i++)
    {
        if (static_cast<int>(gatos.size()) < maxGatos &&
            rand() % 100 < 50)
        {
            Gato* gato = new Gato(opcionais[i][0], opcionais[i][1]);
            gato->configurarPatrulha(opcionais[i][2], opcionais[i][3]);

            gatos.push_back(gato);
            lista_ents.incluir(gato);
            GC.incluirInimigo(gato);
        }
    }
}

void FaseSegunda::criarPlataformas()
{
    // Chao obrigatorio
    Plataforma* chao = new Plataforma(4);

    chao->configurar(0.f, 740.f, 1000.f, 10.f);

    lista_ents.incluir(chao);
    GC.incluirObstaculo(chao);

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
        Plataforma* p = new Plataforma(posicoes[i][3] > posicoes[i][2] ? 6 : 5);

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
            rand() % 100 < 50)
        {
            Plataforma* p = new Plataforma(6);

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
            (i < 3 || rand() % 100 < 50))
        {
            Obst_Dificil* ratoeira = new Obst_Dificil(posicoes[i][0], posicoes[i][1]);

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
    if (pJogador != NULL)
    {
        for (vector<Gato*>::iterator it = gatos.begin();
             it != gatos.end(); it++)
        {
            Gato* g = *it;

            if (g == NULL || !g->getAtivo())
                continue;

            Jogador* alvo = escolherAlvo(g);
            g->setJogador(alvo);

            if (alvo == NULL || !g->verificarAtaque())
                continue;

            float xGato = g->getPosicao().x;
            float yGato = g->getPosicao().y;
            float xJogador = alvo->getPosicao().x;

            float direcao = 1.f;
            if (xJogador < xGato)
                direcao = -1.f;

            Novelo* novelo = new Novelo(xGato + g->getTamanho().x / 2.f, yGato + g->getTamanho().y / 2.f, direcao);
            novelo->setDano(g->getForca());
            lista_ents.incluir(novelo);
            GC.incluirProjetil(novelo);
        }
    }
}

void FaseSegunda::criarInimgos()
{
    criarChefoes();
    criarInimFaceis();
}

void FaseSegunda::criarObstaculo()
{
    criarPlataformas();
    criarObstDificeis();
}

void FaseSegunda::setJogador(Jogador* pJ)
{
    Fase::setJogador(pJ);

    for (vector<Gato*>::iterator it = gatos.begin();
         it != gatos.end(); it++)
    {
        if (*it != NULL)
            (*it)->setJogador(pJ);
    }
}

bool FaseSegunda::getVenceu() const
{
    return venceu;
}

void FaseSegunda::pausar(bool pausa)
{
    for (vector<Gato*>::iterator it = gatos.begin();
         it != gatos.end(); it++)
    {
        if (*it != NULL)
            (*it)->pausar(pausa);
    }
}

void FaseSegunda::reiniciar()
{
    gatos.clear();
    GC.limpar();
    lista_ents.limpar();

    venceu = false;

    criarObstaculo();
    criarInimgos();

    queijo = new Queijo(915.f, 70.f);
    lista_ents.incluir(queijo);

    setJogador(pJogador);
}

bool FaseSegunda::carregar()
{
    ifstream arquivo("inimigos.txt");

    if (!arquivo.is_open())
        return false;

    gatos.clear();
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
        else if (tipo == "Gato")
        {
            Gato* g = new Gato();

            if (g->carregar(arquivo))
            {
                gatos.push_back(g);
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
