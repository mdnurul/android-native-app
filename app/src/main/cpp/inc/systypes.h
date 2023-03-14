/*!
** $URL: http://svn.cel/svn/VVS_Software/release_candidate/BMW/iCAM_SVS/VVS_B6/RC13/source/BMW_iCAM_SVS_VVS_B6_RC13_V05.00.0A.00/P2/components/sys/source/arch/i386_linux/systypes.h $
**
** @(#) $Id: systypes.h 869 2011-03-29 18:19:57Z kellawaytrevor $
**
** \file	systypes.h
**
** \brief	Generic defines and types.
*/

/*****************************************************************************
**                                                                          **
** This program is the confidential and proprietary product of Application  **
** Solutions Limited and Valeo Vision Systems. Any unauthorised use,        **
** reproduction or transfer of this program is strictly prohibited.         **
** Copyright 2007 Application Solutions Limited and Valeo Vision Systems.   **
** (Subject to limited distribution and restricted disclosure only.)        **
** All rights reserved.                                                     **
**                                                                          **
*****************************************************************************/

#ifndef   systypes_h
#define   systypes_h

/*---------------------------------------------------------------------------
** Includes
*/

#ifdef __GNUC__
	#include <stddef.h>
	#include <stdint.h>
#endif

/*---------------------------------------------------------------------------
** Defines and Macros
*/

#ifndef NULL
	#ifdef __cplusplus
		#define NULL 		0
	#else
		#define NULL 		((void *) 0)
	#endif
#endif

/** @name Boolean constants
*/
/*@{*/
#ifdef TRUE
	#undef TRUE
#endif
#ifdef FALSE
	#undef FALSE
#endif
#define TRUE        		((bool) 1)
#define FALSE       		((bool) 0)
/*@}*/

/*---------------------------------------------------------------------------
** Typedefs
*/

#ifdef __cplusplus
extern "C" {
#endif

/** @name Base types
*/
/*@{*/
typedef signed char			int8;
typedef unsigned char		uint8;
typedef signed short		int16;
typedef unsigned short		uint16;

/*
** On the simulator we can't redefine bool, as some Qt function overloading
** then fails due to duplicates, so leave as a different type, and we will
** inhibit Lint for the simulator from overall checking.
*/
#ifndef __cplusplus
	typedef uint8    		bool;
#endif

typedef signed long			int32;
typedef unsigned long		uint32;
typedef signed long			int40;
typedef unsigned long		uint40;
//typedef signed long long	int64;
//typedef unsigned long long	uint64;
/*@}*/

/** @name Shorthand version of fast types
**
** Modify these for the best implementation for a specific CPU architecture.
*/
/*@{*/
typedef int8				intf8;
typedef uint8				uintf8;
typedef int16				intf16;
typedef uint16				uintf16;
typedef int32				intf32;
typedef uint32				uintf32;
/*@}*/

/** @name Draft ISO fast names (for compatibility)
*/
/*@{*/
#ifndef __GNUC__
	typedef int8			int8_t;
	typedef int16			int16_t;
	typedef int32			int32_t;
	typedef uint8			uint8_t;
	typedef uint16			uint16_t;
	typedef uint32			uint32_t;
	typedef intf8			int_fast8_t;
	typedef intf16			int_fast16_t;
	typedef intf32			int_fast32_t;
	typedef uintf8			uint_fast8_t;
	typedef uintf16			uint_fast16_t;
	typedef uintf32			uint_fast32_t;
	typedef int64           int64_t
	typedef uint64          uint64_t
#endif
/*@}*/

/*!
** \brief	Our own character type (to avoid MISRA warnings of direct 'char' use).
*/
typedef char CHAR;


/*!
** \brief	Our own float type (to avoid MISRA warnings of direct 'float' use).
*/
typedef float FLOAT;

/*!
** \brief	Our own double type (to avoid MISRA warnings of direct 'double' use).
*/
typedef double DOUBLE;

/*---------------------------------------------------------------------------
** Data
*/

/*---------------------------------------------------------------------------
** Functions
*/


#ifdef __cplusplus
}
#endif

#endif    /* systypes_h */
/*---------------------------------------------------------------------------
** End of File
*/
