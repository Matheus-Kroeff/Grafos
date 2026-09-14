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

    std::cout << "Matrix deleted succesfully;

}

// Reader - File opener
void graph_utils::readfile(const char *arquivo){
    std::ifstream file(arquivo);

    if(!file.is_open()){
        std::cout << "ERROR - Unable to access file" << std::endl;
        return;
    }
    int graphType, num V;
    file >> graphType; // tipo de Grafo
    file >> num V; // número de veértices

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
void graph_utils::insertV(int pesoV){
    int new_n = 0;
    // Criar array novo size n + 1 ao add mais vertices
    int **new_adj = new int*[new_n];
    for(int r = 0; r < n; r++){
        new_adj[r] = new int[new_n];
        for(int t = 0; t < n; t++){
            new_adj[r][t] = adj[r][t];
        }
        new_adj[r][n] = 0; // novos vertices -> (0,4)(1,4)(r++,n)
        delete [] adj[r]; // liberar linha antiga 
    }
    new_adj[n] = new int[new_n];
    for(int u = 0; u < new_n; u++){
        new_adj[n][u] = 0;
    }

    delete [] adj;
    adj = new_adj;

    //Tratar pesos -> inserindo no novo array de pesos
    int *new_peso = new int[new_n];
    for(int k = 0; k < new_n; k++){
        new_peso[k] = peso[k];
    }
    new_peso[n] = pesoV; // pega proximo peso
    delete [] peso;
    peso = new_peso;

    n = new_n; // update quantidade 
}

// Remover vertice + encolhe matriz (atualiza ele) + diminuir peso + reindexar vertice:
void graph_utils::removeV(int v){
    if(v < 0 || v >= n) return;

    // Ja atualiza arestas + quant de vertices:
    m -= degree(v);
    int new_n = n - 1;

    // Criando matriz + vetor novos vazios (para tratar a remocao + atualizacao geral)
    int **new_adj = nullptr; // matriz
    int *new_p = nullptr; // peso

    if(new_n > 0){
        new_adj = new int*[new_n];
        new_p = new int[new_n];

        int new_linha = 0;  // linha da nova matriz
        for(int a = 0; a < n; a++){
            if(a == v)
                continue; // pulando linha do vertice removido
        

        // Aqui atualiza-se a matrix:
            new_adj[new_linha] = new int[new_n];
            int new_collumn = 0;
            for(int b = 0; b < n; b++){
                if(b == v)
                    continue;
                new_adj[new_linha][new_collumn] = adj[a][b]; //copia os valores antigos -> nova matrix
                new_collumn++; 
            }
            new_p[new_n] = peso[a];
            new_linha++;
        }

        for(int y = 0; y < n; y++){
            delete [] adj[y];
        }  
        // liberando arrays
        delete [] adj;
        delete [] peso;

        // update para estrutura nova + quant de vertices (n)
        adj = new_adj;
        peso = new_p;
        n = new_n;
    }

}


// Insertion Aresta Method:
void graph_utils::insertA(int v, int w){
    if(adj[v][w] == 0 && adj[w][v] == 0){
        adj[v][w] = 1;
        adj[w][v] = 1;
        m++;
    }
}

// Remocao Aresta:
void graph_utils::removeA(int v, int w){
    if(adj[v][w] == 1 && adj[w][v] == 1){
        adj[v][w] = 0;
        adj[w][v] = 0;
        m--;
    }
}

// Remocao Vertice:
void graph_utils::removeA(int v, int w){
    if(adj[v][w] == 1 && adj[w][v] == 1){
        adj[v][w] = 0;
        adj[w][v] = 0;
        m--;
    }
}
// 




