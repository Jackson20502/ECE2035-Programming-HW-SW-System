#=================================================================
# Copyright 2022 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================

#     Intensity Matcher
#
# Your Name:	
# Date:
#
# This program finds the two colors with the closest intensity
# in an eight color palette.
#
#  required output register usage:
#  $10: MinDelta, $11: Color A address, $12: Color B address
#	
#  result must be reported by calling: swi 581

.data
Array:  .alloc  8               # allocate static space for packed color data

.text
IntensityMatch: addi  $1, $0, Array     # set memory base
                swi   589               # create color palette and update memory
		addi  $10, $0, 42	# TEMP: report MinDelta   REPLACE THIS
		addi  $11, $1, 4	# TEMP: report an address REPLACE THIS
		addi  $12, $1, 12	# TEMP: report an address REPLACE THIS
		swi     581
                jr      $31             # return to caller
