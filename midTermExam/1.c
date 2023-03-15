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

    //삽입
    insert("축구");
    insert("야구");
    insert("배구");
    insert("테니스");
    insert("농구");
    insert("골프");
    printf("\n");

    //삭제
    delete("농구");
    printf("\n");

    //탐색
    int index = search("야구");
    printf("%s 탐색 완료\n", mysports[index].name);
    printf("\n");

    //수강과목 리스트 출력
    printf("좋아하는 운동 리스트\n");
    for (int i = 0; i < n; i++) {
        printf("운동명: %s\n", mysports[i].name);
    }

    return 0;
}
//
void insert(char* name) {
    mysports[n].name = name;
    n++;
    printf("운동명: %s 리스트에 추가 완료.\n", name);
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
    printf("%s이(가) 리스트에서 삭제 완료.\n", name);
    return;
}