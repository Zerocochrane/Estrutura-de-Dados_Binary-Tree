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

void clearTree(Arvore* t){
    if(t!=NULL){
        clearTree(t->sae);
        clearTree(t->sad);
        free(t);
    }else{
        return;
    }
}

int maxDepth(Arvore* t)  
{ 
   if (t==NULL)  
       return 0; 
   else 
   { 
       int lDepth = maxDepth(t->sae); 
       int rDepth = maxDepth(t->sad); 
  
       if (lDepth > rDepth)  
           return(lDepth+1); 
       else return(rDepth+1); 
   } 
}

 int getLeafCount( Arvore* t) 
{ 
  if(t == NULL)        
    return 0; 
  if(t->sae == NULL && t->sad==NULL)       
    return 1;             
  else 
    return getLeafCount(t->sae) + getLeafCount(t->sad);       
} 

int main(){
    int numero, x=1, escolha, busca;
    Arvore* t = createTree();
    
    while( x==1){
        printf("\nDigite 1 para popular a  Arvore;");
        printf("\nDigite 2 para imprimir a Arvore;");
        printf("\nDigite 3 para buscar na arvore;");
        printf("\nDigite 4 para ver a altura da Arvore.");
        printf("\nDigite 5 para ver quantas folhas estao na Arvore.");
        printf("\nDigite 6 para sair do programa.");
        printf("\nEscolha: ");
        scanf("%d", &escolha);
        switch (escolha){
            case 1:
                insertTree(&t, 3);
                insertTree(&t, 4);
                insertTree(&t, 5);
                insertTree(&t, 6);
                insertTree(&t, 1);
                insertTree(&t, 2);
                insertTree(&t, 0);
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
                printf("\nDigite o valor que sera buscado: ");
                scanf("%d", &busca);
                if(isInTree(t, busca)){
                    printf("\nO numero %d esta na arvore.", busca);
                }else{
                    printf("\nO numero %d nao esta na arvore.", busca);
                }
                break;

            case 4:
                printf("\nA altura da Arvore eh: %d\n", maxDepth(t) - 1);
                break;
            
            case 5:
                printf("\nO numero de folhas da Arvore eh: %d\n", getLeafCount(t));
                break;

            case 6:
                x=2;
                break;
        
            default:
                break;
        }
    }
    
    clearTree(t);
    if(treeIsEmpty(t)){
        printf("A arvore nao esta vazia");
    }else{
        printf("A arvore esta vazia");
    }
    return 0;
}
