#ifndef __FUNCTION_PTR_H
#define __FUNCTION_PTR_H
typedef void (*func_ptr_t)(void*);       // a function pointer
typedef func_ptr_t* ptr_to_func_ptr;     // a pointer to a function pointer - easy to read
#endif