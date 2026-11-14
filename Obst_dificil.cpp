#include "Obstaculos.h"
#include <iostream>

using namespace Obstaculos;

Obst_Dificil::Obst_Dificil()
{
    armada = true;
    danosidade = 1;

    body.setSize(sf::Vector2f(30.f, 10.f));
    body.setFillColor(sf::Color::Red);
    body.setPosition(sf::Vector2f(190.f, 380.f));
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

        body.setFillColor(sf::Color(100, 100, 100));
    }
}

void Obst_Dificil::salvar()
{

}

