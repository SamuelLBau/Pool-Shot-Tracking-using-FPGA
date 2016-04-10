############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project array_sum
set_top array_sum
add_files array_sum.c
add_files -tb array_sum_test.c
open_solution "solution1"
set_part {xc7vx690tffg1761-2}
create_clock -period 10 -name default
#source "./array_sum/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
