#include "Ente.h"
#include "Gerenciadores.h"

#include <stdlib.h>
using namespace Gerenciadores;

Gerenciador_Grafico* Ente::pGG = NULL;
int Ente::contador = 0;

Ente::Ente(float x, float y) : x(x), y(y), id(++contador), body(sf::Vector2f(100.f, 100.f))
{
    setPosicao(x, y);
}

Ente::~Ente()
{

}

void Ente::setGG(Gerenciador_Grafico* pG) { pGG = pG; }

void Ente::desenhar()
{
    if (pGG != NULL)
        pGG->desenharEnte(this);
}

const sf::RectangleShape& Ente::getBody() const { return body; }
int Ente::getId() const { return id; }

void Ente::setPosicao(float x, float y)
{
    this->x = x;
    this->y = y;
    if (pGG != NULL)
        pGG->posicionarFigura(body, x, y);
    else
        body.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Ente::getPosicao() const
{
    return sf::Vector2f(x, y);
}

sf::Vector2f Ente::getTamanho() const
{
    if (pGG != NULL)
        return pGG->obterTamanho(body);

    return body.getSize();
}

sf::FloatRect Ente::getLimites() const
{
    if (pGG != NULL)
        return pGG->obterLimites(body);

    return body.getGlobalBounds();
}

void Ente::moverFigura(float x, float y)
{
    this->x += x;
    this->y += y;
    if (pGG != NULL)
        pGG->posicionarFigura(body, this->x, this->y);
    else
        body.setPosition(sf::Vector2f(this->x, this->y));
}

void Ente::definirFigura(float x, float y, float largura, float altura, sf::Color cor)
{
    this->x = x;
    this->y = y;
    if (pGG != NULL)
        pGG->configurarFigura(body, x, y, largura, altura, cor);
    else
        body.setPosition(sf::Vector2f(x, y));
}

void Ente::definirTamanho(float largura, float altura)
{
    if (pGG != NULL)
        pGG->dimensionarFigura(body, largura, altura);
}

void Ente::definirCor(sf::Color cor)
{
    if (pGG != NULL)
        pGG->colorirFigura(body, cor);
}

bool Ente::teclaPressionada(sf::Keyboard::Key tecla) const
{
    if (pGG != NULL)
        return pGG->teclaPressionada(tecla);

    return false;
}

bool Ente::carregarTextura(const std::string& caminho)
{
    if (pGG != NULL)
        return pGG->carregarTextura(body, textura, caminho);
    return false;
}
