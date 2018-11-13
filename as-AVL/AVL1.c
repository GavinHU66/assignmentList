#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1

struct treeNode{
  int key;
  struct treeNode * left;
  struct treeNode * right;
};

typedef struct treeNode treeNode;

treeNode * Insert ( treeNode * currentNode , int key );
int getHeight ( treeNode * currentNode );
int heightLeftMinusRight ( treeNode * currentNode );
treeNode * balanceTree ( treeNode * currentNode );
treeNode * R_rotation ( treeNode * parent );
treeNode * L_rotation ( treeNode * parent );
treeNode * LR_rotation ( treeNode * parent );
treeNode * RL_rotation ( treeNode * parent );

// compare two heights and return the larger one.
int maximum ( int a , int b) {
  return a > b ? a : b;
}
// insert a node to the AVL tree
treeNode * Insert ( treeNode * currentNode , int key ){
  if ( currentNode == NULL ){
    #if DEBUG
      printf( "Added key %d\n" , key );
    #endif
    currentNode = ( treeNode *) malloc ( sizeof (treeNode) );
    currentNode -> key = key;
    currentNode -> left = currentNode -> right = NULL;
  } else if ( key > currentNode -> key ) {
    currentNode -> right = Insert ( currentNode -> right , key );
    currentNode = balanceTree ( currentNode );
  } else if ( key < currentNode -> key ) {
    currentNode -> left = Insert ( currentNode -> left , key );
    currentNode = balanceTree ( currentNode );
  } else {
    printf( "fail! - duplicated key\n" );
    exit(-1);
  }
  return currentNode;
}
// return the height of the tree (the height of the longest branch)
int getHeight ( treeNode * currentNode ){
  if ( currentNode == NULL ){
    return -1;
  }else{
    int height = 1 + maximum ( getHeight( currentNode -> right ) , getHeight( currentNode -> left ));
    return height;
  }
}
// return the difference of (left height - right height) // get_balance
int heightLeftMinusRight ( treeNode * currentNode ){
  if ( currentNode == NULL){
    return 0;
  }else{
    return getHeight ( currentNode -> left ) - getHeight ( currentNode -> right ) ;
  }
}
// to make the tree balanced.
treeNode * balanceTree ( treeNode * currentNode ){
  int Diff = heightLeftMinusRight ( currentNode );

  // when abs value of Diff exceed 1, it means the node is unbalanced
  if ( Diff > 1 ){
    if ( heightLeftMinusRight ( currentNode -> left ) > 0 ){ // Diff>0 means left-sub is taller
      // case 1 Right rotation
      currentNode = R_rotation ( currentNode );

    } else {
      // case 3 Double rotation: left + right
      currentNode = LR_rotation ( currentNode );
    }
  } else if ( Diff < -1 ){
    if ( heightLeftMinusRight ( currentNode -> right ) < 0 ){
      // case 2 Left rotation
      currentNode = L_rotation ( currentNode );
    } else {
      // case 4 Double rotation: right + left
      currentNode = RL_rotation ( currentNode );
    }
  }
  return currentNode;
}

treeNode * R_rotation ( treeNode * parent ) {
  #if DEBUG
    printf( "R_rotation on %d\n", parent -> key );
  #endif

  treeNode * child = parent -> left;
  // parent -> left = parent -> right = NULL;
  // child -> right = parent;

  parent -> left = child -> right;
  child -> right = parent;
  return child;
}
treeNode * L_rotation ( treeNode * parent ) {
  #if DEBUG
    printf( "L_rotation on %d\n", parent -> key );
  #endif

  treeNode * child = parent -> right;
  parent -> right = child -> left;
  child -> left = parent;
  return child;
}
treeNode * LR_rotation ( treeNode * parent ) {
  #if DEBUG
    printf( "LR_rotation on %d\n" , parent -> key );
  #endif

  treeNode * child = parent -> left;
  parent -> left = L_rotation ( child );
  return R_rotation ( parent );
}
treeNode * RL_rotation ( treeNode * parent ) {
  #if DEBUG
    printf( "RL_rotation on %d\n" , parent -> key );
  #endif

  treeNode * child = parent -> right;
  parent -> right = R_rotation ( child );
  return L_rotation ( parent );
}

int main() {
  treeNode * root = NULL;
  int input[9] = { 5, 4, 3, 7, 9, 1, 2, 14, 10 };
  for ( int i = 0 ; i < 9 ; i++ ){
    root = Insert ( root , input[i] );
  }
}
