#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

typedef struct
{
	//���ڽṹ 
	int year;
	int month;
	int day;
}DateType;

typedef struct
{
	//�û��ṹ 
	int user_status=0;              //����״̬��0������   1��ɾ��    2���������� 
	char user_num[7]="0";             //�û��˺�
	char user_passwd[7]="0";          //�û����� 
	char user_name[20]="0";           //�û�����
}UserType;

typedef struct
{
	//�鱾�ṹ 
	int book_status=0;             //����״̬��0������   1��ɾ��
	char book_num[11]="0";                 //���
	char book_name[11]="0";              //����
    char book_author_name[11]="0";      //����
    char book_price[11]="0";               //�۸�
    int book_left;                //ʣ����
    
}BookType;

FILE *fp;                     //�����ļ�ָ�� 

void AddData_book()
{
	BookType newbook;      //����
	char tag;              //���ñ�־���ڱ�ʾ�Ƿ�����������
	newbook.book_status=0;
	do
	{
		printf("��ţ�");
		scanf("%s",newbook.book_num);
		printf("������");
		scanf("%s",newbook.book_name);
		printf("���ߣ�");
		scanf("%s",newbook.book_author_name);
		printf("�۸�");
		scanf("%s",newbook.book_price);
		printf("ʣ������");
		scanf("%d",&newbook.book_left);
		
		fseek(fp,0,SEEK_END);              //�ƶ��ļ��ڲ�λ��ָ�� 
		fwrite(&newbook,sizeof(BookType),1,fp);     //��������Ϣ�����ļ��� 
		printf("���������y/n����"); 
		tag=getchar();                    //y��ʾ������n��ʾ����
		while(tag!='y'&&tag!='n')
		{
			printf("����Ƿ����������루y/n��");
			tag=getchar();
		} 
		
	}while(tag=='y'); 
		 
}

void AddData_user()
{
	UserType newuser;      //���û� 
	char tag;              //���ñ�־���ڱ�ʾ�Ƿ�����������
	newuser.user_status=0;
	do
	{
		printf("�˺ţ�");
		scanf("%s",newuser.user_num);
		printf("���룺");
		scanf("%s",newuser.user_passwd);
		printf("������");
		scanf("%s",newuser.user_name);
		
		
		fseek(fp,0,SEEK_END);              //�ƶ��ļ��ڲ�λ��ָ�� 
		fwrite(&newuser,sizeof(UserType),1,fp);     //��������Ϣ�����ļ��� 
		printf("���������y/n����"); 
		tag=getchar();                    //y��ʾ������n��ʾ����
		while(tag!='y'&&tag!='n')
		{
			printf("����Ƿ����������루y/n��");
			tag=getchar();
		} 
		
	}while(tag=='y'); 
} 

void UpdateData_book()
{
	//����������� 
	BookType book;                     //ĳһ���� 
	char book_num[11];                    //����ı�� 
	printf("����Ҫ���µ���ı�ţ�");
	scanf("%s",book_num);
	rewind(fp);                            //ʹλ��ָ�뷵�ص��ļ���ͷ 
	fread(&book,sizeof(BookType),1,fp) ;     //����Ա����Ϣ 
	while(!feof(fp))
	{
		if(strcmp(book.book_num,book_num)==0&&book.book_status==0)
	}
	
	
	
	
}
























int main()
{
	fp=fopen("book.txt","at+");
	AddData_book();
	fclose(fp);
}




















