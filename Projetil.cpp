#include "Entidades.h"
using namespace Entidades;

Projetil::Projetil()
{
    ativo = true;
}

Projetil::~Projetil()
{

}

void Projetil::salvar()
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
