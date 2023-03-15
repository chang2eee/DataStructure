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
    Student data; // key ��
    struct AvlNode* left_child, * right_child;
}AvlNode;

AvlNode* root;


/* LL ȸ�� (���������� ȸ���Ѵ�)
     A
    /                B
   B        ->      / \
  /                C   A
 C

 ��2�� ������ A�� �θ� �ǰ� A->left_child�� B�� child�� �ȴ�.
 A->left�� B�� ������ �ִ� right_child�� �����ϰ� B�� right_child�� A�� �����Ѵ�. */

AvlNode* rotate_LL(AvlNode* parent)
{
    AvlNode* child = parent->left_child;
    parent->left_child = child->right_child;
    child->right_child = parent;
    return child;
}

/* RR ȸ�� (�������� ȸ���Ѵ�)
     A
      \               B
       B     ->      / \
        \           A   C
         C

 ��2�� ������ A�� �θ� �ǰ� A->right_child�� B�� child�� �ȴ�.
 A->right�� B�� ������ �ִ� left_child�� �����ϰ� B�� left_child�� A�� �����Ѵ�. */

AvlNode* rotate_RR(AvlNode* parent)
{
    AvlNode* child = parent->right_child;
    parent->right_child = child->left_child;
    child->left_child = parent;
    return child;
}

/* RL ȸ�� (������-�������� ȸ���Ѵ�)
     A                A
      \                \                C
       B      ->        C      ->      / \
      /                  \            A   B
     C                    B

 ��2�� ������ A�� �θ� �ǰ� A->right_child�� B�� child�� �ȴ�.
 A->right_child�� rotate_LL(B)�� ��ȯ�ϴ� ���� �����Ѵ�. (B,C�� ���� ������ ȸ��)
 rotate_LL(B)ȣ��� B�� C�� ��ȭ�� ����� �ٽ� rotate_RR(A)�� ȣ���ϸ� ����Ʈ���� �ȴ�. */

AvlNode* rotate_RL(AvlNode* parent)
{
    AvlNode* child = parent->right_child;
    parent->right_child = rotate_LL(child);
    return rotate_RR(parent);
}

/*LR ȸ�� (����-���������� ȸ���Ѵ�)
     A                 A
    /                 /                  C
   B         ->      C          ->      / \
    \               /                  A   B
     C             B

 ��2�� ������ A�� �θ� �ǰ� A->left_child�� B�� child�� �ȴ�.
 A->left_child�� rotate_RR(B)�� ��ȯ�ϴ� ���� �����Ѵ�. (B,C�� ���� ���� ȸ��)
 rotate_RR(B)ȣ��� B�� C�� ��ȭ�� ����� �ٽ� rotate_LL(A)�� ȣ���ϸ� ����Ʈ���� �ȴ�.*/

AvlNode* rotate_LR(AvlNode* parent)
{
    AvlNode* child = parent->left_child;
    parent->left_child = rotate_RR(child);
    return rotate_LL(parent);
}

// Ʈ���� ���� ���� �Լ�
// ��ȯȣ��� ������ ���̸� ���ϰ� �̵� �߿��� �� ū���� 1�� ���ϸ� Ʈ���� ���̰� �ȴ�.
int get_height(AvlNode* node)
{
    int height = 0;
    if (node != NULL)
        height = 1 + max(get_height(node->left_child), get_height(node->right_child));
    return height;
}

// ����� �����μ� ��ȯ �Լ�
// ���� ����Ʈ�� ���� - ������ ����Ʈ�� ����
int get_balance(AvlNode* node)
{
    if (node == NULL) return 0;
    return get_height(node->left_child) - get_height(node->right_child);
}

// ���� Ʈ���� ����� �Լ�
AvlNode* balance_tree(AvlNode** node)
{
    int height_diff = get_balance(*node);

    if (height_diff > 1) // ���� ����Ʈ���� ������ �����
    {
        if (get_balance((*node)->left_child) > 0)
            *node = rotate_LL(*node);
        else
            *node = rotate_LR(*node);
    }
    else if (height_diff < -1) // ������ ����Ʈ���� ������ �����
    {
        if (get_balance((*node)->right_child) < 0)
            *node = rotate_RR(*node);
        else
            *node = rotate_RL(*node);
    }
    return *node;
}

// AVL Ʈ���� ���� ����
// key�� ���� ��ȯȣ���� �ݺ��ϹǷν� Ʈ���� ���� �� �� ����ȭ �Լ��� ȣ���Ѵ�.
AvlNode* avl_add(AvlNode** root, Student key)
{
    if (*root == NULL)
    {
        *root = (AvlNode*)malloc(sizeof(AvlNode));
        if (*root == NULL)
        {
            printf("�޸� �Ҵ� ����\n");
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
        printf("�ߺ� Ű�� ���� ���� ����\n");
        exit(-1);
    }
    return *root;
}

// AVL Ʈ�� Ž�� �Լ�
// �Ϲ� ���� ���� Ʈ���� Ž�� �Լ��� ����. AVL�� ���� Ž�� Ʈ���� �����̴�.
AvlNode* avl_search(AvlNode* node, int ID)
{
    if (node == NULL) return NULL;

    //printf("%s %d %s->",node->data.name,node->data.ID,node->data.num);

    if (ID == node->data.ID) {
        printf("�й� %d �л��� �̸��� %s, ��ȭ��ȣ�� %s �Դϴ�.\n", node->data.ID, node->data.name, node->data.num);
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
    strcpy(a.name, "�躴â");
    strcpy(a.num, "01065373859");

    Student b;
    b.ID = 1112;
    strcpy(b.name, "������");
    strcpy(b.num, "01054882132");

    Student c;
    c.ID = 1113;
    strcpy(c.name, "���ȯ");
    strcpy(c.num, "01012155186");

    // ���ο� �л��� ���� �Է�
    if (avl_add(&root, a) != NULL)
        printf("�й�:%d, �̸�:%s, ��ȭ��ȣ:%s �л��� �ԷµǾ����ϴ�.\n", a.ID, a.name, a.num);
    if (avl_add(&root, b) != NULL)
        printf("�й�:%d, �̸�:%s, ��ȭ��ȣ:%s �л��� �ԷµǾ����ϴ�.\n", b.ID, b.name, b.num);
    if (avl_add(&root, c) != NULL)
        printf("�й�:%d, �̸�:%s, ��ȭ��ȣ:%s �л��� �ԷµǾ����ϴ�.\n", c.ID, c.name, c.num);

    printf("\n");
    // �й����� �л��� �̸� ��ȭ��ȣ ����ϴ� Ž��
    avl_search(root, 1111);

    printf("\n");
    //Ʈ�� ���� ��� (�Լ� get_heingt)
    printf("Ʈ���� ���̴� %d �Դϴ�.\n", get_height(root));

    printf("\n");

    //Ư�� �й��� �л� ����
    deletedd(root, b);
    printf("[�й� = %d]�л� ��带 �����Ͽ����ϴ�.\n", b.ID);

    return 0;
}