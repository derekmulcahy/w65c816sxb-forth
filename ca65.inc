.list on
.p816
.define code    .segment "CODE"
.define data    .segment "DATA"
.define db      .byte
.define ds      .res
.define dw      .word
.define else    .else
.define end     .end
.define endif   .endif
.define equ     :=
.define extern  .import
.define if      .if
.define include .include
.define page0   .segment "ZEROPAGE"
.define public  .export
.define set     .set
.define WORDL   .ident(.sprintf("WORD%d", WORDZ))
.feature labels_without_colons
.feature dollar_is_pc
.feature ubiquitous_idents
.macro longi enable
        .if .match(enable,"on")
                .i16
        .else
                .i8
        .endif
.endmacro
.macro longa enable
        .if .match(enable,"on")
                .a16
        .else
                .a8
        .endif
.endmacro
