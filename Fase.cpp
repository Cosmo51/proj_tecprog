#include "Fases.h"
#include <fstream>
#include <stdlib.h>

using namespace std;
using namespace Fases;

Fase::Fase() : pJogador(NULL), pJogador2(NULL)
{
}


Fase::~Fase(){

}

void Fase::executar(){

}

void Fase::criarCenario(){

}

void Fase::setJogador(Jogador* pJ)
{
    pJogador = pJ;
    GC.setJogador(pJ);
}

void Fase::salvar()
{
    ofstream arquivoInimigos("inimigos.txt");
    ofstream arquivoObstaculos("obstaculos.txt");
    ofstream arquivoProjeteis("projeteis.txt");

    if (arquivoInimigos.is_open() &&
        arquivoObstaculos.is_open() &&
        arquivoProjeteis.is_open())
    {
        arquivoInimigos.close();
        arquivoObstaculos.close();
        arquivoProjeteis.close();

        lista_ents.salvar();
    }
}

bool Fase::carregarObstaculos()
{
    ifstream arquivo("obstaculos.txt");

    if (!arquivo.is_open())
        return false;

    string tipo;
    bool sucesso = true;

    while (sucesso && arquivo >> tipo)
    {
        if (tipo == "Plataforma")
        {
            Plataforma* plataforma = new Plataforma();

            if (plataforma->carregar(arquivo))
            {
                lista_ents.incluir(plataforma);
                GC.incluirObstaculo(plataforma);
            }
            else
            {
                delete plataforma;
                sucesso = false;
            }
        }
        else if (tipo == "Lama")
        {
            Obst_Medio* lama = new Obst_Medio();

            if (lama->carregar(arquivo))
            {
                lista_ents.incluir(lama);
                GC.incluirObstaculo(lama);
            }
            else
            {
                delete lama;
                sucesso = false;
            }
        }
        else if (tipo == "Ratoeira")
        {
            Obst_Dificil* ratoeira = new Obst_Dificil();

            if (ratoeira->carregar(arquivo))
            {
                lista_ents.incluir(ratoeira);
                GC.incluirObstaculo(ratoeira);
            }
            else
            {
                delete ratoeira;
                sucesso = false;
            }
        }
        else
        {
            sucesso = false;
        }
    }

    arquivo.close();

    return sucesso;
}

bool Fase::carregarProjeteis()
{
    ifstream arquivo("projeteis.txt");

    if (!arquivo.is_open())
        return false;

    string tipo;
    bool sucesso = true;

    while (sucesso && arquivo >> tipo)
    {
        if (tipo == "Ovo")
        {
            Ovo* ovo = new Ovo();

            if (ovo->carregar(arquivo))
            {
                lista_ents.incluir(ovo);
                GC.incluirProjetil(ovo);
            }
            else
            {
                delete ovo;
                sucesso = false;
            }
        }
        else if (tipo == "Novelo")
        {
            Novelo* novelo = new Novelo();

            if (novelo->carregar(arquivo))
            {
                lista_ents.incluir(novelo);
                GC.incluirProjetil(novelo);
            }
            else
            {
                delete novelo;
                sucesso = false;
            }
        }
        else
        {
            sucesso = false;
        }
    }

    arquivo.close();

    return sucesso;
}




void Fase::setJogador2(Jogador* pJ)
{
    pJogador2 = pJ;
    GC.setJogador2(pJ);
}

Jogador* Fase::escolherAlvo(Inimigo* inimigo)
{
    Jogador* alvo = NULL;
    float menorDistancia = 0.f;
    Jogador* jogadores[2] = {pJogador, pJogador2};

    for (int i = 0; i < 2; i++)
    {
        if (jogadores[i] != NULL && jogadores[i]->getVidas() > 0)
        {
            float distancia = jogadores[i]->getPosicao().x - inimigo->getPosicao().x;
            if (distancia < 0.f)
                distancia = -distancia;
            if (alvo == NULL || distancia < menorDistancia)
            {
                alvo = jogadores[i];
                menorDistancia = distancia;
            }
        }
    }
    return alvo;
}

bool Fase::chegouAoQueijo(Queijo* queijo)
{
    return (pJogador != NULL && pJogador->getVidas() > 0 &&
            GC.verificarColisao(pJogador, queijo)) ||
           (pJogador2 != NULL && pJogador2->getVidas() > 0 &&
            GC.verificarColisao(pJogador2, queijo));
}
