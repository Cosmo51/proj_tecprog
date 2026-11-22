#pragma once

#include <map>
#include <string>
#include <utility>
class Ranking
{
private:
    std::multimap<int, std::string> pontuacoes;

public:
    Ranking();
    ~Ranking();

    void adicionarPontuacao(int pontos, const std::string& nome);

    void salvar() const;
    void carregar();

    const std::multimap<int, std::string>& getPontuacoes() const;
};
