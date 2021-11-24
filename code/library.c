#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct users { //회원구조체
	int num;			//회원 번호
	char name[10];		//회원 이름
	char** borrow_list;	//회원 대출목록
	int borrow_num;		//대출권수
}users;

typedef struct book { //책구조체
	char title[20];		//책 제목
	int num;			//책 번호
}book;


void book_load();		//메모장에서 회원목록을 불러와 동적배열에 옮기는 함수
void users_load();		//메모장에서 도서목록을 ~~~~
int menu();				//메뉴를 선택하는 함수
void show_users();		//동적배열에 저장된 회원정보를 화면에 출력하는 함수
void show_books();		//동적배열에 저장된 도서목록을 ~~~
void users_new();		//동적배열을 증가시키고, 새로운 회원정보를 입력하는 함수
void book_new();		//동적배열을 증가시키고, 새로운 도서정보를 ~~
void users_save();		//동적배열에 저장된 회원정보를 메모장으로 저장하는 함수
void book_save();		//동적배열에 저장된 도서정보를 메모장으로 저장하는 함수
void book_control();	//대출/반납인지 정하는 함수
void book_borrow();		//빌리려는 책의 제목을 회원구조체의 멤버변수로 추가
void book_return();		//반납하려는 책의 제목을 회원구조체의 멤버변수에서 제거

int book_cnt = 0; //현재 프로그램에 저장된 책의 권수
int users_cnt = 0;//현재 프로그램에 저장된 회원 수

book* book_data = NULL;//책의 목록
users* users_data = NULL;//회원 목록

void main() {
	book_data = (book*)malloc(sizeof(book));
	users_data = (users*)malloc(sizeof(users));


	book_load();
	users_load();

	while (1) {
		switch (menu()) {
		case 1:
			show_users();
			break;
		case 2:
			show_books();
			break;
		case 3:
			users_new();
			break;
		case 4:
			book_new();
			break;
		case 5:
			book_control();
			break;
		case 6:
			free(users_data);
			free(book_data);
			printf("종료\n");
			system("pause");
			return;
		default:
			printf("다시 선택해주세요\n");
			break;
		}
		system("cls");
	}
}

int menu() {
	int sel;
	printf("=====메뉴선택=====\n");
	printf("1. 전체회원정보보기\n");
	printf("2. 등록 서적 보기\n");
	printf("3. 회원등록\n");
	printf("4. 도서등록\n");
	printf("5. 대출관리\n");
	printf("6. 종료\n");
	printf("선택 = ");
	scanf("%d", &sel);
	return sel;
}

void users_load() {
	FILE* fp;

	fp = fopen("C:\\test\\Lusers.txt", "r");

	while (!feof(fp)) {
		if (users_cnt > 0) {
			users_data = realloc(users_data, sizeof(users) * (users_cnt + 1));
		}
		fscanf(fp, "%d %s\n", &users_data[users_cnt].num, users_data[users_cnt].name);
		users_data[users_cnt].borrow_list = NULL;
		users_data[users_cnt].borrow_num = 0;
		users_cnt++;

	}
	fclose(fp);
	return;
}

void book_load() {
	FILE* fp;

	fp = fopen("C:\\test\\Lbook.txt", "r");

	while (!feof(fp)) {
		if (book_cnt > 0) {
			book_data = realloc(book_data, sizeof(book) * (book_cnt + 1));
		}
		fscanf(fp, "%d %s\n", &book_data[book_cnt].num, book_data[book_cnt].title);
		book_cnt++;

	}
	fclose(fp);
	return;
}

void show_users() {
	int i, k;
	for (i = 0; i < users_cnt; i++) {
		printf("이용자번호 = %d, 이용자 성명 = %s :: ", users_data[i].num, users_data[i].name);
		if (users_data[i].borrow_num == 0)
			printf("대출중인 도서가 없습니다.");
		else {
			printf("대출권수 = %d권, ", users_data[i].borrow_num);
			for (k = 0; k < users_data[i].borrow_num; k++) {
				printf("%s ", users_data[i].borrow_list[k]);
			}
		}
		printf("\n");
	}
	system("pause");
}

void show_books() {
	int i;
	for (i = 0; i < book_cnt; i++) {
		printf("책 번호 = %d, 책 이름 =  %s\n", book_data[i].num, book_data[i].title);
	}
	system("pause");
}

void users_new() {
	if (users_cnt > 0) {
		users_data = realloc(users_data, sizeof(users) * (users_cnt + 1));
	}
	printf("신규회원이름 = ");
	getchar();
	gets(users_data[users_cnt].name);
	users_data[users_cnt].num = (users_cnt + 1);
	users_data[users_cnt].borrow_list = NULL;
	users_data[users_cnt].borrow_num = 0;

	users_cnt++;

	users_save();
	return;
}

void book_new() {
	if (book_cnt > 0) {
		book_data = realloc(book_data, sizeof(book) * (book_cnt + 1));
	}
	printf("신규도서명 = ");
	getchar();
	gets(book_data[book_cnt].title);
	book_data[book_cnt].num = (book_cnt + 1);
	book_cnt++;

	book_save();
}

void users_save() {
	FILE* fp;
	int i;

	fp = fopen("C:\\test\\Lusers.txt", "w");
	for (i = 0; i < users_cnt; i++) {
		fprintf(fp, "%d %s\n", users_data[i].num, users_data[i].name);
	}
	fclose(fp);
}

void book_save() {
	FILE* fp;
	int i;

	fp = fopen("C:\\test\\Lbook.txt", "w");
	for (i = 0; i < book_cnt; i++) {
		fprintf(fp, "%d %s\n", book_data[i].num, book_data[i].title);
	}
	fclose(fp);
}

void book_control() {
	int x, y, z, i, k, num;
	printf("회원번호 : ");
	scanf("%d", &x);
	printf("%d번 회원의 정보를 처리중입니다\n", x);
	printf("1. 대출 / 2. 반납 :  ");
	scanf("%d", &y);

	if (y == 1)
		book_borrow(x);
	else if (y == 2)
		book_return(x);
	else
		printf("없는 명령입니다.\n");

}

void book_borrow(int x) {
	int i, z;
	show_books();
	printf("어느책을 대출합니까(번호)? : ");
	scanf("%d", &z);
	if (users_data[x - 1].borrow_list == NULL)
		users_data[x - 1].borrow_list = (char**)malloc(sizeof(char*));
	else
		users_data[x - 1].borrow_list = realloc(users_data[x - 1].borrow_list, sizeof(char*) * (users_data[x - 1].borrow_num + 1));

	i = users_data[x - 1].borrow_num;
	users_data[x - 1].borrow_list[i] = (char*)malloc(20);
	strcpy(users_data[x - 1].borrow_list[i], book_data[z - 1].title);
	users_data[x - 1].borrow_num++;

}

void book_return(int x) {
	int i, z;
	printf("어느책을 반납합니까? : ");
	printf("현재 대출목록\n");

	for (i = 0; i < users_data[x - 1].borrow_num; i++) {
		printf("%d. %s\n", i + 1, users_data[x - 1].borrow_list[i]);
	}
	printf("입력 : ");
	scanf("%d", &z);
	while (z < users_data[x - 1].borrow_num) {
		users_data[x - 1].borrow_list[z - 1] = users_data[x - 1].borrow_list[z];
		z++;
	}
	users_data[x - 1].borrow_num--;
	users_data[x - 1].borrow_list = realloc(users_data[x - 1].borrow_list, sizeof(char*) * (users_data[x - 1].borrow_num));

}