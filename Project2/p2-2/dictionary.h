/*
* This file contains the dictionary array which is 
* an array of Word structs that hold words that could be
* potential secret words. You may add or remove from the Word
* struct as you see fit for your own implementation.
* You should add more potential secret words to the dictionary.
*/

struct Word {
   char* letters;
   int counts[5];
   char unique[5];
} word;  


Word dictionary[10] = {
    {"union", {1,1,1,1,1}, {'u', 'n', 'i', 'o', 'n'}},
    {"crane", {1,1,1,1,1}, {'c', 'r', 'a', 'n', 'e'}},
    {"start", {1,1,1,1,1}, {'s', 't', 'a', 'r', 't'}},
    {"actor", {1,1,1,1,1}, {'a', 'c', 't', 'o', 'r'}},
    {"human", {1,1,1,1,1}, {'h', 'u', 'm', 'a', 'n'}},
    {"plane", {1,1,1,1,1}, {'p', 'l', 'a', 'n', 'e'}},
    {"space", {1,1,1,1,1}, {'s', 'p', 'a', 'c', 'e'}},
    {"magic", {1,1,1,1,1}, {'m', 'a', 'g', 'i', 'c'}},
    {"peach", {1,1,1,1,1}, {'p', 'e', 'a', 'c', 'h'}},
    {"heart", {1,1,1,1,1}, {'h', 'e', 'a', 'r', 't'}},
    };
