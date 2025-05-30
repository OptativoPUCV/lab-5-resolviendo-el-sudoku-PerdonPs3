#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  for(int i = 0; i < 9; i++){
    int seen[10] = {0};
    for(int j = 0; j < 9; j++){
      int num = n->sudo[i][j];
      if(num != 0){
        if(seen[num]) return 0;
        seen[num] = 1;
      }
    }
  }
  for(int j = 0; j < 9; j++){
    int seen[10] = {0};
    for(int i = 0; i < 9; i++){
      int num = n->sudo[i][j];
      if(num != 0){
        if(seen[num]) return 0;
        seen[num] = 1;
      }
    }
  }
  for (int row = 0; row < 9; row += 3) { 
    for (int col = 0; col < 9; col += 3) {  
      int seen[10] = {0};  
      for (int i = row; i < row + 3; i++) {  
        for (int j = col; j < col + 3; j++) {  
          int num = n->sudo[i][j];  
          if (num != 0) {  
            if (seen[num]) return 0;  
            seen[num] = 1;  
          }  
        }  
      }
    }
  }
  
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list = createList();
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){
        for(int num = 1; num <= 9; num++){
          n->sudo[i][j] = num;
          if(is_valid(n)){
            Node* newNode = copy(n);
            pushBack(list, newNode);
          }
          n->sudo[i][j] = 0; 
        }
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0)
        return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* S = createStack();
    push(S, initial);

    while (!is_empty(S)) {
      Node* current = top(S);  
      pop(S);
      (*cont)++;

      if(is_final(current)){
        return current;
      }

      List* adj_nodes = get_adj_nodes(current);
      Node* adj_node = first(adj_nodes);
      while(adj_node != NULL){
        if(is_valid(adj_node)){
          push(S, adj_node);
        }
        adj_node = next(adj_nodes);
      } 
      free(adj_nodes);
      free(current); 
    }
    return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/