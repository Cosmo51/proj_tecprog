#include "Fases.h"
#include <fstream>

using namespace Fases;

Fase::Fase() : pJogador(nullptr)
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
    std::ofstream arquivoInimigos("inimigos.txt");
    std::ofstream arquivoObstaculos("obstaculos.txt");
    std::ofstream arquivoProjeteis("projeteis.txt");

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
    std::ifstream arquivo("obstaculos.txt");

    if (!arquivo.is_open())
        return false;

    std::string tipo;
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
    std::ifstream arquivo("projeteis.txt");

    if (!arquivo.is_open())
        return false;

    std::string tipo;
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



