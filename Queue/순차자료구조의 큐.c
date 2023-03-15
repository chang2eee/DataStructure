#include <stdio.h>
#define MAX 100
#define true 1
#define false 0
int front = -1;
int rear = -1;
int n = 100;
int queue[MAX];

int IsEmpty(void) {
    if (front == rear)
        return true;
    else
        return false;
}

int IsFull(void) {
    if (rear == n - 1)
        return true;
    else
        return false;
}

void addQ(int value) {
    if (IsFull())
        printf("큐가 포화상태이다.\n");
    else {
        rear = rear + 1;
        queue[rear] = value;
    }
}

int deleteQ() {
    if (IsEmpty())
        printf("큐가 비었다.\n");
    else {
        front = front + 1;
        return queue[front];
    }
    return 0;
}

int count() {
    return rear - front;
}

void printQ() {
    printf("큐 상태\n");
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
        printf("Insert는 A/a, Delete는 L/l Quit은 Q/q 입력\n");
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
            printf("다음분은 %d번 입니다.\n", deleteQ());
            printQ();
            printf("\n");
        }
        else if (select == 'Q' || select == 'q')
            break;
        getchar();
    }

    printf("총 대기인원은 %d명 입니다.\n", count());
    printQ();

    return 0;
}