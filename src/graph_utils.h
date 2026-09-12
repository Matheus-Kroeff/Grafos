/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/
#include <string>
#include <vector>

#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___


class graph_utils{
	private:
		int n; // quantidade de vertices
		int m; // quantidade de arestas
		int **adj; //matriz de adjacencia
		int *peso;
	public:
		// Construct
		graph_utils( int n);

		// File Methods
		void readfile(const char*arquivo);
		void writefile(const char* arquivo);
		void show_file(const char* arquivo);

		// Methods general:
		void insertA(int v, int w);
		void insertV(int pv);
		void removeA(int v, int w);
		void removeV(int v);
		void setPeso(int v, int p);
		int getpeso(int p);
		
		void show();
		int degree(int v);
		void conex();
		int getN();
		~graph_utils();		
};	

#endif

