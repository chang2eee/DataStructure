#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element; //������ ����ü�� ����

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

//���� �ʱ�ȭ �Լ�
void init_stack(StackType* s) {
	s->top = -1;
}

//���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

//��ȭ ���� ���� �Լ�
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

//�����Լ�
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

//�����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

//��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else  return s->data[s->top];
}

// �켱���� ����
int prec(char ch) {
	switch (ch) {
	case '(': case ')': return 2;
	case '{': case '}': return 1;
	case '[': case ']': return 0;
	case '+': case '-': return 3;
	case '*': case '/': return 4;
	}
	return -1;
}

char infix_to_postfix(char* exp) //���� ǥ��� -> ���� ǥ���
{
	int i = 0;
	char ch, top_op, tf_exp[50];
	int len = strlen(exp);
	StackType s;

	init_stack(&s); //���� �ʱ�ȭ
	for (i = 0; i < len; i++) {
		ch = exp[i]; //�������̸�
		switch (ch) {
		case '+': case '-': case '*': case '/': //������
		//���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				printf("%c", pop(&s));
			push(&s, ch);
			break;
		case '(': // ���� �Ұ�ȣ�� ��
			push(&s, ch);
			break;
		case ')': //������ �Ұ�ȣ
			top_op = pop(&s);
			//���� �Ұ�ȣ�� ���� ������ ���
			while (top_op != '(') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		case '{': // ���� �߰�ȣ�� ��
			push(&s, ch);
			break;
		case '}': //������ �߰�ȣ
			top_op = pop(&s);
			//���� �߰�ȣ�� ���� ������ ���
			while (top_op != '{') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		case '[': // ���� ���ȣ�� ��
			push(&s, ch);
			break;
		case ']': //������ ���ȣ
			top_op = pop(&s);
			//���� ���ȣ�� ���� ������ ���
			while (top_op != '[') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		default: //�ǿ�����
			printf("%c", ch);
			break;
		}
	}
	while (!is_empty(&s)) //���ÿ� ����� �����ڸ� ���
		printf("%c", pop(&s));
	return 0;
}

//���� ǥ��� ��� �Լ�
int eval(char* exp) {
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch, top_op;
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0'; //�Է��� �ǿ������̸�
			push(&s, value);
		}
		else { //�������̸� �ǿ����ڸ� ���ÿ��� ����
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //������ �����ϰ� ���ÿ� ����
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}

int main(void) {
	char exp[50];
	char s1[50], s2[50];
	printf("������ ���� ǥ����� �Է� : ");
	gets(exp);
	printf("���� ǥ������� ������ �� : ");
	infix_to_postfix(exp); //���� ǥ����� ���� ǥ������� ǥ��
	printf("\n��� ���� �Է�(���� ǥ������� �Է�) : ");
	printf("���� ǥ��� ��� ��� : %d\n", eval(gets(exp)));
	return 0;
}