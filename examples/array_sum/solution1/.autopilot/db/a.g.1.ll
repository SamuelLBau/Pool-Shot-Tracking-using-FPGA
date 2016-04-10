; ModuleID = '/home/drichmond/examples/array_sum/solution1/.autopilot/db/a.g.1.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@array_sum.str = internal unnamed_addr constant [10 x i8] c"array_sum\00" ; [#uses=1 type=[10 x i8]*]
@.str1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1 ; [#uses=1 type=[1 x i8]*]
@.str = private unnamed_addr constant [12 x i8] c"hls_label_0\00", align 1 ; [#uses=1 type=[12 x i8]*]

; [#uses=4]
declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

; [#uses=0]
define i32 @array_sum(i32* %array, i32 %length) nounwind uwtable {
  call void (...)* @_ssdm_op_SpecBitsMap(i32 0) nounwind, !map !14
  call void (...)* @_ssdm_op_SpecTopModule([10 x i8]* @array_sum.str) nounwind
  call void @llvm.dbg.value(metadata !{i32* %array}, i64 0, metadata !20), !dbg !21 ; [debug line = 1:19] [debug variable = array]
  call void @llvm.dbg.value(metadata !{i32 %length}, i64 0, metadata !22), !dbg !23 ; [debug line = 1:43] [debug variable = length]
  call void (...)* @_ssdm_SpecArrayDimSize(i32* %array, i32 64) nounwind, !dbg !24 ; [debug line = 2:2]
  br label %1, !dbg !26                           ; [debug line = 4:15]

; <label>:1                                       ; preds = %2, %0
  %sum = phi i32 [ 0, %0 ], [ %sum.1, %2 ]        ; [#uses=2 type=i32]
  %i = phi i32 [ 0, %0 ], [ %i.1, %2 ]            ; [#uses=3 type=i32]
  %exitcond = icmp eq i32 %i, 64, !dbg !26        ; [#uses=1 type=i1] [debug line = 4:15]
  br i1 %exitcond, label %3, label %2, !dbg !26   ; [debug line = 4:15]

; <label>:2                                       ; preds = %1
  %rbegin = call i32 (...)* @_ssdm_op_SpecRegionBegin(i8* getelementptr inbounds ([12 x i8]* @.str, i64 0, i64 0)) nounwind, !dbg !28 ; [#uses=1 type=i32] [debug line = 4:30]
  call void (...)* @_ssdm_Unroll(i32 0, i32 0, i32 0, i8* getelementptr inbounds ([1 x i8]* @.str1, i64 0, i64 0)) nounwind, !dbg !30 ; [debug line = 5:1]
  %tmp = sext i32 %i to i64, !dbg !31             ; [#uses=1 type=i64] [debug line = 6:2]
  %array.addr = getelementptr inbounds i32* %array, i64 %tmp, !dbg !31 ; [#uses=1 type=i32*] [debug line = 6:2]
  %array.load = load i32* %array.addr, align 4, !dbg !31 ; [#uses=2 type=i32] [debug line = 6:2]
  call void (...)* @_ssdm_SpecKeepArrayLoad(i32 %array.load) nounwind
  %sum.1 = add nsw i32 %array.load, %sum, !dbg !31 ; [#uses=1 type=i32] [debug line = 6:2]
  call void @llvm.dbg.value(metadata !{i32 %sum.1}, i64 0, metadata !32), !dbg !31 ; [debug line = 6:2] [debug variable = sum]
  %rend = call i32 (...)* @_ssdm_op_SpecRegionEnd(i8* getelementptr inbounds ([12 x i8]* @.str, i64 0, i64 0), i32 %rbegin) nounwind, !dbg !33 ; [#uses=0 type=i32] [debug line = 7:2]
  %i.1 = add nsw i32 %i, 1, !dbg !34              ; [#uses=1 type=i32] [debug line = 4:25]
  call void @llvm.dbg.value(metadata !{i32 %i.1}, i64 0, metadata !35), !dbg !34 ; [debug line = 4:25] [debug variable = i]
  br label %1, !dbg !34                           ; [debug line = 4:25]

; <label>:3                                       ; preds = %1
  %sum.0.lcssa = phi i32 [ %sum, %1 ]             ; [#uses=1 type=i32]
  ret i32 %sum.0.lcssa, !dbg !36                  ; [debug line = 8:2]
}

; [#uses=1]
declare void @_ssdm_op_SpecTopModule(...)

; [#uses=1]
declare i32 @_ssdm_op_SpecRegionEnd(...)

; [#uses=1]
declare i32 @_ssdm_op_SpecRegionBegin(...)

; [#uses=1]
declare void @_ssdm_op_SpecBitsMap(...)

; [#uses=1]
declare void @_ssdm_Unroll(...) nounwind

; [#uses=1]
declare void @_ssdm_SpecKeepArrayLoad(...)

; [#uses=1]
declare void @_ssdm_SpecArrayDimSize(...) nounwind

!llvm.dbg.cu = !{!0}
!hls.encrypted.func = !{}

!0 = metadata !{i32 786449, i32 0, i32 1, metadata !"/home/drichmond/examples/array_sum/solution1/.autopilot/db/array_sum.pragma.2.c", metadata !"/home/drichmond/examples", metadata !"clang version 3.1 ", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"array_sum", metadata !"array_sum", metadata !"", metadata !6, i32 1, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, i32 (i32*, i32)* @array_sum, null, null, metadata !12, i32 2} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 786473, metadata !"array_sum.c", metadata !"/home/drichmond/examples", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9, metadata !10, metadata !11}
!9 = metadata !{i32 786468, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!10 = metadata !{i32 786447, null, metadata !"", null, i32 0, i64 64, i64 64, i64 0, i32 0, metadata !9} ; [ DW_TAG_pointer_type ]
!11 = metadata !{i32 786468, null, metadata !"unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!12 = metadata !{metadata !13}
!13 = metadata !{i32 786468}                      ; [ DW_TAG_base_type ]
!14 = metadata !{metadata !15}
!15 = metadata !{i32 0, i32 31, metadata !16}
!16 = metadata !{metadata !17}
!17 = metadata !{metadata !"return", metadata !18, metadata !"int", i32 0, i32 31}
!18 = metadata !{metadata !19}
!19 = metadata !{i32 0, i32 1, i32 0}
!20 = metadata !{i32 786689, metadata !5, metadata !"array", metadata !6, i32 16777217, metadata !10, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!21 = metadata !{i32 1, i32 19, metadata !5, null}
!22 = metadata !{i32 786689, metadata !5, metadata !"length", metadata !6, i32 33554433, metadata !11, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!23 = metadata !{i32 1, i32 43, metadata !5, null}
!24 = metadata !{i32 2, i32 2, metadata !25, null}
!25 = metadata !{i32 786443, metadata !5, i32 2, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!26 = metadata !{i32 4, i32 15, metadata !27, null}
!27 = metadata !{i32 786443, metadata !25, i32 4, i32 2, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!28 = metadata !{i32 4, i32 30, metadata !29, null}
!29 = metadata !{i32 786443, metadata !27, i32 4, i32 29, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!30 = metadata !{i32 5, i32 1, metadata !29, null}
!31 = metadata !{i32 6, i32 2, metadata !29, null}
!32 = metadata !{i32 786688, metadata !25, metadata !"sum", metadata !6, i32 3, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!33 = metadata !{i32 7, i32 2, metadata !29, null}
!34 = metadata !{i32 4, i32 25, metadata !27, null}
!35 = metadata !{i32 786688, metadata !27, metadata !"i", metadata !6, i32 4, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!36 = metadata !{i32 8, i32 2, metadata !25, null}
