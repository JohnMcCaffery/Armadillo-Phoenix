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

//#include "llviewerprecompiledheaders.h"

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
:	mDelta(LLVector3(0.f, 0.f, 0.f)),
	mYaw(0.f),
	mPitch(0.F)
{ }

LLViewerRemoteControl::~LLViewerRemoteControl() { }

void LLViewerRemoteControl::Tick() { 
	if (gSavedSettings.getBOOL("EnableRemoteControl")) {
		if (mPitch < 0.F) 
			gAgent.setControlFlags(AGENT_CONTROL_PITCH_POS);
		else if (mPitch > 0.F)
			gAgent.setControlFlags(AGENT_CONTROL_PITCH_NEG);


		if (mYaw < 0.F)
			gAgent.setControlFlags(AGENT_CONTROL_YAW_POS);
		else if (mYaw > 0.F)
			gAgent.setControlFlags(AGENT_CONTROL_YAW_NEG);

		
		if (! (gAgent.getFlying() || !gAgent.canFly() || gAgent.upGrabbed() || !gSavedSettings.getBOOL("AutomaticFly")) )
			gAgent.setFlying(true);

		if (mDelta[0] != 0.f)
			gAgent.moveAt(mDelta[0]);
		if (mDelta[1] != 0.f)
			gAgent.moveLeft(mDelta[1]);
		if (mDelta[2] != 0.f)
			gAgent.moveUp(mDelta[2]);
		if (mYaw != 0.f)
			gAgent.yaw(-mYaw);
		if (mPitch != 0.f)
			gAgent.pitch(-mPitch);
	}
}

void LLViewerRemoteControl::Update(LLVector3 deltas, F32 pitch, F32 yaw) {
	mPitch = pitch;
	mYaw = yaw;

	if (gSavedSettings.getBOOL("RemoteControlScaleSpeed"))
		mDelta = deltas;
	else {
		if (deltas[0] == 0.f) mDelta[0] = 0.f;
		else mDelta[0] = deltas[0] > 0.f ? 1.f : 0.f;

		if (deltas[1] == 0.f) mDelta[1] = 0.f;
		else mDelta[1] = deltas[1] > 0.f ? 1.f : 0.f;

		if (deltas[2] == 0.f) mDelta[2] = 0.f;
		else mDelta[2] = deltas[2] > 0.f ? 1.f : 0.f;
	}
}

void LLViewerRemoteControl::Reset() {
	mDelta[0] = 0.f;
	mDelta[1] = 0.f;
	mDelta[2] = 0.f;

	mPitch = 0.f;
	mYaw = 0.f;
}