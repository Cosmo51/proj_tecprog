#pragma once
#include<SFML/Graphics.hpp>
#include "Ente.h"

class Entidade : public Ente
{
protected:
    int x;
    int y;
    ostream buffer; // não sei como isso funciona.

    // parte do tutorial do SFML.
    sf::RectangleShape body;
    sf::RenderWindow* window;

public:
    Entidade();
    virtual ~Entidade();

protected:
    void salvarDataBuffer();

public:
    virtual void Executar() = 0;
    virtual void salvar() = 0;

    // parte do tutorial do SFML.
    void setWindow(sf::RenderWindow* window);
    void draw();
};
