/**
 * @file coding.c
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
 * Generate code words from the initial data flow
 */

#include <zconf.h>
#include "codingdecoding.h"
#include "stdio.h"
void copyDataBitsCoding(char *message, CodeWord_t *cw, int size)
{
  int i = 0;

  for(i=0; i<size; i++)
    {
      cw[i] = 0;
      setNthBitCW(&(cw[i]), 1, getNthBit(message[i], 1));
      setNthBitCW(&(cw[i]), 2, getNthBit(message[i], 2));
      setNthBitCW(&(cw[i]), 3, getNthBit(message[i], 3));
      setNthBitCW(&(cw[i]), 4, getNthBit(message[i], 4));
      setNthBitCW(&(cw[i]), 5, getNthBit(message[i], 5));
      setNthBitCW(&(cw[i]), 6, getNthBit(message[i], 6));
      setNthBitCW(&(cw[i]), 7, getNthBit(message[i], 7));
      setNthBitCW(&(cw[i]), 8, getNthBit(message[i], 8));
    }

  return;
}

static void compute_even_parity(CodeWord_t *message, int size){
    int i,j;
    for(i=0 ;i<size; i++){
        printBits(message[i],"--");
        int par = 0;
        for( j= 1 ;j<= 8 ;j++)
            par ^=getNthBit(message[i],j);

        setNthBitCW(&message[i],j,par);

    }

}
static void compute_poly(CodeWord_t *message, int size){
    int i;
    unsigned short poly = 0b100011101;
    poly <<= 7;
    for(i=0 ;i<size; i++){
        printBits(message[i],"DD");
        CodeWord_t tmp = message[i] << 8;
        int deg;
        while (getDegree(tmp) > 7){
            deg = getDegree(tmp);
          //  printf("\n=============deg(%d)=================\n",deg);
            tmp <<=16-deg-1;
          //  printBits(tmp,"----DATA");
          //  printBits(poly,"====poly");
            for (int j = 16; j >=8 ; --j) {
                int a = getNthBit(poly,j);
                int b = getNthBit(tmp,j);
            //    printf("%d^%d = %d\n",a,b,a^b);
                setNthBitCW(&tmp,j,a^b);
            }
            tmp >>=16-deg-1;

        }

        //printBits(tmp,"TMP");
        setNthBitCW(&(message[i]), 9, getNthBit(tmp, 1));
        setNthBitCW(&(message[i]), 10, getNthBit(tmp, 2));
        setNthBitCW(&(message[i]), 11, getNthBit(tmp, 3));
        setNthBitCW(&(message[i]), 12, getNthBit(tmp, 4));
        setNthBitCW(&(message[i]), 13, getNthBit(tmp, 5));
        setNthBitCW(&(message[i]), 14, getNthBit(tmp, 6));
        setNthBitCW(&(message[i]), 15, getNthBit(tmp, 7));
        setNthBitCW(&(message[i]), 16, getNthBit(tmp, 8));
       // printBits(message[i],"C");




    }







}
static void compute_hamming(CodeWord_t *message, int size){
    int i;
    for(i=0 ;i<size; i++){
        CodeWord_t tmp = message[i];

       // 0000000000110001
       // 00000011D 0 000D 0 1D 11


        setNthBitCW(&message[i],3,getNthBit(tmp,1));
        setNthBitCW(&message[i],5,getNthBit(tmp,2));
        setNthBitCW(&message[i],6,getNthBit(tmp,3));
        setNthBitCW(&message[i],7,getNthBit(tmp,4));
        setNthBitCW(&message[i],9,getNthBit(tmp,5));
        setNthBitCW(&message[i],10,getNthBit(tmp,6));
        setNthBitCW(&message[i],11,getNthBit(tmp,7));
        setNthBitCW(&message[i],12,getNthBit(tmp,8));

        int p1 = getNthBit(message[i],3)^getNthBit(message[i],5)^getNthBit(message[i],7)^getNthBit(message[i],9)^getNthBit(message[i],11);
        int p2 = getNthBit(message[i],3)^getNthBit(message[i],6)^getNthBit(message[i],7)^getNthBit(message[i],10)^getNthBit(message[i],11);
        int p4 = getNthBit(message[i],5)^getNthBit(message[i],6)^getNthBit(message[i],7)^getNthBit(message[i],12);
        int p8 = getNthBit(message[i],9)^getNthBit(message[i],10)^getNthBit(message[i],11)^getNthBit(message[i],12);

        setNthBitCW(&message[i],1,p1);
        setNthBitCW(&message[i],2,p2);
        setNthBitCW(&message[i],4,p4);
        setNthBitCW(&message[i],8,p8);



    }


    //HHBHBBBHBBBBBB
}



void computeCtrlBits(CodeWord_t *message, int size)
{
    switch (type_){
        case EVEN_PAR:
            compute_even_parity(message,size);
            break;
        case POLY:
            compute_poly(message,size);
            break;
        case HAMMING:
            compute_hamming(message,size);
            break;
        default:
            compute_even_parity(message,size);
            break;
    }
  return;
}


void coding(char *message, int data_size, char *cw, int *cw_size)
{
  *cw_size = data_size * sizeof(CodeWord_t);

  copyDataBitsCoding(message, (CodeWord_t*)cw, data_size);
  //-- to uncomment when complete and needed

  computeCtrlBits((CodeWord_t*)cw, data_size);


  return;
}
