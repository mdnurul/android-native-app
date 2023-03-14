//!
//! $URL: $
//!
//! @(#)$Id: $
//! 
//! \author Vaclav Mocek
//!
//! \file	sysmempool.h
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
#ifndef  sysmempool_h
#define  sysmempool_h
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <sysmempoolallocator.h>

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

//---------------------------------------------------------------------------
//! \class	SysMemPool
//!
//! \brief	Memory pool - see an example of usage bellow.
//! 
//! \note	Not thread safe.	  
//!
template <typename T0, typename T1> 
class SysMemPool
{
public:
	SysMemPool(void) {
		a.init();
	}

	virtual ~SysMemPool(void) {}

	inline void* alloc(size_t n) {
		
		if (sizeof(T0) != n) {
		  	//XXX: An assert here ...
			return 0;
		}

		return a.allocate();
	}

	inline void free(void* p) {
		a.deallocate(p);
	}
private:
		T1 a;
};

//---------------------------------------------------------------------------
#ifdef AN_EXAMPLE_OF_USAGE // Newer define that!
// An example of usage - a memory pool for class AClass, which uses allocator
// SysMemPoolAllocatorHeapFast.
class AClass
{
public:
	AClass(void) {}
	virtual ~AClass(void) {}

	// operator "new" and "delete" are overloaded
	// XXX: if gcc is used, the flag "-fcheck-new" must be used.
	void* operator new(size_t n) {
		void* mem = m_pool.alloc(n);
		if (mem == 0) {
 			// the allocation of memory failed
			;
		}
		return mem;
	}
	void operator delete(void* p) {
		m_pool.free(p);
	}

private:
	// a memory pool
	typedef SysMemPool<AClass, SysMemPoolAllocatorHeapFast<AClass, 32U> > MemoryPool;
	static MemoryPool m_pool;
	// array operators should be disabled
	void* operator new[](size_t n) { return 0;}
	void operator delete[](void* p) {;}
};

// create an instance of memory pool
AClass::MemoryPool AClass::m_pool;
#endif //AN_EXAMPLE_OF_USAGE
//---------------------------------------------------------------------------
} // namespace sys

//---------------------------------------------------------------------------
#endif	// sysmempool_h
//---------------------------------------------------------------------------
// End of File
//---------------------------------------------------------------------------

