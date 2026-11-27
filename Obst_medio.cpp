#include "Obstaculos.h"
#include <stdlib.h>

using namespace std;
using namespace Obstaculos;

Obst_Medio::Obst_Medio(float x, float y) : Obstaculo(x, y)
{
    definirTamanho(70.f, 8.f);
    carregarTextura("assets/lama.png");
}

Obst_Medio::~Obst_Medio(){

}

void Obst_Medio::executar()
{
    if (pJogadorColisao != NULL)
        pJogadorColisao->diminuirVelocidade();
    pJogadorColisao = NULL;
}

void Obst_Medio::salvar()
{
    ofstream arquivo("obstaculos.txt", ios::app);

    if (arquivo.is_open())
    {
        arquivo << "Lama" << " "
                << getPosicao().x << " "
                << getPosicao().y << endl;

        arquivo.close();
    }
}

bool Obst_Medio::carregar(ifstream& arquivo)
{
    float posX, posY;

    if (arquivo >> posX >> posY)
    {
        setPosicao(posX, posY);

        return true;
    }

    return false;
}

void Obst_Medio::obstaculizar(Jogador* p)
{
    pJogadorColisao = p;
}

