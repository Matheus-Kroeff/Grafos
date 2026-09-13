#include <iostream>
#include "TGrafo.h"
#include <fstream>
#include <limits.h>
#include <locale.h>

/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

// Construtor do TGrafo
TGrafo::TGrafo( int n ){
    this->n = n;
    // No in�cio dos tempos n�o h� arestas
    this->m = 0; 
    // aloca da matriz do TGrafo
    int **adjac = new int*[n];
    for(int i = 0; i < n; i++)
    	adjac[i]= new int[n];
    adj = adjac;
    // Inicia a matriz com zeros
	for(int i = 0; i< n; i++)
		for(int j = 0; j< n; j++)
			adj[i][j]=0;	
}

// Destructor, responsavel por
// liberar a memoria alocada para a matriz
TGrafo::~TGrafo(){
    for(int del = 0; del < n; del++){
        delete [] adj[del];
    }
    delete [] adj;
	n = 0;
	m = 0;
	
	std::cout << "espaco liberado" << std::endl;
}

// Insere uma aresta no Grafo tal que
// v � adjacente a w
void TGrafo::insereA(int v, int w){
    // testa se nao temos a aresta
    if(adj[v][w] == 0 ){
        adj[v][w] = 1;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w){
    // testa se temos a aresta
    if(adj[v][w] == 1 ){
        adj[v][w] = 0;
        m--; // atualiza qtd arestas
    }
}

// ⚠️EXERCICIO 1 - RELATORIO
int TGrafo::inDegree(int v){
    int ingrau = 0;
    for(int t = 0; t < n; t++){
        // verifica se "chega" 
        // um 't' que chega em 'v' (alvo):
        // (0,0), (1,0)...
        if(adj[t][v] == 1)  
            ingrau++;
    }
    return ingrau;
}

// ⚠️EXERCICIO 2 - RELATORIO
int TGrafo::outDegree(int v){
    int outgrau = 0;
    for(int t = 0; t < n; t++){
        // verifica se "sai" 
        // de 'v' e chega em 't' (alvo):
        // (0,0), (0,1), (0,2)...
        if(adj[v][t] == 1)  
            outgrau++;
    }
    return outgrau;
}

// ⚠️EXERCICIO 3 - RELATORIO
int TGrafo::degree(int v){
    int grau_total = 0;
    for(int t = 0; t < n; t++){
        if(adj[v][t] == 1)  
            grau_total++;

        if(adj[t][v] == 1)
            grau_total++;
    }
    return grau_total;
}

// ⚠️EXERCICIO 4 - RELATORIO
bool TGrafo::Fonte_check(int v){
    // Calcula os ingrau e outgrau de novo
    int outgrau = outDegree(v);
    int ingrau = inDegree(v);
    
    // Faz a verificacao por fonte:
    if (outgrau > 0 && ingrau == 0)
        return 1;
    else
        return 0;

}

// ⚠️EXERCICIO 5 - RELATORIO
bool TGrafo::Sorvedouro(int v){
    int outgrau = outDegree(v);
    int ingrau = inDegree(v);
    // Faz a verificacao por sorvedouro:
    if (outgrau == 0 && ingrau > 0)
        return 1;
    else
        return 0;
}

// ⚠️EXERCICIO 6 - RELATORIO
int TGrafo::isSymetric(){
    for(int a = 0; a < n; a++){
        for(int b = 0; b < n; b++){
            // Checando se todo o grafo é simétrico:
            if(adj[a][b] != adj[b][a])
                return 0;
        }
    }
    return 1;
}

// ===========================================================
// TGrafo_ND: grafo nao dirigido
// ===========================================================
 
// Construtor do TGrafo Non-Directed
TGrafo_ND::TGrafo_ND(int n){
    this->n = n;
    this->m = 0;
    int **adjac = new int*[n];
    for(int i = 0; i < n; i++)
        adjac[i] = new int[n];
    adj = adjac;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            adj[i][j] = 0;
        }
    }
}
 
// Destructor, responsavel por
// liberar a memoria alocada para a matriz
TGrafo_ND::~TGrafo_ND(){
    // mesma correcao aplicada ao TGrafo: antes tinha um
    // "delete [] *adj;" extra depois deste laco (double free)
    for(int i = 0; i < n; i++)
        delete [] adj[i];
    delete [] adj;
 
    n = 0;
    m = 0;
    std::cout << "espaco liberado (grafo nao-direcionado)" << std::endl;
}
 
// EXERCICIO 7 - RELATORIO
void TGrafo_ND::readfile(const char* grafo_example){
    std::ifstream file(grafo_example);
    if(!file.is_open()){
        std::cout << "ERROR - Unable to access file" << std::endl;
        return;
    }
    int V;
    int A;
    file >> V;
    file >> A;
 
    int a1, a2;
    for(int y = 0; y < A; y++){
        file >> a1 >> a2;
        NDinsereA(a1, a2);
    }
    file.close();
}
 
// ⚠️EXERCICIO 8 - RELATORIO
 
// Insere uma aresta no Grafo tal que v e adjacente a w (nos dois sentidos)
void TGrafo_ND::NDinsereA(int v, int w){
    if(adj[v][w] == 0 && adj[w][v] == 0){
        adj[v][w] = 1;
        adj[w][v] = 1;
        m++;
    }
}
 

void TGrafo_ND::NDremoveA(int v, int w){
    if(adj[v][w] == 1 && adj[w][v] == 1){
        adj[v][w] = 0;
        adj[w][v] = 0;
        m--;
    }
}
 
// ⚠️EXERCICIO 9 - RELATORIO
int TGrafo_ND::degree(int v){
    // Em grafo nao direcionado, o grau e praticamente o
    // numero de vizinhos conectados em v
    int grau_nd = 0;
    for(int b = 0; b < n; b++){
        if(adj[v][b] == 1){
            grau_nd++;
        }
    }
    return grau_nd;
}
 
void TGrafo_ND::NDshow(){
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    std::cout << "\n--GRAFO Nao Direcionado--\n";
    for(int i = 0; i < n; i++){
        std::cout << "\n";
        for(int w = 0; w < n; w++)
            if(adj[i][w] == 1)
                std::cout << "Adj[" << i << "," << w << "]= 1" << " ";
            else
                std::cout << "Adj[" << i << "," << w << "]= 0" << " ";
    }
    std::cout << "\n";
    std::cout << "RESPOSTA 9)\n";
    for(int index = 0; index < n; index++){
        std::cout << "Grau do vertice " << index << ": " << degree(index) << std::endl;
    }
 
    std::cout << "\nfim da impressao do grafo nao dirigido." << std::endl;
}

void TGrafo::show(){
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    std::cout << "\n--GRAFO Direcionado--\n";
    for( int i = 0; i < n; i++){
        std::cout << "\n";
        for( int w=0; w < n; w++)
            if(adj[i][w] == 1)
                std::cout << "Adj[" << i<< "," << w << "]= 1" << " ";
            else std::cout << "Adj[" << i<< "," << w << "]= 0" << " ";
    }

    std::cout << "\n";
    // Resposta 1)
    std::cout << "\nRESPOSTA 1)\n";
    for(int index = 0; index < n; index++){
        
        std::cout << "Grau de Entrada do vertice " << index << ": "<< inDegree(index) << std::endl; 
    }
    
    // Resposta 2)
    std::cout << "\nRESPOSTA 2)\n";
     for(int index = 0; index < n; index++){
        std::cout << "Grau de Saida do vertice " << index << ": "<< outDegree(index) << std::endl; 
    }
    
    // Resposta 3)
    std::cout << "\nRESPOSTA 3)\n";
    for(int v = 0; v < n; v++){
        std::cout << "Grau total do vertice " << v << ": " << degree(v) << std::endl;
    }
    //-----------------------------------------------------------------------------------//
    // Função Checa Fonte e Sorvedouro:
    // Resposta 4) && 5)
    std::cout << "\nRESPOSTA 4 e 5)\n";
    for(int v = 0; v < n; v++){
        std::cout << "Vertice " << v << " -> Fonte: " << Fonte_check(v) << "|| Sorvedouro: " << Sorvedouro(v) << std::endl;
    }
    // Função Checa Simétrico:
    // Resposta 6)
    std::cout << "\nRESPOSTA 6)\n";
    if(isSymetric())
        std::cout << "Retorno de checagem de simetria -> Return: " << isSymetric() <<std::endl; 
    else    
        std::cout << "Retorno de checagem de simetria -> Return: " << isSymetric() <<std::endl; 
    // Resposta 10)
    std::cout << "\nRESPOSTA 10)";
    // Resposta 11)
    std::cout << "\nRESPOSTA 11)";
    // Resposta 12)
    std::cout << "\nRESPOSTA 12)";
    // Resposta 13)
    
    std::cout << "\nfim da impressao dos grafos." << std::endl;
}


