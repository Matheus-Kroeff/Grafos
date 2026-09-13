/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

#include "TGrafo.h"


int main(){
    
    //---------------------------------------------//
    // Cria e aloca os vertices e arestas para um Grafo Dirigido
    TGrafo g(4);

    g.insereA(0,1);
    g.insereA(0,2);
    g.insereA(2,1);
    g.insereA(2,3);
    g.insereA(1,3);
    //---------------------------------------------//
    // Cria e aloca os vertices e arestas para um Grafo Não-Dirigido
    TGrafo_ND g2(6);
    
    g2.readfile("grafo_example.txt");

    g.show();
    g2.NDshow(); 

    return 0;
}
