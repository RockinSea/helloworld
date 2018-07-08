#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

typedef struct
{
	//日期结构 
	int year;
	int month;
	int day;
}DateType;

typedef struct
{
	//用户结构 
	int user_status=0;              //数据状态，0：正常   1：删除    2：借书逾期 
	char user_num[7]="0";             //用户账号
	char user_passwd[7]="0";          //用户密码 
	char user_name[20]="0";           //用户姓名
}UserType;

typedef struct
{
	//书本结构 
	int book_status=0;             //数据状态，0：正常   1：删除
	char book_num[11]="0";                 //编号
	char book_name[11]="0";              //书名
    char book_author_name[11]="0";      //作者
    char book_price[11]="0";               //价格
    int book_left;                //剩余量
    
}BookType;

FILE *fp;                     //声明文件指针 

void AddData_book()
{
	BookType newbook;      //新书
	char tag;              //设置标志用于表示是否继续添加数据
	newbook.book_status=0;
	do
	{
		printf("编号：");
		scanf("%s",newbook.book_num);
		printf("书名：");
		scanf("%s",newbook.book_name);
		printf("作者：");
		scanf("%s",newbook.book_author_name);
		printf("价格：");
		scanf("%s",newbook.book_price);
		printf("剩余量：");
		scanf("%d",&newbook.book_left);
		
		fseek(fp,0,SEEK_END);              //移动文件内部位置指针 
		fwrite(&newbook,sizeof(BookType),1,fp);     //将新书信息存入文件中 
		printf("继续添加吗（y/n）："); 
		tag=getchar();                    //y表示继续，n表示结束
		while(tag!='y'&&tag!='n')
		{
			printf("输入非法，重新输入（y/n）");
			tag=getchar();
		} 
		
	}while(tag=='y'); 
		 
}

void AddData_user()
{
	UserType newuser;      //新用户 
	char tag;              //设置标志用于表示是否继续添加数据
	newuser.user_status=0;
	do
	{
		printf("账号：");
		scanf("%s",newuser.user_num);
		printf("密码：");
		scanf("%s",newuser.user_passwd);
		printf("姓名：");
		scanf("%s",newuser.user_name);
		
		
		fseek(fp,0,SEEK_END);              //移动文件内部位置指针 
		fwrite(&newuser,sizeof(UserType),1,fp);     //将新书信息存入文件中 
		printf("继续添加吗（y/n）："); 
		tag=getchar();                    //y表示继续，n表示结束
		while(tag!='y'&&tag!='n')
		{
			printf("输入非法，重新输入（y/n）");
			tag=getchar();
		} 
		
	}while(tag=='y'); 
} 

void UpdateData_book()
{
	//更新书的数据 
	BookType book;                     //某一本书 
	char book_num[11];                    //该书的编号 
	printf("输入要更新的书的编号：");
	scanf("%s",book_num);
	rewind(fp);                            //使位置指针返回到文件开头 
	fread(&book,sizeof(BookType),1,fp) ;     //读入员工信息 
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




















