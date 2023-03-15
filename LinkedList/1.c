#include <stdio.h>
#include <string.h>
#define MAX 10

struct myclass {
    char* name;
    char* classtime;
};
typedef struct myclass arr;

arr* myclasses;
int n = 0;

void insert(char* name, char* time);
int search(char* name);
void delete(char* name);

int main(void) {
    myclasses = (arr*)malloc(MAX * sizeof(arr));

    insert("��ü�������α׷���", "14:00");
    insert("������ȸ��", "10:00");
    insert("�ڷᱸ���׽ǽ�", "16:00");
    insert("��ǻ�ͳ�Ʈ��ũ", "10:00");
    insert("�ý��ۼ���Ʈ����", "10:00");
    insert("������ȣ����", "10:00");
    printf("\n");

    //����
    delete("������ȸ��");
    printf("\n");

    //Ž��
    int index = search("��ǻ�ͳ�Ʈ��ũ");
    printf("%s�� Ž���մϴ�.\n", myclasses[index].name);
    printf("Ž���� ������ �����ð� = %s\n\n", myclasses[index].classtime);

    //�������� ����Ʈ ���
    printf("������û�� ��� ����\n");
    for (int i = 0; i < n; i++) {
        printf("���Ǹ� : %s, �ð�: %s \n", myclasses[i].name, myclasses[i].classtime);
    }

    return 0;
}

void insert(char* name, char* time) {
    myclasses[n].name = name;
    myclasses[n].classtime = time;
    n++;
    printf("���Ǹ�: %s, �ð�: %s ������û �Ϸ�.\n", name, time);

    return 0;
}

int search(char* name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(myclasses[i].name, name) == 0)
            return i;
    }
    return 0;
}

void delete(char* name) {
    int index = search(name);
    if (index == -1)
        return 0;
    for (int i = index; i < n - 1; i++) {
        myclasses[i].name = myclasses[i + 1].name;
        myclasses[i].classtime = myclasses[i + 1].classtime;
    }
    n--;
    printf("%s ���� ���� ���.\n", name);
    return;
}