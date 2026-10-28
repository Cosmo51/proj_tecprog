#pragma once
#include<SFML/Graphics.hpp>
#include "Personagem.h"

class Jogador : public Personagem
{
protected:
    int pontos;

public:
    Jogador();
    ~Jogador();
};
