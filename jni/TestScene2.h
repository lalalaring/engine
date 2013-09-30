#pragma once

#include "defines.h"
#include "SceneManaging\BaseScene.h"
#include "Logger.h"
#include "Context.h"
#include "SceneGraph/Object.h"
#include "StarComponents.h"
#include "Shaders/Shader.h"
#include "Objects/QuadCol.h"


namespace star 
{
	class Texture2D;

	class TestScene2 : public BaseScene
	{
	public:
		TestScene2(const tstring& name);
		virtual ~TestScene2() {}

		status Initialize(const Context& context);
		status Update(const Context& context);
		status Draw();

	private:
		int m_TotalFrames;
		int m_Step;
		int m_FPS;
		float m_PassedMiliseconds;
		Shader mTextureShader;

		// [COMMENT] Please don't put so much members next to eachother. 
		//			 It makes it hard to read and is impossible to see on a narrow
		//			 window layout.
		Object	*m_pObjectOne, 
				*m_pObjectTwo, 
				*m_pObjectThree,
				*m_pObjectFour, 
				*m_pObjectFive, 
				*m_pObjectSix;

		RectangleColliderComponent* m_pRectCompOne;
		CircleColliderComponent *m_pRectCompTwo;

		PathFindNodeComponent	*m_pPathFindComp, 
								*m_pPathFindCompTwo, 
								*m_pPathFindCompThree, 
								*m_pPathFindCompFour, 
								*m_pPathFindCompFive, 
								*m_pPathFindCompSix;
		
		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		TestScene2(const TestScene2& t);
		TestScene2(TestScene2&& t);
		TestScene2& operator=(const TestScene2& t);
	};
}