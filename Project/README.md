# LYNKIE - Recomendador de jogos

Projeto em C++ que usa um grafo para recomendar jogos pela similaridade entre eles.

## Como rodar com make

Você precisa de `g++` e `make` instalados.

```bash
make
cd src
../run_graph.out
```

Para remover o executável, execute na pasta `Project/`:

```bash
make clean
```

O comando `make run` também compila e executa.

## Como rodar sem make

Abra o terminal e execute:

```bash
g++ -std=c++17 -Wall -Wextra src/*.cpp -o run_graph.out
./run_graph.out
```

## Como usar

No menu, digite os números das opções. Primeiro escolha `1` para carregar `grafos.txt`. Escolha `7` para ver os jogos e seus IDs, `10` para pedir uma recomendação e `11` para sair.

Com Python 3 instalado, execute:

```bash
python3 gerar_grafo.py
```

Isso recria `grafos.txt` usando `games.json`. Não é necessário para rodar o programa com os dados já existentes.

## O que cada arquivo faz

```text
Project/
├── README.md           - Explica o projeto e como rodar.
├── makefile            - Compila com make e remove o executável com make clean.
├── .gitignore          - Evita enviar arquivos .out ao Git.
├── run_graph.out       - Executável gerado pela compilação.
└── src/
    ├── run_graph.cpp   - Mostra o menu e recebe as escolhas do usuário.
    ├── graph_utils.h   - Declara a classe do grafo e suas funções.
    ├── graph_utils.cpp - Implementa o grafo, os arquivos, a conexidade e as recomendações.
    ├── grafos.txt      - Guarda os jogos e suas conexões de similaridade.
    ├── games.json      - Contém os dados dos jogos usados pelo script Python.
    └── gerar_grafo.py  - Gera grafos.txt usando as tags e os gêneros de games.json.
```
