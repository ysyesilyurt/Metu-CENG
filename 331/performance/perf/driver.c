/*******************************************************************
 * 
 * driver.c - Driver program for CS:APP Performance Lab
 * 
 * In kernels.c, students generate an arbitrary number of transpose and
 * col_convert test functions, which they then register with the driver
 * program using the add_transpose_function(), 
 * add_col_convert_function() and add_matrix_multiplication_function
 * functions.
 * 
 * The driver program runs and measures the registered test functions
 * and reports their performance.
 * 
 * Copyright (c) 2002, R. Bryant and D. O'Hallaron, All rights
 * reserved.  May not be used, modified, or copied without permission.
 *
 ********************************************************************/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "fcyc.h"
#include "defs.h"
#include "config.h"

/* Team structure that identifies the students */
extern team_t team; 

/* Keep track of a number of different test functions */
#define MAX_BENCHMARKS 100
#define DIM_CNT 5

/* Misc constants */
#define BSIZE 32     /* cache block size in bytes */     
#define MAX_DIM 1280 /* 1024 + 256 */
#define ODD_DIM 96   /* not a power of 2 */

/* fast versions of min and max */
#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)

/* This struct characterizes the results for one benchmark test */
typedef struct {
	int func_type;
	union func{
        lab_test_func3 tfunct3;
        lab_test_func5 tfunct5;
	} tfunct;
    ; /* The test function */
    double cpes[DIM_CNT]; /* One CPE result for each dimension */
    char *description;    /* ASCII description of the test function */
    unsigned short valid; /* The function is tested if this is non zero */
} bench_t;

/* The range of matrix dimensions that we will be testing */
static int test_dim_conv[] = {32, 64, 128, 256, 512};
static int test_dim_multip[] = {32, 64, 128, 256, 512};

/* Baseline CPEs (see config.h) */
static double conv_baseline_cpes[] = {C32, C64, C128, C256, C512};
static double multip_baseline_cpes[] = {M32, M64, M128, M256, M512};

/* These hold the results for all benchmarks */
static bench_t benchmarks_conv[MAX_BENCHMARKS];
static bench_t benchmarks_multip[MAX_BENCHMARKS];

/* These give the sizes of the above lists */
static int conv_benchmark_count = 0;
static int multip_benchmark_count = 0;

/* 
 * An matrix is a dimxdim matrix of ints stored in a 1D array.  The
 * data array holds three matrixs (the input original, a copy of the original, 
 * and the output result array. There is also an additional BSIZE bytes
 * of padding for alignment to cache block boundaries.
 */
static int data[(3*MAX_DIM*MAX_DIM) + (BSIZE/sizeof(int))];
static int data2[(3*MAX_DIM*MAX_DIM) + (BSIZE/sizeof(int))];
/* Various matrix pointers */
static int *orig = NULL;         /* original matrix */
static int *orig2 = NULL;        /* second matrix original */
static int *copy_of_orig = NULL; /* copy of original for checking result */
static int *copy_of_orig2 = NULL;/* copy of second original for checking result*/
static int *result = NULL;       /* result matrix */

/* Keep track of the best transpose and col_convert score for grading */
double conv_maxmean = 0.0;
char *conv_maxmean_desc = NULL;





double multip_maxmean = 0.0;
char *multip_maxmean_desc = NULL;





/******************** Functions begin *************************/
void add_conv_function(lab_test_func5 f, char *description) 
{
    benchmarks_conv[conv_benchmark_count].func_type = 5;
    benchmarks_conv[conv_benchmark_count].tfunct.tfunct5 = f;
    benchmarks_conv[conv_benchmark_count].description = description;
    benchmarks_conv[conv_benchmark_count].valid = 0;  
    conv_benchmark_count++;
}







void add_matrix_multiplication_function(lab_test_func3 f, char *description) 
{
    benchmarks_multip[multip_benchmark_count].func_type = 3;
    benchmarks_multip[multip_benchmark_count].tfunct.tfunct3 = f;
    benchmarks_multip[multip_benchmark_count].description = description;
    benchmarks_multip[multip_benchmark_count].valid = 0;  
    multip_benchmark_count++;
}




/* 
 * random_in_interval - Returns random integer in interval [low, high) 
 */
static int random_in_interval(int low, int high) 
{
    int size = high - low;
    return (rand()% size) + low;
}

/*
 * create - creates a dimxdim matrix aligned to a BSIZE byte boundary
 */
static void create(int dim, int flag)
{
    int i, j;

    /* Align the matrixs to BSIZE byte boundaries */
    orig = data;
    orig2 = data2;
    while ((unsigned)orig % BSIZE)
		orig = (int *)(((char *)orig) + 1);
    result = orig + dim*dim;
    copy_of_orig = result + dim*dim;

    for (i = 0; i < dim; i++) {
	for (j = 0; j < dim; j++) {
	    /* Original matrix initialized to random colors */
		if(flag==1)
	    	orig[RIDX(i,j,dim)] = random_in_interval(0, 10);
	    else
	   		orig[RIDX(i,j,dim)] = random_in_interval(0, 2);

	    /* Copy of original matrix for checking result */
	    copy_of_orig[RIDX(i,j,dim)] = orig[RIDX(i,j,dim)];
	   

	    /* Result matrix initialized to all black */
	    result[RIDX(i,j,dim)] = 0;
	}
    }

    while ((unsigned)orig2 % BSIZE)
        orig2 = (int *)(((char *)orig2) + 1);
    result = orig2 + dim*dim;
    copy_of_orig2 = result + dim*dim;

    for (i = 0; i < dim; i++) {
    for (j = 0; j < dim; j++) {
        /* Original2 matrix initialized to random colors */
        if(flag==1)
            orig2[RIDX(i,j,dim)] = random_in_interval(0, 10);
        else
            orig2[RIDX(i,j,dim)] = random_in_interval(0, 2);

        /* Copy of original2 matrix for checking result */
        copy_of_orig2[RIDX(i,j,dim)] = orig2[RIDX(i,j,dim)];
       

        /* Result matrix initialized to all black */
    }
    }

    return;
}


/* 
 * compare_ints - Returns 1 if the two arguments don't have same RGB
 *    values, 0 o.w.  
 */
static int compare_ints(int p1, int p2) 
{
    return 
	(p1 != p2);
}


/* Make sure the orig array is unchanged */
static int check_orig(int dim) 
{
    int i, j;

    for (i = 0; i < dim; i++) 
	for (j = 0; j < dim; j++) 
	    if (compare_ints(orig[RIDX(i,j,dim)], copy_of_orig[RIDX(i,j,dim)])) {
		printf("\n");
		printf("Error: Original matrix has been changed!\n");
		return 1;
	    }

    return 0;
}
/* Make sure the orig2 array is unchanged */
static int check_orig2(int dim) 
{
    int i, j;

    for (i = 0; i < dim; i++) 
    for (j = 0; j < dim; j++) 
        if (compare_ints(orig2[RIDX(i,j,dim)], copy_of_orig2[RIDX(i,j,dim)])) {
        printf("\n");
        printf("Error: Second Original matrix has been changed!\n");
        return 1;
        }

    return 0;
}



/* 
 * check_conv - Make sure the convolution actually works. 
 * The orig array and orig2 arrays should not  have been tampered with! 
 */
static int check_conv(int dim) 
{
    int err = 0;
    int i, j,k,l ,sum;
    int err_sum;
    int badi,badj;

    /* return 1 if the original matrix has been  changed */
    if (check_orig(dim)) 
    return 1; 
    /* return 1 if the second original matrix has been  changed */
    if (check_orig2(dim)) 
    return 1; 

    for(i = 0; i < dim-8+1; i++)
        for(j = 0; j < dim-8+1; j++) {
            sum = 0;
            for(k = 0; k < 8; k++)
                for(l = 0; l < 8; l++) {
                    sum = sum +orig[(j+l)*dim+(i+k)]*orig2[l*dim+k];
                }
            if(compare_ints(sum, 
               result[RIDX(j,i,dim)])) {
            badi=i;
            badj=j;
            err_sum = sum;
            err++;
            
        }

        }

    
            
    if (err) {
    printf("\n");
    printf("ERROR: Dimension=%d, %d errors\n", dim, err);    
    printf("Check your convolution results:in result i[%d] j[%d] res=%d correct =%d\n",badi,badj,result[RIDX(j,i,dim)],err_sum);
       

    
    }
    return err;
}







/* 
 * check_multip - Make sure the matrix_multiplication actually works. 
 * The orig array and orig2 arrays should not  have been tampered with! 
 */
static int check_multip(int dim) 
{
    int err = 0;
    int i, j, k, sum;
    int err_sum;
    int badi,badj;

    /* return 1 if the original matrix has been  changed */
    if (check_orig(dim)) 
    return 1; 
    /* return 1 if the second original matrix has been  changed */
    if (check_orig2(dim)) 
    return 1; 

    

    for(i = 0; i < dim; i++)
    for(j = 0; j < dim; j++){
        sum = 0;
        for(k = 0; k < dim; k++) {
            sum = sum + orig[j*dim+k]*orig2[i+k*dim];
        }
        if(compare_ints(sum, 
               result[RIDX(j,i,dim)])) {
            badi=i;
            badj=j;
            err_sum = sum;
            err++;
            
        }
    } 
            
    if (err) {
    printf("\n");
    printf("ERROR: Dimension=%d, %d errors\n", dim, err);    
    printf("Check your multip results:in result i[%d] j[%d] res=%d correct =%d\n",badi,badj,result[RIDX(j,i,dim)],err_sum);
       

    
    }
    return err;
}




void func_wrapper(void *arglist[]) 
{
    int *src, *src2, *dst;
    int mydim;
    lab_test_func3 f3;
    lab_test_func5 f5;
	int type;
	type = *((int*) arglist[0]);
	if( type == 3 ) {
        f3 = (lab_test_func3) arglist[1];
        mydim = *((int *) arglist[2]);
        src = (int *) arglist[3];
        src2 = (int *) arglist[4];
        dst = (int *) arglist[5];
        (*f3)(mydim, src, src2, dst);

    } else if( type == 5 ) {
        f5 = (lab_test_func5) arglist[1];
        mydim = *((int *) arglist[2]);
        src = (int *) arglist[3];
        src2 = (int *) arglist[4];
        dst = (int *) arglist[5];
        (*f5)(mydim, src, src2, dst);

    }
	
    

    

    return;
}
/*conv benchmark*/
void run_conv_benchmark(int idx, int dim) {
    benchmarks_conv[idx].tfunct.tfunct5(dim, orig, orig2, result);
}

void test_conv(int bench_index) {

    int i;
    int test_num;
    char *description = benchmarks_conv[bench_index].description;
    for (test_num = 0; test_num < DIM_CNT; test_num++) {
    int dim;
    /* Check for odd dimension */
    create(ODD_DIM,1);
    run_conv_benchmark(bench_index, ODD_DIM);
    if (check_conv(ODD_DIM)) {
        printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
           benchmarks_conv[bench_index].description, ODD_DIM);
        return;
    }
    
    /* Create a test matrix of the required dimension */
    dim = test_dim_conv[test_num];
    create(dim,1);
#ifdef DEBUG
    printf("DEBUG: Running benchmark \"%s\"\n", benchmarks_conv[bench_index].description);
#endif
    /* Check that the code works */
    run_conv_benchmark(bench_index, dim);
    if (check_conv(dim)) {
        printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
           benchmarks_conv[bench_index].description, dim);
        return;
    }

    /* Measure CPE */
    {
        double num_cycles, cpe;
        int tmpdim = dim;
        void *arglist[6];
        double dimension = (double) dim;
        double work = dimension*dimension;
#ifdef DEBUG
        printf("DEBUG: dimension=%.1f\n",dimension);
        printf("DEBUG: work=%.1f\n",work);
#endif
        int tmp_type = 5;
        arglist[0] = &tmp_type;
        arglist[1] = (void *) benchmarks_conv[bench_index].tfunct.tfunct3;
        arglist[2] = (void *) &tmpdim;
        arglist[3] = (void *) orig;
        arglist[4] = (void *) orig2;
        arglist[5] = (void *) result;

        create(dim,1);
        num_cycles=0;
        num_cycles = fcyc_v((test_funct_v)&func_wrapper, arglist); 
        cpe = num_cycles/work;
        benchmarks_conv[bench_index].cpes[test_num] = cpe;
    }
    }


    /* 
     * Print results as a table 
     */
    printf("conv: Version = %s:\n", description);
    printf("Dim\t");
    for (i = 0; i < DIM_CNT; i++)
    printf("\t%d", test_dim_conv[i]);
    printf("\tMean\n");
  
    printf("Your CPEs");
    for (i = 0; i < DIM_CNT; i++) {
    printf("\t%.1f", benchmarks_conv[bench_index].cpes[i]);
    }
    printf("\n");

    printf("Baseline CPEs");
    for (i = 0; i < DIM_CNT; i++) {
    printf("\t%.1f", conv_baseline_cpes[i]);
    }
    printf("\n");

    /* Compute Speedup */
    {
    double prod, ratio, mean;
    prod = 1.0; /* Geometric mean */
    printf("Speedup\t");
    for (i = 0; i < DIM_CNT; i++) {
        if (benchmarks_conv[bench_index].cpes[i] > 0.0) {
        ratio = conv_baseline_cpes[i]/
            benchmarks_conv[bench_index].cpes[i];
        }
        else {
        printf("Fatal Error: Non-positive CPE value...\n");
        exit(EXIT_FAILURE);
        }
        prod *= ratio;
        printf("\t%.1f", ratio);
    }

    /* Geometric mean */
    mean = pow(prod, 1.0/(double) DIM_CNT);
    printf("\t%.1f", mean);
    printf("\n\n");
    if (mean > conv_maxmean) {
        conv_maxmean = mean;
        conv_maxmean_desc = benchmarks_conv[bench_index].description;
    }
    }


#ifdef DEBUG
    fflush(stdout);
#endif
    return;  


}

/*conv benchmark end*/


void run_multip_benchmark(int idx, int dim) {
    benchmarks_multip[idx].tfunct.tfunct3(dim, orig, orig2, result);
}

void test_multip(int bench_index) {

    int i;
    int test_num;
    char *description = benchmarks_multip[bench_index].description;
    for (test_num = 0; test_num < DIM_CNT; test_num++) {
    int dim;
    /* Check for odd dimension */
    create(ODD_DIM,1);
    run_multip_benchmark(bench_index, ODD_DIM);
    if (check_multip(ODD_DIM)) {
        printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
           benchmarks_multip[bench_index].description, ODD_DIM);
        return;
    }
    
    /* Create a test matrix of the required dimension */
    dim = test_dim_multip[test_num];
    create(dim,1);
#ifdef DEBUG
    printf("DEBUG: Running benchmark \"%s\"\n", benchmarks_multip[bench_index].description);
#endif
    /* Check that the code works */
    run_multip_benchmark(bench_index, dim);
    if (check_multip(dim)) {
        printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
           benchmarks_multip[bench_index].description, dim);
        return;
    }

    /* Measure CPE */
    {
        double num_cycles, cpe;
        int tmpdim = dim;
        void *arglist[6];
        double dimension = (double) dim;
        double work = dimension*dimension;
#ifdef DEBUG
        printf("DEBUG: dimension=%.1f\n",dimension);
        printf("DEBUG: work=%.1f\n",work);
#endif
        int tmp_type = 3;
        arglist[0] = &tmp_type;
        arglist[1] = (void *) benchmarks_multip[bench_index].tfunct.tfunct3;
        arglist[2] = (void *) &tmpdim;
        arglist[3] = (void *) orig;
        arglist[4] = (void *) orig2;
        arglist[5] = (void *) result;

        create(dim,1);
        num_cycles=0;
        num_cycles = fcyc_v((test_funct_v)&func_wrapper, arglist); 
        cpe = num_cycles/work;
        benchmarks_multip[bench_index].cpes[test_num] = cpe;
    }
    }


    /* 
     * Print results as a table 
     */
    printf("Multip: Version = %s:\n", description);
    printf("Dim\t");
    for (i = 0; i < DIM_CNT; i++)
    printf("\t%d", test_dim_multip[i]);
    printf("\tMean\n");
  
    printf("Your CPEs");
    for (i = 0; i < DIM_CNT; i++) {
    printf("\t%.1f", benchmarks_multip[bench_index].cpes[i]);
    }
    printf("\n");

    printf("Baseline CPEs");
    for (i = 0; i < DIM_CNT; i++) {
    printf("\t%.1f", multip_baseline_cpes[i]);
    }
    printf("\n");

    /* Compute Speedup */
    {
    double prod, ratio, mean;
    prod = 1.0; /* Geometric mean */
    printf("Speedup\t");
    for (i = 0; i < DIM_CNT; i++) {
        if (benchmarks_multip[bench_index].cpes[i] > 0.0) {
        ratio = multip_baseline_cpes[i]/
            benchmarks_multip[bench_index].cpes[i];
        }
        else {
        printf("Fatal Error: Non-positive CPE value...\n");
        exit(EXIT_FAILURE);
        }
        prod *= ratio;
        printf("\t%.1f", ratio);
    }

    /* Geometric mean */
    mean = pow(prod, 1.0/(double) DIM_CNT);
    printf("\t%.1f", mean);
    printf("\n\n");
    if (mean > multip_maxmean) {
        multip_maxmean = mean;
        multip_maxmean_desc = benchmarks_multip[bench_index].description;
    }
    }


#ifdef DEBUG
    fflush(stdout);
#endif
    return;  


}



void usage(char *progname) 
{
    fprintf(stderr, "Usage: %s [-hqg] [-f <func_file>] [-d <dump_file>]\n", progname);    
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -h         Print this message\n");
    fprintf(stderr, "  -q         Quit after dumping (use with -d )\n");
    fprintf(stderr, "  -g         Autograder mode: checks only transpose() and col_convert()\n");
    fprintf(stderr, "  -f <file>  Get test function names from dump file <file>\n");
    fprintf(stderr, "  -d <file>  Emit a dump file <file> for later use with -f\n");
    exit(EXIT_FAILURE);
}



int main(int argc, char *argv[])
{
    int i;
    int quit_after_dump = 0;
    int skip_teamname_check = 0;
    int autograder = 0;
    int seed = 1729;
    char c = '0';
    char *bench_func_file = NULL;
    char *func_dump_file = NULL;

    /* register all the defined functions */
    register_conv_functions();
    register_matrix_multiplication_functions();

    /* parse command line args */
    while ((c = getopt(argc, argv, "tgqf:d:s:h")) != -1)
	switch (c) {

	case 't': /* skip team name check (hidden flag) */
	    skip_teamname_check = 1;
	    break;

	case 's': /* seed for random number generator (hidden flag) */
	    seed = atoi(optarg);
	    break;

	case 'g': /* autograder mode (checks only transpose() and col_convert()) */
	    autograder = 1;
	    break;

	case 'q':
	    quit_after_dump = 1;
	    break;

	case 'f': /* get names of benchmark functions from this file */
	    bench_func_file = strdup(optarg);
	    break;

	case 'd': /* dump names of benchmark functions to this file */
	    func_dump_file = strdup(optarg);
	    {
		int i;
		FILE *fp = fopen(func_dump_file, "w");	

		if (fp == NULL) {
		    printf("Can't open file %s\n",func_dump_file);
		    exit(-5);
		}
        for(i = 0; i < conv_benchmark_count; i++) {
            fprintf(fp, "R:%s\n", benchmarks_conv[i].description); 
        }
        for(i = 0; i < multip_benchmark_count; i++) {
            fprintf(fp, "R:%s\n", benchmarks_multip[i].description); 
        }
		fclose(fp);
	    }
	    break;

	case 'h': /* print help message */
	    usage(argv[0]);

	default: /* unrecognized argument */
	    usage(argv[0]);
	}

    if (quit_after_dump) 
	exit(EXIT_SUCCESS);

    /* Print team info */
    if (!skip_teamname_check) {
	if (strcmp("ID", team.team) == 0) {
	    printf("%s: Please fill in your ID in kernels.c.\n", argv[0]);
	    exit(1);
	}
	printf("ID: %s\n", team.team);
	printf("Name: %s\n", team.name1);
	printf("Email: %s\n", team.email1);
	if (*team.name2 || *team.email2) {
	    printf("Name 2: %s\n", team.name2);
	    printf("Email 2: %s\n", team.email2);
	}
	printf("\n");
    }

    srand(seed);

    /* 
     * If we are running in autograder mode, we will only test
     * the transpose() and bench() functions.
     */
    if (autograder) {
    conv_benchmark_count = 1;
    multip_benchmark_count = 1;

    benchmarks_conv[0].tfunct.tfunct5 = convolution;
    benchmarks_conv[0].description = "convolution() function";
    benchmarks_conv[0].valid = 1;

    benchmarks_multip[0].tfunct.tfunct3 = matrix_multiplication;
    benchmarks_multip[0].description = "matrix_multiplication() function";
    benchmarks_multip[0].valid = 1;
    }

    /* 
     * If the user specified a file name using -f, then use
     * the file to determine the versions of transpose and col_convert to test
     */
    else if (bench_func_file != NULL) {

    	char flag;
    	char func_line[256];
    	FILE *fp = fopen(bench_func_file, "r");

    	if (fp == NULL) {
    	    printf("Can't open file %s\n",bench_func_file);
    	    exit(-5);
    	}
    
    	while(func_line == fgets(func_line, 256, fp)) {
    	    char *func_name = func_line;
    	    char **strptr = &func_name;
    	    char *token = strsep(strptr, ":");
    	    flag = token[0];
    	    func_name = strsep(strptr, "\n");
#ifdef DEBUG
	    printf("Function Description is %s\n",func_name);
#endif

        if (flag == 'C') {
            for(i=0; i<conv_benchmark_count; i++) {
                if (strcmp(benchmarks_conv[i].description, func_name) == 0)
                benchmarks_conv[i].valid = 1;
        }
        }

        if (flag == 'M') {
            for(i=0; i<multip_benchmark_count; i++) {
                if (strcmp(benchmarks_multip[i].description, func_name) == 0)
                benchmarks_multip[i].valid = 1;
        }
        }

 
	}

	fclose(fp);
    }

    /* 
     * If the user didn't specify a dump file using -f, then 
     * test all of the functions
     */
    else { /* set all valid flags to 1 */

    for (i = 0; i < conv_benchmark_count; i++)
        benchmarks_conv[i].valid = 1;

    for (i = 0; i < multip_benchmark_count; i++)
        benchmarks_multip[i].valid = 1;

    }

    /* Set measurement (fcyc) parameters */
    set_fcyc_cache_size(1 << 14); /* 16 KB cache size */
    set_fcyc_clear_cache(1); /* clear the cache before each measurement */
    set_fcyc_compensate(1); /* try to compensate for timer overhead */
 

    for(i = 0; i < conv_benchmark_count; i++) {
        if(benchmarks_conv[i].valid)
            test_conv(i);
    } 

    for(i = 0; i < multip_benchmark_count; i++) {
        if(benchmarks_multip[i].valid)
            test_multip(i);
    }


    
   


    if (autograder) {
	printf("\nbestscores:%.1f:%.1f:\n",multip_maxmean,conv_maxmean);
    }
    else {
	printf("Summary of Your Best Scores:\n");
    printf("  Matrix Multiplication: %3.1f (%s)\n", multip_maxmean, multip_maxmean_desc);
    printf("  Convolution: %3.1f (%s)\n", conv_maxmean, conv_maxmean_desc);
    }

    return 0;
}














