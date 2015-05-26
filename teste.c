#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct No{
    char valor[8];
    struct No *proximo;
}No;

//imprimir lista
void imprimir(No *no){
	No *aux=no;
    while (aux != NULL){
        printf("%s\n", aux->valor);
        aux = aux->proximo;
    }
   
}
//inserir fim --OK
void inserir(No **ant, char x[]){
	No *novo =(No*) malloc(sizeof(No));
	strcpy(novo->valor,x);
	novo->proximo=NULL;
	(*ant)->proximo=novo;
	*ant=novo;
}
//insere para todas as funcoes -- TESTAR
void escrever(No **no,int pos, char x[]){
	No *aux=*no;
	int cont;
	for(cont=0;cont<pos;cont++){
		aux->proximo;
		aux=aux->proximo;
	}	
	strcpy(aux->valor,x);
}
//remove para todas as funcoes -- OK
void remover(No *no, char x[]){
	No *anterior, *atual=no;
	int cont, y = busca_valor(&no,x);
	for (cont=0; cont<y;cont++){
		anterior=atual;
		atual=atual->proximo;
	}
	anterior->proximo=atual->proximo;
	
}
//busca o valor pela posicao e retorna valor encontrado --OK
char *busca_pos(No **no, int x){
	No *aux=*no;
	int cont=0;
	while(cont<x){
		aux=aux->proximo;
		cont++;
	}
	return aux->valor;
}
//busca a posicao pelo valor e retorna valor encontrado --OK
int busca_valor(No **no, char x[]){
	No *aux=*no;
	int cont=0;
	while(strcmp(aux->valor,x)!=0){
		aux=aux->proximo;
		cont++;
	}
	return cont;
}



void fifo(No *no, char x[]){

	
}
void lru(No *no, char x[]){
	
/*pode ser feita com comparacao utilizando a busca até q seja 
igual p/ poder ser removido o valor atualizado	
*/
}
void random(No *no, char x[]){

	
}


int main (int argc, char *argv[]) {
    char *substituicao=argv[1], ch2[1], ch3[8], f[]="fifo", l[]="lru", r[]="random", k[]="R", w[]="W";
	FILE *arquivo = fopen(argv[2],"r");
	int t_pagina = atoi(argv[3]), t_memoria= atoi(argv[4]), pos=0;
	int qtd_pagina=t_memoria/t_pagina, cont_page=0, cont_miss=0, cont_hit=0;
	No *no= (No*) malloc(sizeof(No));
	No *cabeca= NULL, *cauda=NULL;
	
    //retorna um erro se o tamanho da paginacao estiver fora do intervalo permitido
	if(t_pagina<2 || t_pagina>64){
		printf("Erro! Esse tamanho de paginacao nao e possivel\n");
		return 0;
	}
	//retorna um erro se o tamanho da memoria estiver fora do intervalo permitido
	if(t_memoria<128 ||t_memoria>16384){
		printf("Erro! Esse tamanho de memoria nao e possivel\n");
		return 0;
	}

    if(!arquivo){
           printf("Erro! Nao e possivel abrir o arquivo\n");
		return 0;
    }
    
    //Essa forma esta correta
    while(fscanf(arquivo,"%s %s\n", ch3,ch2)!=EOF){   	
        if(cont_page<qtd_pagina){//essa forma está correta! -- OK		
	    	if(strcmp(ch2,k)==0){//esta correto
				cont_miss++;//funciona
			}else if(strcmp(ch2,w)==0){
				if(cont_page==0){
					strcpy(no->valor,ch3);
    				no->proximo=NULL;
					cabeca=no;
					cauda=cabeca;		
					printf("primeiro %s\n",cabeca->valor);		
				}else{
						inserir(&cauda,ch3);
					printf("nao eh primeiro %s\n",cauda->valor);
				}
				cont_page++;
			}
		}
	}
	
	
	imprimir(cabeca);
	printf("o indice encontrado %s\n", busca_pos(&no,1));
	printf("o indice encontrado %i\n", busca_valor(&no,busca_pos(&no,1)));
	remover(no,busca_pos(&no,1));
	imprimir(cabeca);
    printf("\nExecutando o simulador...\n");
    printf("Tamanho da memoria: %i KB\n", t_memoria);
    printf("Tamanho das paginas: %i KB\n", t_pagina);
    printf("Tecnica de reposicao: %s\n", substituicao);
    printf("Hit: %i e Miss: %i\n", cont_hit, cont_miss);

    
    
    fclose(arquivo);
    free(no);
    //system("pause");
return 0;
}

