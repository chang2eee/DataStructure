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

    insert("객체지향프로그래밍", "14:00");
    insert("디지털회로", "10:00");
    insert("자료구조및실습", "16:00");
    insert("컴퓨터네트워크", "10:00");
    insert("시스템소프트웨어", "10:00");
    insert("정보보호공학", "10:00");
    printf("\n");

    //삭제
    delete("디지털회로");
    printf("\n");

    //탐색
    int index = search("컴퓨터네트워크");
    printf("%s를 탐색합니다.\n", myclasses[index].name);
    printf("탐색한 과목의 수업시간 = %s\n\n", myclasses[index].classtime);

    //수강과목 리스트 출력
    printf("수강신청한 모든 과목\n");
    for (int i = 0; i < n; i++) {
        printf("강의명 : %s, 시간: %s \n", myclasses[i].name, myclasses[i].classtime);
    }

    return 0;
}

void insert(char* name, char* time) {
    myclasses[n].name = name;
    myclasses[n].classtime = time;
    n++;
    printf("강의명: %s, 시간: %s 수강신청 완료.\n", name, time);

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
    printf("%s 강의 수강 취소.\n", name);
    return;
}