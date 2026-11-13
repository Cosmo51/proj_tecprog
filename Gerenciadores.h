#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<list>
#include "Obstaculos.h"
#include "Entidades.h"
#include "Personagens.h"

using namespace Obstaculos;
using namespace Entidades;
using namespace Personagens;

namespace Gerenciadores
{

class Gerenciador_Grafico
{
private:
// BiblioGrafica obj;

public:
    Gerenciador_Grafico();
    ~Gerenciador_Grafico();
    void desenharEnte(Ente* pE);
};

class Gerenciador_Colisoes
{
private:
    std::vector<Inimigo*> LIs;
    std::list<Obstaculo*> LOs;
    //set<Projetil*> LPs;
    Jogador* pJog1;

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();
    void setJogador(Jogador* pJ);
    const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsInimgs();
    void tratarColisoesJogsProjeteis();
    void incluirInimigo(Inimigo* pi); // novamente ele não colocou tipo.
    void incluirObstaculo(Obstaculo* po); // novamente ele não colocou tipo.
    void incluirProjetil(Projetil* pj); // novamente ele não colocou tipo.
    void executar();
};

}
