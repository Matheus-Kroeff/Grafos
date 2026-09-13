/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

#include "graph_utils.h"

// Ainda NAO mexi no MAIN

int main(){
    //  chama o construtor para criar um grafo 4x4
    graph_utils g(6);


    //---------------------------------------------//

    g.readfile("grafo_example.txt");

    g.show(); 


    return 0;
}
