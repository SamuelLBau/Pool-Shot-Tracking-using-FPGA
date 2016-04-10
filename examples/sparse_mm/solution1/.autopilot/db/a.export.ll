; ModuleID = '/home/drichmond/examples/sparse_mm/solution1/.autopilot/db/a.o.2.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@sparse_mm_str = internal unnamed_addr constant [10 x i8] c"sparse_mm\00"

define void @sparse_mm([4194304 x i64]* %a, i32 %a_y, i32 %a_x, [2048 x i32]* %b, i32 %b_y, i32 %b_x, [2048 x i32]* %c) {
  call void (...)* @_ssdm_op_SpecBitsMap([4194304 x i64]* %a), !map !0
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %a_y), !map !6
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %a_x), !map !12
  call void (...)* @_ssdm_op_SpecBitsMap([2048 x i32]* %b), !map !16
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %b_y), !map !22
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %b_x), !map !26
  call void (...)* @_ssdm_op_SpecBitsMap([2048 x i32]* %c), !map !30
  call void (...)* @_ssdm_op_SpecTopModule([10 x i8]* @sparse_mm_str) nounwind
  %b_x_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %b_x)
  %a_y_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %a_y)
  br label %.loopexit

.loopexit:                                        ; preds = %.preheader, %0
  %ibx = phi i31 [ 0, %0 ], [ %ibx_1, %.preheader ]
  %ibx_cast = zext i31 %ibx to i32
  %tmp = icmp slt i32 %ibx_cast, %b_x_read
  %ibx_1 = add i31 %ibx, 1
  br i1 %tmp, label %.preheader, label %4

.preheader:                                       ; preds = %2, %3, %.loopexit
  %a_i = phi i32 [ 0, %.loopexit ], [ %a_i_1, %3 ], [ %a_i_1, %2 ]
  %iay = phi i32 [ 0, %.loopexit ], [ %iay_1, %2 ], [ %iay, %3 ]
  %sum = phi i32 [ 0, %.loopexit ], [ 0, %2 ], [ %sum_1, %3 ]
  %tmp_1 = icmp ult i32 %iay, %a_y_read
  %a_i_1 = add nsw i32 %a_i, 1
  br i1 %tmp_1, label %1, label %.loopexit

; <label>:1                                       ; preds = %.preheader
  %tmp_2 = sext i32 %a_i to i64
  %a_addr = getelementptr [4194304 x i64]* %a, i64 0, i64 %tmp_2
  %a_load = load i64* %a_addr, align 8
  %tmp_6 = trunc i64 %a_load to i1
  %column = call i31 @_ssdm_op_PartSelect.i31.i64.i32.i32(i64 %a_load, i32 1, i32 31)
  %column_cast = zext i31 %column to i32
  %value = call i32 @_ssdm_op_PartSelect.i32.i64.i32.i32(i64 %a_load, i32 32, i32 63)
  br i1 %tmp_6, label %2, label %3

; <label>:2                                       ; preds = %1
  %iay_1 = add nsw i32 %iay, 1
  %tmp_3 = mul nsw i32 %iay, %b_x_read
  %tmp_5 = add nsw i32 %tmp_3, %ibx_cast
  %tmp_4 = sext i32 %tmp_5 to i64
  %c_addr = getelementptr [2048 x i32]* %c, i64 0, i64 %tmp_4
  store i32 %sum, i32* %c_addr, align 4
  br label %.preheader

; <label>:3                                       ; preds = %1
  %tmp_8 = mul i32 %column_cast, %b_x_read
  %tmp_9 = add i32 %tmp_8, %ibx_cast
  %tmp_s = zext i32 %tmp_9 to i64
  %b_addr = getelementptr [2048 x i32]* %b, i64 0, i64 %tmp_s
  %b_load = load i32* %b_addr, align 4
  %tmp_7 = mul nsw i32 %b_load, %value
  %sum_1 = add nsw i32 %tmp_7, %sum
  br label %.preheader

; <label>:4                                       ; preds = %.loopexit
  ret void
}

declare i64 @llvm.part.select.i64(i64, i32, i32) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

define weak void @_ssdm_op_SpecTopModule(...) {
entry:
  ret void
}

define weak void @_ssdm_op_SpecBitsMap(...) {
entry:
  ret void
}

define weak i32 @_ssdm_op_Read.ap_auto.i32(i32) {
entry:
  ret i32 %0
}

define weak i32 @_ssdm_op_PartSelect.i32.i64.i32.i32(i64, i32, i32) nounwind readnone {
entry:
  %empty = call i64 @llvm.part.select.i64(i64 %0, i32 %1, i32 %2)
  %empty_4 = trunc i64 %empty to i32
  ret i32 %empty_4
}

define weak i31 @_ssdm_op_PartSelect.i31.i64.i32.i32(i64, i32, i32) nounwind readnone {
entry:
  %empty = call i64 @llvm.part.select.i64(i64 %0, i32 %1, i32 %2)
  %empty_5 = trunc i64 %empty to i31
  ret i31 %empty_5
}

declare i1 @_ssdm_op_PartSelect.i1.i64.i32.i32(i64, i32, i32) nounwind readnone

declare i16 @_ssdm_op_HSub(...)

declare i16 @_ssdm_op_HMul(...)

declare i16 @_ssdm_op_HDiv(...)

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
