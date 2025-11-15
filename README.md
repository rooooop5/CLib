# CVector Library: Simple generic implementation of dynamic arrays.
## Features :
  - dynamic arrays of any type
  - useful functions for implementing pushing,popping,
    iterating with macros in a user friendly way
## Design choice for the vectors(READ ONLY IF INTERESTED IN UNDER THE HOOD STUFF)
  - For implementing type safety and prioritising userfriendly-ness
    (pratically absent in C) i have implemented type-specifc code. 
    - This means for each vector that stores a different data type,
      we would first need to initialise that type of vector using 
      macros.
    - Each initialisation would define a new type speicific structure
      and type specific functions that manipulate the cvector.
    - Example: I want to use cvector of type int, the following 
      would happen:
       - a struct would be defined that only holds ints
       - functions would be defined that only manipulate ints 
       Now if I i want to use cvectors of type float, again:
        - a struct would be defined that contains a dynamic array that only
        holds float
        - functions would be defined that only manipulate float

## What the CVector actually is:
   Each cvector is actually a struct under the hood. The struct has three
   containers:
   1. data[ ]: The actual array. It can be of any type.
   2. size: A container of the type size_t. It stores the current size of 
            data[ ].
   3. capacity: A container of the type size_t. It stores the total memory
                that has been allocated for data[ ]

## Functions and Macros:
    The use of the all the functions and the macros in this library is has 
    been described below:
    1. MACRO init_cvec(type,name) : It is the macro that initialises the cvector.
                              - Calls the init_type() function
    2. Abr pore likhbo dhur


