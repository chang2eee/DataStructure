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

    //����
    Node* pre = NULL;
    add_after(pre, "�౸");
    add_after(pre, "�߱�");
    add_after(pre, "�豸");
    add_after(pre, "�״Ͻ�");
    add_after(pre, "��");
    add_after(pre, "����");
    printf("\n");

    //����
    delete("��");
    printf("\n");

    //Ž��
    Node* p = search("�߱�");
    

    //����Ʈ ���
    printf("�����ϴ� � ����Ʈ\n");
    Node* tmp = head;
    while (tmp != NULL) {
        printf("���: %s\n", tmp->name);
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
        printf("���: %s ����Ʈ�� �߰� �Ϸ�.\n", name);
    }
    else if (pre == NULL) // ���� ����Ʈ�� �� �տ� ����
    {
        new_node->next = head;    // ���ο� ��尡 ����Ʈ�� �� �տ� ��ġ
        head->prev = new_node;    // �� �� ����� ���� ��尡 ���ο� ���
        head = new_node;        // ���ο� ��尡 �� �� ��ġ�� ����
        printf("���: %s ����Ʈ�� �߰� �Ϸ�.\n", name);

    }
    else if (pre == tail) // ����Ʈ�� �� �ڿ� ����
    {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
        printf("���: %s ����Ʈ�� �߰� �Ϸ�.\n", name);
    }
    else // �� �յ� �� �ڵ� �ƴ� ��ġ�� ����� �ڿ� ����
    {
        new_node->prev = pre;
        pre->next->prev = new_node;
        new_node->next = pre->next;
        pre->next = new_node;
        printf("���: %s ����Ʈ�� �߰� �Ϸ�.\n", name);
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
        printf("%s��(��) ����Ʈ���� ���� �Ϸ�.\n", name);
    }
    else if (p->prev == NULL)    // p�� head�� ���
    {
        head = p->next;
        head->prev == NULL;
        free(p);
        printf("%s ��(��) ����Ʈ���� ���� �Ϸ�.\n", name);
    }
    else if (p->next == NULL)    // p�� tail�� ���
    {
        tail == p->prev;
        tail->next == NULL;
        free(p);
        printf("%s ��(��) ����Ʈ���� ���� �Ϸ�.\n", name);
    }
    else    // p�� �߰��� ��ġ�� ����� ���
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
        printf("%s ��(��) ����Ʈ���� ���� �Ϸ�.\n", name);
    }
}