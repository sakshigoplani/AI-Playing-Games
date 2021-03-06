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
CameraFocus = 
{
	type = "CameraFocus",

	Editor=
	{
		Model="Objects/Editor/T.cgf",
	},
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:OnInit()
	self:Activate(0);
end

function CameraFocus:OnReset()
	self:GotoState( "Inactive" );
end

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:OnContact( Entity )
end

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:OnDamage( Hit )
end

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:OnShutDown()
end

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:OnEvent( EventId, Params )
end

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:OnSave( stm )
end

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:OnLoad( stm )
end

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:OnWrite( stm )
end

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:OnRead( stm )
end
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:Event_Enable()
	self:GotoState( "Active" );
end

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
function CameraFocus:Event_Disable()
	self:GotoState( "Inactive" );
end

CameraFocus.Active =
{
	-------------------------------------------------------------------------------
	OnBeginState = function( self )
		self:Activate(1);
		--System.SetFocusPos( self:GetPos() );
	end,
	-------------------------------------------------------------------------------
	OnEndState = function( self )
		self:Activate(0);
	end,

	-------------------------------------------------------------------------------
	OnUpdate = function( self )
		--System.SetFocusPos( self:GetPos() );
	end,
}

CameraFocus.Inactive =
{
	-------------------------------------------------------------------------------
	OnBeginState = function( self )
		self:Activate(0);
	end,
}

CameraFocus.FlowEvents =
{
	Inputs =
	{
		Disable = { CameraFocus.Event_Disable, "bool" },
		Enable = { CameraFocus.Event_Enable, "bool" },
	},
	Outputs =
	{
		Disable = "bool",
		Enable = "bool",
	},
}
