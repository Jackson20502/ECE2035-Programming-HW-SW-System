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
 Date: 02/14/2022

ECE 2035 Project 1-1

This is the only file that should be modified for the C implementation
of Project 1.

Do not include any additional libraries.
------------------------------------------

This program finds an exact match of George's face which may be rotated
in a crowd of tumbling (rotated) faces. It reports the location of his
hat and shirt as pixel positions.  The pixels are specified as linear
offsets from the crowd image base.*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

int main(int argc, char *argv[]) {
   int	             CrowdInts[1024];
   // This allows you to access the pixels (individual bytes)
   // as byte array accesses (e.g., Crowd[25] gives pixel 25):
   char *Crowd = (char *)CrowdInts;
   int	             NumInts, HatLoc=0, ShirtLoc=0;
   int               Load_Mem(char *, int *);

   if (argc != 2) {
     printf("usage: ./P1-1 testcase_file\n");
     exit(1);
   }
   NumInts = Load_Mem(argv[1], CrowdInts);
   if (NumInts != 1024) {
      printf("valuefiles must contain 1024 entries\n");
      exit(1);
   }
   if (DEBUG){
     printf("Crowd[582] is Pixel 582 (blue): 0x%02x\n", Crowd[582]);
     printf("Crowd[772] is Pixel 772 (yellow): 0x%02x\n", Crowd[772]);
     printf("Crowd[1091] is Pixel 1091 (black): 0x%02x\n", Crowd[1091]);
     printf("Crowd[378] is Pixel 378 (red): 0x%02x\n", Crowd[378]);
     printf("Crowd[441] is Pixel 441 (white): 0x%02x\n", Crowd[441]);
     printf("Crowd[1030] is Pixel 1030 (green): 0x%02x\n", Crowd[1030]);
   }

   /* your code goes here. */
   for (int i = 0; i < 4084; i++) {                                           // Search the same face if it is rotated by 90 or 270 degrees
       if ((Crowd[i] == 0x03) && (Crowd[i+1] == 0x05) && (Crowd[i+2] == 0x05) && (Crowd[i+3] == 0x08)                                        // Check if each pixel in the middle row of the face match
            && (Crowd[i+4] == 0x08) && (Crowd[i+5] == 0x05) && (Crowd[i+6] == 0x05) && (Crowd[i+7] == 0x05)
            && (Crowd[i+8] == 0x02) && (Crowd[i+9] == 0x01) && (Crowd[i+10] == 0x02) && (Crowd[i+11] == 0x01)
            && (Crowd[i+128] == 0x03) && (Crowd[i+130] == 0x05) && (Crowd[i+131] == 0x05)                                                           // Check if each pixel in the third-to-last row of the face match
            && (Crowd[i+132] == 0x05) && (Crowd[i+133] == 0x08) && (Crowd[i+134] == 0x05) && (Crowd[i+135] == 0x07)
            && (Crowd[i+136] == 0x02) && (Crowd[i+137] == 0x01) && (Crowd[i+138] == 0x02) && (Crowd[i+139] == 0x02)) {
           HatLoc = i + 11;
           ShirtLoc = i;
           break;
       } else if ((Crowd[i] == 0x01) && (Crowd[i+1] == 0x02) && (Crowd[i+2] == 0x01) && (Crowd[i+3] == 0x02)                               // Check if each pixel in the middle row of the face match
            && (Crowd[i+4] == 0x05) && (Crowd[i+5] == 0x05) && (Crowd[i+6] == 0x05) && (Crowd[i+7] == 0x08)
            && (Crowd[i+8] == 0x08) && (Crowd[i+9] == 0x05) && (Crowd[i+10] == 0x05) && (Crowd[i+11] == 0x03)
            && (Crowd[i+128] == 0x02) && (Crowd[i+129] == 0x02) && (Crowd[i+130] == 0x01) && (Crowd[i+131] == 0x02)            // Check if each pixel in the third-to-last row of the face match
            && (Crowd[i+132] == 0x07) && (Crowd[i+133] == 0x05) && (Crowd[i+134] == 0x08) && (Crowd[i+135] == 0x05)
            && (Crowd[i+136] == 0x05) && (Crowd[i+137] == 0x05) && (Crowd[i+139] == 0x03)) {
           HatLoc = i;
           ShirtLoc = i + 11;
           break;
       } else {                                    // If not found, set HatLoc and ShirtLoc to 0
           HatLoc = 0;
           ShirtLoc = 0;
       }
   }

   if (HatLoc == 0 && ShirtLoc == 0) {                                // Search the same face if it is upright or rotated by 180 degrees
       for (int i = 0; i < 3328; i++) {                                       // 3328 = 52 * 64, (64 - 52 = 12, which is the minimum height of the face)
           if ((Crowd[i] == 0x03) && (Crowd[i+64] == 0x05) && (Crowd[i+128] == 0x05) && (Crowd[i+192] == 0x08)                               // Check if each pixel in the middle column of the face match
               && (Crowd[i+256] == 0x08) && (Crowd[i+320] == 0x05) && (Crowd[i+384] == 0x05) && (Crowd[i+448] == 0x05)
               && (Crowd[i+512] == 0x02) && (Crowd[i+576] == 0x01) && (Crowd[i+640] == 0x02) && (Crowd[i+704] == 0x01)
               && (Crowd[i+2] == 0x03) && (Crowd[i+130] == 0x05) && (Crowd[i+194] == 0x05)                                                                 // Check if each pixel in the third-to-last column of the face match
               && (Crowd[i+258] == 0x05) && (Crowd[i+322] == 0x08) && (Crowd[i+386] == 0x05) && (Crowd[i+450] == 0x07)
               && (Crowd[i+514] == 0x02) && (Crowd[i+578] == 0x01) && (Crowd[i+642] == 0x02) && (Crowd[i+706] == 0x02)) {
              HatLoc = i + 704;
              ShirtLoc = i;
              break;
          } else if ((Crowd[i] == 0x01) && (Crowd[i+64] == 0x02) && (Crowd[i+128] == 0x01) && (Crowd[i+192] == 0x02)                       // Check if each pixel in the middle column of the face match
               && (Crowd[i+256] == 0x05) && (Crowd[i+320] == 0x05) && (Crowd[i+384] == 0x05) && (Crowd[i+448] == 0x08)
               && (Crowd[i+512] == 0x08) && (Crowd[i+576] == 0x05) && (Crowd[i+640] == 0x05) && (Crowd[i+704] == 0x03)
               && (Crowd[i+2] == 0x02) && (Crowd[i+66] == 0x02) && (Crowd[i+130] == 0x01) && (Crowd[i+194] == 0x02)                    // Check if each pixel in the third-to-last column of the face match
               && (Crowd[i+258] == 0x07) && (Crowd[i+322] == 0x05) && (Crowd[i+386] == 0x08) && (Crowd[i+450] == 0x05)
               && (Crowd[i+514] == 0x05) && (Crowd[i+578] == 0x05) && (Crowd[i+706] == 0x03)) {
              HatLoc = i;
              ShirtLoc = i + 704;
              break;
          } else {                                   // If not found, set HatLoc and ShirtLoc to 0
              HatLoc = 0;
              ShirtLoc = 0;
          }
      }
   }

   printf("George is located at: hat pixel %d, shirt pixel %d.\n", HatLoc, ShirtLoc);
   exit(0);
}

/* This routine loads in up to 1024 newline delimited integers from
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
      for (N=0; N < 1024; N++) {
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
