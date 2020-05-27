// C11 standard
// created by cicek on 09.11.2018 21:12

#include <stdio.h>
#include <stdlib.h>

int main() {

    /*
     * Memory Management

    Understanding memory is an important aspect of C programming.
     When you declare a variable using a basic data type,
     C automatically allocates space for the variable in an area of memory called the stack.
     */

    int arr111[10];
    printf("%lu\n", sizeof(arr111)); /* output: 40 */

    /*
Dynamic memory allocation is the process of allocating and freeing memory as needed.
Now you can prompt at runtime for the number of array elements and then create an array with that many elements.
Dynamic memory is managed with pointers that point to newly allocated blocks of memory in an area called the heap.
In addition to automatic memory management using the stack and dynamic memory allocation using the heap, there is statically managed data in main memory for variables that persist for the lifetime of the program.
     */

    // Memory Management Functions

/*

malloc(bytes)                   Returns a pointer to a contiguous block of memory that is of size bytes.

calloc(num_items, item_size)    Returns a pointer to a contiguous block of memory that has num_items items, each of size item_size bytes. Typically used for arrays, structures, and other derived data types. The allocated memory is initialized to 0.

realloc(ptr, bytes)             Resizes the memory pointed to by ptr to size bytes. The newly allocated memory is not initialized.

free(ptr)                       Releases the block of memory pointed to by ptr.

*/

    // When you no longer need a block of allocated memory, use the function free() to make the block available to be allocated again.

    // malloc - memory allocation
    // calloc - contiguous allocation
    // realloc - re-allocation
    // free - free allocation

    /*
(1)
calloc(num_items, item_size);
malloc(num_items * item_size);
Is it the same?
(2)
Does it mean that realloc() deletes all the content pointed by ptr?

(1) Yes, but the calloc() set the value of memory to 0, and malloc() do not.
     What does it mean? the calloc set to 0 each item of the size type defined  by the pointer (each item value is zero, a kind of initial value), and malloc keeps what it was at the memory address pointed for each item. (which it is a garbage value).
(2) Yes and no. Realloc takes what it was assigned by malloc and gives it a new address and enough space to store more items.
     So the initial address is lost but the content is not accessible and not deleted because it wasnt freed. As it is unaccessible you can consider it as deleted. Check the draft for c standard on the web. Hope it is less confuse.
     */

    // When the program terminates, memory on stack is freed automatically. Not on heap. After the end of program your data will be still there.

    // The malloc() function allocates a specified number of contiguous bytes in memory.

    int *ptr;
/* a block of 5 ints */
    ptr = malloc(5 * sizeof(*ptr)); // malloc returns a pointer to the allocated memory.

    if (ptr != NULL) {
        *(ptr + 4) = 50;  /* assign 50 to fifth int */
    }

    printf("0: %d\n", *(ptr+0)); // 0
    printf("1: %d\n", *(ptr+1)); // 0
    printf("2: %d\n", *(ptr+2)); // 0
    printf("3: %d\n", *(ptr+3)); // 0
    printf("4: %d\n", *(ptr+4)); // 50


    printf("\n%lu", sizeof(int)); // 4
    printf("\n%lu", sizeof(*ptr)); // 4

    /*
The allocated memory is contiguous and can be treated as an array. Instead of using brackets [ ] to refer to elements, pointer arithmetic is used to traverse the array. You are advised to use + to refer to array elements. Using ++ or += changes the address stored by the pointer.

If the allocation is unsuccessful, NULL is returned. Because of this, you should include code to check for a NULL pointer.
A simple two-dimensional array requires (rows*columns)*sizeof(datatype) bytes of memory.
     */

    /*

the library function malloc is used to allocate a block of memory on the heap.
The program accesses this block of memory via a pointer that malloc returns.
When the memory is no longer needed, the pointer is passed to free which deallocates the memory so that it can be used for other purposes.
     */

    return 0;
}
