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

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_01463305009518618666_3236520523_init();
    work_m_14001251666954120604_1584025541_init();
    work_m_06567788513243345831_0513714970_init();
    work_m_11491833963429943931_2073120511_init();


    xsi_register_tops("work_m_06567788513243345831_0513714970");
    xsi_register_tops("work_m_11491833963429943931_2073120511");


    return xsi_run_simulation(argc, argv);

}
