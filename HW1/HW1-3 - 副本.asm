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
M: .word 0xEFABCD89
.text
addi $1, $0, M
lbu $2, 2($1)
lb    $3, 3($1)

                   jr $31                                               #  return to OS



