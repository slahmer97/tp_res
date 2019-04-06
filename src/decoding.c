/**
 * @file decoding.c
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
 * Functions to decipher the code words
 */

#include <stdio.h>
#include "codingdecoding.h"

void copyDataBitsDecoding(CodeWord_t *cw, char *message, int data_size)
{
  int i = 0;

  for(i=0; i<data_size; i++)
    {
      setNthBitW(&(message[i]), 1, getNthBit(cw[i], 1));
      setNthBitW(&(message[i]), 2, getNthBit(cw[i], 2));
      setNthBitW(&(message[i]), 3, getNthBit(cw[i], 3));
      setNthBitW(&(message[i]), 4, getNthBit(cw[i], 4));
      setNthBitW(&(message[i]), 5, getNthBit(cw[i], 5));
      setNthBitW(&(message[i]), 6, getNthBit(cw[i], 6));
      setNthBitW(&(message[i]), 7, getNthBit(cw[i], 7));
      setNthBitW(&(message[i]), 8, getNthBit(cw[i], 8));
    }
}



void errorCorrection(CodeWord_t *message, int data_size)
{
    int i;
  for(i=0;i<data_size;i++){
        short HC_t = 0;
        CodeWord_t tmp = message[i];
        int hc_t_1_bit = getNthBit(tmp,1)^getNthBit(tmp,3)^
                         getNthBit(tmp,5)^getNthBit(tmp,7)^
                         getNthBit(tmp,9)^getNthBit(tmp,11);
        int hc_t_2_bit = getNthBit(tmp,2)^getNthBit(tmp,3)^
                         getNthBit(tmp,6)^getNthBit(tmp,7)^
                         getNthBit(tmp,10)^getNthBit(tmp,11);
        int hc_t_3_bit = getNthBit(tmp,4)^getNthBit(tmp,5)^
                         getNthBit(tmp,6)^getNthBit(tmp,7)^
                         getNthBit(tmp,12);
        int hc_t_4_bit = getNthBit(tmp,8)^getNthBit(tmp,9)^
                         getNthBit(tmp,10)^getNthBit(tmp,11)^
                         getNthBit(tmp,12);

        setNthBitCW(&HC_t,1,hc_t_1_bit);
        setNthBitCW(&HC_t,2,hc_t_2_bit);
        setNthBitCW(&HC_t,3,hc_t_3_bit);
        setNthBitCW(&HC_t,4,hc_t_4_bit);

        if(HC_t != 0){
            printf("\n{Error in bit %d}\n",HC_t);
            changeNthBitCW(&tmp,HC_t);
        }


      setNthBitW((char *) &(message[i]), 1, getNthBit(tmp, 3));
      setNthBitW((char *) &(message[i]), 2, getNthBit(tmp, 5));
      setNthBitW((char *) &(message[i]), 3, getNthBit(tmp, 6));
      setNthBitW((char *) &(message[i]), 4, getNthBit(tmp, 7));
      setNthBitW((char *) &(message[i]), 5, getNthBit(tmp, 9));
      setNthBitW((char *) &(message[i]), 6, getNthBit(tmp, 10));
      setNthBitW((char *) &(message[i]), 7, getNthBit(tmp, 11));
      setNthBitW((char *) &(message[i]), 8, getNthBit(tmp, 12));

  }

  return;
}




int thereIsError(CodeWord_t *cw, int data_size)
{
    int j,i;
    //even par
   if(type_ == 0){
       for (i = 0; i <data_size ; ++i) {
           int par = 0;

           for( j= 1 ;j<= 8 ;j++)
               par ^=getNthBit(cw[i],j);

           if(par !=  getNthBit(cw[i],j))
               return 1;
       }

   }
   else{//poly
       for (int k = 0; k <data_size; ++k) {
           CodeWord_t tmp = cw[k];
           computeCtrlBits(&tmp,1);
           if((tmp >>8) != (cw[k]>>8))
               return 1;
       }

   }

  return 0;
}


void decoding(char *cw, int cw_size, char *message, int *data_size)
{
  *data_size = cw_size / sizeof(CodeWord_t);


  if(type_ == 2)
    errorCorrection((CodeWord_t*)cw, *data_size);
  else
      if(thereIsError((CodeWord_t*)cw, *data_size))

          printf("PARITY ERROR: \"%s\"\n", message);


    copyDataBitsDecoding((CodeWord_t*)cw, message, *data_size);


    return;
}
