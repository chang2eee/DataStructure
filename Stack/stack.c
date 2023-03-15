#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element; //스택을 구조체로 정의

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

//스택 초기화 함수
void init_stack(StackType* s) {
	s->top = -1;
}

//공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}

//포화 상태 검출 함수
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

//삽입함수
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

//삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

//피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else  return s->data[s->top];
}

// 우선순위 지정
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

char infix_to_postfix(char* exp) //중위 표기식 -> 후위 표기식
{
	int i = 0;
	char ch, top_op, tf_exp[50];
	int len = strlen(exp);
	StackType s;

	init_stack(&s); //스택 초기화
	for (i = 0; i < len; i++) {
		ch = exp[i]; //연산자이면
		switch (ch) {
		case '+': case '-': case '*': case '/': //연산자
		//스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				printf("%c", pop(&s));
			push(&s, ch);
			break;
		case '(': // 왼쪽 소괄호일 때
			push(&s, ch);
			break;
		case ')': //오른쪽 소괄호
			top_op = pop(&s);
			//왼쪽 소괄호를 만날 때까지 출력
			while (top_op != '(') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		case '{': // 왼쪽 중괄호일 때
			push(&s, ch);
			break;
		case '}': //오른쪽 중괄호
			top_op = pop(&s);
			//왼쪽 중괄호를 만날 때까지 출력
			while (top_op != '{') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		case '[': // 왼쪽 대괄호일 때
			push(&s, ch);
			break;
		case ']': //오른쪽 대괄호
			top_op = pop(&s);
			//왼쪽 대괄호를 만날 때까지 출력
			while (top_op != '[') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		default: //피연산자
			printf("%c", ch);
			break;
		}
	}
	while (!is_empty(&s)) //스택에 저장된 연산자를 출력
		printf("%c", pop(&s));
	return 0;
}

//후위 표기식 계산 함수
int eval(char* exp) {
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch, top_op;
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0'; //입력이 피연산자이면
			push(&s, value);
		}
		else { //연산자이면 피연산자를 스택에서 제거
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //연산을 수행하고 스택에 저장
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
	printf("임의의 중위 표기식을 입력 : ");
	gets(exp);
	printf("후위 표기식으로 변경한 식 : ");
	infix_to_postfix(exp); //중위 표기식을 후위 표기식으로 표현
	printf("\n계산 수식 입력(후위 표기식으로 입력) : ");
	printf("후위 표기식 계산 결과 : %d\n", eval(gets(exp)));
	return 0;
}