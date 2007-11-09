// Shape.h: interface for the Shape class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _Shape_H_
#define _Shape_H_

#include "Renderer.h"
#include "VertexBufferManager.h"
#include "Entity2D.h"
#include "Defines.h"

#if _MSC_VER > 1000	
#pragma once
#endif // _MSC_VER > 1000

namespace zak {

enum ShapeType
{
	ZAK_SHAPE_TRIANGLE,
	ZAK_SHAPE_QUAD
};

class ZAKENGINE_API Shape : public Entity2D
{
	private:
		unsigned int   _Color;
		unsigned int   _Color1;
		unsigned int   _Color2;
		unsigned int   _Color3;
		unsigned int   _Color4;
		ShapeType   _eShapeType;
		ColorVertex _vertex[4];

	public:
		void SetColorPerVertex(DWORD dwColor1,DWORD dwColor2,DWORD dwColor3,DWORD dwColor4);
		void SetColorPerVertex(DWORD dwColor1,DWORD dwColor2,DWORD dwColor3);
		void SetColor(DWORD color);
		void SetShape(ShapeType Type);
		void SetDim(float w, float h);

		virtual void Draw();
		
		Shape ();
		virtual ~Shape ();
};

}

#endif // _Shape_H_
