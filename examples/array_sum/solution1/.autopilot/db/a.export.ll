; ModuleID = '/home/drichmond/examples/array_sum/solution1/.autopilot/db/a.o.2.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@array_sum_str = internal unnamed_addr constant [10 x i8] c"array_sum\00"

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

define i32 @array_sum([64 x i32]* %array_r, i32 %length_r) nounwind uwtable readonly {
  call void (...)* @_ssdm_op_SpecBitsMap([64 x i32]* %array_r) nounwind, !map !0
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %length_r) nounwind, !map !6
  call void (...)* @_ssdm_op_SpecBitsMap(i32 0) nounwind, !map !12
  call void (...)* @_ssdm_op_SpecTopModule([10 x i8]* @array_sum_str) nounwind
  %array_addr = getelementptr [64 x i32]* %array_r, i64 0, i64 0
  %array_load = load i32* %array_addr, align 4
  %array_addr_1 = getelementptr [64 x i32]* %array_r, i64 0, i64 1
  %array_load_1 = load i32* %array_addr_1, align 4
  %array_addr_2 = getelementptr [64 x i32]* %array_r, i64 0, i64 2
  %array_load_2 = load i32* %array_addr_2, align 4
  %array_addr_3 = getelementptr [64 x i32]* %array_r, i64 0, i64 3
  %array_load_3 = load i32* %array_addr_3, align 4
  %array_addr_4 = getelementptr [64 x i32]* %array_r, i64 0, i64 4
  %array_load_4 = load i32* %array_addr_4, align 4
  %array_addr_5 = getelementptr [64 x i32]* %array_r, i64 0, i64 5
  %array_load_5 = load i32* %array_addr_5, align 4
  %array_addr_6 = getelementptr [64 x i32]* %array_r, i64 0, i64 6
  %array_load_6 = load i32* %array_addr_6, align 4
  %array_addr_7 = getelementptr [64 x i32]* %array_r, i64 0, i64 7
  %array_load_7 = load i32* %array_addr_7, align 4
  %array_addr_8 = getelementptr [64 x i32]* %array_r, i64 0, i64 8
  %array_load_8 = load i32* %array_addr_8, align 4
  %array_addr_9 = getelementptr [64 x i32]* %array_r, i64 0, i64 9
  %array_load_9 = load i32* %array_addr_9, align 4
  %array_addr_10 = getelementptr [64 x i32]* %array_r, i64 0, i64 10
  %array_load_10 = load i32* %array_addr_10, align 4
  %array_addr_11 = getelementptr [64 x i32]* %array_r, i64 0, i64 11
  %array_load_11 = load i32* %array_addr_11, align 4
  %array_addr_12 = getelementptr [64 x i32]* %array_r, i64 0, i64 12
  %array_load_12 = load i32* %array_addr_12, align 4
  %array_addr_13 = getelementptr [64 x i32]* %array_r, i64 0, i64 13
  %array_load_13 = load i32* %array_addr_13, align 4
  %array_addr_14 = getelementptr [64 x i32]* %array_r, i64 0, i64 14
  %array_load_14 = load i32* %array_addr_14, align 4
  %array_addr_15 = getelementptr [64 x i32]* %array_r, i64 0, i64 15
  %array_load_15 = load i32* %array_addr_15, align 4
  %array_addr_16 = getelementptr [64 x i32]* %array_r, i64 0, i64 16
  %array_load_16 = load i32* %array_addr_16, align 4
  %array_addr_17 = getelementptr [64 x i32]* %array_r, i64 0, i64 17
  %array_load_17 = load i32* %array_addr_17, align 4
  %array_addr_18 = getelementptr [64 x i32]* %array_r, i64 0, i64 18
  %array_load_18 = load i32* %array_addr_18, align 4
  %array_addr_19 = getelementptr [64 x i32]* %array_r, i64 0, i64 19
  %array_load_19 = load i32* %array_addr_19, align 4
  %array_addr_20 = getelementptr [64 x i32]* %array_r, i64 0, i64 20
  %array_load_20 = load i32* %array_addr_20, align 4
  %array_addr_21 = getelementptr [64 x i32]* %array_r, i64 0, i64 21
  %array_load_21 = load i32* %array_addr_21, align 4
  %array_addr_22 = getelementptr [64 x i32]* %array_r, i64 0, i64 22
  %array_load_22 = load i32* %array_addr_22, align 4
  %array_addr_23 = getelementptr [64 x i32]* %array_r, i64 0, i64 23
  %array_load_23 = load i32* %array_addr_23, align 4
  %array_addr_24 = getelementptr [64 x i32]* %array_r, i64 0, i64 24
  %array_load_24 = load i32* %array_addr_24, align 4
  %array_addr_25 = getelementptr [64 x i32]* %array_r, i64 0, i64 25
  %array_load_25 = load i32* %array_addr_25, align 4
  %array_addr_26 = getelementptr [64 x i32]* %array_r, i64 0, i64 26
  %array_load_26 = load i32* %array_addr_26, align 4
  %array_addr_27 = getelementptr [64 x i32]* %array_r, i64 0, i64 27
  %array_load_27 = load i32* %array_addr_27, align 4
  %array_addr_28 = getelementptr [64 x i32]* %array_r, i64 0, i64 28
  %array_load_28 = load i32* %array_addr_28, align 4
  %array_addr_29 = getelementptr [64 x i32]* %array_r, i64 0, i64 29
  %array_load_29 = load i32* %array_addr_29, align 4
  %array_addr_30 = getelementptr [64 x i32]* %array_r, i64 0, i64 30
  %array_load_30 = load i32* %array_addr_30, align 4
  %array_addr_31 = getelementptr [64 x i32]* %array_r, i64 0, i64 31
  %array_load_31 = load i32* %array_addr_31, align 4
  %array_addr_32 = getelementptr [64 x i32]* %array_r, i64 0, i64 32
  %array_load_32 = load i32* %array_addr_32, align 4
  %array_addr_33 = getelementptr [64 x i32]* %array_r, i64 0, i64 33
  %array_load_33 = load i32* %array_addr_33, align 4
  %array_addr_34 = getelementptr [64 x i32]* %array_r, i64 0, i64 34
  %array_load_34 = load i32* %array_addr_34, align 4
  %array_addr_35 = getelementptr [64 x i32]* %array_r, i64 0, i64 35
  %array_load_35 = load i32* %array_addr_35, align 4
  %array_addr_36 = getelementptr [64 x i32]* %array_r, i64 0, i64 36
  %array_load_36 = load i32* %array_addr_36, align 4
  %array_addr_37 = getelementptr [64 x i32]* %array_r, i64 0, i64 37
  %array_load_37 = load i32* %array_addr_37, align 4
  %array_addr_38 = getelementptr [64 x i32]* %array_r, i64 0, i64 38
  %array_load_38 = load i32* %array_addr_38, align 4
  %array_addr_39 = getelementptr [64 x i32]* %array_r, i64 0, i64 39
  %array_load_39 = load i32* %array_addr_39, align 4
  %array_addr_40 = getelementptr [64 x i32]* %array_r, i64 0, i64 40
  %array_load_40 = load i32* %array_addr_40, align 4
  %array_addr_41 = getelementptr [64 x i32]* %array_r, i64 0, i64 41
  %array_load_41 = load i32* %array_addr_41, align 4
  %array_addr_42 = getelementptr [64 x i32]* %array_r, i64 0, i64 42
  %array_load_42 = load i32* %array_addr_42, align 4
  %array_addr_43 = getelementptr [64 x i32]* %array_r, i64 0, i64 43
  %array_load_43 = load i32* %array_addr_43, align 4
  %array_addr_44 = getelementptr [64 x i32]* %array_r, i64 0, i64 44
  %array_load_44 = load i32* %array_addr_44, align 4
  %array_addr_45 = getelementptr [64 x i32]* %array_r, i64 0, i64 45
  %array_load_45 = load i32* %array_addr_45, align 4
  %array_addr_46 = getelementptr [64 x i32]* %array_r, i64 0, i64 46
  %array_load_46 = load i32* %array_addr_46, align 4
  %array_addr_47 = getelementptr [64 x i32]* %array_r, i64 0, i64 47
  %array_load_47 = load i32* %array_addr_47, align 4
  %array_addr_48 = getelementptr [64 x i32]* %array_r, i64 0, i64 48
  %array_load_48 = load i32* %array_addr_48, align 4
  %array_addr_49 = getelementptr [64 x i32]* %array_r, i64 0, i64 49
  %array_load_49 = load i32* %array_addr_49, align 4
  %array_addr_50 = getelementptr [64 x i32]* %array_r, i64 0, i64 50
  %array_load_50 = load i32* %array_addr_50, align 4
  %array_addr_51 = getelementptr [64 x i32]* %array_r, i64 0, i64 51
  %array_load_51 = load i32* %array_addr_51, align 4
  %array_addr_52 = getelementptr [64 x i32]* %array_r, i64 0, i64 52
  %array_load_52 = load i32* %array_addr_52, align 4
  %array_addr_53 = getelementptr [64 x i32]* %array_r, i64 0, i64 53
  %array_load_53 = load i32* %array_addr_53, align 4
  %array_addr_54 = getelementptr [64 x i32]* %array_r, i64 0, i64 54
  %array_load_54 = load i32* %array_addr_54, align 4
  %array_addr_55 = getelementptr [64 x i32]* %array_r, i64 0, i64 55
  %array_load_55 = load i32* %array_addr_55, align 4
  %array_addr_56 = getelementptr [64 x i32]* %array_r, i64 0, i64 56
  %array_load_56 = load i32* %array_addr_56, align 4
  %array_addr_57 = getelementptr [64 x i32]* %array_r, i64 0, i64 57
  %array_load_57 = load i32* %array_addr_57, align 4
  %array_addr_58 = getelementptr [64 x i32]* %array_r, i64 0, i64 58
  %array_load_58 = load i32* %array_addr_58, align 4
  %array_addr_59 = getelementptr [64 x i32]* %array_r, i64 0, i64 59
  %array_load_59 = load i32* %array_addr_59, align 4
  %array_addr_60 = getelementptr [64 x i32]* %array_r, i64 0, i64 60
  %array_load_60 = load i32* %array_addr_60, align 4
  %array_addr_61 = getelementptr [64 x i32]* %array_r, i64 0, i64 61
  %array_load_61 = load i32* %array_addr_61, align 4
  %array_addr_62 = getelementptr [64 x i32]* %array_r, i64 0, i64 62
  %array_load_62 = load i32* %array_addr_62, align 4
  %array_addr_63 = getelementptr [64 x i32]* %array_r, i64 0, i64 63
  %array_load_63 = load i32* %array_addr_63, align 4
  %tmp4 = add i32 %array_load, %array_load_1
  %tmp5 = add i32 %array_load_2, %array_load_3
  %tmp3 = add i32 %tmp5, %tmp4
  %tmp7 = add i32 %array_load_4, %array_load_5
  %tmp8 = add i32 %array_load_6, %array_load_7
  %tmp6 = add i32 %tmp8, %tmp7
  %tmp2 = add i32 %tmp6, %tmp3
  %tmp11 = add i32 %array_load_8, %array_load_9
  %tmp12 = add i32 %array_load_10, %array_load_11
  %tmp10 = add i32 %tmp12, %tmp11
  %tmp14 = add i32 %array_load_12, %array_load_13
  %tmp15 = add i32 %array_load_14, %array_load_15
  %tmp13 = add i32 %tmp15, %tmp14
  %tmp9 = add i32 %tmp13, %tmp10
  %tmp1 = add i32 %tmp9, %tmp2
  %tmp19 = add i32 %array_load_16, %array_load_17
  %tmp20 = add i32 %array_load_18, %array_load_19
  %tmp18 = add i32 %tmp20, %tmp19
  %tmp22 = add i32 %array_load_20, %array_load_21
  %tmp23 = add i32 %array_load_22, %array_load_23
  %tmp21 = add i32 %tmp23, %tmp22
  %tmp17 = add i32 %tmp21, %tmp18
  %tmp26 = add i32 %array_load_24, %array_load_25
  %tmp27 = add i32 %array_load_26, %array_load_27
  %tmp25 = add i32 %tmp27, %tmp26
  %tmp29 = add i32 %array_load_28, %array_load_29
  %tmp30 = add i32 %array_load_30, %array_load_31
  %tmp28 = add i32 %tmp30, %tmp29
  %tmp24 = add i32 %tmp28, %tmp25
  %tmp16 = add i32 %tmp24, %tmp17
  %tmp = add i32 %tmp16, %tmp1
  %tmp35 = add i32 %array_load_32, %array_load_33
  %tmp36 = add i32 %array_load_34, %array_load_35
  %tmp34 = add i32 %tmp36, %tmp35
  %tmp38 = add i32 %array_load_36, %array_load_37
  %tmp39 = add i32 %array_load_38, %array_load_39
  %tmp37 = add i32 %tmp39, %tmp38
  %tmp33 = add i32 %tmp37, %tmp34
  %tmp42 = add i32 %array_load_40, %array_load_41
  %tmp43 = add i32 %array_load_42, %array_load_43
  %tmp41 = add i32 %tmp43, %tmp42
  %tmp45 = add i32 %array_load_44, %array_load_45
  %tmp46 = add i32 %array_load_46, %array_load_47
  %tmp44 = add i32 %tmp46, %tmp45
  %tmp40 = add i32 %tmp44, %tmp41
  %tmp32 = add i32 %tmp40, %tmp33
  %tmp50 = add i32 %array_load_48, %array_load_49
  %tmp51 = add i32 %array_load_50, %array_load_51
  %tmp49 = add i32 %tmp51, %tmp50
  %tmp53 = add i32 %array_load_52, %array_load_53
  %tmp54 = add i32 %array_load_54, %array_load_55
  %tmp52 = add i32 %tmp54, %tmp53
  %tmp48 = add i32 %tmp52, %tmp49
  %tmp57 = add i32 %array_load_56, %array_load_57
  %tmp58 = add i32 %array_load_58, %array_load_59
  %tmp56 = add i32 %tmp58, %tmp57
  %tmp60 = add i32 %array_load_60, %array_load_61
  %tmp61 = add i32 %array_load_62, %array_load_63
  %tmp59 = add i32 %tmp61, %tmp60
  %tmp55 = add i32 %tmp59, %tmp56
  %tmp47 = add i32 %tmp55, %tmp48
  %tmp31 = add i32 %tmp47, %tmp32
  %sum_1_s = add nsw i32 %tmp31, %tmp
  ret i32 %sum_1_s
}

define weak void @_ssdm_op_SpecTopModule(...) {
entry:
  ret void
}

define weak void @_ssdm_op_SpecBitsMap(...) {
entry:
  ret void
}

declare i16 @_ssdm_op_HSub(...)

declare i16 @_ssdm_op_HMul(...)

declare i16 @_ssdm_op_HDiv(...)

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
