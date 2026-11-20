#include "Personagens.h"
#include <iostream>

using namespace Personagens;

Jogador::Jogador(){

    inicializa();

    definirTamanho(35.f, 45.f);
    definirCor(sf::Color::Blue);
    setPosicao(20.f, 695.f);
    posicaoAnterior = getPosicao();
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
    impulsoX = 0.f;
    invulneravel = false;
    pontos = 0;
}

void Jogador::saiuDoChao(){

    noChao = false;

}

void Jogador::mover()
{
    float gravidade = 0.01f;

    posicaoAnterior = getPosicao();

    if (invulneravel &&
        relogioDano.getElapsedTime().asSeconds() >= 0.5f)
    {
        invulneravel = false;
    }

    velY += gravidade;
    moverFigura(0.f, velY);

    // Durante os primeiros 0.2 segundos, aplica o knockback
    if (invulneravel &&
        relogioDano.getElapsedTime().asSeconds() < 0.2f)
    {
        moverFigura(impulsoX, 0.f);
    }
    else
    {
        if (teclaPressionada(sf::Keyboard::Key::A))
        {
            moverFigura(-velX, 0.f);
        }

        if (teclaPressionada(sf::Keyboard::Key::D))
        {
            moverFigura(velX, 0.f);
        }
    }

    // Limite esquerdo
    if (getPosicao().x < 0.f)
    {
        setPosicao(
            0.f, getPosicao().y);
    }

    // Limite direito
    if (getPosicao().x + getTamanho().x > 1000.f)
    {
        setPosicao(1000.f - getTamanho().x, getPosicao().y);
    }

    if (teclaPressionada(sf::Keyboard::Key::Space))
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

void Jogador::perderVida()
{
    if (num_vidas > 0)
    {
        num_vidas--;
    }
}

int Jogador::getVidas() const
{
    return num_vidas;
}

void Jogador::receberDanoContato(float direcao)
{
    if (invulneravel)
        return;

    perderVida();

    std::cout << "Vidas restantes: " << getVidas() << std::endl;

    impulsoX = 1.5f * direcao;
    velY = -0.9f;
    noChao = false;

    invulneravel = true;
    relogioDano.restart();
}

void Jogador::impulsionar()
{
    velY = -1.0f;
    noChao = false;
}

void Jogador::adicionarPontos(int valor){
    pontos+=valor;
}

int Jogador::getPontos() const{
    return pontos;
}



