#include "Gerenciadores.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace Gerenciadores;


Gerenciador_Colisoes::Gerenciador_Colisoes():
pJog1(NULL)
{

}

Gerenciador_Colisoes::~Gerenciador_Colisoes(){

}

void Gerenciador_Colisoes::setJogador(Jogador* pJ)
{
    pJog1 = pJ;
}

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const
{
    if (pe1 == NULL || pe2 == NULL)
    {
        return false;
    }

    sf::FloatRect limites1 = pe1->getLimites();
    sf::FloatRect limites2 = pe2->getLimites();

    return limites1.findIntersection(limites2).has_value();
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacs()
{
    if (pJog1 != NULL)
    {
        pJog1->restaurarVelocidade();

        list<Obstaculo*>::iterator it;

        for (it = LOs.begin(); it != LOs.end(); it++)
        {
            Obstaculo* obstaculo = *it;

            if (obstaculo != NULL)
            {
                if (verificarColisao(pJog1, obstaculo))
                {
                    obstaculo->obstaculizar(pJog1);
                }
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsInimgs()
{
    if (pJog1 != NULL)
    {
        vector<Inimigo*>::iterator it;

        for (it = LIs.begin(); it != LIs.end(); it++)
        {
            Inimigo* inimigo = *it;

            if (inimigo != NULL && inimigo->getAtivo())
            {
                if (verificarColisao(pJog1, inimigo))
                {
                    sf::FloatRect jog = pJog1->getLimites();
                    sf::FloatRect inim = inimigo->getLimites();

                    sf::Vector2f anteriorJ = pJog1->getPosicaoAnterior();
                    sf::Vector2f anteriorI = inimigo->getPosicaoAnterior();

                    float posXJogador = jog.position.x;
                    float topoJ = jog.position.y;

                    float esqI = inim.position.x;
                    float dirI = esqI + inim.size.x;
                    float topoI = inim.position.y;
                    float baseI = topoI + inim.size.y;

                    // Jogador cai sobre o inimigo
                    if (anteriorJ.y + jog.size.y <= anteriorI.y &&
                        pJog1->getVelY() >= 0.f)
                    {
                        pJog1->setPosicao(posXJogador, topoI - jog.size.y);
                        pJog1->impulsionar();

                        inimigo->desativar();
                        pJog1->adicionarPontos(100);

                        cout << "Inimigo eliminado!" << endl;
                        cout<<"Pontuacao: "<< pJog1->getPontos() << endl;
                    }

                    // Jogador bate por baixo
                    else if (anteriorJ.y >= anteriorI.y + inim.size.y && pJog1->getVelY() < 0.f)
                    {
                        pJog1->setPosicao(posXJogador, baseI);
                        pJog1->pararSubida();

                        inimigo->danificar(pJog1);
                    }

                    // Colisao lateral
                    else
                    {
                        float centroJ = posXJogador + jog.size.x / 2.f;
                        float centroI = esqI + inim.size.x / 2.f;

                        if (centroJ < centroI)
                        {
                            pJog1->setPosicao(esqI - jog.size.x, topoJ);
                        }
                        else
                        {
                            pJog1->setPosicao(dirI, topoJ);
                        }

                        inimigo->danificar(pJog1);
                    }
                }
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesInimgsInimgs()
{
    vector<Inimigo*>::iterator it1;
    vector<Inimigo*>::iterator it2;

    for (it1 = LIs.begin(); it1 != LIs.end(); it1++)
    {
        Inimigo* inimigo1 = *it1;

        if (inimigo1 == NULL || !inimigo1->getAtivo())
            continue;

        it2 = it1;
        it2++;

        for (; it2 != LIs.end(); it2++)
        {
            Inimigo* inimigo2 = *it2;

            if (inimigo2 == NULL || !inimigo2->getAtivo())
                continue;

            if (verificarColisao(inimigo1, inimigo2))
            {
                sf::FloatRect r1 = inimigo1->getLimites();
                sf::FloatRect r2 = inimigo2->getLimites();

                float centro1 = r1.position.x + r1.size.x / 2.f;
                float centro2 = r2.position.x + r2.size.x / 2.f;

                float topo1 = r1.position.y;
                float topo2 = r2.position.y;

                float base1 = topo1 + r1.size.y;
                float base2 = topo2 + r2.size.y;

                // Trata apenas encontros laterais
                if (topo1 < base2 && base1 > topo2)
                {
                    if (centro1 < centro2)
                    {
                        inimigo2->setPosicao(
                            r1.position.x + r1.size.x,
                            topo2
                        );
                    }
                    else
                    {
                        inimigo2->setPosicao(
                            r1.position.x - r2.size.x,
                            topo2
                        );
                    }

                    inimigo1->inverterDirecao();
                    inimigo2->inverterDirecao();
                }
            }
        }
    }
}

void Gerenciador_Colisoes::removerInimigosInativos(ListaEntidades& lista)
{
    vector<Inimigo*>::iterator it = LIs.begin();

    while (it != LIs.end())
    {
        Inimigo* inimigo = *it;

        if (inimigo == NULL)
        {
            it = LIs.erase(it);
        }
        else if (!inimigo->getAtivo())
        {
            it = LIs.erase(it);

            lista.removerEntidade(inimigo);
        }
        else
        {
            it++;
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
{
    if (pJog1 != NULL)
    {
        set<Projetil*>::iterator it;

        for (it = LPs.begin(); it != LPs.end(); it++)
        {
            Projetil* projetil = *it;

            if (projetil != NULL)
            {
                if (projetil->getAtivo())
                {
                    if (verificarColisao(pJog1, projetil))
                    {
                        pJog1->perderVida();
                        projetil->desativar();

                        cout << "Vidas restantes: "
                                  << pJog1->getVidas()
                                  << endl;
                    }
                }
            }
        }
    }
}

void Gerenciador_Colisoes::removerProjeteisInativos(ListaEntidades& lista)
{
    set<Projetil*>::iterator it = LPs.begin();

    while (it != LPs.end())
    {
        Projetil* projetil = *it;

        if (projetil == NULL)
        {
            it = LPs.erase(it);
        }
        else
        {
            sf::FloatRect limites = projetil->getLimites();

            // Desativar quando sair da tela
            if (limites.position.x + limites.size.x < 0.f ||
                limites.position.x > 1000.f ||
                limites.position.y + limites.size.y < 0.f ||
                limites.position.y > 750.f)
            {
                projetil->desativar();
            }

            if (!projetil->getAtivo())
            {
                // Primeiro retira do gerenciador
                it = LPs.erase(it);

                // Depois libera a memoria pela lista
                lista.removerEntidade(projetil);
            }
            else
            {
                it++;
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesProjeteisObstacs()
{
    set<Projetil*>::iterator itProj;
    list<Obstaculo*>::iterator itObst;

    for (itProj = LPs.begin(); itProj != LPs.end(); itProj++)
    {
        Projetil* projetil = *itProj;

        if (projetil != NULL && projetil->getAtivo())
        {
            for (itObst = LOs.begin(); itObst != LOs.end(); itObst++)
            {
                Plataforma* plataforma = dynamic_cast<Plataforma*>(*itObst);

                if (plataforma != NULL)
                {
                    if (verificarColisao(projetil, plataforma))
                    {
                        projetil->desativar();
                        break;
                    }
                }
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesInimgsObstacs()
{
    vector<Inimigo*>::iterator itIn;
    list<Obstaculo*>::iterator itOb;

    for (itIn = LIs.begin(); itIn != LIs.end(); itIn++)
    {
        Inimigo* inimigo = *itIn;

        if (inimigo != NULL)
        {
            for (itOb = LOs.begin(); itOb != LOs.end(); itOb++)
            {
                Plataforma* plataforma = dynamic_cast<Plataforma*>(*itOb);

                if (plataforma != NULL)
                {
                    if (verificarColisao(inimigo, plataforma))
                    {
                        plataforma->obstaculizar(inimigo);
                    }
                }
            }
        }
    }
}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pi)
{
    if (pi != NULL)
    {
        LIs.push_back(pi);
    }
}

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* po)
{
    if (po != NULL)
    {
        LOs.push_back(po);
    }
}

void Gerenciador_Colisoes::incluirProjetil(Projetil* pj)
{
    if (pj != NULL)
    {
        LPs.insert(pj);
    }
}

void Gerenciador_Colisoes::executar()
{

}

void Gerenciador_Colisoes::limpar()
{
    LIs.clear();
    LOs.clear();
    LPs.clear();
}
