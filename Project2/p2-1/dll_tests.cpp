extern "C" {
	#include "doubly_linked_list.h"
}
#include "gtest/gtest.h"


// Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>

// Dummy value to store in LLNode
// Note that any type of data (e.g. int, double, struct and etc.) can
// be stored in the data of the LLNode for testing your doubly linked list.
// Only the pointer to the data will be stored in the LLNode.
struct ListItem {
    int entry1;
};

// Helper function for creating a lot of dummy values
void make_items(ListItem* result[], unsigned n)
{
    while(n--)
    {
        result[n] = (ListItem*) malloc(sizeof(ListItem));
        result[n]->entry1 = n;
    }
}

//Helper comparison function to test, your comparison function
//in P2-2 will look something like this
int compareInt(void* input1, void* input2) {
	if (*(int*)input1 == *(int*)input2) {
		return 1;
	}
	else {
		return 0;
	}
}


// Initialization tests
TEST(InitTest, CreateDestroy)
{
	DLinkedList* list = create_dlinkedlist(compareInt);
	destroyList(list);
}

// Access tests
TEST(Access, getHead_Empty)
{
	DLinkedList* list = create_dlinkedlist(compareInt);
	EXPECT_EQ(NULL, getHead(list));
	destroyList(list);
}

TEST(Access, getTail_Empty)
{
	DLinkedList* list = create_dlinkedlist(compareInt);
	EXPECT_EQ(NULL, getTail(list));
	destroyList(list);
}

TEST(Access, getSize_Empty)
{
	DLinkedList* list = create_dlinkedlist(compareInt);
	EXPECT_EQ(0, getSize(list));
	destroyList(list);
}

// Insertion tests
TEST(Insert, Head_Single)
{
	// Initialize items for your test
	size_t num_items = 1;
	ListItem* m[num_items]; make_items(m, num_items);

	// Use the items in your list
	DLinkedList* list = create_dlinkedlist(compareInt);
	insertHead(list, m[0]);

	// Check that the behavior was correct
	EXPECT_EQ(m[0], getData(getHead(list)));
	EXPECT_EQ(m[0], getData(getTail(list)));
	EXPECT_EQ(1, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, Head_Multiple)
{
	// Create list items
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 3; i++){
	  	insertHead(list, m[i]);
	}

	// Check forward links
	LLNode* current = getHead(list);
	for (int i = 2; i >= 0; i--){
	  	ASSERT_EQ(m[i], getData(current));
	  	current = getNext(current);
	}
	ASSERT_EQ(NULL, current);

	// Check backward links
	current = getTail(list);
	for (int i = 0; i <= 2; i++){
	  	ASSERT_EQ(m[i], getData(current));
	  	current = getPrev(current);
	}
	ASSERT_EQ(NULL, current);

	ASSERT_EQ(m[2], getData(getHead(list)));
	ASSERT_EQ(m[0], getData(getTail(list)));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, Tail_Single)
{
	// Initialize items for your test
	size_t num_items = 1;
	ListItem* m[num_items]; make_items(m, num_items);

	// Use the items in your list
	DLinkedList* list = create_dlinkedlist(compareInt);
	insertTail(list, m[0]);

	// Check that the behavior was correct
	EXPECT_EQ(m[0], getData(getHead(list)));
	EXPECT_EQ(m[0], getData(getTail(list)));
	EXPECT_EQ(1, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, Tail_Multiple)
{
	// Create list items
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the tail (resulting list is [0, 1, 2])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 3; i++){
	  	insertTail(list, m[i]);
	}

	// Check forward links
	LLNode* current = getHead(list);
	for (int i = 0; i < 3; i++){
	  	ASSERT_EQ(m[i], getData(current));
	  	current = getNext(current);
	}
	ASSERT_EQ(NULL, current);

	// Check backward links
	current = getTail(list);
	for (int i = 2; i >= 0; i--){
	  	ASSERT_EQ(m[i], getData(current));
	  	current = getPrev(current);
	}
	ASSERT_EQ(NULL, current);

	ASSERT_EQ(m[0], getData(getHead(list)));
	ASSERT_EQ(m[2], getData(getTail(list)));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, After_Middle_Single)
{
	// Create list items
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 2 items at the head (resulting list is [1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 2; i++){
		insertHead(list, m[i]);
	}

	insertAfter(list, getHead(list), m[2]);

	ASSERT_EQ(m[2], getData(getNext(getHead(list))));
	ASSERT_EQ(m[2], getData(getPrev(getTail(list))));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, After_Tail_Single)
{
	// Create list items
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 2 items at the head (resulting list is [1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 2; i++){
	  	insertHead(list, m[i]);
	}

	insertAfter(list, getTail(list), m[2]);

	ASSERT_EQ(m[2], getData(getTail(list)));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, After_Middle_Multiple)
{
	// Create list items
	size_t num_items = 4;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 2 items at the head (resulting list is [1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 2; i++){
	  	insertHead(list, m[i]);
	}

	insertAfter(list, getHead(list), m[2]);
	insertAfter(list, getNext(getHead(list)), m[3]); // (resulting list is [1, 2, 3, 0])

	ASSERT_EQ(m[2], getData(getNext(getHead(list))));
	ASSERT_EQ(m[2], getData(getPrev(getPrev(getTail(list)))));
	ASSERT_EQ(m[3], getData(getNext(getNext(getHead(list)))));
	ASSERT_EQ(m[3], getData(getPrev(getTail(list))));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, After_Tail_Multiple)
{
	// Create list items
	size_t num_items = 4;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 2 items at the head (resulting list is [1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 2; i++){
	  	insertHead(list, m[i]);
	}

	insertAfter(list, getTail(list), m[2]);
	insertAfter(list, getTail(list), m[3]); // (resulting list is [1, 0, 2, 3])

	ASSERT_EQ(m[2], getData(getPrev(getTail(list))));
	ASSERT_EQ(m[3], getData(getTail(list)));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, Before_Middle_Single)
{
	// Create list items
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 2 items at the head (resulting list is [1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 2; i++){
	  	insertHead(list, m[i]);
	}

	insertBefore(list, getTail(list), m[2]);

	ASSERT_EQ(m[2], getData(getNext(getHead(list))));
	ASSERT_EQ(m[2], getData(getPrev(getTail(list))));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, Before_Head_Single)
{
	// Create list items
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 2 items at the head (resulting list is [1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 2; i++){
	  	insertHead(list, m[i]);
	}

	insertBefore(list, getHead(list), m[2]);

	ASSERT_EQ(m[2], getData(getHead(list)));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, Before_Middle_Multiple)
{
	// Create list items
	size_t num_items = 4;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 2 items at the head (resulting list is [1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 2; i++){
	  	insertHead(list, m[i]);
	}

	insertBefore(list, getTail(list), m[2]);
	insertBefore(list, getPrev(getTail(list)), m[3]); // (resulting list is [1, 3, 2, 0])

	ASSERT_EQ(m[3], getData(getNext(getHead(list))));
	ASSERT_EQ(m[3], getData(getPrev(getPrev(getTail(list)))));
	ASSERT_EQ(m[2], getData(getNext(getNext(getHead(list)))));
	ASSERT_EQ(m[2], getData(getPrev(getTail(list))));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, Before_Head_Multiple)
{
	// Create list items
	size_t num_items = 4;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 2 items at the head (resulting list is [1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 2; i++){
	  	insertHead(list, m[i]);
	}

	insertBefore(list, getHead(list), m[2]);
	insertBefore(list, getHead(list), m[3]); // (resulting list is [3, 2, 1, 0])

	ASSERT_EQ(m[3], getData(getHead(list)));
	ASSERT_EQ(m[2], getData(getNext(getHead(list))));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

// Lookup tests
TEST(Lookup, Find_Single)
{
	// Initialize items for your test
	size_t num_items = 1;
	ListItem* m[num_items]; make_items(m, num_items);

	// Use the items in your list
	DLinkedList* list = create_dlinkedlist(compareInt);
	insertHead(list, m[0]);

	// Check that the behavior was correct
	EXPECT_EQ(getData(getHead(list)), m[0]);
	EXPECT_EQ(m[0], getData(findNode(list, m[0])));
	EXPECT_EQ(getHead(list), findNode(list, m[0]));

	// Delete the list
	destroyList(list);
}

TEST(Lookup, Not_Found_Empty)
{
	// Initialize items for your test
	size_t num_items = 1;
	ListItem* m[num_items]; make_items(m, num_items);

	DLinkedList* list = create_dlinkedlist(compareInt);

	EXPECT_EQ(NULL, findNode(list, m[0]));

	// Delete the list
	destroyList(list); // will free items in the DLL, nodes, and DLL struct

	free(m[0]);  // free any items not in the DLL
}

TEST(Lookup, Find_in_Multiple)
{
	// Create list items
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 3; i++){
	  	insertHead(list, m[i]);
	}
	for (int i = 0; i < 3; i++){
	  	ASSERT_EQ(m[i], getData(findNode(list, m[i])));
	}

	// Delete the list
	destroyList(list);
}

TEST(Lookup, Not_Found_in_Multiple)
{
	// Create list items
	size_t num_items = 4;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 3; i++){
	  	insertHead(list, m[i]);
	}

	ASSERT_EQ(NULL, findNode(list, m[3]));
	
	// Delete the list
	destroyList(list);

	free(m[3]); // need to free separately because it wasn't in the DLL
}

// Add more tests (e.g., inserting at tail, inserting before/after a node
// in the middle)

// Add Deletion tests

// Add tests to find and delete node at head/tail/middle

// Add Reverse tests

// Deletion tests
TEST(Delete, delete_Single_Size1)
{
	// Initialize items for your test
	size_t num_items = 1;
	ListItem* m[num_items]; make_items(m, num_items);

	// Use the items in your list
	DLinkedList* list = create_dlinkedlist(compareInt);
	insertHead(list, m[0]);

	deleteNode(list, getHead(list));

	// Check that the behavior was correct
	EXPECT_EQ(NULL, getHead(list));
	EXPECT_EQ(NULL, getTail(list));
	EXPECT_EQ(0, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Delete, delete_Head_Single_Size3)
{
	// Initialize items for your test
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 3; i++){
	  	insertHead(list, m[i]);
	}

	deleteNode(list, getHead(list));

	// Check that the behavior was correct
	EXPECT_EQ(m[1], getData(getHead(list)));
	EXPECT_EQ(m[0], getData(getTail(list)));
	EXPECT_EQ(2, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Delete, delete_Tail_Single_Size3)
{
	// Initialize items for your test
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 3; i++){
	  	insertHead(list, m[i]);
	}

	deleteNode(list, getTail(list));

	// Check that the behavior was correct
	EXPECT_EQ(m[2], getData(getHead(list)));
	EXPECT_EQ(m[1], getData(getTail(list)));
	EXPECT_EQ(2, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Delete, delete_Middle_Single_Size3)
{
	// Initialize items for your test
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 3; i++){
	  	insertHead(list, m[i]);
	}

	deleteNode(list, getNext(getHead(list)));

	// Check that the behavior was correct
	EXPECT_EQ(m[2], getData(getHead(list)));
	EXPECT_EQ(m[0], getData(getTail(list)));
	EXPECT_EQ(2, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Delete, delete_Head_Multiple_Size4)
{
	// Initialize items for your test
	size_t num_items = 4;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [3, 2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 4; i++){
	  	insertHead(list, m[i]);
	}

	deleteNode(list, getHead(list));
	deleteNode(list, getHead(list));
	deleteNode(list, getHead(list));

	// Check that the behavior was correct
	EXPECT_EQ(m[0], getData(getHead(list)));
	EXPECT_EQ(m[0], getData(getTail(list)));
	EXPECT_EQ(1, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Delete, delete_Tail_Multiple_Size4)
{
	// Initialize items for your test
	size_t num_items = 4;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [3, 2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 4; i++){
	  	insertHead(list, m[i]);
	}

	deleteNode(list, getTail(list));
	deleteNode(list, getTail(list));
	deleteNode(list, getTail(list));

	// Check that the behavior was correct
	EXPECT_EQ(m[3], getData(getHead(list)));
	EXPECT_EQ(m[3], getData(getTail(list)));
	EXPECT_EQ(1, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Delete, delete_Middle_Multiple_Size4)
{
	// Initialize items for your test
	size_t num_items = 4;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [3, 2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 4; i++){
	  	insertHead(list, m[i]);
	}

	deleteNode(list, getNext(getHead(list)));
	deleteNode(list, getNext(getHead(list)));

	// Check that the behavior was correct
	EXPECT_EQ(m[3], getData(getHead(list)));
	EXPECT_EQ(m[0], getData(getTail(list)));
	EXPECT_EQ(2, getSize(list));

	// Delete the list
	destroyList(list);
}

// Find and delete tests
TEST(Find_Delete, find_and_delete1)
{
	// Initialize items for your test
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 3; i++){
	  	insertHead(list, m[i]);
	}

	deleteNode(list, findNode(list, m[2]));

	// Check that the behavior was correct
	EXPECT_EQ(m[1], getData(getHead(list)));
	EXPECT_EQ(m[0], getData(getNext(getHead(list))));
	EXPECT_EQ(m[0], getData(getTail(list)));
	EXPECT_EQ(m[1], getData(getPrev(getTail(list))));

	EXPECT_EQ(2, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Find_Delete, find_and_delete2)
{
	// Initialize items for your test
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 3; i++){
	  	insertHead(list, m[i]);
	}

	deleteNode(list, findNode(list, m[1]));

	// Check that the behavior was correct
	EXPECT_EQ(m[2], getData(getHead(list)));
	EXPECT_EQ(m[0], getData(getNext(getHead(list))));
	EXPECT_EQ(m[0], getData(getTail(list)));
	EXPECT_EQ(m[2], getData(getPrev(getTail(list))));
	EXPECT_EQ(2, getSize(list));

	// Delete the list
	destroyList(list);
}

// Reverse tests
TEST(Reverse, getReverse_Single)
{
    // Create list items
	size_t num_items = 1;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 1 items at the head
	DLinkedList* list = create_dlinkedlist(compareInt);
	insertHead(list, m[0]);

	// Reverse the DLL
	reverse(list);

	// Check links after reverse
	ASSERT_EQ(m[0], getData(getHead(list)));

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Reverse, getReverse_Double)
{
    // Create list items
	size_t num_items = 2;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 2 items at the head (resulting list is [1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 2; i++){
	  	insertHead(list, m[i]);
	}

	// Reverse the DLL (resulting list is [0, 1])
	reverse(list);

	// Check links after reverse
	LLNode* current = getHead(list);
	for (int i = 0; i < 2; i++){
		ASSERT_EQ(m[i], getData(current));
	  	current = getNext(current);
	}
	ASSERT_EQ(NULL, current);

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Reverse, getReverse_Multiple)
{
    // Create list items
	size_t num_items = 4;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 4 items at the head (resulting list is [3, 2, 1, 0])
	DLinkedList* list = create_dlinkedlist(compareInt);
	for (int i = 0; i < 4; i++){
	  	insertHead(list, m[i]);
	}

	// Reverse the DLL (resulting list is [0, 1, 2, 3])
	reverse(list);

	// Check links after reverse
	LLNode* current = getHead(list);
	for (int i = 0; i < 4; i++){
		ASSERT_EQ(m[i], getData(current));
	  	current = getNext(current);
	}
	ASSERT_EQ(NULL, current);

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}