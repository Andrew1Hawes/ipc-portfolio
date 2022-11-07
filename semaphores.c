#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ops_sems.h"

int main(int argc, char argv[]){
  //Use our source file as the "key"
  int id=ops_semget("critical_example2.c",1);
  
  int pid=fork();
  if(pid){
    //P1 Henry
    int lyricCounterH = 0;
    while(1){
      ops_wait(id); //signal ready to enter critical section
      printf("In critical section P1 ... \n");
      printf("Henry:\n");
      switch (lyricCounterH)
      {
      case 0:
        printf("There's a hole in the bucket, dear Liza, dear Liza,\n");
        printf("There's a hole in the bucket, dear Liza, a hole.\n");
        break;
      case 1:
        printf("With what shall I fix it, dear Liza, dear Liza?\n");
        printf("With what shall I fix it, dear Liza, with what?\n");
        break;
      case 2:
        printf("The straw is too long, dear Liza, dear Liza,\n");
        printf("The straw is too long, dear Liza, too long.\n");
        break;
      case 3:
        printf("With what shall I cut it, dear Liza, dear Liza?\n");
        printf("With what shall I cut it, dear Liza, with what?\n");
        break;
      default:
        break;
      }
      lyricCounterH++;
      rsleep();
      printf("Ending critical section P1 ... \n");
      ops_signal(id); //signal it's finished in critical section
    }
  }else{
    //P2 Liza
    int lyricCounterL = 0; //variable name could be the same as it's in a different process
    while(1){
      ops_wait(id);
       printf("In critical section P2 ... \n");
      printf("Liza:\n");
      switch (lyricCounterL)
      {
      case 0:
        printf("Then fix it, dear Henry, dear Henry, dear Henry,\n");
        printf("Then fix it, dear Henry, dear Henry, fix it.\n");
        break;
      case 1:
        printf("With straw, dear Henry, dear Henry, dear Henry,\n");
        printf("With straw, dear Henry, dear Henry, with straw.\n");
        break;
      case 2:
        printf("Then cut it, dear Henry, dear Henry, dear Henry,\n");
        printf("Then cut it, dear Henry, dear Henry, cut it.\n");
        break;
      case 3:
        printf("With an axe, dear Henry, dear Henry, dear Henry,\n");
        printf("With an axe, dear Henry, dear Henry, an axe.\n");
        break;
      default:
        break;
      }
      lyricCounterL++;
      rsleep();
      printf("Ending critical section P2 ... \n");
      ops_signal(id);
    }
  }
}
