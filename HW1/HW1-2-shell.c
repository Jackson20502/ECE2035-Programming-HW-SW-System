//=================================================================
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

#include <stdio.h>
#include <stdlib.h>

/* 
 Student Name: Jiacheng Zhang
 Date: 01/19/2022

ECE 2035 Homework 1-2

This is the only file that should be modified for the C implementation
of Homework 1.

Do not include any additional libraries.

This program computes the next integer in a given sequence of integers. The sequence might be an arithmetic or geometric sequence.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

*/
// DO NOT change the following declarations
// (you may only change the initial values):
int Length = 4;
int Seq[] = {-6, 6, 18, 30};

int main() {
  int Next = 0;
  if (Seq[1] - Seq[0] == Seq[2] - Seq[1]) {
    Next = Seq[Length - 1] + (Seq[1] - Seq[0]);
} 
  if ((Seq[1] / Seq[0] == Seq[2] / Seq[1]) && Seq[1] % Seq[0] == 0 && Seq[2] % Seq[1] == 0) {
    Next = Seq[Length - 1] * (Seq[1] / Seq[0]);
} 
   // your program should use this print statement
  printf("The next integer in the sequence: %d\n", Next);

  return 0;
}

