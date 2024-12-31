#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

enum status { RED, BLACK };

typedef struct __node {
    enum status color;
    char *ch;
    struct __node *left;
    struct __node *right;
} Node;

void RBTreePrint(Node * root, int nowLevel, int parantPrinter, int isLeft);
void RBTreeAdd(Node ** root, char * str, Node ** parant, Node ** anciant);
void changeAddColor(Node * root, Node ** anciant);
Node * RBTreeDelete(Node ** root, char * str, Node ** parant, Node ** anciant);
Node * findTreeParantNode(Node * root, Node * child);
void changeDeleteColor(Node * root, Node ** anciant);
// if str1 > str2 => -1, str1 == str2 => 0, str1 < str2 => 1
int strCompare(char * str1, char * str2);
// pointer input
void inputWithPointer(char ** str);
// get most string length in a level tree string value
void treeStringLengthCheck(Node * root);

int * maxLenMemo = NULL;
int lastLevel = 0;

int main(){
    Node * root = NULL;

    while(1){
        printf("MENU: 1. ADD 2. DELETE 3. QUIT ? ");
        int menu = 0;
        char * str;
        scanf("%d", &menu);
        while(getchar() != ’\n’);
        
        if(menu == 1){
            printf("ADD String: ");
            inputWithPointer(&str);
            RBTreeAdd(&root, str, NULL, &root);
            free(str);
        }
        else if(menu == 2){
            printf("DELETE String: ");
            inputWithPointer(&str);
            Node * tmpnode = RBTreeDelete(&root, str, NULL, &root);
            free(tmpnode->ch);
            free(tmpnode);
            free(str);
        }
        else if(menu == 3){
            printf("BYE˜!\n");
            break;
        }
        else{
            printf("Menu ERROR : %d Menu does not exist\n", menu);
            printf("Try Again.\n");
        }

        printf("Now Tree : \n\n");
        treeStringLengthCheck(root);
        RBTreePrint(root, 0, 0, 0);
        printf("\n");
    }
    return 0;
}

void printSpaceTimes(char c,int times){
    int i = 0;
    
    for(i = 0; i < times; i++){
        printf("%c", c);
    }
}

void RBTreePrint(Node * root, int nowLevel, int parantPrinted, int isLeft){
    if(root == NULL){
        printf("This tree is Empty\n");
        return;
    }

    if(!parantPrinted){
        int i;
        for(i = 0; i < nowLevel; i++){
            printSpaceTimes(’ ’,8 + *(maxLenMemo+i));
            printf("|");
        }
    }

    if(isLeft)
        printf(" â\224\224> %c: ", (root->color==RED?’R’:’B’));
    else
        printf(" -> %c: ", (root->color==RED?’R’:’B’));

    printf("%s", root->ch);
    printSpaceTimes(’ ’,*(maxLenMemo + nowLevel) - strlen(root->ch));
    printf(" |");

    if(root->right != NULL) {
        RBTreePrint(root->right, nowLevel+1, 1, 0);
    }
    else if(root->left != NULL){
        printf("-----");
    }

    if(root->left != NULL) {
        int i;
        if(root->right == NULL) printf("\n");
        RBTreePrint(root->left, nowLevel+1, 0, 1);
    }

    if(root->left == NULL && root->right == NULL) printf("\n");
}

void RBTreeAdd(Node ** root, char * str, Node ** parant, Node ** anciant){
    if(*root == NULL){
        (*root) = (Node*)malloc(sizeof(Node));
        (*root)->ch = (char*)malloc(sizeof(char) * strlen(str));

        strcpy((*root)->ch, str);
        
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->color = RED;

        printf("Tree Node Inserted\n\n");

        treeStringLengthCheck(*anciant);
        RBTreePrint(*anciant, 0, 0, 0);

        printf("\n");
        
        changeAddColor(*root, anciant);

        printf("Tree Color Changed\n\n");

        treeStringLengthCheck(*anciant);
        RBTreePrint(*anciant, 0, 0, 0);
        
        printf("\n");
    }
    else{
        int tmpCheck = strCompare((*root)->ch, str);

        switch(tmpCheck){
            case 1:
                RBTreeAdd(&((*root)->right), str, root, anciant);
                break;
            case -1:
                RBTreeAdd(&((*root)->left), str, root, anciant);
                break;
            case 0:
                printf("Aleady Added Key\n");
                return;
        }
    }
}

Node * findTwoChildParant(Node * root, Node * point){
    Node * twoChildParant = root;
    Node * now = root;
    
    while(now == point || now == NULL){
        if(now->right != NULL && now->right != NULL) twoChildParant = now;
            int tmpCheck = strCompare(now->ch, point->ch);

        switch(tmpCheck){
            case 1:
                now = now->right;
                break;
            case -1:
                now = now->left;
                break;
        }
    }

    return twoChildParant;
}

Node * RBTreeDelete(Node ** root, char * str, Node ** parant, Node ** anciant){
    Node * tmpNode = (Node*)malloc(sizeof(Node));
    tmpNode->ch = (char*)malloc(1);
    Node * changedNodePosition = NULL;
    int check = 0;

    if(strcmp((*root)->ch, str) == 0){
        if((*root)->left == NULL & (*root)->right == NULL){
            if(parant != NULL){
                if((*parant)->left == *root) (*parant)->left = NULL;
                else (*parant)->right = NULL;
            }
            
            if((*root)->color == BLACK)check = 1;
        }
        else if((*root)->left != NULL && (*root)->right == NULL){
            if(parant == NULL){
                *root = (*root)->left;
                (*root)->color = BLACK;
                return tmpNode;
            }

            changedNodePosition = (*root)->left;

            if((*root)->color == BLACK && changedNodePosition->color == RED) changedNodePosition->color = BLACK;
            else if((*root)->color == BLACK && changedNodePosition->color == BLACK) check = 1;

            if((*parant)->left == *root) (*parant)->left = changedNodePosition;
            else (*parant)->right = changedNodePosition;
        }
        else if((*root)->left == NULL && (*root)->right != NULL){
            if(parant == NULL){
                *root = (*root)->right;
                (*root)->color = BLACK;
                return tmpNode;
            }
            changedNodePosition = (*root)->right;

            if((*root)->color == BLACK && changedNodePosition->color == RED) changedNodePosition->color = BLACK;
            else if((*root)->color == BLACK && changedNodePosition->color == BLACK) check = 1;

            if((*parant)->left == *root) (*parant)->left = changedNodePosition;
            else (*parant)->right = changedNodePosition;
        }
        else{
            Node * findNextNode = (*root)->right;
            Node * findNodeParant = (*root);
            int n = 0;

            while(findNextNode->left != NULL){
                findNodeParant = findNextNode;
                findNextNode = findNextNode->left;
                n++;
            }

            if(findNextNode->right != NULL){
                if(findNextNode->right->color == RED && findNextNode->color == BLACK) findNextNode->right->color = BLACK;
            }
            else{
                if(findNextNode->color == RED) findNextNode->color = BLACK;
                else if((*root)->color = BLACK) check = 1;
            }

            if(n > 0){
                findNodeParant->left = findNextNode->right;
                findNextNode->right = (*root)->right;
            }

            findNextNode->left = (*root)->left;

            if(parant == NULL){
                *root = findNextNode;
                (*root)->color = BLACK;
                return tmpNode;
            }

            if((*parant)->left == *root) (*parant)->left = findNextNode;
            else (*parant)->right = findNextNode;
        }

        if(check == 1 && changedNodePosition != NULL){
            changeDeleteColor(*parant, anciant);
        }

        free(tmpNode->ch);
        free(tmpNode);
        return *root;
    }
    else{
        if((*root)->left == NULL && (*root)->right == NULL) {
            printf("Node With That Key Does Not Exist.\n");
            return tmpNode;
        }
        int tmpCheck = strCompare((*root)->ch, str);
        switch(tmpCheck){
            case 1:
                RBTreeDelete(&((*root)->right), str, root, anciant);
                break;
            case -1:
                RBTreeDelete(&((*root)->left), str, root, anciant);
                break;
        }
    }
    return tmpNode;
}

void changeDeleteColor(Node * root, Node ** anciant){
    if(root == NULL){
        (*anciant)->color = BLACK;
        return;
    }

    Node * parant = findTreeParantNode(*anciant, root);
    Node * now = root;

    while(parant->left == NULL || parant->right == NULL){
        if(parant->color == RED){
            parant->color == BLACK;
            return;
        }
        root = parant;
        parant = findTreeParantNode(*anciant, parant);
    }

    int nowInLeft = (parant->left == now) ? 1 : 0;
    Node * o_side = (nowInLeft) ? parant->right : parant->left;
    Node * o_sideLeft = o_side->left;
    Node * o_sideRight = o_side->right;
    Node * g_parant = findTreeParantNode(*anciant, root);

    if(parant->color == RED && o_side->color == BLACK){
        parant->color == BLACK;
        o_side->color == RED;
    }
    else if(parant->color == BLACK && o_side->color == BLACK && o_sideLeft->color == BLACK && o_sideRight->color == BLACK){
        o_side->color == RED;
        changeDeleteColor(parant, anciant);
    }
    else if(nowInLeft){
        if(o_sideRight->color == RED){
            o_side->color = parant->color;
            parant->color = BLACK;
            parant->right = o_sideLeft;
            o_side->left = parant;

            if(g_parant == NULL){
                (*anciant) = o_side;
                o_side->color = BLACK;
                return;
            }

            if(g_parant->left == parant) g_parant->left = o_side;
            else g_parant->right = o_side;
        }
        else if(o_sideLeft->color == RED){
            o_sideLeft->color = parant->color;
            o_side->color = RED;
            parant->color = BLACK;
            parant->left = o_sideLeft->left;
            o_side->left = o_sideLeft->right;
            o_sideLeft->left = parant;
            o_sideLeft->right = o_side;

            if(g_parant == NULL){
                (*anciant) = o_sideLeft;
                o_sideLeft->color = BLACK;
                return;
            }

            if(g_parant->left == parant) g_parant->left = o_sideLeft;
            else g_parant->right = o_sideLeft;
        }
        else if(o_side->color == RED && o_sideLeft->color == BLACK && o_sideRight->color == BLACK){
            o_sideLeft->color = RED;
            parant->color = BLACK;
            o_side->color = BLACK;
            o_side->left = parant;
            parant->right = o_sideLeft;

            if(g_parant == NULL){
                (*anciant) = o_side;
                o_side->color = BLACK;
                return;
            }

            if(g_parant->left == parant) g_parant->left = o_side;
            else g_parant->right = o_side;
        }
    }
    else{
        if(o_sideLeft->color == RED){
            o_side->color = parant->color;
            parant->color = BLACK;
            parant->right = o_sideRight;
            o_side->right = parant;

            if(g_parant == NULL){
                (*anciant) = o_side;
                o_side->color = BLACK;
                return;
            }

            if(g_parant->left == parant) g_parant->left = o_side;
            else g_parant->right = o_side;
        }
        else if(o_sideRight->color == RED){
            o_sideRight->color = parant->color;
            o_side->color = RED;
            parant->color = BLACK;
            parant->right = o_sideRight->right;
            o_side->right = o_sideRight->left;
            o_sideRight->right = parant;
            o_sideRight->left = o_side;

            if(g_parant == NULL){
                (*anciant) = o_sideRight;
                o_sideRight->color = BLACK;
                return;
            }

            if(g_parant->left == parant) g_parant->left = o_sideRight;
            else g_parant->right = o_sideRight;
        }
        else if(o_side->color == RED && o_sideLeft->color == BLACK &&
        o_sideRight->color == BLACK){
            o_sideRight->color = RED;
            parant->color = BLACK;
            o_side->color = BLACK;
            o_side->left = parant;
            parant->left = o_sideRight;
            if(g_parant == NULL){
                (*anciant) = o_side;
                o_side->color = BLACK;
                return;
            }
            if(g_parant->left == parant) g_parant->left = o_side;
            else g_parant->right = o_side;
        }
    }
    changeAddColor(parant, anciant);
}

void changeAddColor(Node * root, Node ** anciant){
    Node * parant = findTreeParantNode(*anciant, root);
    Node * g_parant = NULL;

    if(parant == NULL) {
        root->color = BLACK;
        return;
    }

    g_parant = findTreeParantNode(*anciant, parant);

    if(parant->color == RED && root->color == RED){
        int isParantLeft = (g_parant->left == parant) ? 1 : 0;
        int isRootLeft = 0;
        int check = 0;

        if(g_parant->right != NULL) {
            check+=1;
            if(g_parant->right->color == RED) check+=1;
        }

        if(g_parant->left != NULL) {
            check+=1;
            if(g_parant->left->color == RED) check+=1;
        }

        if(check == 4){
            g_parant->right->color = BLACK;
            g_parant->left->color = BLACK;
            g_parant->color = RED;
            changeAddColor(g_parant, anciant);
            return;
        }

        if(isParantLeft){
            isRootLeft = (parant->left == root) ? 1 : 0;
            Node * gg_parant = findTreeParantNode(*anciant, g_parant);
            if(!isRootLeft){
                g_parant->left = root->right;
                parant->right = root->left;
                root->right = g_parant;
                root->left = parant;
                root->color = BLACK;
                g_parant->color = RED;

                if(gg_parant == NULL){
                    (*anciant) = root;
                }
                else{
                    if(gg_parant->left == g_parant) gg_parant->left = root;
                    else gg_parant->right = root;
                }

                return;
            }
            g_parant->left = parant->right;
            parant->right = g_parant;
            parant->color = BLACK;
            g_parant->color = RED;

            if(gg_parant == NULL){
                (*anciant) = parant;
            }
            else{
                if(gg_parant->left == g_parant) gg_parant->left = parant;
                else gg_parant->right = parant;
            }
        }
        else{
            isRootLeft = (parant->left == root) ? 1 : 0;
            Node * gg_parant = findTreeParantNode(*anciant, g_parant);

            if(isRootLeft){
                g_parant->right = root->left;
                parant->left = root->right;
                root->left = g_parant;
                root->right = parant;
                root->color = BLACK;
                g_parant->color = RED;

                if(gg_parant == NULL){
                    (*anciant) = root;
                }
                else{
                    if(gg_parant->left == g_parant) gg_parant->left = root;
                    else gg_parant->right = root;
                }

                return;
            }
            g_parant->right = parant->left;
            parant->left = g_parant;
            parant->color = BLACK;
            g_parant->color = RED;

            if(gg_parant == NULL){
                (*anciant) = parant;
            }
            else{
                if(gg_parant->left == g_parant) gg_parant->left = parant;
                else gg_parant->right = parant;
            }
        }
    }
}

Node * findTreeParantNode(Node * root, Node * child){
    if(root == NULL) return NULL;
    if(root == child) return NULL;
    if(root->right == child || root->left == child)
        return root;

    else{
        int check = strCompare(root->ch, child->ch);

        switch(check){
            case 1:
                return findTreeParantNode(root->right, child);
            case -1:
                return findTreeParantNode(root->left, child);
            default:
                return NULL;
        }
    }
}

int strCompare(char * str1, char * str2){
    int i = 0;

    for(i = 0; (str1[i] != ’\0’ && str2[i] != ’\0’); i++){
        if(str1[i] > str2[i]) return -1;
        else if(str1[i] < str2[i]) return 1;
    }

    if(strlen(str1) > strlen(str2)) return -1;
    else if(strlen(str1) < strlen(str2)) return 1;
    else return 0;
}

void inputWithPointer(char ** str){
    *str = NULL;
    char tmp[10];
    int total_size = 0, size = 0;

    while(1){
        fgets(tmp, 8, stdin);
        size = strlen(tmp);
        total_size += size;

        if(*str == NULL){
            *str = (char *)malloc(total_size + 1);
            strcpy(*str, tmp);
        }
        else {
            *str = (char *)realloc(*str, total_size + 1);
            strcat(*str, tmp);
        }

        if(tmp[size - 1] == ’\n’){
            *(*str+total_size-1) = 0;
            break;
        }
    }
}

int getLevelStringMax(Node * root, int level){
    if(root == NULL)
        return 0;
    
    if(level == 0)
        return strlen(root->ch);
    else{
        int left = getLevelStringMax(root->left, (level-1));
        int right = getLevelStringMax(root->right, (level-1));
        return (left > right ? left : right);
    }
}

int getMaxLevel(Node * root, int nowLevel){
    if(root == NULL) return (nowLevel-1);
    else{
        int left = getMaxLevel(root->left, (nowLevel+1));
        int right = getMaxLevel(root->right, (nowLevel+1));
        return (left > right ? left : right);
    }
}

void treeStringLengthCheck(Node * root){
    int max = getMaxLevel(root, 0), i;
    if(maxLenMemo == NULL) maxLenMemo = (int*)malloc(sizeof(int) * max);
    else if(lastLevel != max){
        free(maxLenMemo);
        maxLenMemo = (int*)malloc(sizeof(int) * max);
    }
    for(i = 0; i <= max; i++)
        *(maxLenMemo+i) = getLevelStringMax(root, i);
}