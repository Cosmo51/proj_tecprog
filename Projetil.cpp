#include "Entidades.h"
using namespace Entidades;

Projetil::Projetil()
{
    ativo = true;
    dano = 1;
}

Projetil::~Projetil()
{

}

bool Projetil::getAtivo() const
{
    return ativo;
}

void Projetil::desativar()
{
    ativo = false;
}

int Projetil::getDano() const
{
    return dano;
}

void Projetil::setDano(int quantidade)
{
    if (quantidade > 0)
        dano = quantidade;
}
