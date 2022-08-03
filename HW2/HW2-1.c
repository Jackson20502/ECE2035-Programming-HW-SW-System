//=================================================================
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*    
Please fill in the following
 Student Name: Jiacheng Zhang
 Date: 01/29/2022

ECE 2035 Homework 2-1

This is the only file that should be modified for the C implementation
of Homework 2.

Do not include any additional libraries.

FOR FULL CREDIT (on all assignments in this class), BE SURE TO TRY
MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

-----------------------------------------------

    Intensity Matcher

  This program finds the two closest colors in an array of packed RGB values,
  based on the difference in their intensities.  Intensity is measured as mean
  color component value: I = (R+G+B)/3).
  It prints the difference in intensities of the two closest colors.

*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

int main(int argc, char *argv[]) {
   int	Pixels[8];
   int	NumPixels, MinDelta=255;  // temporary initial value
   int         Load_Mem(char *, int *);

   if (argc != 2) {
     printf("usage: ./HW2-1 valuefile\n");
     exit(1);
   }
   NumPixels = Load_Mem(argv[1], Pixels);
   if (NumPixels != 8) {
      printf("valuefiles must contain 8 entries\n");
      exit(1);
   }

   if (DEBUG){
     printf("Sample debugging print statement. argc: %d \n", argc);
     printf("Pixels[2] in decimal: %d, in hex: 0x%08x\n", Pixels[2], Pixels[2]);

     printf("Debugging print statement.\n");
     printf("These will only show up when DEBUG is set to 1.\n");
     printf("You should wrap DEBUG around any print statements you add");
     printf(" so that they do not confuse the grading scripts.\n");
     printf("You must set DEBUG to 0 before submitting your code.\n");
   }

   /* Your program goes here */
   int r[8];
   int g[8];
   int b[8];
   int intensity[8];
   int temp = 0;
   /* Separate each color into red, green, and blue components 
   using shift and mask, then get their intensity. */
   for (int i = 0; i < NumPixels; i++) {
     r[i] = (Pixels[i] >> 16) & 0xff;                                       
     g[i] = (Pixels[i] >> 8) & 0xff;
     b[i] = Pixels[i] & 0xff;
     intensity[i] = (r[i] + g[i] + b[i]) / 3;
   }
   /* Traverse all the colors and find the minimal absolute 
   differences between them. */
   for (int i = 0; i < NumPixels - 1; i++) {
     for (int j = i + 1; j < NumPixels; j++) {
       temp = abs(intensity[j] - intensity[i]);
       if (temp < MinDelta) {
         MinDelta = temp;
       }
     }
   }
   
   /* your program should use this print statement */
   printf("The 2 closest colors have an intensity difference of %d\n", MinDelta);
   exit(0);
}

/* This routine loads in up to 8 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < 8; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals == 2)
            IntArray[N] = Value;
         else
            break;
      }
      fclose(FP);
      return N;
   }
}
