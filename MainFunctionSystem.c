#define _CRT_SECURE_NO_WARNINGS
#define DataFile "stuData.txt"
#define DataFileTemp "dataFileTemp.txt"

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
void insertSort();

Student getByIdStu(int);
Student getByNameStu(char*);
Student delByIdStu(int);
Student delByNameStu(char*);

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
		case '5':modStu();break;
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

	insertSort();
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

//删除和修改函数通过创造新的临时文件，复制源文件内容并进行修改，完成后用临时文件代替源文件。有效防止中途写入被终端出现的数据丢失。
void delStu() {
	char opt;
	int id;
	char name[10];
	Student s;

	printf("*****\n");
	printf("通过_删除：\n");
	printf("1.id\n");
	printf("2.name\n");
	printf("其它.返回\n");

	scanf("%c",&opt);
	getchar();

	switch (opt) {
		case '1':
			printf("请输入学号：");
			scanf("%d",&id);
			getchar();
			s = delByIdStu(id);
			if (s.id == -1) { printf("不存在的学生!\n"); }//当id=-1也即未赋值时，没有找到相关，并进行判断。
			else { printf("\n已删除！ | 学号：%d | 姓名：%s | 性别：%s \n", s.id, s.name, s.gender); };
			printf("查找结束\n");
		break;
		case '2':
			printf("请输入名字：");
			scanf("%s", name);
			getchar();
			s = delByNameStu(name);
			if (s.id == -1) { printf("不存在的学生!\n"); }//当id=-1也即未赋值时，没有找到相关，并进行判断。
			else { printf("\n已删除！ | 学号：%d | 姓名：%s | 性别：%s \n", s.id, s.name, s.gender); };
			printf("查找结束\n");
		break;
		default:printf("不存在的选项,返回主菜单\n");return;;
	}
	return;
}

void modStu() {
	int id;//获取输入
	char name[10];//获取修改值
	Student s;//结果
	int idT;//分隔第一项
	char nameT[10];//分隔第二项
	char genderT[10];//分隔第三项
	char buff[40];//一行的读取内容
	char buffRes[40];//存储修改后一行的内容
	s.id = -1;//是否找到匹配项的标识符

	char arrBuff[40][128];//存储读取的所有数据
	int arrNum = 0;//记录当前arrBuff指向第几行，每一次读取并复制会使该值+1.同时也有计数的作用。

	printf("*****\n");
	printf("请输入学号：\n");
	scanf("%d", &id);getchar();
	printf("请输入要修改的名字：\n");
	scanf("%s", &name);getchar();

	FILE* frp = fopen(DataFile, "r");
	//FILE* fwp = fopen("dataFileTemp.txt", "w");

	

	while (fgets(buff,40,frp) != NULL) {

		strcpy(arrBuff[arrNum], buff);//将buff（一行）的内容读取到二维数组的第arrNum行，将此语句置前，以免buff在之后的分隔语句之后乱掉，不好处理

		idT = atoi(strtok(buff, ":"));//把三项分隔出来的字符串放入缓冲,函数本质是用将“：”用字符串终止符替换
		strcpy(nameT, strtok(NULL, ":"));
		strcpy(genderT, strtok(NULL, ":"));
			//如果匹配到修改项，进行赋值操作
			if (id == idT) {
				s.id = idT;
				strcpy(s.name, nameT);
				strcpy(s.gender, genderT);
				strcpy(nameT, name);//将修改值应用到临时变量，以便修改
				sprintf(buffRes,"%d:%s:%s",idT,nameT,genderT);//拼接字符串到buffRes，形成修改后的行，以便写入文件 PS:gender从转移的工程中仍带有换行符号
				strcpy(arrBuff[arrNum], buffRes);
			}
			
		arrNum++;
	}
	fclose(frp);
	frp = NULL;

	if (s.id == -1) { printf("没有找到匹配的学号\n"); return; }//代表没有在循环中复制，也即没有找到对应要修改的项。

	FILE* fwp = fopen(DataFileTemp, "w");
	for (int i = 0 ; i < arrNum ; i++) {
		fputs(arrBuff[i], fwp);
	}


	fclose(fwp);
	fwp = NULL;
	
	//当流关闭后才能操纵文件外部

	remove(DataFile);

	if (rename(DataFileTemp, DataFile)) {
		printf("改名失败!!!!!!!\n");
		return;
	}


	printf("修改成功\n");
	return;
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

Student delByIdStu(int id) {
	FILE* frp = fopen(DataFile, "r");
	//FILE* fwp = fopen("dataFileTemp.txt", "w");
	char arrBuff[128][40];//存储读取的所有数据
	int arrNum = 0;//记录当前arrBuff指向第几行，每一次读取并复制会使该值+1.同时也有计数的作用。

	Student s;//返回值
	int idT;//分隔第一项
	char nameT[10];//分隔第二项
	char genderT[10];//分隔第三项
	char buff[40];//一行的读取内容
	s.id = -1;//是否找到匹配项的标识符

	while (fgets(buff,40,frp) != NULL) {

		strcpy(arrBuff[arrNum], buff);//将buff（一行）的内容读取到二维数组的第arrNum行，将此语句置前，以免buff在之后的分隔语句之后乱掉，不好处理

		idT = atoi(strtok(buff, ":"));//把三项分隔出来的字符串放入缓冲,函数本质是用将“：”用字符串终止符替换
		strcpy(nameT, strtok(NULL, ":"));
		strcpy(genderT, strtok(NULL, ":"));
			//如果匹配到删除项，跳过本次循环，也即本次复制
			if (id == idT) {
				s.id = idT;
				strcpy(s.name, nameT);
				strcpy(s.gender, genderT);
				continue; 
			}
		arrNum++;
	}
	fclose(frp);
	frp = NULL;

	if (s.id == -1) { return s; }//代表没有在循环中复制，也即没有找到对应要删除的项。
	//return s;

	FILE* fwp = fopen(DataFileTemp, "w");
	for (int i = 0 ; i < arrNum ; i++) {
		fputs(arrBuff[i], fwp);
	}


	fclose(fwp);
	fwp = NULL;
	
	//当流关闭后才能操纵文件外部

	remove(DataFile);

	if (rename(DataFileTemp, DataFile)) {
		printf("改名失败!!!!!!!\n");
		return s;
	}

	return s;
}

Student delByNameStu(char* name) {
	FILE* frp = fopen(DataFile, "r");
	//FILE* fwp = fopen("dataFileTemp.txt", "w");
	char arrBuff[128][40];
	int arrNum = 0;//记录当前arrBuff指向第几行，每一次读取并复制会使该值+1.同时也有计数的作用。

	Student s;
	int idT;
	char nameT[10];
	char genderT[10];
	char buff[40];
	s.id = -1;

	while (fgets(buff, 40, frp) != NULL) {

		strcpy(arrBuff[arrNum], buff);//将buff（一行）的内容读取到二维数组的第arrNum行，将此语句置前，以免buff在之后的分隔语句之后乱掉，不好处理

		idT = atoi(strtok(buff, ":"));//把三项分隔出来的字符串放入缓冲,函数本质是用将“：”用字符串终止符替换
		strcpy(nameT, strtok(NULL, ":"));
		strcpy(genderT, strtok(NULL, ":"));
		//如果匹配到删除项，跳过本次循环，也即本次复制
		if (!strcmp(nameT,name)) {
			s.id = idT;
			strcpy(s.name, nameT);
			strcpy(s.gender, genderT);
			continue;
		}
		arrNum++;
	}
	fclose(frp);
	frp = NULL;
	if (s.id == -1) { return s; }//代表没有在循环中复制，也即没有找到对应要删除的项。


	FILE* fwp = fopen(DataFileTemp, "w");
	for (int i = 0; i < arrNum; i++) {
		fputs(arrBuff[i], fwp);
	}


	fclose(fwp);
	fwp = NULL;

	//当流关闭后才能操纵文件外部

	remove(DataFile);

	if (rename(DataFileTemp, DataFile)) {
		printf("改名失败!!!!!!!\n");
		return s;
	}

	return s;
}

void insertSort() {
	char buff[64][40];//尝试直接使用二维数组代替buff，省去了数组复制。
	int buffNum = 0;//buff的行索引
	int id[64];//id缓冲
	char* buffStr[30];//字符串缓冲

	FILE* frp = fopen(DataFile,"r");
	while (!fgets(buff[buffNum],40,frp)==NULL) {
		sscanf(buff[buffNum],"%d:%s",id+buffNum, buffStr);
		buffNum++;
	}
	fclose(frp);frp = NULL;

	int i, j, key;
	char keyBuff[40];

	for (i = 1; i < buffNum; i++) {

		key = id[i];
		strcpy(keyBuff, buff[i]);

		j = i - 1;
		while (j>=0 && id[j]>key) {

			id[j + 1] = id[j];
			strcpy(buff[j + 1], buff[j]);
			j--;
		}

		id[j + 1] = key;
		strcpy(buff[j + 1], keyBuff);


	}

	FILE* fwp = fopen(DataFileTemp,"w");
	for (int i = 0;i < buffNum; i++) {
		fputs(buff[i],fwp);
		//printf("%s",buff[i]);
	}

	fclose(fwp);fwp = NULL;

	remove(DataFile);

	if (rename(DataFileTemp, DataFile)) {
		printf("改名失败!!!!!!!\n");
		return;
	}

	return;
}