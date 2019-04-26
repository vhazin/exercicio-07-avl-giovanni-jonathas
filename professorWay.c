#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    int height;
    struct Node *left;
    struct Node *right;
    struct Node *father;
}node;

int max(int i,int j){
    int result = i;
    if(i < j){
        result = j;
    }
    return result;
}

int height(node *elem){
    int result = 0;
    if (elem != NULL){
        return elem -> height;
    }


}

int updateHeight(node *elem){
    int leftH,rightH;

    if(elem != NULL){
        leftH = height(elem ->right);
        rightH = height(elem -> right);
        elem -> height = max(leftH,rightH) + 1;
    }
}

node *simpleRotationLeft(node *root){
    node *aux = (node *)malloc(sizeof(node));
    aux = root -> right;

    root -> right = aux -> left;
    aux -> left = root;
    aux -> father = root -> father;
    root -> father = aux;
    root -> right -> father = root;
    updateHeight(root -> left);
    updateHeight(root);

    return aux;
}

node *simpleRotationRight(node *root){
    node *aux = (node *)malloc(sizeof(node));
    aux = root -> left;

    root -> left = aux -> right;
    aux -> right = root;
    aux -> father = root -> father;
    root -> father = aux;
    root -> left -> father = root;
    updateHeight(root -> right);
    updateHeight(root);
    
    return aux;
}

node *doubleRotationLeft(node *root){
    node *result = (node *)malloc(sizeof(node));

    root -> right = simpleRotationRight(root ->right);
    result = simpleRotationLeft(root);
    return result;
}


node *doubleRotationRight(node *root){
    node *result = (node *)malloc(sizeof(node));

    root -> left = simpleRotationRight(root ->left);
    result = simpleRotationRight(root);
    return result;
}

void insertAVL(int value,node *root){
    if(root == NULL){
        root = (node *)malloc(sizeof(node));
        root -> value = value;
        root -> left = NULL;
        root -> right = NULL;
        root -> height = 1;
    }
    else {
        if (value < root -> value){
            insertAVL (value, root->left);
            if((height(root -> left)) - (height(root -> right)) == 2){
                if( value < root -> left -> value){
                    simpleRotationRight(root);   
                }
                else {
                    doubleRotationRight(root);
                }
            }
        }
        else {
            insertAVL(value, root ->right);
            if((height(root -> right)) - (height(root -> left)) == 2){
                if( value > root -> right -> value){
                    simpleRotationLeft(root);   
                }
                else {
                    doubleRotationLeft(root);
                }
            }
        }
        updateHeight(root);
    }
}

node *getNode(node *root,int value){
    node *tmp = root;
    while (tmp != NULL){
        if(value >= tmp -> value){
            if(tmp -> value == value){
                return tmp;
            }
            else {
                tmp = tmp -> right;
            }
        }
        else if (value <= tmp -> value){
            if (tmp -> value == value){
                return tmp;
            }
            else {
                tmp = tmp -> left;
            }
        }
    }
    return tmp;
}

int main(void){
    node *root = (node*)malloc(sizeof(node));
    root-> right = NULL;

    int T, cmd, n;
    scanf("%d", &T);

    while(T--) {
        scanf("%d %d", &cmd, &n);
        if(cmd == 1){
            insertAVL(n,root);

        }
        else{ 
            printf("%d",root -> left ->value);
            // printf("%d",getNode(root,n)->height);
            // getNode(root -> right, n);
        }
    }
    return 0;
}