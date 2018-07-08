#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//#include<ctype.h>

typedef struct
{
	//借阅信息结构 
  char user_name[20];           //借书人名
  int user_num;                  //借书人账号
  char book_name[11];           //被借图书名
  char book_auther_name[11];          //被借图书作者名
  int book_num;                       //被借图书编号
  int borrow_date;                      //借书日期
  int flag;                      //还书标志，0为未还，1为已还
}BorrowType;

typedef struct
{
	//用户结构 
	int user_status;              //数据状态，0：正常   1：删除    2：借书逾期 
	int user_num;                 //用户账号
	char user_passwd[7];          //用户密码 
	char user_name[20];           //用户姓名
}UserType;

typedef struct
{
	//书本结构 
	int book_status;                //数据状态，0：正常   1：删除
	int book_num;                   //编号
	char book_name[11];            //书名
    char book_author_name[11];     //作者
    int book_price;               //价格
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
		scanf("%d",&newbook.book_num);
		printf("书名：");
		scanf("%s",newbook.book_name);
		printf("作者：");
		scanf("%s",newbook.book_author_name);
		printf("价格：");
		scanf("%d",&newbook.book_price);
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
		scanf("%d",&newuser.user_num);
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
	int book_num;                    //该书的编号 
	printf("输入要更新的书的编号：");
	scanf("%d",&book_num);
	rewind(fp);                            //使位置指针返回到文件开头 
	fread(&book,sizeof(BookType),1,fp) ;     //读入书籍信息 
	while(!feof(fp))
	{
		if(book.book_num==book_num&&0==book.book_status)     //编号相同 
			break;
		fread(&book,sizeof(BookType),1,fp) ;     //读入书籍信息
	}
	if(!feof(fp))
	{
		//查询成功
		printf("编号:%d\t书名:%s\t作者:%s\t价格:%d\t剩余量:%d\n",book.book_num,book.book_name,book.book_author_name,book.book_price,book.book_left) ;    //输出该书的信息
		printf("输入更新后的数据：\n");
		printf("编号：");
		scanf("%d",&book.book_num);
		printf("书名：");
		scanf("%s",book.book_name);
		printf("作者：");
		scanf("%s",book.book_author_name);
		printf("价格：");
		scanf("%d",&book.book_price);
		printf("剩余量：");
		scanf("%d",&book.book_left);
		fseek(fp,-sizeof(BookType),SEEK_CUR);             //移动文件位成员
		fwrite(&book,sizeof(BookType),1,fp) ;
	}
	else
	{
		//查询失败
		printf("无此编号的书！\n");
		clearerr(fp);                           //清除文件结束标志 
	}
}
void UpdateData_user()
{
	//更新用户的数据 
	UserType user;                     //某一用户 
	int user_num;                    //该用户账号 
	printf("输入要更新的用户的账号：");
	scanf("%d",&user_num);
	rewind(fp);                            //使位置指针返回到文件开头 
	fread(&user,sizeof(UserType),1,fp) ;     //读入用户信息 
	while(!feof(fp))
	{
		if(user.user_num==user_num&&0==user.user_status)     //账号相同 
			break;
		fread(&user,sizeof(UserType),1,fp) ;     //读入用户信息
	}
	if(!feof(fp))
	{
		//查询成功
		printf("用户账号:%d\t用户姓名:%s\t用户密码:%s\n",user.user_num,user.user_name,user.user_passwd) ;    //输出用户的信息
		printf("输入更新后的数据：\n");
		printf("用户账号 ：");
		scanf("%d",&user.user_num);
		printf("用户姓名：");
		scanf("%s",user.user_name);
		printf("用户密码：");
		scanf("%s",user.user_passwd);
		fseek(fp,-sizeof(UserType),SEEK_CUR);             //移动文件位成员
		fwrite(&user,sizeof(UserType),1,fp) ;
	}
	else
	{
		//查询失败
		printf("无此用户！\n");
		clearerr(fp);                           //清除文件结束标志 
	}	
}

void DeleteData_book()                 //删除数据，只作删除标志 
{
	BookType outbook;                  //要删的书 
	int outbook_num;                   //要删的书的编号 
	printf("输入要删除的书的编号：") ;
	scanf("%d",&outbook_num);
	rewind(fp);                         //使文件位置成员指向文件开头 
	fread(&outbook,sizeof(BookType),1,fp);    //读入书籍信息 
	while(!feof(fp))
	{
		//文件末结束
		if(outbook_num==outbook.book_num&&0==outbook.book_status)
			break;
		fread(&outbook,sizeof(BookType),1,fp);
	}
	if(!feof(fp))
	{
		//查询成功
		printf("被删除记录为：\n");
		printf("编号:%d\t书名:%s\t作者:%s\t价格:%d\t剩余量:%d\n",outbook.book_num,outbook.book_name,outbook.book_author_name,outbook.book_price,outbook.book_left);    //输出该书的信息
		printf("已删除成功！"); 
		outbook.book_status=1;              //使数据状态为删除状态
		fseek(fp,-sizeof(BookType),SEEK_CUR);       //移动文件位置成员 
		fwrite(&outbook,sizeof(BookType),1,fp);      //写入数据  
	}	
	else
	{
		//查询失败
		printf("查无此书！\n");
		clearerr(fp); 
	}
}
	
void DeleteData_user()                 //删除数据，只作删除标志 
{
	UserType outuser;                  //要删的用户 
	int outuser_num;                   //要删的用户的账号 
	printf("输入要删除的用户的账号：") ;
	scanf("%d",&outuser_num);
	rewind(fp);                         //使文件位置成员指向文件开头 
	fread(&outuser,sizeof(UserType),1,fp);    //读入用户信息 
	while(!feof(fp))
	{
		//文件末结束
		if(outuser_num==outuser.user_num&&0==outuser.user_status)
			break;
		fread(&outuser,sizeof(UserType),1,fp);
	}
	if(!feof(fp))
	{
		//查询成功
		printf("被删除记录为：\n");
		printf("用户账号:%d\t用户姓名:%s\t用户密码:%s\n",outuser.user_num,outuser.user_name,outuser.user_passwd);    //输出该书的信息
		printf("已删除成功！");
		//getchar();
		outuser.user_status=1;              //使数据状态为删除状态
		fseek(fp,-sizeof(UserType),SEEK_CUR);       //移动文件位置成员 
		fwrite(&outuser,sizeof(UserType),1,fp);      //写入数据  
		
	}	
	else
	{
		//查询失败
		printf("查无此用户！\n");
		clearerr(fp); 
	}
}
	
int main()
{	
/*	int status;//接收使用者身份
    char useraccount[6];//接收账号
    char password[7];//接收密码
    int password_1=0;
    int manager_0=000000;//图书管理员密码
    int manager_1=111111;//系统管理员密码
    int function;//接收使用者要执行的功能
    int i=0; 
    char ch;
    //UserType *person  = new UserType;
    person = (UserType*)malloc(sizeof(UserType)); 
    if(NULL == person) printf("malloc error\n");
    memset(person, 0, sizeof(UserType));
    
    printf("\t\t欢迎使用图书管理系统\n");
    printf("请选择您的身份：\n");
    printf("1.学生\n");
    printf("2.老师\n");
    cout<<"3.图书管理员"<<endl;
    cout<<"4.系统管理员"<<endl;
    cin>>status;
    switch(status)
    {
        case 1:
             {
			 
               cout<<"请输入账号和密码："<<endl;
               cout<<"账号：";
               cin>>useraccount;
               cout<<"密码：";
               while(i<6&&(ch=getch())!='\r')
               {
                  password[i++]=ch;
                  putchar('*');
               }
               password[i]='\0';
               cout<<password;
               ifstream intext("user.txt");
               if(intext.fail())
               {
                   cout<<"打开文件失败！"<<endl;
                   exit(1);
               } 
               intext.read( (char *)person, sizeof(UserType));
               while(!intext.eof())//文件未结束
               { 
                    if(!strcmp(useraccount,person->user_num))//找到匹配账户，检验密码
                    {
                       if(!strcmp(password,person->user_passwd))
                       {
                           cout<<"登陆成功！"<<endl;
                           cout<<"请选择您要执行的操作："<<endl;
                           cout<<"1.办理图书借阅"<<endl;
                           cout<<"2.办理图书归还"<<endl;
                           cin>>function;
                      
                       }
                  
                    }
                   else
                   {
                       intext.read((char *)person ,sizeof(UserType));
                   }

              }
              intext.close();
              break;
           }

        case 2:
            {
			
               cout<<"请输入账号和密码："<<endl;
               cout<<"账号：";
               cin>>useraccount;
               cout<<"密码：";
               for(i=0;i<6;i++)
               {
                   password[i]=getch();
                   putchar('*');
               }
               ifstream intext("user.txt");
               if(intext.fail())
               {
                   cout<<"打开文件失败！"<<endl;
                   exit(1);
               }
               intext.read((char *)person, sizeof(UserType)); 
               while(!intext.eof())//文件未结束
               { 
	              if(!strcmp(useraccount,person->user_num))//找到匹配账户，检验密码
	               {
	                  if(!strcmp(password,person->user_passwd))
	                  {
	                      cout<<"登陆成功！"<<endl;
	                      cout<<"请选择您要执行的操作："<<endl;
	                      cout<<"1.办理图书借阅"<<endl;
	                      cout<<"2.办理图书归还"<<endl;
	                      cin>>function;
	                      break;
	                  }
	                  
	              }
	              else
	              {
	                  intext.read((char *)person ,sizeof(UserType));
	              }
	
	            }
	            intext.close();
	            break;
            }  
        
        case 3:
            {
			
              cout<<"图书管理员密码：";
              cin>>password_1;
              if(manager_0==password_1)//图书管理员登陆成功
              {
                  cout<<"登陆成功!"<<endl;
                  cout<<"请选择您要执行的操作："<<endl;
                  cout<<"1.图书信息的录入"<<endl;
                  cout<<"2.图书信息的修改"<<endl;
                  cout<<"3.图书信息的删除"<<endl;
                  cout<<"4.图书信息的查询"<<endl;
                  cout<<"5.办理图书借阅"<<endl;
                  cout<<"6.办理图书归还"<<endl;
                  cin>>function;
                 
                
              }
              break;
            }
            
        case 4:
        	{
			
              cout<<"系统管理员密码：";
              cin>>password_1;
              if(manager_1 == password_1)//系统管理员登陆成功
              {
                  cout<<"000";
				  cout<<"登陆成功！"<<endl;
                  cout<<"请选择您要执行的操作："<<endl;
                  cout<<"1.图书信息的录入"<<endl;
                  cout<<"2.图书信息的修改"<<endl;
                  cout<<"3.图书信息的删除"<<endl;
                  cout<<"4.图书信息的查询"<<endl;
                  cout<<"5.读者信息的录入"<<endl;
                  cout<<"6.读者信息的修改"<<endl;
                  cout<<"7.读者信息的删除"<<endl;
                  cin>>function;
              }
              
           }
    }
        return 0;
} */
	if((fp=fopen("book.txt","rt+"))==NULL)
	{
		//book.txt文件不存在
		 if((fp=fopen("book.txt","wt+"))==NULL)
		 {
		 	//打开文件失败
			 printf("打开文件book.txt失败！\n") ;
			 exit(1);
		 }
	}
	//AddData_book();                          
	AddData_user();
	//UpdateData_book();                      
	//UpdateData_user(); 
	//DeleteData_book();                       
	//DeleteData_user();
	fclose(fp);
}
