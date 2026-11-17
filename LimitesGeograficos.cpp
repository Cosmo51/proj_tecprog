#include "Obstaculos.h"

using namespace Obstaculos;

LimitesGeograficos::LimitesGeograficos(){

}

LimitesGeograficos::~LimitesGeograficos(){

}

void LimitesGeograficos::direita(){

    definirTamanho(1.f, 400.f);
    definirCor(sf::Color::White);
    setPosicao(399.f, 0.f);
}

void LimitesGeograficos::esquerda(){

    definirTamanho(1.f, 400.f);
    definirCor(sf::Color::White);
    setPosicao(0.f, 0.f);
}

void LimitesGeograficos::executar(){

}

void LimitesGeograficos::salvar(){

}
