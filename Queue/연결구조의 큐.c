#include <stdio.h>
#define MAX 100
#define true 1
#define false 0
int front = -1;
int rear = -1;
int queue[MAX];

int IsEmpty(void) {
    if (front == rear)
        return true;
    else return false;
}
int IsFull(void) {
    int tmp = (rear + 1) % MAX;
    if (tmp == front)
        return true;
    else
        return false;
}
void addQ(int value) {
    if (IsFull())
        printf("ť�� ��ȭ�����̴�.\n");
    else {
        rear = (rear + 1) % MAX;
        queue[rear] = value;
    }

}

int deleteQ() {
    if (IsEmpty())
        printf("ť�� �����.\n");
    else {
        front = (front + 1) % MAX;
        return queue[front];
    }
    return 0;
}

int count() { 
    return rear - front;
}

void printQ() {
    printf("ť ����\n");
    for (int i = front + 1; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main() {
    int i = 1;
    char select;

    while (1)
    {
        printf("Insert�� A/a, Delete�� L/l Quit�� Q/q �Է�\n");
        scanf("%c", &select);

        if (select == 'A' || select == 'a')
        {
            addQ(i);
            i++;
            printQ();
            printf("\n");
        }
        else if (select == 'L' || select == 'l')
        {
            printf("�������� %d�� �Դϴ�.\n", deleteQ());
            printQ();
            printf("\n");
        }
        else if (select == 'Q' || select == 'q')
            break;
        getchar();
    }

    printf("�� ����ο��� %d�� �Դϴ�.\n", count());
    printQ();

    return 0;
}