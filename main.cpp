#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<unistd.h>
#include<stdlib.h>
using namespace std;
typedef struct
{
	//�û��ṹ 
	char user_status[5]="0";         //����״̬��0������   1��ɾ��    2���������� 
	char user_num[7]="0";             //�û��˺�
	char user_passwd[7]="0";          //�û����� 
	char user_name[20]="0";       //�û�����
}UserType;


int main()
{
    int status;//����ʹ�������
    char useraccount[7];//�����˺�
    char password[7];//��������
    int password_1;
    int manager_0=000000;//ͼ�����Ա����
    int manager_1=111111;//ϵͳ����Ա����
    int function;//����ʹ����Ҫִ�еĹ���
    int i=0; 
    UserType *person;
    cout<<'\t'<<"��ӭʹ��ͼ�����ϵͳ"<<endl;
    cout<<"��ѡ��������ݣ�"<<endl;
    cout<<"1.ѧ��"<<endl;
    cout<<"2.��ʦ"<<endl;
    cout<<"3.ͼ�����Ա"<<endl;
    cout<<"4.ϵͳ����Ա"<<endl;
    cin>>status;
    switch(status)
    {
        case 1:
             {
			 
               cout<<"�������˺ź����룺"<<endl;
               cout<<"�˺ţ�";
               cin>>useraccount;
               cout<<"���룺";
               for(i=0;i<6;i++)
               {
                   password[i]=getch();
                   putchar('*');
               }
               ifstream intext("user.txt");
               if(intext.fail())
               {
                   cout<<"���ļ�ʧ�ܣ�"<<endl;
                   
               }
               intext.read((char *)person,sizeof(UserType)); 
               while(!intext.eof())//�ļ�δ����
               { 
            		if(strcmp(useraccount,person->user_num)==0&&strcmp(password,person->user_passwd)==0)//�ҵ�ƥ���˻�����������
               			{
                  			
			                      cout<<"��½�ɹ���"<<endl;
			                      cout<<"��ѡ����Ҫִ�еĲ�����"<<endl;
			                      cout<<"1.����ͼ�����"<<endl;
			                      cout<<"2.����ͼ��黹"<<endl;
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
			
               cout<<"�������˺ź����룺"<<endl;
               cout<<"�˺ţ�";
               cin>>useraccount;
               cout<<"���룺";
               for(i=0;i<6;i++)
               {
                   password[i]=getch();
                   putchar('*');
               }
               ifstream intext("user.txt");
               if(intext.fail())
               {
                   cout<<"���ļ�ʧ�ܣ�"<<endl;
                
               }
               intext.read((char *)person,sizeof(UserType)); 
               while(!intext.eof())//�ļ�δ����
               { 
              if(!strcmp(useraccount,person->user_num))//�ҵ�ƥ���˻�����������
               {
                  if(!strcmp(password,person->user_passwd))
                  {
                      cout<<"��½�ɹ���"<<endl;
                      cout<<"��ѡ����Ҫִ�еĲ�����"<<endl;
                      cout<<"1.����ͼ�����"<<endl;
                      cout<<"2.����ͼ��黹"<<endl;
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
			
              cout<<"ͼ�����Ա���룺";
              cin>>password;
              if(manager_0==password_1)//ͼ�����Ա��½�ɹ�
              {
                  cout<<"��½�ɹ�!"<<endl;
                  cout<<"��ѡ����Ҫִ�еĲ�����"<<endl;
                  cout<<"1.ͼ����Ϣ��¼��"<<endl;
                  cout<<"2.ͼ����Ϣ���޸�"<<endl;
                  cout<<"3.ͼ����Ϣ��ɾ��"<<endl;
                  cout<<"4.ͼ����Ϣ�Ĳ�ѯ"<<endl;
                  cout<<"5.����ͼ�����"<<endl;
                  cout<<"6.����ͼ��黹"<<endl;
                  cin>>function;
                 
                
              }
              break;
            }
            
        case 4:
        	{
			
              cout<<"ϵͳ����Ա���룺";
              cin>>password;
              if(manager_1==password_1)//ϵͳ����Ա��½�ɹ�
              {
                  cout<<"��½�ɹ���"<<endl;
                  cout<<"��ѡ����Ҫִ�еĲ�����"<<endl;
                  cout<<"1.ͼ����Ϣ��¼��"<<endl;
                  cout<<"2.ͼ����Ϣ���޸�"<<endl;
                  cout<<"3.ͼ����Ϣ��ɾ��"<<endl;
                  cout<<"4.ͼ����Ϣ�Ĳ�ѯ"<<endl;
                  cout<<"5.������Ϣ��¼��"<<endl;
                  cout<<"6.������Ϣ���޸�"<<endl;
                  cout<<"7.������Ϣ��ɾ��"<<endl;
                  cin>>function;
              }
              break;
           }
    }
        return 0;
}

