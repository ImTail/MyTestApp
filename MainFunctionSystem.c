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

Student getByIdStu(int);
Student getByNameStu(char*);

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
		case '4':delStu();break;
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
	int idIn;
	char nameIn[10];
	Student s;

	printf("*****\n");
	printf("ͨ��_���ң�\n");
	printf("1.id\n");
	printf("2.name\n");
	printf("����.����\n");
	scanf("%c",&opt);
	getchar();

	switch (opt) {
		case '1':
			printf("������ѧ�ţ�");
			scanf("%d",&idIn);
			getchar();
			s=getByIdStu(idIn);//���ò��Һ�����������ͬ���ݵĽṹ��
			if (s.id == -1) { printf("�����ڵ�ѧ��!\n"); }//��id=-1Ҳ��δ��ֵʱ��û���ҵ���أ��������жϡ�
			else {printf("\n~ | ѧ�ţ�%d | ������%s | �Ա�%s \n", s.id, s.name, s.gender);};
			printf("���ҽ���\n");
		break;
		case '2':
			printf("���������֣�");
			scanf("%s", nameIn);
			getchar();
			s = getByNameStu(nameIn);;
			if (s.id == -1) { printf("�����ڵ�ѧ��!\n"); } 
			else { printf("\n~ | ѧ�ţ�%d | ������%s | �Ա�%s \n", s.id, s.name, s.gender); };
			printf("���ҽ���\n");
			break;
		default:printf("�����ڵ�ѡ��,�������˵�\n");return;
	}
	printf("*****\n");
	return;
}


void delStu() {

}

Student getByIdStu(int id) {
	
	FILE* fp = fopen(DataFile,"r");//�õ��ļ���
	char buff[40];//��ȡ�ַ�������
	Student s;//����ֵ
	s.id = -1;//��û�б���ֵʱ�����ֵ��Ϊ��־λ�жϡ�

	int idT;
	char nameT[10];
	char genderT[10];

	while (fgets(buff,40,fp)!=NULL) {

		idT = atoi(strtok(buff, ":"));//������ָ��������ַ������뻺��
		strcpy(nameT, strtok(NULL, ":"));
		strcpy(genderT, strtok(NULL, ":"));
		
		//���ҵ�ƥ�����ֵ���ṹ�壬���ڷ���ֵ
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
	FILE* fp = fopen(DataFile, "r");//�õ��ļ���
	char buff[40];//��ȡ�ַ�������
	Student s;//����ֵ
	s.id = -1;

	int idT;
	char nameT[10];
	char genderT[10];

	while (fgets(buff, 40, fp) != NULL) {

		idT = atoi(strtok(buff, ":"));//������ָ��������ַ������뻺��
		strcpy(nameT, strtok(NULL, ":"));
		strcpy(genderT, strtok(NULL, ":"));

		//���ҵ�ƥ�����ֵ���ṹ�壬���ڷ���ֵ
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