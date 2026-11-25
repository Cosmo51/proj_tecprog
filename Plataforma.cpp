#include "Obstaculos.h"
#include <stdlib.h>

using namespace std;
using namespace Obstaculos;

Plataforma::Plataforma():altura(0)
{
    carregarTextura("assets/plataforma.png");
}

Plataforma::~Plataforma(){

}

void Plataforma::executar(){

}


void Plataforma::obstaculizar(Jogador* p)
{
    if (p != NULL)
    {
        sf::FloatRect jogador = p->getLimites();
        sf::FloatRect plataforma = getLimites();

        sf::Vector2f anterior = p->getPosicaoAnterior();

        float esqJ = jogador.position.x;
        float dirJ = esqJ + jogador.size.x;
        float topoJ = jogador.position.y;
        float baseJ = topoJ + jogador.size.y;

        float esqP = plataforma.position.x;
        float dirP = esqP + plataforma.size.x;
        float topoP = plataforma.position.y;
        float baseP = topoP + plataforma.size.y;

        float esqAnterior = anterior.x;
        float dirAnterior = anterior.x + jogador.size.x;
        float topoAnterior = anterior.y;
        float baseAnterior = anterior.y + jogador.size.y;

        // Colisao por cima
        if (baseAnterior <= topoP && baseJ >= topoP && p->getVelY() >= 0.f)
        {
            p->setPosicao(esqJ, topoP - jogador.size.y);
            p->pararQueda();
        }

        // Colisao por baixo
        else if (topoAnterior >= baseP && topoJ <= baseP && p->getVelY() < 0.f)
        {
            p->setPosicao(esqJ, baseP);
            p->pararSubida();
        }

        // Colisao pela esquerda
        else if (dirAnterior <= esqP && dirJ >= esqP)
        {
            p->setPosicao(esqP - jogador.size.x, topoJ);
        }

        // Colisao pela direita
        else if (esqAnterior >= dirP && esqJ <= dirP)
        {
            p->setPosicao(dirP, topoJ);
        }
    }
}

void Plataforma::obstaculizar(Inimigo* p)
{
    if (p != NULL)
    {
        sf::FloatRect inimigo = p->getLimites();
        sf::FloatRect plataforma = getLimites();

        sf::Vector2f anterior = p->getPosicaoAnterior();

        float esqI = inimigo.position.x;
        float dirI = esqI + inimigo.size.x;
        float topoI = inimigo.position.y;
        float baseI = topoI + inimigo.size.y;

        float esqP = plataforma.position.x;
        float dirP = esqP + plataforma.size.x;
        float topoP = plataforma.position.y;
        float baseP = topoP + plataforma.size.y;

        float esqAnterior = anterior.x;
        float dirAnterior = anterior.x + inimigo.size.x;
        float topoAnterior = anterior.y;
        float baseAnterior = anterior.y + inimigo.size.y;

        // Colisao por cima
        if (baseAnterior <= topoP && baseI >= topoP &&
            p->getVelocidadeY() >= 0.f)
        {
            p->setPosicao(esqI, topoP - inimigo.size.y);
            p->pararQueda();
        }

        // Colisao por baixo
        else if (topoAnterior >= baseP && topoI <= baseP &&
                 p->getVelocidadeY() < 0.f)
        {
            p->setPosicao(esqI, baseP);
            p->pararQueda();
        }

        // Colisao pela esquerda
        else if (dirAnterior <= esqP && dirI >= esqP)
        {
            p->setPosicao(esqP - inimigo.size.x, topoI);
            p->inverterDirecao();
        }

        // Colisao pela direita
        else if (esqAnterior >= dirP && esqI <= dirP)
        {
            p->setPosicao(dirP, topoI);
            p->inverterDirecao();
        }
    }
}

void Plataforma::salvar()
{
    ofstream arquivo("obstaculos.txt", ios::app);

    if (arquivo.is_open())
    {
        arquivo << "Plataforma" << " "
                << getPosicao().x << " "
                << getPosicao().y << " "
                << getTamanho().x << " "
                << getTamanho().y << endl;

        arquivo.close();
    }
}

bool Plataforma::carregar(ifstream& arquivo)
{
    float posX, posY, largura, altura;

    if (arquivo >> posX >> posY >> largura >> altura)
    {
        configurar(posX, posY, largura, altura);

        return true;
    }

    return false;
}

void Plataforma::configurar(float x, float y)
{
    setPosicao(x, y);
}

void Plataforma::configurar(float x, float y, float largura, float altura)
{
    definirTamanho(largura, altura);
    setPosicao(x, y);

    this->altura = static_cast<int>(altura);
}

