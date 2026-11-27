#include "Personagens.h"
#include <stdlib.h>

using namespace std;
using namespace Personagens;

Gato::Gato(float x, float y) : Inimigo(x, y), pJogador(NULL)
{
    definirTamanho(68.f, 60.f);
    carregarTextura("assets/gato.png");

    nivel_maldade = 3;
    velocidadeX = 0.12f * nivel_maldade;
    velocidadeY = 0.f;

    forca = 2;
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
    if (p != NULL)
    {
        float centroJogador = p->getPosicao().x
                            + p->getTamanho().x / 2.f;

        float centroGato = getPosicao().x
                         + getTamanho().x / 2.f;

        float direcao = -1.f;

        if (centroJogador >= centroGato)
            direcao = 1.f;

        p->receberDanoContato(direcao, forca);
    }
}

void Gato::inverterDirecao()
{
    velocidadeX = -velocidadeX;
}

void Gato::salvar()
{
    ofstream arquivo("inimigos.txt", ios::app);

    if (arquivo.is_open())
    {
        arquivo << "Gato" << " "
                << getPosicao().x << " "
                << getPosicao().y << " "
                << velocidadeX << " "
                << velocidadeY << " "
                << limiteEsquerdo << " "
                << limiteDireito << " "
                << forca << endl;

        arquivo.close();
    }
}

bool Gato::carregar(ifstream& arquivo)
{
    float posX, posY;
    float velX, velY;
    float esquerda, direita;
    short int forcaSalva;

    if (arquivo >> posX >> posY
                >> velX >> velY
                >> esquerda >> direita
                >> forcaSalva)
    {
        setPosicao(posX, posY);

        posicaoAnterior = getPosicao();

        velocidadeX = velX;
        velocidadeY = velY;

        configurarPatrulha(esquerda, direita);

        forca = forcaSalva;

        relogioDisparo.restart();

        return true;
    }

    return false;
}

void Gato::setJogador(Jogador* p)
{
    pJogador = p;
}

bool Gato::verificarAtaque()
{
    if (pJogador == NULL || !getAtivo())
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

void Gato::pausar(bool pausa)
{
    if (pausa)
        relogioDisparo.stop();
    else
        relogioDisparo.start();
}



