/**
 * @file macros.h
 * @author ERSG group 3
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MY_MACROS_H
#define MY_MACROS_H

#if defined(__x86_64__)
#define MY_ARCH_PC
#endif
#if defined(__i386__)
#define MY_ARCH_PC
#endif

#ifndef MY_ARCH_PC
#define MY_ARCH_RASP
#endif

#endif // MY_MACROS_H
