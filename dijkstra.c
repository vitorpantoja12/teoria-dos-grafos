#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

struct No {
    int valor, peso;
    struct No *prox;
};

typedef struct No No;

typedef struct Grafo {
    int n_ver;
    No **lista_de_adj;
} Grafo;

Grafo *Criar_Grafo(int vertices){
    Grafo *Novo_Grafo = malloc(sizeof(Grafo));
    Novo_Grafo->n_ver = vertices;
    Novo_Grafo->lista_de_adj = calloc(vertices, sizeof(No*));
    
    return Novo_Grafo;
};

void inserir_aresta(Grafo *g, int o, int d, int peso)
{
    No *novo = malloc(sizeof(No));
    novo->valor = d;
    novo->peso = peso;

    novo->prox = g->lista_de_adj[o];
    g->lista_de_adj[o] = novo;
}

void dijkstra(Grafo *G, int origem){
    int *resolvidos, tam_r;
    No* p;

    int dist[G->n_ver];
    int pai[G->n_ver];

    for (int i = 0; i < G->n_ver; i++)
    {
        dist[i] = INF;
        pai[i] = -1;
    }
    
    dist[origem] = 0;

    resolvidos = malloc(G->n_ver*sizeof(int));
    tam_r = 0;

    for (int i = 0; i < G->n_ver; i++)
    {
        resolvidos[i] = 0;
    }

    int min_dist, vertice_atual;
    
    while (tam_r < G->n_ver)
    {
        min_dist = INF;
        vertice_atual = -1;

        for (int i = 0; i < G->n_ver; i++)
        {
            if (resolvidos[i] == 0 && dist[i] < min_dist)
            {
                vertice_atual = i;
                min_dist = dist[i];
            }
        }

        if (vertice_atual == -1) break;

        resolvidos[vertice_atual] = 1;
        tam_r++;

        for (p = G->lista_de_adj[vertice_atual]; p != NULL; p = p->prox)
        {
            int v = p->valor;
            int peso = p->peso;

            if (resolvidos[v] == 0 && dist[v] > dist[vertice_atual]+peso)
            {
                dist[v] = dist[vertice_atual]+peso;
                pai[v] = vertice_atual;
            }
        }
    }
    
    printf("Origem: %d\n\n", origem);

    printf("Vertice\tDistancia\tPai\n");

    for (int i = 0; i < G->n_ver; i++)
    {
        printf("%d\t", i);

        if (dist[i] == INF)
            printf("INF\t\t");
        else
            printf("%d\t\t", dist[i]);

        if (pai[i] == -1)
            printf("-\n");
        else
            printf("%d\n", pai[i]);
    }

    free(resolvidos);
}