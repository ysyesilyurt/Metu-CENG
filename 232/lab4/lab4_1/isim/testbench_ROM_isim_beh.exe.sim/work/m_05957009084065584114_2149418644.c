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
static const char *ng1 = "Starting Testbench";
static unsigned int ng2[] = {0U, 0U};
static int ng3[] = {1, 0};
static const char *ng4 = "time:";
static const char *ng5 = ":For romAddress:%b Error in romData:%b";
static unsigned int ng6[] = {1U, 0U};
static unsigned int ng7[] = {2U, 0U};
static unsigned int ng8[] = {4U, 0U};
static unsigned int ng9[] = {3U, 0U};
static unsigned int ng10[] = {7U, 0U};
static unsigned int ng11[] = {10U, 0U};
static unsigned int ng12[] = {5U, 0U};
static unsigned int ng13[] = {11U, 0U};
static unsigned int ng14[] = {6U, 0U};
static unsigned int ng15[] = {13U, 0U};
static unsigned int ng16[] = {14U, 0U};
static unsigned int ng17[] = {8U, 0U};
static unsigned int ng18[] = {17U, 0U};
static unsigned int ng19[] = {9U, 0U};
static unsigned int ng20[] = {18U, 0U};
static unsigned int ng21[] = {20U, 0U};
static unsigned int ng22[] = {23U, 0U};
static unsigned int ng23[] = {12U, 0U};
static unsigned int ng24[] = {25U, 0U};
static unsigned int ng25[] = {26U, 0U};
static unsigned int ng26[] = {30U, 0U};
static unsigned int ng27[] = {15U, 0U};
static unsigned int ng28[] = {31U, 0U};
static const char *ng29 = "Result %d";
static const char *ng30 = "Testbench was finished";



static void Initial_11_0(char *t0)
{
    char t4[8];
    char t30[8];
    char t32[16];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    char *t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    char *t31;

LAB0:    t1 = (t0 + 2520U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(11, ng0);

LAB4:    xsi_set_current_line(13, ng0);
    xsi_vlogfile_write(1, 0, 0, ng1, 1, t0);
    xsi_set_current_line(16, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB5;

LAB1:    return;
LAB5:    xsi_set_current_line(17, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(18, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB6;
    goto LAB1;

LAB6:    xsi_set_current_line(19, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng2)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB10;

LAB7:    if (t16 != 0)
        goto LAB9;

LAB8:    *((unsigned int *)t4) = 1;

LAB10:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB11;

LAB12:    xsi_set_current_line(20, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB13:    xsi_set_current_line(22, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB14;
    goto LAB1;

LAB9:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB10;

LAB11:    xsi_set_current_line(19, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB13;

LAB14:    xsi_set_current_line(24, ng0);
    t2 = ((char*)((ng6)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(25, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB15;
    goto LAB1;

LAB15:    xsi_set_current_line(26, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng7)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB19;

LAB16:    if (t16 != 0)
        goto LAB18;

LAB17:    *((unsigned int *)t4) = 1;

LAB19:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB20;

LAB21:    xsi_set_current_line(27, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB22:    xsi_set_current_line(29, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB23;
    goto LAB1;

LAB18:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB19;

LAB20:    xsi_set_current_line(26, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB22;

LAB23:    xsi_set_current_line(31, ng0);
    t2 = ((char*)((ng7)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(32, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB24;
    goto LAB1;

LAB24:    xsi_set_current_line(33, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng8)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB28;

LAB25:    if (t16 != 0)
        goto LAB27;

LAB26:    *((unsigned int *)t4) = 1;

LAB28:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB29;

LAB30:    xsi_set_current_line(34, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB31:    xsi_set_current_line(36, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB32;
    goto LAB1;

LAB27:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB28;

LAB29:    xsi_set_current_line(33, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB31;

LAB32:    xsi_set_current_line(38, ng0);
    t2 = ((char*)((ng9)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(39, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB33;
    goto LAB1;

LAB33:    xsi_set_current_line(40, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng10)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB37;

LAB34:    if (t16 != 0)
        goto LAB36;

LAB35:    *((unsigned int *)t4) = 1;

LAB37:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB38;

LAB39:    xsi_set_current_line(41, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB40:    xsi_set_current_line(42, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB41;
    goto LAB1;

LAB36:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB37;

LAB38:    xsi_set_current_line(40, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB40;

LAB41:    xsi_set_current_line(44, ng0);
    t2 = ((char*)((ng8)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(45, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB42;
    goto LAB1;

LAB42:    xsi_set_current_line(46, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng11)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB46;

LAB43:    if (t16 != 0)
        goto LAB45;

LAB44:    *((unsigned int *)t4) = 1;

LAB46:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB47;

LAB48:    xsi_set_current_line(47, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB49:    xsi_set_current_line(49, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB50;
    goto LAB1;

LAB45:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB46;

LAB47:    xsi_set_current_line(46, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB49;

LAB50:    xsi_set_current_line(51, ng0);
    t2 = ((char*)((ng12)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(52, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB51;
    goto LAB1;

LAB51:    xsi_set_current_line(53, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng13)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB55;

LAB52:    if (t16 != 0)
        goto LAB54;

LAB53:    *((unsigned int *)t4) = 1;

LAB55:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB56;

LAB57:    xsi_set_current_line(54, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB58:    xsi_set_current_line(55, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB59;
    goto LAB1;

LAB54:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB55;

LAB56:    xsi_set_current_line(53, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB58;

LAB59:    xsi_set_current_line(57, ng0);
    t2 = ((char*)((ng14)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(58, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB60;
    goto LAB1;

LAB60:    xsi_set_current_line(59, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng15)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB64;

LAB61:    if (t16 != 0)
        goto LAB63;

LAB62:    *((unsigned int *)t4) = 1;

LAB64:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB65;

LAB66:    xsi_set_current_line(60, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB67:    xsi_set_current_line(62, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB68;
    goto LAB1;

LAB63:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB64;

LAB65:    xsi_set_current_line(59, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB67;

LAB68:    xsi_set_current_line(64, ng0);
    t2 = ((char*)((ng10)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(65, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB69;
    goto LAB1;

LAB69:    xsi_set_current_line(66, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng16)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB73;

LAB70:    if (t16 != 0)
        goto LAB72;

LAB71:    *((unsigned int *)t4) = 1;

LAB73:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB74;

LAB75:    xsi_set_current_line(67, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB76:    xsi_set_current_line(68, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB77;
    goto LAB1;

LAB72:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB73;

LAB74:    xsi_set_current_line(66, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB76;

LAB77:    xsi_set_current_line(70, ng0);
    t2 = ((char*)((ng17)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(71, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB78;
    goto LAB1;

LAB78:    xsi_set_current_line(72, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng18)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB82;

LAB79:    if (t16 != 0)
        goto LAB81;

LAB80:    *((unsigned int *)t4) = 1;

LAB82:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB83;

LAB84:    xsi_set_current_line(73, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB85:    xsi_set_current_line(75, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB86;
    goto LAB1;

LAB81:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB82;

LAB83:    xsi_set_current_line(72, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB85;

LAB86:    xsi_set_current_line(77, ng0);
    t2 = ((char*)((ng19)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(78, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB87;
    goto LAB1;

LAB87:    xsi_set_current_line(79, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng20)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB91;

LAB88:    if (t16 != 0)
        goto LAB90;

LAB89:    *((unsigned int *)t4) = 1;

LAB91:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB92;

LAB93:    xsi_set_current_line(80, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB94:    xsi_set_current_line(82, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB95;
    goto LAB1;

LAB90:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB91;

LAB92:    xsi_set_current_line(79, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB94;

LAB95:    xsi_set_current_line(84, ng0);
    t2 = ((char*)((ng11)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(85, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB96;
    goto LAB1;

LAB96:    xsi_set_current_line(86, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng21)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB100;

LAB97:    if (t16 != 0)
        goto LAB99;

LAB98:    *((unsigned int *)t4) = 1;

LAB100:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB101;

LAB102:    xsi_set_current_line(87, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB103:    xsi_set_current_line(88, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB104;
    goto LAB1;

LAB99:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB100;

LAB101:    xsi_set_current_line(86, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB103;

LAB104:    xsi_set_current_line(90, ng0);
    t2 = ((char*)((ng13)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(91, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB105;
    goto LAB1;

LAB105:    xsi_set_current_line(92, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng22)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB109;

LAB106:    if (t16 != 0)
        goto LAB108;

LAB107:    *((unsigned int *)t4) = 1;

LAB109:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB110;

LAB111:    xsi_set_current_line(93, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB112:    xsi_set_current_line(95, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB113;
    goto LAB1;

LAB108:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB109;

LAB110:    xsi_set_current_line(92, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB112;

LAB113:    xsi_set_current_line(97, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(98, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB114;
    goto LAB1;

LAB114:    xsi_set_current_line(99, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng24)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB118;

LAB115:    if (t16 != 0)
        goto LAB117;

LAB116:    *((unsigned int *)t4) = 1;

LAB118:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB119;

LAB120:    xsi_set_current_line(100, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB121:    xsi_set_current_line(102, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB122;
    goto LAB1;

LAB117:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB118;

LAB119:    xsi_set_current_line(99, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB121;

LAB122:    xsi_set_current_line(104, ng0);
    t2 = ((char*)((ng15)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(105, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB123;
    goto LAB1;

LAB123:    xsi_set_current_line(106, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng25)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB127;

LAB124:    if (t16 != 0)
        goto LAB126;

LAB125:    *((unsigned int *)t4) = 1;

LAB127:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB128;

LAB129:    xsi_set_current_line(107, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB130:    xsi_set_current_line(108, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB131;
    goto LAB1;

LAB126:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB127;

LAB128:    xsi_set_current_line(106, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB130;

LAB131:    xsi_set_current_line(110, ng0);
    t2 = ((char*)((ng16)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(111, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB132;
    goto LAB1;

LAB132:    xsi_set_current_line(112, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng26)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB136;

LAB133:    if (t16 != 0)
        goto LAB135;

LAB134:    *((unsigned int *)t4) = 1;

LAB136:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB137;

LAB138:    xsi_set_current_line(113, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB139:    xsi_set_current_line(116, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB140;
    goto LAB1;

LAB135:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB136;

LAB137:    xsi_set_current_line(112, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB139;

LAB140:    xsi_set_current_line(118, ng0);
    t2 = ((char*)((ng27)));
    t3 = (t0 + 1448);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(119, ng0);
    t2 = (t0 + 2328);
    xsi_process_wait(t2, 7000LL);
    *((char **)t1) = &&LAB141;
    goto LAB1;

LAB141:    xsi_set_current_line(120, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng28)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB145;

LAB142:    if (t16 != 0)
        goto LAB144;

LAB143:    *((unsigned int *)t4) = 1;

LAB145:    t20 = (t4 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t4);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB146;

LAB147:    xsi_set_current_line(121, ng0);
    t2 = xsi_vlog_time(t32, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng4, 2, t0, (char)118, t32, 64);
    t3 = (t0 + 1448);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    xsi_vlogfile_write(1, 0, 0, ng5, 3, t0, (char)118, t6, 4, (char)118, t20, 5);

LAB148:    xsi_set_current_line(124, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    xsi_vlogfile_write(1, 0, 0, ng29, 2, t0, (char)119, t5, 32);
    xsi_set_current_line(125, ng0);
    xsi_vlogfile_write(1, 0, 0, ng30, 1, t0);
    xsi_set_current_line(126, ng0);
    xsi_vlog_finish(1);
    goto LAB1;

LAB144:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB145;

LAB146:    xsi_set_current_line(120, ng0);
    t26 = (t0 + 1608);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    memset(t30, 0, 8);
    xsi_vlog_signed_add(t30, 32, t28, 32, t29, 32);
    t31 = (t0 + 1608);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 32);
    goto LAB148;

}


extern void work_m_05957009084065584114_2149418644_init()
{
	static char *pe[] = {(void *)Initial_11_0};
	xsi_register_didat("work_m_05957009084065584114_2149418644", "isim/testbench_ROM_isim_beh.exe.sim/work/m_05957009084065584114_2149418644.didat");
	xsi_register_executes(pe);
}
