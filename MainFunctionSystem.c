#define _CRT_SECURE_NO_WARNINGS
#define DataFile "stuData.txt"
#define DataFileTemp "dataFileTemp.txt"

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
void insertSort();

Student getByIdStu(int);
Student getByNameStu(char*);
Student delByIdStu(int);
Student delByNameStu(char*);

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
		case '5':modStu();break;
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

	insertSort();
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

//ɾ�����޸ĺ���ͨ�������µ���ʱ�ļ�������Դ�ļ����ݲ������޸ģ���ɺ�����ʱ�ļ�����Դ�ļ�����Ч��ֹ��;д�뱻�ն˳��ֵ����ݶ�ʧ��
void delStu() {
	char opt;
	int id;
	char name[10];
	Student s;

	printf("*****\n");
	printf("ͨ��_ɾ����\n");
	printf("1.id\n");
	printf("2.name\n");
	printf("����.����\n");

	scanf("%c",&opt);
	getchar();

	switch (opt) {
		case '1':
			printf("������ѧ�ţ�");
			scanf("%d",&id);
			getchar();
			s = delByIdStu(id);
			if (s.id == -1) { printf("�����ڵ�ѧ��!\n"); }//��id=-1Ҳ��δ��ֵʱ��û���ҵ���أ��������жϡ�
			else { printf("\n��ɾ���� | ѧ�ţ�%d | ������%s | �Ա�%s \n", s.id, s.name, s.gender); };
			printf("���ҽ���\n");
		break;
		case '2':
			printf("���������֣�");
			scanf("%s", name);
			getchar();
			s = delByNameStu(name);
			if (s.id == -1) { printf("�����ڵ�ѧ��!\n"); }//��id=-1Ҳ��δ��ֵʱ��û���ҵ���أ��������жϡ�
			else { printf("\n��ɾ���� | ѧ�ţ�%d | ������%s | �Ա�%s \n", s.id, s.name, s.gender); };
			printf("���ҽ���\n");
		break;
		default:printf("�����ڵ�ѡ��,�������˵�\n");return;;
	}
	return;
}

void modStu() {
	int id;//��ȡ����
	char name[10];//��ȡ�޸�ֵ
	Student s;//���
	int idT;//�ָ���һ��
	char nameT[10];//�ָ��ڶ���
	char genderT[10];//�ָ�������
	char buff[40];//һ�еĶ�ȡ����
	char buffRes[40];//�洢�޸ĺ�һ�е�����
	s.id = -1;//�Ƿ��ҵ�ƥ����ı�ʶ��

	char arrBuff[40][128];//�洢��ȡ����������
	int arrNum = 0;//��¼��ǰarrBuffָ��ڼ��У�ÿһ�ζ�ȡ�����ƻ�ʹ��ֵ+1.ͬʱҲ�м��������á�

	printf("*****\n");
	printf("������ѧ�ţ�\n");
	scanf("%d", &id);getchar();
	printf("������Ҫ�޸ĵ����֣�\n");
	scanf("%s", &name);getchar();

	FILE* frp = fopen(DataFile, "r");
	//FILE* fwp = fopen("dataFileTemp.txt", "w");

	

	while (fgets(buff,40,frp) != NULL) {

		strcpy(arrBuff[arrNum], buff);//��buff��һ�У������ݶ�ȡ����ά����ĵ�arrNum�У����������ǰ������buff��֮��ķָ����֮���ҵ������ô���

		idT = atoi(strtok(buff, ":"));//������ָ��������ַ������뻺��,�����������ý����������ַ�����ֹ���滻
		strcpy(nameT, strtok(NULL, ":"));
		strcpy(genderT, strtok(NULL, ":"));
			//���ƥ�䵽�޸�����и�ֵ����
			if (id == idT) {
				s.id = idT;
				strcpy(s.name, nameT);
				strcpy(s.gender, genderT);
				strcpy(nameT, name);//���޸�ֵӦ�õ���ʱ�������Ա��޸�
				sprintf(buffRes,"%d:%s:%s",idT,nameT,genderT);//ƴ���ַ�����buffRes���γ��޸ĺ���У��Ա�д���ļ� PS:gender��ת�ƵĹ������Դ��л��з���
				strcpy(arrBuff[arrNum], buffRes);
			}
			
		arrNum++;
	}
	fclose(frp);
	frp = NULL;

	if (s.id == -1) { printf("û���ҵ�ƥ���ѧ��\n"); return; }//����û����ѭ���и��ƣ�Ҳ��û���ҵ���ӦҪ�޸ĵ��

	FILE* fwp = fopen(DataFileTemp, "w");
	for (int i = 0 ; i < arrNum ; i++) {
		fputs(arrBuff[i], fwp);
	}


	fclose(fwp);
	fwp = NULL;
	
	//�����رպ���ܲ����ļ��ⲿ

	remove(DataFile);

	if (rename(DataFileTemp, DataFile)) {
		printf("����ʧ��!!!!!!!\n");
		return;
	}


	printf("�޸ĳɹ�\n");
	return;
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

Student delByIdStu(int id) {
	FILE* frp = fopen(DataFile, "r");
	//FILE* fwp = fopen("dataFileTemp.txt", "w");
	char arrBuff[128][40];//�洢��ȡ����������
	int arrNum = 0;//��¼��ǰarrBuffָ��ڼ��У�ÿһ�ζ�ȡ�����ƻ�ʹ��ֵ+1.ͬʱҲ�м��������á�

	Student s;//����ֵ
	int idT;//�ָ���һ��
	char nameT[10];//�ָ��ڶ���
	char genderT[10];//�ָ�������
	char buff[40];//һ�еĶ�ȡ����
	s.id = -1;//�Ƿ��ҵ�ƥ����ı�ʶ��

	while (fgets(buff,40,frp) != NULL) {

		strcpy(arrBuff[arrNum], buff);//��buff��һ�У������ݶ�ȡ����ά����ĵ�arrNum�У����������ǰ������buff��֮��ķָ����֮���ҵ������ô���

		idT = atoi(strtok(buff, ":"));//������ָ��������ַ������뻺��,�����������ý����������ַ�����ֹ���滻
		strcpy(nameT, strtok(NULL, ":"));
		strcpy(genderT, strtok(NULL, ":"));
			//���ƥ�䵽ɾ�����������ѭ����Ҳ�����θ���
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

	if (s.id == -1) { return s; }//����û����ѭ���и��ƣ�Ҳ��û���ҵ���ӦҪɾ�����
	//return s;

	FILE* fwp = fopen(DataFileTemp, "w");
	for (int i = 0 ; i < arrNum ; i++) {
		fputs(arrBuff[i], fwp);
	}


	fclose(fwp);
	fwp = NULL;
	
	//�����رպ���ܲ����ļ��ⲿ

	remove(DataFile);

	if (rename(DataFileTemp, DataFile)) {
		printf("����ʧ��!!!!!!!\n");
		return s;
	}

	return s;
}

Student delByNameStu(char* name) {
	FILE* frp = fopen(DataFile, "r");
	//FILE* fwp = fopen("dataFileTemp.txt", "w");
	char arrBuff[128][40];
	int arrNum = 0;//��¼��ǰarrBuffָ��ڼ��У�ÿһ�ζ�ȡ�����ƻ�ʹ��ֵ+1.ͬʱҲ�м��������á�

	Student s;
	int idT;
	char nameT[10];
	char genderT[10];
	char buff[40];
	s.id = -1;

	while (fgets(buff, 40, frp) != NULL) {

		strcpy(arrBuff[arrNum], buff);//��buff��һ�У������ݶ�ȡ����ά����ĵ�arrNum�У����������ǰ������buff��֮��ķָ����֮���ҵ������ô���

		idT = atoi(strtok(buff, ":"));//������ָ��������ַ������뻺��,�����������ý����������ַ�����ֹ���滻
		strcpy(nameT, strtok(NULL, ":"));
		strcpy(genderT, strtok(NULL, ":"));
		//���ƥ�䵽ɾ�����������ѭ����Ҳ�����θ���
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
	if (s.id == -1) { return s; }//����û����ѭ���и��ƣ�Ҳ��û���ҵ���ӦҪɾ�����


	FILE* fwp = fopen(DataFileTemp, "w");
	for (int i = 0; i < arrNum; i++) {
		fputs(arrBuff[i], fwp);
	}


	fclose(fwp);
	fwp = NULL;

	//�����رպ���ܲ����ļ��ⲿ

	remove(DataFile);

	if (rename(DataFileTemp, DataFile)) {
		printf("����ʧ��!!!!!!!\n");
		return s;
	}

	return s;
}

void insertSort() {
	char buff[64][40];//����ֱ��ʹ�ö�ά�������buff��ʡȥ�����鸴�ơ�
	int buffNum = 0;//buff��������
	int id[64];//id����
	char* buffStr[30];//�ַ�������

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
		printf("����ʧ��!!!!!!!\n");
		return;
	}

	return;
}