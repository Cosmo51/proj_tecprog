#include "Personagens.h"

using namespace Personagens;

Jogador::Jogador(): velocidadeY(0.f){

    body.setSize(sf::Vector2f(25.f, 100.f));
    body.setFillColor(sf::Color::Blue);
    body.setPosition(sf::Vector2f(20.f, 290.f));

}

Jogador::~Jogador(){

}

void Jogador::colidir(Inimigo* pIn){

}

void Jogador::executar(){



}

void Jogador::salvar(){

}

void Jogador::mover(float deltaTime){

    float velocidade = 0.05f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        body.move(sf::Vector2(-velocidade, 0.f));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        body.move(sf::Vector2(velocidade, 0.f));
    }

    //body.move(sf::Vector2(0.f, velocidadeY * deltaTime));//inicio da logica de gravidade a ser implementada
}
