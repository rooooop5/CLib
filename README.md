# CVector Library: Simple type-specific implementation of dynamic arrays.
## Features :
  - dynamic arrays of any type
  - useful functions for implementing pushing,popping,
    iterating with macros in a user friendly way

## What the CVector actually is:
   Each cvector is actually a struct under the hood. The struct has three
   containers:
   -  data[ ]: The actual array. It can be of any type.
   -  size: A container of the type size_t. It stores the current size of 
      data[ ].
   -  capacity: A container of the type size_t. It stores the total memory
      that has been allocated for data[ ]

## Functions and Macros:
The use of the all the functions and the macros in this library is has 
been described below:
- MACRO cvector(int): 
  - brings in the definition of the structure and the functions
  - should be done outside any function as function definitions 
    are not allowed to be in another function
- MACRO init_cvec(type,name):
  - declares the structure using the type and name given
    - name becomes identifyer 
    - type becomes the datatype of the array inside the structure
- FUNCTION typecv_push(cvector_type* , type value):
  - appends to the cvector
  - needs the memory address of the cvector and the value to be appended
- FUNCTION typecv_pop(cvector_type* v)
  - removes the last element of the cvector
  - returns the last element of the cvector
- FUNCTION cvec_type_remove(cvector_type* v,int idx)
  - removes the element at the given index of the cvector
- MACRO iterate_byval(cvector_type v,iterator,type)
  - iterates through the cvector by value
  - read only
  - arguments needed are the cvector,the iterator variable (no need to declare
    it before use, macro handles it), and the type of the cvector
- MACRO iterate_byref(cvector_type v,iterator,type)
  - iterates through the cvector by ref
  - read or write in place
  - arguments needed are the cvector,the iterator variable (no need to declare
    it before use, macro handles it), and the type of the cvector

## Design choice for the vectors(READ ONLY IF INTERESTED IN UNDER THE HOOD STUFF)
  - For implementing type safety and prioritising userfriendly-ness
    (pratically absent in C) i have implemented type-specifc code. 
    - This means for each vector that stores a different data type,
      we would first need to initialise that type of vector using 
      macros.
    - Each initialisation would define a new type-speicific structure
      and type-specific functions that manipulate the cvector.
    - Example: I want to use cvector of type int, the following 
      would happen:
       - a struct would be defined that contains a dynamic array that only 
         holds ints
       - functions would be defined that only manipulate int arrays
    - Now if I want to use cvectors of type float, again:
        - a struct would be defined that contains a dynamic array that only
        holds float
        - functions would be defined that only manipulate float arrays