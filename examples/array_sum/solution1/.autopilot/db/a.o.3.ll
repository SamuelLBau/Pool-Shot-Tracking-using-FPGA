; ModuleID = '/home/drichmond/examples/array_sum/solution1/.autopilot/db/a.o.3.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@array_sum_str = internal unnamed_addr constant [10 x i8] c"array_sum\00" ; [#uses=1 type=[10 x i8]*]

; [#uses=2]
declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

; [#uses=0]
define i32 @array_sum([64 x i32]* %array, i32 %length) nounwind uwtable readonly {
  call void (...)* @_ssdm_op_SpecBitsMap([64 x i32]* %array) nounwind, !map !0
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %length) nounwind, !map !6
  call void (...)* @_ssdm_op_SpecBitsMap(i32 0) nounwind, !map !12
  call void (...)* @_ssdm_op_SpecTopModule([10 x i8]* @array_sum_str) nounwind
  call void @llvm.dbg.value(metadata !{[64 x i32]* %array}, i64 0, metadata !18), !dbg !31 ; [debug line = 1:19] [debug variable = array]
  call void @llvm.dbg.value(metadata !{i32 %length}, i64 0, metadata !32), !dbg !33 ; [debug line = 1:43] [debug variable = length]
  %array_addr = getelementptr [64 x i32]* %array, i64 0, i64 0, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load = load i32* %array_addr, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_1 = getelementptr [64 x i32]* %array, i64 0, i64 1, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_1 = load i32* %array_addr_1, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_2 = getelementptr [64 x i32]* %array, i64 0, i64 2, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_2 = load i32* %array_addr_2, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_3 = getelementptr [64 x i32]* %array, i64 0, i64 3, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_3 = load i32* %array_addr_3, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_4 = getelementptr [64 x i32]* %array, i64 0, i64 4, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_4 = load i32* %array_addr_4, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_5 = getelementptr [64 x i32]* %array, i64 0, i64 5, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_5 = load i32* %array_addr_5, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_6 = getelementptr [64 x i32]* %array, i64 0, i64 6, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_6 = load i32* %array_addr_6, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_7 = getelementptr [64 x i32]* %array, i64 0, i64 7, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_7 = load i32* %array_addr_7, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_8 = getelementptr [64 x i32]* %array, i64 0, i64 8, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_8 = load i32* %array_addr_8, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_9 = getelementptr [64 x i32]* %array, i64 0, i64 9, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_9 = load i32* %array_addr_9, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_10 = getelementptr [64 x i32]* %array, i64 0, i64 10, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_10 = load i32* %array_addr_10, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_11 = getelementptr [64 x i32]* %array, i64 0, i64 11, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_11 = load i32* %array_addr_11, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_12 = getelementptr [64 x i32]* %array, i64 0, i64 12, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_12 = load i32* %array_addr_12, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_13 = getelementptr [64 x i32]* %array, i64 0, i64 13, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_13 = load i32* %array_addr_13, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_14 = getelementptr [64 x i32]* %array, i64 0, i64 14, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_14 = load i32* %array_addr_14, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_15 = getelementptr [64 x i32]* %array, i64 0, i64 15, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_15 = load i32* %array_addr_15, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_16 = getelementptr [64 x i32]* %array, i64 0, i64 16, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_16 = load i32* %array_addr_16, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_17 = getelementptr [64 x i32]* %array, i64 0, i64 17, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_17 = load i32* %array_addr_17, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_18 = getelementptr [64 x i32]* %array, i64 0, i64 18, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_18 = load i32* %array_addr_18, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_19 = getelementptr [64 x i32]* %array, i64 0, i64 19, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_19 = load i32* %array_addr_19, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_20 = getelementptr [64 x i32]* %array, i64 0, i64 20, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_20 = load i32* %array_addr_20, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_21 = getelementptr [64 x i32]* %array, i64 0, i64 21, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_21 = load i32* %array_addr_21, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_22 = getelementptr [64 x i32]* %array, i64 0, i64 22, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_22 = load i32* %array_addr_22, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_23 = getelementptr [64 x i32]* %array, i64 0, i64 23, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_23 = load i32* %array_addr_23, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_24 = getelementptr [64 x i32]* %array, i64 0, i64 24, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_24 = load i32* %array_addr_24, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_25 = getelementptr [64 x i32]* %array, i64 0, i64 25, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_25 = load i32* %array_addr_25, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_26 = getelementptr [64 x i32]* %array, i64 0, i64 26, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_26 = load i32* %array_addr_26, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_27 = getelementptr [64 x i32]* %array, i64 0, i64 27, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_27 = load i32* %array_addr_27, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_28 = getelementptr [64 x i32]* %array, i64 0, i64 28, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_28 = load i32* %array_addr_28, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_29 = getelementptr [64 x i32]* %array, i64 0, i64 29, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_29 = load i32* %array_addr_29, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_30 = getelementptr [64 x i32]* %array, i64 0, i64 30, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_30 = load i32* %array_addr_30, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_31 = getelementptr [64 x i32]* %array, i64 0, i64 31, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_31 = load i32* %array_addr_31, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_32 = getelementptr [64 x i32]* %array, i64 0, i64 32, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_32 = load i32* %array_addr_32, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_33 = getelementptr [64 x i32]* %array, i64 0, i64 33, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_33 = load i32* %array_addr_33, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_34 = getelementptr [64 x i32]* %array, i64 0, i64 34, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_34 = load i32* %array_addr_34, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_35 = getelementptr [64 x i32]* %array, i64 0, i64 35, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_35 = load i32* %array_addr_35, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_36 = getelementptr [64 x i32]* %array, i64 0, i64 36, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_36 = load i32* %array_addr_36, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_37 = getelementptr [64 x i32]* %array, i64 0, i64 37, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_37 = load i32* %array_addr_37, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_38 = getelementptr [64 x i32]* %array, i64 0, i64 38, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_38 = load i32* %array_addr_38, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_39 = getelementptr [64 x i32]* %array, i64 0, i64 39, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_39 = load i32* %array_addr_39, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_40 = getelementptr [64 x i32]* %array, i64 0, i64 40, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_40 = load i32* %array_addr_40, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_41 = getelementptr [64 x i32]* %array, i64 0, i64 41, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_41 = load i32* %array_addr_41, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_42 = getelementptr [64 x i32]* %array, i64 0, i64 42, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_42 = load i32* %array_addr_42, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_43 = getelementptr [64 x i32]* %array, i64 0, i64 43, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_43 = load i32* %array_addr_43, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_44 = getelementptr [64 x i32]* %array, i64 0, i64 44, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_44 = load i32* %array_addr_44, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_45 = getelementptr [64 x i32]* %array, i64 0, i64 45, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_45 = load i32* %array_addr_45, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_46 = getelementptr [64 x i32]* %array, i64 0, i64 46, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_46 = load i32* %array_addr_46, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_47 = getelementptr [64 x i32]* %array, i64 0, i64 47, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_47 = load i32* %array_addr_47, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_48 = getelementptr [64 x i32]* %array, i64 0, i64 48, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_48 = load i32* %array_addr_48, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_49 = getelementptr [64 x i32]* %array, i64 0, i64 49, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_49 = load i32* %array_addr_49, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_50 = getelementptr [64 x i32]* %array, i64 0, i64 50, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_50 = load i32* %array_addr_50, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_51 = getelementptr [64 x i32]* %array, i64 0, i64 51, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_51 = load i32* %array_addr_51, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_52 = getelementptr [64 x i32]* %array, i64 0, i64 52, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_52 = load i32* %array_addr_52, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_53 = getelementptr [64 x i32]* %array, i64 0, i64 53, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_53 = load i32* %array_addr_53, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_54 = getelementptr [64 x i32]* %array, i64 0, i64 54, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_54 = load i32* %array_addr_54, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_55 = getelementptr [64 x i32]* %array, i64 0, i64 55, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_55 = load i32* %array_addr_55, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_56 = getelementptr [64 x i32]* %array, i64 0, i64 56, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_56 = load i32* %array_addr_56, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_57 = getelementptr [64 x i32]* %array, i64 0, i64 57, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_57 = load i32* %array_addr_57, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_58 = getelementptr [64 x i32]* %array, i64 0, i64 58, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_58 = load i32* %array_addr_58, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_59 = getelementptr [64 x i32]* %array, i64 0, i64 59, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_59 = load i32* %array_addr_59, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_60 = getelementptr [64 x i32]* %array, i64 0, i64 60, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_60 = load i32* %array_addr_60, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_61 = getelementptr [64 x i32]* %array, i64 0, i64 61, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_61 = load i32* %array_addr_61, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_62 = getelementptr [64 x i32]* %array, i64 0, i64 62, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_62 = load i32* %array_addr_62, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %array_addr_63 = getelementptr [64 x i32]* %array, i64 0, i64 63, !dbg !34 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array_load_63 = load i32* %array_addr_63, align 4, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp4 = add i32 %array_load, %array_load_1, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp5 = add i32 %array_load_2, %array_load_3, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp3 = add i32 %tmp5, %tmp4, !dbg !34          ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp7 = add i32 %array_load_4, %array_load_5, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp8 = add i32 %array_load_6, %array_load_7, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp6 = add i32 %tmp8, %tmp7, !dbg !34          ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp2 = add i32 %tmp6, %tmp3, !dbg !34          ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp11 = add i32 %array_load_8, %array_load_9, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp12 = add i32 %array_load_10, %array_load_11, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp10 = add i32 %tmp12, %tmp11, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp14 = add i32 %array_load_12, %array_load_13, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp15 = add i32 %array_load_14, %array_load_15, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp13 = add i32 %tmp15, %tmp14, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp9 = add i32 %tmp13, %tmp10, !dbg !34        ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp1 = add i32 %tmp9, %tmp2, !dbg !34          ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp19 = add i32 %array_load_16, %array_load_17, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp20 = add i32 %array_load_18, %array_load_19, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp18 = add i32 %tmp20, %tmp19, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp22 = add i32 %array_load_20, %array_load_21, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp23 = add i32 %array_load_22, %array_load_23, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp21 = add i32 %tmp23, %tmp22, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp17 = add i32 %tmp21, %tmp18, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp26 = add i32 %array_load_24, %array_load_25, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp27 = add i32 %array_load_26, %array_load_27, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp25 = add i32 %tmp27, %tmp26, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp29 = add i32 %array_load_28, %array_load_29, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp30 = add i32 %array_load_30, %array_load_31, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp28 = add i32 %tmp30, %tmp29, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp24 = add i32 %tmp28, %tmp25, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp16 = add i32 %tmp24, %tmp17, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp = add i32 %tmp16, %tmp1, !dbg !34          ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp35 = add i32 %array_load_32, %array_load_33, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp36 = add i32 %array_load_34, %array_load_35, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp34 = add i32 %tmp36, %tmp35, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp38 = add i32 %array_load_36, %array_load_37, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp39 = add i32 %array_load_38, %array_load_39, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp37 = add i32 %tmp39, %tmp38, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp33 = add i32 %tmp37, %tmp34, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp42 = add i32 %array_load_40, %array_load_41, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp43 = add i32 %array_load_42, %array_load_43, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp41 = add i32 %tmp43, %tmp42, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp45 = add i32 %array_load_44, %array_load_45, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp46 = add i32 %array_load_46, %array_load_47, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp44 = add i32 %tmp46, %tmp45, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp40 = add i32 %tmp44, %tmp41, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp32 = add i32 %tmp40, %tmp33, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp50 = add i32 %array_load_48, %array_load_49, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp51 = add i32 %array_load_50, %array_load_51, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp49 = add i32 %tmp51, %tmp50, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp53 = add i32 %array_load_52, %array_load_53, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp54 = add i32 %array_load_54, %array_load_55, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp52 = add i32 %tmp54, %tmp53, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp48 = add i32 %tmp52, %tmp49, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp57 = add i32 %array_load_56, %array_load_57, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp58 = add i32 %array_load_58, %array_load_59, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp56 = add i32 %tmp58, %tmp57, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp60 = add i32 %array_load_60, %array_load_61, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp61 = add i32 %array_load_62, %array_load_63, !dbg !34 ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp59 = add i32 %tmp61, %tmp60, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp55 = add i32 %tmp59, %tmp56, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp47 = add i32 %tmp55, %tmp48, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %tmp31 = add i32 %tmp47, %tmp32, !dbg !34       ; [#uses=1 type=i32] [debug line = 6:2]
  %sum_1_s = add nsw i32 %tmp31, %tmp, !dbg !34   ; [#uses=1 type=i32] [debug line = 6:2]
  ret i32 %sum_1_s, !dbg !38                      ; [debug line = 8:2]
}

; [#uses=1]
define weak void @_ssdm_op_SpecTopModule(...) {
entry:
  ret void
}

; [#uses=3]
define weak void @_ssdm_op_SpecBitsMap(...) {
entry:
  ret void
}

; [#uses=0]
declare i16 @_ssdm_op_HSub(...)

; [#uses=0]
declare i16 @_ssdm_op_HMul(...)

; [#uses=0]
declare i16 @_ssdm_op_HDiv(...)

; [#uses=0]
declare i16 @_ssdm_op_HAdd(...)

!hls.encrypted.func = !{}
!llvm.map.gv = !{}

!0 = metadata !{metadata !1}
!1 = metadata !{i32 0, i32 31, metadata !2}
!2 = metadata !{metadata !3}
!3 = metadata !{metadata !"array", metadata !4, metadata !"int", i32 0, i32 31}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 0, i32 63, i32 1}
!6 = metadata !{metadata !7}
!7 = metadata !{i32 0, i32 31, metadata !8}
!8 = metadata !{metadata !9}
!9 = metadata !{metadata !"length", metadata !10, metadata !"unsigned int", i32 0, i32 31}
!10 = metadata !{metadata !11}
!11 = metadata !{i32 0, i32 0, i32 0}
!12 = metadata !{metadata !13}
!13 = metadata !{i32 0, i32 31, metadata !14}
!14 = metadata !{metadata !15}
!15 = metadata !{metadata !"return", metadata !16, metadata !"int", i32 0, i32 31}
!16 = metadata !{metadata !17}
!17 = metadata !{i32 0, i32 1, i32 0}
!18 = metadata !{i32 786689, metadata !19, metadata !"array", null, i32 1, metadata !28, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!19 = metadata !{i32 786478, i32 0, metadata !20, metadata !"array_sum", metadata !"array_sum", metadata !"", metadata !20, i32 1, metadata !21, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, null, metadata !26, i32 2} ; [ DW_TAG_subprogram ]
!20 = metadata !{i32 786473, metadata !"array_sum.c", metadata !"/home/drichmond/examples", null} ; [ DW_TAG_file_type ]
!21 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !22, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!22 = metadata !{metadata !23, metadata !24, metadata !25}
!23 = metadata !{i32 786468, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!24 = metadata !{i32 786447, null, metadata !"", null, i32 0, i64 64, i64 64, i64 0, i32 0, metadata !23} ; [ DW_TAG_pointer_type ]
!25 = metadata !{i32 786468, null, metadata !"unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!26 = metadata !{metadata !27}
!27 = metadata !{i32 786468}                      ; [ DW_TAG_base_type ]
!28 = metadata !{i32 786433, null, metadata !"", null, i32 0, i64 2048, i64 32, i32 0, i32 0, metadata !23, metadata !29, i32 0, i32 0} ; [ DW_TAG_array_type ]
!29 = metadata !{metadata !30}
!30 = metadata !{i32 786465, i64 0, i64 63}       ; [ DW_TAG_subrange_type ]
!31 = metadata !{i32 1, i32 19, metadata !19, null}
!32 = metadata !{i32 786689, metadata !19, metadata !"length", metadata !20, i32 33554433, metadata !25, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!33 = metadata !{i32 1, i32 43, metadata !19, null}
!34 = metadata !{i32 6, i32 2, metadata !35, null}
!35 = metadata !{i32 786443, metadata !36, i32 4, i32 29, metadata !20, i32 2} ; [ DW_TAG_lexical_block ]
!36 = metadata !{i32 786443, metadata !37, i32 4, i32 2, metadata !20, i32 1} ; [ DW_TAG_lexical_block ]
!37 = metadata !{i32 786443, metadata !19, i32 2, i32 1, metadata !20, i32 0} ; [ DW_TAG_lexical_block ]
!38 = metadata !{i32 8, i32 2, metadata !37, null}
