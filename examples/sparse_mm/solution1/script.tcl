############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project sparse_mm
set_top sparse_mm
add_files sparse_mm.cpp
add_files -tb sparse_mm_test.cpp -cflags "-std=c++0x"
open_solution "solution1"
set_part {xc7vx690tffg1761-2}
create_clock -period 10 -name default
#source "./sparse_mm/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
