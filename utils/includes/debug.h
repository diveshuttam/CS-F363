#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef __DEBUG
#define debug_msg1(...) {printf("%s:%d:",__FILE__,__LINE__);printf(__VA_ARGS__);fflush(stdout);}
#define debug_msg(...) {printf(__VA_ARGS__); fflush(stdout);}
#else
#define debug_msg(...) {;}
#define debug_msg1(...) {printf(__VA_ARGS__);}
#endif

#endif