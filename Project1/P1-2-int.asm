#=================================================================
# Copyright 2022 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================
#     F i n d  T u m b l i n g G e o r g e  i n  a  C r o w d
#
# P1-2-int
# Student Name: Jiacheng Zhang
# Date: 02/23/2022
#
# This routine finds an exact match of George's face which may be
# rotated in a crowd of tumbling (rotated) faces.
#
#===========================================================================
# CHANGE LOG: brief description of changes made from P1-2-shell.asm
# to this version of code.
# Date  Modification
# 02/23 The program is able to return the correct result to $2, 
#            but the dynamic instruction length is too long.
#===========================================================================

.data
Array:  .alloc	1024

.text

FindGeorge:	addi	$1, $0, Array		# point to array base
		swi	570			# generate tumbling crowd

# ***************************************************************************
	# SWI 552 is useful for debugging. Remove calls to it in
	# final program submission.
	# TEMP: remove the lines between **********
                addi    $2, $0, 160             # TEMP: mark the 160th pixel
		swi	552			# TEMP: with this swi
                addi    $2, $0, 161             # TEMP: mark the 161th pixel
		swi	552			# TEMP: with this swi
# ***************************************************************************
	
	# your code goes here
	# pack hat/shirt locations into $2 and report your answer

                addi  $4, $0, 0                   # i = 0
                addi  $5, $0, 1                   # white
                addi  $6, $0, 3                   # blue
                addi  $7, $0, 2                   # red
                addi  $8, $0, 7                   # green
                addi  $9, $0, 5                   # yellow
                addi  $10, $0, 8                 # black
                
Loop:       slti      $11, $4, 4084               # if i < 4084, $11 = 1 else 0
                beq    $11, $0, Exit                 # if $11 = 0, Exit
                addi   $11, $4, 0                     # $11: i 
                lbu     $12, Array($11)            # $12 = mem[Array + i]
                bne    $12, $6, ElseIf1             # not blue, go to ElseIf1
                addi   $28, $11, 0                   # the location of blue
                addi   $11, $4, 11                   # $11: i + 11
                lbu     $12, Array($11)            # $12 = mem[Array + i + 11]
                bne    $12, $5, ElseIf1             # not white, go to ElseIf1
                addi   $27, $11, 0                   # the location of white
                addiu $11, $4, -123                # $11: i - 123
                lbu     $12, Array($11)            # $12 = mem[Array + i - 123]
                bne    $12, $10, ElseIf1           # not black, go to ElseIf1
                addiu $11, $4, -122                # $11: i - 122
                lbu     $12, Array($11)            # $12 = mem[Array + i - 122]
                bne    $12, $9, ElseIf1             # not yellow, go to ElseIf1
                addiu $11, $4, -121                # $11: i - 121
                lbu     $12, Array($11)            # $12 = mem[Array + i - 121]
                bne    $12, $8, ElseIf1             # not green, go to ElseIf1
                addiu $11, $4, -120                # $11: i - 120
                lbu     $12, Array($11)            # $12 = mem[Array + i - 120]
                bne    $12, $7, ElseIf1             # not red, go to ElseIf1
                j         Exit

ElseIf1:     addi   $11, $4, 0                     # $11: i
                lbu     $12, Array($11)            # $12 = mem[Array + i]
                bne    $12, $5, ElseIf2             # not white, go to ElseIf2
                addi   $27, $11, 0                   # the location of white
                addi   $11, $4, 11                   # $11: i + 11
                lbu     $12, Array($11)            # $12 = mem[Array + i + 11]
                bne    $12, $6, ElseIf2             # not blue, go to ElseIf2
                addi   $28, $11, 0                   # the location of blue
                addiu $11, $4, -125                # $11: i - 125
                lbu     $12, Array($11)            # $12 = mem[Array + i - 125]
                bne    $12, $7, ElseIf2             # not red, go to ElseIf2
                addiu $11, $4, -124                # $11: i - 124
                lbu     $12, Array($11)            # $12 = mem[Array + i - 124]
                bne    $12, $8, ElseIf2             # not green, go to ElseIf2
                addiu $11, $4, -123                # $11: i - 123
                lbu     $12, Array($11)            # $12 = mem[Array + i - 123]
                bne    $12, $9, ElseIf2             # not yellow, go to ElseIf2
                addiu $11, $4, -122                # $11: i - 122
                lbu     $12, Array($11)            # $12 = mem[Array + i - 122]
                bne    $12, $10, ElseIf2           # not black, go to ElseIf2
                j         Exit

ElseIf2:     addi   $11, $4, 0                     # $11: i
                lbu     $12, Array($11)            # $12 = mem[Array + i]
                bne    $12, $6, ElseIf3             # not blue, go to ElseIf3
                addi   $28, $11, 0                   # the location of blue
                addi   $11, $4, 704                 # $11: i + 704
                lbu     $12, Array($11)            # $12 = mem[Array + i + 704]
                bne    $12, $5, ElseIf3             # not white, go to ElseIf3
                addi   $27, $11, 0                   # the location of white
                addi   $11, $4, 322                 # $11: i + 322
                lbu     $12, Array($11)            # $12 = mem[Array + i + 322]
                bne    $12, $10, ElseIf3           # not black, go to ElseIf3
                addi   $11, $4, 386                 # $11: i + 386
                lbu     $12, Array($11)            # $12 = mem[Array + i + 386]
                bne    $12, $9, ElseIf3             # not yellow, go to ElseIf3
                addi   $11, $4, 450                 # $11: i + 450
                lbu     $12, Array($11)            # $12 = mem[Array + i + 450]
                bne    $12, $8, ElseIf3             # not green, go to ElseIf3
                addi   $11, $4, 514                 # $11: i + 514
                lbu     $12, Array($11)            # $12 = mem[Array + i + 514]
                bne    $12, $7, ElseIf3             # not red, go to ElseIf3
                j         Exit

ElseIf3:     addi   $11, $4, 0                     # $11: i
                lbu     $12, Array($11)            # $12 = mem[Array + i]
                bne    $12, $5, Inc                  # not white, go to Inc
                addi   $27, $11, 0                   # the location of white
                addi   $11, $4, 704                 # $11: i + 704
                lbu     $12, Array($11)            # $12 = mem[Array + i + 704]
                bne    $12, $6, Inc                  # not blue, go to Inc
                addi   $28, $11, 0                   # the location of blue
                addi   $11, $4, 194                 # $11: i + 194
                lbu     $12, Array($11)            # $12 = mem[Array + i + 194]
                bne    $12, $7, Inc                  # not red, go to Inc
                addi   $11, $4, 258                 # $11: i + 258
                lbu     $12, Array($11)            # $12 = mem[Array + i + 258]
                bne    $12, $8, Inc                  # not green, go to Inc
                addi   $11, $4, 322                 # $11: i + 322
                lbu     $12, Array($11)            # $12 = mem[Array + i + 322]
                bne    $12, $9, Inc                  # not yellow, go to Inc
                addi   $11, $4, 386                 # $11: i + 386
                lbu     $12, Array($11)            # $12 = mem[Array + i + 386]
                bne    $12, $10, Inc                # not black, go to Inc
                j         Exit
                
Inc:          addi   $4, $4, 1                       # i = i + 1
                j         Loop                            # jump to Loop
  
# ***************************************************************************
	# TEMP: replace these lines to pack locations properly and report answer

Exit: 	addu $2, $0, $27                     # add location of hat to $2
                sll      $2, $2, 16                       # move to upper 16 bits
	or      $2, $2, $28                     # add location of shirt to $2
# ***************************************************************************
	
		swi	571			# submit answer and check
		# oracle returns correct answer in $3

		jr	$31			# return to caller
