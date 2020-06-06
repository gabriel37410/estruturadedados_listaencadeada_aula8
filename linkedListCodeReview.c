#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct _estudante {
    int id;
	char name[100];
	float notaAluno;
} Estudante;

typedef struct _node {
	Estudante estudante;
	struct _node *prox;
	struct _node *ant;
} Node, *list;

void insert_list (list *lista_estudante, Estudante estudante) {
	Node *auxiliar;

	auxiliar = (Node *) malloc (sizeof (Node));
	auxiliar->estudante = estudante;

	if(*lista_estudante == NULL) {
		*lista_estudante = auxiliar;
	} else {
		(*lista_estudante)->ant = auxiliar;
		auxiliar->prox = *lista_estudante;

		*lista_estudante = auxiliar;
	}
}

Estudante *search_list (list lista_estudante, int id) {
	Node *auxiliar;

	for (auxiliar = lista_estudante; auxiliar && auxiliar->estudante.id != id; auxiliar=auxiliar->prox);
	
	if (auxiliar) {
		return &auxiliar->estudante;
	}
	else {
		return NULL;
	}
}

void create_list (list *lista_estudante) {
	*lista_estudante = NULL;
}

list lerArquivo() {
	list lista_estudante;
	Estudante	estudante;
	
	FILE *file;

	file = fopen ("list.txt", "r");

	if (!file) {
		printf("Erro ao ler o arquivo\n");
		exit (1);
	}

	create_list (&lista_estudante);

	while(!feof(file)) {
		fscanf (file, "%d %s %f\n", &estudante.id, estudante.name, &estudante.notaAluno);
		insert_list (&lista_estudante, estudante);
	}

	fclose (file);

	return lista_estudante;
}

void buscarPorID() {
	Estudante *seleciona_estudante;
	int id = 0;

	list lista_estudante = lerArquivo();

	while(id != -1) {
		printf ("\n-1 para voltar ao menu.\nDigite o ID do estudante:");
		scanf ("%d", &id);

		seleciona_estudante = search_list (lista_estudante, id);

		!seleciona_estudante ? printf("\nEstudante nao encontrado\n") : printf("\n%d\t%s\t%0.2f\n", seleciona_estudante->id, seleciona_estudante->name, seleciona_estudante->notaAluno);
	}
}

void exibirOrdemDecrescente() {
	list lista_estudante = lerArquivo();
	Node *auxiliar;
	
	auxiliar = (Node *) malloc(sizeof(Node));
	*auxiliar = *lista_estudante;

	while(auxiliar) {
		printf("ID: %i\tName: %s\tNota: %.2f\n", auxiliar->estudante.id, auxiliar->estudante.name, auxiliar->estudante.notaAluno);

		if(auxiliar->prox == NULL) {
			break;
		}
		*auxiliar = *auxiliar->prox;
	}
	free(auxiliar);
}

void exibirOrdemCrescente() {
	list lista_estudante = lerArquivo();
	Node *fim;
	
	fim = (Node *) malloc(sizeof(Node));
	*fim = *lista_estudante;

	while(fim->prox != NULL) {
		*fim = *fim->prox;
	}

	while(fim) {
		printf("ID: %i\tName: %s\tNota: %.2f\n", fim->estudante.id, fim->estudante.name, fim->estudante.notaAluno);
		
		if(fim->ant == NULL) {
			break;
		}

		*fim = *fim->ant;
	}
	free(fim);
}


int main() {
 int menu = -1;
	do{
		printf("1 - Procurar alunos na lista.\n");
		printf("2 - Listar alunos em ordem crescente.\n");
		printf("3 - Listar alunos em ordem descrescente.\n");
		printf("4 - Remover aluno da lista.\n");
		printf("0 - Sair\n");
		scanf("%i", &menu);

		switch(menu) {
			case 0: break;
			case 1:
				buscarPorID();
				break;

			case 2:
				exibirOrdemCrescente();
				break;

			case 3:
				exibirOrdemDecrescente();
				break;

			case 4:
				printf("Opcao temporariamente indisponivel.\n Aperta qualquer tecla para retornar ao menu.\n\n");
				getch();
				break;

			default:
				printf("Opcao invalida.\n\n");
				break;
		}
	}while(menu != 0);

	exit (0);
}