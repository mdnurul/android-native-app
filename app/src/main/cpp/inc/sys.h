/*!
** $URL: http://tua1-svn.vnet.valeo.com/svn/VVS_Software/trunk/sw/P2/components/sys/source/sys.h $
**
** @(#)$Id: sys.h 19688 2012-04-19 17:13:13Z blaithin.kennedy $
**
** \file	sys.h
**
** \brief	System header.
*/

/*****************************************************************************
**                                                                          **
** This program is the confidential and proprietary product of Application  **
** Solutions Limited and Valeo Vision Systems. Any unauthorised use,        **
** reproduction or transfer of this program is strictly prohibited.         **
** Copyright 2010 Application Solutions Limited and Valeo Vision Systems.   **
** (Subject to limited distribution and restricted disclosure only.)        **
** All rights reserved.                                                     **
**                                                                          **
*****************************************************************************/

#ifndef   sys_h
#define   sys_h


/*lint -esym(766,sys.h) Possibly unref */

/*
** Provide method to mark TI header files for special Lint processing.
** This must be defined prior to systypes.h as this includes TI headers.
*/
#define SYS_LINT_TI_HDR_START	/*lint -save -efreeze \
									-e451 \
									-e514 -e553 -e578 \
									-e632 -e639 \
									-e726 -e760 -e723 -e773 \
									-e829 -e845 -e835 -e849 \
									-e937 -e960 -e961 -e970 \
									-e1053 \
									-e1509 -e1510 -e1511 -e1516 -e1573 \
									-e1704 -e1717 -e1712 -e1720 -e1721 -e1724 -e1725 -e1735 -e1736 -e1790 \
									-esym(18,operator new) -esym(18,operator new[]) */
#define SYS_LINT_TI_HDR_END		/*lint -restore */

/*---------------------------------------------------------------------------
** Includes
*/

#include <systypes.h>
/*---------------------------------------------------------------------------
** Defines and Macros
*/

/*
** Provide a clean way of casting a pointer to a uint with Lint suppression.
*/

#ifdef __cplusplus
/*lint -save -e1960 -e961 function like macro used in C and C++ files so most basic definition is required */
/*lint -emacro(923,SYS_CAST_PTR_TO_UINT32) Cast ptr to int (MISRA 2004 Rule 11.3) */
#define SYS_CAST_PTR_TO_UINTPTR(ptr)		(reinterpret_cast<uintptr_t>(ptr)) 
/*lint -restore */
#else
/*lint -save -e1960 -e961 function like macro used in C and C++ files so most basic definition is required */
/*lint -emacro(923,SYS_CAST_PTR_TO_UINT32) Cast ptr to int (MISRA 2004 Rule 11.3) */
#define SYS_CAST_PTR_TO_UINTPTR(ptr)		((uintptr_t) (ptr))
/*lint -restore */
#endif

/*
** Provide a clean way of casting a uint to a void pointer with Lint suppression.
*/
/*lint -save -e1960 -e961 function like macro used in C and C++ files so most basic definition is required */
#ifdef __cplusplus
/*lint -emacro(923,SYS_CAST_PTR_TO_UINT32) Cast ptr to int (MISRA 2004 Rule 11.3) */
#define SYS_CAST_UINTPTR_TO_PTR(val)		(reinterpret_cast<void*>(val))
/*lint -restore */
#else
/*lint -emacro(923,SYS_CAST_PTR_TO_UINT32) Cast ptr to int (MISRA 2004 Rule 11.3) */
#define SYS_CAST_UINTPTR_TO_PTR(val)		((void*) (val))

#endif


/*
** Provide a way for class inline functions that need to be fast to avoid checking
** for null pointers.
*/
#define SYS_BYPASS_ALL_NULL_PTR_CHECK()	/*lint --e{613} Possible null pointer */

/*!
** \brief	Maximum value a specific signed variable will hold.
**
** Useful for asserting that a variable can hold a maximum size value.
** Assumes int32 is the largest size.
*/
/*lint -save -e1960 -e961 function like macro used in C and C++ files so most basic definition is required */
/*lint -emacro(506,SYS_MAX_SSIZE,SYS_MAX_USIZE) Constant value Boolean */
/*lint -emacro(774,SYS_MAX_SSIZE,SYS_MAX_USIZE) Constant value expression */
#define SYS_MAX_SSIZE(x)	(	(sizeof(x) == 1U) ? 			\
						 		SCHAR_MAX : 				\
						 		((sizeof(x) == 2U) ?        \
						 			SHRT_MAX :              \
						 			LONG_MAX)				\
						)

/*
** Calculate number of elements in an array.
*/

#define SYS_NUM_ELEMENTS(a)				(sizeof(a) / sizeof((a)[0]))

/*
** Macro to specify a parameter is ignored.
*/

#define SYS_UNREF_PARAM(name)			((void) name)
/*lint -restore */
/*!
** \brief	Macro to prevent c++ class copying using the default operator's
**
**			class MyClass {
**			...
**				SYS_DISABLE_COPY_OPERATOR(MyClass)
**			};
*/
/*lint -save -e1960 -e961 function like macro used in C and C++ files so most basic definition is required */
#ifdef __cplusplus
	/*lint -emacro(1736,SYS_DISABLE_COPY_OPERATOR) Redundant access specifier */
	#define SYS_DISABLE_COPY_OPERATOR(Class) \
		private: \
			Class &operator=(const Class & c);\
			/*lint -e{1704} Constructor has private access */ \
			Class(const Class & c);
#endif
/*lint -restore */
/*!
** \brief	Macro to prevent c++ class default constructor from being invoked
**			Note that this won't work if class has templated members.
**
**			class MyClass {
**			...
**				SYS_DISABLE_DEFAULT_CONSTRUCTOR(MyClass)
**			};
*/
/*lint -save -e1960 -e961 function like macro used in C and C++ files so most basic definition is required */
#ifdef __cplusplus
	/*lint -emacro(1736,SYS_DISABLE_DEFAULT_CONSTRUCTOR) Redundant access specifier */
	#define SYS_DISABLE_DEFAULT_CONSTRUCTOR(Class) \
		private: \
			/*lint -e{1704} Constructor has private access */ \
			/*lint -e{1744} member possibly not initialised */ \
			Class() {  }
#endif
/*lint -restore */

/*lint -save -e1960 -e961 used in C and C++ files so most basic definition is required.   */
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

// Maximum macro definition
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

// Absolute value macro definition
#define ABS(x) (((x) > 0) ? (x) : ((-1)*(x)))
/*lint -restore */
/////// adding the additional memory mangement part//////////

#include <sysmemc.h>
#ifdef __cplusplus
#include <sysmempool.h>
#endif //__cplusplus

/////// adding the additional memory mangement part//////////
/*---------------------------------------------------------------------------
** Typedefs
*/

/*---------------------------------------------------------------------------
** Data
*/

/*---------------------------------------------------------------------------
** Functions
*/

#endif    /* sys_h */
/*---------------------------------------------------------------------------
** End of File
*/
