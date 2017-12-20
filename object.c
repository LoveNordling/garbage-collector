#include <stdio.h>
#include <malloc.h>
#include <math.h>





int char_symbol_to_value(char c)
{
  if( c == '*' || c == 'l' || c == 'd')
    {
      return 8;
    }
  else if( c == 'i' || c == 'f')
    {
      return 4;
    }
  else if( c == 'c')
    {
      return 1;
    }
  else
    {
      return 0;
    }
}


int format_string_parser(char layout[])
{
  char current;
  int sum = 0;
  for(int i = 0; layout[i] != '\0'; i++)
    {
      current = layout[i];
      sum = sum + char_symbol_to_value(current);
      
    }
  return sum;
  
}


int main()
{
  char layout[] = "**ii";
  printf("Amount of bytes that need allocating %d", format_string_parser(layout));
  //printf("Storage size for : %d \n", sizeof(double));

  return 0;
}
