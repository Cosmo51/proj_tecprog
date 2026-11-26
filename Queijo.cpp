#include "Entidades.h"

using namespace Entidades;
using namespace std;

Queijo::Queijo()
{
    definirTamanho(30.f, 30.f);
    carregarTextura("assets/queijo.png");
}

Queijo::~Queijo()
{
}

void Queijo::executar()
{
    if (relogioBrilho.getElapsedTime().asSeconds() < 0.5f)
        definirCor(sf::Color::White);
    else
        definirCor(sf::Color(255, 235, 170));

    if (relogioBrilho.getElapsedTime().asSeconds() >= 1.f)
        relogioBrilho.restart();
}

void Queijo::salvar()
{
    ofstream arquivo("queijo.txt");
    if (arquivo.is_open())
        arquivo << getPosicao().x << " " << getPosicao().y << endl;
}

bool Queijo::carregar()
{
    ifstream arquivo("queijo.txt");
    float posX, posY;
    if (arquivo >> posX >> posY)
    {
        setPosicao(posX, posY);
        return true;
    }
    return false;
}
