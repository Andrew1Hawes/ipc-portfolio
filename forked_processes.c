#include <unistd.h>
#include <stdio.h>
#include "sys/types.h"
#include <sys/wait.h>

int main() {
  
  pid_t pid_value;
  int status = 0;
  int menuChoice;
  
  for (int loop=0; loop<=5; loop++){
    
    //print menu to user
    printf("Menu\n-----\n");
    printf("1. Show the processes (ps)\n");
    printf("2. Show todays date (date)\n");
    printf("3. List the contents of the current directory (ls)\n");
    printf("4. Print user names of users currently logged on to current host \n");
    //get integer input from user and store in menuChoice
    //https://www.programiz.com/c-programming/c-input-output
    scanf("%d", &menuChoice);
    //split program into 2 processes (parent and child)
    pid_value = fork();
    if(pid_value!=0) {
      //parent process
      wait(&status); //waits for the child process to finish before continuing
      printf( "I am the parent, my Process ID is %d, my Parents PID is %d \n",getpid(),getppid());
    }else {
      //child process
      printf( "I am the child, my Process ID is %d , my Parents PID is %d \n",getpid(),getppid());
      sleep(2); //delay to ensure the parent process is ready before continuing
      
      switch (menuChoice)
      {
      case 1:
        printf( "Using execl to display running processes \n");
        execl( "/bin/ps","ps",(char*)0);
      case 2:
        printf("Using execl to display todays date\n");
        execl("/bin/date","",(char*)0);
      case 3:
        printf("Using execl to list files and directories in current directory\n");
        execl("/bin/ls","",(char*)0);
      case 4:
        printf("Using execl to display users currently logged in\n");
        execl("/bin/users","",(char*)0);
      default:
        printf("Menu choice invalid\n");
        break;
      }
      
      printf( "Due to the execl, you should not be able to read this\n" );
    }
  }
  return 0;
}
