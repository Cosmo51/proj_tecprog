#include "Gerenciadores.h"
#include <iostream>
using namespace Gerenciadores;


Gerenciador_Colisoes::Gerenciador_Colisoes():
pJog1(nullptr)
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
    if (pe1 == nullptr || pe2 == nullptr)
    {
        return false;
    }

    sf::FloatRect limites1 = pe1->getBody().getGlobalBounds();
    sf::FloatRect limites2 = pe2->getBody().getGlobalBounds();

    return limites1.findIntersection(limites2).has_value();
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacs()
{
    if (pJog1 == nullptr)
        return;

    pJog1->restaurarVelocidade();

    std::list<Obstaculo*>::iterator it;

    for (it = LOs.begin(); it != LOs.end(); it++)
    {
        Obstaculo* obstaculo = *it;

        if (obstaculo != nullptr)
        {
            if (verificarColisao(pJog1, obstaculo))
            {
                obstaculo->obstaculizar(pJog1);
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsInimgs()
{
    if (pJog1 == nullptr)
        return;

    std::vector<Inimigo*>::iterator it;

    for (it = LIs.begin(); it != LIs.end(); it++)
    {
        Inimigo* inimigo = *it;

        if (inimigo != nullptr && inimigo->getAtivo())
        {
            if (verificarColisao(pJog1, inimigo))
            {
                sf::FloatRect jog = pJog1->getBody().getGlobalBounds();
                sf::FloatRect inim = inimigo->getBody().getGlobalBounds();

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

                    std::cout << "Inimigo eliminado!" << std::endl;
                    std::cout<<"Pontuacao: "<< pJog1->getPontos() << std::endl;
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

void Gerenciador_Colisoes::removerInimigosInativos(ListaEntidades& lista)
{
    std::vector<Inimigo*>::iterator it = LIs.begin();

    while (it != LIs.end())
    {
        Inimigo* inimigo = *it;

        if (inimigo == nullptr)
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
    if (pJog1 == nullptr)
        return;

    std::set<Projetil*>::iterator it;

    for (it = LPs.begin(); it != LPs.end(); it++)
    {
        Projetil* projetil = *it;

        if (projetil != nullptr)
        {
            if (projetil->getAtivo())
            {
                if (verificarColisao(pJog1, projetil))
                {
                    pJog1->perderVida();
                    projetil->desativar();

                    std::cout << "Vidas restantes: "
                              << pJog1->getVidas()
                              << std::endl;
                }
            }
        }
    }
}

void Gerenciador_Colisoes::removerProjeteisInativos(ListaEntidades& lista)
{
    std::set<Projetil*>::iterator it = LPs.begin();

    while (it != LPs.end())
    {
        Projetil* projetil = *it;

        if (projetil == nullptr)
        {
            it = LPs.erase(it);
        }
        else
        {
            sf::FloatRect limites = projetil->getBody().getGlobalBounds();

            // Desativar quando sair da tela
            if (limites.position.x + limites.size.x < 0.f ||
                limites.position.x > 400.f ||
                limites.position.y + limites.size.y < 0.f ||
                limites.position.y > 400.f)
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
    std::set<Projetil*>::iterator itProj;
    std::list<Obstaculo*>::iterator itObst;

    for (itProj = LPs.begin(); itProj != LPs.end(); itProj++)
    {
        Projetil* projetil = *itProj;

        if (projetil != nullptr && projetil->getAtivo())
        {
            for (itObst = LOs.begin(); itObst != LOs.end(); itObst++)
            {
                Plataforma* plataforma = dynamic_cast<Plataforma*>(*itObst);

                if (plataforma != nullptr)
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
    std::vector<Inimigo*>::iterator itIn;
    std::list<Obstaculo*>::iterator itOb;

    for (itIn = LIs.begin(); itIn != LIs.end(); itIn++)
    {
        Inimigo* inimigo = *itIn;

        if (inimigo != nullptr)
        {
            for (itOb = LOs.begin(); itOb != LOs.end(); itOb++)
            {
                Plataforma* plataforma = dynamic_cast<Plataforma*>(*itOb);

                if (plataforma != nullptr)
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
    if (pi != nullptr)
    {
        LIs.push_back(pi);
    }
}

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* po)
{
    if (po != nullptr)
    {
        LOs.push_back(po);
    }
}

void Gerenciador_Colisoes::incluirProjetil(Projetil* pj)
{
    if (pj != nullptr)
    {
        LPs.insert(pj);
    }
}

void Gerenciador_Colisoes::executar()
{

}
