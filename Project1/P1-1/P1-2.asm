# =================================================================
# Copyright 2022 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================
#     F i n d  T u m b l i n g G e o r g e  i n  a  C r o w d
#
# P1-2
# Student Name: Bozhou Lu
# Date: 02/25/2022
#
# This routine finds an exact match of George's face which may be
# rotated in a crowd of tumbling (rotated) faces.
#
# ===========================================================================
# CHANGE LOG: brief description of changes made from P1-2-shell.asm
# to this version of code.
# Date  Modification
# 02/22 Create Loop that loops through all the elements in the array
# 02/23 Wrote code that look at 5 elements to check if the face matches
# 02/25 Modified the code, which gives some correct answers, but sometimes find
# index out of bound
# 02/25 Modified the code, solved the outofbound problem, execute correctly, 
# but still lack of efficiency
# 02/26 Increase the efficiency by incrementing counter by 4 each time
# 02/26 Increase the efficiency by incrementing counter by 7 times, change
# checking the face through a black pixel
# 02/26 Finalizing the code,result: 90 SI, around 3000-4000 SI, and 12 registers
# ===========================================================================

.data
Array:  .alloc	1024

.text
FindGeorge:	addi	$1, $0, Array		# point to array base
		swi	570			# generate tumbling crowd

# ***************************************************************************

	addi	$10, $0, 1		# color white
	addi	$11, $0, 2		# color red
	addi	$12, $0, 3		# color blue
	addi	$13, $0, 5		# color yellow
	addi	$14, $0, 7		# color green
	addi	$15, $0, 8		# color black

	addi	$2, $0, 0		# Location tracker
	addi	$3, $0, 0		# Loop counter
	addi	$4, $0, 197		# Big counter	

BLoop:	lb	$5, Array($4)		# Load the checking big loop pixel
	beq	$5, $13, Cont		# Increment counter if the pixel isn't black or yellow
	bne	$5, $15, Back2

Cont:	addi 	$3, $4, -4		# Set the initial small loop checker
	addi	$4, $4, 4		# Set the stopping thresh hole

Loop:	lbu	$5, Array($3)		# Loop through each byte to see if matches the face
	bne	$5, $15, Back		# If small looping pixel is not black, go to Back

	add	$6, $1, $3		# keep address

Left:	lbu	$5, 3($6)		# check 5 elements in relation to the first black small loop pixel
	bne	$5, $12, Right		# see if it is facing Left else, go to Right
	lbu	$5, -4($6)
	bne	$5, $13, Right
	lbu	$5, -132($6)
	bne	$5, $14, Back
	lbu	$5, -5($6)
	bne	$5, $11, Back
	lbu	$5, -8($6)
	bne	$5, $10, Back

	addi	$5, $3, -8
	sll	$2, $5, 16		# store head address
	addi	$5, $5, 11
	or	$2, $2, $5		# store shirt address
	j	Exit


Right:	lbu	$5, -3($6)		# check 5 elements in relation to the first black small loop pixel
	bne	$5, $12, Down		# see if it is facing Right else, go to Down
	lbu	$5, 4($6)
	bne	$5, $13, Down
	lbu	$5, 132($6)
	bne	$5, $14, Back
	lbu	$5, 5($6)
	bne	$5, $11, Back
	lbu	$5, 8($6)
	bne	$5, $10, Back

	addi	$5, $3, 8
	sll	$2, $5, 16		# store head address
	addi	$5, $5, -11
	or	$2, $2, $5		# store shirt address
	j	Exit


Down:	lbu	$5, -192($6)		# check 5 elements in relation to the first black small loop pixel
	bne	$5, $12, Up		# see if it is facing Down else, go to Up
	lbu	$5, 256($6)
	bne	$5, $13, Up
	lbu	$5, 254($6)
	bne	$5, $14, Back
	lbu	$5, 320($6)
	bne	$5, $11, Back
	lbu	$5, 512($6)
	bne	$5, $10, Back

	addi	$5, $3, 512
	sll	$2, $5, 16		# store head address
	addi	$5, $5, -704
	or	$2, $2, $5		# store shirt address
	j	Exit

Up:	lbu	$5, 192($6)		# check 5 elements in relation to the first black small loop pixel
	bne	$5, $12, Back		# see if it is facing Up else, go to Back

	slti	$5, $3, 512		# see if the pixel can be out of bound
	bne	$5, $0, Back

	lbu	$5, -256($6)
	bne	$5, $13, Back
	lbu	$5, -254($6)
	bne	$5, $14, Back
	lbu	$5, -320($6)
	bne	$5, $11, Back
	lbu	$5, -512($6)
	bne	$5, $10, Back

	addi	$5, $3, -512
	sll	$2, $5, 16		# store head address
	addi	$5, $5, 704
	or	$2, $2, $5		# store shirt address
	j	Exit


Back:	beq	$3, $4, Back3
	addi	$3, $3, 1		# increment small loop counter	
	j	Loop			# jump back to loop

Back2: 	addi	$4, $4, 7		# increment big loop counter
	j	BLoop

Back3:	addi	$4, $4, 3		# increment big loop counter if big loop pixel is black
	j	BLoop

Exit:	swi	571			# submit answer and check, oracle returns correct answer in $3
	jr	$31			# return to caller
