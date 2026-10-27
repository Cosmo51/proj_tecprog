#pragma once
#include<SFML/Graphics.hpp>
#include "Entidade.h"

class Projetil : public Entidade
{
protected:
    bool ativo;

public:
    Projetil();
    ~Projetil();
    void executar();
    void salvar();
};
