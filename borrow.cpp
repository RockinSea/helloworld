#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

typedef struct 
{
  char person_name[20];   //��������
  int usernum;           //�������˺�
  char book_name[11];    //����ͼ����
  char book_author_name[11];   //����ͼ��������
  int book_num;                //����ͼ����
  int date;               //��������
  int flag;               //�����־��0Ϊδ����1Ϊ�ѻ�
}BorrowType;

typedef struct
{
	//�鱾�ṹ 
	int book_status;             //����״̬��0������   1��ɾ��
	int book_num;                 //���
	char book_name[11];              //����
    char book_author_name[11];      //����
    int book_price;               //�۸�
    int book_left;                //ʣ����
    
}BookType;


int Searchbook()
{
	
    int choice;//����ʹ����ѡ��Ĳ�ѯ��ʽ
    BookType temple;
    int fact_left=-1;//����ʣ����,-1��ʾ���޴���
    FILE *fp;
	if((fp=fopen("book.txt","rt"))==NULL)
    {
        cout<<"���ļ�ʧ�ܣ�"<<endl;
        exit(1);
    }  
    cout<<"��ѡ��Ҫ��ѯͼ��ķ�ʽ�������Ӧ������1��2��3���ɣ���"<<endl;
    cout<<"1.��������ѯ"<<endl;
    cout<<"2.�����߲�ѯ"<<endl;
    cout<<"3.����Ų�ѯ"<<endl;
    cin>>choice;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
                                          
    switch(choice)
    {
        case 1:
        {
            char str1[11];//����Ҫ��ѯ������
            cout<<"������������"<<endl;
            cin>>str1;
            rewind(fp);
            fread(&temple,sizeof(BookType),1,fp);
            while(!feof(fp))//�ļ�δ����
            { 
              if(!strcmp(str1,(temple.book_name)))
              {
                  fact_left=temple.book_left;//�ҵ�ƥ����Ŀ����ѯʣ����
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
            char str2[11];//����Ҫ��ѯ������
            cout<<"���������ߣ�"<<endl;
            cin>>str2;
            while(!feof(fp))//�ļ�δ����
            { 
              if(!strcmp(str2,temple.book_author_name))
              {
                  fact_left=temple.book_left;//�ҵ�ƥ�����ߣ���ѯʣ����
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
            int code;//����Ҫ��ѯ�ı��
            cout<<"�������ţ�"<<endl;
            cin>>code;
            while(!feof(fp))//�ļ�δ����
            { 
              if(code == (temple.book_num))
              {
                  fact_left=temple.book_left;//�ҵ�ƥ���ţ���ѯʣ����
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
    int n;//����ʣ���� 
    BorrowType borrow1; //���ս�����Ϣ 
    cout<<"������Ҫ���ĵ��鼮��"<<endl;
    n=Searchbook();
	if(n== -1) 	
	{
	   cout<<"����ʧ�ܣ����޴��飡"<<endl;
	}
	else if(n==0) 
	{ 
	   cout<<"����ʧ�ܣ������ѱ����ģ���ʣ�࣡"<<endl;
	}
	else 
	{   
		cout<<"�����鼮ʣ��"<<n<<"�����ɽ���" <<endl; 
		cout<<"�Ǽǽ�����Ϣ:"<<endl;
		cout<<"�����������������";
	    cin>>borrow1.person_name;
	    cout<<"������������˺ţ�";
		cin>>borrow1.usernum;
		cout<<"�����뱻��ͼ������"; 
		cin>>borrow1.book_name;
		cout<<"�����뱻��ͼ����������";
		cin>>borrow1.book_author_name;
		cout<<"�����뱻�����ţ�";
		cin>>borrow1.book_num;
		cout<<"������������ڣ�";
		cin>>borrow1.date;
		borrow1.flag=0;
	    FILE *zf;
	    if((zf=fopen("borrow.txt","at"))==NULL)
        {
            cout<<"���ļ�ʧ�ܣ�"<<endl;
            exit(1);
        }  
        fwrite(&borrow1,sizeof(BorrowType),1,zf);	
        fclose(zf);
		cout<<"���ĳɹ��������ı��ܣ�"<<endl;
		
		//�޸Ŀ���¼ 
		int book_num1=borrow1.book_num;
		FILE *tp;
		BookType temple1;
	    if((tp=fopen("book.txt","rt+"))==NULL)
        {
          cout<<"���ļ�ʧ�ܣ�"<<endl;
          exit(2);
        }  
        rewind(tp);
        fread(&temple1,sizeof(BookType),1,tp);
        while(!feof(tp))//�ļ�δ����
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
	cout<<"�����������鼮�ı��:";
	cin>>backbook;
	FILE *fp;
	if((fp=fopen("borrow.txt","rt+"))==NULL)
    {
        cout<<"���ļ�ʧ�ܣ�"<<endl;
        exit(1);
    }  
    rewind(fp);
    fread(&temple,sizeof(BorrowType),1,fp);
    while(!feof(fp))//�ļ�δ����
    { 
        if(backbook == temple.book_num)
        {
		    temple.flag=1;     //��ʾ�Ѿ�����          
            fseek(fp,-sizeof(BorrowType),SEEK_CUR);             //�ƶ��ļ�λ��Ա
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
        cout<<"���ļ�ʧ�ܣ�"<<endl;
        exit(2);
    }  
    rewind(tp);
    fread(&temple1,sizeof(BookType),1,tp);
    while(!feof(tp))//�ļ�δ����
    { 
        if(backbook == temple1.book_num)
        {
            temple1.book_left=temple1.book_left+1;//�ҵ�ƥ���ţ���ѯʣ����
            fseek(tp,-sizeof(BookType),SEEK_CUR);             //�ƶ��ļ�λ��Ա
		    fwrite(&temple1,sizeof(BookType),1,tp) ;
			break;
        }
        else
        {
            fread(&temple1,sizeof(BookType),1,tp);
        }

    }
    fclose(tp);
	cout<<"����ɹ���";	
	
 }
 
 int main()
 {
 	cout<<"��ӭʹ�ý���";
    Borrowbook();
 	int n=Searchbook();
 	cout<<n;
 	return 0;
 }
 
 

 
 
 
