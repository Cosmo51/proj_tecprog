#include "Obstaculos.h"

using namespace Obstaculos;

Plataforma::Plataforma(float x, float y, float largura, float altura){

    body.setSize(sf::Vector2f(largura, altura));
    body.setFillColor(sf::Color::Green);
    body.setPosition(sf::Vector2f(x, y));

}

Plataforma::~Plataforma(){

}

void Plataforma::executar(){

}

void Plataforma::obstaculizar(Jogador* p){

}

void Plataforma::salvar(){

}

