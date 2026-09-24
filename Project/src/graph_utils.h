/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <string>

class graph_utils {
private:
    int n;                 // Número de vértices
    int m;                 // Número de arestas
    int **adj;             // Matriz de adjacência
    int *peso;             // Vetor de pesos dos vértices
    std::string *rotulos;  // Vetor com os nomes dos jogos

public:
    graph_utils(int n);
    ~graph_utils();

    // Opção a: Ler dados do arquivo
    void readfile(const char *arquivo);

    // Opção b: Gravar dados no arquivo
    void writefile(const char *arquivo);

    // Opção c: Inserir vértice
    void insertV(int pesoV, std::string nomeJogo = "");

    // Opção d: Inserir aresta
    void insertA(int v, int w, int pAresta = 1);

    // Opção e: Remover vértice
    void removeV(int v);

    // Opção f: Remover aresta
    void removeA(int v, int w);

    // Opção g: Mostrar conteúdo do arquivo
    void showFileContent();

    // Opção h: Mostrar grafo
    void printGraph();

    // Opção i: Apresentar conexidade
    void showConnectivity();

    // Funcionalidade Principal do Projeto
    void recomendar(int v);

    // Getters auxiliares
    int getNumV() const { return n; }
    int getNumA() const { return m; }
};

#endif