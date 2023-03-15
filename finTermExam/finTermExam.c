#include <stdio.h>
#include <stdlib.h>
#define LINE       printf("\n----------------------------------------\n");
#define show(x)    LINE; printf("     [현재까지의 이진 트리 출력]\n["); inorder(x); printf("]"); LINE;
#define MAX 100
int getMax(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

typedef struct Node {
	int data;
	int height; /*높이 필요하다*/
	struct Node* leftChild;
	struct Node* rightChild;
}Node;

void inorder(const Node* node) //중위 순회
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

/*모든 노드는 회전 수행 이후에 높이를 다시 계산*/
void setHeight(Node* node) {
	node->height = getMax(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
} /*둘 중 더 큰 자식의 높이에 1을 더한 값이 자신의 높이*/

int getDefference(Node* node) {
	if (node == NULL)
		return 0;
	Node* leftChild = node->leftChild;
	Node* rightChild = node->rightChild;
	return getHeight(leftChild) - getHeight(rightChild);
}

/*AVL트리의 LL회전*/
Node* rotateLL(Node* node) { 
	Node* leftChild = node->leftChild;
	node->leftChild = leftChild->rightChild;
	leftChild->rightChild = node;
	setHeight(node); /*회전 이후에 높이 재계산*/
	return leftChild; /*leftChild는 이후에 setHeight() 수행*/
}

/*AVL트리의 RR회전*/
Node* rotateRR(Node* node) {
	Node* rightChild = node->rightChild;
	node->rightChild = rightChild->leftChild;
	rightChild->leftChild = node;
	setHeight(node);
	return rightChild; /*rightChild는 이후에 setHeight() 수행*/
}

/*AVL트리의 LR회전*/
Node* rotateLR(Node* node) {
	Node* leftChild = node->leftChild;
	node->leftChild = rotateRR(leftChild);
	setHeight(node->leftChild);
	return rotateLL(node); /*rightChild는 이후에 setHeight() 수행*/
}

/*AVL트리의 RL회전*/
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
	setHeight(node); /*회전 이후에 높이 재계산*/
	return node;
}

Node* insertNode(Node* node, int data) {
	if (!node) {
		node = (Node*)malloc(sizeof(Node));
		node->data = data;
		node->height = 1;
		node->leftChild = node->rightChild = NULL;
		printf("입력된 값 : %d\n", data);
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
		printf("데이터 중복\n");

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

void preorder(const Node* node) //전위 순회
{
	if (node != NULL)
	{
		printf("%d  ", node->data);
		preorder(node->leftChild);
		preorder(node->rightChild);
	}
}

void postorder(const Node* node) //후위 순회
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
		printf("값 입력 (종료시 -1 입력) : ");
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
	printf("전위 순회: ");
	preorder(root);
	printf("\n\n중위 순회: ");
	inorder(root);
	printf("\n\n후위 순회: ");
	postorder(root);

	printf("\n");
}