; ModuleID = '/home/drichmond/examples/sparse_mm/solution1/.autopilot/db/a.g.1.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%union.csr.0 = type { i64 }

@sparse_mm.str = internal unnamed_addr constant [10 x i8] c"sparse_mm\00" ; [#uses=1 type=[10 x i8]*]

; [#uses=0]
define void @sparse_mm(%union.csr.0* %a, i32 %a_y, i32 %a_x, i32* %b, i32 %b_y, i32 %b_x, i32* %c) nounwind uwtable {
  call void (...)* @_ssdm_op_SpecTopModule([10 x i8]* @sparse_mm.str) nounwind
  call void @llvm.dbg.value(metadata !{%union.csr.0* %a}, i64 0, metadata !29), !dbg !30 ; [debug line = 2:22] [debug variable = a]
  call void @llvm.dbg.value(metadata !{i32 %a_y}, i64 0, metadata !31), !dbg !32 ; [debug line = 2:49] [debug variable = a_y]
  call void @llvm.dbg.value(metadata !{i32 %a_x}, i64 0, metadata !33), !dbg !34 ; [debug line = 2:67] [debug variable = a_x]
  call void @llvm.dbg.value(metadata !{i32* %b}, i64 0, metadata !35), !dbg !36 ; [debug line = 2:76] [debug variable = b]
  call void @llvm.dbg.value(metadata !{i32 %b_y}, i64 0, metadata !37), !dbg !38 ; [debug line = 2:91] [debug variable = b_y]
  call void @llvm.dbg.value(metadata !{i32 %b_x}, i64 0, metadata !39), !dbg !40 ; [debug line = 2:100] [debug variable = b_x]
  call void @llvm.dbg.value(metadata !{i32* %c}, i64 0, metadata !41), !dbg !42 ; [debug line = 2:109] [debug variable = c]
  call void (...)* @_ssdm_SpecArrayDimSize(%union.csr.0* %a, i32 4194304) nounwind, !dbg !43 ; [debug line = 2:121]
  call void (...)* @_ssdm_SpecArrayDimSize(i32* %b, i32 2048) nounwind, !dbg !45 ; [debug line = 2:157]
  call void (...)* @_ssdm_SpecArrayDimSize(i32* %c, i32 2048) nounwind, !dbg !46 ; [debug line = 2:190]
  %a_csr = getelementptr inbounds %union.csr.0* %a, i64 0, i32 0, !dbg !47 ; [#uses=1 type=i64*] [debug line = 3:55]
  call void @llvm.dbg.value(metadata !{i64* %a_csr}, i64 0, metadata !48), !dbg !47 ; [debug line = 3:55] [debug variable = a_csr]
  br label %1, !dbg !50                           ; [debug line = 4:17]

; <label>:1                                       ; preds = %6, %0
  %ibx = phi i32 [ 0, %0 ], [ %ibx.1, %6 ]        ; [#uses=4 type=i32]
  %tmp = icmp slt i32 %ibx, %b_x, !dbg !50        ; [#uses=1 type=i1] [debug line = 4:17]
  br i1 %tmp, label %.preheader.preheader, label %7, !dbg !50 ; [debug line = 4:17]

.preheader.preheader:                             ; preds = %1
  br label %.preheader, !dbg !52                  ; [debug line = 5:36]

.preheader:                                       ; preds = %5, %.preheader.preheader
  %a_i = phi i32 [ %a_i.1, %5 ], [ 0, %.preheader.preheader ] ; [#uses=2 type=i32]
  %iay = phi i32 [ %iay.1, %5 ], [ 0, %.preheader.preheader ] ; [#uses=4 type=i32]
  %sum = phi i32 [ %sum.1, %5 ], [ 0, %.preheader.preheader ] ; [#uses=2 type=i32]
  %tmp.1 = icmp ult i32 %iay, %a_y, !dbg !52      ; [#uses=1 type=i1] [debug line = 5:36]
  br i1 %tmp.1, label %2, label %6, !dbg !52      ; [debug line = 5:36]

; <label>:2                                       ; preds = %.preheader
  %tmp.2 = sext i32 %a_i to i64, !dbg !55         ; [#uses=1 type=i64] [debug line = 6:33]
  %a_csr.addr = getelementptr inbounds i64* %a_csr, i64 %tmp.2, !dbg !55 ; [#uses=1 type=i64*] [debug line = 6:33]
  %a_csr.load = load i64* %a_csr.addr, align 8, !dbg !55 ; [#uses=6 type=i64] [debug line = 6:33]
  call void (...)* @_ssdm_SpecKeepArrayLoad(i64 %a_csr.load) nounwind
  %tmp.3 = and i64 %a_csr.load, 1, !dbg !55       ; [#uses=1 type=i64] [debug line = 6:33]
  %end_row = icmp eq i64 %tmp.3, 0, !dbg !55      ; [#uses=1 type=i1] [debug line = 6:33]
  call void @llvm.dbg.value(metadata !{i1 %end_row}, i64 0, metadata !57), !dbg !55 ; [debug line = 6:33] [debug variable = end_row]
  call void (...)* @_ssdm_SpecKeepArrayLoad(i64 %a_csr.load) nounwind
  %tmp.4 = lshr i64 %a_csr.load, 1, !dbg !58      ; [#uses=1 type=i64] [debug line = 7:56]
  %tmp.5 = trunc i64 %tmp.4 to i32, !dbg !58      ; [#uses=1 type=i32] [debug line = 7:56]
  %column = and i32 %tmp.5, 2147483647, !dbg !58  ; [#uses=1 type=i32] [debug line = 7:56]
  call void @llvm.dbg.value(metadata !{i32 %column}, i64 0, metadata !59), !dbg !58 ; [debug line = 7:56] [debug variable = column]
  call void (...)* @_ssdm_SpecKeepArrayLoad(i64 %a_csr.load) nounwind
  %tmp.6 = lshr i64 %a_csr.load, 32, !dbg !60     ; [#uses=1 type=i64] [debug line = 8:32]
  %value = trunc i64 %tmp.6 to i32, !dbg !60      ; [#uses=1 type=i32] [debug line = 8:32]
  call void @llvm.dbg.value(metadata !{i32 %value}, i64 0, metadata !61), !dbg !60 ; [debug line = 8:32] [debug variable = value]
  br i1 %end_row, label %4, label %3, !dbg !62    ; [debug line = 9:4]

; <label>:3                                       ; preds = %2
  %iay.2 = add nsw i32 %iay, 1, !dbg !63          ; [#uses=1 type=i32] [debug line = 10:5]
  call void @llvm.dbg.value(metadata !{i32 %iay.2}, i64 0, metadata !65), !dbg !63 ; [debug line = 10:5] [debug variable = iay]
  %tmp.14 = mul nsw i32 %iay, %b_x, !dbg !63      ; [#uses=1 type=i32] [debug line = 10:5]
  %tmp.15 = add nsw i32 %tmp.14, %ibx, !dbg !63   ; [#uses=1 type=i32] [debug line = 10:5]
  %tmp.16 = sext i32 %tmp.15 to i64, !dbg !63     ; [#uses=1 type=i64] [debug line = 10:5]
  %c.addr = getelementptr inbounds i32* %c, i64 %tmp.16, !dbg !63 ; [#uses=1 type=i32*] [debug line = 10:5]
  store i32 %sum, i32* %c.addr, align 4, !dbg !63 ; [debug line = 10:5]
  br label %5, !dbg !66                           ; [debug line = 12:4]

; <label>:4                                       ; preds = %2
  %tmp.8 = mul i32 %column, %b_x, !dbg !67        ; [#uses=1 type=i32] [debug line = 13:5]
  %tmp.9 = add i32 %tmp.8, %ibx, !dbg !67         ; [#uses=1 type=i32] [debug line = 13:5]
  %tmp.10 = zext i32 %tmp.9 to i64, !dbg !67      ; [#uses=1 type=i64] [debug line = 13:5]
  %b.addr = getelementptr inbounds i32* %b, i64 %tmp.10, !dbg !67 ; [#uses=1 type=i32*] [debug line = 13:5]
  %b.load = load i32* %b.addr, align 4, !dbg !67  ; [#uses=2 type=i32] [debug line = 13:5]
  call void (...)* @_ssdm_SpecKeepArrayLoad(i32 %b.load) nounwind
  %tmp.11 = mul nsw i32 %b.load, %value, !dbg !67 ; [#uses=1 type=i32] [debug line = 13:5]
  %sum.2 = add nsw i32 %tmp.11, %sum, !dbg !67    ; [#uses=1 type=i32] [debug line = 13:5]
  call void @llvm.dbg.value(metadata !{i32 %sum.2}, i64 0, metadata !69), !dbg !67 ; [debug line = 13:5] [debug variable = sum]
  br label %5

; <label>:5                                       ; preds = %4, %3
  %iay.1 = phi i32 [ %iay.2, %3 ], [ %iay, %4 ]   ; [#uses=1 type=i32]
  %sum.1 = phi i32 [ 0, %3 ], [ %sum.2, %4 ]      ; [#uses=1 type=i32]
  %a_i.1 = add nsw i32 %a_i, 1, !dbg !70          ; [#uses=1 type=i32] [debug line = 5:49]
  call void @llvm.dbg.value(metadata !{i32 %a_i.1}, i64 0, metadata !71), !dbg !70 ; [debug line = 5:49] [debug variable = a_i]
  br label %.preheader, !dbg !70                  ; [debug line = 5:49]

; <label>:6                                       ; preds = %.preheader
  %ibx.1 = add nsw i32 %ibx, 1, !dbg !72          ; [#uses=1 type=i32] [debug line = 4:31]
  call void @llvm.dbg.value(metadata !{i32 %ibx.1}, i64 0, metadata !73), !dbg !72 ; [debug line = 4:31] [debug variable = ibx]
  br label %1, !dbg !72                           ; [debug line = 4:31]

; <label>:7                                       ; preds = %1
  ret void, !dbg !74                              ; [debug line = 17:1]
}

; [#uses=15]
declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

; [#uses=1]
declare void @_ssdm_op_SpecTopModule(...)

; [#uses=4]
declare void @_ssdm_SpecKeepArrayLoad(...)

; [#uses=3]
declare void @_ssdm_SpecArrayDimSize(...) nounwind

!llvm.dbg.cu = !{!0}
!hls.encrypted.func = !{}

!0 = metadata !{i32 786449, i32 0, i32 4, metadata !"/home/drichmond/examples/sparse_mm/solution1/.autopilot/db/sparse_mm.pragma.2.cpp", metadata !"/home/drichmond/examples", metadata !"clang version 3.1 ", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"sparse_mm", metadata !"sparse_mm", metadata !"_Z9sparse_mmP3csrjjPiiiS1_", metadata !6, i32 2, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, void (%union.csr.0*, i32, i32, i32*, i32, i32, i32*)* @sparse_mm, null, null, metadata !27, i32 2} ; [ DW_TAG_subprogram ]
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
!29 = metadata !{i32 786689, metadata !5, metadata !"a", metadata !6, i32 16777218, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!30 = metadata !{i32 2, i32 22, metadata !5, null}
!31 = metadata !{i32 786689, metadata !5, metadata !"a_y", metadata !6, i32 33554434, metadata !21, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!32 = metadata !{i32 2, i32 49, metadata !5, null}
!33 = metadata !{i32 786689, metadata !5, metadata !"a_x", metadata !6, i32 50331650, metadata !21, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!34 = metadata !{i32 2, i32 67, metadata !5, null}
!35 = metadata !{i32 786689, metadata !5, metadata !"b", metadata !6, i32 67108866, metadata !26, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!36 = metadata !{i32 2, i32 76, metadata !5, null}
!37 = metadata !{i32 786689, metadata !5, metadata !"b_y", metadata !6, i32 83886082, metadata !23, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!38 = metadata !{i32 2, i32 91, metadata !5, null}
!39 = metadata !{i32 786689, metadata !5, metadata !"b_x", metadata !6, i32 100663298, metadata !23, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!40 = metadata !{i32 2, i32 100, metadata !5, null}
!41 = metadata !{i32 786689, metadata !5, metadata !"c", metadata !6, i32 117440514, metadata !26, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!42 = metadata !{i32 2, i32 109, metadata !5, null}
!43 = metadata !{i32 2, i32 121, metadata !44, null}
!44 = metadata !{i32 786443, metadata !5, i32 2, i32 120, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!45 = metadata !{i32 2, i32 157, metadata !44, null}
!46 = metadata !{i32 2, i32 190, metadata !44, null}
!47 = metadata !{i32 3, i32 55, metadata !44, null}
!48 = metadata !{i32 786688, metadata !44, metadata !"a_csr", metadata !6, i32 3, metadata !49, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!49 = metadata !{i32 786447, null, metadata !"", null, i32 0, i64 64, i64 64, i64 0, i32 0, metadata !25} ; [ DW_TAG_pointer_type ]
!50 = metadata !{i32 4, i32 17, metadata !51, null}
!51 = metadata !{i32 786443, metadata !44, i32 4, i32 2, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!52 = metadata !{i32 5, i32 36, metadata !53, null}
!53 = metadata !{i32 786443, metadata !54, i32 5, i32 3, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!54 = metadata !{i32 786443, metadata !51, i32 4, i32 38, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!55 = metadata !{i32 6, i32 33, metadata !56, null}
!56 = metadata !{i32 786443, metadata !53, i32 5, i32 56, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!57 = metadata !{i32 786688, metadata !56, metadata !"end_row", metadata !6, i32 6, metadata !19, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!58 = metadata !{i32 7, i32 56, metadata !56, null}
!59 = metadata !{i32 786688, metadata !56, metadata !"column", metadata !6, i32 7, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!60 = metadata !{i32 8, i32 32, metadata !56, null}
!61 = metadata !{i32 786688, metadata !56, metadata !"value", metadata !6, i32 8, metadata !23, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!62 = metadata !{i32 9, i32 4, metadata !56, null}
!63 = metadata !{i32 10, i32 5, metadata !64, null}
!64 = metadata !{i32 786443, metadata !56, i32 9, i32 15, metadata !6, i32 5} ; [ DW_TAG_lexical_block ]
!65 = metadata !{i32 786688, metadata !53, metadata !"iay", metadata !6, i32 5, metadata !23, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!66 = metadata !{i32 12, i32 4, metadata !64, null}
!67 = metadata !{i32 13, i32 5, metadata !68, null}
!68 = metadata !{i32 786443, metadata !56, i32 12, i32 11, metadata !6, i32 6} ; [ DW_TAG_lexical_block ]
!69 = metadata !{i32 786688, metadata !53, metadata !"sum", metadata !6, i32 5, metadata !23, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!70 = metadata !{i32 5, i32 49, metadata !53, null}
!71 = metadata !{i32 786688, metadata !53, metadata !"a_i", metadata !6, i32 5, metadata !23, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!72 = metadata !{i32 4, i32 31, metadata !51, null}
!73 = metadata !{i32 786688, metadata !51, metadata !"ibx", metadata !6, i32 4, metadata !23, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!74 = metadata !{i32 17, i32 1, metadata !44, null}
