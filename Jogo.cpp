#include "Jogo.h"
#include <iostream>

Jogo::Jogo() : noMenu(true), faseAtual(1),
               pausado(false), modoTeste(false)
{
    fase1.setJogador(&pJog1);
    fase2.setJogador(&pJog1);

    menu.setJogo(this);

    executar();
}

Jogo::~Jogo()
{

}

void Jogo::executar()
{
    bool teclaPAnterior = false;

    while (GG.estaAberta())
    {
        GG.tratarEventos();

        if (!GG.estaAberta())
            break;

        // Menu principal
        if (noMenu)
        {
            GG.limpar();

            menu.executar();

            if (!GG.estaAberta())
                break;

            GG.mostrar();

            continue;
        }

        // Controle da pausa
        bool teclaPAtual = GG.teclaPressionada(sf::Keyboard::Key::P);

        if (teclaPAtual && !teclaPAnterior)
        {
            pausar(!pausado);
        }

        teclaPAnterior = teclaPAtual;

        // Menu de pausa
        if (pausado)
        {
            GG.limpar();

            menu.executar();

            if (!GG.estaAberta())
                break;

            GG.mostrar();

            continue;
        }

        GG.limpar();

        pJog1.mover();
        pJog1.saiuDoChao();

        if (faseAtual == 1)
        {
            fase1.executar();
        }
        else
        {
            fase2.executar();
        }

        if (pJog1.getVidas() <= 0)
        {
            finalizarJogo(false);
            continue;
        }

        if (faseAtual == 1 && fase1.getVenceu())
        {
            std::cout << "FASE 1 CONCLUIDA!" << std::endl;
            std::cout << "Pontuacao: "
                      << pJog1.getPontos() << std::endl;

            faseAtual = 2;
            pJog1.prepararNovaFase();

            continue;
        }

        if (faseAtual == 2 && fase2.getVenceu())
        {
            finalizarJogo(true);
            continue;
        }

        pJog1.desenhar();

        GG.mostrar();
    }
}

void Jogo::iniciarJogo(int fase)
{

    pJog1.reiniciar();

    fase1.reiniciar();
    fase2.reiniciar();

    faseAtual = fase;

    pausado = false;
    noMenu = false;
}

void Jogo::sair()
{
    GG.fechar();
}

void Jogo::pausar(bool pausa)
{
    pausado = pausa;

    pJog1.pausar(pausado);

    if (faseAtual == 1)
        fase1.pausar(pausado);
    else
        fase2.pausar(pausado);

    if (pausado)
    {
        menu.setTipoMenu(2);
        std::cout << "JOGO PAUSADO!" << std::endl;
    }
    else
    {
        std::cout << "JOGO RETOMADO!" << std::endl;
    }
}

void Jogo::voltarMenu()
{
    pausado = false;
    noMenu = true;

    menu.setTipoMenu(0);
}

int Jogo::getPontuacao() const
{
    return pJog1.getPontos();
}

void Jogo::finalizarJogo(bool venceu)
{
    pausado = false;
    noMenu = true;

    if (!modoTeste)
    {
        ranking.adicionarPontuacao(pJog1.getPontos(), nomeJogador);
        ranking.salvar();
    }

    if (venceu)
        menu.setTipoMenu(4);
    else
        menu.setTipoMenu(3);
}

void Jogo::setNomeJogador(const std::string& nome)
{
    nomeJogador = nome;
}

const std::string& Jogo::getNomeJogador() const
{
    return nomeJogador;
}

Ranking& Jogo::getRanking()
{
    return ranking;
}

void Jogo::setModoTeste(bool teste)
{
    modoTeste = teste;
}

