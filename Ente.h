#pragma once
#include<SFML/Graphics.hpp>

class Ente
{
protected:
    int id;
    //static Gerenciador_Grafico* pGG;
    //Figura* pFig; // não existe classe Figura no modelo UML do professor, provavelmente teremos que criar um.

public:
    Ente();
    virtual ~Ente();
    virtual void executar() = 0;
    void desenhar();
//    static void setGG(Gerenciador_Grafico* pG);
};
