#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

/*结构体，表示图书各项信息*/
typedef struct Book {
	char loginnum[16];
	char bookname[24];
	char author[24];
	char typenum[16];
	char publishinghouse[32];
	char publishingtime[16];
	char price[16];
}Book;
/*链表节点结构体*/
typedef struct Node {
	Book book;
	struct Node* next;
}Node;
/*图书信息文件*/
const char* dataFilePath = "D:\\librarydata.txt";
/*高级特效函数*/
int zhuangbilityFunction();
/*初始化链表函数*/
int initializeList();
/*初始化文件函数*/
int initializeFile();
/*添加图书菜单项函数*/
int addBookMenuItem();
/*图书信息浏览菜单项*/
int booksInfBrosweMenuItem();
/*查找书籍菜单项*/
int findAndSortMenuItem();
/*删除图书菜单项*/
int deleteBookMenuItem();
/*修改图书菜单项*/
int modifyBookMenuItem();
/*对node节点的book变量录入数据*/
int inputDataToBook(Node* node);
/*输出node节点book变量的各项信息*/
int printBookData(Node* node);
/*显示所有图书信息*/
int printAllBooks();
/*将图书数据从文件读入内存中*/
int readDataFromFile();
/*将内存中的图书数据写入文件中*/
int writeDataToFile(FILE* file);
/*保存内存中的所有图书数据*/
int saveAllBooks();
/*通过书名查找链表节点返回对应地址*/
Node* findBookByNameV(const char* inputName);
/*通过作者查找链表节点返回对应地址*/
Node* findBookByAuthorV(const char* inputAuthor);
/*删除书名对应的链表节点*/
int deleteBook(const char* inputName);
/*修改书名对应的链表节点*/
int modifyBook(const char* inputName);
/*关闭图书管理系统函数*/
int shutdownsystem();
/*文件指针*/
FILE* file = NULL;
/*图书链表头节点*/
Node* head = NULL;
/*当前图书节点*/
Node* currentBookNode = NULL;
/*主函数*/
int main()
{
	int n;
	zhuangbilityFunction();
	/*修改命令提示符窗口大小*/
	system("MODE con: COLS=160 LINES=30");
	/*初始化链表*/
	initializeList();
	/*判断数据文件是否正确打开*/
	if (initializeFile() != 0) {
		printf("系统启动失败,请稍后重试!\n");
		return 0;
	}
	/*进入菜单循环*/
	do {
		printf("\n欢迎来到图书信息管理系统!\n请输入操作序号:\n");
		printf("1.图书信息录入\n");
		printf("2.图书信息浏览\n");
		printf("3.查询和排序\n");
		printf("4.图书信息删除\n");
		printf("5.图书信息修改\n");
		printf("6.退出并保存\n\n");
		scanf("%d", &n);
		/*根据用户输入选项进入对应功能*/
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
			printf("输入有误请重试!\n\n");
		}
		/*当输入为6时结束循环，退出系统*/
	} while (n != 6);
	printf("欢迎下次使用!\n\n");
	/*进行关闭系统操作*/
	shutdownsystem();
	return 0;

}

int zhuangbilityFunction() {
	/*获取当前命令提示符窗口句柄*/
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	/*初始化光标位置结构体变量*/
	COORD pos = { 0,0 };
	/*初始化命令提示符缓冲区信息*/
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int randomDelay = 0, j, k;
	/*改变窗口大小*/
	system("MODE con: COLS=160 LINES=20");
	printf("系统启动中.....\n");
	for (k = 0; k < 157; k++) {
		printf("=");
	}
	/*通过句柄获取窗口缓冲区信息*/
	GetConsoleScreenBufferInfo(hOut, &csbi);
	/*更改光标XY坐标*/
	pos.X = csbi.dwCursorPosition.X - 157;
	pos.Y = csbi.dwCursorPosition.Y;
	/*将更改应用于窗口*/
	SetConsoleCursorPosition(hOut, pos);
	/*使用当前时间初始化随机数种子*/
	srand(time(0));
	for (j = 0; j < 157; j++) {
		/*设置随机休眠时间*/
		Sleep(rand() % 30);
		printf(">");
	}
	printf("\n\n启动成功!\n");
	/*系统终断2000毫秒*/
	Sleep(2000);
	return 0;
}

int initializeList() {
	/*为链表头节点分配内存空间*/
	head = (Node*)malloc(sizeof(Node));
	/*初始化该内存区域全部为0*/
	memset(head, 0, sizeof(Node));
	/*将头节点指针域置为空*/
	head->next = NULL;
	/*将当前图书节点指向头节点内存空间*/
	currentBookNode = head;
	return 0;
}

int initializeFile() {
	/*尝试以只读方式打开数据文件*/
	file = fopen(dataFilePath, "r");
	/*判断是否打开成功*/
	if (file == NULL) {
		/*若失败则以覆写方式打开文件*/
		file = fopen(dataFilePath, "w");
		if (file == NULL) {
			/*若失败，提示相关信息*/
			printf("请检查对应目录是否有权限进行读写或者文件被占用!\n");
			return -1;
		}
	}
	/*打开成功以后从文件读入数据*/
	readDataFromFile();
	return 0;
}

int addBookMenuItem() {
	/*申请内存空间*/
	Node* blankNode = (Node*)malloc(sizeof(Node));
	/*向当前书籍指针指向的内存区域写入数据*/
	inputDataToBook(currentBookNode);
	/*初始化刚申请的内存空间全部为0*/
	memset(blankNode, 0, sizeof(Node));
	/*将新申请的节点指针域置为空*/
	blankNode->next = NULL;
	/*将申请好的节点拼接到原链表尾部*/
	currentBookNode->next = blankNode;
	/*移动当前书籍指针到下一个节点*/
	currentBookNode = currentBookNode->next;
	return 0;
}

int booksInfBrosweMenuItem() {
	if (printAllBooks() == -1) {
		printf("列表为空,请先录入!\n");
	}
	return 0;
}

int findAndSortMenuItem() {
	int type;
	Node* node = NULL;
	/*声明带输入的字符数组*/
	char name[30] = { 0 };
	printf("请输入你要查找的方式:\n1.按书名查找\n2.按作者查找\n");
	scanf("%d", &type);
	/*输入为1按照书名查找*/
	if (type == 1) {
		printf("请输入书名:\n");
		scanf("%s", name);
		/*将node变量赋值为通过函数查找得到的图书节点*/
		node = findBookByNameV(name);
	}
	/*输入为2按照作者查找*/
	else if (type == 2) {
		printf("请输入作者:\n");
		scanf("%s", name);
		/*将node变量赋值为通过函数查找得到的图书节点*/
		node = findBookByAuthorV(name);
	}
	/*输入异常处理*/
	else {
		printf("输入有误!\n");
		return -1;
	}
	/*查找结果为空时提示信息*/
	if (node == NULL) {
		printf("查无此书!\n");
		return 1;
	}
	/*有结果则输出信息*/
	printf("书籍信息如下:\n    登录号 书名  作者  分类号  出版单位  出版时间  价格  \n");
	printBookData(node);
	return 0;
}

int deleteBookMenuItem() {
	char name[30] = { 0 };
	printf("请输入待删除书名:\n");
	scanf("%s", name);
	if (deleteBook(name) == -1) {
		printf("列表为空,请先录入!\n");
		return -1;
	}
	return 0;
}

int modifyBookMenuItem() {
	char name[30] = { 0 };
	printf("请输入待修改书名:\n");
	scanf("%s", name);
	if (modifyBook(name) == -1) {
		printf("列表为空,请先录入!\n");
		return -1;
	}
	return 0;
}

int inputDataToBook(Node* node) {
	/*声明变量Book指针，值为node节点book结构体变量首地址*/
	Book* b = &node->book;
	/*输入各项信息*/
	printf("请输入登录号:\n");
	scanf("%s", b->loginnum);
	printf("请输入书名:\n");
	scanf("%s", b->bookname);
	printf("请输入作者名:\n");
	scanf("%s", b->author);
	printf("请输入分类号:\n");
	scanf("%s", b->typenum);
	printf("请输入出版单位:\n");
	scanf("%s", b->publishinghouse);
	printf("请输入出版时间:\n");
	scanf("%s", b->publishingtime);
	printf("请输入价格:\n");
	scanf("%s", b->price);
	return 0;
}

int printBookData(Node* node) {
	Book* b;
	/*判断传入的地址是否为空，为空则直接返回-1*/
	if (node == NULL) {
		return -1;
	}
	b = &node->book;
	/*输出对应的各项图书信息*/
	printf("%10s%24s%24s%16s%32s%16s%10s\n", b->loginnum, b->bookname, b->author, b->typenum, b->publishinghouse, b->publishingtime, b->price);
	return 0;
}

int printAllBooks() {
	/*声明指针地址为头节点地址*/
	Node* p = head;
	if (head->next == NULL) {
		return -1;
	}
	printf("书籍信息如下:\n    登录号                    书名                    作者          分类号                        出版单位        出版时间      价格   \n");
	/*循环移动指针，直到尾节点停止循环*/
	while (p->next != NULL) {
		/*输出当前节点对应的图书信息*/
		printBookData(p);
		/*将p移动到链表下一个节点*/
		p = p->next;
	}
	return 0;
}

Node* findBookByNameV(const char* inputName) {
	Node* p = head;
	/*判断当前链表是否为空，如果为空无任何图书信息，返回空指针*/
	if (inputName == NULL || head->next == NULL) {
		return NULL;
	}
	/*循环移动指针，直到尾节点停止循环*/
	while (p->next != NULL) {
		/*比较传入字符串与当前链表节点对应的书籍名称是否相同，如果相同则返回当前节点地址*/
		if (strcmp(inputName, p->book.bookname) == 0) {
			return p;
		}
		/*移动p到链表下一个节点*/
		p = p->next;
	}
	return NULL;
}

Node* findBookByAuthorV(const char* inputAuthor) {
	Node* p = head;
	/*同上一个函数，比较者变为图书作者*/
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
	/*判断要删除的图书是否在头节点上*/
	if (strcmp(inputName, head->book.bookname) == 0) {
		/*将q指向链表头节点*/
		q = head;
		/*将头指针移动到下一个节点*/
		head = head->next;
		/*释放头节点内存空间*/
		free(q);
		printf("删除成功!\n");
		return 0;
	}
	/*不是头节点则进入循环*/
	p = head->next;
	q = head;
	while (p->next != NULL) {
		/*比较字符串内容是否与当前节点书名相同*/
		if (strcmp(inputName, p->book.bookname) == 0) {
			/*若相同则将该节点前一个节点的指针域赋值为该节点的指针域*/
			q->next = p->next;
			/*释放该节点内存空间*/
			free(p);
			printf("删除成功!\n");
			return 0;
		}
		/*将p和q移动到下一个节点*/
		/*在移动过程中q始终为p的前驱节点*/
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
	/*查找书名对应的节点地址*/
	p = findBookByNameV(inputName);
	if (p == NULL) {
		printf("未找到待修改的书名!\n");
		return 1;
	}
	printf("请输入新的信息:\n");
	/*修改p节点对应的信息*/
	inputDataToBook(p);
	printf("修改成功!\n");
	return 0;
}

int readDataFromFile() {
	Node* blankNode = NULL;
	/*从file文件结构体中读取数据
	* 第一个参数为待写入的内存地址
	* 第二个参数为每一次读入区块的大小
	* 第三个参数为读入区块的数量
	* 第四个参数为文件指针
	* 循环读取，当读到文件末尾时fread函数返回-1，停止读取
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
	/*判断链表中是否无数据*/
	if (head->next == NULL) {
		return -1;
	}
	/*
	* 每次向文件中写入当前节点book结构体变量首地址的数据
	* 大小为Book结构体的大小
	* 当p的指针域为空时停止读取
	*/
	while (p->next != NULL) {
		fwrite(&p->book, sizeof(Book), 1, file);
		//移动p到下一个节点
		p = p->next;
	}
	/*及时将缓冲区中的数据写入文件中，防止异常状况下文件内容丢失*/
	fflush(file);
	/*写入完成后及时关闭文件*/
	fclose(file);
	return 0;
}

int saveAllBooks() {
	fflush(file);
	fclose(file);
	/*以w方式打开文件，则在写入前将会清空源文件全部内容*/
	file = fopen(dataFilePath, "w");
	if (file == NULL) {
		printf("文件内容保存失败!请稍后重试!");
	}
	writeDataToFile(file);
	return 0;
}

int shutdownsystem() {
	saveAllBooks();
	return 0;
}