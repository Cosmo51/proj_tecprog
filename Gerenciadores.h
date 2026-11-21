#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<list>
#include <set>
#include "Obstaculos.h"
#include "Entidades.h"
#include "Personagens.h"
#include "Listas.h"

using namespace Obstaculos;
using namespace Entidades;
using namespace Personagens;
using namespace Listas;


namespace Gerenciadores
{

class Gerenciador_Grafico
{
private:
    sf::RenderWindow janela;

public:
    Gerenciador_Grafico();
    ~Gerenciador_Grafico();
    void desenharEnte(Ente* pE);
    bool estaAberta() const;
    void tratarEventos();
    void limpar();
    void mostrar();
    bool teclaPressionada(sf::Keyboard::Key tecla) const;
    void configurarFigura(sf::RectangleShape& figura, float x, float y, float largura, float altura, sf::Color cor);
    void posicionarFigura(sf::RectangleShape& figura, float x, float y);
    void dimensionarFigura(sf::RectangleShape& figura, float largura, float altura);
    void colorirFigura(sf::RectangleShape& figura, sf::Color cor);
    void moverFigura(sf::RectangleShape& figura, float x, float y);
    sf::Vector2f obterPosicao(const sf::RectangleShape& figura) const;
    sf::Vector2f obterTamanho(const sf::RectangleShape& figura) const;
    sf::FloatRect obterLimites(const sf::RectangleShape& figura) const;
    void desenharTexto(const sf::Text& texto);
    void fechar();
};

class Gerenciador_Colisoes
{
private:
    std::vector<Inimigo*> LIs;
    std::list<Obstaculo*> LOs;
    std::set<Projetil*> LPs;
    Jogador* pJog1;

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();
    void setJogador(Jogador* pJ);
    const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsInimgs();
    void removerInimigosInativos(ListaEntidades& lista);
    void tratarColisoesJogsProjeteis();
    void removerProjeteisInativos(ListaEntidades& lista);
    void tratarColisoesProjeteisObstacs();
    void tratarColisoesInimgsObstacs();
    void tratarColisoesInimgsInimgs();
    void incluirInimigo(Inimigo* pi); // novamente ele não colocou tipo.
    void incluirObstaculo(Obstaculo* po); // novamente ele não colocou tipo.
    void incluirProjetil(Projetil* pj); // novamente ele não colocou tipo.
    void executar();
};

}
