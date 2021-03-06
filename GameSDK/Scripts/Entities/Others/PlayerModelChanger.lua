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
PlayerModelChanger =
{
	Properties =
	{
		objPlayerModel 		= "",
		objArmsModel			= "",
		bPreCacheModels		= 0,
	},
	
	Editor =
	{
		Model="editor/objects/box.cgf",
	},	
}

-------------------------------------------------------
function PlayerModelChanger:OnLoad(table)
  self.changePlayerModel = table.changePlayerModel
end

-------------------------------------------------------
function PlayerModelChanger:OnSave(table)
  table.changePlayerModel = self.changePlayerModel
end


----------------------------------------------------------------------------------------------------
function PlayerModelChanger:OnPropertyChange()
	self:Reset();
end


----------------------------------------------------------------------------------------------------
function PlayerModelChanger:OnReset()
	self:Reset();
end


----------------------------------------------------------------------------------------------------
function PlayerModelChanger:OnSpawn()
	self:Reset();
end


----------------------------------------------------------------------------------------------------
function PlayerModelChanger:OnDestroy()
end


----------------------------------------------------------------------------------------------------
function PlayerModelChanger:Reset()
	self:Activate(0);
	
	if (self.Properties.bPreCacheModels) then	
		local playerModel = self.Properties.objPlayerModel;
		local armsModel = self.Properties.objArmsModel;
		
		if (playerModel and (string.len(playerModel) > 0)) then
			self:LoadCharacter(0, self.Properties.objPlayerModel);
			self:DrawSlot(0, 0);
			self.changePlayerModel = true;
		end

		if (armsModel and (string.len(armsModel) > 0)) then
			self:LoadCharacter(1, self.Properties.objArmsModel);
			self:DrawSlot(1, 0);
			self.changeArmsModel = true;
		end
	end
end


----------------------------------------------------------------------------------------------------
function PlayerModelChanger:ChangeModel()
	if (g_localActor) then
		local model, arms;
		
		if (self.changePlayerModel) then
			model = self.Properties.objPlayerModel;
		end
		
		if (self.changeArmsModel) then
			arms = self.Properties.objArmsModel;
		end

		g_localActor:SetModel(model, arms);
	end
end


----------------------------------------------------------------------------------------------------
function PlayerModelChanger:Event_ChangePlayerModel(sender)
	self:ChangeModel();
	BroadcastEvent(self, "ChangeModel");
end


----------------------------------------------------------------------------------------------------
function PlayerModelChanger:Event_Reset(sender)
	self:Reset();
	BroadcastEvent(self, "Reset");
end

----------------------------------------------------------------------------------------------------

PlayerModelChanger.FlowEvents =
{
	Inputs =
	{
		ChangePlayerModel = { PlayerModelChanger.Event_ChangePlayerModel, "bool" },
		Reset = { PlayerModelChanger.Event_Reset, "bool" },
	},
	Outputs =
	{
		ChangePlayerModel = "bool",
		Reset = "bool",
	},
}
