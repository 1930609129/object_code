cmake_minimum_required(VERSION 3.21)
project(object C)

set(CMAKE_C_STANDARD 99)

add_library(object used.h list.c list.h stack.c stack.h queue.c queue.h link.c link.h DLink.c DLink.h dict.c dict.h CString.c CString.h hash.c hash.h set.c set.h alm.h vector.c vector.h q_queue.c q_queue.h q_stack.c q_stack.h)
