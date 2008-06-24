/** @file
 * GameCatapult �ǐՃJ�����N���X
 *
 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
 * @date 2004/02/08 6:08:56
 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
 */
#include "common.h"
#include <gctp/scene/chasecamera.hpp>
#include <gctp/scene/camera.hpp>
#include <gctp/scene/entity.hpp>
#include <gctp/skeleton.hpp>
#include <gctp/app.hpp>
#include <gctp/dbgout.hpp>

using namespace std;

namespace gctp { namespace scene {

	ChaseCamera::ChaseCamera() : Updater(-1, 0x10), dumping_factor(0.3f), position_offset(VectorC(0, 0, 0)), posture_offset(VectorC(0, 0, 0))
	{
	}

	bool ChaseCamera::doUpdate(float delta)
	{
		Pointer<Camera> target = target_.lock();
		if(target) {
			Stance chasee_stance = chasee_->val.wtm().orthoNormal();
			chasee_stance.position += chasee_stance.posture.transform(position_offset);
			chasee_stance.posture *= QuatC(posture_offset.y, posture_offset.x, posture_offset.z);

			Stance oldstance = target->stance();
			Stance newstance;
			newstance.set2PInterpolation(oldstance, chasee_stance, dumping_factor);
			target->setStance(newstance);
		}
		return true;
	}
	
	void ChaseCamera::attach(luapp::Stack &L)
	{
		if(L.top() >= 2) {
			target_ = tuki_cast<Camera>(L[1]);
			Pointer<Entity> entity = tuki_cast<Entity>(L[2]);
			if(entity) {
				if(L.top() >= 3) {
					chasee_ = entity->skeleton()[L[3].toCStr()];
				}
				else {
					chasee_ = entity->skeleton().root();
				}
			}
		}
		else {
			target_ = 0;
			chasee_ = 0;
		}
	}

	void ChaseCamera::setPositionOffset(luapp::Stack &L)
	{
		if(L.top() >= 3) {
			position_offset = VectorC((float)L[1].toNumber(), (float)L[2].toNumber(), (float)L[3].toNumber());
		}
	}

	void ChaseCamera::setPostureOffset(luapp::Stack &L)
	{
		if(L.top() >= 3) {
			posture_offset = VectorC((float)L[2].toNumber(), (float)L[1].toNumber(), (float)L[3].toNumber());
		}
	}

	void ChaseCamera::setDumpingFactor(luapp::Stack &L)
	{
		if(L.top() >= 1) {
			dumping_factor = (float)L[1].toNumber();
		}
	}

	GCTP_IMPLEMENT_CLASS_NS2(gctp, scene, ChaseCamera, Updater);
	TUKI_IMPLEMENT_BEGIN_NS2(gctp, scene, ChaseCamera)
		TUKI_METHOD(ChaseCamera, activate)
		TUKI_METHOD(ChaseCamera, setPriority)
		TUKI_METHOD(ChaseCamera, attach)
		TUKI_METHOD(ChaseCamera, setPositionOffset)
		TUKI_METHOD(ChaseCamera, setPostureOffset)
		TUKI_METHOD(ChaseCamera, setDumpingFactor)
	TUKI_IMPLEMENT_END(ChaseCamera)

}} // namespace gctp::scene