#include "Gerenciadores.h"
#include <iostream>
using namespace Gerenciadores;

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const
{
    if (pe1 == nullptr || pe2 == nullptr)
    {
        return false;
    }

    sf::FloatRect limites1 = pe1->getBody().getGlobalBounds();
    sf::FloatRect limites2 = pe2->getBody().getGlobalBounds();

    return limites1.findIntersection(limites2).has_value();
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacs()
{

}

void Gerenciador_Colisoes::tratarColisoesJogsInimgs()
{

}

void Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
{

}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pi)
{

}

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* po)
{

}

void Gerenciador_Colisoes::incluirProjetil(Projetil* pj)
{

}

void Gerenciador_Colisoes::executar()
{

}
