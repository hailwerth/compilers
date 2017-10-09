#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

/*A setup function to parse the shell command and its arguments*/
void setup(char inputBuffer[], char *args[])
{
  int length, /* # of characters in the command line */
  i,          /* loop index for accessing inputBuffer array */
  start,      /* index where beginning of next command parameter is */
  ct = 0;     /* index where to place the next parameter into args[] */

  length = strlen(inputBuffer);
  start = -1;
  if (length == 0) exit(0); 
  if (length < 0){ 
    perror("error reading the command"); 
    exit(-1); 
  } 
  /* examine every character in the inputBuffer */ 
  for (i=0;i<length;i++) { 
    switch (inputBuffer[i]){ 
      case ' ': 
      case '\t' : /* argument separators */ 
        if(start != -1){ 
          args[ct] = &inputBuffer[start];    /* set up pointer */ 
          ct++; 
        } 
        inputBuffer[i] = '\0'; /* add a null char; make a C string */ 
        start = -1; 
        break; 
      case '\n':         /* should be the final char examined */ 
        if (start != -1){ 
          args[ct] = &inputBuffer[start];     
          ct++; 
        } 
        inputBuffer[i] = '\0'; 
        args[ct] = NULL; /* no more arguments to this command */ 
        break; 
      default :    /* some other character */ 
        if (start == -1) start = i; 
    } 
  }    
  args[ct] = NULL; /* just in case the input line was > 80 */ 
} 


/* sample signal handler */
void handle_SIGINT()
{
  char output[100];
  strcpy(output,"\n\nSample <Ctrl><C> signal handler\n\n");
  write(STDOUT_FILENO,output,strlen(output));
  exit(1);
}


/* ------------------------------------------------------ */ 
/* The main program starts here */ 
/* ------------------------------------------------------ */ 
int main(int argc, char *argv[]) { 
  pid_t  pid1;
  char read_in[80]; /*store the complete shell command*/ 
  char *cmd_line[50]; /*parsed shell command for execvp*/
  
  /*setup a sample signal handler*/
  struct sigaction handler;
  handler.sa_handler = handle_SIGINT;
  sigaction(SIGINT, &handler, NULL);
  
  /*get a command*/
  strcpy(read_in,"ps -f");

  /*parse the command*/
  setup(read_in, cmd_line);

  /*fork a child process*/ 
  if ((pid1 = fork()) < 0) {
    printf("*** ERROR: forking child process failed\n"); 
    exit(1); 
  } 

  /*execute command in child*/ 
  if (pid1 == 0) {      
    if (execvp(read_in, cmd_line) < 0) {
      printf("*** ERROR: exec failed\n"); 
      exit(1);
    } 
  } 

  /*make the parent wait until the child finishes*/	
  if (pid1 > 0) { wait(NULL); } 

  while(1) {  //sit in infinite loop until receiving signal
    ;
  }
}

