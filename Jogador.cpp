#include "Personagens.h"
#include <iostream>
#include <fstream>

using namespace std;

using namespace Personagens;

Jogador::Jogador(){

    inicializa();

    definirTamanho(35.f, 45.f);
    carregarTextura("assets/rato.png");
    setPosicao(20.f, 695.f);
    posicaoAnterior = getPosicao();
}

Jogador::~Jogador(){

}



void Jogador::colidir(Inimigo* pIn)
{
    if (pIn != NULL && pIn->getAtivo())
    {
        sf::FloatRect jog = getLimites();
        sf::FloatRect inim = pIn->getLimites();

        sf::Vector2f anteriorJ = getPosicaoAnterior();
        sf::Vector2f anteriorI = pIn->getPosicaoAnterior();

        float posXJogador = jog.position.x;
        float topoJ = jog.position.y;

        float esqI = inim.position.x;
        float dirI = esqI + inim.size.x;
        float topoI = inim.position.y;
        float baseI = topoI + inim.size.y;

        // Jogador cai sobre o inimigo
        if (anteriorJ.y + jog.size.y <= anteriorI.y &&
            getVelY() >= 0.f)
        {
            setPosicao(posXJogador, topoI - jog.size.y);
            impulsionar();

            pIn->desativar();
            adicionarPontos(100);

            cout << "Inimigo eliminado!" << endl;
            cout<<"Pontuacao: "<< getPontos() << endl;
        }

        // Jogador bate por baixo
        else if (anteriorJ.y >= anteriorI.y + inim.size.y && getVelY() < 0.f)
        {
            setPosicao(posXJogador, baseI);
            pararSubida();

            pIn->danificar(this);
        }

        // Colisao lateral
        else
        {
            float centroJ = posXJogador + jog.size.x / 2.f;
            float centroI = esqI + inim.size.x / 2.f;

            if (centroJ < centroI)
            {
                setPosicao(esqI - jog.size.x, topoJ);
            }
            else
            {
                setPosicao(dirI, topoJ);
            }

            pIn->danificar(this);
        }
    }
}

void Jogador::executar()
{
    mover();
    saiuDoChao();
}

void Jogador::salvar()
{
    ofstream arquivo("jogador.txt");

    if (arquivo.is_open())
    {
        arquivo << getPosicao().x << " "
                << getPosicao().y << endl;

        arquivo << num_vidas << endl;
        arquivo << pontos << endl;

        arquivo << velX << " " << velY << endl;
        arquivo << noChao << endl;

        arquivo.close();
    }
    else
    {
        cout << "Erro ao salvar jogador!" << endl;
    }
}

void Jogador::inicializa()
{
    velX = 0.5f;
    velY = 0.f;
    noChao = false;
    impulsoX = 0.f;
    invulneravel = false;
    pontos = 0;
}

void Jogador::saiuDoChao(){

    noChao = false;

}

void Jogador::mover()
{
    float gravidade = 0.01f;

    posicaoAnterior = getPosicao();

    if (invulneravel &&
        relogioDano.getElapsedTime().asSeconds() >= 0.5f)
    {
        invulneravel = false;
    }

    velY += gravidade;
    moverFigura(0.f, velY);

    // Durante os primeiros 0.2 segundos, aplica o knockback
    if (invulneravel &&
        relogioDano.getElapsedTime().asSeconds() < 0.2f)
    {
        moverFigura(impulsoX, 0.f);
    }
    else
    {
        if (teclaPressionada(sf::Keyboard::Key::A))
        {
            moverFigura(-velX, 0.f);
        }

        if (teclaPressionada(sf::Keyboard::Key::D))
        {
            moverFigura(velX, 0.f);
        }
    }

    // Limite esquerdo
    if (getPosicao().x < 0.f)
    {
        setPosicao(
            0.f, getPosicao().y);
    }

    // Limite direito
    if (getPosicao().x + getTamanho().x > 1000.f)
    {
        setPosicao(1000.f - getTamanho().x, getPosicao().y);
    }

    if (teclaPressionada(sf::Keyboard::Key::Space))
    {
        pular();
    }
}

void Jogador::pararQueda()
{
    velY = 0.f;
    noChao = true;
}

float Jogador::getVelY() const
{
    return velY;
}

void Jogador::pular()
{
    if(noChao)
    {
        if(velX == 0.25f)
            velY = -0.6f;
        else
            velY = -1.8f;

        noChao = false;
    }
}

sf::Vector2f Jogador::getPosicaoAnterior() const
{
    return posicaoAnterior;
}

void Jogador::pararSubida()
{
    velY = 0.f;
    noChao = false;
}

void Jogador::diminuirVelocidade()
{
    velX = 0.25f;
}

void Jogador::restaurarVelocidade()
{
    velX = 0.5f;
}

void Jogador::perderVida()
{
    operator--();
}

int Jogador::getVidas() const
{
    return num_vidas;
}

void Jogador::receberDanoContato(float direcao, int dano)
{
    if (!invulneravel)
    {
        for (int i = 0; i < dano; i++)
            perderVida();

        cout << "Vidas restantes: " << getVidas() << endl;

        impulsoX = 1.5f * direcao;
        velY = -0.9f;
        noChao = false;

        invulneravel = true;
        relogioDano.restart();
    }
}

void Jogador::impulsionar()
{
    velY = -1.0f;
    noChao = false;
}

void Jogador::adicionarPontos(int quantidade)
{
    operator+=(quantidade);
}

int Jogador::getPontos() const{
    return pontos;
}

void Jogador::prepararNovaFase()
{
    setPosicao(20.f, 695.f);
    posicaoAnterior = getPosicao();

    velX = 0.5f;
    velY = 0.f;
    impulsoX = 0.f;

    noChao = false;
    invulneravel = false;
}

void Jogador::pausar(bool pausa)
{
    if (pausa)
        relogioDano.stop();
    else
        relogioDano.start();
}

void Jogador::reiniciar()
{
    inicializa();
    prepararNovaFase();

    num_vidas = 3;

    relogioDano.restart();
}

bool Jogador::carregar()
{
    ifstream arquivo("jogador.txt");

    if (!arquivo.is_open())
    {
        cout << "Erro ao carregar jogador!" << endl;
        return false;
    }

    float posX, posY;
    int vidasSalvas, pontosSalvos;
    float velXSalva, velYSalva;
    bool noChaoSalvo;

    if (!(arquivo >> posX >> posY
                  >> vidasSalvas
                  >> pontosSalvos
                  >> velXSalva >> velYSalva
                  >> noChaoSalvo))
    {
        return false;
    }

    setPosicao(posX, posY);
    posicaoAnterior = getPosicao();

    num_vidas = vidasSalvas;
    pontos = pontosSalvos;

    velX = velXSalva;
    velY = velYSalva;

    noChao = noChaoSalvo;

    impulsoX = 0.f;
    invulneravel = false;

    relogioDano.restart();

    arquivo.close();

    return true;
}

void Jogador::operator--()
{
    if (num_vidas > 0)
        num_vidas--;
}

void Jogador::operator+=(int pontosGanhos)
{
    pontos += pontosGanhos;
}

