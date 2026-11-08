#include "Personagens.h"

using namespace Personagens;

Jogador::Jogador(){

    body.setSize(sf::Vector2(25.f, 100.f));
    body.setFillColor(sf::Color::Blue);
    body.setPosition(sf::Vector2f(20.f, 170.f));

}

Jogador::~Jogador(){

}

Jogador::colidir(Inimigo* pIn){

}

void Jogador::executar(){



}

void Jogador::salvar(){

}

void Jogador::mover(){

}
