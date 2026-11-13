#pragma once
#include <SFML/Graphics.hpp>
#include "Entidades.h"

using namespace Entidades;

namespace Listas
{

template<class TL>
class Lista
{
    template<class TE>
    class Elemento
    {
    private:
        Elemento<TE>* pProx;
        TE* pinfo;

    public:
        Elemento();
        ~Elemento();

        void incluir(TE* p);
        void setProx(Elemento<TE>* pE);
        Elemento<TE>* getProximo() const;
        TE* getInfo() const;
    };

private:
    Elemento<TL>* pPrimeiro;
    Elemento<TL>* pUltimo;

public:
    Lista();
    ~Lista();

    void incluir(TL* p);
    void limpar();

    void remover(TL* p);
    void remover(int pos);
    void percorrer();
    void desenhar();
    void setWindow(sf::RenderWindow* janela);
};


// Implementacao da classe Elemento

template<class TL>
template<class TE>
Lista<TL>::Elemento<TE>::Elemento():
    pProx(nullptr), pinfo(nullptr)
{
}

template<class TL>
template<class TE>
Lista<TL>::Elemento<TE>::~Elemento()
{
}

template<class TL>
template<class TE>
void Lista<TL>::Elemento<TE>::incluir(TE* p)
{
    pinfo = p;
}

template<class TL>
template<class TE>
void Lista<TL>::Elemento<TE>::setProx(Elemento<TE>* pE)
{
    pProx = pE;
}

template<class TL>
template<class TE>
typename Lista<TL>::template Elemento<TE>*
Lista<TL>::Elemento<TE>::getProximo() const
{
    return pProx;
}

template<class TL>
template<class TE>
TE* Lista<TL>::Elemento<TE>::getInfo() const
{
    return pinfo;
}

// Implementacao da classe Lista

template<class TL>
Lista<TL>::Lista():
pPrimeiro(nullptr), pUltimo(nullptr)
{
}

template<class TL>
Lista<TL>::~Lista()
{
    limpar();
}

template<class TL>
void Lista<TL>::incluir(TL* p)
{
    if (p == nullptr)
        return;

    Elemento<TL>* novo = new Elemento<TL>;

    novo->incluir(p);

    if (pPrimeiro == nullptr)
    {
        pPrimeiro = novo;
    }
    else
    {
        pUltimo->setProx(novo);
    }

    pUltimo = novo;
}

template<class TL>
void Lista<TL>::limpar()
{
    Elemento<TL>* atual = pPrimeiro;

    while (atual != nullptr)
    {
        Elemento<TL>* proximo = atual->getProximo();

        delete atual->getInfo();
        delete atual;
        atual = proximo;
    }

    pPrimeiro = nullptr;
    pUltimo = nullptr;
}

template<class TL>
void Lista<TL>::remover(TL* p)
{
    Elemento<TL>* atual = pPrimeiro;
    Elemento<TL>* anterior = nullptr;

    while (atual != nullptr)
    {
        if (atual->getInfo() == p)
        {
            Elemento<TL>* proximo = atual->getProximo();

            if (anterior == nullptr)
                pPrimeiro = proximo;
            else
                anterior->setProx(proximo);

            if (atual == pUltimo)
                pUltimo = anterior;

            delete atual->getInfo();
            delete atual;
            return;
        }

        anterior = atual;
        atual = atual->getProximo();
    }
}

template<class TL>
void Lista<TL>::remover(int pos)
{
    if (pos < 0)
        return;

    Elemento<TL>* atual = pPrimeiro;
    Elemento<TL>* anterior = nullptr;

    int indice = 0;

    while (atual != nullptr && indice < pos)
    {
        anterior = atual;
        atual = atual->getProximo();
        indice++;
    }

    if (atual == nullptr)
        return;

    Elemento<TL>* proximo = atual->getProximo();

    if (anterior == nullptr)
        pPrimeiro = proximo;
    else
        anterior->setProx(proximo);

    if (atual == pUltimo)
        pUltimo = anterior;

    delete atual->getInfo();
    delete atual;
}

template<class TL>
void Lista<TL>::percorrer()
{
    Elemento<TL>* atual = pPrimeiro;

    while (atual != nullptr)
    {
        TL* entidade = atual->getInfo();

        if (entidade != nullptr)
            entidade->executar();

        atual = atual->getProximo();
    }
}

template<class TL>
void Lista<TL>::desenhar()
{
    Elemento<TL>* atual = pPrimeiro;

    while (atual != nullptr)
    {
        TL* entidade = atual->getInfo();

        if (entidade != nullptr)
            entidade->desenhar();

        atual = atual->getProximo();
    }
}

template<class TL>
void Lista<TL>::setWindow(sf::RenderWindow* janela)
{
    Elemento<TL>* atual = pPrimeiro;

    while (atual != nullptr)
    {
        TL* entidade = atual->getInfo();

        if (entidade != nullptr)
        {
            entidade->setWindow(janela);
        }

        atual = atual->getProximo();
    }
}



// Classe que gerencia a lista de entidades

class ListaEntidades
{
private:
    Lista<Entidade> LEs;

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidade* pE);
    void removerEntidade(Entidade* entidade);
    void removerEntidade(int pos);
    void percorrer();
    void desenhar();
    void setWindow(sf::RenderWindow* janela);
};

}

