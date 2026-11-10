#include "Ente.h"

Ente::Ente(): body(sf::Vector2f(100.f, 100.f))
{

}

Ente::~Ente()
{

}



void Ente::setWindow(sf::RenderWindow* window)
{
    this->window = window;
}

void Ente::desenhar()
{

    window->draw(body);

}

/*void Ente::setGG(Gerenciador_Grafico* pG)
{

}*/
