#include "Personagens.h"

using namespace Personagens;

Aranha::Aranha(){

    definirTamanho(25.f, 100.f);
    definirCor(sf::Color::Red);
    setPosicao(355.f, 290.f);
    velocidadeX = -0.2f;
    velocidadeY = 0.f;

}

Aranha::~Aranha(){

}

void Aranha::danificar(Jogador* p)
{
    if (p == nullptr)
        return;

    float centroJogador = p->getPosicao().x
                        + p->getTamanho().x / 2.f;

    float centroInimigo = getPosicao().x
                       + getTamanho().x / 2.f;

    float direcao = -1.f;

    if (centroJogador >= centroInimigo)
    {
        direcao = 1.f;
    }

    p->receberDanoContato(direcao);
}

void Aranha::executar(){

    mover();

}


void Aranha::salvar(){

}

void Aranha::mover()
{
    posicaoAnterior = getPosicao();

    float gravidade = 0.01f;

    velocidadeY += gravidade;
    moverFigura(0.f, velocidadeY);
    moverFigura(velocidadeX, 0.f);

    if(getPosicao().x <= 200.f){
        velocidadeX = 0.2f;
    }

    if(getPosicao().x + getTamanho().x >= 399.f){
        velocidadeX = -0.2f;
    }
}

void Aranha::inverterDirecao()
{
    velocidadeX = -velocidadeX;
}


