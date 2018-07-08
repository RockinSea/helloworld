#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

typedef struct 
{
  char person_name[20];   //借书人名
  int usernum;           //借书人账号
  char book_name[11];    //被借图书名
  char book_author_name[11];   //被借图书作者名
  int book_num;                //被借图书编号
  int date;               //借书日期
  int flag;               //还书标志，0为未还，1为已还
}BorrowType;

typedef struct
{
	//书本结构 
	int book_status;             //数据状态，0：正常   1：删除
	int book_num;                 //编号
	char book_name[11];              //书名
    char book_author_name[11];      //作者
    int book_price;               //价格
    int book_left;                //剩余量
    
}BookType;


int Searchbook()
{
	
    int choice;//接收使用者选择的查询方式
    BookType temple;
    int fact_left=-1;//接收剩余量,-1表示查无此书
    FILE *fp;
	if((fp=fopen("book.txt","rt"))==NULL)
    {
        cout<<"打开文件失败！"<<endl;
        exit(1);
    }  
    cout<<"请选择要查询图书的方式（输入对应的数字1或2或3即可）："<<endl;
    cout<<"1.按书名查询"<<endl;
    cout<<"2.按作者查询"<<endl;
    cout<<"3.按编号查询"<<endl;
    cin>>choice;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
                                          
    switch(choice)
    {
        case 1:
        {
            char str1[11];//接收要查询的书名
            cout<<"请输入书名："<<endl;
            cin>>str1;
            rewind(fp);
            fread(&temple,sizeof(BookType),1,fp);
            while(!feof(fp))//文件未结束
            { 
              if(!strcmp(str1,(temple.book_name)))
              {
                  fact_left=temple.book_left;//找到匹配书目，查询剩余量
                  break;
              }
              else
              {
                  fread(&temple,sizeof(BookType),1,fp);
              }

            }
            break;

        }

        case 2:
        {
            char str2[11];//接收要查询的作者
            cout<<"请输入作者："<<endl;
            cin>>str2;
            while(!feof(fp))//文件未结束
            { 
              if(!strcmp(str2,temple.book_author_name))
              {
                  fact_left=temple.book_left;//找到匹配作者，查询剩余量
                  break;
              }
              else
              {
                  fread(&temple,sizeof(BookType),1,fp);

              }
           }
            break;

        }

        case 3:
        {
            int code;//接收要查询的编号
            cout<<"请输入编号："<<endl;
            cin>>code;
            while(!feof(fp))//文件未结束
            { 
              if(code == (temple.book_num))
              {
                  fact_left=temple.book_left;//找到匹配编号，查询剩余量
                  break;
              }
              else
              {
                  fread(&temple,sizeof(BookType),1,fp);
              }

            }
            break;
       }

    }
    fclose(fp);
    return fact_left;
}



void Borrowbook()
{   
    int n;//接受剩余量 
    BorrowType borrow1; //接收借阅信息 
    cout<<"请搜索要借阅的书籍："<<endl;
    n=Searchbook();
	if(n== -1) 	
	{
	   cout<<"借阅失败！查无此书！"<<endl;
	}
	else if(n==0) 
	{ 
	   cout<<"借阅失败！此书已被借阅，无剩余！"<<endl;
	}
	else 
	{   
		cout<<"所查书籍剩余"<<n<<"本，可借阅" <<endl; 
		cout<<"登记借阅信息:"<<endl;
		cout<<"请输入借阅者姓名：";
	    cin>>borrow1.person_name;
	    cout<<"请输入借阅者账号：";
		cin>>borrow1.usernum;
		cout<<"请输入被借图书名："; 
		cin>>borrow1.book_name;
		cout<<"请输入被借图书作者名：";
		cin>>borrow1.book_author_name;
		cout<<"请输入被借书编号：";
		cin>>borrow1.book_num;
		cout<<"请输入借书日期：";
		cin>>borrow1.date;
		borrow1.flag=0;
	    FILE *zf;
	    if((zf=fopen("borrow.txt","at"))==NULL)
        {
            cout<<"打开文件失败！"<<endl;
            exit(1);
        }  
        fwrite(&borrow1,sizeof(BorrowType),1,zf);	
        fclose(zf);
		cout<<"借阅成功！请用心保管！"<<endl;
		
		//修改库存记录 
		int book_num1=borrow1.book_num;
		FILE *tp;
		BookType temple1;
	    if((tp=fopen("book.txt","rt+"))==NULL)
        {
          cout<<"打开文件失败！"<<endl;
          exit(2);
        }  
        rewind(tp);
        fread(&temple1,sizeof(BookType),1,tp);
        while(!feof(tp))//文件未结束
        { 
            if(book_num1 == temple1.book_num)
            {
				break;
            }
            else
            {
                fread(&temple1,sizeof(BookType),1,tp);
            }
        }
        if(!feof(tp))
        {
		    temple1.book_left=temple1.book_left-1;
            fseek(tp,-sizeof(BookType),SEEK_CUR);            
		    fwrite(&temple1,sizeof(BookType),1,tp);
		}
        fclose(tp);		
		
	 } 
 } 
 
 
 void Sendback()
 {
 	int backbook;
 	BorrowType temple;
	cout<<"请输入所还书籍的编号:";
	cin>>backbook;
	FILE *fp;
	if((fp=fopen("borrow.txt","rt+"))==NULL)
    {
        cout<<"打开文件失败！"<<endl;
        exit(1);
    }  
    rewind(fp);
    fread(&temple,sizeof(BorrowType),1,fp);
    while(!feof(fp))//文件未结束
    { 
        if(backbook == temple.book_num)
        {
		    temple.flag=1;     //表示已经还书          
            fseek(fp,-sizeof(BorrowType),SEEK_CUR);             //移动文件位成员
		    fwrite(&temple,sizeof(BorrowType),1,fp) ;
			break;
        }
        else
        {
            fread(&temple,sizeof(BorrowType),1,fp);
        }

    }
    fclose(fp);
    FILE *tp;
	BookType temple1;
	if((tp=fopen("book.txt","rt+"))==NULL)
    {
        cout<<"打开文件失败！"<<endl;
        exit(2);
    }  
    rewind(tp);
    fread(&temple1,sizeof(BookType),1,tp);
    while(!feof(tp))//文件未结束
    { 
        if(backbook == temple1.book_num)
        {
            temple1.book_left=temple1.book_left+1;//找到匹配编号，查询剩余量
            fseek(tp,-sizeof(BookType),SEEK_CUR);             //移动文件位成员
		    fwrite(&temple1,sizeof(BookType),1,tp) ;
			break;
        }
        else
        {
            fread(&temple1,sizeof(BookType),1,tp);
        }

    }
    fclose(tp);
	cout<<"还书成功！";	
	
 }
 
 int main()
 {
 	cout<<"欢迎使用借书";
    Borrowbook();
 	int n=Searchbook();
 	cout<<n;
 	return 0;
 }
 
 

 
 
 
