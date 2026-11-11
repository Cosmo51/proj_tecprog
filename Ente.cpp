#include "Ente.h"

Ente::Ente():id(0), body(sf::Vector2f(100.f, 100.f)), window(nullptr)
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
    if (window != nullptr)
    {
        window->draw(body);
    }
}

const sf::RectangleShape& Ente::getBody() const
{
    return body;
}

void Ente::setPosicao(float x, float y)
{
    body.setPosition(sf::Vector2f(x, y));
}

/*void Ente::setGG(Gerenciador_Grafico* pG)
{

}*/
