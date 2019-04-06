//
// Created by seyyidahmedlahmer on 4/4/19.
//
#include <codingdecoding.h>
#include <stdlib.h>
#include "stdio.h"


int main(){

    //set_type();
    type_ = 1;


    CodeWord_t c[4];
    char* message = "1234";
    int size;
    coding(message,4, (char *) &c, &size);
    printBits(c[0],"1/1");
    setNthBitCW(&c[0],5,1);
    printBits(c[0],"1/2");

    printBits(c[0],"1/1");
    setNthBitCW(&c[0],5,2);
    printBits(c[0],"1/2");

    printBits(c[1],"2/1");
    setNthBitCW(&c[1],1,1);
    printBits(c[1],"2/2");

    printBits(c[2],"3/1");
    setNthBitCW(&c[2],8,1);
    printBits(c[2],"3/2");

    printBits(c[3],"3/1");
    setNthBitCW(&c[3],12,1);
    printBits(c[3],"3/2");

  //  printBits(c,"CCC");
    char out[5];
    int s;
    decoding((char *) &c, size, out, &s);

    printf("%s",out);


    return 0;
}