// Provided by:   MIGUEL DOMINGUEZ
// Email Address: mdoming005@citymail.cuny.edu

// FILE: sequence.cpp
// CLASS IMPLEMENTE: sequence
// INVARIANT for the sequence class
// 1. The number of items in the sequence is in the member variable used
// 2. For an empty sequence we don't care about the size of data, for a nonempy
//    sequence the numbers are stored in the array data, which ranges from 
//    data[0] up to data[used-1]
// 3. The index of the current number in the sequence is in current_index,
//    if there is no current item then the index is the variable used



#include "sequence1.h"
#include <cassert>
namespace main_savitch_3
{
   const sequence::size_type sequence::CAPACITY; //static member constants
   
   //CONSTRUCTOR
   sequence::sequence()
   {
      used = 0;
   }
   
   //MODIFICATION MEMBER FUNCTIONS
   void sequence::start()
   {
      if(size() > 0) //SHOULD WE USE ASSERT() ??????
	  {
	     current_index = 0;
	  }
   }
   
   void sequence::advance()
   {
      assert(is_item());
	  {
	     ++current_index;
	  }
   }
   
   void sequence::insert(const value_type& entry)
   {
      assert(size() < CAPACITY);
	  
	  if(size() == 0) //empty array
	  {
	     data[used] = entry;
		 current_index = used;
		 ++used;
	  }
	  else if(current_index == size()) //off the array
	  {
	     for( int i = used; i > 0; i--)
		 {
		    data[i] = data[i-1];
		 }
		 
		 data[0] = entry;
		 current_index = 0;
		 ++used;
	  }
	  else
	  {
	     for( int i = used; i > current_index; i--)
		 {
		    data[i] = data[i-1];
		 }
		 
		 data[current_index] = entry;
		 used++;
	  }
   
	     
   }
   
   void sequence::attach(const value_type& entry)
   {
      if(size() == 0)
	  {
	     data[used] = entry;
		 current_index = used;
		 ++used;
	  }
	  else if(size() == current_index)
	  {
	     data[used] = entry;
		 current_index = used;
		 ++used;
	  }
	  else
	  {
	     for(int i = used; i > current_index + 1; i--)
		 {
		    data[i] = data[i-1];
		 }
		 
		 data[current_index +1] = entry;
		 ++current_index;
		 ++used;
	  }
   }
   
   void sequence::remove_current()
   {
      assert(is_item());
	  
	  for(int i = current_index; i < used -1; ++i)
	  {
	     data[i] = data[i+1];
	  }
	  
	  used--;
	  
   }
   
   //CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
      return used;
   }
   
   bool sequence::is_item() const
   {
      if(size() == 0 || current_index == used)
	  {
	     return false;
	  }
	  else
	  {
	     return true;
	  }
   }
   
   sequence::value_type sequence::current() const
   {
      assert(is_item());
	  
	  return data[current_index];
   }
}