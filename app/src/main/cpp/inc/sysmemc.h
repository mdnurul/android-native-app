//!
//! $URL: $
//!
//! @(#)$Id: $
//!
//! \file	sysmemc.h
//!
//! \brief
//!

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

//---------------------------------------------------------------------------
#ifndef  sysmemc_h
#define  sysmemc_h
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Defines and Macros
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Typedefs
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Data
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

void* SYS_malloc(size_t size);
void* SYS_malloc_aligned(size_t alignment, size_t size);
void  SYS_free(void* ptr);
void SYS_free_aligned(void* ptr);
void* SYS_calloc(size_t num, size_t size);
void* SYS_realloc(void* ptr, size_t size);

#ifdef __cplusplus
} // extern "C"
#endif

//---------------------------------------------------------------------------
#endif	// sysmemc_h
//---------------------------------------------------------------------------
// End of File
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

