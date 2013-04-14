/** 
 * @file llviewerjoystick.cpp
 * @brief Remote Control functionality.
 *
 * $LicenseInfo:firstyear=2002&license=viewerlgpl$
 * Second Life Viewer Source Code
 * Copyright (C) 2010, Linden Research, Inc.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation;
 * version 2.1 of the License only.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * Linden Research, Inc., 945 Battery Street, San Francisco, CA  94111  USA
 * $/LicenseInfo$
 */

#include "llviewerprecompiledheaders.h"

#include "llviewerremotecontrol.h"

#include "llviewercontrol.h"
#include "llagent.h"

//#include "llviewerwindow.h"
//#include "llviewercamera.h"
//#include "llappviewer.h"
//#include "llkeyboard.h"
//#include "lltoolmgr.h"
//#include "llselectmgr.h"
//#include "llviewermenu.h"
//#include "llagentcamera.h"
//#include "llfocusmgr.h"
//#include "llmoveview.h"

// -----------------------------------------------------------------------------
LLViewerRemoteControl::LLViewerRemoteControl()
//:	mDelta(LLVector3(0.f, 0.f, 0.f)),
:	mForward(0),
	mSlide(0),
	mFly(0),
	mYaw(0.f),
	mPitch(0.F)
{ }

LLViewerRemoteControl::~LLViewerRemoteControl() { }

void LLViewerRemoteControl::Tick() { 
	if (gSavedSettings.getBOOL("EnableRemoteControl")) {
		if (mPitch != 0.f) {
			if (mPitch < 0.f) 
				gAgent.setControlFlags(AGENT_CONTROL_PITCH_POS);
			else if (mPitch > 0.f)
				gAgent.setControlFlags(AGENT_CONTROL_PITCH_NEG);
		}


		if (mYaw != 0.f) {
			if (mYaw < 0.f)
				gAgent.setControlFlags(AGENT_CONTROL_YAW_POS);
			else if (mYaw > 0.f)
				gAgent.setControlFlags(AGENT_CONTROL_YAW_NEG);
		}

		
		if (mFly > 0 && !(gAgent.getFlying() || !gAgent.canFly() || gAgent.upGrabbed() || !gSavedSettings.getBOOL("AutomaticFly")) )
			gAgent.setFlying(true);

		gAgent.moveAt(mForward, false);
		gAgent.moveLeft(mSlide);
		gAgent.moveUp(mFly);
		gAgent.yaw(mYaw);
		if (mPitch != 0)
			gAgent.pitch(mPitch);
	}
}

void LLViewerRemoteControl::Update(LLVector3 deltas, F32 pitch, F32 yaw) {
	mPitch = pitch;
	mYaw = yaw;

	if (deltas[0] == 0.f) mForward = 0;
	else mForward = deltas[0] > 0.f ? 1 : -1;

	if (deltas[0] > gSavedSettings.getF32("RemoteControlRunThreshold"))
		gAgent.setTempRun();
	else
		gAgent.clearTempRun();

	if (deltas[1] == 0.f) mSlide = 0.f;
	else mSlide = deltas[1] > 0.f ? 1 : -1;

	if (deltas[2] == 0.f) mFly = 0.f;
	else mFly = deltas[2] > 0.f ? 1 : -1;
}

void LLViewerRemoteControl::Reset() {
	mForward = 0;
	mSlide = 0;
	mFly = 0;
	mPitch = 0.f;
	mYaw = 0.f;

	gAgent.moveAt(0);
	gAgent.moveLeft(0);
	gAgent.moveUp(0);
	gAgent.yaw(0.f);
	gAgent.pitch(0.f);
}