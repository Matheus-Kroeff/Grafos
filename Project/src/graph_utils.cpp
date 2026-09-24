/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <cmath>
#include "graph_utils.h"

// Constructor:
graph_utils::graph_utils(int n){
    this -> n = n;
    this -> m = 0;

    // Alocação da Matriz n x n
    adj = new int*[n];
    for(int u = 0; u < n; u++) {
        adj[u] = new int[n];
    }

    // Preenchendo Matriz criada:
    for(int var1 = 0; var1 < n; var1++){
        for(int var2 = 0; var2 < n; var2++){
            adj[var1][var2] = 0;
        }
    }
    // Alocação dos vetores auxiliares
    peso = new int[n];
    rotulos = new std::string[n]; // Nome do Jogo

    for(int t = 0; t < n; t++){
        peso[t] = 0;
        rotulos[t] = "Jogo " + std::to_string(t);
    }
}

// Deleter
graph_utils::~graph_utils(){
    for(int v = 0; v < n; v++){
        delete [] adj[v];
    }

    delete [] adj;
    delete [] peso;
    delete [] rotulos;
    
    n = 0;
    m = 0;

    std::cout << "Matrix deleted succesfully\n";

}

// Reader - File opener
void graph_utils::readfile(const char *arquivo){
    std::ifstream file(arquivo);

    if(!file.is_open()){
        std::cout << "ERROR - Unable to access file" << arquivo << std::endl;
        return;
    }
    int graphType, numV;
    file >> graphType; // tipo de Grafo
    file >> numV; // número de veértices

    this->n = numV;
    this->m = 0;

// Leitura dos Vértices: ID, Rótulo ("Nome do Jogo") e Peso do Vértice
    for(int i = 0; i < n; i++) {
        int id, pV;
        std::string rotulo;
        file >> id;

        // Trata a leitura de nomes com espaços contidos entre aspas
        std::string aux;
        file >> aux;
        if (aux.front() == '"') {
            while (aux.back() != '"') {
                std::string temp;
                file >> temp;
                aux += " " + temp;
            }
            rotulo = aux.substr(1, aux.size() - 2); // Remove as aspas
        } else {
            rotulo = aux;
        }

        file >> pV;
        rotulos[id] = rotulo;
        peso[id] = pV;
    }

    int numA;
    file >> numA; // Leitura do número de Arestas

    // Leitura das Arestas: Origem, Destino e Peso 
    int u, v, pA;
    for(int a = 0; a < numA; a++) {
        file >> u >> v >> pA;
        insertA(u, v, pA); // Passa o peso da aresta para a matriz
    }

    file.close();
    std::cout << "Arquivo lido com sucesso!\n";

}

// Insertion Vertice Method + Peso:
void graph_utils::insertV(int pesoV, std::string nomeJogo) {
    int new_n = n + 1; // O novo tamanho tem de ser n + 1
    
    // Alocar nova matriz
    int **new_adj = new int*[new_n];
    for(int r = 0; r < new_n; r++) {
        new_adj[r] = new int[new_n];
        for(int c = 0; c < new_n; c++) {
            new_adj[r][c] = 0;
        }
    }

    // Copiar valores antigos
    for(int r = 0; r < n; r++) {
        for(int t = 0; t < n; t++) {
            new_adj[r][t] = adj[r][t];
        }
        delete [] adj[r];
    }
    delete [] adj;
    adj = new_adj;

    // Tratar vetores de pesos e rótulos
    int *new_peso = new int[new_n];
    std::string *new_rotulos = new std::string[new_n];

    for(int k = 0; k < n; k++) {
        new_peso[k] = peso[k];
        new_rotulos[k] = rotulos[k];
    }
    new_peso[n] = pesoV;
    new_rotulos[n] = nomeJogo.empty() ? ("Jogo " + std::to_string(n)) : nomeJogo;

    delete [] peso;
    delete [] rotulos;

    peso = new_peso;
    rotulos = new_rotulos;

    n = new_n; // Atualiza a quantidade total de vértices
}

// Remover vertice + encolhe matriz (atualiza ele) + diminuir peso + reindexar vertice:
void graph_utils::removeV(int v) {
    if(v < 0 || v >= n) return;

    int new_n = n - 1;
    if(new_n <= 0) return;

    int **new_adj = new int*[new_n];
    int *new_p = new int[new_n];
    std::string *new_r = new std::string[new_n];

    int new_linha = 0;
    for(int a = 0; a < n; a++) {
        if(a == v) continue; // Pula o vértice removido

        new_adj[new_linha] = new int[new_n];
        int new_column = 0;
        for(int b = 0; b < n; b++) {
            if(b == v) continue;
            new_adj[new_linha][new_column] = adj[a][b];
            new_column++;
        }
        new_p[new_linha] = peso[a];
        new_r[new_linha] = rotulos[a];
        new_linha++;
    }

    // Liberta a memória antiga
    for(int y = 0; y < n; y++) {
        delete [] adj[y];
    }
    delete [] adj;
    delete [] peso;
    delete [] rotulos;

    // Atualiza com os novos vetores
    adj = new_adj;
    peso = new_p;
    rotulos = new_r;
    n = new_n;
}


// Insertion Aresta Method:
void graph_utils::insertA(int v, int w, int pAresta) {
    if(v >= 0 && v < n && w >= 0 && w < n) {
        if(adj[v][w] == 0) m++;
        adj[v][w] = pAresta; // Grava o peso diretamente
    }
}

// Remocao Aresta:
void graph_utils::removeA(int v, int w) {
    if(v >= 0 && v < n && w >= 0 && w < n) {
        if(adj[v][w] != 0) {
            adj[v][w] = 0;
            m--;
        }
    }
}

// Gravar dados no arquivo grafo.txt
void graph_utils::writefile(const char *arquivo) {
    
}

// Mostrar conteúdo do arquivo
void graph_utils::showFileContent() {
    
}

// Mostrar grafo (Matriz de Adjacência)
void graph_utils::printGraph() {

}

// Apresentar conexidade
void graph_utils::showConnectivity() { 

}

