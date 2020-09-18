#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h> 
int main ()
{
    system("gcc my_shell.c -lreadline -o prob");
    system("chmod +x ./prob");
    //system("./prob");    
    system("gnome-terminal --title my_shell -- ./prob  ");
    return 0 ;
}