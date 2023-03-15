#include <stdio.h>
#include <string.h>
#define NULL 0

struct myclass {
    char* name;
    char* classtime;
    struct myclass* next;

};
typedef struct myclass Node;

Node* head = NULL;

void add_first(char* name, char* classtime);
int add_after(Node* prev, char* name, char* classtime);
Node* remove_first();
Node* remove_after(Node* prev);
Node* search(char* word);
Node* get_node(int index);

int insert(int index, char* name, char* classtime);
Node* delete(char* item);
Node* search(char* word);


int main(void) {
    insert(0, "객체지향프로그래밍", "14:00");
    insert(1, "디지털회로", "10:00");
    insert(2, "자료구조및실습", "16:00");
    insert(3, "컴퓨터네트워크", "10:00");
    insert(4, "시스템소프트웨어", "10:00");
    insert(3, "정보보호공학", "10:00");
    printf("\n");

    delete("디지털회로");
    printf("\n");

    Node* p = search("컴퓨터네트워크");
    printf("%s를 탐색합니다.\n", p->name);
    printf("탐색한 과목의 수업시간 = %s\n", p->classtime);
    printf("\n");

    printf("수강신청한 모든 과목\n");
    printf("\n");
    Node* tmp = head;
    while (tmp != NULL) {
        printf("강의명: %s, 시간: %s\n", tmp->name, tmp->classtime);
        tmp = tmp->next;
    }

    return 0;
}

void add_first(char* name, char* classtime)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->name = name;
    temp->classtime = classtime;
    temp->next = head;
    head = temp;
}

int add_after(Node* prev, char* name, char* classtime) //성공시 1, 실패시 0 반환
{
    if (prev == NULL)
        return 0;
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->name = name;
    tmp->classtime = classtime;
    tmp->next = prev->next;
    prev->next = tmp;
    return 1;
}

Node* remove_first() { //첫 노드 삭제 후, 그 노드 주소 반환
    if (head == NULL) {
        return NULL;
    }
    else {
        Node* tmp = head;
        head = head->next;
        return tmp;
    }
}

Node* remove_after(Node* prev) {
    Node* tmp = prev->next;
    if (tmp == NULL) {
        return NULL;
    }
    else {
        prev->next = tmp->next;
        return tmp;
    }
}

Node* search(char* word) {
    Node* p = head;
    while (p != NULL) {
        if (strcmp(p->name, word) == 0) return p;
        p = p->next;
    }
    return NULL;
}

Node* get_node(int index) {
    if (index < 0)
        return NULL;
    Node* p = head;
    for (int i = 0; i < index && p != NULL; i++)
        p = p->next;
    return p;
}

int insert(int index, char* name, char* classtime) {
    if (index < 0)
        return 0;
    if (index == 0) {
        add_first(name, classtime);
        printf("강의명: %s, 시간: %s 수강신청 완료.\n", name, classtime);
        return 1;
    }
    Node* prev = get_node(index - 1);
    if (prev != NULL) {
        add_after(prev, name, classtime);
        printf("강의명: %s, 시간: %s 수강신청 완료.\n", name, classtime);
        return 1;
    }
    return 0;
}

Node* delete(char* name) {
    Node* p = head;
    Node* q = NULL;
    while (p != NULL && strcmp(p->name, name) != 0) {
        q = p;
        p = p->next;
    }
    printf("%s 강의가 수강 취소.\n", name);
    if (p == NULL) return NULL;
    if (q == NULL) return remove_first();
    else
        return remove_after(q);
}