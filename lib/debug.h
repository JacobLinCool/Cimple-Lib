/**
 * @file debug.h
 * @author JacobLinCool <jacoblincool@gmail.com> (github.com/JacobLinCool)
 * @brief The debug header file of Jacob's Helper Library.
 * @version 2.0.0
 * @date 2022-02-28
 *
 * @copyright Copyright (c) 2022 JacobLinCool (MIT License)
 *
 */
#ifndef JACOB_HELPER_DEBUG_H
#define JACOB_HELPER_DEBUG_H

#include "base.h"

#ifdef DEBUG
#define DBG(expr) ({expr})
#define THROW(format, args...) ({ \
    fprintf(stderr, CLR_RED "[ERROR]" CLR_NONE " " format, ##args); \
    fprintf(stderr, CLR_RED "[ERROR]" CLR_NONE " at %s:%s (Line %d)\n", __FILE__, __FUNCTION__, __LINE__); \
    exit(EXIT_FAILURE); \
})
#define DBG_PRINT(format, args...) ({ \
    printf(CLR_YELLOW "[DEBUG]" CLR_NONE " " format, ##args); \
})
#else
#define DBG(expr) ((void)0)
#define THROW(format, args...) ({ \
    fprintf(stderr, CLR_RED "[ERROR]" CLR_NONE " " format, ##args); \
    exit(EXIT_FAILURE); \
})
#define DBG_PRINT(format, args...) ((void)0)
#endif

#define THROW_IF(condition, format, args...) ({ \
    if (condition) { \
        THROW(format, ##args); \
    } \
})

#endif // JACOB_HELPER_DEBUG_H
