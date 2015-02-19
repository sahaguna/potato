// main.c, 159
// simulated kernel
//
// Team Name: ??????? (Members: ?????? and ??????)

#include "spede.h"      // spede stuff
#include "main.h"       // main stuff
#include "isr.h"        // ISR's
#include "tool.h"       // handy functions
#include "proc.h"       // processes such as Init()
#include "type.h"       // processes such as Init()

// kernel data structure:
int CRP;                // current running PID, -1 means no process
q_t run_q, none_q;      // processes ready to run and not used
pcb_t pcb[MAX_PROC];    // process table
char stack[MAX_PROC][STACK_SIZE]; // run-time stacks for processes

int main() {
   InitData(); 		//call Init Data to initialize kernel data
   
   CreateISR(0);	//call CreateISR(0) to create Idle process (PID 0)

   while (1) {      // alter 2 things below
      Dispatch();    // to dispatch/run CRP
      Kernel();      // for kernel control
   }

   //return 0;
}

void InitData() {
   int i;
   /*initialize 2 queues (use MyBzero() you code in tool.c/.h)
   queue PID's 1~19 (skip 0) into none_q (un-used PID's)
   set state to NONE in all un-used pcb[1~19]
   set CRP to 0 (Idle proc ID)*/
   MyBZero(&run_q,0);
   MyBZero(&none_q,0);
   
   i = 1;
   for(i  ; i<Q_SIZE;i++){
      pcb[i].state = NONE;
      EnQ(i,&none_q);
      
   }
   CRP = 0;
}

void SelectCRP() {       // select which PID to be new CRP
   
    printf("Selcet CRP  Beggineing CRP %d \n",CRP);
   /*simply return if CRP is greater than 0 (already good one selected)
   (continue only when CRP is Idle or none (0 or -1)
   */ 
   if(CRP > 0){
      return;
   }    
   //if it's' 0 (Idle), change its state in PCB to RUN
   if(CRP == 0){
      pcb[0].state = RUN;
   }
    printf("after checking if its zero or greater CRP %d \n",CRP);
   //if no processes to run (check size in run queue against zero)
   printf("run_q size = %d \n",run_q.size);
   //   set CRP to 0 (at least we can run Idle proc)
   if(run_q.size == 0 ){
      printf("run_q size = %d \n ",run_q.size);
      CRP = 0;
   }else{  
       printf("after checking run q size CRP %d \n",CRP);
      //set CRP to first in run queue (dequeue it)
      CRP = DeQ(&run_q); 
      printf("after DeQ in selectcrp %d \n",CRP);
      //change mode in PCB of CRP to UMODE
      pcb[CRP].mode = UMODE;
      //change state in PCB of CRP to RUNNING
      pcb[CRP].state = RUNNING;
   }
}

void Kernel() {
   int pid,i;
   char key;

   //change state in PCB of CRP to kernel mode
   pcb[CRP].state = KMODE;
   //call TimerISR() to service timer interrupt as it just occurred
   TimerISR();
   if (cons_kbhit()) {
      key = cons_getchar(); // key = cons_getchar();
      switch(key) {
         case 'n':                                                   //if 'n'
            printf("n pressed\n");
            if (none_q.size == 0){                                   //no processes left in none queue
               cons_printf("No more process!\n");                    //"No more process!\n" (msg on target PC)
            }else{
            pid = DeQ(&none_q);                                      //get 1st PID un-used (dequeue none queue)
             printf("after pressing n pid is %d \n",pid);
            CreateISR(pid);                                          //call CreateISR() with it to create new process
            i = 1;
            for(i  ; i<Q_SIZE;i++){
               printf("in runque %d",run_q.q[i]);
               
            }
               
            }
            break;
         case 't':                                                   //if 't'
            printf("t pressed\n");
            TerminateISR();                                          //call TerminateISR() to terminate CRP
            break;   
         case 'b':                                                   //if 'b'
            printf("b pressed \n");
            breakpoint();                                            // this goes back to GDB prompt
            break;
         case 'q':                                                   //if 'q'
            printf("q pressed\n");
            exit(0);                                                 //just do exit(0);
      }                                                              // end switch
   }                                                                 // end if some key pressed
   printf("after case statement \n");
   SelectCRP();                                                       //call SelectCRP() to settle/determine for next CRP
   
}

