#include "Entidades.h"
using namespace Entidades;

Entidade::Entidade(float x, float y) :
Ente(), x(x), y(y)
{
    setPosicao(x, y);
}

Entidade::~Entidade()
{

}

void Entidade::salvarDataBuffer()
{

}




