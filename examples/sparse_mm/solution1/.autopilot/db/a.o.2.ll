; ModuleID = '/home/drichmond/examples/sparse_mm/solution1/.autopilot/db/a.o.2.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@sparse_mm.str = internal unnamed_addr constant [10 x i8] c"sparse_mm\00" ; [#uses=1 type=[10 x i8]*]

; [#uses=0]
define void @sparse_mm([4194304 x i64]* %a, i32 %a_y, i32 %a_x, [2048 x i32]* %b, i32 %b_y, i32 %b_x, [2048 x i32]* %c) {
  call void (...)* @_ssdm_op_SpecBitsMap([4194304 x i64]* %a), !map !29
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %a_y), !map !35
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %a_x), !map !41
  call void (...)* @_ssdm_op_SpecBitsMap([2048 x i32]* %b), !map !45
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %b_y), !map !51
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %b_x), !map !55
  call void (...)* @_ssdm_op_SpecBitsMap([2048 x i32]* %c), !map !59
  call void (...)* @_ssdm_op_SpecTopModule([10 x i8]* @sparse_mm.str) nounwind
  call void @llvm.dbg.value(metadata !{[4194304 x i64]* %a}, i64 0, metadata !63), !dbg !68 ; [debug line = 2:22] [debug variable = a]
  call void @llvm.dbg.value(metadata !{i32 %a_y}, i64 0, metadata !69), !dbg !70 ; [debug line = 2:49] [debug variable = a_y]
  call void @llvm.dbg.value(metadata !{i32 %a_x}, i64 0, metadata !71), !dbg !72 ; [debug line = 2:67] [debug variable = a_x]
  call void @llvm.dbg.value(metadata !{[2048 x i32]* %b}, i64 0, metadata !73), !dbg !77 ; [debug line = 2:76] [debug variable = b]
  call void @llvm.dbg.value(metadata !{i32 %b_y}, i64 0, metadata !78), !dbg !79 ; [debug line = 2:91] [debug variable = b_y]
  call void @llvm.dbg.value(metadata !{i32 %b_x}, i64 0, metadata !80), !dbg !81 ; [debug line = 2:100] [debug variable = b_x]
  call void @llvm.dbg.value(metadata !{[2048 x i32]* %c}, i64 0, metadata !82), !dbg !83 ; [debug line = 2:109] [debug variable = c]
  call void @llvm.dbg.value(metadata !{[4194304 x i64]* %a}, i64 0, metadata !84), !dbg !87 ; [debug line = 3:55] [debug variable = a_csr]
  br label %1, !dbg !88                           ; [debug line = 4:17]

; <label>:1                                       ; preds = %6, %0
  %ibx = phi i31 [ 0, %0 ], [ %ibx.1, %6 ]        ; [#uses=2 type=i31]
  %ibx.cast = zext i31 %ibx to i32, !dbg !88      ; [#uses=3 type=i32] [debug line = 4:17]
  %tmp = icmp slt i32 %ibx.cast, %b_x, !dbg !88   ; [#uses=1 type=i1] [debug line = 4:17]
  br i1 %tmp, label %.preheader, label %7, !dbg !88 ; [debug line = 4:17]

.preheader:                                       ; preds = %5, %1
  %a_i = phi i32 [ %a_i.1, %5 ], [ 0, %1 ]        ; [#uses=2 type=i32]
  %iay = phi i32 [ %iay.1, %5 ], [ 0, %1 ]        ; [#uses=4 type=i32]
  %sum = phi i32 [ %sum.1, %5 ], [ 0, %1 ]        ; [#uses=2 type=i32]
  %tmp.1 = icmp ult i32 %iay, %a_y, !dbg !90      ; [#uses=1 type=i1] [debug line = 5:36]
  br i1 %tmp.1, label %2, label %6, !dbg !90      ; [debug line = 5:36]

; <label>:2                                       ; preds = %.preheader
  %tmp.2 = sext i32 %a_i to i64, !dbg !93         ; [#uses=1 type=i64] [debug line = 6:33]
  %a.addr = getelementptr [4194304 x i64]* %a, i64 0, i64 %tmp.2, !dbg !93 ; [#uses=1 type=i64*] [debug line = 6:33]
  %a.load = load i64* %a.addr, align 8, !dbg !93  ; [#uses=3 type=i64] [debug line = 6:33]
  %a.load.cast1 = trunc i64 %a.load to i1, !dbg !93 ; [#uses=1 type=i1] [debug line = 6:33]
  %a.load.cast = trunc i64 %a.load to i33, !dbg !93 ; [#uses=1 type=i33] [debug line = 6:33]
  %tmp.4 = lshr i33 %a.load.cast, 1, !dbg !95     ; [#uses=1 type=i33] [debug line = 7:56]
  %column = trunc i33 %tmp.4 to i31, !dbg !95     ; [#uses=1 type=i31] [debug line = 7:56]
  %column.cast = zext i31 %column to i32, !dbg !95 ; [#uses=1 type=i32] [debug line = 7:56]
  call void @llvm.dbg.value(metadata !{i31 %column}, i64 0, metadata !96), !dbg !95 ; [debug line = 7:56] [debug variable = column]
  %tmp.6 = lshr i64 %a.load, 32, !dbg !97         ; [#uses=1 type=i64] [debug line = 8:32]
  %value = trunc i64 %tmp.6 to i32, !dbg !97      ; [#uses=1 type=i32] [debug line = 8:32]
  call void @llvm.dbg.value(metadata !{i32 %value}, i64 0, metadata !98), !dbg !97 ; [debug line = 8:32] [debug variable = value]
  br i1 %a.load.cast1, label %3, label %4, !dbg !99 ; [debug line = 9:4]

; <label>:3                                       ; preds = %2
  %iay.2 = add nsw i32 %iay, 1, !dbg !100         ; [#uses=1 type=i32] [debug line = 10:5]
  call void @llvm.dbg.value(metadata !{i32 %iay.2}, i64 0, metadata !102), !dbg !100 ; [debug line = 10:5] [debug variable = iay]
  %tmp.3 = mul nsw i32 %iay, %b_x, !dbg !100      ; [#uses=1 type=i32] [debug line = 10:5]
  %tmp.5 = add nsw i32 %ibx.cast, %tmp.3, !dbg !100 ; [#uses=1 type=i32] [debug line = 10:5]
  %tmp.10 = sext i32 %tmp.5 to i64, !dbg !100     ; [#uses=1 type=i64] [debug line = 10:5]
  %c.addr = getelementptr [2048 x i32]* %c, i64 0, i64 %tmp.10, !dbg !100 ; [#uses=1 type=i32*] [debug line = 10:5]
  store i32 %sum, i32* %c.addr, align 4, !dbg !100 ; [debug line = 10:5]
  br label %5, !dbg !103                          ; [debug line = 12:4]

; <label>:4                                       ; preds = %2
  %tmp.8 = mul i32 %column.cast, %b_x, !dbg !104  ; [#uses=1 type=i32] [debug line = 13:5]
  %tmp.9 = add i32 %ibx.cast, %tmp.8, !dbg !104   ; [#uses=1 type=i32] [debug line = 13:5]
  %tmp. = zext i32 %tmp.9 to i64, !dbg !104       ; [#uses=1 type=i64] [debug line = 13:5]
  %b.addr = getelementptr [2048 x i32]* %b, i64 0, i64 %tmp., !dbg !104 ; [#uses=1 type=i32*] [debug line = 13:5]
  %b.load = load i32* %b.addr, align 4, !dbg !104 ; [#uses=1 type=i32] [debug line = 13:5]
  %tmp.7 = mul nsw i32 %value, %b.load, !dbg !104 ; [#uses=1 type=i32] [debug line = 13:5]
  %sum.2 = add nsw i32 %sum, %tmp.7, !dbg !104    ; [#uses=1 type=i32] [debug line = 13:5]
  call void @llvm.dbg.value(metadata !{i32 %sum.2}, i64 0, metadata !106), !dbg !104 ; [debug line = 13:5] [debug variable = sum]
  br label %5

; <label>:5                                       ; preds = %4, %3
  %iay.1 = phi i32 [ %iay.2, %3 ], [ %iay, %4 ]   ; [#uses=1 type=i32]
  %sum.1 = phi i32 [ 0, %3 ], [ %sum.2, %4 ]      ; [#uses=1 type=i32]
  %a_i.1 = add nsw i32 %a_i, 1, !dbg !107         ; [#uses=1 type=i32] [debug line = 5:49]
  call void @llvm.dbg.value(metadata !{i32 %a_i.1}, i64 0, metadata !108), !dbg !107 ; [debug line = 5:49] [debug variable = a_i]
  br label %.preheader, !dbg !107                 ; [debug line = 5:49]

; <label>:6                                       ; preds = %.preheader
  %ibx.1 = add i31 %ibx, 1, !dbg !109             ; [#uses=1 type=i31] [debug line = 4:31]
  call void @llvm.dbg.value(metadata !{i31 %ibx.1}, i64 0, metadata !110), !dbg !109 ; [debug line = 4:31] [debug variable = ibx]
  br label %1, !dbg !109                          ; [debug line = 4:31]

; <label>:7                                       ; preds = %1
  ret void, !dbg !111                             ; [debug line = 17:1]
}

; [#uses=14]
declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

; [#uses=1]
declare void @_ssdm_op_SpecTopModule(...)

; [#uses=7]
declare void @_ssdm_op_SpecBitsMap(...)

!llvm.dbg.cu = !{!0}
!hls.encrypted.func = !{}
!llvm.map.gv = !{}

!0 = metadata !{i32 786449, i32 0, i32 4, metadata !"/home/drichmond/examples/sparse_mm/solution1/.autopilot/db/sparse_mm.pragma.2.cpp", metadata !"/home/drichmond/examples", metadata !"clang version 3.1 ", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"sparse_mm", metadata !"sparse_mm", metadata !"_Z9sparse_mmP3csrjjPiiiS1_", metadata !6, i32 2, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, null, metadata !27, i32 2} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 786473, metadata !"sparse_mm.cpp", metadata !"/home/drichmond/examples", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{null, metadata !9, metadata !21, metadata !21, metadata !26, metadata !23, metadata !23, metadata !26}
!9 = metadata !{i32 786447, null, metadata !"", null, i32 0, i64 64, i64 64, i64 0, i32 0, metadata !10} ; [ DW_TAG_pointer_type ]
!10 = metadata !{i32 786454, null, metadata !"csr_t", metadata !6, i32 23, i64 0, i64 0, i64 0, i32 0, metadata !11} ; [ DW_TAG_typedef ]
!11 = metadata !{i32 786455, null, metadata !"csr", metadata !12, i32 19, i64 64, i64 64, i64 0, i32 0, null, metadata !13, i32 0, null} ; [ DW_TAG_union_type ]
!12 = metadata !{i32 786473, metadata !"./sparse_mm.h", metadata !"/home/drichmond/examples", null} ; [ DW_TAG_file_type ]
!13 = metadata !{metadata !14, metadata !24}
!14 = metadata !{i32 786445, metadata !11, metadata !"csr_s", metadata !12, i32 21, i64 64, i64 32, i64 0, i32 0, metadata !15} ; [ DW_TAG_member ]
!15 = metadata !{i32 786454, null, metadata !"csr_s_t", metadata !12, i32 17, i64 0, i64 0, i64 0, i32 0, metadata !16} ; [ DW_TAG_typedef ]
!16 = metadata !{i32 786434, null, metadata !"csr_s_t", metadata !12, i32 13, i64 64, i64 32, i32 0, i32 0, null, metadata !17, i32 0, null, null} ; [ DW_TAG_class_type ]
!17 = metadata !{metadata !18, metadata !20, metadata !22}
!18 = metadata !{i32 786445, metadata !16, metadata !"end_row", metadata !12, i32 14, i64 1, i64 8, i64 0, i32 0, metadata !19} ; [ DW_TAG_member ]
!19 = metadata !{i32 786468, null, metadata !"bool", null, i32 0, i64 8, i64 8, i64 0, i32 0, i32 2} ; [ DW_TAG_base_type ]
!20 = metadata !{i32 786445, metadata !16, metadata !"column", metadata !12, i32 15, i64 31, i64 32, i64 1, i32 0, metadata !21} ; [ DW_TAG_member ]
!21 = metadata !{i32 786468, null, metadata !"unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!22 = metadata !{i32 786445, metadata !16, metadata !"value", metadata !12, i32 16, i64 32, i64 32, i64 32, i32 0, metadata !23} ; [ DW_TAG_member ]
!23 = metadata !{i32 786468, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!24 = metadata !{i32 786445, metadata !11, metadata !"csr_v", metadata !12, i32 22, i64 64, i64 64, i64 0, i32 0, metadata !25} ; [ DW_TAG_member ]
!25 = metadata !{i32 786468, null, metadata !"long long unsigned int", null, i32 0, i64 64, i64 64, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!26 = metadata !{i32 786447, null, metadata !"", null, i32 0, i64 64, i64 64, i64 0, i32 0, metadata !23} ; [ DW_TAG_pointer_type ]
!27 = metadata !{metadata !28}
!28 = metadata !{i32 786468}                      ; [ DW_TAG_base_type ]
!29 = metadata !{metadata !30}
!30 = metadata !{i32 0, i32 63, metadata !31}
!31 = metadata !{metadata !32}
!32 = metadata !{metadata !"a", metadata !33, metadata !"void", i32 0, i32 63}
!33 = metadata !{metadata !34}
!34 = metadata !{i32 0, i32 4194303, i32 1}
!35 = metadata !{metadata !36}
!36 = metadata !{i32 0, i32 31, metadata !37}
!37 = metadata !{metadata !38}
!38 = metadata !{metadata !"a_y", metadata !39, metadata !"unsigned int", i32 0, i32 31}
!39 = metadata !{metadata !40}
!40 = metadata !{i32 0, i32 0, i32 0}
!41 = metadata !{metadata !42}
!42 = metadata !{i32 0, i32 31, metadata !43}
!43 = metadata !{metadata !44}
!44 = metadata !{metadata !"a_x", metadata !39, metadata !"unsigned int", i32 0, i32 31}
!45 = metadata !{metadata !46}
!46 = metadata !{i32 0, i32 31, metadata !47}
!47 = metadata !{metadata !48}
!48 = metadata !{metadata !"b", metadata !49, metadata !"int", i32 0, i32 31}
!49 = metadata !{metadata !50}
!50 = metadata !{i32 0, i32 2047, i32 1}
!51 = metadata !{metadata !52}
!52 = metadata !{i32 0, i32 31, metadata !53}
!53 = metadata !{metadata !54}
!54 = metadata !{metadata !"b_y", metadata !39, metadata !"int", i32 0, i32 31}
!55 = metadata !{metadata !56}
!56 = metadata !{i32 0, i32 31, metadata !57}
!57 = metadata !{metadata !58}
!58 = metadata !{metadata !"b_x", metadata !39, metadata !"int", i32 0, i32 31}
!59 = metadata !{metadata !60}
!60 = metadata !{i32 0, i32 31, metadata !61}
!61 = metadata !{metadata !62}
!62 = metadata !{metadata !"c", metadata !49, metadata !"int", i32 0, i32 31}
!63 = metadata !{i32 790531, metadata !64, metadata !"a", null, i32 2, metadata !65, i32 0, i32 0} ; [ DW_TAG_arg_variable_field ]
!64 = metadata !{i32 786689, metadata !5, metadata !"a", metadata !6, i32 16777218, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!65 = metadata !{i32 786433, null, metadata !"", null, i32 0, i64 268435456, i64 64, i32 0, i32 0, metadata !11, metadata !66, i32 0, i32 0} ; [ DW_TAG_array_type ]
!66 = metadata !{metadata !67}
!67 = metadata !{i32 786465, i64 0, i64 4194303}  ; [ DW_TAG_subrange_type ]
!68 = metadata !{i32 2, i32 22, metadata !5, null}
!69 = metadata !{i32 786689, metadata !5, metadata !"a_y", metadata !6, i32 33554434, metadata !21, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!70 = metadata !{i32 2, i32 49, metadata !5, null}
!71 = metadata !{i32 786689, metadata !5, metadata !"a_x", metadata !6, i32 50331650, metadata !21, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!72 = metadata !{i32 2, i32 67, metadata !5, null}
!73 = metadata !{i32 786689, metadata !5, metadata !"b", null, i32 2, metadata !74, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!74 = metadata !{i32 786433, null, metadata !"", null, i32 0, i64 65536, i64 32, i32 0, i32 0, metadata !23, metadata !75, i32 0, i32 0} ; [ DW_TAG_array_type ]
!75 = metadata !{metadata !76}
!76 = metadata !{i32 786465, i64 0, i64 2047}     ; [ DW_TAG_subrange_type ]
!77 = metadata !{i32 2, i32 76, metadata !5, null}
!78 = metadata !{i32 786689, metadata !5, metadata !"b_y", metadata !6, i32 83886082, metadata !23, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!79 = metadata !{i32 2, i32 91, metadata !5, null}
!80 = metadata !{i32 786689, metadata !5, metadata !"b_x", metadata !6, i32 100663298, metadata !23, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!81 = metadata !{i32 2, i32 100, metadata !5, null}
!82 = metadata !{i32 786689, metadata !5, metadata !"c", null, i32 2, metadata !74, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!83 = metadata !{i32 2, i32 109, metadata !5, null}
!84 = metadata !{i32 786688, metadata !85, metadata !"a_csr", null, i32 3, metadata !86, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!85 = metadata !{i32 786443, metadata !5, i32 2, i32 120, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!86 = metadata !{i32 786433, null, metadata !"", null, i32 0, i64 268435456, i64 64, i32 0, i32 0, metadata !25, metadata !66, i32 0, i32 0} ; [ DW_TAG_array_type ]
!87 = metadata !{i32 3, i32 55, metadata !85, null}
!88 = metadata !{i32 4, i32 17, metadata !89, null}
!89 = metadata !{i32 786443, metadata !85, i32 4, i32 2, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!90 = metadata !{i32 5, i32 36, metadata !91, null}
!91 = metadata !{i32 786443, metadata !92, i32 5, i32 3, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!92 = metadata !{i32 786443, metadata !89, i32 4, i32 38, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!93 = metadata !{i32 6, i32 33, metadata !94, null}
!94 = metadata !{i32 786443, metadata !91, i32 5, i32 56, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!95 = metadata !{i32 7, i32 56, metadata !94, null}
!96 = metadata !{i32 786688, metadata !94, metadata !"column", metadata !6, i32 7, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!97 = metadata !{i32 8, i32 32, metadata !94, null}
!98 = metadata !{i32 786688, metadata !94, metadata !"value", metadata !6, i32 8, metadata !23, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!99 = metadata !{i32 9, i32 4, metadata !94, null}
!100 = metadata !{i32 10, i32 5, metadata !101, null}
!101 = metadata !{i32 786443, metadata !94, i32 9, i32 15, metadata !6, i32 5} ; [ DW_TAG_lexical_block ]
!102 = metadata !{i32 786688, metadata !91, metadata !"iay", metadata !6, i32 5, metadata !23, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!103 = metadata !{i32 12, i32 4, metadata !101, null}
!104 = metadata !{i32 13, i32 5, metadata !105, null}
!105 = metadata !{i32 786443, metadata !94, i32 12, i32 11, metadata !6, i32 6} ; [ DW_TAG_lexical_block ]
!106 = metadata !{i32 786688, metadata !91, metadata !"sum", metadata !6, i32 5, metadata !23, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!107 = metadata !{i32 5, i32 49, metadata !91, null}
!108 = metadata !{i32 786688, metadata !91, metadata !"a_i", metadata !6, i32 5, metadata !23, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!109 = metadata !{i32 4, i32 31, metadata !89, null}
!110 = metadata !{i32 786688, metadata !89, metadata !"ibx", metadata !6, i32 4, metadata !23, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!111 = metadata !{i32 17, i32 1, metadata !85, null}
