#include "Personagens.h"

using namespace Personagens;

Galinha::Galinha(){

    body.setSize(sf::Vector2f(25.f, 100.f));
    body.setFillColor(sf::Color::Yellow);
    body.setPosition(sf::Vector2f(300.f, 240.f));

}

Galinha::~Galinha(){

}

void Galinha::salvar(){

}

void Galinha::danificar(Jogador* p){

}

void Galinha::executar()
{
    mover();
}

void Galinha::mover()
{
    posicaoAnterior = body.getPosition();

    float gravidade = 0.01f;

    velocidadeY += gravidade;

    body.move(sf::Vector2f(0.f, velocidadeY));
}

