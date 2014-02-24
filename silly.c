/* silly.c - silly command shell */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void say(const char *msg, int smile) {

   if (smile) {   
      // Codes to make bright/black/yellow and then reset/white/black (see http://www.linuxjournal.com/article/8603)
      printf("%c[%d;%d;%dm<#_#>", 0x1B, 1, 0 + 30, 3 + 40);
   }
   // Would like to set to reset/yellow/black, but it sticks like that.
   // printf("%c[%d;%d;%dm", 0x1B, 0, 3 + 30, 0 + 40);
   // So for now, just reset to reset/white/black here instead of after output.
   printf("%c[%d;%d;%dm", 0x1B, 0, 7 + 30, 0 + 40);
   if (smile) {
      printf(" ");
   }
   printf("%s", msg);
}

int main()
{
  char line[256];
  char temp[256]; // temp string for messages about the line
  char prompt[] = "o_O";
  
  // Pointer array to up to 100 tokens
  const char MAX_TOKEN = 99;
  char * tokenAry[MAX_TOKEN];
  
  printf("Silly Shell, for CS 3376 by Robert Brooks / rab120130@utdallas.edu\n");
  say("Hi! I'm a silly shell, and I'm at your 'command'\n", 1);
  /* prompt me! */
  printf("%s ", prompt);
  /* Input... INPUT!!! */
  while(fgets(line, sizeof line, stdin) != NULL)
  {
    /* Get rid of the cr */
    if (strlen(line) == 0) return 0;
    line[strlen(line)-1] = '\0';
    
    /* Tokenize the line, using space as delimiter (note that this munges the original string) */
    int curTokPtr = 0;
    char *curTok = strtok(line, " ");

    if (curTok == NULL) {
      say("You didn't give me anything to do, so I think I'll go home now. Bye!\n", 1);
      return 0;
    }
        
     while (curTok != NULL)
     {
       //printf ("%s\n",curTok);
       if (curTokPtr > MAX_TOKEN) {
         // Well, that was a lot of typing wasted, wasn't it?
         say("Oh man, you typed so much I couldn't pay attention any more. Sorry!\n", 1);
         return 1;
       }
       tokenAry[curTokPtr] = curTok;
       
       curTokPtr++;
       curTok = strtok (NULL, " ");
     }    
  
     if (curTokPtr <= MAX_TOKEN) {
      tokenAry[curTokPtr] = curTok; // null
     }
     
    say("Here's what I saw when you hit Enter:\n", 1);
     int i;
     for (i = 0; i < MAX_TOKEN; i++) {
      if (tokenAry[i] == NULL) break;
      printf("%s\n", tokenAry[i]);
     }
       
     if (strcasecmp(tokenAry[0], "exit") == 0) {
      say("You said 'exit'\n", 1);
      say("Let's blow this pop stand!\n", 1);
      return 0;
     }
  
  // We have a command. How far does it go?
  int nextCommand = 0; // 0 = end  
  sprintf(temp, "Here's the command: %s\n", tokenAry[0]);
  say(temp, 1);
  say("Parameters:", 1);
  int idxDelim;
  for (idxDelim = 1; idxDelim < MAX_TOKEN; idxDelim++) {
   if (tokenAry[idxDelim] == NULL) { nextCommand = 0; break; }
   if (strcmp(tokenAry[idxDelim], "<") == 0) { nextCommand = 1; break; }
   if (strcmp(tokenAry[idxDelim], ">") == 0) { nextCommand = 2; break; }
   if (strcmp(tokenAry[idxDelim], ">>") == 0) { nextCommand = 3; break; }
   if (strcmp(tokenAry[idxDelim], "|") == 0) { nextCommand = 4; break; }
   if (strcmp(tokenAry[idxDelim], "&") == 0) { nextCommand = 5; break; }
   printf(" %s", tokenAry[idxDelim]);
  }
  printf("\n");
  
  // Send off a child and see what it does
  int childPid = fork();
  
  if (childPid != 0) {
   // Parent here. Say what we think the child will do
     
     switch (nextCommand)
      {
     case 0: // end
        say("I would execute the command and wait for it to complete.", 1);
        break;
     case 1: // <
        say("I would get input from a file for this command.", 1);
        break;
     case 2: // >
        say("I would send output from this command to a file.", 1);
        break;
     case 3: // >>
        say("I would send output from this command to a file (append).", 1);
        break;
     case 4: // |
        say("I would pipe output from this command to the next one.", 1);
        break;
     case 5: // &
        say("I would execute the command in the background.", 1);
        break;
      //  default:
      }  
      printf("\n");
      
      if (nextCommand != 5) {
         // Wait for the child to complete
         say("Waiting for the command...\n", 1);
         // waitpid(-1, &status, 0); // wait for all children, but we want to wait for specific child
         waitpid(childPid, NULL, 0); // null because we're not checking status (yet)
         say("All done!\n", 1);
      } // if we need to wait
      else {
         say("I'm not waiting up for you!\n", 1);
      }
   }
   else {
      // Child here. Do the command.
      // exec* will be a "dead end". Execution will not resume after exec* unless error occurs.
      say("Performing the command...\n", 1);

      // "Part 1" - we don't care what made the command line end, just zap it
      // "The array of pointers must be terminated by a NULL pointer."
      tokenAry[idxDelim] = NULL;
      
      // int execvp(const char *file, char *const argv[]);
      execvp(tokenAry[0], tokenAry);
      say("Something went terribly wrong with the command. Sorry!\n", 1);
      return 1;
   } // end if (else) parent  

    /* How exactly do we want to execute the command the user entered? */
/*    system(line);*/
    printf("%s ", prompt);
  }
  return 0;
}
