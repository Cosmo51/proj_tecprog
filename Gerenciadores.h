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
    desenharEnte(Ente* pE); /* ele não colocou tipo para esse método, mas acredito
                            que deve ser void, por enquanto deixei sem nada mesmo. */
};

class Gerenciador_Colisoes
{
private:
//    vector<Inimigo*> LIs;
//    list<Obstaculo*> LOs;
//    set<Projetil*> LPs;
    Jogador* pJog1;

public:
    const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsInimgs();
    void tratarColisoesJogsProjeteis();
    incluirInimigo(Inimigo* pi); // novamente ele não colocou tipo.
    incluirObstaculo(Obstaculo* po); // novamente ele não colocou tipo.
    incluirProjetil(Projetil* pj); // novamente ele não colocou tipo.
    void executar();
};

}
