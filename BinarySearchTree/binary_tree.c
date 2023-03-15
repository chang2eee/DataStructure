#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define MAX 11
//#define NULL 0

typedef struct student
{
    char name[MAX];
    int ID;
    char num[MAX];
}Student;

typedef struct AvlNode
{
    Student data; // key 값
    struct AvlNode* left_child, * right_child;
}AvlNode;

AvlNode* root;


/* LL 회전 (오른쪽으로 회전한다)
     A
    /                B
   B        ->      / \
  /                C   A
 C

 ±2를 가지는 A가 부모가 되고 A->left_child인 B가 child가 된다.
 A->left에 B가 가지고 있는 right_child를 대입하고 B의 right_child에 A을 대입한다. */

AvlNode* rotate_LL(AvlNode* parent)
{
    AvlNode* child = parent->left_child;
    parent->left_child = child->right_child;
    child->right_child = parent;
    return child;
}

/* RR 회전 (왼쪽으로 회전한다)
     A
      \               B
       B     ->      / \
        \           A   C
         C

 ±2를 가지는 A가 부모가 되고 A->right_child인 B가 child가 된다.
 A->right에 B가 가지고 있는 left_child를 대입하고 B의 left_child에 A을 대입한다. */

AvlNode* rotate_RR(AvlNode* parent)
{
    AvlNode* child = parent->right_child;
    parent->right_child = child->left_child;
    child->left_child = parent;
    return child;
}

/* RL 회전 (오른쪽-왼쪽으로 회전한다)
     A                A
      \                \                C
       B      ->        C      ->      / \
      /                  \            A   B
     C                    B

 ±2를 가지는 A가 부모가 되고 A->right_child인 B가 child가 된다.
 A->right_child에 rotate_LL(B)가 반환하는 값을 대입한다. (B,C에 대해 오른쪽 회전)
 rotate_LL(B)호출시 B와 C가 변화가 생기고 다시 rotate_RR(A)을 호출하면 균형트리가 된다. */

AvlNode* rotate_RL(AvlNode* parent)
{
    AvlNode* child = parent->right_child;
    parent->right_child = rotate_LL(child);
    return rotate_RR(parent);
}

/*LR 회전 (왼쪽-오른쪽으로 회전한다)
     A                 A
    /                 /                  C
   B         ->      C          ->      / \
    \               /                  A   B
     C             B

 ±2를 가지는 A가 부모가 되고 A->left_child인 B가 child가 된다.
 A->left_child에 rotate_RR(B)가 반환하는 값을 대입한다. (B,C에 대해 왼쪽 회전)
 rotate_RR(B)호출시 B와 C가 변화가 생기고 다시 rotate_LL(A)을 호출하면 균형트리가 된다.*/

AvlNode* rotate_LR(AvlNode* parent)
{
    AvlNode* child = parent->left_child;
    parent->left_child = rotate_RR(child);
    return rotate_LL(parent);
}

// 트리의 높이 측정 함수
// 순환호출로 각각의 높이를 구하고 이들 중에서 더 큰값에 1을 더하면 트리의 높이가 된다.
int get_height(AvlNode* node)
{
    int height = 0;
    if (node != NULL)
        height = 1 + max(get_height(node->left_child), get_height(node->right_child));
    return height;
}

// 노드의 균형인수 반환 함수
// 왼쪽 서브트리 높이 - 오른쪽 서브트리 높이
int get_balance(AvlNode* node)
{
    if (node == NULL) return 0;
    return get_height(node->left_child) - get_height(node->right_child);
}

// 균형 트리를 만드는 함수
AvlNode* balance_tree(AvlNode** node)
{
    int height_diff = get_balance(*node);

    if (height_diff > 1) // 왼쪽 서브트리의 균형을 맞춘다
    {
        if (get_balance((*node)->left_child) > 0)
            *node = rotate_LL(*node);
        else
            *node = rotate_LR(*node);
    }
    else if (height_diff < -1) // 오른쪽 서브트리의 균형을 맞춘다
    {
        if (get_balance((*node)->right_child) < 0)
            *node = rotate_RR(*node);
        else
            *node = rotate_RL(*node);
    }
    return *node;
}

// AVL 트리의 삽입 연산
// key에 대해 순환호출을 반복하므로써 트리에 삽입 한 후 균형화 함수를 호출한다.
AvlNode* avl_add(AvlNode** root, Student key)
{
    if (*root == NULL)
    {
        *root = (AvlNode*)malloc(sizeof(AvlNode));
        if (*root == NULL)
        {
            printf("메모리 할당 실패\n");
            exit(-1);
        }
        (*root)->data.ID = key.ID;
        strcpy((*root)->data.name, key.name);
        strcpy((*root)->data.num, key.num);
        (*root)->left_child = (*root)->right_child = NULL;

    }

    else if (key.ID < (*root)->data.ID)
    {
        (*root)->left_child = avl_add(&((*root)->left_child), key);
        (*root) = balance_tree(root);
    }
    else if (key.ID > (*root)->data.ID)
    {
        (*root)->right_child = avl_add(&((*root)->right_child), key);
        (*root) = balance_tree(root);
    }
    else
    {
        printf("중복 키로 인한 삽입 실패\n");
        exit(-1);
    }
    return *root;
}

// AVL 트리 탐색 함수
// 일반 적인 이진 트리의 탐색 함수와 같다. AVL도 이진 탐색 트리의 일종이다.
AvlNode* avl_search(AvlNode* node, int ID)
{
    if (node == NULL) return NULL;

    //printf("%s %d %s->",node->data.name,node->data.ID,node->data.num);

    if (ID == node->data.ID) {
        printf("학번 %d 학생의 이름은 %s, 전화번호는 %s 입니다.\n", node->data.ID, node->data.name, node->data.num);
        return node;
    }
    else if (ID < node->data.ID)
        avl_search(node->left_child, ID);
    else
        avl_search(node->right_child, ID);
    return NULL;
}

void deletetree(AvlNode* bt) {
    if (bt == NULL)
        return;

    deletetree(bt->left_child);
    deletetree(bt->right_child);

    printf("delete the Node : %d", bt->data.ID);

    free(bt);
}

AvlNode* deletedd(AvlNode* root, Student key)
{
    AvlNode* remove_node = root;
    if (root == NULL) {
        return root;
    }
    if (key.ID < root->data.ID) {
        root->left_child = deletedd(root->left_child, key);
    }
    else if (key.ID > root->data.ID) {
        root->right_child = deletedd(root->right_child, key);
    }
    else {
        if ((root->left_child == NULL) && (root->right_child != NULL)) {
            remove_node = root->right_child;
            *root = *remove_node;
            deletetree(remove_node); // this is for free-ing the memory
        }
        else if ((root->right_child == NULL) && (root->left_child != NULL)) {
            remove_node = root->left_child;
            *root = *remove_node;
            deletetree(remove_node);
        }
        else if ((root->right_child == NULL) && (root->left_child == NULL)) {
            remove_node = root;
            root = NULL;
        }
        else {
            //remove_node = successor(root);
            root->data = remove_node->data;
            root->right_child = deletedd(root->right_child, remove_node->data);
        }
    }

    if (root == NULL) {
        return root;

        if (get_balance(root) == 2) {
            if (get_balance(root->left_child) == -1) {
                return rotate_RL(root);
            }
            else if (get_balance(root->left_child) == 1) {
                return rotate_LL(root);
            }
        }
        if (get_balance(root) == -2) {
            if (get_balance(root->right_child) == -1) {
                return rotate_LR(root);
            }
            else if (get_balance(root->right_child) == 1) {
                return rotate_RR(root);
            }
        }
    }
    return root;
}



int main()
{
    Student a;
    a.ID = 1111;
    strcpy(a.name, "김병창");
    strcpy(a.num, "01065373859");

    Student b;
    b.ID = 1112;
    strcpy(b.name, "최혁준");
    strcpy(b.num, "01054882132");

    Student c;
    c.ID = 1113;
    strcpy(c.name, "김대환");
    strcpy(c.num, "01012155186");

    // 새로운 학생의 정보 입력
    if (avl_add(&root, a) != NULL)
        printf("학번:%d, 이름:%s, 전화번호:%s 학생이 입력되었습니다.\n", a.ID, a.name, a.num);
    if (avl_add(&root, b) != NULL)
        printf("학번:%d, 이름:%s, 전화번호:%s 학생이 입력되었습니다.\n", b.ID, b.name, b.num);
    if (avl_add(&root, c) != NULL)
        printf("학번:%d, 이름:%s, 전화번호:%s 학생이 입력되었습니다.\n", c.ID, c.name, c.num);

    printf("\n");
    // 학번으로 학생의 이름 전화번호 출력하는 탐색
    avl_search(root, 1111);

    printf("\n");
    //트리 높이 출력 (함수 get_heingt)
    printf("트리의 높이는 %d 입니다.\n", get_height(root));

    printf("\n");

    //특정 학번의 학생 삭제
    deletedd(root, b);
    printf("[학번 = %d]학생 노드를 삭제하였습니다.\n", b.ID);

    return 0;
}