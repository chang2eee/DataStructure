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
    add_after(pre, "��ü�������α׷���", "14:00");
    add_after(pre, "������ȸ��", "10:00");
    add_after(pre, "�ڷᱸ���׽ǽ�", "16:00");
    add_after(pre, "��ǻ�ͳ�Ʈ��ũ", "10:00");
    add_after(pre, "�ý��ۼ���Ʈ����", "10:00");
    add_after(pre, "������ȣ����", "10:00");
    printf("\n");
     
    delete("������ȸ��");
    printf("\n");
  
    Node* p = search("��ǻ�ͳ�Ʈ��ũ");
    printf("%s�� Ž���մϴ�.\n", p->name);
    printf("Ž���� ������ �����ð� = %s\n", p->classtime);
    printf("\n");

    //�������� ����Ʈ ���
    printf("������û�� ��� ����\n");
    Node* tmp = head;
    while (tmp != NULL) {
        printf("���Ǹ�: %s, �ð�: %s\n", tmp->name, tmp->classtime);
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
        printf("���Ǹ�: %s, �ð�: %s ������û �Ϸ�.\n", name, time);
    }
    else if (pre == NULL) // ���� ����Ʈ�� �� �տ� ����
    {
        new_node->next = head;    // ���ο� ��尡 ����Ʈ�� �� �տ� ��ġ
        head->prev = new_node;    // �� �� ����� ���� ��尡 ���ο� ���
        head = new_node;        // ���ο� ��尡 �� �� ��ġ�� ����
        printf("���Ǹ�: %s, �ð�: %s ������û �Ϸ�.\n", name, time);

    }
    else if (pre == tail) // ����Ʈ�� �� �ڿ� ����
    {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
        printf("���Ǹ�: %s, �ð�: %s ������û �Ϸ�.\n", name, time);
    }
    else // �� �յ� �� �ڵ� �ƴ� ��ġ�� ����� �ڿ� ����
    {
        new_node->prev = pre;
        pre->next->prev = new_node;
        new_node->next = pre->next;
        pre->next = new_node;
        printf("���Ǹ�: %s, �ð�: %s ������û �Ϸ�.\n", name, time);
    }
    size++;    // ����� ���� ����
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
    if (p->prev == NULL && p->next == NULL)    // p�� ������ ���
    {
        head == NULL;
        tail == NULL;
        free(p);
        printf("%s ���ǰ� ���� ���.\n", name);
    }
    else if (p->prev == NULL)    // p�� head�� ���
    {
        head = p->next;
        head->prev == NULL;
        free(p);
        printf("%s ���ǰ� ���� ���.\n", name);
    }
    else if (p->next == NULL)    // p�� tail�� ���
    {
        tail == p->prev;
        tail->next == NULL;
        free(p);
        printf("%s ���ǰ� ���� ���.\n", name);
    }
    else    // p�� �߰��� ��ġ�� ����� ���
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
        printf("%s���ǰ� ���� ���.\n", name);
    }
}