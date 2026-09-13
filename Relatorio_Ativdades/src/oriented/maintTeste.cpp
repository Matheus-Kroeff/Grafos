/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

#include "TGrafo.h"

int main(){
    //  chama o construtor para criar um grafo 4x4
    TGrafo g(4);

    //insere as arestas do grafo
    //A={(0,1),(0,2),(2,1),(2,3),(1,3)}
    g.insereA(0,1);
    g.insereA(0,2);
    g.insereA(2,1);
    g.insereA(2,3);
    g.insereA(1,3);
    //---------------------------------------------//

    g.show();

    return 0;
}
