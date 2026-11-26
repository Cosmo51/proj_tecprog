#include "Personagens.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace Personagens;

Galinha::Galinha(){

    definirTamanho(44.f, 49.f);
    carregarTextura("assets/galinha.png");
    setPosicao(300.f, 290.f);

    pJogador = NULL;
    nivel_maldade = 2;
    velocidadeX = 0.1f * nivel_maldade;

}

Galinha::~Galinha(){

}

void Galinha::salvar()
{
    ofstream arquivo("inimigos.txt", ios::app);

    if (arquivo.is_open())
    {
        arquivo << "Galinha" << " "
                << getPosicao().x << " "
                << getPosicao().y << " "
                << velocidadeX << " "
                << velocidadeY << " "
                << limiteEsquerdo << " "
                << limiteDireito << endl;

        arquivo.close();
    }
}

bool Galinha::carregar(ifstream& arquivo)
{
    float posX, posY;
    float velX, velY;
    float esquerda, direita;

    if (arquivo >> posX >> posY
                >> velX >> velY
                >> esquerda >> direita)
    {
        setPosicao(posX, posY);

        posicaoAnterior = getPosicao();

        velocidadeX = velX;
        velocidadeY = velY;

        configurarPatrulha(esquerda, direita);

        relogioDisparo.restart();

        return true;
    }

    return false;
}

void Galinha::danificar(Jogador* p)
{
    if (p != NULL)
    {
        float centroJogador = p->getPosicao().x + p->getTamanho().x / 2.f;

        float centroInimigo = getPosicao().x + getTamanho().x / 2.f;

        float direcao = -1.f;

        if (centroJogador >= centroInimigo)
        {
            direcao = 1.f;
        }

        p->receberDanoContato(direcao, forca);
    }
}

void Galinha::executar()
{
    mover();
}

void Galinha::mover()
{
    posicaoAnterior = getPosicao();

    float gravidade = 0.01f;

    velocidadeY += gravidade;

    moverFigura(0.f, velocidadeY);
    moverFigura(velocidadeX, 0.f);

    // Mantem todo o corpo sobre a plataforma de patrulha.
    if (getPosicao().x < limiteEsquerdo)
    {
        setPosicao(limiteEsquerdo, getPosicao().y);
        if (velocidadeX < 0.f)
            inverterDirecao();
    }

    if (getPosicao().x + getTamanho().x > limiteDireito)
    {
        setPosicao(limiteDireito - getTamanho().x, getPosicao().y);
        if (velocidadeX > 0.f)
            inverterDirecao();
    }
}

void Galinha::setJogador(Jogador* p)
{
    pJogador = p;
}

bool Galinha::verificarAtaque()
{
    if (pJogador == NULL)
        return false;

    sf::Vector2f posGalinha = getPosicao();
    sf::Vector2f posJogador = pJogador->getPosicao();

    float distanciaX = posJogador.x - posGalinha.x;

    if (distanciaX < 0.f)
        distanciaX = -distanciaX;

    if (distanciaX <= 250.f)
    {
        if (relogioDisparo.getElapsedTime().asSeconds() >= 3.f)
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

void Galinha::pausar(bool pausa)
{
    if (pausa)
        relogioDisparo.stop();
    else
        relogioDisparo.start();
}




