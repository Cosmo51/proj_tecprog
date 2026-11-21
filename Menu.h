#pragma once
#include<SFML/Graphics.hpp>
#include "Ente.h"

class Jogo;

class Menu : public Ente{

private:
    Jogo* pJogo;
    sf::Font fonte;
    int opcaoSelecionada;
    bool teclaCimaAnterior;
    bool teclaBaixoAnterior;
    bool teclaEnterAnterior;
    int tipoMenu;

public:
    Menu();
    ~Menu();
    void executar();
    void setJogo(Jogo* pJ);
    void setTipoMenu(int tipo);
};
