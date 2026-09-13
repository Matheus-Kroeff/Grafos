/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

/*
Implementa��o de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjac�ncia
e m�todos para utiliza��o de um grafo dirigido.
*/
#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___

// defini��o de uma estrutura para armezanar um grafo
// Tamb�m seria poss�vel criar um arquivo grafo.h 
// e fazer a inclus�o "#include <grafo.h>"
class TGrafo{
	private:
		int n; // quantidade de v�rtices
		int m; // quantidade de arestas
		int **adj; //matriz de adjac�ncia
	public:
		TGrafo( int n);
		void insereA(int v, int w);
		void removeA(int v, int w);
		void show();
		int inDegree(int v);
		int outDegree(int v);
		int degree(int v);
		bool Fonte_check(int v);
		bool Sorvedouro(int v);
		int isSymetric();
		void isfloat(int v);
		~TGrafo();		
};	

#endif

