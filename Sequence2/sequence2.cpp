// Provided by:   MIGUEL DOMINGUEZ
// Email Address: 

// FILE: sequence.cpp
// CLASS IMPLEMENTE: sequence
// INVARIANT for the sequence class
// 1. The number of items in the sequence is in the member variable used
// 2. The pointer data points to an array that holds the values of the sequence
// 3. The number of elements the array can hold are in variable capacity which can also be increased or reduced
// 4. The current item is indicated by the member variable current_index, if used == 0 or the index is greater than used then there is no current item



#include "sequence2.h"
#include <cassert>
namespace main_savitch_4
{
   const sequence::size_type sequence::DEFAULT_CAPACITY; //static member constants
   
   //CONSTRUCTORS
   sequence::sequence(size_type initial_capacity)  //Default Constructor
   {
      used = 0;
      capacity = initial_capacity;
      data = new value_type[capacity];
   }
   
   sequence::sequence(const sequence& source)      //Copy Constructor
   {
      used = source.used;                 //Copy variable values
      capacity = source.capacity;
      current_index = source.current_index;
	  
	  data = new value_type[capacity];    //Allocate dynamic memory for copy
	  
	  for(int i = 0; i < used; ++i)       //Copy source elements
	  {
	     data[i] = source.data[i];
	  }
   }
   
   //Destructor
   sequence::~sequence()
   {
      delete [] data;
   }
   
   //MODIFICATION MEMBER FUNCTIONS
   void sequence::resize(size_type new_capacity)
   {
      if(size() < new_capacity)
	  {
	     value_type * dummy = data;            //New pointer to help us point to data
	     capacity = new_capacity;
	     data = new value_type[capacity];      //Dynamic memory for a larger array
	  
	     for(int i = 0; i < used; ++i)         //Copy the elements from the old array
	     {
	        data[i] = dummy[i];
	     }
	  
	     delete [] dummy;                      //Deallocate the old array being pointed by dummy
	  }
   }
   
   void sequence::start()
   {
      if(size() > 0)
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
      if(size() == capacity)
	  {
	     resize(capacity + ((capacity*10)/100));     //Resizes the orgininal capacity by 10% 
	  }
	  
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
      if(size() == capacity)
	  {
	     resize(capacity + ((capacity*10)/100));     //Resizes the orgininal capacity by 10% 
	  }
	  
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
   
   //OPERATORS
   
   void sequence::operator=(const sequence& source)
   {
      if(this == &source)                                 //Self assigment
	  {
	     return;
	  }
	  
	  value_type * dummy;								
	  
	  if(capacity != source.capacity)                    //If capacities are different
	  {
	     dummy = new value_type[source.capacity]; 
		 delete [] data;                                 //Deleting old data
		 data = dummy;
		 capacity = source.capacity;
	  }
	  
	  current_index = source.current_index;
	  used = source.used;
	  for(int i = 0; i < used; ++i)                      //Copying elements
	  {
	     data[i] = source.data[i];
	  }
   
   }
   
   //CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
      return used;
   }
   
   bool sequence::is_item() const
   {
      if(size() == 0 || current_index >= used)
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