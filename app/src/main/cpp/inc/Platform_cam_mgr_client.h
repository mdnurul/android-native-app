//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
//lint 

#include <stdlib.h>
#include "ped_config.npb.hpp"
#include "ped_enums.h"
#include "cam_mgr.h"
//lint -restore

//---------------------------------------------------------------------------
// Defines and Macros
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Typedefs
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------

//namespace camera {
	
//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------
class P1_CameraMgrClient {
public:
	P1_CameraMgrClient();
	P1_CameraMgrClient(int32_t camera_id);
	~P1_CameraMgrClient();
	
	/*void getCurrentXZZ(struct Extrinsics &,long)const;
	void getCamIntr(struct Intrinsics &,long)const;
	memmgr::SPtr<class ICameraHelper_v2> createCamHelper_v2(long)const;
	memmgr::SPtr<class ICameraHelper> createCamHelper(long)const;*/
	bool updatedSinceLastCheck(int32_t vtg_id);
	bool updatedSinceLastCheck();
	//std::string getCfgString();

private:
	bool											m_cfgLoaded;
	nanopb::PedestrianVariants						m_pedCfg;
};

//} // namespace pedalg
