#include "Ente.h"
#include "Gerenciadores.h"

using namespace Gerenciadores;

Gerenciador_Grafico* Ente::pGG = nullptr;

Ente::Ente() : id(0), body(sf::Vector2f(100.f, 100.f)) {}
Ente::~Ente() {}

void Ente::setGG(Gerenciador_Grafico* pG) { pGG = pG; }

void Ente::desenhar()
{
    if (pGG != nullptr)
        pGG->desenharEnte(this);
}

const sf::RectangleShape& Ente::getBody() const { return body; }

void Ente::setPosicao(float x, float y)
{
    if (pGG != nullptr)
        pGG->posicionarFigura(body, x, y);
}

sf::Vector2f Ente::getPosicao() const
{
    return pGG->obterPosicao(body);
}

sf::Vector2f Ente::getTamanho() const
{
    return pGG->obterTamanho(body);
}

sf::FloatRect Ente::getLimites() const
{
    return pGG->obterLimites(body);
}

void Ente::moverFigura(float x, float y)
{
    pGG->moverFigura(body, x, y);
}

void Ente::definirFigura(float x, float y, float largura, float altura, sf::Color cor)
{
    pGG->configurarFigura(body, x, y, largura, altura, cor);
}

void Ente::definirTamanho(float largura, float altura)
{
    pGG->dimensionarFigura(body, largura, altura);
}

void Ente::definirCor(sf::Color cor)
{
    pGG->colorirFigura(body, cor);
}

bool Ente::teclaPressionada(sf::Keyboard::Key tecla) const
{
    return pGG->teclaPressionada(tecla);
}
