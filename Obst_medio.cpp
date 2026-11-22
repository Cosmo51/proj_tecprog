#include "Obstaculos.h"

using namespace Obstaculos;

Obst_Medio::Obst_Medio()
{
    definirTamanho(70.f, 8.f);
    definirCor(sf::Color(120, 75, 35));
    setPosicao(250.f, 382.f);
}

Obst_Medio::~Obst_Medio(){

}

void Obst_Medio::executar(){

}

void Obst_Medio::configurar(float x, float y)
{
    setPosicao(x, y);
}

void Obst_Medio::salvar()
{
    std::ofstream arquivo("obstaculos.txt", std::ios::app);

    if (arquivo.is_open())
    {
        arquivo << "Lama" << " "
                << getPosicao().x << " "
                << getPosicao().y << std::endl;

        arquivo.close();
    }
}

bool Obst_Medio::carregar(std::ifstream& arquivo)
{
    float posX, posY;

    if (arquivo >> posX >> posY)
    {
        configurar(posX, posY);

        return true;
    }

    return false;
}

void Obst_Medio::obstaculizar(Jogador* p)
{
    if (p != nullptr)
    {
        p->diminuirVelocidade();
    }
}

