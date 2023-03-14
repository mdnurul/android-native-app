//!
//! $URL: $
//!
//! @(#)$Id: $
//!
//! \author Vaclav Mocek
//!
//! \file	sysmempoolallocator.h
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
#ifndef  sysmempoolallocator_h
#define  sysmempoolallocator_h
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "sysmemc.h"

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

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------
namespace sys {


// The class AnAllocator has to implement three methods:
// 
// template <T>
// class AnAllocator {
//
// 		AnAllocator(void) {}
// 		virtual ~AnAllocator(void) {}
// 		...
//		void init(void) {
//			// initialize the resources
//		}
//
//		void* allocate(void) {
//			// return a block of memory of size sizeof(T),
//			// if not available returns 0
//			return something;
//		}
//
//		void deallocate(void* p) {
//			// deallocates the memory bloc pointed by p
//		}
//		...
// };


//---------------------------------------------------------------------------
//! \class      SysMemPoolAllocatorHeap
//!
//! \brief      A memory pool allocator, which directly uses the heap.
//!
template <typename T> 
class SysMemPoolAllocatorHeap {
public:
	SysMemPoolAllocatorHeap(void) {}

	virtual ~SysMemPoolAllocatorHeap(void) {}

	void init(void) {}

	void* allocate(void) {
	  return SYS_malloc(sizeof(T));
	}

	void deallocate(void* p) {
		SYS_free(p);
	}
};

//---------------------------------------------------------------------------
//! \class      SysMemPoolAllocatorHeapFast
//!
//! \brief      A memory pool allocator, which uses the heap - a fast way
//!				with a fix number of elements.
//!
template <typename T, uint32_t N> 
class SysMemPoolAllocatorHeapFast {
public:
	SysMemPoolAllocatorHeapFast(void):
		m_num_slots_available(0U)
	{
		m_buffer = (uint8_t*)SYS_malloc(sizeof(T) * N);
		if (m_buffer != 0) {
			m_num_slots_available = N;
			m_slots[0] = 0U;
			for (uint32_t i = 1U; i <= N; ++i) {

				m_slots[i] = reinterpret_cast<T*>(&m_buffer[sizeof(T) * (i - 1U)]);
			}		
		}
		else {

			// XXX: SYS_malloc failed ...
			;
		}	
	}

	virtual ~SysMemPoolAllocatorHeapFast(void) {
		if (m_buffer) {
			SYS_free((void*)m_buffer);
			m_buffer = 0U;
		}
	}

	void init(void) {}

	void* allocate(void) {

		if ((m_num_slots_available == 0U) || (m_buffer == 0U)) {
			return 0;
		}
	
		T* t = m_slots[1U];
		m_slots[1U] = m_slots[m_num_slots_available];
		m_slots[m_num_slots_available] = 0U;
		--m_num_slots_available;
		
		return t;
	}

	void deallocate(void* p) {
		if ( (p == 0) || (m_num_slots_available >= N) ) {
			return;
		}

		++m_num_slots_available;
		m_slots[m_num_slots_available] = reinterpret_cast<T*>(p);
	}
	
private:
	uint32_t m_num_slots_available;
	T* m_slots[N + 1U];
	uint8_t* m_buffer;
};


//---------------------------------------------------------------------------
//! \class      SysMemPoolAllocatorStatic
//!
//! \brief      A memory pool allocator, which allocates objects in a static
//!				array.
//!
template <typename T, uint32_t N> 
class SysMemPoolAllocatorStatic {
public:
	SysMemPoolAllocatorStatic(void):
		m_num_slots_available(N)
	{	
		m_slots[0U] = 0;
		for (uint32_t i = 1U; i <= N; ++i) {
			m_slots[i] = reinterpret_cast<T*>(&m_buffer[sizeof(T) * (i - 1U)]);
		}
	}

	virtual ~SysMemPoolAllocatorStatic(void) {}

	void init(void) {}

	void* allocate(void) {

	 	if (m_num_slots_available == 0U) {
			return 0;
		}
	
		T* t = m_slots[1U];
		m_slots[1U] = m_slots[m_num_slots_available];
		m_slots[m_num_slots_available] = 0;
		--m_num_slots_available;
		
		return t;
	}

	void deallocate(void* p) {
		if ( (p == 0) || (m_num_slots_available >= N) ) {
			return;
		}

		++m_num_slots_available;
		m_slots[m_num_slots_available] = reinterpret_cast<T*>(p);
	}
	
private:
	uint32_t m_num_slots_available;
	T* m_slots[N + 1U];
	uint8_t m_buffer[sizeof(T) * N];
};
} // namespace sys

//---------------------------------------------------------------------------
#endif	// sysmempoolallocator_h
//---------------------------------------------------------------------------
// End of File
//---------------------------------------------------------------------------

