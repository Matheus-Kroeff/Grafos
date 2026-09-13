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

// Destructor, respons�vel por
// liberar a mem�ria alocada para a matriz
TGrafo::~TGrafo(){
	n = 0;
	m = 0;
	delete [] *adj;
	std::cout << "espa�o liberado";
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
    int outgrau = 0;
    for(int t = 0; t < n; t++){
        if(adj[v][t] == 1)  
            outgrau++;
    }

    int ingrau = 0;
    for(int t = 0; t < n; t++){
        if(adj[t][v] == 1)  
            ingrau++;
    }
    // Faz a verificacao por fonte:
    if (outgrau > 0 && ingrau == 0)
        return 1;
    else
        return 0;

}

// ⚠️EXERCICIO 5 - RELATORIO
bool TGrafo::Sorvedouro(int v){
    int outgrau = 0;
    for(int t = 0; t < n; t++){
        if(adj[v][t] == 1)  
            outgrau++;
    }

    int ingrau = 0;
    for(int t = 0; t < n; t++){
        if(adj[t][v] == 1)  
            ingrau++;
    }
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

// Apresenta o Grafo contendo
// n�mero de v�rtices, arestas
// e a matriz de adjac�ncia obtida
void TGrafo::show(){
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for( int i=0; i < n; i++){
        std::cout << "\n";
        for( int w=0; w < n; w++)
            if(adj[i][w] == 1)
                std::cout << "Adj[" << i<< "," << w << "]= 1" << " ";
            else std::cout << "Adj[" << i<< "," << w << "]= 0" << " ";
    }

    std::cout << "\n";
    // Funções sobre Grau:
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
    
    std::cout << "\nfim da impressao do grafo." << std::endl;
}


