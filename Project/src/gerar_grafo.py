import pandas as pd

def gerar_grafo_steam(csv_path="steam_games.csv", output_path="grafos.txt", max_jogos=85, min_similaridade=20):
    print("A carregar o ficheiro CSV da Steam...")
    
    # 1. Leitura do dataset
    try:
        df = pd.read_csv(csv_path)
    except FileNotFoundError:
        print(f"ERRO: Ficheiro '{csv_path}' nao encontrado na pasta!")
        return

    # Trata colunas nulas e seleciona apenas os primeiros 'max_jogos'
    df = df.dropna(subset=['Name', 'Genres']) if 'Genres' in df.columns else df.dropna(subset=['Name'])
    df = df.head(max_jogos).reset_index(drop=True)

    num_vertices = len(df)
    vertices = []
    
    # 2. Mapeamento dos Vértices (ID, Rótulo/Nome, Peso do Vértice)
    for idx, row in df.iterrows():
        nome_jogo = str(row['Name']).replace('"', '') # Remove aspas internas para nao quebrar o C++
        # Trata generos/tags como um conjunto de palavras para o calculo
        tags = set(str(row.get('Genres', '')).split(',')) | set(str(row.get('Categories', '')).split(','))
        
        vertices.append({
            'id': idx,
            'nome': nome_jogo,
            'peso': 0, # Peso do vértice é 0 no Grafo Tipo 6
            'tags': {t.strip().lower() for t in tags if t.strip()}
        })

    # 3. Cálculo das Arestas (Índice de Jaccard)
    arestas = []
    for i in range(num_vertices):
        for j in range(num_vertices):
            if i == j:
                continue # Evita auto-laços
            
            set_i = vertices[i]['tags']
            set_j = vertices[j]['tags']
            
            uniao = len(set_i.union(set_j))
            if uniao > 0:
                intersecao = len(set_i.intersection(set_j))
                # Similaridade de Jaccard normalizada entre 0 e 100
                similaridade = int((intersecao / uniao) * 100)
                
                # Regra de corte para nao poluir a matriz com ligacoes fracas
                if similaridade >= min_similaridade:
                    arestas.append((i, j, similaridade))

    # 4. Escrita do ficheiro grafos.txt conforme o padrão exigido
    print(f"A exportar para '{output_path}'...")
    with open(output_path, 'w', encoding='utf-8') as f:
        # Linha 1: Tipo de Grafo (6 = Orientado com Peso na Aresta)
        f.write("6\n")
        
        # Linha 2: Numero total de Vertices
        f.write(f"{num_vertices}\n")
        
        # Seção de Vértices: ID "Nome_do_Jogo" Peso_Vertice
        for v in vertices:
            f.write(f'{v["id"]} "{v["nome"]}" {v["peso"]}\n')
            
        # Numero total de Arestas
        f.write(f"{len(arestas)}\n")
        
        # Seção de Arestas: ID_Origem ID_Destino Peso_Aresta
        for u, v, peso_aresta in arestas:
            f.write(f"{u} {v} {peso_aresta}\n")

    print(f"Concluido com sucesso! {num_vertices} vertices e {len(arestas)} arestas geradas.")

if __name__ == "__main__":
    # Garanta que o ficheiro CSV do Steam esteja na mesma pasta com o nome 'steam_games.csv'
    gerar_grafo_steam()
