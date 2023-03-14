#pragma once

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <camhelper.h>
#include <camerafisheye.h>
#include <camera_types.h>


class NewCam : public ICameraHelper_v2 {
public:
	NewCam() {};
		
	~NewCam() {};
	
	virtual void
	configure(
		const camera::Extrinsics& 		camPosRot,	 /* In  */
		const camera::Intrinsics&		camInt,       /* In  */
		const bool          useRearAxleCoords,       /* In  */
        const uint32_t      wheelBase_mm      		/* In  */
	) {

		m_cameraFisheye.configure(camInt, camPosRot);
		
	}
	
	virtual void
	configure(
		const camera::Extrinsics& 		camPosRot,	 /* In  */
		const camera::IntrinsicsMagna&		camInt,       /* In  */
		const bool          useRearAxleCoords,       /* In  */
        const uint32_t      wheelBase_mm = 0U       		/* In  */
	) {

		m_cameraFisheye.configure(camInt, camPosRot);
		
	}
	
	virtual bool
	mapWorldToRaw(
		FLOAT& x,								/* Out */
		FLOAT& y,								/* Out */
		const VEC& wldPt						/* In  */
	) const {
		lalgebra::Vector2 px;
		lalgebra::Vector3 ret;
		ret.x() = wldPt.x;
		ret.y() = wldPt.y;
		ret.z() = wldPt.z;
		bool status = m_cameraFisheye.worldPtToRaw(ret, px);
		x = px.x();
		y = px.y();		
		return status;
	}
	
	virtual bool 
	mapRawToGround(
		VEC&				wldPt,				/* Out	*/
		FLOAT&				x,					/* In	*/
		FLOAT&				y					/* In	*/

	) const {
		lalgebra::Vector2 px;
		lalgebra::Vector3 wldPnt;
		px.x() = x;
		px.y() = y;
		bool ret = m_cameraFisheye.rawToGroundPlanePt(wldPnt, px);
		wldPt.x = wldPnt.x();
		wldPt.y = wldPnt.y();
		wldPt.z = wldPnt.z();
		return ret;
	}

	virtual bool 
	mapRawToPlane(
		VEC&				wldPt,				/* Out	*/
		FLOAT&				x,					/* In	*/
		FLOAT&				y,					/* In	*/
		FLOAT&				z_offset			/* In	*/

	) const {
		lalgebra::Vector2 px;
		lalgebra::Vector3 wldPnt;
		px.x() = x;
		px.y() = y;
		bool ret = m_cameraFisheye.rawToHorizontalPlanePt(wldPnt, px, z_offset);
		wldPt.x = wldPnt.x();
		wldPt.y = wldPnt.y();
		wldPt.z = wldPnt.z();
		return ret;
	}

	virtual bool 
	mapRawToWorldRay(
		VEC&				wldRay,				
		FLOAT&				x,					
		FLOAT&				y					

	) const {
		lalgebra::Vector3 wrldRay;
		//wrldRay = m_cameraFisheye.rawToWorldRay(x, y);
		bool status = m_cameraFisheye.rawToWorldRay(wrldRay, x, y);
		wldRay.x = wrldRay.x();
		wldRay.y = wrldRay.y();
		wldRay.z = wrldRay.z();
		return status;
	}

	virtual void 
	addWorldRotDevXYZ(
		camera::Rotation&	camRotOut,			/* Out	*/	
		const FLOAT&		dx_rad,				/* In	*/
		const FLOAT&		dy_rad,				/* In	*/
		const FLOAT&		dz_rad				/* In	*/

	) {
		m_cameraFisheye.addWorldRotDevXYZ(dx_rad, dy_rad, dz_rad);
		m_cameraFisheye.getCurrentRotationsXZZ(camRotOut.x_rad, camRotOut.z1_rad, camRotOut.z2_rad);
	}
	
	virtual void 
	addCameraRotDevXYZ(
		camera::Rotation&	camRotOut,			/* Out	*/	
		const FLOAT&		dx_rad,				/* In	*/
		const FLOAT&		dy_rad,				/* In	*/
		const FLOAT&		dz_rad				/* In	*/

	) {
		m_cameraFisheye.addCameraRotDevXYZ(dx_rad, dy_rad, dz_rad);
		m_cameraFisheye.getCurrentRotationsXZZ(camRotOut.x_rad, camRotOut.z1_rad, camRotOut.z2_rad);
	}

	virtual void 
	setCamPose(
		const camera::Extrinsics&		camPose			/* In  */
	) {
		m_cameraFisheye.setExtrinsicPosition(camPose.pos.x_mm, camPose.pos.y_mm, camPose.pos.z_mm);

		m_cameraFisheye.setExtrinsicRotationsXZZ(camPose.rot.x_rad, camPose.rot.z1_rad, camPose.rot.z2_rad);
	}

    virtual camera::Position 
	getCamPosition(
		void
	) const {
        lalgebra::Vector3 pos = m_cameraFisheye.getExtrinsicPosition();
        camera::Position position;
        position.x_mm = pos.x();
        position.y_mm = pos.y();
        position.z_mm = pos.z();
        
        return position;
    }

	virtual void
	getImageDimensions(
		FLOAT&	width_px,
		FLOAT&  height_px
	) const {
		lalgebra::Vector2 img_px = m_cameraFisheye.getImageDimensions();
		width_px = img_px.x();
		height_px = img_px.y();
	}

	virtual void
	getCamera2WorldRotMatrix(
		lalgebra::Matrix3x3& camera2WorldRotMatrix	
	) const {
		camera2WorldRotMatrix = m_cameraFisheye.getCamToWldRotMatrix();
	}

	virtual void
	getWorld2CameraRotMatrix(
		lalgebra::Matrix3x3& world2CameraRotMatrix	
	) const {
		world2CameraRotMatrix = m_cameraFisheye.getWldToCamRotMatrix();
	}
	
	virtual bool
		mapCamRayToRaw(
		FLOAT& x,								/* Out */
		FLOAT& y,								/* Out */
		const VEC& wldPt						/* In  */
	) const {
		lalgebra::Vector3 cameraRay;
		cameraRay.x() = wldPt.x;
		cameraRay.y() = wldPt.y;
		cameraRay.z() = wldPt.z;
		lalgebra::Vector2 px;
		bool ret = m_cameraFisheye.cameraRayToRaw(cameraRay, px);
		x = px.x();
		y = px.y();
		return ret;
	}

	virtual bool
	mapCamRayToRaw(
		lalgebra::Vector2& ret,
		const lalgebra::Vector3& camRay_mm
	) const {
		return m_cameraFisheye.cameraRayToRaw(camRay_mm, ret);
	}

	virtual bool
	mapWorldToRaw(	
		lalgebra::Vector2& ret,
		const lalgebra::Vector3& wldPt_mm
	) const {
		return m_cameraFisheye.worldPtToRaw(wldPt_mm, ret);
	}

	virtual bool 
	mapRawToGround(
		lalgebra::Vector3& retGdPt_mm,		
		const lalgebra::Vector2& imPt_px	
	) const {
		return m_cameraFisheye.rawToGroundPlanePt(retGdPt_mm, imPt_px);
	}

	virtual bool 
	mapRawToPlane(
		lalgebra::Vector3& retPlPt_mm,	
		const lalgebra::Vector2& imPt_px,
		const FLOAT& planeZ_mm	
	) const {
		return m_cameraFisheye.rawToHorizontalPlanePt(retPlPt_mm, imPt_px, planeZ_mm);
	}

	virtual bool 
	mapRawToWorldRay(
		lalgebra::Vector3& wldRay_mm,		
		const lalgebra::Vector2& imPt_px
	) const {
		//wldRay_mm = m_cameraFisheye.rawToWorldRay(imPt_px);
		return m_cameraFisheye.rawToWorldRay(wldRay_mm, imPt_px);
	}
	
	virtual void
    getMaxMappingImageRadius(
        lalgebra::Vector2& imageCenter,
        FLOAT& imageRadius
    ) const {
        return m_cameraFisheye.getMaxMappingImageRadius(imageCenter, imageRadius);
    }
	
	virtual camera::FISHEYE_MODEL
		getFishEyeModel() const {
		return m_cameraFisheye.getFishEyeModel();
	}
	
private:	
	camera::CameraFisheye m_cameraFisheye;
};



