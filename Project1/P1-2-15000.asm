#=================================================================
# Copyright 2022 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================
#     F i n d  T u m b l i n g G e o r g e  i n  a  C r o w d
#
# P1-2
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

                addi  $4, $0, 0                        # i = 0
                addi  $5, $0, 1                        # white
                addi  $6, $0, 3                        # blue
                addi  $7, $0, 2                        # red
                addi  $8, $0, 7                        # green
                addi  $9, $0, 5                        # yellow
                addi  $10, $0, 8                      # black
                
       
Loop:       slti      $11, $4, 3764               # if i < 3764, $11 = 1 else 0
                beq    $11, $0, Exit                 # if $11 = 0, Exit           
                lbu     $11, Array($4)              # check if the first pixel is blue or white
                beq    $11, $6, ElseIf0             # is blue, go to ElseIf0
                beq    $11, $5, ElseIf1             # is white, go to ElseIf1
                j         Inc                                # jump to Inc

ElseIf0:     add    $3, $1, $4                     # store the address of the first equivalent pixel, Rot90

                
                lbu     $12, 11($3)                   # $12 = mem[Array + i + 11]
                bne    $12, $5, ElseIf2             # not white, go to ElseIf2
               # lbu     $12, -53($3)                 # $12 = mem[Array + i - 53]
               # bne    $12, $5, Inc                   # not white, go to Inc
               # lbu     $12, 75($3)                   # $12 = mem[Array + i + 75]
               # bne    $12, $5, Inc                   # not white, go to Inc

                lbu     $12, 133($3)               # $12 = mem[Array + i + 133]
                bne    $12, $10, Inc            # not black, go to Inc12
                lbu     $12, 134($3)               # $12 = mem[Array + i + 134]
                bne    $12, $9, Inc              # not yellow, go to Inc12
                lbu     $12, 135($3)               # $12 = mem[Array + i + 135]
                bne    $12, $8, Inc              # not green, go to Inc12
                lbu     $12, 136($3)               # $12 = mem[Array + i + 136]
                bne    $12, $7, Inc              # not red, go to Inc12

                addi   $28, $4, 0                     # the location of blue
                addi   $27, $4, 11                   # the location of white
               

                j         Exit

ElseIf1:     add    $3, $1, $4                     # store the address of the first equivalent pixel, Rot270

                
                lbu     $12, 11($3)                   # $12 = mem[Array + i + 11]
                bne    $12, $6, ElseIf3             # not blue, go to ElseIf3

               # lbu     $12, -64($3)                 # $12 = mem[Array + i - 64]
               # bne    $12, $5, Inc                   # not white, go to Inc
               # lbu     $12, 64($3)                   # $12 = mem[Array + i + 64]
               # bne    $12, $5, Inc                   # not white, go to Inc

                lbu     $12, 131($3)               # $12 = mem[Array + i + 131]
                bne    $12, $7, Inc              # not red, go to Inc12
                lbu     $12, 132($3)               # $12 = mem[Array + i + 132]
                bne    $12, $8, Inc              # not green, go to Inc12
                lbu     $12, 133($3)               # $12 = mem[Array + i + 133]
                bne    $12, $9, Inc              # not yellow, go to Inc12
                lbu     $12, 134($3)               # $12 = mem[Array + i + 134]
                bne    $12, $10, Inc            # not black, go to Inc12

                addi   $28, $4, 11                   # the location of blue
                addi   $27, $4, 0                     # the location of white


                j         Exit

ElseIf2:     slti      $11, $4, 3386               # if i < 3386, $11 = 1 else 0, Rot180
                beq    $11, $0, Inc                  # if $11 = 0, Inc

               # add    $3, $1, $4                     # store the address of the first equivalent pixel

                lbu     $12, 704($3)                # $12 = mem[Array + i + 704]
                bne    $12, $5, Inc                  # not white, go to Inc
               # lbu     $12, 703($3)                # $12 = mem[Array + i + 703]
               # bne    $12, $5, Inc                  # not white, go to Inc
               # lbu     $12, 705($3)                # $12 = mem[Array + i + 705]
               # bne    $12, $5, Inc                  # not white, go to Inc

                lbu     $12, 322($3)                # $12 = mem[Array + i + 322]
                bne    $12, $10, Inc            # not black, go to Inc11
                lbu     $12, 386($3)                # $12 = mem[Array + i + 386]
                bne    $12, $9, Inc              # not yellow, go to Inc11
                lbu     $12, 450($3)                # $12 = mem[Array + i + 450]
                bne    $12, $8, Inc              # not green, go to Inc11
                lbu     $12, 514($3)                # $12 = mem[Array + i + 514]
                bne    $12, $7, Inc              # not red, go to Inc11

                addi   $28, $4, 0                     # the location of blue
                addi   $27, $4, 704                 # the location of white

                j         Exit

ElseIf3:     slti      $11, $4, 3386               # if i < 3386, $11 = 1 else 0, Upright
                beq    $11, $0, Inc                  # if $11 = 0, Inc

               # add    $3, $1, $4                     # store the address of the first equivalent pixel

                lbu     $12, 704($3)                # $12 = mem[Array + i + 704] 
                bne    $12, $6, Inc                  # not blue, go to Inc

               # lbu     $12, -1($3)                   # $12 = mem[Array + i - 1]
               # bne    $12, $5, Inc                  # not white, go to Inc
               # lbu     $12, 1($3)                    # $12 = mem[Array + i + 1]
               # bne    $12, $5, Inc                  # not white, go to Inc

                lbu     $12, 194($3)                # $12 = mem[Array + i + 194]
                bne    $12, $7, Inc              # not red, go to Inc11
                lbu     $12, 258($3)                # $12 = mem[Array + i + 258]
                bne    $12, $8, Inc              # not green, go to Inc11
                lbu     $12, 322($3)                # $12 = mem[Array + i + 322]
                bne    $12, $9, Inc              # not yellow, go to Inc11
                lbu     $12, 386($3)                # $12 = mem[Array + i + 386]
                bne    $12, $10, Inc            # not black, go to Inc11

                addi   $28, $4, 704                 # the location of blue
                addi   $27, $4, 0                     # the location of white


                j         Exit
                
Inc:          addi   $4, $4, 1                       # i = i + 1
                j         Loop                            # jump to Loop

Inc11:      addi   $4, $4, 11                     # i = i + 11
                j         Loop                            # jump to Loop

Inc12:      addi   $4, $4, 12                     # i = i + 12
                j         Loop                            # jump to Loop

Exit:          addu $2, $0, $27                   # add location of hat to $2
                sll      $2, $2, 16                     # move to upper 16 bits
                or      $2, $2, $28                   # add location of shirt to $2
	
 	swi	571	              # submit answer and check
		                              # oracle returns correct answer in $3

	jr	$31	              # return to caller
