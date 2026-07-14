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
}

void inserir_aresta(Grafo *g, int o, int d, int peso)
{
    No *novo = malloc(sizeof(No));
    novo->valor = d;
    novo->peso = peso;
    novo->prox = g->lista_de_adj[o];
    g->lista_de_adj[o] = novo;

    // Grafo não direcionado
    novo = malloc(sizeof(No));
    novo->valor = o;
    novo->peso = peso;
    novo->prox = g->lista_de_adj[d];
    g->lista_de_adj[d] = novo;
}

void prim(Grafo *G)
{
    int key[G->n_ver];
    int pai[G->n_ver];
    int mstSet[G->n_ver];

    // Inicialização
    for(int i = 0; i < G->n_ver; i++)
    {
        key[i] = INF;
        pai[i] = -1;
        mstSet[i] = 0;
    }

    // Começa pelo vértice 0
    key[0] = 0;

    for(int cont = 0; cont < G->n_ver - 1; cont++)
    {
        int menor = INF;
        int u = -1;

        // Escolhe o vértice de menor key
        for(int i = 0; i < G->n_ver; i++)
        {
            if(mstSet[i] == 0 && key[i] < menor)
            {
                menor = key[i];
                u = i;
            }
        }

        if(u == -1)
            break;

        mstSet[u] = 1;

        // Percorre os vizinhos
        No *p = G->lista_de_adj[u];

        while(p != NULL)
        {
            int v = p->valor;
            int peso = p->peso;

            if(mstSet[v] == 0 && peso < key[v])
            {
                key[v] = peso;
                pai[v] = u;
            }

            p = p->prox;
        }
    }

    printf("Arestas da MST:\n");

    int custo = 0;

    for(int i = 1; i < G->n_ver; i++)
    {
        printf("%d - %d (peso %d)\n", pai[i], i, key[i]);
        custo += key[i];
    }

    printf("\nCusto total = %d\n", custo);
}

int main()
{
    Grafo *g = Criar_Grafo(5);

    inserir_aresta(g,0,1,2);
    inserir_aresta(g,0,3,6);
    inserir_aresta(g,1,2,3);
    inserir_aresta(g,1,3,8);
    inserir_aresta(g,1,4,5);
    inserir_aresta(g,2,4,7);
    inserir_aresta(g,3,4,9);

    prim(g);

    return 0;
}