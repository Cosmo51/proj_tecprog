#include "Listas.h"

using namespace Listas;

ListaEntidades::ListaEntidades()
{
}

ListaEntidades::~ListaEntidades()
{
}

void ListaEntidades::incluir(Entidade* pE)
{
    LEs.incluir(pE);
}

void ListaEntidades::removerEntidade(Entidade* entidade)
{
    LEs.remover(entidade);
}

void ListaEntidades::removerEntidade(int pos)
{
    LEs.remover(pos);
}

void ListaEntidades::percorrer()
{
    LEs.percorrer();
}

void ListaEntidades::desenhar()
{
    LEs.desenhar();
}

