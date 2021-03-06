----------------------------------------------------------------------------------------------------
--
-- All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
-- its licensors.
--
-- For complete copyright and license terms please see the LICENSE at the root of this
-- distribution (the "License"). All use of this software is governed by the License,
-- or, if provided, by the license below or the license accompanying this file. Do not
-- remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
--
-- Original file Copyright Crytek GMBH or its affiliates, used under license.
--
----------------------------------------------------------------------------------------------------
Script.ReloadScript( "SCRIPTS/Entities/AI/Characters/Human_x.lua")
Script.ReloadScript( "SCRIPTS/Entities/actor/BasicActor.lua")
Script.ReloadScript( "SCRIPTS/Entities/AI/Shared/BasicAI.lua")

Medic_x = {
  Properties = {
    bAdditionalBool = false,
  }
}

function Medic_x:OnEnemySeen()
  AIBase.OnEnemySeen(self);
  Log(tostring("In Medic OnEnemySeen"))
  local attentionTarget = AI.GetAttentionTargetEntity(self.id);
  if ((attentionTarget.Properties.esFaction == "Friend" or attentionTarget.Properties.esFaction == "Players") and attentionTarget.actor:GetHealth() < 500 and AI.GetAttentionTargetDistance(self.id) < 2.6) then
    AI.Signal(SIGNALFILTER_SENDER, 1, "OnInjuredPlayerSeen", self.id);
  end
end

function Medic_x:HealPlayer()
  Log(tostring("Healing you buddy!"))
  local attentionTarget = AI.GetAttentionTargetEntity(self.id);
  attentionTarget.actor:SetHealth(500);
  AI.Signal(0, -1, "GoTo_GoToHostage", attentionTarget.id)
end

--mergef(Medic_x,Human_x_Medic,1)
mergef(Medic_x,Human_x,1)
CreateActor(Medic_x)
Medic=CreateAI(Medic_x)

Script.ReloadScript( "SCRIPTS/AI/Assignments.lua")
InjectAssignmentFunctionality(Medic)
AddDefendAreaAssignment(Medic)
AddHoldPositionAssignment(Medic)
AddCombatMoveAssignment(Medic)
AddPsychoCombatAllowedAssignment(Medic)

Medic:Expose()
