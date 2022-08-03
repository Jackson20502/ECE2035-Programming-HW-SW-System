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
# ===========================================================================

.data
Array:  .alloc	1024

.text
FindGeorge:	addi	$1, $0, Array		# point to array base
		swi	570			# generate tumbling crowd

# ***************************************************************************

	addi	$10, $0, 1		#color white
	addi	$11, $0, 2		#color red
	addi	$12, $0, 3		#color blue
	addi	$13, $0, 5		#color yellow
	addi	$14, $0, 7		#color green
	addi	$15, $0, 8		#color black

	addi	$2, $0, 0		#location tracker
	addi	$3, $0, 0		#Loop counter
	addi	$4, $0, 0		#Big counter	

BLoop:	lb	$5, Array($4)
	slti	$5, $5, 3
	beq	$5, $0, Back2
	
	addi 	$3, $4, -3
	addi	$4, $4, 4

Loop:	lbu	$5, Array($3)
	bne	$5, $10, Back

	add	$6, $1, $3		#keep address

Up:	slti	$5, $3, 3392		#check if out of bound
	beq	$5, $0, Down

	lbu	$5, 192($6)		#check 5 elements in relation to the first element
	bne	$5, $11, Down		#see if it is facing Up else, go to down
	lbu	$5, 256($6)
	bne	$5, $13, Down
	lbu	$5, 512($6)
	bne	$5, $15, Back
	lbu	$5, 254($6)
	bne	$5, $14, Back
	lbu	$5, 704($6)
	bne	$5, $12, Back

	sll	$2, $3, 16		#store head address
	addi	$5, $3, 704
	or	$2, $2, $5		#store shirt address
	j	Exit
	
Down:	slti	$5, $3, 704		#check if out of bound
	bne	$5, $0, Left

	lbu	$5, -192($6)		#check 5 elements in relation to the first element
	bne	$5, $11, Left		#see if it is facing Down else, go to Down
	lbu	$5, -256($6)
	bne	$5, $13, Left
	lbu	$5, -512($6)
	bne	$5, $15, Back
	lbu	$5, -254($6)
	bne	$5, $14, Back
	lbu	$5, -704($6)
	bne	$5, $12, Back

	sll	$2, $3, 16		#store head address
	addi	$5, $3, -704
	or	$2, $2, $5		#store shirt address
	j	Exit


Left:	lbu	$5, 3($6)		#check 5 elements in relation to the first element
	bne	$5, $11, Right		#see if it is facing Left else, go to Right
	lbu	$5, 4($6)
	bne	$5, $13, Right
	lbu	$5, 8($6)
	bne	$5, $15, Back
	lbu	$5, 132($6)
	bne	$5, $14, Back
	lbu	$5, 11($6)
	bne	$5, $12, Back

	sll	$2, $3, 16		#store head address
	addi	$5, $3, 11
	or	$2, $2, $5		#store shirt address
	j	Exit


Right:	lbu	$5, -3($6)		#check 5 elements in relation to the first element
	bne	$5, $11, Back		#see if it is facing Right else, go to Back
	lbu	$5, -4($6)
	bne	$5, $13, Back
	lbu	$5, -8($6)
	bne	$5, $15, Back
	lbu	$5, -132($6)
	bne	$5, $14, Back
	lbu	$5, -11($6)
	bne	$5, $12, Back

	sll	$2, $3, 16		#store head address
	addi	$5, $3, -11
	or	$2, $2, $5		#store shirt address
	j	Exit

Back:	addi	$2, $3, 0
	swi	552
	addi	$3, $3, 1		#increment loop counter
	
	beq	$3, $4, BLoop
	j	Loop			#jump back to loop

Back2: 	addi	$4, $4, 4
	j	BLoop
	
Exit:	swi	571			# submit answer and check, oracle returns correct answer in $3
	jr	$31			# return to caller
