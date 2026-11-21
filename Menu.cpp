#include "Menu.h"
#include "Gerenciadores.h"
#include "Jogo.h"
#include <iostream>
#include <string>

Menu::Menu() : pJogo(nullptr), opcaoSelecionada(0),
               teclaCimaAnterior(false),
               teclaBaixoAnterior(false),
               teclaEnterAnterior(false),
               tipoMenu(0)
{
    if (!fonte.openFromFile("arial.ttf"))
    {
        std::cout << "Erro ao carregar a fonte!" << std::endl;
    }
}

Menu::~Menu()
{

}

void Menu::executar()
{
    if (pGG == nullptr)
        return;

    bool teclaCimaAtual = pGG->teclaPressionada(sf::Keyboard::Key::Up);
    bool teclaBaixoAtual = pGG->teclaPressionada(sf::Keyboard::Key::Down);
    bool teclaEnterAtual = pGG->teclaPressionada(sf::Keyboard::Key::Enter);

    int quantidadeOpcoes = 0;

    switch (tipoMenu)
    {
        case 0:
            quantidadeOpcoes = 5;
            break;

        case 1:
            quantidadeOpcoes = 3;
            break;

        case 2:
            quantidadeOpcoes = 4;
            break;

        case 3:
        case 4:
            quantidadeOpcoes = 3;
            break;
    }

    // Navegacao para cima
    if (teclaCimaAtual && !teclaCimaAnterior)
    {
        opcaoSelecionada--;

        if (opcaoSelecionada < 0)
            opcaoSelecionada = quantidadeOpcoes - 1;
    }

    // Navegacao para baixo
    if (teclaBaixoAtual && !teclaBaixoAnterior)
    {
        opcaoSelecionada++;

        if (opcaoSelecionada >= quantidadeOpcoes)
            opcaoSelecionada = 0;
    }

    // Confirmacao da opcao
    if (teclaEnterAtual && !teclaEnterAnterior)
    {
        if (pJogo != nullptr)
        {
            switch (tipoMenu)
            {
                // Menu principal
                case 0:
                    switch (opcaoSelecionada)
                    {
                        case 0:
                            pJogo->iniciarJogo();
                            break;

                        case 1:
                            setTipoMenu(1);
                            break;

                        case 2:
                            std::cout << "Carregar jogo" << std::endl;
                            break;

                        case 3:
                            std::cout << "Ranking" << std::endl;
                            break;

                        case 4:
                            pJogo->sair();
                            return;
                    }
                    break;

                // Selecao de fases
                case 1:
                    switch (opcaoSelecionada)
                    {
                        case 0:
                            pJogo->iniciarJogo(1);
                            break;

                        case 1:
                            pJogo->iniciarJogo(2);
                            break;

                        case 2:
                            setTipoMenu(0);
                            opcaoSelecionada = 1;
                            break;
                    }
                    break;

                // Menu de pausa
                case 2:
                    switch (opcaoSelecionada)
                    {
                        case 0:
                            pJogo->pausar(false);
                            break;

                        case 1:
                            std::cout << "Salvar jogo" << std::endl;
                            break;

                        case 2:
                            pJogo->voltarMenu();
                            break;

                        case 3:
                            pJogo->sair();
                            return;
                    }
                    break;

                // Game Over e Vitoria
                case 3:
                case 4:
                    switch (opcaoSelecionada)
                    {
                        case 0:
                            pJogo->iniciarJogo();
                            break;

                        case 1:
                            pJogo->voltarMenu();
                            break;

                        case 2:
                            pJogo->sair();
                            return;
                    }
                    break;
            }
        }
    }

    teclaCimaAnterior = teclaCimaAtual;
    teclaBaixoAnterior = teclaBaixoAtual;
    teclaEnterAnterior = teclaEnterAtual;

    sf::Text titulo(fonte);

    titulo.setCharacterSize(50);
    titulo.setFillColor(sf::Color::Yellow);

    // Desenha o menu principal
    if (tipoMenu == 0)
    {
        titulo.setString("RATINHO NA FAZENDA");
        titulo.setPosition({220.f, 100.f});

        pGG->desenharTexto(titulo);

        const std::string opcoes[5] = {
            "Novo jogo",
            "Selecionar fase",
            "Carregar jogo",
            "Ranking",
            "Sair"
        };

        const float posicoes[][2] = {
            {420.f, 250.f},
            {380.f, 325.f},
            {395.f, 400.f},
            {435.f, 475.f},
            {470.f, 550.f}
        };

        for (int i = 0; i < 5; i++)
        {
            sf::Text texto(fonte);

            texto.setString(opcoes[i]);
            texto.setCharacterSize(35);
            texto.setPosition({posicoes[i][0], posicoes[i][1]});

            if (i == opcaoSelecionada)
                texto.setFillColor(sf::Color::Yellow);
            else
                texto.setFillColor(sf::Color::White);

            pGG->desenharTexto(texto);
        }
    }

    // Desenha o menu de selecao de fases
    else if (tipoMenu == 1)
    {
        titulo.setString("SELECIONAR FASE");
        titulo.setPosition({270.f, 100.f});

        pGG->desenharTexto(titulo);

        const std::string opcoes[3] = {
            "Primeira fase",
            "Segunda fase",
            "Voltar"
        };

        const float posicoes[][2] = {
            {400.f, 250.f},
            {390.f, 325.f},
            {455.f, 400.f}
        };

        for (int i = 0; i < 3; i++)
        {
            sf::Text texto(fonte);

            texto.setString(opcoes[i]);
            texto.setCharacterSize(35);
            texto.setPosition({posicoes[i][0], posicoes[i][1]});

            if (i == opcaoSelecionada)
                texto.setFillColor(sf::Color::Yellow);
            else
                texto.setFillColor(sf::Color::White);

            pGG->desenharTexto(texto);
        }
    }

    // Desenha o menu de pausa
    else if (tipoMenu == 2)
    {
        titulo.setString("JOGO PAUSADO");
        titulo.setPosition({305.f, 100.f});

        pGG->desenharTexto(titulo);

        const std::string opcoes[4] = {
            "Continuar jogo",
            "Salvar jogo",
            "Menu principal",
            "Sair"
        };

        const float posicoes[][2] = {
            {385.f, 250.f},
            {410.f, 325.f},
            {380.f, 400.f},
            {470.f, 475.f}
        };

        for (int i = 0; i < 4; i++)
        {
            sf::Text texto(fonte);

            texto.setString(opcoes[i]);
            texto.setCharacterSize(35);
            texto.setPosition({posicoes[i][0], posicoes[i][1]});

            if (i == opcaoSelecionada)
                texto.setFillColor(sf::Color::Yellow);
            else
                texto.setFillColor(sf::Color::White);

            pGG->desenharTexto(texto);
        }
    }

    // Desenha as telas de Game Over e Vitoria
    else if (tipoMenu == 3 || tipoMenu == 4)
    {
        if (tipoMenu == 3)
        {
            titulo.setString("GAME OVER");
            titulo.setFillColor(sf::Color::Red);
            titulo.setPosition({345.f, 100.f});
        }
        else
        {
            titulo.setString("VITORIA!");
            titulo.setFillColor(sf::Color::Green);
            titulo.setPosition({390.f, 100.f});
        }

        pGG->desenharTexto(titulo);

        // Pontuacao final
        sf::Text pontuacao(fonte);

        if (pJogo != nullptr)
        {
            pontuacao.setString(
                "Pontuacao final: " +
                std::to_string(pJogo->getPontuacao())
            );
        }

        pontuacao.setCharacterSize(30);
        pontuacao.setFillColor(sf::Color::White);
        pontuacao.setPosition({350.f, 200.f});

        pGG->desenharTexto(pontuacao);

        const std::string opcoes[3] = {
            "Jogar novamente",
            "Menu principal",
            "Sair"
        };

        const float posicoes[][2] = {
            {365.f, 325.f},
            {380.f, 400.f},
            {470.f, 475.f}
        };

        for (int i = 0; i < 3; i++)
        {
            sf::Text texto(fonte);

            texto.setString(opcoes[i]);
            texto.setCharacterSize(35);
            texto.setPosition({posicoes[i][0], posicoes[i][1]});

            if (i == opcaoSelecionada)
                texto.setFillColor(sf::Color::Yellow);
            else
                texto.setFillColor(sf::Color::White);

            pGG->desenharTexto(texto);
        }
    }
}

void Menu::setJogo(Jogo* pJ)
{
    pJogo = pJ;
}

void Menu::setTipoMenu(int tipo)
{
    tipoMenu = tipo;
    opcaoSelecionada = 0;
}



