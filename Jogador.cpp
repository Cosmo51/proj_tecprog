#include "Personagens.h"

using namespace Personagens;

Jogador::Jogador(){

    inicializa();

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

void Jogador::inicializa(){
    vel = 0.5;
}

const sf::RectangleShape Jogador::getBody(){
    return body;
}



void Jogador::mover(){


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        body.move(sf::Vector2(-vel, 0.f));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        body.move(sf::Vector2(vel, 0.f));
    }

}
