/*
  Algoritimo inicialmente feito para disiplina de grafos, para cria��o e manipula��o de um Lista de Adjac�ncias
  adaptado para projeto de Compiladores com objetivo de representar um Automato Finito Deterministico.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Estrutara completa
struct art{	// Estrutura das arestas
  char trans[67];
	int dest;
	struct art *prox;
};

struct vet{	// Estrutura dos vertece
	int id;
	struct art *art;
	struct vet *prox;
};
// Fim_estrutura completa

struct vet *inserir_v(struct vet *grafo, int id){//função de inserção de novo estado
	struct vet *novo;
	struct vet *p = grafo;

	if(grafo == NULL){//se for a primeira insençao
		novo = (struct vet*)malloc(sizeof(struct vet));
		novo->id = id;
		novo->art = NULL;
		novo->prox = NULL;

		return novo;
	}

	while(p->prox != NULL){//indo para o final da fila
		p = p->prox;
	}

	//adicionando o novo vertice
	novo = (struct vet*)malloc(sizeof(struct vet));
	novo->id = id;
	novo->art = NULL;
	novo->prox = NULL;

	p->prox = novo;

	return grafo;
}

struct vet *remover_a(struct vet *grafo, int vet_1, int vet_2){//funçao de remoçao de arestas nao otilizada nesse projeto
	struct vet *p=grafo;//pecorre lista de verteces
	struct art *q, *artant; //pecorre lista de arestas

	while(p->id != vet_1){//buscando vet_1
		p = p->prox;
	}
	q = p->art;

	while(q->dest != vet_2){
		artant = q;
		q = q->prox;
	}

	if(q == p->art){//caso a aresta seja a primeira da lista
		p->art = q->prox;
	}else{
		artant->prox = q->prox;
	}

	free(q);

	//restaurando variaveis
	/*p = grafo;
	q = NULL;

	while(p->id != vet_2){//buscando vet_2
		p = p->prox;
	}
	q = p->art;

	while(q->dest != vet_1){
		artant = q;
		q = q->prox;
	}

	if(q == p->art){//caso a aresta seja a primeira da lista
		p->art = q->prox;
	}else{
		artant->prox = q->prox;
	}

	free(q);*/

	return grafo;
}

struct vet *remover_v(struct vet *grafo, int id){//reompçao de estados não ultilizada nesse projeto
	struct vet *vet_r=grafo;//vet a ser removido
	struct vet *p=grafo; //pecorre lista de vertece
	struct art *q; //pecorre lista de arestas
	struct vet *antvet; //variavel para elemeto anterior
	int idart=-1;

	while(vet_r->id != id){//encontrando vet
		antvet = vet_r;
		vet_r = vet_r->prox;
	}

	//remove aresta das listas dos outros vertices
	while(p != NULL){
		q = p->art;
		while(q != NULL){
			if(q->dest == id){
				idart = q->dest;
			}
			q = q->prox;
			if(idart != -1){
				grafo = remover_a(grafo, p->id,id);
				idart = -1;
			}
		}
		p =p->prox;
	}

	//removendo o vertce
	if(vet_r == grafo){//caso seja o primeiro da lista
		grafo = grafo->prox;
	}else{
		antvet->prox = vet_r->prox;
	}

	free(vet_r);

	return grafo;
}

struct vet *inserir_a(struct vet *grafo, int vet_1, int vet_2, char lis_car[67]){//função de inserção de arestas
	struct vet *p=grafo;//pecorrer lista verteces
	struct art *nova,*q;// (q)pecorrer lista de arestas

	while(p->id != vet_1){//encontrando vet_1
		p = p->prox;
	}
	q = p->art;

	nova = (struct art*)malloc(sizeof(struct art));
	nova->dest = vet_2;
  memset(nova->trans, 0, 67);
  strncat(nova->trans, lis_car, strlen(lis_car));
	if(q == NULL){//caso não possua arestas
		nova->prox = NULL;
		p->art = nova;
	}else{
		while(q->prox != NULL){
			q = q->prox;
		}

		q->prox = nova;
		nova->prox = NULL;
	}

	//restaurando variaveis
	/*p = grafo;
	q = nova = NULL;

	//alocando arestas no vertice 2
	while(p->id != vet_2){//encontrando vet_2
		p = p->prox;
	}
	q = p->art;

	nova = (struct art*)malloc(sizeof(struct art));
	nova->dest = vet_1;
	if(q == NULL){//caso não possua arestas
		nova->prox = NULL;
		p->art = nova;
	}else{
		while(q->prox != NULL){
			q = q->prox;
		}

		q->prox = nova;
		nova->prox = NULL;
	}*/

	return grafo;
}

struct vet *ret_pont(struct vet *autom, int id){//retorna o ponteiro para o indentificado especificado
  struct vet *p=autom;

  while(p != NULL){
    if(p->id == id){
      return p;
    }
    p = p->prox;
  }
}

int reconhecer(struct vet *autom, char token[]){//retorna o estado final do token
  struct vet *q= autom; //quarda estado atual
  struct art *p; //pecorre lista de arestas
  int es_atual; //indetifica estado
  int i, j; //variavel de controle

  for(i=0;i<strlen(token);i++){
    p = q->art;
    while(p != NULL){
      for(j=0;j<strlen(p->trans);j++){
        if(token[i] == p->trans[j]){
          es_atual = p->dest;
          break;
        }
      }
      p = p->prox;
    }
    q = ret_pont(autom, es_atual);
  }

  return es_atual;
}

void exibir(struct vet *grafo){//exibir a lista de adjacencia nao foi ultilizada nesse projeto
	struct art *p;

	if(grafo == NULL){
		printf("Lista vazia.\n\n");
		return;
	}
	printf("Lista de adjacencia\n\n");

	while(grafo != NULL){
		printf("%d| ",grafo->id);
		p = grafo->art;
		while(p != NULL){
			printf("->%d ", p->dest);
			p = p->prox;
		}
		printf("\n");
		grafo = grafo->prox;
	}

	printf("----------------\n\n");

}
