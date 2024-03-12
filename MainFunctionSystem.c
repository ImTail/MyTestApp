#define _CRT_SECURE_NO_WARNINGS
#define DataFile "stuData.txt"
#include <stdio.h>
#include <stdlib.h>//ʹ��malloc
#include <string.h>

typedef struct Student {
	int id;
	char name[20];
	char gender[10];
} Student;

//Student stuList[100] = { {1,"����",'��'},{2,"����",'Ů'},{3,"����",'��'}};

void showMenu();
void addStu();
void showStu();
void checkStu();
void delStu();
void modStu();

void getByIdStu();


//������ѭ��
int main() {

	char num;
	int isRunning = 1;

	printf("*****\n");
	while (isRunning) {
		showMenu();

		scanf("%c",&num);//���������ַ����س�ȷ��ʱ�����뻺�������������ַ���num��\n�����߻�����һ���ַ���ȡʱʹ�ã�����BUG���֣������������������䡣
		getchar();//�̵��ַ��������Ļس��ַ�'\n'
		printf("���������%c\n",num);
		switch (num)
		{
		case '1':addStu();break;
		case '2':showStu();break;
		case '3':checkStu();break;
		case '4':break;
		case '5':break;
		case '6':isRunning = 0;printf("��лʹ�ã��ټ���\n"); break;
		default:printf("��Ч������,�����ԣ�\n");
		}
	}

	return 0;
}

//չʾ���˵�
void showMenu() {
	printf("��ӭ����ѧ������ϵͳ��\n");
	printf("1.���ѧ����\n");
	printf("2.��ʾѧ����\n");
	printf("3.��ѯѧ����\n");
	printf("4.ɾ��ѧ����\n");
	printf("5.�޸�ѧ�����ݣ�\n");
	printf("6.�˳�ϵͳ��\n");
	printf("����������1~6��\n");
}

void addStu() {
	FILE* fp = fopen(DataFile, "a");

	Student s;


	printf("*****\n");
	printf("������ѧ��:");
	scanf("%d",&s.id);
	getchar();
	printf("����������:");
	scanf("%s",s.name);
	getchar();
	printf("�������Ա�:");
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
	printf("��ӳɹ�\n");
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
	printf("ͨ��_���ң�\n");
	printf("1.id\n");
	printf("2.name\n");
	scanf("%c",&opt);
	getchar();

	switch (opt) {
		case '1':getByIdStu();break;
		case '2':break;
		default:printf("�����ڵ�ѡ��,�������˵�");return;
	}
	printf("*****\n");
	return;
}

void getByIdStu() {
	Student * ss = (Student*)malloc(sizeof(Student)*1024); //����1024���ṹ��Student���ڴ�ռ�
	Student* start = ss;//��¼ss����ʼ��ַ��
	FILE* fp = fopen(DataFile,"r");//�õ��ļ���
	char* buff[40];//��ȡ�ַ�������
	char* tok;
	char id;

	printf("������id(����q�˳�):");
	scanf("%c",&id);
	getchar();

	if (id == 'q')return;

	while (fgets(buff,40,fp)!=NULL) {

		tok = strtok(buff,":");
		ss -> id =atoi(tok);//��ѧ�ţ��ַ�����ת��Ϊ�������뵽�ṹ��
		printf("%s \n",tok);


		tok = strtok(NULL, ":");//��ȡ�ڶ�λ�����֣�
		strcpy(ss->name,tok);
		printf("%s \n", tok);

		tok = strtok(NULL, ":");
		strcpy(ss->gender, tok);//��ȡ����λ���Ա�
		printf("%s", tok);//���һ���Դ����з�

		ss++;
	}
	printf("���ҽ���\n");

	free(start);//ss++����ԭָ����ڴ��ַ�仯��free�ĵ�ַ�����仯����Ҫ����ʼ�ĵ�ַ�����ͷš�
	ss = NULL;
	start = NULL;

	return;
}