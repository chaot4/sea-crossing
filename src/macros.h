#ifndef defs_h
#define defs_h

// #define NDEBUG

#ifdef NDEBUG
#define Debug(x)
#else
#include <iostream>
#define Debug(x) std::cout << x << std::endl
#endif

// #define NVERBOSE

#ifdef NVERBOSE
#define Print(x)
#else
#include <iostream>
#define Print(x) std::cout << x << std::endl
#endif

#endif
