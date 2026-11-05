#pragma once
#include<SFML/Graphics.hpp>
#include "Ente.h"
#include "Jogo.h"

class Menu : public Ente{

private:
    Jogo* pJogo;

public:
    Menu();
    ~Menu();
    void executar();

};
