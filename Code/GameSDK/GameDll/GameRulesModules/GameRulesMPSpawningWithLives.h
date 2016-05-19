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

#ifndef __GAMERULES_MP_SPAWNING_WITH_LIVES_H__
#define __GAMERULES_MP_SPAWNING_WITH_LIVES_H__

#include "GameRulesMPSimpleSpawning.h"
#include "GameRulesModules/IGameRulesPlayerStatsListener.h"
#include "GameRulesModules/IGameRulesRoundsListener.h"

class CGameRulesMPSpawningWithLives :	public CGameRulesRSSpawning,
																			public IGameRulesPlayerStatsListener
{
private:

	typedef CGameRulesRSSpawning  inherited;

protected:

	typedef CryFixedStringT<32> TFixedString;

	struct SElimMarker
	{
		EntityId  markerEid;
		EntityId  playerEid;
		float  time;
	};

	static const int  m_kMaxElimMarkers = MAX_PLAYER_LIMIT;

protected:

	SElimMarker  m_elimMarkers[m_kMaxElimMarkers];

	TFixedString  m_tmpPlayerEliminatedMsg;
	TFixedString  m_tmpPlayerEliminatedMarkerTxt;

	SElimMarker*  m_freeElimMarker;

	int  m_numLives;
	int  m_dbgWatchLvl;
	float  m_elimMarkerDuration;
	bool m_bLivesDirty;

public:

	// (public data)

public:

	CGameRulesMPSpawningWithLives();
	virtual ~CGameRulesMPSpawningWithLives();

	// IGameRulesSpawningModule
	virtual void ReviveAllPlayers(bool isReset, bool bOnlyIfDead);
	virtual int  GetRemainingLives(EntityId playerId);
	virtual int  GetNumLives()  { return m_numLives; }
	// ~IGameRulesSpawningModule

	// IGameRulesKillListener - already inherited from in CGameRulesMPSpawningBase
	virtual void OnEntityKilled(const HitInfo &hitInfo);
	// ~IGameRulesKillListener

	// IGameRulesRevivedListener
	virtual void EntityRevived(EntityId entityId);
	// ~IGameRulesRevivedListener

	// IGameRulesPlayerStatsListener
	virtual void ClPlayerStatsNetSerializeReadDeath(const SGameRulesPlayerStat* s, uint16 prevDeathsThisRound, uint8 prevFlags);
	// ~IGameRulesPlayerStatsListener

	// IGameRulesRoundsListener
	virtual void ClRoundsNetSerializeReadState(int newState, int curState);
	// ~IGameRulesRoundsListener

protected:

	virtual void Init(XmlNodeRef xml);
	virtual void Update(float frameTime);

	virtual void PerformRevive(EntityId playerId, int teamId, EntityId preferredSpawnId);
	virtual void PlayerJoined(EntityId playerId);
	virtual void PlayerLeft(EntityId playerId);

	void OnPlayerElimination(EntityId playerId);
	void SvNotifySurvivorCount();

	void CreateElimMarker(EntityId playerId);
	void UpdateElimMarkers(float frameTime);
	void RemoveAllElimMarkers();

	bool IsInSuddenDeath();
};


#endif // __GAMERULES_MP_SPAWNING_WITH_LIVES_H__
