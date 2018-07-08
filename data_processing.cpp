#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//#include<ctype.h>

typedef struct
{
	//������Ϣ�ṹ 
  char user_name[20];           //��������
  int user_num;                  //�������˺�
  char book_name[11];           //����ͼ����
  char book_auther_name[11];          //����ͼ��������
  int book_num;                       //����ͼ����
  int borrow_date;                      //��������
  int flag;                      //�����־��0Ϊδ����1Ϊ�ѻ�
}BorrowType;

typedef struct
{
	//�û��ṹ 
	int user_status;              //����״̬��0������   1��ɾ��    2���������� 
	int user_num;                 //�û��˺�
	char user_passwd[7];          //�û����� 
	char user_name[20];           //�û�����
}UserType;

typedef struct
{
	//�鱾�ṹ 
	int book_status;                //����״̬��0������   1��ɾ��
	int book_num;                   //���
	char book_name[11];            //����
    char book_author_name[11];     //����
    int book_price;               //�۸�
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
		scanf("%d",&newbook.book_num);
		printf("������");
		scanf("%s",newbook.book_name);
		printf("���ߣ�");
		scanf("%s",newbook.book_author_name);
		printf("�۸�");
		scanf("%d",&newbook.book_price);
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
		scanf("%d",&newuser.user_num);
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
	int book_num;                    //����ı�� 
	printf("����Ҫ���µ���ı�ţ�");
	scanf("%d",&book_num);
	rewind(fp);                            //ʹλ��ָ�뷵�ص��ļ���ͷ 
	fread(&book,sizeof(BookType),1,fp) ;     //�����鼮��Ϣ 
	while(!feof(fp))
	{
		if(book.book_num==book_num&&0==book.book_status)     //�����ͬ 
			break;
		fread(&book,sizeof(BookType),1,fp) ;     //�����鼮��Ϣ
	}
	if(!feof(fp))
	{
		//��ѯ�ɹ�
		printf("���:%d\t����:%s\t����:%s\t�۸�:%d\tʣ����:%d\n",book.book_num,book.book_name,book.book_author_name,book.book_price,book.book_left) ;    //����������Ϣ
		printf("������º�����ݣ�\n");
		printf("��ţ�");
		scanf("%d",&book.book_num);
		printf("������");
		scanf("%s",book.book_name);
		printf("���ߣ�");
		scanf("%s",book.book_author_name);
		printf("�۸�");
		scanf("%d",&book.book_price);
		printf("ʣ������");
		scanf("%d",&book.book_left);
		fseek(fp,-sizeof(BookType),SEEK_CUR);             //�ƶ��ļ�λ��Ա
		fwrite(&book,sizeof(BookType),1,fp) ;
	}
	else
	{
		//��ѯʧ��
		printf("�޴˱�ŵ��飡\n");
		clearerr(fp);                           //����ļ�������־ 
	}
}
void UpdateData_user()
{
	//�����û������� 
	UserType user;                     //ĳһ�û� 
	int user_num;                    //���û��˺� 
	printf("����Ҫ���µ��û����˺ţ�");
	scanf("%d",&user_num);
	rewind(fp);                            //ʹλ��ָ�뷵�ص��ļ���ͷ 
	fread(&user,sizeof(UserType),1,fp) ;     //�����û���Ϣ 
	while(!feof(fp))
	{
		if(user.user_num==user_num&&0==user.user_status)     //�˺���ͬ 
			break;
		fread(&user,sizeof(UserType),1,fp) ;     //�����û���Ϣ
	}
	if(!feof(fp))
	{
		//��ѯ�ɹ�
		printf("�û��˺�:%d\t�û�����:%s\t�û�����:%s\n",user.user_num,user.user_name,user.user_passwd) ;    //����û�����Ϣ
		printf("������º�����ݣ�\n");
		printf("�û��˺� ��");
		scanf("%d",&user.user_num);
		printf("�û�������");
		scanf("%s",user.user_name);
		printf("�û����룺");
		scanf("%s",user.user_passwd);
		fseek(fp,-sizeof(UserType),SEEK_CUR);             //�ƶ��ļ�λ��Ա
		fwrite(&user,sizeof(UserType),1,fp) ;
	}
	else
	{
		//��ѯʧ��
		printf("�޴��û���\n");
		clearerr(fp);                           //����ļ�������־ 
	}	
}

void DeleteData_book()                 //ɾ�����ݣ�ֻ��ɾ����־ 
{
	BookType outbook;                  //Ҫɾ���� 
	int outbook_num;                   //Ҫɾ����ı�� 
	printf("����Ҫɾ������ı�ţ�") ;
	scanf("%d",&outbook_num);
	rewind(fp);                         //ʹ�ļ�λ�ó�Աָ���ļ���ͷ 
	fread(&outbook,sizeof(BookType),1,fp);    //�����鼮��Ϣ 
	while(!feof(fp))
	{
		//�ļ�ĩ����
		if(outbook_num==outbook.book_num&&0==outbook.book_status)
			break;
		fread(&outbook,sizeof(BookType),1,fp);
	}
	if(!feof(fp))
	{
		//��ѯ�ɹ�
		printf("��ɾ����¼Ϊ��\n");
		printf("���:%d\t����:%s\t����:%s\t�۸�:%d\tʣ����:%d\n",outbook.book_num,outbook.book_name,outbook.book_author_name,outbook.book_price,outbook.book_left);    //����������Ϣ
		printf("��ɾ���ɹ���"); 
		outbook.book_status=1;              //ʹ����״̬Ϊɾ��״̬
		fseek(fp,-sizeof(BookType),SEEK_CUR);       //�ƶ��ļ�λ�ó�Ա 
		fwrite(&outbook,sizeof(BookType),1,fp);      //д������  
	}	
	else
	{
		//��ѯʧ��
		printf("���޴��飡\n");
		clearerr(fp); 
	}
}
	
void DeleteData_user()                 //ɾ�����ݣ�ֻ��ɾ����־ 
{
	UserType outuser;                  //Ҫɾ���û� 
	int outuser_num;                   //Ҫɾ���û����˺� 
	printf("����Ҫɾ�����û����˺ţ�") ;
	scanf("%d",&outuser_num);
	rewind(fp);                         //ʹ�ļ�λ�ó�Աָ���ļ���ͷ 
	fread(&outuser,sizeof(UserType),1,fp);    //�����û���Ϣ 
	while(!feof(fp))
	{
		//�ļ�ĩ����
		if(outuser_num==outuser.user_num&&0==outuser.user_status)
			break;
		fread(&outuser,sizeof(UserType),1,fp);
	}
	if(!feof(fp))
	{
		//��ѯ�ɹ�
		printf("��ɾ����¼Ϊ��\n");
		printf("�û��˺�:%d\t�û�����:%s\t�û�����:%s\n",outuser.user_num,outuser.user_name,outuser.user_passwd);    //����������Ϣ
		printf("��ɾ���ɹ���");
		//getchar();
		outuser.user_status=1;              //ʹ����״̬Ϊɾ��״̬
		fseek(fp,-sizeof(UserType),SEEK_CUR);       //�ƶ��ļ�λ�ó�Ա 
		fwrite(&outuser,sizeof(UserType),1,fp);      //д������  
		
	}	
	else
	{
		//��ѯʧ��
		printf("���޴��û���\n");
		clearerr(fp); 
	}
}
	
int main()
{	
/*	int status;//����ʹ�������
    char useraccount[6];//�����˺�
    char password[7];//��������
    int password_1=0;
    int manager_0=000000;//ͼ�����Ա����
    int manager_1=111111;//ϵͳ����Ա����
    int function;//����ʹ����Ҫִ�еĹ���
    int i=0; 
    char ch;
    //UserType *person  = new UserType;
    person = (UserType*)malloc(sizeof(UserType)); 
    if(NULL == person) printf("malloc error\n");
    memset(person, 0, sizeof(UserType));
    
    printf("\t\t��ӭʹ��ͼ�����ϵͳ\n");
    printf("��ѡ��������ݣ�\n");
    printf("1.ѧ��\n");
    printf("2.��ʦ\n");
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
                   cout<<"���ļ�ʧ�ܣ�"<<endl;
                   exit(1);
               } 
               intext.read( (char *)person, sizeof(UserType));
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
                   exit(1);
               }
               intext.read((char *)person, sizeof(UserType)); 
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
			
              cout<<"ͼ�����Ա���룺";
              cin>>password_1;
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
              cin>>password_1;
              if(manager_1 == password_1)//ϵͳ����Ա��½�ɹ�
              {
                  cout<<"000";
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
              
           }
    }
        return 0;
} */
	if((fp=fopen("book.txt","rt+"))==NULL)
	{
		//book.txt�ļ�������
		 if((fp=fopen("book.txt","wt+"))==NULL)
		 {
		 	//���ļ�ʧ��
			 printf("���ļ�book.txtʧ�ܣ�\n") ;
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
