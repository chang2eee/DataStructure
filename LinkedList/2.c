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
    insert(0, "��ü�������α׷���", "14:00");
    insert(1, "������ȸ��", "10:00");
    insert(2, "�ڷᱸ���׽ǽ�", "16:00");
    insert(3, "��ǻ�ͳ�Ʈ��ũ", "10:00");
    insert(4, "�ý��ۼ���Ʈ����", "10:00");
    insert(3, "������ȣ����", "10:00");
    printf("\n");

    delete("������ȸ��");
    printf("\n");

    Node* p = search("��ǻ�ͳ�Ʈ��ũ");
    printf("%s�� Ž���մϴ�.\n", p->name);
    printf("Ž���� ������ �����ð� = %s\n", p->classtime);
    printf("\n");

    printf("������û�� ��� ����\n");
    printf("\n");
    Node* tmp = head;
    while (tmp != NULL) {
        printf("���Ǹ�: %s, �ð�: %s\n", tmp->name, tmp->classtime);
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

int add_after(Node* prev, char* name, char* classtime) //������ 1, ���н� 0 ��ȯ
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

Node* remove_first() { //ù ��� ���� ��, �� ��� �ּ� ��ȯ
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
        printf("���Ǹ�: %s, �ð�: %s ������û �Ϸ�.\n", name, classtime);
        return 1;
    }
    Node* prev = get_node(index - 1);
    if (prev != NULL) {
        add_after(prev, name, classtime);
        printf("���Ǹ�: %s, �ð�: %s ������û �Ϸ�.\n", name, classtime);
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
    printf("%s ���ǰ� ���� ���.\n", name);
    if (p == NULL) return NULL;
    if (q == NULL) return remove_first();
    else
        return remove_after(q);
}