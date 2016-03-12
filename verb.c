/*
本代码 只实现了基本功能 代码冗余没时间修改，前面定义的数组基本没用
*/ 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
int colum;         //出错行
char messages[100];  //出错消息
char digit[10] = {'0','1','2','3','4','5','6','7','8','9'};  //构建数字表
char letter_[53]; //构建字母表
char bound[8] = {'{','}',';','[',']','(',')','.'};
char bounds[8][10] = {"LP","RP","SEMI","MLP","MRP","SLP","SRP","DOT"};//token name
char keyword[11][20] = {"float","boolean","doc","int","if","else","do","while","for","return","char"};
//char op[]={'+','-','*','/','!','^','%'};
char result[20];
char temp[100];
void stateConvert(char nowWord,int col);
int  record=0;
int recordExcute=0;
int expFlag=0;
int globeCount=1;
int m=0;
int main()
{
    FILE *fp=fopen("E://CYU/test/test.txt","r+");
    result[0]='#';//最为清空的标志
    int i;
   // char str[100];
   char str[100];
   char* temp=str;
    for(int i=0;i<=19;i++)
    {
        result[i]='\0';
    }
    for(int i=0;i<=99;i++)
    {
        temp[i]='\0';
    }
   int flag=0;
    colum = 1;
    for(i = 0;i < 26;i++)
    {
        letter_[i] = 'A'+i;
        letter_[i+26] = letter_[i]+32;
    }
    letter_[52] = '_';    //字母表构造完成
    if(fp == NULL)
    {
        printf("Error Openning");
        exit(0);
    }

    while(!feof(fp))
    {
        //printf("%s\n",str);
        fgets(temp,100,fp);
                i = 0;
      while(str[i] != '\0')
        {
            switch (str[i])
            {
            case ' ':
                {
                i++;
                flag=1;
                break;
                }
            case '\n':
                i++;
                flag=1;
                break;
            case '\t':
                i++;
                flag=1;
                break;
            case '\r':
                i++;
                flag=1;
                break;
            default:
                flag=0;
                break;
            }
            if(flag==0)
            {
                stateConvert(str[i],colum);
                i++;
            }
        // cout<<"是的是的"<<endl;
        // cout<<str[i]<<endl;
        }
       if(str[i]=='\0')
        {
            stateConvert(str[i],colum);
        }
        colum++;
    }

    return 0;
}
void stateConvert(char nowWord,int col)
{
    char temp=' ';
    int myFlag=0;
    //int flagEnd=0;
    if(result[0]=='#')//其实 意义不大 为了 处理输入的是 下一个还是当前的字符
{
    result[0]=nowWord;
}   result[record]=nowWord;
if(expFlag==0)//为了表示注释符，是注释符后的 不进行处理
{
    if(result[0]>='0'&&result[0]<='9')
    {
       if((result[record]>='0'&&result[record]<='9')||result[record]=='.'||result[record]=='E')//判断后接数字
           {
               if(result[record-1]=='.'&&result[record]=='.')
               {
                   cout<<"ERROR   "<<"at Line "<< "[" <<col<< "]：" <<col<<"非法输入"<<endl;
                   record=0;
                   memset(result,0,20);
                   return ;
               }
               else if(result[record-1]=='E'&&result[record]=='E')
               {
                   cout<<"ERROR   "<<"at Line "<< "[" <<col<< "]：" <<col<<"非法输入"<<endl;
                   record=0;
                   memset(result,0,20);
                   return ;
               }
               else if(result[record-1]=='E'&&result[record]!='E')
               {
                   if(result[record]>='0'&&result[record]<='9')
                   {
                 cout<<result<< "      ";
                 cout<<"<"<<"CONST"<<","<<result<<">"<<endl;
               for(int i=0;i<=19;i++)
               {
                   result[i]='\0';
               }
               record=0;
                   }
                 else
                   {
                    cout<<"ERROR   "<<"at Line "<< "[" <<col<< "]：" <<col<<"非法输入"<<endl;
                   record=0;
                   memset(result,0,20);
                   return ;
                   }
               }
               else
              record++;
           }else
           {
               temp=result[record];
               result[record]=' ';
               cout<<result<< "      ";
               cout<<"<"<<"CONST"<<","<<result<<">"<<endl;
               for(int i=0;i<=19;i++)
               {
                   result[i]='\0';
               }
               result[0]=temp;
               if(temp=='\0')//记录当前处理字符
               {
                   record=0;
               }else
               record=1;
                return;
           }
    }
    if(result[0]>='A'&&result[0]<='z')
    {
         if(result[record]>='0'&&result[record]<='9')
        {
            record++;

        }
        else if(result[record]>='A'&&result[record]<='z')
        {

           if( strcmp(result,keyword[0])==0)
           {
                cout<<result<<"       ";
               cout<<"<"<<"FLOAT"<<","<<"_ "<<">"<<endl;
               for(int i=0;i<=19;i++)
               {
                   result[i]='\0';
               }
                 result[0]='#';
                 record=0;
            return;
           }
           if(strcmp(result,keyword[1])==0)
           {
               cout<<result<<"       ";
               cout<<"<"<<"BOOLEAN"<<","<<"_ "<<">"<<endl;
               for(int i=0;i<=19;i++)
               {
                   result[i]='\0';
               }
                 result[0]='#';
                 record=0;
            return;
           }
           for(int i=2;i<=10;i++)
           {
               if(strcmp(result,keyword[i])==0)
               {
                   switch (i)
                   {
                   case 2:
                    cout<<result<<"       ";
                    cout<<"<"<<"DOC"<<","<<"_ "<<">"<<endl;
                    myFlag=0;
                    break;
                     case 3:
                    cout<<result<<"       ";
                    cout<<"<"<<"INT"<<","<<"_ "<<">"<<endl;
                    myFlag=0;
                    break;
                     case 4:
                    cout<<result<<"       ";
                    cout<<"<"<<"IF"<<","<<"_ "<<">"<<endl;
                    myFlag=0;
                    break;
                     case 5:
                         cout<<result<<"       ";
                    cout<<"<"<<"ELSE"<<","<<"_ "<<">"<<endl;
                    myFlag=0;
                    break;
                     case 6:
                         cout<<result<<"       ";
                    cout<<"<"<<"DO"<<","<<"_ "<<">"<<endl;
                    myFlag=0;
                    break;
                     case 7:
                         cout<<result<<"       ";
                    cout<<"<"<<"WHILE"<<","<<"_ "<<">"<<endl;
                    myFlag=0;
                    break;
                     case 8:
                         cout<<result<<"       ";
                    cout<<"<"<<"FOE"<<","<<"_ "<<">"<<endl;
                    myFlag=0;
                    break;
                     case 9:
                         cout<<result<<"       ";
                    cout<<"<"<<"RETURN"<<","<<"_ "<<">"<<endl;
                    myFlag=0;
                    break;
                     case 10:
                    cout<<result<<"       ";
                    cout<<"<"<<"CHAR"<<","<<"_ "<<">"<<endl;
                    myFlag=0;
                    break;
                   }
                   if(myFlag==0)
                   {
                        for(int i=0;i<=19;i++)
               {
                   result[i]='\0';
               }
                 result[0]='#';
                 myFlag=1;
                 record=0;
                 return;
                   }
               }
           }
            record++;
        }
        else if(result[record]=='_')
        {
            record++;
        }
        else{
               temp=result[record];
               result[record]=' ';
               cout<<result<< "      ";
               cout<<"<"<<"IDN"<<","<<result<<">"<<endl;
               if(temp=='\0')
               {
                   for(int i=0;i<=19;i++)
            {
                result[i]='\0';
            }
                   record=0;
               }
               else
               {for(int i=0;i<=19;i++)
            {
                result[i]='\0';
            }
               result[0]=temp;
               record=1;
               }
               return;
        }
    }
    switch (result[0])//处理界符
    {
        case  '{':
            cout<<result[0]<< "      ";
            cout<<"<"<<"LP"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
            break;
            case  '}':
            cout<<result[0]<< "      ";
            cout<<"<"<<"RP"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
            break;
            case  ';':
            cout<<result[0]<< "      ";
            cout<<"<"<<"SEMT"<<","<<"_ "<<">"<<endl;
           if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
            break;
            case  '[':
            cout<<result[0]<< "      ";
            cout<<"<"<<"MLP"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
            break;
            case  ']':
            cout<<result[0]<< "      ";
            cout<<"<"<<"MRP"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
            break;
            case  '(':
            cout<<result[0]<< "      ";
            cout<<"<"<<"SLP"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
            break;
            case  ')':
            cout<<result[0]<< "      ";
            cout<<"<"<<"SRP"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
            break;
            case  '.':
            cout<<result[0]<< "      ";
            cout<<"<"<<"DOT"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
            break;
            case  '\'':
{
            record++;
            if(result[1]=='\0')
            {  cout<<result[0]<< "      ";
                cout<<"<"<<"单引号"<<","<<"_ "<<">"<<endl;
                record=0;
            }
           else if(result[1]=='\'')
           {
               cout<<"ERROR"<<"出错行："<<col<<"无效输入"<<endl;
               record=0;
               result[0]='\0';
               result[1]='\0';
           }
           else if(result[1]!='\0'&&result[1]!='\''&&result[2]!='\0')
           {
               //record=2;
               if(result[2]=='\'')
               {
               cout<<result<< "      ";
               cout<<"<"<<"字符"<<","<<"_ "<<">"<<endl;
               record=0;
               result[0]='\0';
               result[1]='\0';
               result[2]='\0';
               return;
               }
               if(result[2]!='\'')
               {
                  // cout<<result[2]<<"_____________________________"<<endl;
              // cout<<result[1]<<endl;
              // cout<<result[0]<<endl;
                   cout<<"ERROR   "<<"at Line "<< "[" <<col<< "]：" <<col<<"无效输入"<<endl;
                   //cout<<result[2]<<"___________"<<endl;
                //   cout<<result[3]<<endl;
                   result[0]='\0';
               result[1]='\0';
               result[2]='\0';
                   record=0;
                   return;
               }
              // record=1;
           }
           else{
          }
            break;
}
            default:
            break;
    }
    switch (result[0])//处理运算符
    {
        //char op[]={'+','-','*','/','!','^','%','|','='};
    case '+':
        if(record==0)
        {
            record=1;
            return;
        }
        if(result[record]=='+'||result[record]=='=')
        {
           cout<<result<<"      ";
           cout<<"<"<<"INC"<<","<<"_ "<<">"<<endl;
           result[0]='\0';
           result[1]='\0';
           record=0;
        }
        else{
            cout<<result[0]<<"      ";
           cout<<"<"<<"ADD"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
        }
        break;
    case '-':
        if(record==0)
        {
            record=1;
            return;
        }
        if(result[record]=='-'||result[record]=='=')
        {
           cout<<result<<"      ";
           cout<<"<"<<"RED"<<","<<"_ "<<">"<<endl;
           result[0]='\0';
           result[1]='\0';
           record=0;
        }
        else{
            cout<<result[0]<<"      ";
           cout<<"<"<<"RED1"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
        }
        break;
    case '*':
        {if(record==0)
        {
            record=1;
            return;
        }
            if(result[record]=='=')
        {
           cout<<result<<"      ";
           cout<<"<"<<"PLX"<<","<<"_ "<<">"<<endl;
           result[0]='\0';
           result[1]='\0';
           record=0;
        }
        else{
            cout<<result[0]<<"      ";
           cout<<"<"<<"PLX1"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
        }
        break;
    }
    case '/':
        if(record==0)
        {
            record=1;
            return;
        }
        {
            if(result[record]=='=')
        {
           cout<<result<<"      ";
           cout<<"<"<<"DIV"<<","<<"_ "<<">"<<endl;
           result[0]='\0';
           result[1]='\0';
           record=0;
        }
        else if(result[record]=='*')
        {        expFlag=1;
                 //cout<<result<<endl;
                // cout<<record<<endl;
                 record=2;
                 return;
        }
        else
        {
            cout<<result[0]<<"      ";
           cout<<"<"<<"DIV1"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
        }
        break;
    }
    case '=':
        {if(record==0)
        {
            record=1;
            return;
        }
            if(result[record]=='=')
        {
           cout<<result<<"      ";
           cout<<"<"<<"EQUAL"<<","<<"_ "<<">"<<endl;
           result[0]='\0';
           result[1]='\0';
           record=0;
        }
        else{
            cout<<result[0]<<"      ";
           cout<<"<"<<"EQUAL1"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
        }
        break;
    }
        case '%':
        {
            if(record==0)
        {
            record=1;
            return;
        }if(result[record]=='=')
        {
           cout<<result<<"      ";
           cout<<"<"<<"YU"<<","<<"_ "<<">"<<endl;
           result[0]='\0';
           result[1]='\0';
           record=0;
        }
        else{
            cout<<result[0]<<"      ";
            cout<<"<"<<"YUEQUAL"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
        }
        break;
    }
          case '!':
        {
            if(record==0)
        {
            record=1;
            return;
        }if(result[record]=='=')
        {
           cout<<result<<"      ";
           cout<<"<"<<"NOTEQUAL"<<","<<"_ "<<">"<<endl;
           result[0]='\0';
           result[1]='\0';
           record=0;
        }
        else{
                //ERROR
            cout<<result[0]<<"      ";
            cout<<"<"<<"ERROR"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
        }
        break;
    }
      case '^':
        {if(result[record]=='=')
        {
           cout<<result<<"      ";
           cout<<"<"<<"PHA"<<","<<"_ "<<">"<<endl;
           result[0]='\0';
           result[1]='\0';
           record=0;
        }
        else{
                //ERROR
            cout<<result[0]<<"      ";
            cout<<"<"<<"PHA1"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
        }
        break;
    }
    case '|':
        {
            if(record==0)
        {
            record=1;
            return;
        }if(result[record]=='|')
        {
           cout<<result<<"      ";
           cout<<"<"<<"OR"<<","<<"_ "<<">"<<endl;
           result[0]='\0';
           result[1]='\0';
           record=0;
        }
        else{
                //ERROR
            cout<<result[0]<<"      ";
            cout<<"<"<<"SINGGLOR"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
        }
        break;
    }
    case '&':
        {
            if(record==0)
        {
            record=1;
            return;
        }if(result[record]=='&')
        {
           cout<<result<<"      ";
           cout<<"<"<<"AND"<<","<<"_ "<<">"<<endl;
           result[0]='\0';
           result[1]='\0';
           record=0;
        }
        else{
                //ERROR
            cout<<result[0]<<"      ";
            cout<<"<"<<"YU"<<","<<"_ "<<">"<<endl;
            if(result[1]=='\0')
            {
                record=0;
            }
           else
           {
               result[0]=result[1];
               record=1;
           }
        }
        break;
    }
    }
}
else{
   if(result[0]=='/')
   {
       if(result[1]=='*')
       {
           record=2;
           if(result[record]=='*')
           {
               recordExcute=record;//记录最后/前的*号
               record=3;
           }
           if(result[record]=='/'&&record==(recordExcute+1))
                   {
                       cout<<result[0]<<result[1]<<result[recordExcute]<<result[record]<<"      ";
                       cout<<"<"<<"EXP"<<","<<"_ "<<">"<<endl;
                       result[0]='\0';
                       result[1]='\0';
                       result[2]='\0';
                       result[3]='\0';
                       record=0;
                       expFlag=0;
                   }//并不处理其余字符
       }
   }
}
}

