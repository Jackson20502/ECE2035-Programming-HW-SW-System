#=================================================================
# Copyright 2022 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================
#
# HW1-3
# Student Name: Jiacheng Zhang
# Date: 01/21/2022
#
# This program computes the next integer in a given sequence of integers and
# writes it to memory location labeled Result.  The sequence might be an
# arithmetic or geometric sequence.

# NOTE:
# The program should work on multiple test cases, not just the one provided.
# For full credit, be sure to document your code.

.data
# DO NOT change the following labels (you may only change the initial values):
LAddr:    .word  4
Seq:        .word  -6, 6, 18, 30
#  Seq:      .word  1, -3, 9, -27
#  Seq:      .word  -2, -4, -6, -8
Result:    .alloc 1
	
.text
                                                                          # write your code here...
addi $26, $0, -1
addi $26, $26, 1

                   lw  $1, LAddr($0)                            #  $1  holds the length of the sequence, which is 4
                   addi  $2, $0, Seq                             #  $2  holds addr of first word in Seq 
                   lw  $3, 0($2)                                    #  read 1st word into $3 ($3<-Mem[Seq+0])
                   lw  $4, 4($2)                                    #  read 2nd word into $4 ($4<-Mem[Seq+4])
                   lw  $5, 8($2)                                    #  read 3rd word into $5 ($5<-Mem[Seq+8])
                   lw  $6, 12($2)                                  #  read 4th word into $6 ($6<-Mem[Seq+12])
                   sub  $7, $4, $3                                #  $7 = $4 - $3
                   sub  $8, $5, $4                                #  $8 = $5 - $4
                   add  $10, $0, $0                              #  initialize $10
                   beq  $7, $8, arithmetic                    #  if $7 = $8, go to arithmetic
                   div  $4, $3                                       #  Lo = $4 / $3, Hi = $4 mod $3
                   mfhi  $9                                           #  transfer remainder to $9
                   mflo  $10                                         #  transfer quotient to $10
                   div  $5, $4                                       #  Lo = $5 / $4, Hi = $5 mod $4
                   mfhi  $11                                         #  transfer remainder to $11
                   mflo  $12                                         #  transfer quotient to $12
                   bne  $9, $0, exception                     #  if $9 != $0, go to exception
                   bne  $11, $0, exception                   #  if $11 != $0, go to exception
                   beq  $10, $12, geometric                #  if $10 = $12, go to geometric    

arithmetic:  add  $20, $6, $7                              #  $20 = $6 + $7
                   sw  $20, Result($0)                          #  store Result to $20  

geometric:  mult  $6, $10                                   #  Hi, Lo = $6 * $10
                   mflo  $13                                         #  transfer product to $13
                   add   $21, $0, $13                           #  $21 = $0 + $13
                   sw  $21, Result($0)                          #  store Result to $21 

exception:   add   $22, $0, $0                             #  exception

                   jr $31                                               #  return to OS


