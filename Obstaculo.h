#pragma once
#include<SFML/Graphics.hpp>
#include "Entidade.h"

class Obstaculo:public Entidade{

protected:
    bool danoso;

public:
    Obstaculo();
    ~Obstaculo();

    void salvarDataBuffer();
    virtual void executar() = 0;
    virtual void salvar() = 0;
    virtual void obstaculizar(Jogador* p) = 0;

};
