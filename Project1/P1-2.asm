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
# Date: 03/03/2022
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
# 02/27 Reduce the dynamic instruction length from 50000 to 15000
#            by changing the way of getting the load byte's address.
# 03/01 Reduce the dynamic instruction length from 15000 to 4000 by
#            skipping some specific combinations of pixels during the pixel pairing.
# 03/03 Avoid the "address[...] read before define" error by changing the pixel
#            pairing order. 
#===========================================================================

.data
Array:  .alloc	1024

.text

FindGeorge:	addi	$1, $0, Array		# point to array base
		swi	570			# generate tumbling crowd

		addi  	$3, $0, 0	               		# j = 0
                	addi  	$4, $0, 197                   	# i = 197
               	 	addi  	$5, $0, 1                        	# white
                	addi  	$6, $0, 3                       	# blue
                	addi  	$7, $0, 2                        	# red
                	addi  	$8, $0, 7                        	# green
                	addi  	$9, $0, 5                        	# yellow
                	addi  	$10, $0, 8                      	# black
       
Loop1:     	lbu     	$11, Array($4)               	# check the color of the first pixel
                	beq    	$11, $9, EdgeChecker              # is yellow, set the EdgeChecker
                	bne    	$11, $10, Inc7               	# not black, jump 7 pixels

EdgeChecker:      	addi  	$3, $4, -4                       	# Locate the (i - 4) pixel
		addi  	$4, $4, 4                         	# Locate the (i + 4) pixel

Loop2:     	lbu    	$11, Array($3)                	# $11 = mem[Array + j - 4]
                	bne   	$11, $10, Inc2                  	# not black, go to Inc2

Rot90:      	add    	$13, $1, $3                    	# store the address of the black pixel
 
                	lbu     	$12, -3($13)                   	# $12 = mem[Array + j - 3]
                	bne    	$12, $6, Rot270             	# not blue, go to Rot270
                	lbu     	$12, 130($13)                	# $12 = mem[Array + j + 130]
                	bne    	$12, $10, Rot270           	# not black, go to Rot270
                	lbu     	$12, 131($13)                	# $12 = mem[Array + j + 131]
                	bne    	$12, $9, Inc2                    	# not yellow, go to Inc2
                	lbu     	$12, 132($13)                	# $12 = mem[Array + j + 132]
                	bne    	$12, $8, Inc2                    	# not green, go to Inc2
                	lbu     	$12, 133($13)                	# $12 = mem[Array + j + 133]
                	bne    	$12, $7, Inc2                   	# not red, go to Inc2
                	lbu     	$12, 8($13)                    	# $12 = mem[Array + j + 8]
                	bne    	$12, $5, Inc2                    	# not white, go to Inc2

                	addiu 	$28, $3, -3                     	# the location of blue
                	addi   	$27, $3, 8                      	# the location of white
               
                	j         	Exit

Rot270:    	add    	$13, $1, $3                    	# store the address of the black pixel
        
                	lbu     	$12, 3($13)                   	# $12 = mem[Array + j + 3]
                	bne    	$12, $6, Rot180            	#  not blue, go to Rot180
                	lbu     	$12, -130($13)              	# $12 = mem[Array + j + 130]
                	bne    	$12, $10, Rot180          	# not black, go to Rot180
                	lbu     	$12, -131($13)              	# $12 = mem[Array + j - 131]
                	bne    	$12, $9, Inc2                   	# not yellow, go to Inc2
                	lbu     	$12, -132($13)              	# $12 = mem[Array + j - 132]
                	bne    	$12, $8, Inc2                   	# not green, go to Inc2
                	lbu     	$12, -133($13)              	# $12 = mem[Array + j - 133]
                	bne    	$12, $7, Inc2                   	# not red, go to Inc2
                	lbu     	$12, -8($13)                  	# $12 = mem[Array + j - 8]
                	bne    	$12, $5, Inc2                   	# not white, go to Inc2

                	addi   	$28, $3, 3                     	# the location of blue
                	addiu 	$27, $3, -8                   	# the location of white
               
                	j         	Exit

Rot180:   		add    	$13, $1, $3                    	# store the address of the black pixel
        
                	lbu     	$12, -192($13)              	# $12 = mem[Array + j - 192]
               		bne    	$12, $6, Upright            	# not blue, go to Upright
                	lbu     	$12, 126($13)                	# $12 = mem[Array + j + 126]
                	bne    	$12, $10, Upright          	# not black, go to Upright
                	lbu     	$12, 190($13)                	# $12 = mem[Array + j + 190]
                	bne    	$12, $9, Inc2                    	# not yellow, go to Inc2
                	lbu     	$12, 254($13)                	# $12 = mem[Array + j + 254]
                	bne    	$12, $8, Inc2                    	# not green, go to Inc2
                	lbu     	$12, 318($13)                	# $12 = mem[Array + j + 318]
                	bne    	$12, $7, Inc2                    	# not red, go to Inc2
                	lbu     	$12, 512($13)                	# $12 = mem[Array + j + 512]
                	bne    	$12, $5, Inc2                    	# not white, go to Inc2
                
                	addiu 	$28, $3, -192                 	# the location of blue
                	addi   	$27, $3, 512                  	# the location of white
               
               		j         	Exit

Upright:   	add    	$13, $1, $3                    	# store the address of the black pixel
        
                	lbu     	$12, 192($13)                	# $12 = mem[Array + j + 192]
                	bne    	$12, $6, Inc2                    	# not blue, go to Inc2
                	lbu     	$12, -126($13)               	# $12 = mem[Array + j - 126]
                	bne    	$12, $10, Inc2                  	# not black, go to Inc2
                	lbu     	$12, -190($13)               	# $12 = mem[Array + j - 190]
                	bne    	$12, $9, Inc2                    	# not yellow, go to Inc2
                	lbu     	$12, -254($13)               	# $12 = mem[Array + j - 254]
                	bne    	$12, $8, Inc2                    	# not green, go to Inc2
                	lbu     	$12, -318($13)               	# $12 = mem[Array + j - 318]
                	bne    	$12, $7, Inc2                    	# not red, go to Inc2
                	lbu     	$12, -512($13)               	# $12 = mem[Array + j - 512]
                	bne    	$12, $5, Inc2                    	# not white, go to Inc2

	                addi   	$28, $3, 192                   	# the location of blue
                	addiu 	$27, $3, -512                 	# the location of white
               
               		j         	Exit

Inc:                	addi   	$3, $3, 1                        	# j = j + 1
                	j         	Loop2                            	# jump to Loop2

Inc2:        		bne    	$3, $4, Inc
		addi   	$4, $4, 2                         	# i = i + 2
                	j         	Loop1                            	# jump to Loop1

Inc7:        		addi   	$4, $4, 7                         	# i = i + 7
                	j         	Loop1                            	# jump to Loop1

Exit:          	addu 	$2, $0, $27                     	# add location of hat to $2
                	sll      	$2, $2, 16                       	# move to upper 16 bits
                	or      	$2, $2, $28                     	# add location of shirt to $2
	
 		swi	571	                	# submit answer and check
		                                		# oracle returns correct answer in $3

		jr	$31	                	# return to caller
