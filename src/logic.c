/**
 * @file logic.c
 * @author Arash Habibi
 * @author Julien Montavont
 * @version 2.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Several basic logical functions such as XOR
 */

#include "logic.h"
#include <stdio.h>
#include <stdlib.h>


unsigned char type_ = 0;

char getNthBit(int number, int order)
{
  return((number & (1<<(order-1)))>>(order-1));
}

void printBits(CodeWord_t sh, char *comment)
{
  printf("%s : %u : %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",
	 comment,
	 sh,
	 getNthBit(sh, 16),
	 getNthBit(sh, 15),
	 getNthBit(sh, 14),
	 getNthBit(sh, 13),
	 getNthBit(sh, 12),
	 getNthBit(sh, 11),
	 getNthBit(sh, 10),
	 getNthBit(sh, 9),
	 getNthBit(sh, 8),
	 getNthBit(sh, 7),
	 getNthBit(sh, 6),
	 getNthBit(sh, 5),
	 getNthBit(sh, 4),
	 getNthBit(sh, 3),
	 getNthBit(sh, 2),
	 getNthBit(sh, 1));

  return;
}

void setNthBitCW(CodeWord_t *number, int order, int value)
{
  if(value)
    {
      *number = *number | (1<<(order-1));
    }
  else
    {
      *number = *number & (~(1<<(order-1)));
    }

  return;
}

void setNthBitW(char *number, int order, int value)
{
  if(value)
    {
      *number = *number | (1<<(order-1));
    }
  else
    {
      *number = *number & (~(1<<(order-1)));
    }

  return;
}

CodeWord_t xor(CodeWord_t a, CodeWord_t b)
{
  return(a^b);
}

void changeNthBitCW(CodeWord_t *cw, int order)
{
  *cw = xor(*cw, 1<<(order-1));
  return;
}

void changeNthBitW(char *word, int order)
{
  *word = xor(*word, 1<<(order-1));
  return;
}

void truncNbits(CodeWord_t *cw, int N)
{
  int i = 0;

  for(i=8*sizeof(CodeWord_t); i>N; i--)
    {
      setNthBitCW(cw, i, 0);
    }
}

int getDegree(CodeWord_t cw)
{
  int i = 8*sizeof(CodeWord_t);

  if(cw == 0)
    {
      return(0);
    }
  else
    {
      while(getNthBit(cw, i) == 0)
	{
	  i--;
	}
    }

  return(i-1);
}


void set_type(){
    const char* s = getenv("TP_RES_TYPE");
    if(s == NULL){
        type_ = 0;
        printf("Even Parity checking is set to used \n");
    }
    else if(s[0] == '0'){
        type_ = 0;
        printf("Even Parity checking is set to used \n");
    }
    else if(s[0] == '1'){
        type_ = 1;
        printf("Poly checking is set to used \n");

    }
    else if(s[0] == '2'){
        type_ = 2;
        printf("Hamming checking is set to used \n");
    }
    else {
        type_ = 0;
        printf("Even Parity checking is set to used \n");
    }

}