#include "Personagens.h"

using namespace Personagens;

Jogador::Jogador(){

    inicializa();

    body.setSize(sf::Vector2f(25.f, 100.f));
    body.setFillColor(sf::Color::Blue);
    body.setPosition(sf::Vector2f(20.f, 290.f));
    posicaoAnterior = body.getPosition();
}

Jogador::~Jogador(){

}



void Jogador::colidir(Inimigo* pIn){

}

void Jogador::executar(){



}

void Jogador::salvar(){

}

void Jogador::inicializa()
{
    velX = 0.5f;
    velY = 0.f;
    noChao = false;
}

void Jogador::saiuDoChao(){

    noChao = false;

}

void Jogador::mover(){

    float gravidade = 0.01f;

    posicaoAnterior = body.getPosition();

    velY += gravidade;

    body.move(sf::Vector2f(0.f, velY));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        body.move(sf::Vector2(-velX, 0.f));
    }

    if(body.getPosition().x < 1.f){
        body.setPosition(sf::Vector2f(1.f, body.getPosition().y));

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        body.move(sf::Vector2(velX, 0.f));
    }

    if(body.getPosition().x + body.getSize().x > 399.f){
        body.setPosition(sf::Vector2f(399.f - body.getSize().x, body.getPosition().y));

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        pular();
    }

}

void Jogador::pararQueda()
{
    velY = 0.f;
    noChao = true;
}

float Jogador::getVelY() const
{
    return velY;
}

void Jogador::pular()
{
    if(noChao)
    {
        if(velX == 0.25f)
            velY = -0.6f;
        else
            velY = -1.8f;

        noChao = false;
    }
}

sf::Vector2f Jogador::getPosicaoAnterior() const
{
    return posicaoAnterior;
}

void Jogador::pararSubida()
{
    velY = 0.f;
    noChao = false;
}

void Jogador::diminuirVelocidade()
{
    velX = 0.25f;
}

void Jogador::restaurarVelocidade()
{
    velX = 0.5f;
}

