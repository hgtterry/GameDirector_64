/*
Copyright (c) GameDirector 2019 To 2024 HGT Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "pch.h"
#include "CL64_App.h"
#include "CL64_DebugBulletWorld.h"

#pragma warning( disable : 4305)

CL64_DebugBulletWorld::CL64_DebugBulletWorld(void)
{
	Render_Debug_Flag = 1;
	m_debugMode = (DebugDrawModes)DBG_DrawWireframe;

	ColourMain = Ogre::ColourValue(0, 1, 0, 1);
	mLines = nullptr;

	btDebug_Manual = App->CL_Ogre->mSceneMgr->createManualObject("btManual");
	btDebug_Manual->setRenderQueueGroup(Ogre::RENDER_QUEUE_MAX);

	btDebug_Manual->setDynamic(true);
	btDebug_Manual->estimateVertexCount(2000);

	btDebug_Manual->begin("Template/White_Alpha", Ogre::RenderOperation::OT_LINE_LIST,App->CL_Ogre->App_Resource_Group);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(ColourMain);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(ColourMain);
	btDebug_Manual->end();

	btDebug_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	btDebug_Node->attachObject(btDebug_Manual);

	vertex_From.resize(100000);
	vertex_To.resize(100000);
	vertex_Colour.resize(100000);
	V_Count = 0;
}

CL64_DebugBulletWorld::~CL64_DebugBulletWorld(void)
{
}

void CL64_DebugBulletWorld::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
{
	//FlashWindow(App->MainHwnd,true);
}

void CL64_DebugBulletWorld::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{

}

void CL64_DebugBulletWorld::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{

	vertex_Colour[V_Count].x = color.getX();
	vertex_Colour[V_Count].y = color.getY();
	vertex_Colour[V_Count].z = color.getZ();

	vertex_From[V_Count].x = from.getX();
	vertex_From[V_Count].y = from.getY();
	vertex_From[V_Count].z = from.getZ();

	vertex_To[V_Count].x = to.getX();
	vertex_To[V_Count].y = to.getY();
	vertex_To[V_Count].z = to.getZ();
	V_Count++;

}

void CL64_DebugBulletWorld::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar)
{
	//FlashWindow(App->MainHwnd,true);
}

void CL64_DebugBulletWorld::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	//FlashWindow(App->MainHwnd,true);
}

void CL64_DebugBulletWorld::reportErrorWarning(const char* warningString)
{
	//FlashWindow(App->MainHwnd,true);
}

void CL64_DebugBulletWorld::draw3dText(const btVector3& location, const char* textString)
{
	//FlashWindow(App->MainHwnd,true);
}

void CL64_DebugBulletWorld::setDebugMode(int debugMode)
{
	m_debugMode = (DebugDrawModes)DBG_DrawWireframe;
}

int CL64_DebugBulletWorld::getDebugMode() const {

	return DBG_DrawWireframe;
}

// *************************************************************************
// *		renderQueueStarted:- Terry and Hazel Flanigan 2024			   *
// *************************************************************************
void CL64_DebugBulletWorld::renderQueueStarted(Ogre::uint8 queueGroupId, const String& invocation, bool& skipThisInvocation)
{
	Render_Debug();
}
// *************************************************************************
// *			renderQueueEnded:- Terry and Hazel Flanigan 2024		   *
// *************************************************************************
void CL64_DebugBulletWorld::renderQueueEnded(Ogre::uint8 queueGroupId, const String& invocation, bool& repeatThisInvocation)
{
	if (queueGroupId != RENDER_QUEUE_MAIN)
	{
		return;
	}

}

// *************************************************************************
// *				PreRender:- Terry and Hazel Flanigan 2024			   *
// *************************************************************************
void CL64_DebugBulletWorld::PreRender()
{

}

// *************************************************************************
// *				PostRender:- Terry and Hazel Flanigan 2024			   *
// *************************************************************************
void CL64_DebugBulletWorld::PostRender()
{

}

// *************************************************************************
// *		Render_Debug_Bullet:- Terry and Hazel Flanigan 2024			   *
// *************************************************************************
void CL64_DebugBulletWorld::Render_Debug_Bullet()
{
	Render_Debug();
}

// *************************************************************************
// *				Render_Debug:- Terry and Hazel Flanigan 2024	  	   *
// *************************************************************************
bool CL64_DebugBulletWorld::Render_Debug(void)
{
	if (Render_Debug_Flag == 1)
	{
		if (V_Count > 0)
		{
			btDebug_Manual->beginUpdate(0);

			int Count = 0;
			while (Count < V_Count)
			{
				btDebug_Manual->position(vertex_From[Count].x, vertex_From[Count].y, vertex_From[Count].z);
				btDebug_Manual->colour(ColourMain);
				btDebug_Manual->position(vertex_To[Count].x, vertex_To[Count].y, vertex_To[Count].z);
				btDebug_Manual->colour(ColourMain);
				Count++;
			}

			btDebug_Manual->end();

			V_Count = 0;
		}

	}
	else
	{
		App->Flash_Window();
		Clear_Debug_Render();
	}

	V_Count = 0;
	return 1;
}

// *************************************************************************
// *			Clear_Debug_Render:- Terry and Hazel Flanigan 2024		   *
// *************************************************************************
void CL64_DebugBulletWorld::Clear_Debug_Render()
{
	btDebug_Manual->beginUpdate(0);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(ColourMain);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(ColourMain);
	btDebug_Manual->end();
}
