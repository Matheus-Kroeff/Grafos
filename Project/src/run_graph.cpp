/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

#include <iostream>
#include <string>
#include "graph_utils.h"

int main() {
    graph_utils grafo(0);
    int opcao = 0;
    std::string arquivo = "grafos.txt";

    std::cout << "===========================================================\n";
    std::cout << "   SYSTEM RECOMMEND-A-GAME (TEORIA DOS GRAFOS)             \n";
    std::cout << "===========================================================\n";

    do {
        std::cout << "\n-----------------------------------------------------------\n";
        std::cout << "MENU DE OPCOES:\n";
        std::cout << "1.  a) Ler dados do arquivo grafos.txt\n";
        std::cout << "2.  b) Gravar dados no arquivo grafos.txt\n";
        std::cout << "3.  c) Inserir vertice (Novo Jogo)\n";
        std::cout << "4.  d) Inserir aresta (Nova Similaridade)\n";
        std::cout << "5.  e) Remover vertice\n";
        std::cout << "6.  f) Remover aresta\n";
        std::cout << "7.  g) Mostrar conteudo do arquivo\n";
        std::cout << "8.  h) Mostrar grafo (Matriz de Adjacencia)\n";
        std::cout << "9.  i) Apresentar a conexidade do grafo e o reduzido\n";
        std::cout << "10. FUNCIONALIDADE: Recomendador de Jogos\n";
        std::cout << "11. j) Encerrar a aplicacao\n";
        std::cout << "-----------------------------------------------------------\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: // a) Ler dados do arquivo
                grafo.readfile(arquivo.c_str());
                break;

            case 2: // b) Gravar dados no arquivo
                std::cout << "Opcao b: Gravando dados atualizados no arquivo " << arquivo << "...\n";
                grafo.writefile(arquivo.c_str());
                break;

            case 3: { // c) Inserir vértice (Sem pedir peso do vértice, pois o Tipo 6 tem peso só na aresta)
                std::string nome;
                std::cout << "Digite o nome do novo jogo: ";
                std::cin.ignore();
                std::getline(std::cin, nome);
                grafo.insertV(0, nome); // Peso 0 para o vértice
                std::cout << "Jogo '" << nome << "' inserido no grafo!\n";
                break;
            }

            case 4: { // d) Inserir aresta
                int u, v, pA;
                std::cout << "ID Origem: "; std::cin >> u;
                std::cout << "ID Destino: "; std::cin >> v;
                std::cout << "Peso da Similaridade (1 a 100): "; std::cin >> pA;
                grafo.insertA(u, v, pA);
                std::cout << "Conexao de similaridade inserida entre " << u << " e " << v << "!\n";
                break;
            }

            case 5: { // e) Remover vértice
                int id;
                std::cout << "Digite o ID do vertice/jogo a remover: ";
                std::cin >> id;
                grafo.removeV(id);
                break;
            }

            case 6: { // f) Remover aresta
                int u, v;
                std::cout << "ID Origem: "; std::cin >> u;
                std::cout << "ID Destino: "; std::cin >> v;
                grafo.removeA(u, v);
                std::cout << "Aresta entre " << u << " e " << v << " removida.\n";
                break;
            }

            case 7: // g) Mostrar conteúdo do arquivo
                std::cout << "\n=== CONTEUDO DO GRAFO ===\n";
                std::cout << "Total de Vertices (n): " << grafo.getNumV() << "\n";
                break;

            case 8: // h) Mostrar grafo
                std::cout << "\n=== EXIBICAO DO GRAFO (MATRIZ) ===\n";
                grafo.printGraph();
                break;

            case 9: // i) Conexidade
                std::cout << "\n=== CONEXIDADE DO GRAFO ===\n";
                std::cout << "Grafo Orientado (Tipo 6). Verificando componentes fortemente conexas (FCONEX)...\n";
                break;

            case 10: { // Funcionalidade Principal de Recomendação
                int id;
                std::cout << "Digite o ID do jogo escolhido (0 a " << grafo.getNumV() - 1 << "): ";
                std::cin >> id;
                grafo.recomendar(id);
                break;
            }

            case 11: // j) Encerrar
                std::cout << "Encerrando a aplicacao...\n";
                break;

            default:
                std::cout << "Opcao invalida! Tente novamente.\n";
        }
    } while (opcao != 11);

    return 0;
}
