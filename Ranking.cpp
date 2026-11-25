#include "Ranking.h"
#include <fstream>

using namespace std;

Ranking::Ranking()
{
    carregar();
}

Ranking::~Ranking(){

}

void Ranking::adicionarPontuacao(int pontos, const string& nome){
    pontuacoes.insert(make_pair(pontos, nome));
}

void Ranking::salvar() const
{
    ofstream arquivo("ranking.txt");

    if (arquivo.is_open())
    {
        for (multimap<int, string>::const_reverse_iterator it = pontuacoes.rbegin();
             it != pontuacoes.rend(); it++)
        {
            arquivo << it->first << "|" << it->second << endl;
        }
        arquivo.close();
    }
}

void Ranking::carregar()
{
    ifstream arquivo("ranking.txt");

    if (arquivo.is_open())
    {
        pontuacoes.clear();
        int pontos;
        string nome;

        while (arquivo >> pontos)
        {
            if (arquivo.peek() == '|')
            {
                arquivo.get();
                getline(arquivo, nome);
                pontuacoes.insert(make_pair(pontos, nome));
            }
        }
        arquivo.close();
    }
}

const multimap<int, string>& Ranking::getPontuacoes() const
{
    return pontuacoes;
}

