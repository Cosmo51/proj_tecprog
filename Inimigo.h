#pragma once
#include<SFML/Graphics.hpp>

class Inimigo : public Personagem
{

protected:

    int nivel_maldade;

public:

    Inimigo();
    ~Inimigo();

    void salvarDataBuffer();

    virtual void executar() = 0;
    virtual void danificar (*Jogador p) = 0;
    virtual void salvar() = 0;
};
