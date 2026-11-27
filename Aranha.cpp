#include "Personagens.h"
#include <fstream>

#include <stdlib.h>

using namespace std;
using namespace Personagens;

Aranha::Aranha(float x, float y) : Inimigo(x, y){

    definirTamanho(35.f, 35.f);
    carregarTextura("assets/aranha.png");
    nivel_maldade = 2;
    velocidadeX = -0.1f * nivel_maldade;
    velocidadeY = 0.f;

}

Aranha::~Aranha(){

}

void Aranha::danificar(Jogador* p)
{
    if (p != NULL)
    {
        float centroJogador = p->getPosicao().x
                            + p->getTamanho().x / 2.f;

        float centroInimigo = getPosicao().x
                           + getTamanho().x / 2.f;

        float direcao = -1.f;

        if (centroJogador >= centroInimigo)
        {
            direcao = 1.f;
        }

        p->receberDanoContato(direcao, forca);
    }
}

void Aranha::executar(){

    mover();

}

void Aranha::salvar()
{
    ofstream arquivo("inimigos.txt", ios::app);

    if (arquivo.is_open())
    {
        arquivo << "Aranha" << " "
                << getPosicao().x << " "
                << getPosicao().y << " "
                << velocidadeX << " "
                << velocidadeY << " "
                << limiteEsquerdo << " "
                << limiteDireito << endl;

        arquivo.close();
    }
}

bool Aranha::carregar(ifstream& arquivo)
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

        return true;
    }

    return false;
}

void Aranha::mover()
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

void Aranha::inverterDirecao()
{
    velocidadeX = -velocidadeX;
}


