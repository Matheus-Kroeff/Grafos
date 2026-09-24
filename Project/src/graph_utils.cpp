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
graph_utils::graph_utils(int n) {
    this->n = n;
    this->m = 0;

    if (n > 0) {
        adj = new int*[n];
        for (int u = 0; u < n; u++) {
            adj[u] = new int[n];
            for (int v = 0; v < n; v++) {
                adj[u][v] = 0;
            }
        }

        peso = new int[n];
        rotulos = new std::string[n];

        for (int t = 0; t < n; t++) {
            peso[t] = 0;
            rotulos[t] = "Jogo " + std::to_string(t);
        }
    } else {
        adj = nullptr;
        peso = nullptr;
        rotulos = nullptr;
    }
}

// Deleter
graph_utils::~graph_utils() {
    if (adj != nullptr) {
        for (int v = 0; v < n; v++) {
            delete [] adj[v];
        }
        delete [] adj;
    }

    if (peso != nullptr) delete [] peso;
    if (rotulos != nullptr) delete [] rotulos;

    n = 0;
    m = 0;

    std::cout << "Matrix deleted successfully\n";
}

// Reader - File opener
void graph_utils::readfile(const char *arquivo) {
    std::ifstream file(arquivo);

    if (!file.is_open()) {
        std::cout << "ERROR - Unable to access file " << arquivo << std::endl;
        return;
    }

    // Libera a memória antiga existente (caso o grafo já tivesse dados)
    if (n > 0 && adj != nullptr) {
        for (int v = 0; v < n; v++) {
            delete [] adj[v];
        }
        delete [] adj;
        delete [] peso;
        delete [] rotulos;
    }

    int graphType, numV;
    file >> graphType; // Tipo do Grafo
    file >> numV;      // Número de vértices lido do arquivo

    // Atualiza os limites e aloca a memória necessária para os dados lidos
    this->n = numV;
    this->m = 0;

    adj = new int*[n];
    for (int u = 0; u < n; u++) {
        adj[u] = new int[n];
        for (int v = 0; v < n; v++) {
            adj[u][v] = 0; // Inicializa a matriz zerada
        }
    }

    peso = new int[n];
    rotulos = new std::string[n];

    // Leitura dos Vértices: ID, Rótulo ("Nome do Jogo") e Peso do Vértice
    for (int i = 0; i < n; i++) {
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
        if (id >= 0 && id < n) {
            rotulos[id] = rotulo;
            peso[id] = pV;
        }
    }

    int numA;
    file >> numA; // Leitura do número de Arestas

    // 4. Leitura das Arestas: Origem, Destino e Peso
    int u, v, pA;
    for (int a = 0; a < numA; a++) {
        file >> u >> v >> pA;
        insertA(u, v, pA); // Grava o peso da aresta na matriz
    }

    file.close();
    std::cout << "Arquivo lido com sucesso! Vértices carregados: " << n << "\n";
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
    if (n == 0 || adj == nullptr) {
        std::cout << "Grafo vazio na memoria. Nada para salvar.\n";
        return;
    }

    std::ofstream file(arquivo);
    if (!file.is_open()) {
        std::cout << "ERRO: Nao foi possivel abrir o arquivo para gravacao.\n";
        return;
    }

    // Tipo do grafo (6 - Orientado com peso na aresta)
    file << "6\n";
    file << n << "\n";

    // Escreve os vértices: ID "Nome" Peso
    for (int i = 0; i < n; i++) {
        file << i << " \"" << rotulos[i] << "\" " << peso[i] << "\n";
    }

    // Escreve o número de arestas e as conexões
    file << m << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] > 0) {
                file << i << " " << j << " " << adj[i][j] << "\n";
            }
        }
    }

    file.close();
    std::cout << "Dados salvos com sucesso no arquivo " << arquivo << "!\n";
}

// Mostrar conteúdo do arquivo
void graph_utils::showFileContent() {
    if (n == 0) {
        std::cout << "O grafo esta vazio! Leia o arquivo primeiro (Opcao 1).\n";
        return;
    }

    std::cout << "\n=======================================================\n";
    std::cout << "              INFORMACOES DO GRAFO ATUAL               \n";
    std::cout << "=======================================================\n";
    std::cout << " Tipo do Grafo : 6 (Orientado com Peso nas Arestas)\n";
    std::cout << " Total Vertices: " << n << "\n";
    std::cout << " Total Arestas : " << m << "\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << " LISTA DE JOGOS (VERTICES):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "   [ID " << i << "] " << rotulos[i] << "\n";
    }
    std::cout << "-------------------------------------------------------\n";
    std::cout << " CONEXOES DE SIMILARIDADE (ARESTAS):\n";
    bool temAresta = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] > 0) {
                std::cout << "   " << rotulos[i] << " ---> " << rotulos[j] 
                          << " (Similaridade: " << adj[i][j] << "%)\n";
                temAresta = true;
            }
        }
    }
    if (!temAresta) {
        std::cout << "   Nenhuma aresta/conexao cadastrada.\n";
    }
    std::cout << "=======================================================\n";
}

// Mostrar grafo (Matriz de Adjacência)
void graph_utils::printGraph() {
    if (n == 0 || adj == nullptr) {
        std::cout << "O grafo esta vazio! Leia o arquivo primeiro (Opcao 1).\n";
        return;
    }

    std::cout << "\n=======================================================\n";
    std::cout << "            MATRIZ DE ADJACENCIA DO GRAFO              \n";
    std::cout << "=======================================================\n\n";

    // Imprime os IDs das colunas no topo
    std::cout << "      ";
    for (int j = 0; j < n; j++) {
        std::cout << "[" << j << "]\t";
    }
    std::cout << "\n";

    // Imprime as linhas da matriz
    for (int i = 0; i < n; i++) {
        std::cout << "[" << i << "]\t";
        for (int j = 0; j < n; j++) {
            std::cout << adj[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n=======================================================\n";
}

// Apresentar conexidade
void graph_utils::showConnectivity() { 

}

// Recomendador de Jogos
void graph_utils::recomendar(int v) {
    if (v < 0 || v >= n) {
        std::cout << "ID de jogo invalido!\n";
        return;
    }

    std::cout << "\n=======================================================\n";
    std::cout << " RECOMENDACOES PARA: " << rotulos[v] << "\n";
    std::cout << "=======================================================\n";

    bool encontrou = false;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] > 0) {
            std::cout << " -> " << rotulos[i] << " | Similaridade: " << adj[v][i] << "%\n";
            encontrou = true;
        }
    }

    if (!encontrou) {
        std::cout << " Nenhuma conexao de similaridade encontrada para este jogo.\n";
    }
}