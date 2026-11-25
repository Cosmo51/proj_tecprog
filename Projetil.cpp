#include "Entidades.h"
using namespace Entidades;

Projetil::Projetil()
{
    ativo = true;
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
