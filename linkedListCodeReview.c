// http://hpca23.cse.tamu.edu/taco/utsa-www/ut/utsa/cs1723/lecture4.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string.h>

//===========================ELEMENTOS DA LISTA===========================
typedef struct _student {
	int		  id;
	char		name[100];
	float		notaAluno;
} student;

//===========================NÓ DA LISTA ENCADEADA===========================
typedef struct _node {
	student		k;
	struct _node	*next; // ponteiro para o próximo elemento
} node, *list;

//===========================INSERI OS DADOS NA LISTA===========================
void insert_list (list *L, student k) {
	node	*p;
	p = (node *) malloc (sizeof (node));
	p->k = k;
	p->next = *L;

	*L = p;
}

//===========================PROCURA NA LISTA===========================
student *search_list (list L, int id) {
	node	*p;

	for (p=L; p && p->k.id != id; p=p->next);

	if (p)
		return &p->k;
	else
		return NULL;
}

//===========================CRIA UMA LISTA VAZIA===========================
void create_list (list *L) {
	*L = NULL;
}

//===========================OPÇÕES DO MENU===========================
void mostraMenu() {
	printf("1 - Procurar elemento na lista\n");
    printf("2 - Adicionar elemento na lista\n");
    printf("3 - Remover elemento da lista\n");
	printf("4 - Exibir lista de forma ordenada\n");
    printf("0 - Sair\n");
}

int main () {

	setlocale(LC_ALL, "Portuguese");
	
	list		C;	/* a class of students */
	student		s, *p;
	int		id;
	FILE		*f;


	//===========================ABRE E CARREGA O ARQUIVO TXT===========================
	f = fopen ("./List.txt", "r");
	if (!f) {
		perror ("List");
		exit (1);
	}

	create_list (&C);

	for (;;) {
		fscanf (f, "%d %s %f\n", &s.id, s.name, &s.notaAluno);
		if (feof (f))
      break;
		insert_list (&C, s);
	}
	fclose (f);
	//

	//===========================MENU===========================
	int menu = -1;
	do{
	system("@cls||clear");
	mostraMenu();
	printf("Informe a opção: ");
	scanf ("%d", &menu);
    system("@cls||clear");

    switch (menu)
    {
    	case 0: break;
        case 1:
        	for (;;) {
				printf ("Enter student ID, -1 to finish: ");
				scanf ("%d", &id);

				if (id == -1)
       				break;

				p = search_list (C, id);


				if (!p)
					printf ("ID #%d not found!\n", id);
				else
					printf ("%d\t%s\t%0.2f\n", p->id, p->name, p->notaAluno);
			}
            break;
        
        case 2:
            //
            break;

        case 3:
            //
            break;

        case 4:
            //
            break;

        default:
            printf("Opção invalida");
            break;
    }
	}while(menu != 0);

	exit (0);
}