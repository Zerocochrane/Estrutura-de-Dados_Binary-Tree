#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

struct TipoArvore {
    int info;
    struct TipoArvore* sae;
    struct TipoArvore* sad;
};
typedef struct TipoArvore Arvore;

Arvore* createTree(){
    return NULL;
}
int treeIsEmpty(Arvore* t){
    return t == NULL;
}


void print2DUtil(Arvore *t, int space) { 
    if (t == NULL){ 
        return;
    }

    space += COUNT; 
  
    print2DUtil(t->sad, space); 
  
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d\n", t->info); 

    print2DUtil(t->sae, space); 
}  

void impressaoPreOrdem(Arvore* t){

    if(!treeIsEmpty(t)){
        printf("%d ", t->info);
        impressaoPreOrdem(t->sae);
        impressaoPreOrdem(t->sad);
  }
}

void impressaoPosOrdem(Arvore* t){

    if(!treeIsEmpty(t)){
        impressaoPosOrdem(t->sae);
        printf("%d ", t->info);
        impressaoPosOrdem(t->sad);
  }
}

void impressaoInOrdem(Arvore* t){

    if(!treeIsEmpty(t)){
        impressaoInOrdem(t->sae);
        impressaoInOrdem(t->sad);
        printf("%d ", t->info);
  }
}

void insertTree(Arvore** t, int info){
    if(*t == NULL){
        *t = (Arvore*)malloc(sizeof(Arvore));
        (*t)->sae = NULL;
        (*t)->sad = NULL;
        (*t)->info = info;
    }else{
        if(info < (*t)->info){
            insertTree(&(*t)->sae, info);
        }
        if(info > (*t)->info){
            insertTree(&(*t)->sad, info);
        }
    }
}

int isInTree(Arvore* t, int info){
    if(treeIsEmpty(t)) {
        return 0;
    }
    return t->info==info || isInTree(t->sae, info) || isInTree(t->sad, info);
}

int main(){
    int numero, x=1, escolha;
    Arvore* t = createTree();
    
    while( x==1){
        printf("\nDigite 1 para inserir na Arvore;");
        printf("\nDigite 2 para imprimir a Arvore;");
        printf("\nDigite 3 para sair do programa.");
        printf("\nEscolha: ");
        scanf("%d", &escolha);
        switch (escolha){
            case 1:
                printf("\nDigite o numero que sera inserido na Arvore: ");
                scanf("%d", &numero);
                insertTree(&t, numero);
                break;
        
            case 2:
                printf("\n\n\n--- Imprimindo a Arvore de forma 2D ---\n");
                print2DUtil(t, 0);
                printf("\n--- Final da Impressao da Arvore ---");

                printf("\n\n\n--- Imprimindo a Arvore em pre-ordem ---\n");
                impressaoPosOrdem(t);
                printf("\n--- Final da Impressao da Arvore ---");

                printf("\n\n\n--- Imprimindo a Arvore de em pos-ordem ---\n");
                impressaoPreOrdem(t);
                printf("\n--- Final da Impressao da Arvore ---");

                printf("\n\n\n--- Imprimindo a Arvore de em in-ordem ---\n");
                impressaoInOrdem(t);
                printf("\n--- Final da Impressao da Arvore ---");
                break;
        
            case 3:
                x=2;
                break;
        
            default:
                break;
        }
    }
   
  
    free(t);
    return 0;
}
