#pragma once
#include "Vector4D.h"
#include <vector>
#include <list>
#include <algorithm>

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "GL\glew.h"

const float fPI = 3.1415926535897f;
const float fEPS = 0.00001f; //option 0.01f,     //0.0001
const float fEPS_POINT = 0.01f;



class CMath3D
{
public:
	static bool ArePointsOverlapped(const CVector4D* pP0, const CVector4D* pP1);																		
	static bool ArePointsOverlapped(const CVector4D& rP0, const CVector4D& rP1);
};



