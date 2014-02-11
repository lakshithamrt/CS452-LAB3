#ifndef TRNSFORM_H_
#define TRNSFORM_H_

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "Angel.h"
#include "mat.h"


#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "GL/glu.h"

float PI = 3.1415926;

//----------------------Function Prototypes------------------------------------
mat4 ScaleMatrix(float x, float y, float z);
mat4 Rotx(float xangle);
mat4 Roty(float yangle);
mat4 Rotz(float zangle);
mat4 translate(float x, float y,float z);
mat4 projection(float fov,float znear,float zfar,float aspect);

//------------------------------------------------------------------------------
//--------------scaling of the object-------------------------------------------
mat4 ScaleMatrix(float x, float y, float z)
{
	 mat4 temp;
	 temp[0][0]=x;
	 temp[1][1]=y;
	 temp[2][2]=z;

	 return temp;
	   
	}
//-----------------------------------------------------------------------------
//----------------------Rotation arround x-axis---------------------------------
 mat4 Rotx(float xangle){
	
	float a= PI/180*xangle;
	mat4 temp;
    temp[0][0]=temp[3][3]=1;
    temp[2,2]=cos(a);
    temp[1][1]=temp[2][2];
    temp[1][2]=-sin(a);
    temp[2][1]=-temp[1][2];

    return temp;
}

//------------------------------------------------------------------------------
//--------------------Rotation arround Y-axis-----------------------------------
mat4 Roty(float yangle){
	
	float a= PI/180*yangle;
	mat4 temp;
    temp[1][1]=temp[3][3]=1;
    temp[2,2]=cos(a);
    temp[0][0]=temp[2][2];
    temp[0][2]=-sin(a);
    temp[2][0]=-temp[0][2];

    return temp;
}

//--------------------------------------------------------------------------------
//--------------------Rotation arround Z-axis-------------------------------------
mat4 Rotz(float zangle){
	
	float a= PI/180*zangle;
	mat4 temp;
    temp[2][2]=temp[3][3]=1;
    temp[1,1]=cos(a);
    temp[0][0]=temp[1][1];
    temp[0][1]=-sin(a);
    temp[1][0]=-temp[0][1];

    return temp;
}

//---------------------------------------------------------------------------------
//--------------------Translate to different location------------------------------
mat4 translate(float x,float y,float z){
	mat4 temp=identity();
	 temp[0][3]=x;
	 temp[1][3]=y;
	 temp[2][3]=z;
	 temp[3][3]= temp[2][2]= temp[1][1]= temp[0][0]=1;
	 return temp;
}

//----------------------------------------------------------------------------------
//----------------------Projection Matrix-------------------------------------------
mat4 projection(float fov,float znear,float zfar,float aspect){

  float ymax = znear * tan(fov * PI/180);
  float ymin = -ymax;


  float xmax = ymax * aspect;
  float xmin = ymin * aspect;

  float width = xmax - xmin;
  float height = ymax - ymin;

  float depth = zfar - znear;
  float q = -(zfar + znear) / depth;
  float qn = -2 * (zfar * znear) / depth;

  float w = 2 * znear / width;
  w = w / aspect;
  float h = 2 * znear / height;

  mat4 mv;

mv[1][1]=h;
mv[2][2]=q;
mv[2][3]=-1;
mv[3][3]=0;
mv[3][2]=qn;
mv[0][0]=w;

return mv;

}

#endif

//-----------------------------------------------------------------------------------

