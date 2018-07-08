#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<unistd.h>
#include<stdlib.h>
using namespace std;
typedef struct
{
	//用户结构 
	char user_status[5]="0";         //数据状态，0：正常   1：删除    2：借书逾期 
	char user_num[7]="0";             //用户账号
	char user_passwd[7]="0";          //用户密码 
	char user_name[20]="0";       //用户姓名
}UserType;


int main()
{
    int status;//接收使用者身份
    char useraccount[7];//接收账号
    char password[7];//接收密码
    int password_1;
    int manager_0=000000;//图书管理员密码
    int manager_1=111111;//系统管理员密码
    int function;//接受使用者要执行的功能
    int i=0; 
    UserType *person;
    cout<<'\t'<<"欢迎使用图书管理系统"<<endl;
    cout<<"请选择您的身份："<<endl;
    cout<<"1.学生"<<endl;
    cout<<"2.老师"<<endl;
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
               for(i=0;i<6;i++)
               {
                   password[i]=getch();
                   putchar('*');
               }
               ifstream intext("user.txt");
               if(intext.fail())
               {
                   cout<<"打开文件失败！"<<endl;
                   
               }
               intext.read((char *)person,sizeof(UserType)); 
               while(!intext.eof())//文件未结束
               { 
            		if(strcmp(useraccount,person->user_num)==0&&strcmp(password,person->user_passwd)==0)//找到匹配账户，检验密码
               			{
                  			
			                      cout<<"登陆成功！"<<endl;
			                      cout<<"请选择您要执行的操作："<<endl;
			                      cout<<"1.办理图书借阅"<<endl;
			                      cout<<"2.办理图书归还"<<endl;
			                      cin>>function;
			                      getchar();
			                      break;
                  				
                  
            			}
              
              
                   intext.read((char *)person ,sizeof(UserType));
              

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
                
               }
               intext.read((char *)person,sizeof(UserType)); 
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
                  break;
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
              cin>>password;
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
              cin>>password;
              if(manager_1==password_1)//系统管理员登陆成功
              {
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
              break;
           }
    }
        return 0;
}

