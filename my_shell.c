#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int status=1;

char *a_read_line()
{
char *line=NULL;
ssize_t buff_size=0;
getline(&line,&buff_size,stdin);
return line;
}

#define TOK_BUFSIZE 40
#define TOK_DELIM "\t\r\n\a " " "
char **get_tokens(char *line)
{
int buff_size= TOK_BUFSIZE;
int position =0;
char **tokens=malloc(buff_size *sizeof(char*));
char *token;

if(!tokens)
{
fprintf(stderr,"my_shell : allocation error\n");
exit(EXIT_FAILURE);
}
token = strtok(line,TOK_DELIM);
while(token!= NULL)
{
tokens[position]=token;
position++;
if(position>=buff_size)
{
buff_size+=TOK_BUFSIZE;
tokens = realloc(tokens,buff_size * sizeof(char*));
if(!tokens)
{
fprintf(stderr,"my_shell: allocation error");
exit(EXIT_FAILURE);
}
}
token=strtok(NULL,TOK_DELIM);
}
tokens[position]=NULL;
return tokens;
}
char *shell_command[] ={"ls",
"-a",
"cd",
"cat",
"mkdir",
"-m",
"cp",
"-u",
"sort",
"-r",
"grep",
"-n",
"exit"};          /////////DECLARATION OF ALL SHELL COMMAND TO BE EXECUTED BY STORING THEM IN TO AN VECTOR FOR EASY ACCESS THROUGHOUT THE PROGRAM

void ls_function()
{


struct dirent **namelist;
int n;
n= scandir(".",&namelist,NULL,alphasort);

if(n<0)
{
perror("scandir");
}
else
{
while(n--)
{
if((strcmp(namelist[n]->d_name,".")!=0)&&(strcmp(namelist[n]->d_name,"..")!=0))
printf("%s\n",namelist[n]->d_name);
free(namelist[n]);
}
//printf("\n");
free(namelist);
}
}







void shell_execute(char **args)
{
    if(args[0]==NULL)
    { 
       //printf("..");

    }
else
{



if((strcmp(args[0],shell_command[0])==0))    //LS COMMAND
{
    if(args[1]==NULL)
    {
        ls_function();
    }
char add[100];

if(args[1]!=NULL && strcmp(args[1],shell_command[1])==0)
    {
        printf(".\n..\n");
        ls_function();
    }
        if(args[1]!=NULL && strcmp(args[1],shell_command[1])!=0)
        printf("%s $myShell >Enter Valid Command\n",getcwd(add,100));

}

if(strcmp(args[0],shell_command[2])==0)     //cd
{
char add[100];
chdir(args[1]);
if (args[1]==NULL)
{
    printf("%s $myShell >Enter Valid Command\n",getcwd(add,100));
}


//char s[100];
//printf("\n%s $myShell >",getcwd(s,100));
//chdir("..");
//printf("\n\n%s $myShell >",getcwd(s,100));

}
if(strcmp(args[0],shell_command[3])==0)     //cat
{
char add[100];
char buffer1[1000];
int count,f;
/*f=open(args[1],O_RDONLY);
if(f==-1)
{
    printf("%s $myShell >File Cannot Open\n",getcwd(add,100));

}
while((count=read(f,buffer1,sizeof*(buffer1)))>0)
{
//printf("%s",buffer1);
}*/

if(strcmp(args[1],shell_command[11])==0)
{
int i=1;
FILE *file;
file=fopen(args[2],"r");
if(file==NULL)
{
   printf("%s $myShell >File Cannot Open\n",getcwd(add,100));
 
}
else
{
while (fscanf(file,"%[^\n]\n",buffer1)!=EOF)
{
    printf("%d  %s\n",i,buffer1);
    i++;
}
fclose(file);
i=1;
}

}

else
{
FILE *file;
file=fopen(args[1],"r");
if(file==NULL)
{
   printf("%s $myShell >File Cannot Open\n",getcwd(add,100));
 
}
else
{
while (fscanf(file,"%[^\n]\n",buffer1)!=EOF)
{
    printf("%s\n",buffer1);
}
fclose(file);
}
}
}

if(strcmp(args[0],shell_command[4])==0)     //mkdir
{
    char add[100];
    if(args[1]==NULL)
    {
        printf("%s $myShell >Enter Valid Command\n",getcwd(add,100));
    }
    else
    {
        mkdir(args[1],0777);
    }

    

}

if(strcmp(args[0],shell_command[6])==0)     //cp
{
int f1,f2,r;
char buffer[1000],c;
f1=open(args[1],0,00777);
if(f1==-1)
{
printf("Error: No Source File !!\n");
}
f2=creat(args[2],00777);
while((r=read(f1,buffer,1))>0)
write(f2,buffer,1);
}



if(strcmp(args[0],shell_command[12])==0) //exit
{
status=0;
}

if(strcmp(args[0],shell_command[10])==0)  //grep
{
char add[100];
//printf("agya");
if(args[1]==NULL||args[2]==NULL)
{
printf("%s $myShell >Enter Valid Command\n",getcwd(add,100));
}
else{
if(strcmp(args[1],shell_command[11])==0)    //grep -n
{
char temp[500];
int num=0;
FILE *f_op;
f_op=fopen(args[3],"r");
while(!feof(f_op))
{
num++;
fgets(temp,1000,f_op);
if(strstr(temp,args[2]))
printf("%s $myShell >%d : %s",getcwd(add,100),num,temp);
}
fclose(f_op);
}
else{
if(args[3]==NULL)
{
char temp[500];
FILE *f_op;
f_op=fopen(args[2],"r");
while(!feof(f_op))
{
fgets(temp,1000,f_op);
if(strstr(temp,args[1]))
printf("%s $myShell >%s",getcwd(add,100),temp);
}
fclose(f_op);
}
else
{
printf("%s $myShell >Enter Valid Command\n",getcwd(add,100));
}

}
}
}   ///grep finish

if(strcmp(args[0],shell_command[8])==0)  /////SORT
{
    if (args[2]!=NULL)
    {
    
    char temp_str[200];
    char **data=NULL;
    int i,j,n=0;
    FILE *f1;
    FILE *f2;
    f1=fopen(args[1],"r");
    f2=fopen(args[2],"a");

    if (f1==NULL)
    {
        printf("File Not Found");
    }
    



    while (fgets(temp_str,200,f1)!=NULL)
    {
        if (strchr(temp_str,'\n'))
        {
            temp_str[strlen(temp_str)-1]='\0';
        }
        data=(char**)realloc(data,sizeof(char**)*(n+1));
        data[n]=(char*)calloc(200,sizeof(char));
        strcpy(data[n],temp_str);
        n++;
        
    }

    for ( i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (strcmp(data[j],data[j+1])>0)
            {
                strcpy(temp_str,data[j]);
                strcpy(data[j],data[j+1]);
                strcpy(data[j+1],temp_str);
            }
            
        }
        
    }

    for ( i = 0; i < n; i++)
    {
        fprintf(f2,"%s\n",data[i]);
    }
    for ( i = 0; i < n; i++)
    {
        free(data[i]);
    }
    free(data);
    fclose(f1);
    fclose(f2);
    
    
    }

    else
    {
           char temp_str[200];
    char **data=NULL;
    int i,j,n=0;
    FILE *f1;
   // FILE *f2;
    f1=fopen(args[1],"r");
    //f2=fopen(args[2],"a");

    if (f1==NULL)
    {
        printf("HOGYA CHUTIYAPA");
    }
    



    while (fgets(temp_str,200,f1)!=NULL)
    {
        if (strchr(temp_str,'\n'))
        {
            temp_str[strlen(temp_str)-1]='\0';
        }
        data=(char**)realloc(data,sizeof(char**)*(n+1));
        data[n]=(char*)calloc(200,sizeof(char));
        strcpy(data[n],temp_str);
        n++;
        
    }

    for ( i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (strcmp(data[j],data[j+1])>0)
            {
                strcpy(temp_str,data[j]);
                strcpy(data[j],data[j+1]);
                strcpy(data[j+1],temp_str);
            }
            
        }
        
    }

    for ( i = 0; i < n; i++)
    {
        printf("%s\n",data[i]);
    }
    for ( i = 0; i < n; i++)
    {
        free(data[i]);
    }
    free(data);
    fclose(f1);
   // fclose(f2);
    
    
    }
    
    
    

    
}
    

}

}





void shell_loop()
{
char *line;
char **args;


do
{
char add[100];
printf("%s $myShell >",getcwd(add,100));    ///to print the path of the directory of the shell
line = a_read_line();         //function to read the input line 
args = get_tokens(line);      //function to divide line into tokens called ARGUMENTS
shell_execute(args);          //function to execute shell commands
free(line);
free(args);

}while(status);
}



void new_term()
{
//int a=system("gnome-terminal");
shell_loop();

}



int main(int argc, char **argv)
{
new_term();

return EXIT_SUCCESS;
}



