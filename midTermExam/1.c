#include <stdio.h>
#include <string.h>
#define MAX 100

struct sport {
    char* name;
};
typedef struct sport Mysport;

Mysport* mysports;
int n = 0;

void insert(char* name);
int search(char* name);
void delete(char* name);

int main(void) {
    mysports = (Mysport*)malloc(MAX * sizeof(Mysport));

    //����
    insert("�౸");
    insert("�߱�");
    insert("�豸");
    insert("�״Ͻ�");
    insert("��");
    insert("����");
    printf("\n");

    //����
    delete("��");
    printf("\n");

    //Ž��
    int index = search("�߱�");
    printf("%s Ž�� �Ϸ�\n", mysports[index].name);
    printf("\n");

    //�������� ����Ʈ ���
    printf("�����ϴ� � ����Ʈ\n");
    for (int i = 0; i < n; i++) {
        printf("���: %s\n", mysports[i].name);
    }

    return 0;
}
//
void insert(char* name) {
    mysports[n].name = name;
    n++;
    printf("���: %s ����Ʈ�� �߰� �Ϸ�.\n", name);
    return;

}
int search(char* name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(mysports[i].name, name) == 0)
            return i;
    }
    return -1;
}
void delete(char* name) {
    int index = search(name);
    if (index == -1) return;
    for (int i = index; i < n - 1; i++) {
        mysports[i].name = mysports[i + 1].name;
    }
    n--;
    printf("%s��(��) ����Ʈ���� ���� �Ϸ�.\n", name);
    return;
}