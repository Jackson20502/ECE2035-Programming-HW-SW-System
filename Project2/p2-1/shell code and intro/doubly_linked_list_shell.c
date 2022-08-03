//=================================================================
// Implementation for DLL module.
//
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

//===========================
/* Creating nodes and lists */
//===========================

LLNode* create_llnode(void* data) {

}

DLinkedList* create_dlinkedlist(CompareFunction compare) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    newList->compare = compare;
    return newList;
}

//============================
/* Accessing nodes and lists */
//============================

int getSize(DLinkedList* dLinkedList){

}

LLNode* getHead(DLinkedList* dLinkedList){

}

LLNode* getTail(DLinkedList* dLinkedList){

}

LLNode* getNext(LLNode* node){

}

LLNode* getPrev(LLNode* node){

}

void* getData(LLNode* node){

}

//============================
/* Inserting nodes into lists */
//============================

void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){

}


void insertBefore(DLinkedList* dLinkedList, LLNode* prev_node, void* data){

}


void insertHead(DLinkedList* dLinkedList, void* data){

}

void insertTail(DLinkedList* dLinkedList, void* data){

}

//============================
/* Looking up nodes in lists */
//============================

LLNode* findNode(DLinkedList* dLinkedList, void* data){
    
}

//===========================
/* Deleting nodes and lists */
//===========================

void deleteNode(DLinkedList* dLinkedList, LLNode* Node){

}


void destroyList(DLinkedList* dLinkedList){
    
}

//==================
/* Reversing lists */
//==================

void reverse(DLinkedList* dLinkedList){
    
}     



