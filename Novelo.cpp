#include "Entidades.h"

using namespace std;

using namespace Entidades;

Novelo::Novelo()
{
    dano = 2;
    velocidadeX = 0.f;
    velocidadeY = 0.f;
    gravidade = 0.01f;

    definirTamanho(15.f, 15.f);
    carregarTextura("assets/novelo.png");
}

Novelo::~Novelo()
{
}

void Novelo::executar()
{
    if (ativo)
    {
        velocidadeY += gravidade;

        moverFigura(velocidadeX, velocidadeY);
    }
}

void Novelo::salvar()
{
    ofstream arquivo("projeteis.txt", ios::app);

    if (arquivo.is_open())
    {
        arquivo << "Novelo" << " "
                << getPosicao().x << " "
                << getPosicao().y << " "
                << velocidadeX << " "
                << velocidadeY << endl;

        arquivo.close();
    }
}

bool Novelo::carregar(ifstream& arquivo)
{
    float posX, posY;
    float velX, velY;

    if (arquivo >> posX >> posY >> velX >> velY)
    {
        setPosicao(posX, posY);

        velocidadeX = velX;
        velocidadeY = velY;

        return true;
    }

    return false;
}

void Novelo::configurar(float x, float y, float direcao)
{
    setPosicao(x, y);

    velocidadeX = 0.7f * direcao;
    velocidadeY = -1.5f;
}

