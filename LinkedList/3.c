#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NULL 0

struct myclass {
    char* name;
    char* classtime;
    struct myclass* next;
    struct myclass* prev;
};
typedef struct myclass Node;

Node* head = NULL;
Node* tail = NULL;
int size = 0;

void add_after(Node* pre, char* name, char* classtime);
Node* search(char* word);
void delete(char* name);

int main(void) {

    Node* pre = NULL;
    add_after(pre, "객체지향프로그래밍", "14:00");
    add_after(pre, "디지털회로", "10:00");
    add_after(pre, "자료구조및실습", "16:00");
    add_after(pre, "컴퓨터네트워크", "10:00");
    add_after(pre, "시스템소프트웨어", "10:00");
    add_after(pre, "정보보호공학", "10:00");
    printf("\n");
     
    delete("디지털회로");
    printf("\n");
  
    Node* p = search("컴퓨터네트워크");
    printf("%s를 탐색합니다.\n", p->name);
    printf("탐색한 과목의 수업시간 = %s\n", p->classtime);
    printf("\n");

    //수강과목 리스트 출력
    printf("수강신청한 모든 과목\n");
    Node* tmp = head;
    while (tmp != NULL) {
        printf("강의명: %s, 시간: %s\n", tmp->name, tmp->classtime);
        tmp = tmp->next;
    }

    return 0;
}

void add_after(Node* pre, char* name, char* time)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->name = name;
    new_node->classtime = time;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (pre == NULL && head == NULL)    // empty list
    {
        head = new_node;
        tail = new_node;
        printf("강의명: %s, 시간: %s 수강신청 완료.\n", name, time);
    }
    else if (pre == NULL) // 연결 리스트의 맨 앞에 삽입
    {
        new_node->next = head;    // 새로운 노드가 리스트의 맨 앞에 위치
        head->prev = new_node;    // 맨 앞 노드의 이전 노드가 새로운 노드
        head = new_node;        // 새로운 노드가 맨 앞 위치를 차지
        printf("강의명: %s, 시간: %s 수강신청 완료.\n", name, time);

    }
    else if (pre == tail) // 리스트의 맨 뒤에 삽입
    {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
        printf("강의명: %s, 시간: %s 수강신청 완료.\n", name, time);
    }
    else // 맨 앞도 맨 뒤도 아닌 위치의 노드의 뒤에 삽입
    {
        new_node->prev = pre;
        pre->next->prev = new_node;
        new_node->next = pre->next;
        pre->next = new_node;
        printf("강의명: %s, 시간: %s 수강신청 완료.\n", name, time);
    }
    size++;    // 노드의 개수 증가
}


Node* search(char* word) {
    Node* p = head;
    while (p != NULL) {
        if (strcmp(p->name, word) == 0) return p;
        p = p->next;

    }
    return NULL;
}

void delete(char* name) {
    Node* p = search(name);
    if (p->prev == NULL && p->next == NULL)    // p가 유일한 노드
    {
        head == NULL;
        tail == NULL;
        free(p);
        printf("%s 강의가 수강 취소.\n", name);
    }
    else if (p->prev == NULL)    // p가 head인 경우
    {
        head = p->next;
        head->prev == NULL;
        free(p);
        printf("%s 강의가 수강 취소.\n", name);
    }
    else if (p->next == NULL)    // p가 tail인 경우
    {
        tail == p->prev;
        tail->next == NULL;
        free(p);
        printf("%s 강의가 수강 취소.\n", name);
    }
    else    // p가 중간에 위치한 노드인 경우
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
        printf("%s강의가 수강 취소.\n", name);
    }
}