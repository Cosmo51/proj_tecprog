#pragma once
#include<SFML/Graphics.hpp>
#include "Entidades.h"
using namespace Entidades;


namespace Personagens
{

class Personagem : public Entidade
{

protected:
    int num_vidas;

public:
    Personagem();
    virtual ~Personagem();

    void salvarDataBuffer();
    virtual void executar() = 0;
    virtual void salvar() = 0;
    virtual void mover() = 0;

};

class Inimigo;

class Jogador : public Personagem
{

private:
    float velX;
    float velY;
    bool noChao;
    void inicializa();
    sf::Vector2f posicaoAnterior;
    float impulsoX;
    bool invulneravel;
    sf::Clock relogioDano;

protected:
    int pontos;

public:
    Jogador();
    ~Jogador();

    void colidir(Inimigo* pIn);
    void executar();
    void salvar();
    void mover();
    void pararQueda();
    float getVelY() const;
    void pular();
    void saiuDoChao();
    sf::Vector2f getPosicaoAnterior() const;
    void pararSubida();
    void diminuirVelocidade();
    void restaurarVelocidade();
    void perderVida();
    int getVidas() const;
    void receberDanoContato(float direcao);
    void impulsionar();
    void adicionarPontos(int valor);
    int getPontos() const;
};

class Inimigo : public Personagem
{
protected:
    int nivel_maldade;
    float velocidadeY;
    sf::Vector2f posicaoAnterior;
    bool ativo;
    float limiteEsquerdo;
    float limiteDireito;

public:
    Inimigo();
    virtual ~Inimigo();

    void salvarDataBuffer();

    virtual void executar() = 0;
    virtual void danificar(Jogador* p) = 0;
    virtual void salvar() = 0;
    virtual void inverterDirecao() = 0;

    void pararQueda();
    float getVelocidadeY() const;
    sf::Vector2f getPosicaoAnterior() const;
    bool getAtivo() const;
    void desativar();
    void configurarPatrulha(float esquerda, float direita);
};

class Aranha : public Inimigo
{
private:
    float raio;
    float velocidadeX;

public:
    Aranha();
    ~Aranha();

    void danificar(Jogador* p);
    void executar();
    void salvar();
    void mover();
    void inverterDirecao();
};

class Galinha : public Inimigo
{

private:
    int tamanho;
    float velocidadeX;
    Jogador* pJogador;
    sf::Clock relogioDisparo;

public:
    Galinha();
    ~Galinha();
    void danificar(Jogador* p);
    void executar();
    void salvar();
    void mover();
    void setJogador(Jogador* p);
    bool verificarAtaque();
    void inverterDirecao();
};

class Gato : public Inimigo
{
private:
    short int forca;
    float velocidadeX;
    Jogador* pJogador;
    sf::Clock relogioDisparo;

public:
    Gato();
    ~Gato();

    void executar();
    void mover();
    void danificar(Jogador* p);
    void inverterDirecao();
    void salvar();
    void setJogador(Jogador* p);
    bool verificarAtaque();
};
}
