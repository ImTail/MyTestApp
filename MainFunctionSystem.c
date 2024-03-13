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

Student getByIdStu(int);
Student getByNameStu(char*);

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
		case '4':delStu();break;
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
	int idIn;
	char nameIn[10];
	Student s;

	printf("*****\n");
	printf("通过_查找：\n");
	printf("1.id\n");
	printf("2.name\n");
	printf("其它.返回\n");
	scanf("%c",&opt);
	getchar();

	switch (opt) {
		case '1':
			printf("请输入学号：");
			scanf("%d",&idIn);
			getchar();
			s=getByIdStu(idIn);//调用查找函数，返回相同数据的结构体
			if (s.id == -1) { printf("不存在的学生!\n"); }//当id=-1也即未赋值时，没有找到相关，并进行判断。
			else {printf("\n~ | 学号：%d | 姓名：%s | 性别：%s \n", s.id, s.name, s.gender);};
			printf("查找结束\n");
		break;
		case '2':
			printf("请输入名字：");
			scanf("%s", nameIn);
			getchar();
			s = getByNameStu(nameIn);;
			if (s.id == -1) { printf("不存在的学生!\n"); } 
			else { printf("\n~ | 学号：%d | 姓名：%s | 性别：%s \n", s.id, s.name, s.gender); };
			printf("查找结束\n");
			break;
		default:printf("不存在的选项,返回主菜单\n");return;
	}
	printf("*****\n");
	return;
}


void delStu() {

}

Student getByIdStu(int id) {
	
	FILE* fp = fopen(DataFile,"r");//得到文件流
	char buff[40];//读取字符串缓冲
	Student s;//返回值
	s.id = -1;//当没有被赋值时，这个值作为标志位判断。

	int idT;
	char nameT[10];
	char genderT[10];

	while (fgets(buff,40,fp)!=NULL) {

		idT = atoi(strtok(buff, ":"));//把三项分隔出来的字符串放入缓冲
		strcpy(nameT, strtok(NULL, ":"));
		strcpy(genderT, strtok(NULL, ":"));
		
		//查找到匹配项，赋值到结构体，用于返回值
		if (idT==id) {

			s.id = idT;

			strcpy(s.name, nameT);

			strcpy(s.gender, genderT);
		}

	}
	fclose(fp);
	fp = NULL;

	return s;
}

Student getByNameStu(char* name) {
	FILE* fp = fopen(DataFile, "r");//得到文件流
	char buff[40];//读取字符串缓冲
	Student s;//返回值
	s.id = -1;

	int idT;
	char nameT[10];
	char genderT[10];

	while (fgets(buff, 40, fp) != NULL) {

		idT = atoi(strtok(buff, ":"));//把三项分隔出来的字符串放入缓冲
		strcpy(nameT, strtok(NULL, ":"));
		strcpy(genderT, strtok(NULL, ":"));

		//查找到匹配项，赋值到结构体，用于返回值
		if (!strcmp(name,nameT)) {

			s.id = idT;

			strcpy(s.name, nameT);

			strcpy(s.gender, genderT);
		}

	}
	fclose(fp);
	fp = NULL;

	return s;
}