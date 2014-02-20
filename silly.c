/* silly.c - silly command shell */
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
  char line[256];
  char prompt[] = "o_O ";
  
  printf("Silly Shell, for CS 3376 by Robert Brooks / rab120130@utdallas.edu\n");
  /* prompt me! */
  printf("%s", prompt);
  /* Input... INPUT!!! */
  while(fgets(line, sizeof line, stdin) != NULL)
  {
    /* Get rid of the cr */
    line[strlen(line)-1] = '\0';
    printf("Here's what I saw when you hit Enter:\n%s\n", line);
    
    /* Tokenize the line, using space as delimiter (note that this munges the original string) */
    char *curTok = strtok(line, " ");
  while (curTok != NULL)
  {
    printf ("%s\n",curTok);
    curTok = strtok (NULL, " ");
  }    
    

    /* How exactly do we want to execute the command the user entered? */
/*    system(line);*/
    printf("%s", prompt);
  }
  return 0;
}
