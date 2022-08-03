#=================================================================
# Copyright 2022 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================

#     Intensity Matcher
#
# Your Name: Jiacheng Zhang
# Date: 01/30/2022
#
# This program finds the two colors with the closest intensity
# in an eight color palette.
#
#  required output register usage:
#  $10: MinDelta, $11: Color A address, $12: Color B address
#	
#  result must be reported by calling: swi 581

.data
Array:  .alloc  8                                       # allocate static space for packed color data

.text
IntensityMatch: addi  $1, $0, Array        # set memory base
                         swi   589                       # create color palette and update memory
                         addi  $28, $0, 3

                         lbu   $2, 0($1)               # Color 1
                         lbu   $3, 1($1)
                         lbu   $4, 2($1)               # Load the RGB conponents of color 1
                         add  $5, $2, $3
                         add  $6, $4, $5             # Get the sum of three conponents
                         divu  $6, $28
                         mflo  $2                        # Get the intensity of color 1
                         sw   $2, 1000($0)          # Store the intensity to mem[1000]
                         
                         lbu   $3, 4($1)               # Color 2
                         lbu   $4, 5($1)
                         lbu   $5, 6($1)               # Load the RGB conponents of color 2
                         add  $6, $3, $4
                         add  $7, $5, $6             # Get the sum of three conponents
                         divu  $7, $28
                         mflo  $3                        # Get the intensity of color 2
                         sw   $3, 1004($0)          # Store the intensity to mem[1004]

                         lbu   $4, 8($1)                # Color 3
                         lbu   $5, 9($1)
                         lbu   $6, 10($1)              # Load the RGB conponents of color 3
                         add  $7, $4, $5
                         add  $8, $6, $7               # Get the sum of three conponents
                         divu  $8, $28
                         mflo  $4                          # Get the intensity of color 3
                         sw   $4, 1008($0)            # Store the intensity to mem[1008]

                         lbu   $5, 12($1)               # Color 4
                         lbu   $6, 13($1)
                         lbu   $7, 14($1)               # Load the RGB conponents of color 4
                         add  $8, $5, $6
                         add  $9, $7, $8               # Get the sum of three conponents
                         divu  $9, $28
                         mflo  $5                          # Get the intensity of color 4
                         sw   $5, 1012($0)            # Store the intensity to mem[1012]

                         lbu   $6, 16($1)               # Color 5
                         lbu   $7, 17($1)
                         lbu   $8, 18($1)               # Load the RGB conponents of color 5
                         add  $9, $6, $7
                         add  $13, $8, $9             # Get the sum of three conponents
                         divu  $13, $28
                         mflo  $6                          # Get the intensity of color 5
                         sw   $6, 1016($0)            # Store the intensity to mem[1016]

                         lbu   $7, 20($1)               # Color 6
                         lbu   $8, 21($1)
                         lbu   $9, 22($1)               # Load the RGB conponents of color 6
                         add  $13, $7, $8
                         add  $14, $9, $13            # Get the sum of three conponents
                         divu  $14, $28
                         mflo  $7                           # Get the intensity of color 6
                         sw   $7, 1020($0)             # Store the intensity to mem[1020]

                         lbu   $13, 24($1)              # Color 7
                         lbu   $14, 25($1)
                         lbu   $15, 26($1)              # Load the RGB conponents of color 7
                         add  $16, $13, $14
                         add  $17, $15, $16          # Get the sum of three conponents
                         divu  $17, $28
                         mflo  $8                           # Get the intensity of color 7
                         sw   $8, 1024($0)             # Store the intensity to mem[1024]

                         lbu   $16, 28($1)              # Color 8
                         lbu   $17, 29($1)
                         lbu   $18, 30($1)              # Load the RGB conponents of color 8
                         add  $19, $16, $17
                         add  $20, $18, $19          # Get the sum of three conponents
                         divu  $20, $28
                         mflo  $9                          # Get the intensity of color 8
                         sw   $9, 1028($0)            # Store the intensity to mem[1028]

                         addi  $2, $0, 255            # MinDelta = 255
                         addi  $3, $0, 0                # temp = 0
                         addi  $4, $0, 0                # i = 0
                         addi  $20, $0, 0              # tempAddressA = 0
                         addi  $21, $0, 0              # tempAddressB = 0
                         
#                         addi  $6, $0, 28              # Loop limit for the outer loop = 28
#                         addi  $7, $0, 32              # Loop limit for the inner loop = 32

OuterLoop:       slti    $6, $4, 28               # If $4 < 28, $6 = 1 else $6 = 0
                         beq  $6, $0, Leave          # If $6 = 0($4 >= 28), then Leave
                         lw     $8, 1000($4)          # Load the intensity of a color stored in the mem[1000+$4] previously
                         addi  $5, $4, 4                # j = i + 4
                         j        InnerLoop              # Jump to InnerLoop

InnerLoop:        slti    $7, $5, 32               # If $5 < 32, $7 = 1 else $7 = 0
                         beq  $7, $0, SkipSumi     # If $7 = 0($5 >= 32), then SkipSumi
                         lw     $9, 1000($5)           # Load the intensity of a color stored in the mem[1000+$5] previously
                         sub   $3, $8, $9               # Get the value of MinDelta

                         sra    $22, $3, 31             # Get the absolute value of MinDelta
                         xor    $3, $3, $22             # Flip all bits in $3
                         sub   $3, $3, $22             # $3 = $3 - (-1)

                         slt     $13, $3, $2              # If $3 < $2, $13 = 1 else $13 = 0
                         bne  $13, $0, SwapMin   # If $13 != 0($3 >= $2), then SwapMin
                         j        SkipSumj                # Jump to SkipSumj

SkipSumi:         addi  $4, $4, 4                 # Outer loop counter
                         j         OuterLoop            # Jump to OuterLoop

SkipSumj:         addi  $5, $5, 4                 # Inner loop counter
                         j         InnerLoop             # Jump to InnerLoop

SwapMin:         add   $2, $0, $3               # If temp < MinDelta, then MinDelta = temp
                         add   $20, $0, $4            # Store the first matched color's address counter to $20
                         add   $21, $0, $5            # Store the second matched color's address counter to $20
                         j        SkipSumj               # Jump to SkipSumj       

Leave:               add   $10, $0, $2	# TEMP: report MinDelta   REPLACE THIS
                         add   $11, $1, $20	# TEMP: report an address REPLACE THIS
                         add   $12, $1, $21	# TEMP: report an address REPLACE THIS

                         swi     581
                         jr      $31             # return to caller
