#include "Obstaculos.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace Obstaculos;

Obst_Dificil::Obst_Dificil(float x, float y) : Obstaculo(x, y)
{
    danoso = true;
    danosidade = 1;

    definirTamanho(30.f, 10.f);
    carregarTextura("assets/ratoeira.png");
}


Obst_Dificil::~Obst_Dificil(){

}

void Obst_Dificil::salvarDataBuffer(){

}

void Obst_Dificil::executar()
{
    // A danosidade representa o estado da ratoeira: 1 ativa, 0 desativada.
    if (danoso)
    {
        danosidade = 1;
    }
    else
    {
        danosidade = 0;
    }

    if (pJogadorColisao != NULL && danosidade > 0)
    {
        pJogadorColisao->perderVida();
        cout << "Vidas restantes: " << pJogadorColisao->getVidas() << endl;
        danoso = false;
        danosidade = 0;
        definirCor(sf::Color(100, 100, 100));
    }
    pJogadorColisao = NULL;
}

void Obst_Dificil::obstaculizar(Jogador* p)
{
    pJogadorColisao = p;
}

void Obst_Dificil::salvar()
{
    ofstream arquivo("obstaculos.txt", ios::app);

    if (arquivo.is_open())
    {
        arquivo << "Ratoeira" << " "
                << getPosicao().x << " "
                << getPosicao().y << " "
                << danoso << endl;

        arquivo.close();
    }
}

bool Obst_Dificil::carregar(ifstream& arquivo)
{
    float posX, posY;
    bool danosoSalvo;

    if (arquivo >> posX >> posY >> danosoSalvo)
    {
        setPosicao(posX, posY);
        danoso = danosoSalvo;

        if (danoso)
        {
            danosidade = 1;
        }
        else
        {
            danosidade = 0;
        }

        if (!danoso)
            definirCor(sf::Color(100, 100, 100));

        return true;
    }

    return false;
}

