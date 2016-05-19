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
#include "HUDOnScreenMessageDef.h"
#include "HUDControllerInputIcons.h"
#include <IItemSystem.h>

SOnScreenMessageDef::SOnScreenMessageDef()
{
	m_pInputRenderInfo = new CControllerInputRenderInfo;
	m_lifespan = 0.f;
}

SOnScreenMessageDef::SOnScreenMessageDef(const SOnScreenMessageDef& _in)
{
	m_pInputRenderInfo = new CControllerInputRenderInfo;
	*m_pInputRenderInfo = *(_in.m_pInputRenderInfo);
	m_lifespan = _in.m_lifespan;
	m_onScreenMessageText = _in.m_onScreenMessageText;
}

SOnScreenMessageDef::~SOnScreenMessageDef()
{
	SAFE_DELETE(m_pInputRenderInfo);
}

void SOnScreenMessageDef::operator=(const SOnScreenMessageDef & fromHere)
{
	m_lifespan = fromHere.m_lifespan;
	*m_pInputRenderInfo = *(fromHere.m_pInputRenderInfo);
	m_onScreenMessageText = fromHere.m_onScreenMessageText;

//CryLog ("[HUD MESSAGE DEFINITION] Copied: '%s' lifespan=%f (type %d, '%s') vanish=%u", m_onScreenMessageText.c_str(), m_lifespan, m_inputRenderInfo.GetType(), m_inputRenderInfo.GetText(), m_vanishSettings);
}

void SOnScreenMessageDef::Read(const XmlNodeRef xml)
{
	// Read on-screen message text
	m_onScreenMessageText = xml->getAttr("display");

	// Read prompt icon information
	const char * inputMapName = xml->getAttr("inputMapName");
	const char * inputName = xml->getAttr("inputName");
	CRY_ASSERT_MESSAGE((inputMapName == NULL) == (inputName == NULL), string().Format("Provided %s", inputMapName ? "inputMapName but not inputName" : "inputName but not inputMapName"));
	if ((inputMapName != NULL) && (inputMapName[0]) && (inputName != NULL) && inputName[0])
	{
		m_pInputRenderInfo->CreateForInput(inputMapName, inputName);
	}

	// Read lifespan
	xml->getAttr("lifespan", m_lifespan);

//CryLog ("[HUD MESSAGE DEFINITION] Read from XML: '%s' lifespan=%f (type %d, '%s') vanish=%u", m_onScreenMessageText.c_str(), m_lifespan, m_inputRenderInfo.GetType(), m_inputRenderInfo.GetText(), m_vanishSettings);
}
