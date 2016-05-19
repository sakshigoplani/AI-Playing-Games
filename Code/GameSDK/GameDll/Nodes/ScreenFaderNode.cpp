/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#include "StdAfx.h"
#include "ScreenFaderNode.h"
#include "GameEnvironment/GameEnvironment.h"

#include "EngineFacade/GameFacade.h"

//--------------------------------------------------------------------------------

const SInputPortConfig CFlowNode_ScreenFader::inputPorts[] =
{
	InputPortConfig_Void("FadeIn", _HELP("Fade back to normal screen")),
	InputPortConfig_Void("FadeOut", _HELP("Fade the screen out")),
	InputPortConfig<float>("FadeInTime", 2.0f, _HELP("Duration of fade in")),
	InputPortConfig<float>("FadeOutTime", 2.0f, _HELP("Duration of fade out")),
	InputPortConfig<Vec3> ("color_FadeColor", Vec3(ZERO), _HELP("Target Color to fade to")),
	InputPortConfig<bool> ("UseCurrentColor", true, _HELP("If checked, use the current color as Source color. Otherwise use [FadeColor] as Source color and Target color.")),
	InputPortConfig<string> ("tex_TextureName", _HELP("Texture Name")),
	{0},
};

CFlowNode_ScreenFader::CFlowNode_ScreenFader(IGameEnvironment& environment, SActivationInfo* activationInformation)
: m_environment(environment)
{

}

void CFlowNode_ScreenFader::GetConfiguration(SFlowNodeConfig& config)
{
	config.nFlags |= EFLN_TARGET_ENTITY;
	config.pInputPorts = inputPorts;
	config.SetCategory(EFLN_ADVANCED);
}


void CFlowNode_ScreenFader::ProcessActivateEvent(SActivationInfo* activationInformation)
{
	if (InputEntityIsLocalPlayer(activationInformation) == false)
		return;

	if (IsPortActive(activationInformation, eInputPorts_FadeIn))
	{
		const float fadeInTime = GetPortFloat(activationInformation, eInputPorts_FadeInTime);
		const Vec3 fadeColor = GetPortVec3(activationInformation, eInputPorts_FadeColor);
		const string texture = GetPortString(activationInformation, eInputPorts_Texture);
		const bool useCurrentColor = GetPortBool(activationInformation, eInputPorts_UseCurrentColor);
		ColorF color;
		color.Set(fadeColor.x, fadeColor.y, fadeColor.z);
		m_environment.GetGame().FadeInScreen(texture, color, fadeInTime, useCurrentColor);
	}
	else if (IsPortActive(activationInformation, eInputPorts_FadeOut))
	{
		const float fadeOutTime = GetPortFloat(activationInformation, eInputPorts_FadeOutTime);
		const Vec3 fadeColor = GetPortVec3(activationInformation, eInputPorts_FadeColor);
		const string texture = GetPortString(activationInformation, eInputPorts_Texture);
		const bool useCurrentColor = GetPortBool(activationInformation, eInputPorts_UseCurrentColor);
		ColorF color;
		color.Set(fadeColor.x, fadeColor.y, fadeColor.z);
		m_environment.GetGame().FadeOutScreen(texture, color, fadeOutTime, useCurrentColor);	
	}

}

void CFlowNode_ScreenFader::GetMemoryStatistics(ICrySizer* sizer)
{
	sizer->Add(*this);
}

REGISTER_FLOW_NODE_WITH_ENVIRONMENT("Crysis2FX:ScreenFader", CFlowNode_ScreenFader);
