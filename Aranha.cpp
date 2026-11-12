#include "Personagens.h"

using namespace Personagens;

Aranha::Aranha(){

    body.setSize(sf::Vector2f(25.f, 100.f));
    body.setFillColor(sf::Color::Red);
    body.setPosition(sf::Vector2f(355.f, 290.f));
    velocidadeX = -0.2f;
    velocidadeY = 0.f;

}

Aranha::~Aranha(){

}

void Aranha::danificar(Jogador* p){

}

void Aranha::executar(){

}

void Aranha::salvar(){

}

void Aranha::mover(){

    float gravidade = 0.01f;

    velocidadeY += gravidade;
    body.move(sf::Vector2f(0.f, velocidadeY));
    body.move(sf::Vector2f(velocidadeX, 0.f));

    if(body.getPosition().x <= 200.f){
        velocidadeX = 0.2f;
    }

    if(body.getPosition().x + body.getSize().x >= 399.f){
        velocidadeX = -0.2f;
    }



}

void Aranha::pararQueda(){

    velocidadeY = 0.f;

}


float Aranha::getVelocidadeY() const
{
    return velocidadeY;
}


