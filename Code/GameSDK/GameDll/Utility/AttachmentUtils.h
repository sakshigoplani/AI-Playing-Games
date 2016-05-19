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

#ifndef __ATTACHMENTUTILS_H__
#define __ATTACHMENTUTILS_H__

struct IAttachment;
struct SEntitySlotInfo;
struct IEntity;

namespace AttachmentUtils
{
	const int kDefaultPlayerMainSlot = 0;
	const int kDefaultPlayerShadowSlot = 5;

	enum EAttachmentFlags
	{
		eAF_SyncCloak					=BIT(0),
		eAF_SyncRenderNearest	=BIT(1),
		eAF_AllowShadowCharAtt=BIT(2),

		eAF_Default = eAF_SyncCloak|eAF_SyncRenderNearest|eAF_AllowShadowCharAtt,
	};
	typedef uint8 TAttachmentFlags;

	int FindFirstRenderedSlot( const IEntity* pEntity );
	bool IsEntityRenderedInNearestMode( const IEntity* pEntity );
	void SetEntityRenderInNearestMode( IEntity* pEntity, const bool drawNear );
	void SyncRenderInNearestModeWithEntity( IEntity* pMasterEntity, IEntity* pSlaveEntity );
	void SyncCloakWithEntity( const EntityId masterEntityId, const IEntity* pSlaveEntity, const bool forceDecloak = false );
	void SetupShadowAttachmentBinding( IEntity* pPlayerEntity, IEntity* pObjectEntity, const uint32 attNameCRC32Lower, const int shadowSlotIndex = kDefaultPlayerShadowSlot, const bool bAllowCharacters = true );
	void SetupEntityAttachmentBinding( IAttachment* pPlayerAttachment, const EntityId objectEntityId );
	IAttachment* GetAttachment( IEntity* pEntity, const char* pAttachmentName, const int slotIndex );
	IAttachment* GetAttachment( IEntity* pEntity, const uint32 attNameCRC32Lower, const int slotIndex );
	
	void AttachObject( const bool bFirstPerson, IEntity* pPlayerEntity, IEntity* pObjectEntity, const char* pAttachmentName, const TAttachmentFlags flags = eAF_Default, const int playerMainSlot = kDefaultPlayerMainSlot, const int playerShadowSlot = kDefaultPlayerShadowSlot );
	void AttachObject( const bool bFirstPerson, IEntity* pPlayerEntity, IEntity* pObjectEntity, const uint32 attNameCRC32Lower, const TAttachmentFlags flags = eAF_Default, const int playerMainSlot = kDefaultPlayerMainSlot, const int playerShadowSlot = kDefaultPlayerShadowSlot );
	void DetachObject( IEntity* pPlayerEntity, IEntity* pObjectEntity, const char* pAttachmentName, const TAttachmentFlags flags = eAF_Default, const int playerMainSlot = kDefaultPlayerMainSlot, const int playerShadowSlot = kDefaultPlayerShadowSlot );
	void DetachObject( IEntity* pPlayerEntity, IEntity* pObjectEntity, const uint32 attNameCRC32Lower, const TAttachmentFlags flags = eAF_Default, const int playerMainSlot = kDefaultPlayerMainSlot, const int playerShadowSlot = kDefaultPlayerShadowSlot );
}

#endif // __ATTACHMENTUTILS_H__
