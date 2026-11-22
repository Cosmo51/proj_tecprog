#include "Ente.h"
#include "Gerenciadores.h"

#include <stdlib.h>
using namespace Gerenciadores;

Gerenciador_Grafico* Ente::pGG = NULL;

Ente::Ente() : id(0), body(sf::Vector2f(100.f, 100.f))
{

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

void Ente::setPosicao(float x, float y)
{
    if (pGG != NULL)
        pGG->posicionarFigura(body, x, y);
}

sf::Vector2f Ente::getPosicao() const
{
    if (pGG != NULL)
        return pGG->obterPosicao(body);

    return body.getPosition();
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
    if (pGG != NULL)
        pGG->moverFigura(body, x, y);
}

void Ente::definirFigura(float x, float y, float largura, float altura, sf::Color cor)
{
    if (pGG != NULL)
        pGG->configurarFigura(body, x, y, largura, altura, cor);
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
