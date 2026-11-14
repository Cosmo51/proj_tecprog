#include "Personagens.h"
#include <iostream>

using namespace Personagens;

Galinha::Galinha(){

    body.setSize(sf::Vector2f(25.f, 100.f));
    body.setFillColor(sf::Color::Yellow);
    body.setPosition(sf::Vector2f(300.f, 290.f));

    pJogador = nullptr;
    velocidadeX = 0.2f;

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
    body.move(sf::Vector2f(velocidadeX, 0.f));

    if (body.getPosition().x <= 200.f)
    {
        velocidadeX = 0.2f;
    }

    if (body.getPosition().x + body.getSize().x >= 399.f)
    {
        velocidadeX = -0.2f;
    }
}

void Galinha::setJogador(Jogador* p)
{
    pJogador = p;
}

bool Galinha::verificarAtaque()
{
    if (pJogador == nullptr)
        return false;

    sf::Vector2f posGalinha = body.getPosition();
    sf::Vector2f posJogador = pJogador->getBody().getPosition();

    float distanciaX = posJogador.x - posGalinha.x;

    if (distanciaX < 0.f)
        distanciaX = -distanciaX;

    if (distanciaX <= 100.f)
    {
        if (relogioDisparo.getElapsedTime().asSeconds() >= 2.f)
        {
            relogioDisparo.restart();
            return true;
        }
    }

    return false;
}

void Galinha::inverterDirecao()
{
    velocidadeX = -velocidadeX;
}




