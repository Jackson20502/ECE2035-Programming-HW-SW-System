//Put your DLL from P2-1 in here
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
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
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
    return dLinkedList->size;
}

LLNode* getHead(DLinkedList* dLinkedList){
    return dLinkedList->head;
}

LLNode* getTail(DLinkedList* dLinkedList){
    return dLinkedList->tail;
}

LLNode* getNext(LLNode* node){
    return node->next;
}

LLNode* getPrev(LLNode* node){
    return node->prev;
}

void* getData(LLNode* node){
    return node->data;
}

//============================
/* Inserting nodes into lists */
//============================

void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
    if (prev_node == NULL) {
        printf("The previous node should not be null!");
        return;
    }
    LLNode* insert_node = create_llnode(data);
    if (prev_node == dLinkedList->tail) {
        insert_node->next = NULL;
        insert_node->prev = dLinkedList->tail;
        dLinkedList->tail->next = insert_node;
        dLinkedList->tail = insert_node;
    } else {
        insert_node->next = prev_node->next;
        insert_node->prev = prev_node;
        prev_node->next->prev = insert_node;
        prev_node->next = insert_node;
    }
    dLinkedList->size++;
}


void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){
    if (next_node == NULL) {
        printf("The next node suould not be null!");
        return;
    }
    LLNode* insert_node = create_llnode(data);
    if (next_node == dLinkedList->head) {
        insert_node->prev = NULL;
        insert_node->next = dLinkedList->head;
        dLinkedList->head->prev = insert_node;
        dLinkedList->head = insert_node;
    } else {
        insert_node->prev = next_node->prev;
        insert_node->next = next_node;
        next_node->prev->next = insert_node;
        next_node->prev = insert_node;
    }
    dLinkedList->size++;
}


void insertHead(DLinkedList* dLinkedList, void* data){
    LLNode* insert_node = create_llnode(data);
    if (dLinkedList->head == NULL && dLinkedList->tail == NULL) {
        dLinkedList->head = insert_node;
        dLinkedList->tail = insert_node;
        dLinkedList->size++;
    } else {
        insertBefore(dLinkedList, dLinkedList->head, data);
    }
}

void insertTail(DLinkedList* dLinkedList, void* data){
    LLNode* insert_node = create_llnode(data);
    if (dLinkedList->head == NULL && dLinkedList->tail == NULL) {
        dLinkedList->head = insert_node;
        dLinkedList->tail = insert_node;
        dLinkedList->size++;
    } else {
        insertAfter(dLinkedList, dLinkedList->tail, data);
    }
}

//============================
/* Looking up nodes in lists */
//============================

LLNode* findNode(DLinkedList* dLinkedList, void* data){
    if (dLinkedList->head == NULL && dLinkedList->tail == NULL) {
        return NULL;
    }
    LLNode* curr_node = dLinkedList->head;
    while (curr_node != NULL) {
        if (dLinkedList->compare(curr_node->data, data)) {
            return curr_node;
            break;
        }
        curr_node = curr_node->next;
    }
    return NULL;
}

//===========================
/* Deleting nodes and lists */
//===========================

void deleteNode(DLinkedList* dLinkedList, LLNode* Node){
    if (dLinkedList->size == 1) {
        dLinkedList->head = NULL;
        dLinkedList->tail = NULL;
    } else if (Node == dLinkedList->head) {
        dLinkedList->head->next->prev = NULL;
        dLinkedList->head = dLinkedList->head->next;
    } else if (Node == dLinkedList->tail) {
        dLinkedList->tail->prev->next = NULL;
        dLinkedList->tail = dLinkedList->tail->prev;
    } else {
        Node->prev->next = Node->next;
        Node->next->prev = Node->prev;
    }
    free(Node->data);
    free(Node);
    dLinkedList->size--;
}


void destroyList(DLinkedList* dLinkedList){
    LLNode* temp_node = NULL;
    LLNode* curr_node = dLinkedList->head;
    while (curr_node != NULL) {
        temp_node = curr_node->next;
        free(curr_node->data);
        free(curr_node);
        curr_node = temp_node;
    }
    free(dLinkedList);
}

//==================
/* Reversing lists */
//==================

void reverse(DLinkedList* dLinkedList){
    LLNode* curr_node = dLinkedList->head;
    LLNode* temp_node = NULL;
    while (curr_node !=  NULL) {
        temp_node = curr_node->prev;
        curr_node->prev = curr_node->next;
        curr_node->next = temp_node;             
        curr_node = curr_node->prev;
    }
    temp_node = dLinkedList->head;
    dLinkedList->head = dLinkedList->tail;
    dLinkedList->tail = temp_node;
}