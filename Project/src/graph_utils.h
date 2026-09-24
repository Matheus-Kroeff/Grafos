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

    void readfile(const char *arquivo);
    void writefile(const char *arquivo);
    void insertV(int pesoV, std::string nomeJogo = "");
    void removeV(int v);
    void insertA(int v, int w, int pAresta = 1);
    void removeA(int v, int w);
    
    // Métodos de exibição e análise do menu
    void showFileContent();
    void printGraph();       // Sem o 'const' no final para bater com o .cpp
    void showConnectivity();
    
    // Recomendador de jogos
    void recomendar(int v);

    // Getters auxiliares
    int getNumV() const { return n; }
};

#endif