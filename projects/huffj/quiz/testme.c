/************************************************************
*
* testme.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Random Testing Quiz
* -----------------
*
* Random Testing Quiz -- learning how to write a random test generator
*
*************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function to produce random values
    // Must include a space, brackets, parentheses, braces, a space, and lowercase letters.
    // ASCII - 32, 40, 41, 91, 93, 123, 125, 97 - 122 
    char randomCharacterArray[] = " ()[]{}abcdefghijklmnopqrstuvwxyz";
    return randomCharacterArray[rand() % sizeof(randomCharacterArray) - 1];
}

char *inputString()
{
    // TODO: rewrite this function to produce random values
    // Must include lowercase letter and null
    // ASCII - 97 - 122, 0
    int i;
    char randomStrArray[] ="abcdefghijklmnopqrstuvwxyz";
    char* returnStr = malloc(6 * sizeof(char));
    memset(returnStr, '\0', 6);
    for (i = 0; i < 5; i++){
    
      returnStr[i] = randomStrArray[rand() % sizeof(randomStrArray) - 1];
    }
    
    return returnStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
