#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NULL 0

struct sport {
    char* name;
    struct sport* next;
    struct sport* prev;
};
typedef struct sport Node;

Node* head = NULL;
Node* tail = NULL;
int size = 0;

void add_after(Node* pre, char* name);
Node* search(char* word);
void delete(char* name);

int main(void) {

    //삽입
    Node* pre = NULL;
    add_after(pre, "축구");
    add_after(pre, "야구");
    add_after(pre, "배구");
    add_after(pre, "테니스");
    add_after(pre, "농구");
    add_after(pre, "골프");
    printf("\n");

    //삭제
    delete("농구");
    printf("\n");

    //탐색
    Node* p = search("야구");
    

    //리스트 출력
    printf("좋아하는 운동 리스트\n");
    Node* tmp = head;
    while (tmp != NULL) {
        printf("운동명: %s\n", tmp->name);
        tmp = tmp->next;
    }

    return 0;
}

void add_after(Node* pre, char* name)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->name = name;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (pre == NULL && head == NULL)    // empty list
    {
        head = new_node;
        tail = new_node;
        printf("운동명: %s 리스트에 추가 완료.\n", name);
    }
    else if (pre == NULL) // 연결 리스트의 맨 앞에 삽입
    {
        new_node->next = head;    // 새로운 노드가 리스트의 맨 앞에 위치
        head->prev = new_node;    // 맨 앞 노드의 이전 노드가 새로운 노드
        head = new_node;        // 새로운 노드가 맨 앞 위치를 차지
        printf("운동명: %s 리스트에 추가 완료.\n", name);

    }
    else if (pre == tail) // 리스트의 맨 뒤에 삽입
    {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
        printf("운동명: %s 리스트에 추가 완료.\n", name);
    }
    else // 맨 앞도 맨 뒤도 아닌 위치의 노드의 뒤에 삽입
    {
        new_node->prev = pre;
        pre->next->prev = new_node;
        new_node->next = pre->next;
        pre->next = new_node;
        printf("운동명: %s 리스트에 추가 완료.\n", name);
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
        printf("%s이(가) 리스트에서 삭제 완료.\n", name);
    }
    else if (p->prev == NULL)    // p가 head인 경우
    {
        head = p->next;
        head->prev == NULL;
        free(p);
        printf("%s 이(가) 리스트에서 삭제 완료.\n", name);
    }
    else if (p->next == NULL)    // p가 tail인 경우
    {
        tail == p->prev;
        tail->next == NULL;
        free(p);
        printf("%s 이(가) 리스트에서 삭제 완료.\n", name);
    }
    else    // p가 중간에 위치한 노드인 경우
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
        printf("%s 이(가) 리스트에서 삭제 완료.\n", name);
    }
}