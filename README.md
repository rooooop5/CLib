# CVector Library: Simple generic implementation of dynamic arrays.
## Features :
  - dynamic arrays of any type
  - useful functions for implementing pushing,popping,
    iterating with macros in a user friendly way
## What the CVector actually is:
   Each cvector is actually a struct under the hood. The struct has three
   containers:
   1. data[]: The actual array. It can be of any type.
   2. size: A container of the type size_t. It stores the current size of 
            data[].
   3. capacity: A container of the type size_t. It stores the total memory
                that has been allocated for data[]

