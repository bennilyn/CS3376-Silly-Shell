/* silly.c - silly command shell */
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
  char line[256];
  char prompt[] = "o_O";
  char robot[] = "<#_#>";
  // Pointer array to up to 100 tokens
  const char MAX_TOKEN = 99;
  char * tokenAry[MAX_TOKEN];
  
  printf("Silly Shell, for CS 3376 by Robert Brooks / rab120130@utdallas.edu\n");
  printf("%s Hi! I'm a silly shell, and I'm at your 'command'\n", robot);
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
      printf("%s You didn't give me anything to do, so I think I'll go home now. Bye!\n", robot);
      return 0;
    }
        
     while (curTok != NULL)
     {
       //printf ("%s\n",curTok);
       if (curTokPtr > MAX_TOKEN) {
         // Well, that was a lot of typing wasted, wasn't it?
         printf("%s Oh man, you typed so much I couldn't pay attention any more. Sorry!\n", robot);
         return 1;
       }
       tokenAry[curTokPtr] = curTok;
       
       curTokPtr++;
       curTok = strtok (NULL, " ");
     }    
  
     if (curTokPtr <= MAX_TOKEN) {
      tokenAry[curTokPtr] = curTok; // null
     }
     
    printf("%s Here's what I saw when you hit Enter:\n", robot);
     int i;
     for (i = 0; i < MAX_TOKEN; i++) {
      if (tokenAry[i] == NULL) break;
      printf("%s\n", tokenAry[i]);
     }
       
     if (strcasecmp(tokenAry[0], "exit") == 0) {
      printf("%s You said '%s'\n", robot, tokenAry[0]);
      printf("%s Let's blow this pop stand!\n", robot);
      return 0;
     }
  
  // We have a command. How far does it go?
  int nextCommand = 0; // 0 = end  
  printf("%s Here's the command: %s\n", robot, tokenAry[0]);
  printf("%s Parameters:", robot);
  for (i = 1; i < MAX_TOKEN; i++) {
   if (tokenAry[i] == NULL) { nextCommand = 0; break; }
   if (strcmp(tokenAry[i], "<") == 0) { nextCommand = 1; break; }
   if (strcmp(tokenAry[i], ">") == 0) { nextCommand = 2; break; }
   if (strcmp(tokenAry[i], ">>") == 0) { nextCommand = 3; break; }
   if (strcmp(tokenAry[i], "|") == 0) { nextCommand = 4; break; }
   if (strcmp(tokenAry[i], "&") == 0) { nextCommand = 5; break; }
   printf(" %s", tokenAry[i]);
  }
  printf("\n");
  
  switch (nextCommand)
{
  case 0: // end
     printf("%s I would execute the command and that's it.", robot);
     break;
  case 1: // <
     printf("%s I would get input from a file for this command.", robot);
     break;
  case 2: // >
     printf("%s I would send output from this command to a file.", robot);
     break;
  case 3: // >>
     printf("%s I would send output from this command to a file (append).", robot);
     break;
  case 4: // |
     printf("%s I would pipe output from this command to the next one.", robot);
     break;
  case 5: // &
     printf("%s I would execute the command in the background.", robot);
     break;
//  default:
}  
   printf("\n");

    /* How exactly do we want to execute the command the user entered? */
/*    system(line);*/
    printf("%s ", prompt);
  }
  return 0;
}
