#include "Obstaculos.h"
#include <iostream>

using namespace Obstaculos;

Obst_Dificil::Obst_Dificil()
{
    armada = true;
    danosidade = 1;

    definirTamanho(30.f, 10.f);
    definirCor(sf::Color::Red);
    setPosicao(190.f, 380.f);
}


Obst_Dificil::~Obst_Dificil(){

}

void Obst_Dificil::salvarDataBuffer(){

}

void Obst_Dificil::executar(){

}

void Obst_Dificil::obstaculizar(Jogador* p)
{
    if (p != nullptr && armada)
    {
        p->perderVida();
        std::cout << "Vidas restantes: " << p->getVidas() << std::endl;
        armada = false;

        definirCor(sf::Color(100, 100, 100));
    }
}

void Obst_Dificil::configurar(float x, float y)
{
    setPosicao(x, y);
}

void Obst_Dificil::salvar()
{
    std::ofstream arquivo("obstaculos.txt", std::ios::app);

    if (arquivo.is_open())
    {
        arquivo << "Ratoeira" << " "
                << getPosicao().x << " "
                << getPosicao().y << " "
                << armada << std::endl;

        arquivo.close();
    }
}

bool Obst_Dificil::carregar(std::ifstream& arquivo)
{
    float posX, posY;
    bool armadaSalva;

    if (arquivo >> posX >> posY >> armadaSalva)
    {
        configurar(posX, posY);

        armada = armadaSalva;

        if (!armada)
            definirCor(sf::Color(100, 100, 100));

        return true;
    }

    return false;
}

