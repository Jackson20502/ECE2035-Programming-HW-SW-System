#=================================================================
# Copyright 2022 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================
#
# HW1-3
# Student Name:
# Date:
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
Seq:      .word  -6, 6, 18, 30
Result:   .alloc 1
	
.text
                # write your code here...

                jr $31   # return to OS


