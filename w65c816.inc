;==============================================================================
; __        ____  ____   ____ ___  _  __   
; \ \      / / /_| ___| / ___( _ )/ |/ /_  
;  \ \ /\ / / '_ \___ \| |   / _ \| | '_ \ 
;   \ V  V /| (_) |__) | |__| (_) | | (_) |
;    \_/\_/  \___/____/ \____\___/|_|\___/ 
;
; Western Design Center W65C816 device definitions                                          
;------------------------------------------------------------------------------
; Copyright (C)2015 HandCoded Software Ltd.
; All rights reserved.
;
; This work is made available under the terms of the Creative Commons
; Attribution-NonCommercial-ShareAlike 4.0 International license. Open the
; following URL to see the details.
;
; http://creativecommons.org/licenses/by-nc-sa/4.0/
;
;===============================================================================
; Notes:
;
; Various macros and definitions for the W65C816 microprocessor.
;
;===============================================================================
; Revision History:
;
; 2015-12-18 AJ Initial version
;-------------------------------------------------------------------------------
; $Id$
;-------------------------------------------------------------------------------

;==============================================================================
; Status Register Bits
;------------------------------------------------------------------------------

N_FLAG          equ     1<<7
V_FLAG          equ     1<<6
M_FLAG          equ     1<<5
X_FLAG          equ     1<<4
B_FLAG          equ     1<<4
D_FLAG          equ     1<<3
I_FLAG          equ     1<<2
Z_FLAG          equ     1<<1
C_FLAG          equ     1<<0

;==============================================================================
; Macros
;------------------------------------------------------------------------------

; Puts the processor in emulation mode. A, X and Y become 8-bits and the stack
; is fixed at $0100-$01ff. 

.macro          emulate
                sec
                xce
.endmacro

; Puts the processor in native mode. The size of the memory and index register
; operations is not controlled by the M & X bits in the status register.

.macro          native
                clc
                xce
.endmacro

; Resets the M bit making the accumulator and memory accesses 16-bits wide.
 
.macro          long_a
                rep     #M_FLAG
                .a16
.endmacro

; Resets the X bit making the index registers 16-bits wide

.macro          long_i
                rep     #X_FLAG
                .i16
.endmacro

; Resets the M and X bits making the accumulator, memory accesses and index
; registers 16-bits wide.
                
.macro          long_ai
                rep     #M_FLAG|X_FLAG
                .a16
                .i16
.endmacro

; Sets the M bit making the accumulator and memory accesses 8-bits wide.

.macro          short_a
                sep     #M_FLAG
                .a8
.endmacro

; Sets the X bit making the index registers 8-bits wide.

.macro          short_i
                sep     #X_FLAG
                .i8
.endmacro
                
; Sets the M & X bits making the accumulator, memory accesses and index
; registers 8-bits wide.

.macro          short_ai
                sep     #M_FLAG|X_FLAG
                .a8
                .i8
.endmacro
