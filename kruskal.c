#include <stdio.h>
#include <stdlib.h>

typedef struct Aresta {
    int u, v, peso;
} Aresta;

typedef struct Grafo {
    int n_ver, n_ar;
    Aresta* arestas;
} Grafo;

typedef struct Conjunto {
    int pai, rank;
} Conjunto;

int comparacao (const void *a, const void *b){
    Aresta *e1 = (Aresta*) a;
    Aresta *e2 = (Aresta*) b;

    return e1->peso - e2->peso;
}

void makeset(Conjunto* subconjunto, int n_vertices){
    for (int i = 0; i < n_vertices; i++)
    {
        subconjunto[i].pai = i;
        subconjunto[i].rank = 0;
    }
}

int find(Conjunto *conjuntos, int vertice){
    if (conjuntos[vertice].pai != vertice){
        conjuntos[vertice].pai = find(conjuntos, conjuntos[vertice].pai);
    }
    return conjuntos[vertice].pai;
}

void union_find(Conjunto *conjuntos, int vertice_x, int vertice_y){
    int raiz_x = find (conjuntos, vertice_x);
    int raiz_y = find (conjuntos, vertice_y);

    if (raiz_x == raiz_y) {
        return;
    }

    if (conjuntos[raiz_x].rank > conjuntos[raiz_y].rank)
    {
        conjuntos[raiz_y].pai = raiz_x;
    } else {
        if (conjuntos[raiz_y].rank > conjuntos[raiz_x].rank)
        {
            conjuntos[raiz_x].pai = raiz_y;
        } else {
            conjuntos[raiz_y].pai = raiz_x;
            conjuntos[raiz_y].rank ++;
        }
    }
}

Aresta *kruskal (Grafo G){
    qsort(G.arestas, G.n_ar, sizeof(Aresta), comparacao);

    Conjunto *conjunto = malloc(G.n_ver * sizeof(Conjunto));
    makeset (conjunto, G.n_ver);

    Aresta *AGM = malloc((G.n_ver - 1) * sizeof(Aresta));
    int mst_index = 0;

    for (int i = 0; i < G.n_ar; i++)
    {
        Aresta atual = G.arestas[i];
        int u = find(conjunto, atual.u);
        int v = find(conjunto, atual.v);

        if (u != v){
            AGM[mst_index++] = atual;
            union_find(conjunto, u, v);
        }
    }
    
    return AGM;
}

int main() {
    Grafo g;

    g.n_ver = 4;
    g.n_ar = 4;

    g.arestas = malloc(g.n_ar * sizeof(Aresta));

    g.arestas[0] = (Aresta){0,1,1};
    g.arestas[1] = (Aresta){1,3,2};
    g.arestas[2] = (Aresta){2,3,3};
    g.arestas[3] = (Aresta){0,2,4};

    Aresta *agm = kruskal(g);

    int peso_total = 0;

    printf("Arestas da AGM:\n");

    for (int i = 0; i < g.n_ver - 1; i++) {
        printf("%d -- %d (peso %d)\n", agm[i].u, agm[i].v, agm[i].peso);
        peso_total += agm[i].peso;
    }

    printf("Peso total = %d\n", peso_total);

    free(agm);
    free(g.arestas);

    return 0;
}