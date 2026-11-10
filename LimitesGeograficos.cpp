#include "Obstaculos.h"

using namespace Obstaculos;

LimitesGeograficos::LimitesGeograficos(){

}

LimitesGeograficos::~LimitesGeograficos(){

}

void LimitesGeograficos::direita(){

    body.setSize(sf::Vector2f(1.f, 400.f));
    body.setFillColor(sf::Color::White);
    body.setPosition(sf::Vector2f(0.f, 0.f));
}

void LimitesGeograficos::esquerda(){

    body.setSize(sf::Vector2f(1.f, 400.f));
    body.setFillColor(sf::Color::White);
    body.setPosition(sf::Vector2f(399.f, 0.f));
}

void LimitesGeograficos::executar(){

}

void LimitesGeograficos::salvar(){

}
