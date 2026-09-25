"""
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
"""

"""
SÍNTESE DO ARQUIVO:
Este script Python realiza a leitura e o pré-processamento do arquivo 'games.json' 
para construir a estrutura de dados do grafo de recomendação de jogos.

O script calcula o peso das arestas através da Similaridade de Jaccard entre cada par 
de jogos, dividindo a interseção (características, gêneros e tags em comum) pela 
união (total de características únicas dos dois jogos combinados). 

Os resultados que atingem o limite mínimo de similaridade (15%) são exportados para o 
arquivo 'grafos.txt', contendo o tipo de grafo (Tipo 6: Orientado e Ponderado), a 
lista de vértices (IDs e nomes dos jogos) e a lista de arestas ponderadas.
"""

import json
import re
import os

def gerar_grafo_steam_json(json_path="games.json", output_path="grafos.txt", min_similaridade=15):
    print(f"Lendo o arquivo JSON '{json_path}'...")
    
    if not os.path.exists(json_path):
        print(f"ERRO: Arquivo '{json_path}' nao encontrado na pasta!")
        return

    # Leitura do JSON com tratamento para vírgulas sobressalentes
    try:
        with open(json_path, 'r', encoding='utf-8') as f:
            conteudo_raw = f.read()

        # Limpa eventuais vírgulas sobressalentes antes do fecho de chaves/colchetes
        conteudo_limpo = re.sub(r',\s*([\}\]])', r'\1', conteudo_raw)
        dados = json.loads(conteudo_limpo)
        
    except Exception as e:
        print(f"ERRO ao ler o arquivo JSON: {e}")
        return

    vertices = []
    
    # Mapeamento dos Vértices (ID, Nome/Rótulo, Peso)
    for idx, (app_id, jogo) in enumerate(dados.items()):
        if not isinstance(jogo, dict):
            continue

        nome_bruto = str(jogo.get('name', f"Jogo {idx}"))
        nome_limpo = nome_bruto.replace('"', '').replace('\n', '').replace('\r', '').strip()

        tags_set = set()
        
        # Leitura das tags
        tags_obj = jogo.get('tags', {})
        if isinstance(tags_obj, dict):
            tags_set.update([t.strip().lower() for t in tags_obj.keys()])
        elif isinstance(tags_obj, list):
            tags_set.update([str(t).strip().lower() for t in tags_obj])

        # Leitura dos generos
        genres_obj = jogo.get('genres', [])
        if isinstance(genres_obj, list):
            tags_set.update([str(g).strip().lower() for g in genres_obj])

        vertices.append({
            'id': len(vertices),
            'nome': nome_limpo,
            'peso': 0, # Peso 0 no Grafo Tipo 6
            'tags': tags_set
        })

    num_vertices = len(vertices)

    # Cálculo das Arestas (Similaridade de Jaccard)
    arestas = []
    for i in range(num_vertices):
        for j in range(num_vertices):
            if i == j:
                continue 
            
            set_i = vertices[i]['tags']
            set_j = vertices[j]['tags']
            
            uniao = len(set_i.union(set_j))
            if uniao > 0:
                intersecao = len(set_i.intersection(set_j))
                similaridade = int((intersecao / uniao) * 100)
                
                # Guarda aresta se atingir a nota de corte
                if similaridade >= min_similaridade:
                    arestas.append((i, j, similaridade))

    # Escrita do arquivo grafos.txt para C++
    print(f"Exportando para '{output_path}'...")
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write("6\n") # Tipo do Grafo
        f.write(f"{num_vertices}\n")
        
        for v in vertices:
            f.write(f'{v["id"]} "{v["nome"]}" {v["peso"]}\n')
            
        f.write(f"{len(arestas)}\n")
        
        for u, v, peso_aresta in arestas:
            f.write(f"{u} {v} {peso_aresta}\n")

    print(f"Sucesso! Gerados {num_vertices} vertices e {len(arestas)} arestas no '{output_path}'.")

if __name__ == "__main__":
    gerar_grafo_steam_json()
