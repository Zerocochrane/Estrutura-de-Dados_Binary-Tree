#include <stdio.h>

typedef struct Tree Tree;

struct Tree{
  Tree * left, * right;
  int element;
};

Tree *make_empty(Tree *t){
  if (t != NULL){
    make_empty(t->left);
    make_empty(t->right);
    free(t);
  }

  return NULL;
}

Tree *find_min(Tree *t){
  if (t == NULL){
    return NULL;
  }
  else if (t->left == NULL){
    return t;
  }
  else{
    return find_min(t->left);
  }
}

Tree *find_max(Tree *t){
  if (t == NULL){
    return NULL;
  }
  else if (t->right == NULL){
    return t;
  }
  else{
    return find_max(t->right);
  }
}

Tree *find(int elem, Tree *t){
  if (t == NULL){
    return NULL;
  }

  if (elem < t->element){
    return find(elem, t->left);
  }
  else if (elem > t->element){
    return find(elem, t->right);
  }
  else{
    return t;
  }
}
               
Tree * insert(int value, Tree * t){
  Tree * new_node;
    
  if (t == NULL){
    new_node = (Tree *) malloc (sizeof (Tree));
    if (new_node == NULL){
	    return t;
    }

    new_node->element = value;

	  new_node->left = new_node->right = NULL;
	  return new_node;
  }
  
  if (value < t->element){
    t->left = insert(value, t->left);
  } 
  else if (value > t->element){
	  t->right = insert(value, t->right);
  } 
  else{ 
	  return t;
  }
  return t;
}

Tree * delete(int value, Tree * t){
  Tree * x;
  Tree *tmp_cell;
  
  if (t==NULL) return NULL;
  
  if (value < t->element){
    t->left = delete(value, t->left);
  } 
  else if (value > t->element){
	  t->right = delete(value, t->right);
  } 
  else if (t->left && t->right){
    tmp_cell = find_min(t->right);
    t->element = tmp_cell->element;
    t->right = delete(t->element, t->right);
  }
  else{ 
    tmp_cell = t;
    if (t->left == NULL)
      t = t->right;
    else if (t->right == NULL)
      t = t->left;
    free(tmp_cell);
  }

  return t;
}


typedef struct asciinode_struct asciinode;

struct asciinode_struct{
  asciinode * left, * right;
  int edge_length; 
  int height;      
  int lablen;
  int parent_dir;   
  char label[11];  
};


#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)


int gap = 3;  

int print_next;    

int MIN (int X, int Y){
  return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y){
  return ((X) > (Y)) ? (X) : (Y);
}

asciinode * build_ascii_tree_recursive(Tree * t){
  asciinode * node;
  
  if (node == NULL){
    return;
  }

  node = malloc(sizeof(asciinode));
  node->left = build_ascii_tree_recursive(t->left);
  node->right = build_ascii_tree_recursive(t->right);
  
  if (node->left != NULL){
    node->left->parent_dir = -1;
  }

  if (node->right != NULL){
    node->right->parent_dir = 1;
  }

  sprintf(node->label, "%d", t->element);
  node->lablen = strlen(node->label);

  return node;
}


asciinode * build_ascii_tree(Tree * t) 
{
  asciinode *node;
  if (t == NULL){
    return NULL;
  }
  node = build_ascii_tree_recursive(t);
  node->parent_dir = 0;
  return node;
}

void free_ascii_tree(asciinode *node){
  if (node == NULL){
    return;
  }
  free_ascii_tree(node->left);
  free_ascii_tree(node->right);
  free(node);
}

void compute_lprofile(asciinode *node, int x, int y){
  int i, isleft;
  if (node == NULL){
    return;
  }
  isleft = (node->parent_dir == -1);
  lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
  if (node->left != NULL){
	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++){
	    lprofile[y+i] = MIN(lprofile[y+i], x-i);
    }
  }
  compute_lprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
  compute_lprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

void compute_rprofile(asciinode *node, int x, int y){
  int i, notleft;
  if (node == NULL){ 
    return;
  }
  notleft = (node->parent_dir != -1);
  rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
  if (node->right != NULL){
	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++){
	    rprofile[y+i] = MAX(rprofile[y+i], x+i);
    }
  }
  compute_rprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
  compute_rprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

void compute_edge_lengths(asciinode *node){
  int h, hmin, i, delta;
  if (node == NULL) return;
  compute_edge_lengths(node->left);
  compute_edge_lengths(node->right);

  if (node->right == NULL && node->left == NULL){
	  node->edge_length = 0;
  } 
  else{
    if (node->left != NULL){
	    for (i=0; i<node->left->height && i < MAX_HEIGHT; i++){
		    rprofile[i] = -INFINITY;
	    }
	    compute_rprofile(node->left, 0, 0);
	    hmin = node->left->height;
    } 
    else{
	    hmin = 0;
    }
	  if (node->right != NULL){
	    for (i=0; i<node->right->height && i < MAX_HEIGHT; i++) 
      {
		    lprofile[i] = INFINITY;
	    }
	    compute_lprofile(node->right, 0, 0);
	    hmin = MIN(node->right->height, hmin);
    } 
    else{
	    hmin = 0;
    }
	  delta = 4;
	  for (i=0; i<hmin; i++){
	    delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
    }
	  
	  if (((node->left != NULL && node->left->height == 1) ||
	      (node->right != NULL && node->right->height == 1))&&delta>4){
      delta--;
    }
	    
    node->edge_length = ((delta+1)/2) - 1;
  }

  h = 1;
  if (node->left != NULL){
	  h = MAX(node->left->height + node->edge_length + 1, h);
  }
  if (node->right != NULL){
	  h = MAX(node->right->height + node->edge_length + 1, h);
  }
  node->height = h;
}

void print_level(asciinode *node, int x, int level){
  int i, isleft;
  if (node == NULL) return;
  isleft = (node->parent_dir == -1);
  if (level == 0){
	  for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++){
	    printf(" ");
    }
	  print_next += i;
	  printf("%s", node->label);
	  print_next += node->lablen;
  } 
  else if (node->edge_length >= level) {
	  if (node->left != NULL) 
    {
	    for (i=0; i<(x-print_next-(level)); i++){
		    printf(" ");
	    }
	    print_next += i;
	    printf("/");
	    print_next++;
    }
	  if (node->right != NULL){
	    for (i=0; i<(x-print_next+(level)); i++){
		    printf(" ");
	    }
	    print_next += i;
	    printf("\\");
	    print_next++;
    }
  } 
  else{
	  print_level(node->left, 
                x-node->edge_length-1, 
                level-node->edge_length-1);
	  print_level(node->right, 
                x+node->edge_length+1, 
                level-node->edge_length-1);
  }
}

void print_ascii_tree(Tree * t) {
  asciinode *proot;
  int xmin, i;
  if (t == NULL){
    return;
  }
  proot = build_ascii_tree(t);
  compute_edge_lengths(proot);
  for (i=0; i<proot->height && i < MAX_HEIGHT; i++) {
	  lprofile[i] = INFINITY;
  }
  compute_lprofile(proot, 0, 0);
  xmin = 0;
  for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
	  xmin = MIN(xmin, lprofile[i]);
  }
  for (i = 0; i < proot->height; i++) {
	  print_next = 0;
	  print_level(proot, -xmin, i);
	  printf("\n");
  }
  if (proot->height >= MAX_HEIGHT) {
	  printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
  }
  free_ascii_tree(proot); 
}

void main(){
  Tree * root;
  root = NULL;    
  make_empty(root);

  int numero, x=1, escolha;
    
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
                print2DUtil(t, 0);
                break;
        
            case 3:
                x=2;
                break;
        
            default:
                break;
        }
    }

  make_empty(root);
}