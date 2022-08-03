#include "keyboard.h"
#include "dictionary.h"
#include <string>

char guessLetters[6];
char* goalWord;
char secretLetters[6];
DLinkedList* list;
LLNode* curr;
LLNode* temp_node;
LLNode* next_node;
int arrayIndex;
int position;
int lastpushed; //=0, b1 select_letter()/=1, b2 remove_letter()
char correctLetter[6];
int roundCount;
int rowCount;
int wordEqual;
int correctCount;
int correctIndex;
int found;
int reset;

int compareChar(void* input1, void* input2){
    if(*(char*)input1 == *(char*)input2){
        return 1;
    }
    else{
        return 0;
    }
}


void init_keyboard()
{
    list = create_dlinkedlist(compareChar);
    char letter = 'a';
    for (int i = 0; i < 26; i++) {
        char* alphabet = (char*) malloc(sizeof(char));
        *alphabet = letter;
        insertTail(list, alphabet);
        letter++;
    }
    uLCD.text_string((char*) getData(getTail(list)), 7, 15, FONT_7X8, GREEN);
    uLCD.text_string((char*) getData(getHead(list)), 9, 15, FONT_7X8, RED);
    uLCD.text_string((char*) getData(getNext(getHead(list))), 11, 15, FONT_7X8, GREEN);
    curr = getHead(list);
    reset = 0;
    arrayIndex = 0;
    position = 0;
    lastpushed = -1;
    roundCount = 0;
    rowCount = 5;
    wordEqual = 0;
    correctCount = 0;
    correctIndex = 0;
    found = -1;
    Word chooseWord = dictionary[rand() % 10];
    for (int i = 0; i < 6; i++) {
        guessLetters[i] = '\0';
        secretLetters[i] = '\0';
        correctLetter[i] = '\0';
    }
    
    //uLCD.locate(1,12);
    for (int i = 0; i < 5; i++) {
        secretLetters[i] = chooseWord.unique[i];
        //uLCD.printf("%c", secretLetters[i]);//Test print
    }
}

void moveleft() {
    if (getPrev(curr) != NULL) {
        curr = getPrev(curr);
        if (getPrev(curr) != NULL) {
            uLCD.text_string((char*) getData(getPrev(curr)), 7, 15, FONT_7X8, GREEN);
            uLCD.text_string((char*) getData(curr), 9, 15, FONT_7X8, RED);
            uLCD.text_string((char*) getData(getNext(curr)), 11, 15, FONT_7X8, GREEN);
        } else {
            uLCD.text_string((char*) getData(getTail(list)), 7, 15, FONT_7X8, GREEN);
            uLCD.text_string((char*) getData(curr), 9, 15, FONT_7X8, RED);
            uLCD.text_string((char*) getData(getNext(curr)), 11, 15, FONT_7X8, GREEN);
        }
    } else {
        curr = getTail(list);
        uLCD.text_string((char*) getData(getPrev(curr)), 7, 15, FONT_7X8, GREEN);
        uLCD.text_string((char*) getData(curr), 9, 15, FONT_7X8, RED);
        uLCD.text_string((char*) getData(getHead(list)), 11, 15, FONT_7X8, GREEN);
    }
}

void moveright(){
    if (getNext(curr) != NULL) {
        curr = getNext(curr);
        if (getNext(curr) != NULL) {
            uLCD.text_string((char*) getData(getPrev(curr)), 7, 15, FONT_7X8, GREEN);
            uLCD.text_string((char*) getData(curr), 9, 15, FONT_7X8, RED);
            uLCD.text_string((char*) getData(getNext(curr)), 11, 15, FONT_7X8, GREEN);
        } else {
            uLCD.text_string((char*) getData(getPrev(curr)), 7, 15, FONT_7X8, GREEN);
            uLCD.text_string((char*) getData(curr), 9, 15, FONT_7X8, RED);
            uLCD.text_string((char*) getData(getHead(list)), 11, 15, FONT_7X8, GREEN);
        }
    } else {
        curr = getHead(list);
        uLCD.text_string((char*) getData(getTail(list)), 7, 15, FONT_7X8, GREEN);
        uLCD.text_string((char*) getData(curr), 9, 15, FONT_7X8, RED);
        uLCD.text_string((char*) getData(getNext(curr)), 11, 15, FONT_7X8, GREEN);
    }
}


void select_letter()
{   
    if (lastpushed == 1) {
        arrayIndex = position;
    }
    if (arrayIndex < 5) {
        guessLetters[arrayIndex] = *(char*)getData(curr);
        position = arrayIndex;
//        uLCD.locate(9, 12); // Test arrayIndex
//        uLCD.printf("%d", arrayIndex);
        uLCD.locate(7, rowCount);
        uLCD.printf("%s", guessLetters);
        arrayIndex++;
    }
    uLCD.printf("\n");
    lastpushed = 0;
}


void remove_letter()
{   
    if (lastpushed == 0) {
        arrayIndex = position;
    }
    if (arrayIndex >= 0) {
        guessLetters[arrayIndex] = ' ';
        position = arrayIndex;
//        uLCD.locate(9, 12); // Test arrayIndex
//        uLCD.printf("%d", arrayIndex);
        uLCD.locate(7, rowCount);
        uLCD.printf("%s", guessLetters);
        arrayIndex--; 
    }
    lastpushed = 1;
}

void check_word()
{
    int letterEnterEN = 0;
    
    uLCD.text_string("Correct Letter:", 3, 0, FONT_7X8, GREEN);
    
    temp_node = getHead(list);

    while (temp_node != NULL) {      // Remove letters
        for (int i = 0; i < 5; i++) {
            if (secretLetters[i] == *(char*) getData(temp_node)) {
                found = 1;
                break;
            } else {
                found = 0;
            }
        }
        
        if (found == 0) {
            next_node = getNext(temp_node);
            deleteNode(list, temp_node);
            temp_node = next_node;
        } 
        if (found == 1) {
            temp_node = getNext(temp_node);
        }
    }

    curr = getHead(list); // Refresh the curr node;
    uLCD.text_string((char*) getData(getTail(list)), 7, 15, FONT_7X8, GREEN);
    uLCD.text_string((char*) getData(getHead(list)), 9, 15, FONT_7X8, RED);
    uLCD.text_string((char*) getData(getNext(getHead(list))), 11, 15, FONT_7X8, GREEN);

    for (int i = 0; i < 5; i++) { // word match
        if (guessLetters[i] != secretLetters[i]) {
            break;
        } else {
            if (i == 4) {
                wordEqual = 1;
            }
        }
    }
    
    if (wordEqual == 0) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if ((i == j) && (guessLetters[i] == secretLetters[j])) {
                    letterEnterEN = 0;
                    i++;
                }
                if ((i == j) && (guessLetters[i] != secretLetters[j])) {
                    guessLetters[i] = ' ';
                    letterEnterEN = 0;
                }
                if ((i != j) && (guessLetters[i] == secretLetters[j])){
                    for (int k = 0; k < 5; k++) {
                        if (correctLetter[k] == guessLetters[i]) {
                            letterEnterEN = 0;
                            break;
                        } else {
                            letterEnterEN = 1;
                        }
                    }
                    if (letterEnterEN == 1) {
                        correctLetter[correctIndex] = guessLetters[i];
                        correctIndex++;
                    }
                
                }
                
            }
        }
    
        uLCD.locate(5, 2);
        uLCD.printf("%s", correctLetter);
    
        uLCD.locate(7, rowCount);
    
        for(int i = 0; i < 5; i++) {
            uLCD.printf("%c", guessLetters[i]);
        }
    
        rowCount++;
    
        for (int i = 0; i < 6; i++) {
            guessLetters[i] = '\0';
        }
    }


}
