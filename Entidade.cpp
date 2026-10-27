#include "Entidade.h"

Entidade::Entidade():
body(sf::Vector2f(100.f, 100.f))
{

}

virtual Entidade::~Entidade()
{

}

void Entidade::salvarDataBuffer()
{

}

void Entidade::setWindow(sf::RenderWindow* window)
{
    this->window = window;
}

void Entidade::draw()
{
    window->draw(body);
}

