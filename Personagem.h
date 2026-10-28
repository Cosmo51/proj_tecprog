#pragma once
#include<SFML/Graphics.hpp>

class Personagem : public Entidade
{
protected:
    int num_vidas;

public:
    Personagem();
    ~Personagem();
};
