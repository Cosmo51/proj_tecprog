#include "Ranking.h"
#include <fstream>

Ranking::Ranking()
{
    carregar();
}

Ranking::~Ranking(){

}

void Ranking::adicionarPontuacao(int pontos, const std::string& nome){
    pontuacoes.insert(std::make_pair(pontos, nome));
}

void Ranking::salvar()const{

    std::ofstream arquivo("ranking.txt");

    if(!arquivo.is_open())
       return;

    for(std::multimap<int, std::string>::const_reverse_iterator it =
        pontuacoes.rbegin(); it != pontuacoes.rend(); it++)
    {
        arquivo << it->first << "|" << it->second << std::endl;
    }

    arquivo.close();
}

void Ranking::carregar(){
    std::ifstream arquivo("ranking.txt");

    if (!arquivo.is_open())
        return;

    pontuacoes.clear();

    int pontos;
    std::string nome;

    while(arquivo >> pontos)
    {

        if(arquivo.peek()== '|'){
            arquivo.get();
            std::getline(arquivo, nome);

            pontuacoes.insert(std::make_pair(pontos, nome));
        }
    }
    arquivo.close();
}

const std::multimap<int, std::string>& Ranking::getPontuacoes() const
{
    return pontuacoes;
}

