#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace Gerenciadores { class Gerenciador_Grafico; }

class Ente
{
protected:
    float x;
    float y;
    int id;
    static int contador;
    sf::RectangleShape body;
    sf::Texture textura;
    static Gerenciadores::Gerenciador_Grafico* pGG;

public:
    Ente(float x = 0.f, float y = 0.f);
    virtual ~Ente();
    virtual void executar() = 0;
    void desenhar();
    static void setGG(Gerenciadores::Gerenciador_Grafico* pG);
    const sf::RectangleShape& getBody() const;
    int getId() const;
    void setPosicao(float x, float y);

    // Metodos de acesso grafico: implementacao delegada ao Gerenciador_Grafico.
    sf::Vector2f getPosicao() const;
    sf::Vector2f getTamanho() const;
    sf::FloatRect getLimites() const;
    void moverFigura(float x, float y);
    void definirFigura(float x, float y, float largura, float altura, sf::Color cor);
    void definirTamanho(float largura, float altura);
    void definirCor(sf::Color cor);
    bool teclaPressionada(sf::Keyboard::Key tecla) const;
    bool carregarTextura(const std::string& caminho);
};
