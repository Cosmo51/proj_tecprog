#include "Jogo.h"
#include <iostream>
#include <fstream>

using namespace std;

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

        pJog1.executar();

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
            cout << "FASE 1 CONCLUIDA!" << endl;
            cout << "Pontuacao: "
                      << pJog1.getPontos() << endl;

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
        cout << "JOGO PAUSADO!" << endl;
    }
    else
    {
        cout << "JOGO RETOMADO!" << endl;
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

void Jogo::setNomeJogador(const string& nome)
{
    nomeJogador = nome;
}

const string& Jogo::getNomeJogador() const
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

void Jogo::salvarJogo()
{
    if (!modoTeste)
    {
        ofstream arquivo("jogo.txt");

        if (arquivo.is_open())
        {
            arquivo << faseAtual << endl;
            arquivo << nomeJogador << endl;
            arquivo.close();

            pJog1.salvar();

            if (faseAtual == 1)
                fase1.salvar();
            else
                fase2.salvar();

            cout << "Jogo salvo!" << endl;
        }
        else
        {
            cout << "Erro ao salvar jogo!" << endl;
        }
    }
    else
    {
        cout << "Nao e possivel salvar partidas de teste!" << endl;
    }
}

void Jogo::carregarJogo()
{
    ifstream arquivo("jogo.txt");

    int faseSalva;
    string nomeSalvo;

    if (arquivo >> faseSalva &&
        getline(arquivo >> ws, nomeSalvo) &&
        (faseSalva == 1 || faseSalva == 2) &&
        pJog1.carregar())
    {
        bool sucesso;

        if (faseSalva == 1)
            sucesso = fase1.carregar();
        else
            sucesso = fase2.carregar();

        if (sucesso)
        {
            faseAtual = faseSalva;
            nomeJogador = nomeSalvo;

            if (faseAtual == 1)
                fase2.reiniciar();
            else
                fase1.reiniciar();

            modoTeste = false;
            noMenu = false;

            pausar(false);

            cout << "Jogo carregado!" << endl;
        }
        else
        {
            cout << "Erro ao carregar fase!" << endl;
        }
    }
    else
    {
        cout << "Erro ao carregar jogo!" << endl;
    }

    arquivo.close();
}

