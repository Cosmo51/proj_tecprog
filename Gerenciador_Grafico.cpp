#include "Gerenciadores.h"
using namespace Gerenciadores;

<<<<<<< HEAD
Gerenciador_Grafico::Gerenciador_Grafico() :
    janela(sf::VideoMode({1000, 750}), "Jogo")
{
    janela.setFramerateLimit(240);

    sf::View vista(sf::FloatRect({0.f, 0.f}, {1000.f, 750.f}));
    janela.setView(vista);

    Ente::setGG(this);
=======
Gerenciador_Grafico::Gerenciador_Grafico() :
    janela(sf::VideoMode({1000, 750}), "Jogo")
{
    janela.setFramerateLimit(240);

    sf::View vista(sf::FloatRect({0.f, 0.f}, {1000.f, 750.f}));
    janela.setView(vista);

    Ente::setGG(this);
>>>>>>> 4ca3bc9b27626093d96e0e68ee8a5edadfd3c7fb
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
    Ente::setGG(nullptr);
}

void Gerenciador_Grafico::desenharEnte(Ente* pE)
{
    if (pE != nullptr)
        janela.draw(pE->getBody());
}

bool Gerenciador_Grafico::estaAberta() const { return janela.isOpen(); }

void Gerenciador_Grafico::tratarEventos()
{
    while (const std::optional evento = janela.pollEvent())
    {
        if (evento->is<sf::Event::Closed>())
            janela.close();
    }
}

void Gerenciador_Grafico::limpar() { janela.clear(); }
void Gerenciador_Grafico::mostrar() { janela.display(); }
bool Gerenciador_Grafico::teclaPressionada(sf::Keyboard::Key tecla) const
{
    return sf::Keyboard::isKeyPressed(tecla);
}

void Gerenciador_Grafico::configurarFigura(sf::RectangleShape& figura, float x, float y, float largura, float altura, sf::Color cor)
{
    figura.setSize(sf::Vector2f(largura, altura));
    figura.setFillColor(cor);
    figura.setPosition(sf::Vector2f(x, y));
}

void Gerenciador_Grafico::posicionarFigura(sf::RectangleShape& figura, float x, float y)
{
    figura.setPosition(sf::Vector2f(x, y));
}

void Gerenciador_Grafico::dimensionarFigura(sf::RectangleShape& figura, float largura, float altura)
{
    figura.setSize(sf::Vector2f(largura, altura));
}

void Gerenciador_Grafico::colorirFigura(sf::RectangleShape& figura, sf::Color cor)
{
    figura.setFillColor(cor);
}

void Gerenciador_Grafico::moverFigura(sf::RectangleShape& figura, float x, float y)
{
    figura.move(sf::Vector2f(x, y));
}

sf::Vector2f Gerenciador_Grafico::obterPosicao(const sf::RectangleShape& figura) const
{
    return figura.getPosition();
}

sf::Vector2f Gerenciador_Grafico::obterTamanho(const sf::RectangleShape& figura) const
{
    return figura.getSize();
}

sf::FloatRect Gerenciador_Grafico::obterLimites(const sf::RectangleShape& figura) const
{
    return figura.getGlobalBounds();
}
