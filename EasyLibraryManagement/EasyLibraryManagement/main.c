#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

/*�ṹ�壬��ʾͼ�������Ϣ*/
typedef struct Book {
	char loginnum[16];
	char bookname[24];
	char author[24];
	char typenum[16];
	char publishinghouse[32];
	char publishingtime[16];
	char price[16];
}Book;
/*����ڵ�ṹ��*/
typedef struct Node {
	Book book;
	struct Node* next;
}Node;
/*ͼ����Ϣ�ļ�*/
const char* dataFilePath = "D:\\librarydata.txt";
/*�߼���Ч����*/
int zhuangbilityFunction();
/*��ʼ��������*/
int initializeList();
/*��ʼ���ļ�����*/
int initializeFile();
/*���ͼ��˵����*/
int addBookMenuItem();
/*ͼ����Ϣ����˵���*/
int booksInfBrosweMenuItem();
/*�����鼮�˵���*/
int findAndSortMenuItem();
/*ɾ��ͼ��˵���*/
int deleteBookMenuItem();
/*�޸�ͼ��˵���*/
int modifyBookMenuItem();
/*��node�ڵ��book����¼������*/
int inputDataToBook(Node* node);
/*���node�ڵ�book�����ĸ�����Ϣ*/
int printBookData(Node* node);
/*��ʾ����ͼ����Ϣ*/
int printAllBooks();
/*��ͼ�����ݴ��ļ������ڴ���*/
int readDataFromFile();
/*���ڴ��е�ͼ������д���ļ���*/
int writeDataToFile(FILE* file);
/*�����ڴ��е�����ͼ������*/
int saveAllBooks();
/*ͨ��������������ڵ㷵�ض�Ӧ��ַ*/
Node* findBookByNameV(const char* inputName);
/*ͨ�����߲�������ڵ㷵�ض�Ӧ��ַ*/
Node* findBookByAuthorV(const char* inputAuthor);
/*ɾ��������Ӧ������ڵ�*/
int deleteBook(const char* inputName);
/*�޸�������Ӧ������ڵ�*/
int modifyBook(const char* inputName);
/*�ر�ͼ�����ϵͳ����*/
int shutdownsystem();
/*�ļ�ָ��*/
FILE* file = NULL;
/*ͼ������ͷ�ڵ�*/
Node* head = NULL;
/*��ǰͼ��ڵ�*/
Node* currentBookNode = NULL;
/*������*/
int main()
{
	int n;
	zhuangbilityFunction();
	/*�޸�������ʾ�����ڴ�С*/
	system("MODE con: COLS=160 LINES=30");
	/*��ʼ������*/
	initializeList();
	/*�ж������ļ��Ƿ���ȷ��*/
	if (initializeFile() != 0) {
		printf("ϵͳ����ʧ��,���Ժ�����!\n");
		return 0;
	}
	/*����˵�ѭ��*/
	do {
		printf("\n��ӭ����ͼ����Ϣ����ϵͳ!\n������������:\n");
		printf("1.ͼ����Ϣ¼��\n");
		printf("2.ͼ����Ϣ���\n");
		printf("3.��ѯ������\n");
		printf("4.ͼ����Ϣɾ��\n");
		printf("5.ͼ����Ϣ�޸�\n");
		printf("6.�˳�������\n\n");
		scanf("%d", &n);
		/*�����û�����ѡ������Ӧ����*/
		switch (n) {
		case 1:
			addBookMenuItem();
			break;
		case 2:
			booksInfBrosweMenuItem();
			break;
		case 3:
			findAndSortMenuItem();
			break;
		case 4:
			deleteBookMenuItem();
			break;
		case 5:
			modifyBookMenuItem();
			break;
		case 6:
			break;
		default:
			printf("��������������!\n\n");
		}
		/*������Ϊ6ʱ����ѭ�����˳�ϵͳ*/
	} while (n != 6);
	printf("��ӭ�´�ʹ��!\n\n");
	/*���йر�ϵͳ����*/
	shutdownsystem();
	return 0;

}

int zhuangbilityFunction() {
	/*��ȡ��ǰ������ʾ�����ھ��*/
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	/*��ʼ�����λ�ýṹ�����*/
	COORD pos = { 0,0 };
	/*��ʼ��������ʾ����������Ϣ*/
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int randomDelay = 0, j, k;
	/*�ı䴰�ڴ�С*/
	system("MODE con: COLS=160 LINES=20");
	printf("ϵͳ������.....\n");
	for (k = 0; k < 157; k++) {
		printf("=");
	}
	/*ͨ�������ȡ���ڻ�������Ϣ*/
	GetConsoleScreenBufferInfo(hOut, &csbi);
	/*���Ĺ��XY����*/
	pos.X = csbi.dwCursorPosition.X - 157;
	pos.Y = csbi.dwCursorPosition.Y;
	/*������Ӧ���ڴ���*/
	SetConsoleCursorPosition(hOut, pos);
	/*ʹ�õ�ǰʱ���ʼ�����������*/
	srand(time(0));
	for (j = 0; j < 157; j++) {
		/*�����������ʱ��*/
		Sleep(rand() % 30);
		printf(">");
	}
	printf("\n\n�����ɹ�!\n");
	/*ϵͳ�ն�2000����*/
	Sleep(2000);
	return 0;
}

int initializeList() {
	/*Ϊ����ͷ�ڵ�����ڴ�ռ�*/
	head = (Node*)malloc(sizeof(Node));
	/*��ʼ�����ڴ�����ȫ��Ϊ0*/
	memset(head, 0, sizeof(Node));
	/*��ͷ�ڵ�ָ������Ϊ��*/
	head->next = NULL;
	/*����ǰͼ��ڵ�ָ��ͷ�ڵ��ڴ�ռ�*/
	currentBookNode = head;
	return 0;
}

int initializeFile() {
	/*������ֻ����ʽ�������ļ�*/
	file = fopen(dataFilePath, "r");
	/*�ж��Ƿ�򿪳ɹ�*/
	if (file == NULL) {
		/*��ʧ�����Ը�д��ʽ���ļ�*/
		file = fopen(dataFilePath, "w");
		if (file == NULL) {
			/*��ʧ�ܣ���ʾ�����Ϣ*/
			printf("�����ӦĿ¼�Ƿ���Ȩ�޽��ж�д�����ļ���ռ��!\n");
			return -1;
		}
	}
	/*�򿪳ɹ��Ժ���ļ���������*/
	readDataFromFile();
	return 0;
}

int addBookMenuItem() {
	/*�����ڴ�ռ�*/
	Node* blankNode = (Node*)malloc(sizeof(Node));
	/*��ǰ�鼮ָ��ָ����ڴ�����д������*/
	inputDataToBook(currentBookNode);
	/*��ʼ����������ڴ�ռ�ȫ��Ϊ0*/
	memset(blankNode, 0, sizeof(Node));
	/*��������Ľڵ�ָ������Ϊ��*/
	blankNode->next = NULL;
	/*������õĽڵ�ƴ�ӵ�ԭ����β��*/
	currentBookNode->next = blankNode;
	/*�ƶ���ǰ�鼮ָ�뵽��һ���ڵ�*/
	currentBookNode = currentBookNode->next;
	return 0;
}

int booksInfBrosweMenuItem() {
	if (printAllBooks() == -1) {
		printf("�б�Ϊ��,����¼��!\n");
	}
	return 0;
}

int findAndSortMenuItem() {
	int type;
	Node* node = NULL;
	/*������������ַ�����*/
	char name[30] = { 0 };
	printf("��������Ҫ���ҵķ�ʽ:\n1.����������\n2.�����߲���\n");
	scanf("%d", &type);
	/*����Ϊ1������������*/
	if (type == 1) {
		printf("����������:\n");
		scanf("%s", name);
		/*��node������ֵΪͨ���������ҵõ���ͼ��ڵ�*/
		node = findBookByNameV(name);
	}
	/*����Ϊ2�������߲���*/
	else if (type == 2) {
		printf("����������:\n");
		scanf("%s", name);
		/*��node������ֵΪͨ���������ҵõ���ͼ��ڵ�*/
		node = findBookByAuthorV(name);
	}
	/*�����쳣����*/
	else {
		printf("��������!\n");
		return -1;
	}
	/*���ҽ��Ϊ��ʱ��ʾ��Ϣ*/
	if (node == NULL) {
		printf("���޴���!\n");
		return 1;
	}
	/*�н���������Ϣ*/
	printf("�鼮��Ϣ����:\n    ��¼�� ����  ����  �����  ���浥λ  ����ʱ��  �۸�  \n");
	printBookData(node);
	return 0;
}

int deleteBookMenuItem() {
	char name[30] = { 0 };
	printf("�������ɾ������:\n");
	scanf("%s", name);
	if (deleteBook(name) == -1) {
		printf("�б�Ϊ��,����¼��!\n");
		return -1;
	}
	return 0;
}

int modifyBookMenuItem() {
	char name[30] = { 0 };
	printf("��������޸�����:\n");
	scanf("%s", name);
	if (modifyBook(name) == -1) {
		printf("�б�Ϊ��,����¼��!\n");
		return -1;
	}
	return 0;
}

int inputDataToBook(Node* node) {
	/*��������Bookָ�룬ֵΪnode�ڵ�book�ṹ������׵�ַ*/
	Book* b = &node->book;
	/*���������Ϣ*/
	printf("�������¼��:\n");
	scanf("%s", b->loginnum);
	printf("����������:\n");
	scanf("%s", b->bookname);
	printf("������������:\n");
	scanf("%s", b->author);
	printf("����������:\n");
	scanf("%s", b->typenum);
	printf("��������浥λ:\n");
	scanf("%s", b->publishinghouse);
	printf("���������ʱ��:\n");
	scanf("%s", b->publishingtime);
	printf("������۸�:\n");
	scanf("%s", b->price);
	return 0;
}

int printBookData(Node* node) {
	Book* b;
	/*�жϴ���ĵ�ַ�Ƿ�Ϊ�գ�Ϊ����ֱ�ӷ���-1*/
	if (node == NULL) {
		return -1;
	}
	b = &node->book;
	/*�����Ӧ�ĸ���ͼ����Ϣ*/
	printf("%10s%24s%24s%16s%32s%16s%10s\n", b->loginnum, b->bookname, b->author, b->typenum, b->publishinghouse, b->publishingtime, b->price);
	return 0;
}

int printAllBooks() {
	/*����ָ���ַΪͷ�ڵ��ַ*/
	Node* p = head;
	if (head->next == NULL) {
		return -1;
	}
	printf("�鼮��Ϣ����:\n    ��¼��                    ����                    ����          �����                        ���浥λ        ����ʱ��      �۸�   \n");
	/*ѭ���ƶ�ָ�룬ֱ��β�ڵ�ֹͣѭ��*/
	while (p->next != NULL) {
		/*�����ǰ�ڵ��Ӧ��ͼ����Ϣ*/
		printBookData(p);
		/*��p�ƶ���������һ���ڵ�*/
		p = p->next;
	}
	return 0;
}

Node* findBookByNameV(const char* inputName) {
	Node* p = head;
	/*�жϵ�ǰ�����Ƿ�Ϊ�գ����Ϊ�����κ�ͼ����Ϣ�����ؿ�ָ��*/
	if (inputName == NULL || head->next == NULL) {
		return NULL;
	}
	/*ѭ���ƶ�ָ�룬ֱ��β�ڵ�ֹͣѭ��*/
	while (p->next != NULL) {
		/*�Ƚϴ����ַ����뵱ǰ����ڵ��Ӧ���鼮�����Ƿ���ͬ�������ͬ�򷵻ص�ǰ�ڵ��ַ*/
		if (strcmp(inputName, p->book.bookname) == 0) {
			return p;
		}
		/*�ƶ�p��������һ���ڵ�*/
		p = p->next;
	}
	return NULL;
}

Node* findBookByAuthorV(const char* inputAuthor) {
	Node* p = head;
	/*ͬ��һ���������Ƚ��߱�Ϊͼ������*/
	if (inputAuthor == NULL || head->next == NULL) {
		return NULL;
	}

	while (p->next != NULL) {
		if (strcmp(inputAuthor, p->book.author) == 0) {
			return p;
		}
		p = p->next;
	}
	return NULL;

}

int deleteBook(const char* inputName) {
	Node* p = head, *q = NULL;
	if (inputName == NULL || head->next == NULL) {
		return -1;
	}
	/*�ж�Ҫɾ����ͼ���Ƿ���ͷ�ڵ���*/
	if (strcmp(inputName, head->book.bookname) == 0) {
		/*��qָ������ͷ�ڵ�*/
		q = head;
		/*��ͷָ���ƶ�����һ���ڵ�*/
		head = head->next;
		/*�ͷ�ͷ�ڵ��ڴ�ռ�*/
		free(q);
		printf("ɾ���ɹ�!\n");
		return 0;
	}
	/*����ͷ�ڵ������ѭ��*/
	p = head->next;
	q = head;
	while (p->next != NULL) {
		/*�Ƚ��ַ��������Ƿ��뵱ǰ�ڵ�������ͬ*/
		if (strcmp(inputName, p->book.bookname) == 0) {
			/*����ͬ�򽫸ýڵ�ǰһ���ڵ��ָ����ֵΪ�ýڵ��ָ����*/
			q->next = p->next;
			/*�ͷŸýڵ��ڴ�ռ�*/
			free(p);
			printf("ɾ���ɹ�!\n");
			return 0;
		}
		/*��p��q�ƶ�����һ���ڵ�*/
		/*���ƶ�������qʼ��Ϊp��ǰ���ڵ�*/
		p = p->next;
		q = q->next;
	}

	return 1;
}

int modifyBook(const char* inputName) {
	Node* p;
	if (inputName == NULL || head->next == NULL) {
		return -1;
	}
	/*����������Ӧ�Ľڵ��ַ*/
	p = findBookByNameV(inputName);
	if (p == NULL) {
		printf("δ�ҵ����޸ĵ�����!\n");
		return 1;
	}
	printf("�������µ���Ϣ:\n");
	/*�޸�p�ڵ��Ӧ����Ϣ*/
	inputDataToBook(p);
	printf("�޸ĳɹ�!\n");
	return 0;
}

int readDataFromFile() {
	Node* blankNode = NULL;
	/*��file�ļ��ṹ���ж�ȡ����
	* ��һ������Ϊ��д����ڴ��ַ
	* �ڶ�������Ϊÿһ�ζ�������Ĵ�С
	* ����������Ϊ�������������
	* ���ĸ�����Ϊ�ļ�ָ��
	* ѭ����ȡ���������ļ�ĩβʱfread��������-1��ֹͣ��ȡ
	*/
	while (fread(&currentBookNode->book, sizeof(Book), 1, file) != 0) {
		blankNode = (Node*)malloc(sizeof(Node));
		memset(blankNode, 0, sizeof(Node));
		blankNode->next = NULL;
		currentBookNode->next = blankNode;
		currentBookNode = currentBookNode->next;
	}
	return 0;
}

int writeDataToFile(FILE* file) {
	Node* p = head;
	/*�ж��������Ƿ�������*/
	if (head->next == NULL) {
		return -1;
	}
	/*
	* ÿ�����ļ���д�뵱ǰ�ڵ�book�ṹ������׵�ַ������
	* ��СΪBook�ṹ��Ĵ�С
	* ��p��ָ����Ϊ��ʱֹͣ��ȡ
	*/
	while (p->next != NULL) {
		fwrite(&p->book, sizeof(Book), 1, file);
		//�ƶ�p����һ���ڵ�
		p = p->next;
	}
	/*��ʱ���������е�����д���ļ��У���ֹ�쳣״�����ļ����ݶ�ʧ*/
	fflush(file);
	/*д����ɺ�ʱ�ر��ļ�*/
	fclose(file);
	return 0;
}

int saveAllBooks() {
	fflush(file);
	fclose(file);
	/*��w��ʽ���ļ�������д��ǰ�������Դ�ļ�ȫ������*/
	file = fopen(dataFilePath, "w");
	if (file == NULL) {
		printf("�ļ����ݱ���ʧ��!���Ժ�����!");
	}
	writeDataToFile(file);
	return 0;
}

int shutdownsystem() {
	saveAllBooks();
	return 0;
}