#include "Menu.h"
#include "Gerenciadores.h"
#include "Jogo.h"
#include <iostream>
#include <string>

Menu::Menu() : pJogo(nullptr),
               opcaoSelecionada(0),
               teclaCimaAnterior(false),
               teclaBaixoAnterior(false),
               teclaEnterAnterior(false),
               tipoMenu(0),
               nomeJogador(""),
               teclaBackspaceAnterior(false)
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


if (tipoMenu == 5)
{
    char32_t caractere;

    while (pGG->obterCaractereDigitado(caractere))
    {

        if (caractere >= 32 && caractere <= 126 &&
            nomeJogador.size() < 16)
        {
            nomeJogador += static_cast<char>(caractere);
        }
    }


    bool teclaBackspaceAtual =
        pGG->teclaPressionada(sf::Keyboard::Key::Backspace);

    if (teclaBackspaceAtual && !teclaBackspaceAnterior &&
        !nomeJogador.empty())
    {
        nomeJogador.pop_back();
    }

    teclaBackspaceAnterior = teclaBackspaceAtual;
}

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

        case 6:
            quantidadeOpcoes = 1;
            break;
    }

    // Navegacao para cima
    if (tipoMenu != 5 && teclaCimaAtual && !teclaCimaAnterior)
    {
        opcaoSelecionada--;

        if (opcaoSelecionada < 0)
            opcaoSelecionada = quantidadeOpcoes - 1;
    }

    // Navegacao para baixo
    if (tipoMenu != 5 && teclaBaixoAtual && !teclaBaixoAnterior)
    {
        opcaoSelecionada++;

        if (opcaoSelecionada >= quantidadeOpcoes)
            opcaoSelecionada = 0;
    }

    // Confirmacao da opcao
    if (tipoMenu != 5 &&
    teclaEnterAtual && !teclaEnterAnterior)
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
                            nomeJogador.clear();
                            setTipoMenu(5);
                            break;

                        case 1:
                            setTipoMenu(1);
                            break;

                        case 2:
                            std::cout << "Carregar jogo" << std::endl;
                            break;

                        case 3:
                            setTipoMenu(6);
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
                            pJogo->setModoTeste(true);
                            pJogo->iniciarJogo(1);
                            break;

                        case 1:
                            pJogo->setModoTeste(true);
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

                case 6:
                    setTipoMenu(0);
                    break;
            }
        }
    }

        // Confirmacao do nome
    if (tipoMenu == 5 &&
        teclaEnterAtual && !teclaEnterAnterior)
    {
        if (!nomeJogador.empty() && pJogo != nullptr)
        {
            pJogo->setModoTeste(false);
            pJogo->setNomeJogador(nomeJogador);
            pJogo->iniciarJogo();
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

        else if (tipoMenu == 6)
        {
            titulo.setString("RANKING");
            titulo.setPosition({390.f, 100.f});
            pGG->desenharTexto(titulo);
            const std::multimap<int, std::string>& pontuacoes =
            pJogo->getRanking().getPontuacoes();

            int posicao = 1;
            float altura = 170.f;

            for (std::multimap<int, std::string>::const_reverse_iterator it =
            pontuacoes.rbegin();
            it != pontuacoes.rend() && posicao <= 10;
            it++)
            {
                sf::Text texto(fonte);

                texto.setString(
                    std::to_string(posicao) + ". " +
                    it->second + " - " +
                    std::to_string(it->first) + " pontos"
                );

                texto.setCharacterSize(27);
                texto.setFillColor(sf::Color::White);
                texto.setPosition({300.f, altura});

                pGG->desenharTexto(texto);

                altura += 40.f;
                posicao++;
            }

            sf::Text voltar(fonte);

            voltar.setString("ENTER - Voltar");
            voltar.setCharacterSize(25);
            voltar.setFillColor(sf::Color::Yellow);
            voltar.setPosition({400.f, 600.f});

            pGG->desenharTexto(voltar);
        }

        // Tela de entrada do nome
        else if (tipoMenu == 5)
        {
            titulo.setString("NOVO JOGO");
            titulo.setPosition({350.f, 150.f});

            pGG->desenharTexto(titulo);

            sf::Text instrucao(fonte);

            instrucao.setString("Digite seu nome:");
            instrucao.setCharacterSize(30);
            instrucao.setFillColor(sf::Color::White);
            instrucao.setPosition({350.f, 300.f});

            pGG->desenharTexto(instrucao);

            sf::Text nome(fonte);

            nome.setString(nomeJogador + "_");
            nome.setCharacterSize(35);
            nome.setFillColor(sf::Color::Yellow);
            nome.setPosition({350.f, 370.f});

            pGG->desenharTexto(nome);

            sf::Text ajuda(fonte);

            ajuda.setString("ENTER - Confirmar | BACKSPACE - Apagar");
            ajuda.setCharacterSize(20);
            ajuda.setFillColor(sf::Color::White);
            ajuda.setPosition({250.f, 470.f});

            pGG->desenharTexto(ajuda);
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



