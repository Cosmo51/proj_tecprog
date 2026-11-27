#include "Obstaculos.h"
#include <stdlib.h>
#include <sstream>

using namespace std;
using namespace Obstaculos;

Plataforma::Plataforma(int tipo) : altura(0), tipoTextura(tipo)
{
    selecionarTextura(tipo);
}

void Plataforma::selecionarTextura(int tipo)
{
    tipoTextura = tipo;

    switch (tipo)
    {
        case 1:
            carregarTextura("assets/chao.png");
            break;

        case 2:
            carregarTextura("assets/plataforma_horizontal.png");
            break;

        case 3:
            carregarTextura("assets/plataforma_vertical.png");
            break;

        case 4:
            carregarTextura("assets/chao_fase2.png");
            break;

        case 5:
            carregarTextura("assets/plataforma_horizontal_fase2.png");
            break;

        case 6:
            carregarTextura("assets/plataforma_vertical_fase2.png");
            break;
    }
}

Plataforma::~Plataforma(){

}

void Plataforma::executar()
{
    if (pJogadorColisao != NULL && (tipoTextura == 2 || tipoTextura == 5))
    {
        if (rand() % 100000 == 0)
            pJogadorColisao->perderVida();
    }
    pJogadorColisao = NULL;
}


void Plataforma::obstaculizar(Jogador* p)
{
    pJogadorColisao = p;
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
                << getTamanho().y << " "
                << tipoTextura << endl;

        arquivo.close();
    }
}

bool Plataforma::carregar(ifstream& arquivo)
{
    float posX, posY, largura, altura;

    if (arquivo >> posX >> posY >> largura >> altura)
    {
        int tipo = 2;
        string restante;
        getline(arquivo, restante);
        istringstream leitura(restante);
        if (!(leitura >> tipo))
        {
            tipo = 2;
            if (largura >= 1000.f && posY >= 740.f)
                tipo = 1;
            else if (altura > largura)
                tipo = 3;
        }
        selecionarTextura(tipo);
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
    body.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(largura), static_cast<int>(altura)}));
}

