
#include <stdio.h>
#include <stdlib.h>
#include "libhello.h"

void my_func(struct Result *r)
{
    // Populating the result with some data:
    // - Single buffer contains this byte array 0x01, 0x02, 0x03
    // - The array of buffers contains 2 buffers:
    // --- Buffer1:  0x04, 0x05
    // --- Buffer2:  0x06
    
    r->singleBuff.len = 3;
    uint8_t *data1 = (uint8_t *)malloc(r->singleBuff.len * sizeof(uint8_t));
    data1[0] = 0x01;
    data1[1] = 0x02;
    data1[2] = 0x03;
    r->singleBuff.ptr = data1;
   
    r->lenBuffArr = 2;
    r->ptrBuffArr = (Buffer *)malloc(2 * sizeof(Buffer));

    Buffer buffer1;
    buffer1.len = 2;
    uint8_t *data2 = (uint8_t *)malloc(buffer1.len * sizeof(uint8_t));
    data2[0] = 0x04;
    data2[1] = 0x05;
    buffer1.ptr = data2;
    r->ptrBuffArr[0] = buffer1;

    Buffer buffer2;
    buffer2.len = 1;
    uint8_t *data3 = (uint8_t *)malloc(buffer2.len * sizeof(uint8_t));
    data3[0] = 0x06;
    buffer2.ptr = data3;
    r->ptrBuffArr[1] = buffer2;
}

void free_result(struct Result *r) 
{
    // This assumes the result fields are populated
    free((void *) r->singleBuff.ptr);
    for (int i = 0; i < r->lenBuffArr; i++) {
        free((void *) r->ptrBuffArr[i].ptr);
    }
}