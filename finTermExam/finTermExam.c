#include <stdio.h>
#include <stdlib.h>
#define LINE       printf("\n----------------------------------------\n");
#define show(x)    LINE; printf("     [��������� ���� Ʈ�� ���]\n["); inorder(x); printf("]"); LINE;
#define MAX 100
int getMax(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

typedef struct Node {
	int data;
	int height; /*���� �ʿ��ϴ�*/
	struct Node* leftChild;
	struct Node* rightChild;
}Node;

void inorder(const Node* node) //���� ��ȸ
{
	if (node != NULL) {
		inorder(node->leftChild);
		printf("%d ", node->data);
		inorder(node->rightChild);
	}
}

int getHeight(Node* node) {
	if (node == NULL)
		return 0;
	return node->height;
}

/*��� ���� ȸ�� ���� ���Ŀ� ���̸� �ٽ� ���*/
void setHeight(Node* node) {
	node->height = getMax(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
} /*�� �� �� ū �ڽ��� ���̿� 1�� ���� ���� �ڽ��� ����*/

int getDefference(Node* node) {
	if (node == NULL)
		return 0;
	Node* leftChild = node->leftChild;
	Node* rightChild = node->rightChild;
	return getHeight(leftChild) - getHeight(rightChild);
}

/*AVLƮ���� LLȸ��*/
Node* rotateLL(Node* node) { 
	Node* leftChild = node->leftChild;
	node->leftChild = leftChild->rightChild;
	leftChild->rightChild = node;
	setHeight(node); /*ȸ�� ���Ŀ� ���� ����*/
	return leftChild; /*leftChild�� ���Ŀ� setHeight() ����*/
}

/*AVLƮ���� RRȸ��*/
Node* rotateRR(Node* node) {
	Node* rightChild = node->rightChild;
	node->rightChild = rightChild->leftChild;
	rightChild->leftChild = node;
	setHeight(node);
	return rightChild; /*rightChild�� ���Ŀ� setHeight() ����*/
}

/*AVLƮ���� LRȸ��*/
Node* rotateLR(Node* node) {
	Node* leftChild = node->leftChild;
	node->leftChild = rotateRR(leftChild);
	setHeight(node->leftChild);
	return rotateLL(node); /*rightChild�� ���Ŀ� setHeight() ����*/
}

/*AVLƮ���� RLȸ��*/
Node* rotateRL(Node* node) {
	Node* rightChild = node->rightChild;
	node->rightChild = rotateLL(rightChild);
	setHeight(node->rightChild);
	return rotateRR(node);
}

Node* balance(Node* node) {
	int difference = getDefference(node);
	if (difference >= 2) {
		if (getDefference(node->leftChild) >= 1)
			node = rotateLL(node);
		else
			node = rotateLR(node);
	}
	else if (difference <= -2) {
		if (getDefference(node->rightChild) <= -1)
			node = rotateRR(node);
		else
			node = rotateRL(node);
	}
	setHeight(node); /*ȸ�� ���Ŀ� ���� ����*/
	return node;
}

Node* insertNode(Node* node, int data) {
	if (!node) {
		node = (Node*)malloc(sizeof(Node));
		node->data = data;
		node->height = 1;
		node->leftChild = node->rightChild = NULL;
		printf("�Էµ� �� : %d\n", data);
	}
	else if (data < node->data) {
		node->leftChild = insertNode(node->leftChild, data);
		node = balance(node);
	}
	else if (data > node->data) {
		node->rightChild = insertNode(node->rightChild, data);
		node = balance(node);
	}
	else
		printf("������ �ߺ�\n");

	return node;
}

Node* root = NULL;

void display(Node* node, int level) {
	if (node != NULL) {
		display(node->rightChild, level + 1);
		printf("\n");
		if (node == root)
			printf("Root : ");
		for (int i = 0; i < level && node != root; i++)
			printf("	");
		printf("%d(%d)", node->data, getHeight(node));
		display(node->leftChild, level + 1);
	}
}

void preorder(const Node* node) //���� ��ȸ
{
	if (node != NULL)
	{
		printf("%d  ", node->data);
		preorder(node->leftChild);
		preorder(node->rightChild);
	}
}

void postorder(const Node* node) //���� ��ȸ
{
	if (node != NULL)
	{
		postorder(node->leftChild);
		postorder(node->rightChild);
		printf("%d  ", node->data);
	}
}

int main(void) {
	int count = 0;
	int A[MAX];

	while (1) {
		printf("�� �Է� (����� -1 �Է�) : ");
		scanf("%d", &A[count]);
		if (A[count] == -1)
			break;
		else {
			count++;
		}
	}
	printf("\n\n");

	for (int i = 0; i < count; i++) {
		root = insertNode(root, A[i]);
		show(root);
		display(root, 1);
		printf("\n");
	}

	printf("\n");
	printf("���� ��ȸ: ");
	preorder(root);
	printf("\n\n���� ��ȸ: ");
	inorder(root);
	printf("\n\n���� ��ȸ: ");
	postorder(root);

	printf("\n");
}