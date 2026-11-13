#include "Gerenciadores.h"
#include <iostream>
using namespace Gerenciadores;


Gerenciador_Colisoes::Gerenciador_Colisoes():
pJog1(nullptr)
{

}

Gerenciador_Colisoes::~Gerenciador_Colisoes(){

}

void Gerenciador_Colisoes::setJogador(Jogador* pJ)
{
    pJog1 = pJ;
}

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
    if (pJog1 == nullptr)
        return;

    pJog1->restaurarVelocidade();

    std::list<Obstaculo*>::iterator it;

    for (it = LOs.begin(); it != LOs.end(); it++)
    {
        Obstaculo* obstaculo = *it;

        if (obstaculo != nullptr)
        {
            if (verificarColisao(pJog1, obstaculo))
            {
                obstaculo->obstaculizar(pJog1);
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsInimgs()
{

}

void Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
{

}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pi)
{
    if (pi != nullptr)
    {
        LIs.push_back(pi);
    }
}

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* po)
{
    if (po != nullptr)
    {
        LOs.push_back(po);
    }
}

void Gerenciador_Colisoes::incluirProjetil(Projetil* pj)
{

}

void Gerenciador_Colisoes::executar()
{

}
