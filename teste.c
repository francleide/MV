#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//estrutura da lista (no)
typedef struct No{
    char valor[9];
    struct No *proximo;
}No;
//variaveis globais
char R[]="R", W[]="W";
int cont_miss=0, cont_hit=0, write_backs=0, op_leitura=0, op_escrita=0, fault = 0, op_entrada=0;
No *cabeca= NULL, *cauda=NULL, *no=NULL;


//imprimir lista --OK
void imprimir(){
	No *aux=cabeca;
    while (aux != NULL){
        printf("[%s] -> ", aux->valor);
        aux = aux->proximo;
    }
    printf("\n");
}
//inserir fim --OK
void inserir(char x[]){
	No *novo =(No*) malloc(sizeof(No));
	strcpy(novo->valor,x);
	//x[8]='\0';
	novo->proximo=NULL;
	cauda->proximo=novo;
	cauda=novo;
}
//escreve para a funcao random e quano for a mesma informacao -- TESTAR
void escrever(int pos, char x[9]){
	No *aux=cabeca;
	int cont;
	x[8]='\0';
	for(cont=0;cont<pos;cont++){
		aux->proximo;
		aux=aux->proximo;
	}	
	strcpy(aux->valor,x);
}
//remove inicio-- OK
void remover(){
	printf("chamou funcao remover\n" );
	if(cabeca==NULL){
		printf("lista vazia");
		return;
	}
	cabeca=cabeca->proximo;
}
//trocar o valor encontrado para tornalo recente
void trocar(char x[]){
	No *atual=cabeca, *ant=NULL;
	while(atual!=NULL){
		if(strcmp(atual->valor,x)==0){
			if(ant==NULL){
				remover();
			}else{
				if(atual->proximo!=NULL){
					ant->proximo=atual->proximo;
				}else{
					cauda=ant;
				}		
			}
			inserir(x);	
		}
		ant=atual;
		atual=atual->proximo;
	}
	printf("chamou funcao troca\n" );
}
//busca a posicao pelo valor e retorna valor encontrado --OK
int busca_valor(char x[]){
	No *aux=cabeca;
	int cont=0;
	while(aux != NULL){
		if(strcmp(aux->valor,x)==0){
			return cont;
		}
		aux=aux->proximo;
		cont++;
	}
	return -1;
}


//funcao de substituicao fifo
void s_fifo(char informacao[],char wr[]){
imprimir();
int i= busca_valor(informacao);	
	if(strcmp(wr,W)==0){
		if(i==-1){
			remover();
			inserir(informacao);	
		}else {
			escrever(i,informacao);
		}
		op_escrita++;
	}
	if(strcmp(wr,R)==0){
		if(i==-1){	
			remover();
			inserir(informacao);
			op_escrita++;
			cont_miss++;
			fault++;
		}else{
			cont_hit++;
		}
		op_leitura++;
		}
		
		write_backs++;
}
//funcao de substituicao lru
void s_lru(char informacao[],char wr[]){
	imprimir();
	int i= busca_valor(informacao);	
	if(strcmp(wr,W)==0){
		if(i==-1){
			remover();
			inserir(informacao);
		}else {
			trocar(informacao);
		}
		op_escrita++;
	}
	if(strcmp(wr,R)==0){
		if(i==-1){
			remover();
			inserir(informacao);
			op_escrita++;
			cont_miss++;
			fault++;
		}else{
			cont_hit++;
			trocar(informacao);
		}
		op_leitura++;
		
		}
		
		write_backs++;
}
//funcao de substituicao random
void s_random(char informacao[],char wr[],int cont_page){
	imprimir();
	int n;
	//srand(time(NULL));
	n=(rand()%cont_page);
	printf("rand %i\n",n);
	int i= busca_valor(informacao);	
	if(strcmp(wr,W)==0){
		if(i==-1){
			escrever(n,informacao);	
		}else {
			escrever(i,informacao);	
		}
		op_escrita++;
	}
	if(strcmp(wr,R)==0){
		if(i==-1){
			escrever(n,informacao);	
			cont_miss++;
			fault++;			
		}else{
			cont_hit++;
		}
		op_leitura++;
		}
		
		write_backs++;
}



int main (int argc, char *argv[]) {
    char *substituicao=argv[1], ch2[1], informacao[9], fifo[]="fifo", lru[]="lru", random[]="random";
	FILE *arquivo = fopen(argv[2],"r");
	int t_pagina = atoi(argv[3]), t_memoria= atoi(argv[4]), pos=0;
	int qtd_pagina=t_memoria/t_pagina, cont_page=0, i;
	unsigned int tx_pagefault;
	no= (No*) malloc(sizeof(No));
	
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
    
    //essa forma está correta! -- OK
	while(fscanf(arquivo,"%s %s\n",informacao,ch2)!=EOF){   
        if(cont_page<qtd_pagina){		
    		if(strcmp(ch2,R)==0){
				int u;
				if(cont_page==0){
					strcpy(no->valor,informacao);
    				no->proximo=NULL;
					cabeca=no;
					cauda=cabeca;			
					cont_miss++;
					op_escrita++;
				}else{
					u = busca_valor(informacao);
					if(u==-1){
						inserir(informacao);
						op_escrita++;
						cont_miss++;
					}else{
						if(strcmp(substituicao,lru)==0){
							trocar(informacao);
						}else
						escrever(u,informacao);
						cont_hit++;			
					}	
				}
				op_leitura++;
			}
			else {
				if(strcmp(ch2,W)==0){
					if(cont_page==0){
						strcpy(no->valor,informacao);
	    				no->proximo=NULL;
						cabeca=no;
						cauda=cabeca;			
					}else {
						int u=busca_valor(informacao);
						if(u==-1){
							inserir(informacao);
						}
						else{
							if(strcmp(substituicao,lru)==0){
								trocar(informacao);
							}else
							escrever(u,informacao);
						}		
					}
					op_escrita++;			
				}	
			}	
			cont_page++;
		}
		else{
			if(strcmp(substituicao,lru)==0){//essa substituicao esta OK
				s_lru(informacao,ch2);
			}
			if(strcmp(substituicao,random)==0){//essa substituicao esta OK
				s_random(informacao,ch2,cont_page);
			}
			if(strcmp(substituicao,fifo)==0){//essa substituicao esta OK
				s_fifo(informacao,ch2);
			}
		}
		op_entrada++;
	}
	tx_pagefault=(100*fault)/op_leitura;
	//imprime a lista
	imprimir();
	//pequeno relatorio
    printf("\nExecutando o simulador...\n");
    printf("Tamanho da memoria: %i KB\n", t_memoria);
    printf("Tamanho das paginas: %i KB\n", t_pagina);
    printf("Tecnica de reposicao: %s\n", substituicao);
    printf("Operacoes no arquivo de entrada: %i\n", op_entrada);
    printf("Operacoes de leitura: %i\nOperacoes de escrita: %i\n", op_leitura, op_escrita);
    printf("Page Hits: %i \nPage Misses: %i\n", cont_hit, cont_miss);
    printf("Numero de writebacks: %i\n", write_backs);
	printf("Taxa page fault: %i%%\n", tx_pagefault);

    
    
    fclose(arquivo);
    
   /*free(cabeca);
    free(cauda);*/
    free(no);
    
    //system("pause");
return 0;
}

