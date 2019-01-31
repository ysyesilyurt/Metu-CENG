/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x9ca8bed6 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/home/yavuz/Desktop/lab4_1/testbench_ROM.v";
static const char *ng1 = "1/2 = %d";
static int ng2[] = {1, 0};
static int ng3[] = {2, 0};



static void Initial_5_0(char *t0)
{
    char t3[8];
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(5, ng0);

LAB2:    xsi_set_current_line(6, ng0);
    t1 = ((char*)((ng2)));
    t2 = ((char*)((ng3)));
    memset(t3, 0, 8);
    xsi_vlog_signed_divide(t3, 32, t1, 32, t2, 32);
    xsi_vlogfile_write(1, 0, 0, ng1, 2, t0, (char)119, t3, 32);

LAB1:    return;
}


extern void work_m_00000000000000000000_0210835833_init()
{
	static char *pe[] = {(void *)Initial_5_0};
	xsi_register_didat("work_m_00000000000000000000_0210835833", "isim/sa_isim_beh.exe.sim/work/m_00000000000000000000_0210835833.didat");
	xsi_register_executes(pe);
}
