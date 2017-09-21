// Provided by:   MIGUEL DOMINGUEZ
// Email Address: 

// FILE: sequence3.cpp
// CLASS IMPLEMENTATION: sequence3

// INVARIANT FOR THE SEQUENCE CLASS
//
// 1. The number of items (nodes) in the sequence is contained in the variable mManyNodes.
//    If new items are inserted or attached then the number of mManyNodes increases.
//	  Else, if items of the sequence are removed then mManyNodes decreases.
//
// 2. The pointer variable mHeadPtr points to the first item (node) of a sequence.
//    If the sequence is empty then mHeadPtr points to NULL.
//
// 3. The pointer variable mTailPtr points to the last item (node) of the sequence.
//    If the sequence is empty then mTailPtr points to NULL.
//
// 4. The pointer variable mPreCursor points to the item (node) before the current item.
//    If the sequence is empty OR the current item is the first item in the sequence,
//    then mPrecursor points to NULL. 
//
// 5. The pointer variable mCursor points to the current item (node). If there is no current item
//    then mCursor points to NULL.

#include "sequence3.h"
#include <cassert>

namespace main_savitch_5
{
   //DEFAULT CONSTRUCTOR
   //Sets all pointers to NULL for a newly created sequence
   //and the number of items (nodes) to 0
   
   //Big-0 Notation: O(1)
   //Similar to the default constructor of the dynamic array sequence
   //this constructor's run time analyzis is CONSTANT.
   sequence::sequence()
   {
      mManyNodes = 0;         //NUmber of nodes is 0 for empty sequence
	  mHeadPtr   = NULL;      //Sets all node pointers to null for an empty sequence
	  mTailPtr   = NULL;
	  mCursor    = NULL;
	  mPreCursor = NULL;
   }
   
   //COPY CONSTRUCTOR
   //Copies all items from a source sequence and sets pointers
   //to their corresponding nodes
   
   //Big-O Notation: O(n^3) (WORST CASE)
   //This copy constructor traverses the source items to make each copy
   //It also searches the precursor in the source sequence with a loop
   //It sets the precursor to the right node using a second loop
   //The dynamic array sequence copy constructor has linear time analysis 
   //while this one has cube time 
   sequence::sequence(const sequence& source)
   {
      list_copy(source.mHeadPtr, mHeadPtr, mTailPtr);
	  
	  if(source.mPreCursor == NULL && source.mCursor == NULL)    //Empty list case
	  {
	     mPreCursor = NULL;
		 mCursor = NULL;
	  }
	  else if(source.mCursor == source.mHeadPtr)                 //When current is the first node
	  {
	     mPreCursor = NULL;
		 mCursor = mHeadPtr;
	  }
	  else                                                       //When the current item is not the first node
	  {
	     sequence::size_type counter = 0;
		 sequence::size_type  i      = 0;
		 node * helper;
		 helper = source.mHeadPtr;
		 while(helper != source.mPreCursor)                      //Searching for the precursor in the source
		 {
		    helper = helper->link();
			++counter;
		 }
		 
		 helper = mHeadPtr;
		 while(i < counter)                                      //Assigning the precursor to the copied list right node
		 {
		    helper = helper->link();
			++i;
		 }
	     mPreCursor = helper;
		 mCursor = mPreCursor->link();
	  }
	  
	  mManyNodes = source.mManyNodes;                            //Copy number of nodes
   }
   
   //DESTRUCTOR
   //Returns dynamically allocated memory to the heap by deleting each item
   
   //Big-O Notation: 0(n)
   //The destructor has to delete every single item in the sequence. This
   //results in linear time. On the other side, the dynamic array sequence destructor
   //has constant run time analysis.
   sequence::~sequence()
   {
      list_clear(mHeadPtr);    //Release each node allocared memory
      mTailPtr   = NULL;       //Reset pointers
	  mCursor    = NULL;
	  mPreCursor = NULL;
	  mManyNodes = 0;          //Set number of items to 0
   }
   
   //////MODIFICATION MEMBER FUNCTIONS//////
   
   //START FUNCTION
   //Sets first item in the sequence to current item
   
   //Big-O Notation: O(1)
   //The start function here and the one from the dynamic array sequence
   //have constant time. 
   void sequence::start()
   {
      if(size() > 0)
	  {
	     mCursor = mHeadPtr;   //Pointing to the first node
	     mPreCursor = NULL;    //Set to null if precursor was pointing to another node and then start() is called
	  }
   }
   
   //ADVANCE FUNCTION
   //Moves precursor and cursor to their corresponding next nodes
   
   //Big-O Notation: O(1)
   //Similar to the advance() function from the dynamic array sequence
   //this advance requires just a few steps to do its job
   void sequence::advance()
   {
      assert(is_item());
	  
	  mPreCursor = mCursor;
	  mCursor = mCursor->link();
   }
   
   //INSERT FUNCTION
   //Inserts an item before the current item.
   //If there is no current, then the item is inserted
   //at the front of the sequence.
   
   //Big-O Notation: O(1)
   //Suprisingly, since nodes have pointers and there is a precursor
   //it is easy to add a new item before the current item.
   //This takes constant time. In the other side, the dynamic array
   //takes 0(n^2) assuming we have to resize and move array elements
   void sequence::insert(const value_type& entry)
   {
      if(is_item())                         //Inserts a node before current item
	  {
	     if(mPreCursor == NULL)             //This checks when cursor is the first node and precursor is a null
		 {
		    list_head_insert(mHeadPtr, entry);
		    mCursor = mHeadPtr;
			++mManyNodes;
		 }
		 else
		 {
	        list_insert(mPreCursor, entry); //Inserts a node before cursor
			mCursor = mPreCursor->link();   //Change cursor to freshly inserted node
			++mManyNodes;
		 }
	  }
	  else if(size() == 0)                
	  {
	     list_head_insert(mHeadPtr, entry); //Insert very first node
	     mCursor = mHeadPtr;                //Change cursor to point to the FIRST node
		 mTailPtr = mHeadPtr;               //Set the tail to point the FIRST node
		 ++mManyNodes;
	  }
	  else
	  {
	     list_head_insert(mHeadPtr, entry); //If there is not current item in a nonempty list or current is the first node then we insert at the front
	     mCursor = mHeadPtr;                //Change cursor to freshly inserted node
	     mPreCursor = NULL;                 //Set to precursor to null if the precursor was pointing to the last node after a final advance()
		 ++mManyNodes;
	  }
   }
   
   //ATTACH FUNCTION
   //Attaches a new item after the current item.
   //If there is no current item then it attaches the
   //item to the end of the sequence
   
   //Big-O Notation: 0(1)
   //This functions takes constant time since the link field
   //facilitate a single insertion. Unfortunately, the dynamic array
   //takes linear time if the indexes have to be changed or even quadratic
   //time if the array has to be resized
   void sequence::attach(const value_type& entry)
   {
      if(is_item())                               //There is a current item
	  {
	     if(mCursor == mTailPtr)                  //The cursor is the tail
		 {
		    mPreCursor = mCursor;
			mCursor = new node(entry, NULL);
			mPreCursor->set_link(mCursor);
			mTailPtr = mCursor;
			++mManyNodes;
		 }
		 else
		 {
		    list_insert(mCursor, entry); 
			mPreCursor = mCursor;
			mCursor = mCursor->link();
			++mManyNodes;
		 }
	  }
	  else if(size() == 0)                        //First attached node
	  {
	     list_head_insert(mHeadPtr, entry);
		 mCursor = mHeadPtr;
		 mTailPtr = mHeadPtr;
		 ++mManyNodes;
	  }
	  else                                        //Case where there is no current item
	  {
	     node * helper;
		 helper = mTailPtr;
		 mTailPtr = new node(entry, NULL);
		 helper->set_link(mTailPtr);
		 mPreCursor = helper;
		 mCursor = mTailPtr;
		 ++mManyNodes;
	  }
   }
   
   //REMOVE CURRENT FUNCTION
   //Removes current item
   
   //Big-O Notation: 0(1)
   //Removing takes constant time because we have the help of the precursor and cursor
   //Removing in a dynamic array takes linear time since we need a loop
   //to change the element positions after an item has been removed
   void sequence::remove_current()
   {
      assert(is_item());                  //Checks if there is a current item
	  
	  if(size() == 1)                     //Case where there is only one node and we need to reset all variables
	  {
	     delete mHeadPtr;
		 mHeadPtr   = NULL;
		 mTailPtr   = NULL;
		 mCursor    = NULL;
		 mPreCursor = NULL;
		 --mManyNodes;
	  }
	  else if(mCursor == mHeadPtr)       //Current is the very first node
	  {
	     list_head_remove(mHeadPtr);
		 mCursor = mHeadPtr;
		 --mManyNodes;
	  }
	  else if(mCursor == mTailPtr)       //Current is the last node or tail
	  {
	     list_remove(mPreCursor);
		 mTailPtr = mPreCursor;
		 mCursor = NULL;
		 --mManyNodes;
	  }
	  else                              //All other cases for current items
	  {
	     list_remove(mPreCursor);
		 mCursor = mPreCursor->link();
		 --mManyNodes;
	  }
   }
   
   //OPERATOR = 
   //Assigns a copy of a source sequence to another sequence object
   
   //Big-O Notation: O(n^3)  (WORST CASE!)
   //For the linked list, copying, searching the precursor and assigning the precursor to
   //the copied sequence takes n*n*n* which is cubic time for a worst case scenarion.
   //The dynamic array sequence is more efficient since it takes linear time to copy indexed elementes
   void sequence::operator=(const sequence& source)
   {
      if(this == &source)                                             //Self Assigment
	  {
	     return;
	  }
	  
	  list_clear(mHeadPtr);
	  mManyNodes = 0;
	  list_copy(source.mHeadPtr, mHeadPtr, mTailPtr);
	  
	  if(source.mPreCursor == NULL && source.mCursor == NULL)         //Cursor and precursor point to null
	  {
	     mPreCursor = NULL;
		 mCursor = NULL;
	  }
	  else if(source.mCursor == source.mHeadPtr)                      //When current is the first node
	  {
	     mPreCursor = NULL;
		 mCursor = mHeadPtr;
	  }
	  else                                                            //Case where Cursor is not the first node
	  {
	     sequence::size_type counter = 0;
		 sequence::size_type  i      = 0;
		 node * helper;
		 helper = source.mHeadPtr;
		 while(helper != source.mPreCursor)                           //Searching for the precursor in the original sequence
		 {
		    helper = helper->link();
		    ++counter;
		 }
		 
		 helper = mHeadPtr;
		 while(i < counter)                                            //Assigning the precursor for the copied sequence
		 {
		    helper = helper->link();
		    ++i;
		 }
		 mPreCursor = helper;
		 mCursor = mPreCursor->link();
	  }
	  
	  mManyNodes = source.mManyNodes;                                  //Copying number of nodes
   }
   
   //////CONSTANT MEMBER FUNCTIONS/////
   
   //SIZE()
   //Returns number of items
   
   //Big-O Notation: 0(1)
   //Similar to the dynamic array sequence
   //it takes constant time to retrive constat values
   sequence::size_type sequence::size() const
   {
      return mManyNodes;
   }
   
   //IS ITEM
   //Returns true or false depending on wheter there is a current item
   
   //Big-O Notation: 0(1)
   //Similar to the dynamic array sequence
   //it takes constant time to decide the vality of
   //the current item
   bool sequence::is_item() const
   {
      if(mCursor == NULL)
	  {
	     return false;
	  }
	  
	  return true;
   }
   
   //CURRENT
   //Returns the data in the current node
   
   //Similar to the dynamic array sequence
   //it takes constant time to retrive const values
   sequence::value_type sequence::current() const
   {
      assert(is_item());
	  
	  return mCursor->data();
   }
}  