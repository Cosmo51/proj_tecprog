
#include "Personagens.h"

using namespace Personagens;

Gato::Gato() : pJogador(nullptr)
{
    definirTamanho(55.f, 45.f);
    definirCor(sf::Color::Magenta);

    velocidadeX = 0.35f;
    velocidadeY = 0.f;

    forca = 3;
    nivel_maldade = 3;
}

Gato::~Gato()
{
}

void Gato::executar()
{
    mover();
}

void Gato::mover()
{
    posicaoAnterior = getPosicao();

    float gravidade = 0.01f;

    velocidadeY += gravidade;

    moverFigura(0.f, velocidadeY);
    moverFigura(velocidadeX, 0.f);

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

void Gato::danificar(Jogador* p)
{
    if (p == nullptr)
        return;

    float centroJogador = p->getPosicao().x
                        + p->getTamanho().x / 2.f;

    float centroGato = getPosicao().x
                     + getTamanho().x / 2.f;

    float direcao = -1.f;

    if (centroJogador >= centroGato)
        direcao = 1.f;

    p->receberDanoContato(direcao);
}

void Gato::inverterDirecao()
{
    velocidadeX = -velocidadeX;
}

void Gato::salvar()
{

}

void Gato::setJogador(Jogador* p)
{
    pJogador = p;
}

bool Gato::verificarAtaque()
{
    if (pJogador == nullptr || !getAtivo())
        return false;

    sf::Vector2f posGato = getPosicao();
    sf::Vector2f posJogador = pJogador->getPosicao();

    float distanciaX = posJogador.x - posGato.x;

    if (distanciaX < 0.f)
        distanciaX = -distanciaX;

    if (distanciaX <= 350.f)
    {
        if (relogioDisparo.getElapsedTime().asSeconds() >= 3.f)
        {
            relogioDisparo.restart();
            return true;
        }
    }

    return false;
}



