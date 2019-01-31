/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/* 
 * Please fill in the following student struct 
 */
team_t team = {
    "2259166",              /* Student ID */

    "Yavuz Selim Yesilyurt",     /* full name */
    "yesilyurt.selim@metu.edu.tr",  /* email address */

    "",                   /* leave blank */
    ""                    /* leave blank */
};


/***************
 * CONVOLUTION KERNEL
 ***************/

/******************************************************
 * Your different versions of the convolution functions  go here
 ******************************************************/

/* 
 * naive_conv - The naive baseline version of convolution 
 */
char naive_conv_descr[] = "naive_conv: Naive baseline implementation";
void naive_conv(int dim,int *src, int *ker,int *dst) {
    int i,j,k,l;

    for(i = 0; i < dim-8+1; i++)
        for(j = 0; j < dim-8+1; j++) {
            dst[j*dim+i] = 0;
            for(k = 0; k < 8; k++)
                for(l = 0; l < 8; l++) {
                    dst[j*dim+i] = dst[j*dim+i] +src[(j+l)*dim+(i+k)]*ker[l*dim+k];
                }
        }
}

/* 
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
char convolution_descr[] = "Dot product: Current working version";
void convolution(int dim,int *src, int *ker,int *dst) 
{
    int i,j,res,initIndex = dim - 7;
    int kernValues[64];
    int *tmpSrc, *rwDst, *rwSrc;

    for (i = 0; i < 64; i+=8)
    {
        for (j = 0; j < 8; ++j)
            kernValues[i+j] = ker[j];
        ker += dim;
    }    

    for(i = initIndex; i > 0 ; --i) 
    {
        tmpSrc = src; 
        rwDst = dst;
        for(j = initIndex; j > 0 ; --j) 
        {
            rwSrc = tmpSrc;
            res = rwSrc[0] * kernValues[0];
            res += (rwSrc[1] * kernValues[1]) + (rwSrc[2] * kernValues[2]) +
                   (rwSrc[3] * kernValues[3]) + (rwSrc[4] * kernValues[4]) + (rwSrc[5] * kernValues[5]) +
                   (rwSrc[6] * kernValues[6]) + (rwSrc[7] * kernValues[7]);
            rwSrc += dim;
            res += (rwSrc[0] * kernValues[8]) + (rwSrc[1] * kernValues[9]) + (rwSrc[2] * kernValues[10]) +
                   (rwSrc[3] * kernValues[11]) + (rwSrc[4] * kernValues[12]) + (rwSrc[5] * kernValues[13]) +
                   (rwSrc[6] * kernValues[14]) + (rwSrc[7] * kernValues[15]);
            rwSrc += dim;
            res += (rwSrc[0] * kernValues[16]) + (rwSrc[1] * kernValues[17]) + (rwSrc[2] * kernValues[18]) +
                   (rwSrc[3] * kernValues[19]) + (rwSrc[4] * kernValues[20]) + (rwSrc[5] * kernValues[21]) +
                   (rwSrc[6] * kernValues[22]) + (rwSrc[7] * kernValues[23]);
            rwSrc += dim;
            res += (rwSrc[0] * kernValues[24]) + (rwSrc[1] * kernValues[25]) + (rwSrc[2] * kernValues[26]) +
                   (rwSrc[3] * kernValues[27]) + (rwSrc[4] * kernValues[28]) + (rwSrc[5] * kernValues[29]) +
                   (rwSrc[6] * kernValues[30]) + (rwSrc[7] * kernValues[31]);
            rwSrc += dim;
            res += (rwSrc[0] * kernValues[32]) + (rwSrc[1] * kernValues[33]) + (rwSrc[2] * kernValues[34]) +
                   (rwSrc[3] * kernValues[35]) + (rwSrc[4] * kernValues[36]) + (rwSrc[5] * kernValues[37]) +
                   (rwSrc[6] * kernValues[38]) + (rwSrc[7] * kernValues[39]);
            rwSrc += dim;
            res += (rwSrc[0] * kernValues[40]) + (rwSrc[1] * kernValues[41]) + (rwSrc[2] * kernValues[42]) +
                   (rwSrc[3] * kernValues[43]) + (rwSrc[4] * kernValues[44]) + (rwSrc[5] * kernValues[45]) +
                   (rwSrc[6] * kernValues[46]) + (rwSrc[7] * kernValues[47]);
            rwSrc += dim;
            res += (rwSrc[0] * kernValues[48]) + (rwSrc[1] * kernValues[49]) + (rwSrc[2] * kernValues[50]) +
                   (rwSrc[3] * kernValues[51]) + (rwSrc[4] * kernValues[52]) + (rwSrc[5] * kernValues[53]) +
                   (rwSrc[6] * kernValues[54]) + (rwSrc[7] * kernValues[55]);
            rwSrc += dim;
            res += (rwSrc[0] * kernValues[56]) + (rwSrc[1] * kernValues[57]) + (rwSrc[2] * kernValues[58]) +
                   (rwSrc[3] * kernValues[59]) + (rwSrc[4] * kernValues[60]) + (rwSrc[5] * kernValues[61]) +
                   (rwSrc[6] * kernValues[62]) + (rwSrc[7] * kernValues[63]);
            ++tmpSrc;
            *rwDst++ = res;
        }
        src += dim;
        dst += dim;
    }
}


/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_conv_functions() {
    //add_conv_function(&naive_conv, naive_conv_descr);   
    add_conv_function(&convolution, convolution_descr);   
    /* ... Register additional test functions here */
}


/***************
 * MATRIX MULTIP KERNEL
 ***************/

/******************************************************
 * Your different versions of the matrix multiplications  go here
 ******************************************************/

/* 
 * naive_matrix_multiplication - The naive baseline version of matrix multiplication 
 */
char naive_matrix_multiplication_descr[] = "Naive_matrix_multiplication: Naive baseline implementation";
void naive_matrix_multiplication(int dim,int *src, int *src2,int *dst) {
    int i,j,k;

    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++) {
            dst[j*dim+i]=0;
            for(k = 0; k < dim; k++) 
                dst[j*dim+i] = dst[j*dim+i] + src[j*dim+k]*src2[i+k*dim];
        }    
}

/* 
 * matrix_multiplication - Your current working version of matrix_multiplication
 * IMPORTANT: This is the version you will be graded on
 */
char matrix_multiplication_descr[] = "Matrix multiplications: Current working version";
void matrix_multiplication(int dim,int *src, int *src2,int *dst) 
{
    int i,j,k,res;
    int size = dim*dim, offset = dim*(dim-1),initIndex = dim >> 3;
    int *rwSrc2_1 = malloc(size * sizeof(int));
    int *rwSrc2_2 = src2, *rwSrc2_3 = rwSrc2_1;
    int *tmpSrc2_1, *tmpSrc2_2, *tmpSrc2_3, *tmpSrc2_4, *dstTmp, *tmpSrc1;

    for (i = dim; i > 0 ; --i) 
    {
        tmpSrc2_1 = rwSrc2_3;
        tmpSrc2_2 = rwSrc2_2;
        for (j = initIndex; j > 0 ; --j) 
        {
            *tmpSrc2_1  = tmpSrc2_2[0];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[1];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[2];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[3];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[4];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[5];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[6];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[7];
            tmpSrc2_1  += dim;

            tmpSrc2_2 += 8;
        }
        rwSrc2_2 += dim;
        ++rwSrc2_3;
    }    

    dst += dim - 1;
    rwSrc2_1 += offset;

    initIndex = dim >> 5;
    for (i = dim; i > 0 ; --i) 
    {
        tmpSrc2_3 = rwSrc2_1;
        dstTmp  = dst;
        for (j = dim; j > 0 ; --j) 
        {
            res = 0;
            tmpSrc1  = src;
            tmpSrc2_4 = tmpSrc2_3;
            for (k = initIndex; k > 0 ; --k) 
            {
                res += (tmpSrc1[0] * tmpSrc2_4[0]) + (tmpSrc1[1] * tmpSrc2_4[1]) + (tmpSrc1[2] * tmpSrc2_4[2]) +
                       (tmpSrc1[3] * tmpSrc2_4[3]) + (tmpSrc1[4] * tmpSrc2_4[4]) + (tmpSrc1[5] * tmpSrc2_4[5]) +
                       (tmpSrc1[6] * tmpSrc2_4[6]) + (tmpSrc1[7] * tmpSrc2_4[7]) + (tmpSrc1[8] * tmpSrc2_4[8]) +
                       (tmpSrc1[9] * tmpSrc2_4[9]) + (tmpSrc1[10] * tmpSrc2_4[10]) + (tmpSrc1[11] * tmpSrc2_4[11]) +
                       (tmpSrc1[12] * tmpSrc2_4[12]) + (tmpSrc1[13] * tmpSrc2_4[13]) + (tmpSrc1[14] * tmpSrc2_4[14]) +
                       (tmpSrc1[15] * tmpSrc2_4[15]) + (tmpSrc1[16] * tmpSrc2_4[16]) + (tmpSrc1[17] * tmpSrc2_4[17]) +
                       (tmpSrc1[18] * tmpSrc2_4[18]) + (tmpSrc1[19] * tmpSrc2_4[19]) + (tmpSrc1[20] * tmpSrc2_4[20]) +
                       (tmpSrc1[21] * tmpSrc2_4[21]) + (tmpSrc1[22] * tmpSrc2_4[22]) + (tmpSrc1[23] * tmpSrc2_4[23]) +
                       (tmpSrc1[24] * tmpSrc2_4[24]) + (tmpSrc1[25] * tmpSrc2_4[25]) + (tmpSrc1[26] * tmpSrc2_4[26]) +
                       (tmpSrc1[27] * tmpSrc2_4[27]) + (tmpSrc1[28] * tmpSrc2_4[28]) + (tmpSrc1[29] * tmpSrc2_4[29]) +
                       (tmpSrc1[30] * tmpSrc2_4[30]) + (tmpSrc1[31] * tmpSrc2_4[31]);
                tmpSrc1 += 32;
                tmpSrc2_4 += 32;
            }

            *dstTmp = res;
            --dstTmp;
            tmpSrc2_3 -= dim;
        }
        dst += dim;
        src += dim;
    }    
}

/*********************************************************************
 * register_matrix_multiplication_functions - Register all of your different versions
 *     of the matrix multiplication  with the driver by calling the
 *     add_matrix_multiplication_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_matrix_multiplication_functions() {
    // add_matrix_multiplication_function(&naive_matrix_multiplication, naive_matrix_multiplication_descr);   
    add_matrix_multiplication_function(&matrix_multiplication, matrix_multiplication_descr);   
    /* ... Register additional test functions here */
}

