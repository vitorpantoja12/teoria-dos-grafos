#include <stdio.h>
#include <stdlib.h>

typedef struct Aresta {
    int destino;
    struct Aresta *prox;
} Aresta;

typedef struct Grafo {
    int n_vertices;
    Aresta **adj;
} Grafo;

Grafo *Criar_Grafo(int n){
    Grafo *Novo_Grafo = malloc(sizeof(Grafo));
    Novo_Grafo->n_vertices = n;

    Novo_Grafo->adj = malloc(n * sizeof(Aresta *));

    for (int i = 0; i < n; i++)
    {
        Novo_Grafo->adj[i] = NULL;
    }
    
    return Novo_Grafo;
}

void Adicionar_Aresta (Grafo *grafo, int origem, int destino){
    Aresta *Nova_Aresta = malloc(sizeof(Aresta));
    Nova_Aresta->destino = destino;

    Nova_Aresta->prox = grafo->adj[origem];
    grafo->adj[origem] = Nova_Aresta;
}

void BFS (Grafo *grafo, int vertice_origem){
    for (int i = 0; i < grafo->n_vertices; i++)
    {
        grafo->adj[i] = 
    }
    
}