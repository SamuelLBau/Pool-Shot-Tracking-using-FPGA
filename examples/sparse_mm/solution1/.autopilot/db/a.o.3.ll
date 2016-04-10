; ModuleID = '/home/drichmond/examples/sparse_mm/solution1/.autopilot/db/a.o.3.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@sparse_mm_str = internal unnamed_addr constant [10 x i8] c"sparse_mm\00" ; [#uses=1 type=[10 x i8]*]

; [#uses=0]
define void @sparse_mm([4194304 x i64]* %a, i32 %a_y, i32 %a_x, [2048 x i32]* %b, i32 %b_y, i32 %b_x, [2048 x i32]* %c) {
  call void (...)* @_ssdm_op_SpecBitsMap([4194304 x i64]* %a), !map !0
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %a_y), !map !6
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %a_x), !map !12
  call void (...)* @_ssdm_op_SpecBitsMap([2048 x i32]* %b), !map !16
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %b_y), !map !22
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %b_x), !map !26
  call void (...)* @_ssdm_op_SpecBitsMap([2048 x i32]* %c), !map !30
  call void (...)* @_ssdm_op_SpecTopModule([10 x i8]* @sparse_mm_str) nounwind
  %b_x_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %b_x) ; [#uses=3 type=i32]
  call void @llvm.dbg.value(metadata !{i32 %b_x_read}, i64 0, metadata !34), !dbg !59 ; [debug line = 2:100] [debug variable = b_x]
  %a_y_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %a_y) ; [#uses=1 type=i32]
  call void @llvm.dbg.value(metadata !{i32 %a_y_read}, i64 0, metadata !60), !dbg !61 ; [debug line = 2:49] [debug variable = a_y]
  call void @llvm.dbg.value(metadata !{[4194304 x i64]* %a}, i64 0, metadata !62), !dbg !67 ; [debug line = 2:22] [debug variable = a]
  call void @llvm.dbg.value(metadata !{i32 %a_y}, i64 0, metadata !60), !dbg !61 ; [debug line = 2:49] [debug variable = a_y]
  call void @llvm.dbg.value(metadata !{i32 %a_x}, i64 0, metadata !68), !dbg !69 ; [debug line = 2:67] [debug variable = a_x]
  call void @llvm.dbg.value(metadata !{[2048 x i32]* %b}, i64 0, metadata !70), !dbg !74 ; [debug line = 2:76] [debug variable = b]
  call void @llvm.dbg.value(metadata !{i32 %b_y}, i64 0, metadata !75), !dbg !76 ; [debug line = 2:91] [debug variable = b_y]
  call void @llvm.dbg.value(metadata !{i32 %b_x}, i64 0, metadata !34), !dbg !59 ; [debug line = 2:100] [debug variable = b_x]
  call void @llvm.dbg.value(metadata !{[2048 x i32]* %c}, i64 0, metadata !77), !dbg !78 ; [debug line = 2:109] [debug variable = c]
  call void @llvm.dbg.value(metadata !{[4194304 x i64]* %a}, i64 0, metadata !79), !dbg !82 ; [debug line = 3:55] [debug variable = a_csr]
  br label %.loopexit, !dbg !83                   ; [debug line = 4:17]

.loopexit:                                        ; preds = %.preheader, %0
  %ibx = phi i31 [ 0, %0 ], [ %ibx_1, %.preheader ] ; [#uses=2 type=i31]
  %ibx_cast = zext i31 %ibx to i32, !dbg !83      ; [#uses=3 type=i32] [debug line = 4:17]
  %tmp = icmp slt i32 %ibx_cast, %b_x_read, !dbg !83 ; [#uses=1 type=i1] [debug line = 4:17]
  %ibx_1 = add i31 %ibx, 1, !dbg !85              ; [#uses=1 type=i31] [debug line = 4:31]
  call void @llvm.dbg.value(metadata !{i31 %ibx_1}, i64 0, metadata !86), !dbg !85 ; [debug line = 4:31] [debug variable = ibx]
  br i1 %tmp, label %.preheader, label %4, !dbg !83 ; [debug line = 4:17]

.preheader:                                       ; preds = %3, %2, %.loopexit
  %a_i = phi i32 [ 0, %.loopexit ], [ %a_i_1, %3 ], [ %a_i_1, %2 ] ; [#uses=2 type=i32]
  %iay = phi i32 [ 0, %.loopexit ], [ %iay_1, %2 ], [ %iay, %3 ] ; [#uses=4 type=i32]
  %sum = phi i32 [ 0, %.loopexit ], [ 0, %2 ], [ %sum_1, %3 ] ; [#uses=2 type=i32]
  %tmp_1 = icmp ult i32 %iay, %a_y_read, !dbg !87 ; [#uses=1 type=i1] [debug line = 5:36]
  %a_i_1 = add nsw i32 %a_i, 1, !dbg !90          ; [#uses=2 type=i32] [debug line = 5:49]
  call void @llvm.dbg.value(metadata !{i32 %a_i_1}, i64 0, metadata !91), !dbg !90 ; [debug line = 5:49] [debug variable = a_i]
  br i1 %tmp_1, label %1, label %.loopexit, !dbg !87 ; [debug line = 5:36]

; <label>:1                                       ; preds = %.preheader
  %tmp_2 = sext i32 %a_i to i64, !dbg !92         ; [#uses=1 type=i64] [debug line = 6:33]
  %a_addr = getelementptr [4194304 x i64]* %a, i64 0, i64 %tmp_2, !dbg !92 ; [#uses=1 type=i64*] [debug line = 6:33]
  %a_load = load i64* %a_addr, align 8, !dbg !92  ; [#uses=3 type=i64] [debug line = 6:33]
  %tmp_6 = trunc i64 %a_load to i1, !dbg !92      ; [#uses=1 type=i1] [debug line = 6:33]
  %column = call i31 @_ssdm_op_PartSelect.i31.i64.i32.i32(i64 %a_load, i32 1, i32 31), !dbg !94 ; [#uses=1 type=i31] [debug line = 7:56]
  %column_cast = zext i31 %column to i32, !dbg !94 ; [#uses=1 type=i32] [debug line = 7:56]
  call void @llvm.dbg.value(metadata !{i31 %column}, i64 0, metadata !95), !dbg !94 ; [debug line = 7:56] [debug variable = column]
  %value = call i32 @_ssdm_op_PartSelect.i32.i64.i32.i32(i64 %a_load, i32 32, i32 63), !dbg !96 ; [#uses=1 type=i32] [debug line = 8:32]
  call void @llvm.dbg.value(metadata !{i32 %value}, i64 0, metadata !97), !dbg !96 ; [debug line = 8:32] [debug variable = value]
  br i1 %tmp_6, label %2, label %3, !dbg !98      ; [debug line = 9:4]

; <label>:2                                       ; preds = %1
  %iay_1 = add nsw i32 %iay, 1, !dbg !99          ; [#uses=1 type=i32] [debug line = 10:5]
  call void @llvm.dbg.value(metadata !{i32 %iay_1}, i64 0, metadata !101), !dbg !99 ; [debug line = 10:5] [debug variable = iay]
  %tmp_3 = mul nsw i32 %iay, %b_x_read, !dbg !99  ; [#uses=1 type=i32] [debug line = 10:5]
  %tmp_5 = add nsw i32 %tmp_3, %ibx_cast, !dbg !99 ; [#uses=1 type=i32] [debug line = 10:5]
  %tmp_4 = sext i32 %tmp_5 to i64, !dbg !99       ; [#uses=1 type=i64] [debug line = 10:5]
  %c_addr = getelementptr [2048 x i32]* %c, i64 0, i64 %tmp_4, !dbg !99 ; [#uses=1 type=i32*] [debug line = 10:5]
  store i32 %sum, i32* %c_addr, align 4, !dbg !99 ; [debug line = 10:5]
  br label %.preheader, !dbg !102                 ; [debug line = 12:4]

; <label>:3                                       ; preds = %1
  %tmp_8 = mul i32 %column_cast, %b_x_read, !dbg !103 ; [#uses=1 type=i32] [debug line = 13:5]
  %tmp_9 = add i32 %tmp_8, %ibx_cast, !dbg !103   ; [#uses=1 type=i32] [debug line = 13:5]
  %tmp_s = zext i32 %tmp_9 to i64, !dbg !103      ; [#uses=1 type=i64] [debug line = 13:5]
  %b_addr = getelementptr [2048 x i32]* %b, i64 0, i64 %tmp_s, !dbg !103 ; [#uses=1 type=i32*] [debug line = 13:5]
  %b_load = load i32* %b_addr, align 4, !dbg !103 ; [#uses=1 type=i32] [debug line = 13:5]
  %tmp_7 = mul nsw i32 %b_load, %value, !dbg !103 ; [#uses=1 type=i32] [debug line = 13:5]
  %sum_1 = add nsw i32 %tmp_7, %sum, !dbg !103    ; [#uses=1 type=i32] [debug line = 13:5]
  call void @llvm.dbg.value(metadata !{i32 %sum_1}, i64 0, metadata !105), !dbg !103 ; [debug line = 13:5] [debug variable = sum]
  br label %.preheader

; <label>:4                                       ; preds = %.loopexit
  ret void, !dbg !106                             ; [debug line = 17:1]
}

; [#uses=2]
declare i64 @llvm.part.select.i64(i64, i32, i32) nounwind readnone

; [#uses=16]
declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

; [#uses=1]
define weak void @_ssdm_op_SpecTopModule(...) {
entry:
  ret void
}

; [#uses=7]
define weak void @_ssdm_op_SpecBitsMap(...) {
entry:
  ret void
}

; [#uses=2]
define weak i32 @_ssdm_op_Read.ap_auto.i32(i32) {
entry:
  ret i32 %0
}

; [#uses=1]
define weak i32 @_ssdm_op_PartSelect.i32.i64.i32.i32(i64, i32, i32) nounwind readnone {
entry:
  %empty = call i64 @llvm.part.select.i64(i64 %0, i32 %1, i32 %2) ; [#uses=1 type=i64]
  %empty_4 = trunc i64 %empty to i32              ; [#uses=1 type=i32]
  ret i32 %empty_4
}

; [#uses=1]
define weak i31 @_ssdm_op_PartSelect.i31.i64.i32.i32(i64, i32, i32) nounwind readnone {
entry:
  %empty = call i64 @llvm.part.select.i64(i64 %0, i32 %1, i32 %2) ; [#uses=1 type=i64]
  %empty_5 = trunc i64 %empty to i31              ; [#uses=1 type=i31]
  ret i31 %empty_5
}

; [#uses=0]
declare i1 @_ssdm_op_PartSelect.i1.i64.i32.i32(i64, i32, i32) nounwind readnone

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
!1 = metadata !{i32 0, i32 63, metadata !2}
!2 = metadata !{metadata !3}
!3 = metadata !{metadata !"a", metadata !4, metadata !"void", i32 0, i32 63}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 0, i32 4194303, i32 1}
!6 = metadata !{metadata !7}
!7 = metadata !{i32 0, i32 31, metadata !8}
!8 = metadata !{metadata !9}
!9 = metadata !{metadata !"a_y", metadata !10, metadata !"unsigned int", i32 0, i32 31}
!10 = metadata !{metadata !11}
!11 = metadata !{i32 0, i32 0, i32 0}
!12 = metadata !{metadata !13}
!13 = metadata !{i32 0, i32 31, metadata !14}
!14 = metadata !{metadata !15}
!15 = metadata !{metadata !"a_x", metadata !10, metadata !"unsigned int", i32 0, i32 31}
!16 = metadata !{metadata !17}
!17 = metadata !{i32 0, i32 31, metadata !18}
!18 = metadata !{metadata !19}
!19 = metadata !{metadata !"b", metadata !20, metadata !"int", i32 0, i32 31}
!20 = metadata !{metadata !21}
!21 = metadata !{i32 0, i32 2047, i32 1}
!22 = metadata !{metadata !23}
!23 = metadata !{i32 0, i32 31, metadata !24}
!24 = metadata !{metadata !25}
!25 = metadata !{metadata !"b_y", metadata !10, metadata !"int", i32 0, i32 31}
!26 = metadata !{metadata !27}
!27 = metadata !{i32 0, i32 31, metadata !28}
!28 = metadata !{metadata !29}
!29 = metadata !{metadata !"b_x", metadata !10, metadata !"int", i32 0, i32 31}
!30 = metadata !{metadata !31}
!31 = metadata !{i32 0, i32 31, metadata !32}
!32 = metadata !{metadata !33}
!33 = metadata !{metadata !"c", metadata !20, metadata !"int", i32 0, i32 31}
!34 = metadata !{i32 786689, metadata !35, metadata !"b_x", metadata !36, i32 100663298, metadata !53, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!35 = metadata !{i32 786478, i32 0, metadata !36, metadata !"sparse_mm", metadata !"sparse_mm", metadata !"_Z9sparse_mmP3csrjjPiiiS1_", metadata !36, i32 2, metadata !37, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, null, metadata !57, i32 2} ; [ DW_TAG_subprogram ]
!36 = metadata !{i32 786473, metadata !"sparse_mm.cpp", metadata !"/home/drichmond/examples", null} ; [ DW_TAG_file_type ]
!37 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !38, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!38 = metadata !{null, metadata !39, metadata !51, metadata !51, metadata !56, metadata !53, metadata !53, metadata !56}
!39 = metadata !{i32 786447, null, metadata !"", null, i32 0, i64 64, i64 64, i64 0, i32 0, metadata !40} ; [ DW_TAG_pointer_type ]
!40 = metadata !{i32 786454, null, metadata !"csr_t", metadata !36, i32 23, i64 0, i64 0, i64 0, i32 0, metadata !41} ; [ DW_TAG_typedef ]
!41 = metadata !{i32 786455, null, metadata !"csr", metadata !42, i32 19, i64 64, i64 64, i64 0, i32 0, null, metadata !43, i32 0, null} ; [ DW_TAG_union_type ]
!42 = metadata !{i32 786473, metadata !"./sparse_mm.h", metadata !"/home/drichmond/examples", null} ; [ DW_TAG_file_type ]
!43 = metadata !{metadata !44, metadata !54}
!44 = metadata !{i32 786445, metadata !41, metadata !"csr_s", metadata !42, i32 21, i64 64, i64 32, i64 0, i32 0, metadata !45} ; [ DW_TAG_member ]
!45 = metadata !{i32 786454, null, metadata !"csr_s_t", metadata !42, i32 17, i64 0, i64 0, i64 0, i32 0, metadata !46} ; [ DW_TAG_typedef ]
!46 = metadata !{i32 786434, null, metadata !"csr_s_t", metadata !42, i32 13, i64 64, i64 32, i32 0, i32 0, null, metadata !47, i32 0, null, null} ; [ DW_TAG_class_type ]
!47 = metadata !{metadata !48, metadata !50, metadata !52}
!48 = metadata !{i32 786445, metadata !46, metadata !"end_row", metadata !42, i32 14, i64 1, i64 8, i64 0, i32 0, metadata !49} ; [ DW_TAG_member ]
!49 = metadata !{i32 786468, null, metadata !"bool", null, i32 0, i64 8, i64 8, i64 0, i32 0, i32 2} ; [ DW_TAG_base_type ]
!50 = metadata !{i32 786445, metadata !46, metadata !"column", metadata !42, i32 15, i64 31, i64 32, i64 1, i32 0, metadata !51} ; [ DW_TAG_member ]
!51 = metadata !{i32 786468, null, metadata !"unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!52 = metadata !{i32 786445, metadata !46, metadata !"value", metadata !42, i32 16, i64 32, i64 32, i64 32, i32 0, metadata !53} ; [ DW_TAG_member ]
!53 = metadata !{i32 786468, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!54 = metadata !{i32 786445, metadata !41, metadata !"csr_v", metadata !42, i32 22, i64 64, i64 64, i64 0, i32 0, metadata !55} ; [ DW_TAG_member ]
!55 = metadata !{i32 786468, null, metadata !"long long unsigned int", null, i32 0, i64 64, i64 64, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!56 = metadata !{i32 786447, null, metadata !"", null, i32 0, i64 64, i64 64, i64 0, i32 0, metadata !53} ; [ DW_TAG_pointer_type ]
!57 = metadata !{metadata !58}
!58 = metadata !{i32 786468}                      ; [ DW_TAG_base_type ]
!59 = metadata !{i32 2, i32 100, metadata !35, null}
!60 = metadata !{i32 786689, metadata !35, metadata !"a_y", metadata !36, i32 33554434, metadata !51, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!61 = metadata !{i32 2, i32 49, metadata !35, null}
!62 = metadata !{i32 790531, metadata !63, metadata !"a", null, i32 2, metadata !64, i32 0, i32 0} ; [ DW_TAG_arg_variable_field ]
!63 = metadata !{i32 786689, metadata !35, metadata !"a", metadata !36, i32 16777218, metadata !39, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!64 = metadata !{i32 786433, null, metadata !"", null, i32 0, i64 268435456, i64 64, i32 0, i32 0, metadata !41, metadata !65, i32 0, i32 0} ; [ DW_TAG_array_type ]
!65 = metadata !{metadata !66}
!66 = metadata !{i32 786465, i64 0, i64 4194303}  ; [ DW_TAG_subrange_type ]
!67 = metadata !{i32 2, i32 22, metadata !35, null}
!68 = metadata !{i32 786689, metadata !35, metadata !"a_x", metadata !36, i32 50331650, metadata !51, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!69 = metadata !{i32 2, i32 67, metadata !35, null}
!70 = metadata !{i32 786689, metadata !35, metadata !"b", null, i32 2, metadata !71, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!71 = metadata !{i32 786433, null, metadata !"", null, i32 0, i64 65536, i64 32, i32 0, i32 0, metadata !53, metadata !72, i32 0, i32 0} ; [ DW_TAG_array_type ]
!72 = metadata !{metadata !73}
!73 = metadata !{i32 786465, i64 0, i64 2047}     ; [ DW_TAG_subrange_type ]
!74 = metadata !{i32 2, i32 76, metadata !35, null}
!75 = metadata !{i32 786689, metadata !35, metadata !"b_y", metadata !36, i32 83886082, metadata !53, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!76 = metadata !{i32 2, i32 91, metadata !35, null}
!77 = metadata !{i32 786689, metadata !35, metadata !"c", null, i32 2, metadata !71, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!78 = metadata !{i32 2, i32 109, metadata !35, null}
!79 = metadata !{i32 786688, metadata !80, metadata !"a_csr", null, i32 3, metadata !81, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!80 = metadata !{i32 786443, metadata !35, i32 2, i32 120, metadata !36, i32 0} ; [ DW_TAG_lexical_block ]
!81 = metadata !{i32 786433, null, metadata !"", null, i32 0, i64 268435456, i64 64, i32 0, i32 0, metadata !55, metadata !65, i32 0, i32 0} ; [ DW_TAG_array_type ]
!82 = metadata !{i32 3, i32 55, metadata !80, null}
!83 = metadata !{i32 4, i32 17, metadata !84, null}
!84 = metadata !{i32 786443, metadata !80, i32 4, i32 2, metadata !36, i32 1} ; [ DW_TAG_lexical_block ]
!85 = metadata !{i32 4, i32 31, metadata !84, null}
!86 = metadata !{i32 786688, metadata !84, metadata !"ibx", metadata !36, i32 4, metadata !53, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!87 = metadata !{i32 5, i32 36, metadata !88, null}
!88 = metadata !{i32 786443, metadata !89, i32 5, i32 3, metadata !36, i32 3} ; [ DW_TAG_lexical_block ]
!89 = metadata !{i32 786443, metadata !84, i32 4, i32 38, metadata !36, i32 2} ; [ DW_TAG_lexical_block ]
!90 = metadata !{i32 5, i32 49, metadata !88, null}
!91 = metadata !{i32 786688, metadata !88, metadata !"a_i", metadata !36, i32 5, metadata !53, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!92 = metadata !{i32 6, i32 33, metadata !93, null}
!93 = metadata !{i32 786443, metadata !88, i32 5, i32 56, metadata !36, i32 4} ; [ DW_TAG_lexical_block ]
!94 = metadata !{i32 7, i32 56, metadata !93, null}
!95 = metadata !{i32 786688, metadata !93, metadata !"column", metadata !36, i32 7, metadata !51, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!96 = metadata !{i32 8, i32 32, metadata !93, null}
!97 = metadata !{i32 786688, metadata !93, metadata !"value", metadata !36, i32 8, metadata !53, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!98 = metadata !{i32 9, i32 4, metadata !93, null}
!99 = metadata !{i32 10, i32 5, metadata !100, null}
!100 = metadata !{i32 786443, metadata !93, i32 9, i32 15, metadata !36, i32 5} ; [ DW_TAG_lexical_block ]
!101 = metadata !{i32 786688, metadata !88, metadata !"iay", metadata !36, i32 5, metadata !53, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!102 = metadata !{i32 12, i32 4, metadata !100, null}
!103 = metadata !{i32 13, i32 5, metadata !104, null}
!104 = metadata !{i32 786443, metadata !93, i32 12, i32 11, metadata !36, i32 6} ; [ DW_TAG_lexical_block ]
!105 = metadata !{i32 786688, metadata !88, metadata !"sum", metadata !36, i32 5, metadata !53, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!106 = metadata !{i32 17, i32 1, metadata !80, null}
