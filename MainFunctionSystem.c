#define _CRT_SECURE_NO_WARNINGS
#define DataFile "stuData.txt"
#include <stdio.h>
#include <stdlib.h>//使用malloc
#include <string.h>

typedef struct Student {
	int id;
	char name[20];
	char gender[10];
} Student;

//Student stuList[100] = { {1,"张三",'男'},{2,"李四",'女'},{3,"王五",'男'}};

void showMenu();
void addStu();
void showStu();
void checkStu();
void delStu();
void modStu();

void getByIdStu();
void getByNameStu();

//主程序循环
int main() {

	char num;
	int isRunning = 1;

	printf("*****\n");
	while (isRunning) {
		showMenu();

		scanf("%c",&num);//当用输入字符并回车确定时，输入缓冲区会有两个字符：num和\n，后者会在下一次字符获取时使用，导致BUG出现，解决方法如下相邻语句。
		getchar();//吞掉字符缓冲区的回车字符'\n'
		printf("你输入的是%c\n",num);
		switch (num)
		{
		case '1':addStu();break;
		case '2':showStu();break;
		case '3':checkStu();break;
		case '4':break;
		case '5':break;
		case '6':isRunning = 0;printf("感谢使用，再见！\n"); break;
		default:printf("无效的输入,请重试！\n");
		}
	}

	return 0;
}

//展示主菜单
void showMenu() {
	printf("欢迎来到学生管理系统：\n");
	printf("1.添加学生：\n");
	printf("2.显示学生：\n");
	printf("3.查询学生：\n");
	printf("4.删除学生：\n");
	printf("5.修改学生数据：\n");
	printf("6.退出系统：\n");
	printf("请输入数字1~6：\n");
}

void addStu() {
	FILE* fp = fopen(DataFile, "a");

	Student s;


	printf("*****\n");
	printf("请输入学号:");
	scanf("%d",&s.id);
	getchar();
	printf("请输入姓名:");
	scanf("%s",s.name);
	getchar();
	printf("请输入性别:");
	scanf("%s", s.gender);
	getchar();
	printf("*****\n");


	fprintf(fp, "%d:%s:%s\n", s.id, s.name, s.gender);


	if (fp == NULL) {
		printf("error");
		return 0;
	}
	fclose(fp);
	fp = NULL;
	printf("添加成功\n");
}

void showStu() {
	FILE* fp = fopen(DataFile,"r");
	char buff[40];

	printf("*****\n");
	while (fgets(buff,40,fp) != NULL) {
		printf("%s",buff);
	}

	fclose(fp);
	fp = NULL;
	printf("*****\n");

}

void checkStu() {
	char opt;

	printf("*****\n");
	printf("通过_查找：\n");
	printf("1.id\n");
	printf("2.name\n");
	scanf("%c",&opt);
	getchar();

	switch (opt) {
		case '1':getByIdStu();break;
		case '2':getByNameStu(); break;
		default:printf("不存在的选项,返回主菜单");return;
	}
	printf("*****\n");
	return;
}

void getByIdStu() {

	/*
	Student * ss = (Student*)malloc(sizeof(Student)*1024); //开辟1024个结构体Student的内存空间
	Student* start = ss;//记录ss的起始地址。
	*/
	
	FILE* fp = fopen(DataFile,"r");//得到文件流
	char buff[40];//读取字符串缓冲
	char tok[10];//临时接收被分割出来的字符串
	int id;//查找的id号

	printf("请输入id(输入q退出):");
	scanf("%d",&id);
	getchar();

	if (id == 'q')return;

	while (fgets(buff,40,fp)!=NULL) {

			strcpy(tok, strtok(buff, ":"));
			//ss -> id =atoi(tok);//将学号（字符串）转换为整形输入到结构体

		if (atoi(tok)==id) {

			printf("~学号：%s\n", tok);


			strcpy(tok, strtok(NULL, ":"));
			//strcpy(ss->name,tok);
			printf("~名字：%s\n", tok);


			strcpy(tok, strtok(NULL, ":"));
			//strcpy(ss->gender, tok);//获取第三位（性别）
			printf("~性别：%s", tok);//最后一项自带换行符
		}

		//ss++;//前往下一个结构体
	}
	printf("查找结束\n");

	/*
	free(start);//ss++导致原指针的内存地址变化，free的地址发生变化，需要用起始的地址进行释放。
	ss = NULL;
	start = NULL;
	*/

	fclose(fp);
	fp = NULL;

	return;
}

void getByNameStu() {
	FILE* fp = fopen(DataFile,"r");//文件流
	char buff[40];//读入缓冲区
	char tok[10];//分隔字符串缓冲
	char name[10];//输入名字缓冲区
	int id;//id存储，因为id是在name前面一个，如果找到目标，需要调用输出。

	printf("请输入名字(输入q退出)：");
	scanf("%s", name);
	getchar();

	if (!strcmp(name, "q")) return;


	while (fgets(buff,40,fp) != NULL) {
			strcpy(tok,strtok(buff, ":"));
			id = atoi(tok);

			strcpy(tok, strtok(NULL, ":"));
			if (!strcmp(tok,name)) {

				printf("~学号：%d\n", id);

				printf("~名字：%s\n",tok);

				strcpy(tok, strtok(NULL, ":"));
				printf("~性别：%s", tok);
		}
	}

	printf("查找结束\n");

	fclose(fp);
	fp = NULL;
	return;
}