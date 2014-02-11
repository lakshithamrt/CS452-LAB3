#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "vec.h"
#include "transform.h"
#include "mat.h"

#include "myshader.h" // for shader creation
#include <math.h> 
#include <vector>
#include <cstdio>
#include <iostream>

#include "Angel.h"

using namespace std;

GLint modelmatrixLoc, projectionmatrixLoc;

GLuint program_shader;


 int flag=0;

float pi=3.141592;
float theta =0;
float R=0.5;

float counter=1;//counter to increase how many vertices are going to be drawn at a given time
int j=0;

GLuint vao, vbo;//vao and vbo names


//---------------------------------------------------------------------------------------------------
//Colors for the vertices of the phyramid
vec4 colorarray[]={
    vec4 (0.5,0.5,0.5,1),vec4 (0.5,0.5,0.5,1),vec4 (-0.5,0.5,-0.5,1),
    vec4 (0.5,0.5,0.5,1),vec4 (0.5,0.5,0.5,1),vec4 (0.5,-0.5,-0.5,1),
    vec4 (0.5,0.5,0.5,1),vec4 (0,0,1,1),vec4 (0.5,0.5,0.5,1),
    vec4 (0.5,0.5,0.5,1),vec4 (0,0,1,1),vec4 (-0.5,0.5,-0.5,1),
    vec4 (0.5,0.5,0.5,1),vec4 (0,0,1,1),vec4 (-0.5,0.5,-0.5,1),
    vec4 (-0.5,0.5,0.5,1),vec4 (0,0,1,1),vec4 (0.5,0.5,-0.5,1)
};


//---------------------------------------------------------------------------------------------------

void init(void){
	
theta=-pi/6;
	//vertices of the phyramid
 vec3 vertexarray[]={
    vec3 (0.5,-0.5,-0.5),vec3 (0.5,0.5,-0.5),vec3 (-0.5,0.5,-0.5),
    vec3 (-0.5,0.5,-0.5),vec3 (-0.5,-0.5,-0.5),vec3 (0.5,-0.5,-0.5),
    vec3 (0.5,-0.5,-0.5),vec3 (0,0,0.2),vec3 (0.5,0.5,-0.5),
    vec3 (0.5,0.5,-0.5),vec3 (0,0,0.2),vec3 (-0.5,0.5,-0.5),
    vec3 (-0.5,0.5,-0.5),vec3 (0,0,0.2),vec3 (-0.5,-0.5,-0.5),
    vec3 (-0.5,-0.5,-0.5),vec3 (0,0,0.2),vec3 (0.5,-0.5,-0.5)
};
  
	
 ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL} 
  };
   

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertexarray)+sizeof(colorarray),NULL,GL_STATIC_DRAW);

  glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertexarray),vertexarray);

  glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertexarray),sizeof(colorarray),colorarray);
 

 // Load shaders and use the resulting shader program
    program_shader = BuildShaders(shaders);
    glUseProgram( program_shader );
    

  GLuint vPositionID = glGetAttribLocation( program_shader,"vertexarray" );
  GLuint vColorID = glGetAttribLocation( program_shader, "colorarray" ); 

  glVertexAttribPointer(vPositionID, 3, GL_FLOAT, GL_FALSE, 0,0);
  glVertexAttribPointer( vColorID, 4, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(sizeof(vertexarray)));
 
  glEnableVertexAttribArray( vPositionID );
  glEnableVertexAttribArray( vColorID ); 


}

//-----------------------------------------------------------------------------------------------------
void drawscene(){
  glClear(GL_COLOR_BUFFER_BIT);

  float x1,y1,z1;
  float angle,zn,zf,r;

  mat4 ctm, projmatrix;

  x1=counter;
  y1=counter;
  z1=counter;

  switch(flag){  //selction of operation for the different character input 
    case 1:
    {
      x1=counter;
      y1=counter;
      z1=counter;

     ctm=ScaleMatrix(x1,y1,z1); 
    }
break;
    case 2:{

        x1=counter;
        y1=counter;
        z1=counter;
       ctm=ScaleMatrix(x1,y1,z1);
           }
      break;
    case 3:{


      y1=counter;
      z1=0;
      x1=0;
      ctm=translate(x1,y1,z1);
    }
    break;

    case 4:{
      y1=0;
      z1=0;
      x1=counter;
      ctm=translate(x1,y1,z1);
    }
    break;

    case 5:{
      y1=counter;
      z1=0;
      x1=0;
      ctm=translate(x1,y1,z1);
    }
    break;

    case 6:{
      y1=0;
      z1=0;
      x1=counter;
      ctm=translate(x1,y1,z1);
    }
    break;

    case 7:{
      float angle= -counter;
      ctm=Rotx(angle);
    }
    break;

    case 8:{
      float angle= -counter;
      ctm=Roty(angle);
    }
    break;

    case 9:{
      float angle= counter;
      ctm=Rotx(-angle);
    }
    break;

    case 10:{
      float angle= -counter;
      ctm=Roty(angle);
    }
    break;
  }

  angle=45;
  zn=500;
  zf=1500;
  r=1;
  

  projmatrix=projection(angle,zn,zf,r);

  modelmatrixLoc = glGetUniformLocation(program_shader,"modelMatrix"); // getting the corresponding location in the vertex shader
  projectionmatrixLoc= glGetUniformLocation(program_shader,"projectionMatrix");

  if (modelmatrixLoc==-1)
    cout<<"Location is invalid"<<endl;


  glUniformMatrix4fv(modelmatrixLoc,1,GL_FALSE,ctm);//transfer the CTM to the relevant location in vertex shader
  //glUniformMatrix4fv(projectionmatrixLoc,1,GL_TRUE,projmatrix);

  cout<<"hello"<<endl;  

  for(int i=0;i<4;i++){

    cout<<ctm[i][3]<<endl;
}
  glDrawArrays(GL_TRIANGLES,0,18);
  glFlush();
}

//------------------------------------------------------------------------------------------------
void
keyboard( unsigned char key, int x, int y ) 
{
    //charactor input selection
       switch( key ) {  
    case 'Q': 
    {counter=counter+0.1;flag=1;drawscene();
    }  
    break;
    case 'E':
    {counter = counter-0.1;flag=2;drawscene();
    }
    break;
    case 'W':
    {counter = counter+0.1;flag=3;drawscene();
    }
    break;
    case 'A':
    {counter = counter-0.1;flag=4;drawscene();
    }
    break;
    case 'S':
    {counter = counter-0.1;flag=5;drawscene();
    }
    break;
    case 'D':
    {counter = counter+0.1;flag=6;drawscene();
    }
    break;

    case 'I':{

      counter=counter+1;flag=7;drawscene();
    }
    break;

    case 'J':{
      counter=counter+1;flag=8;drawscene();
    }
    break;

    case 'K':{
      counter=counter-1;flag=9;drawscene();
    }
    break;

    case 'L':{
      counter=counter-1;flag=10;drawscene();
    }
    break;
    
    case 'X':{
      exit( EXIT_SUCCESS );
    }
    break;
  }
}

//-------------------------------------------------------------------------------------------------------

int main(int argc,char ** argv){

  glutInit(&argc, argv);
  gluPerspective(120,1,1,1024);
  glutInitWindowSize(600,600);

  glutCreateWindow("phyramid");//creates the window with the specified name
  
  //initializes glew
  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  glutInitContextVersion(4, 3);//specifies the version of opengl
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);//specifies what profile your using
	
	init();

  //retruns what version of opengl and glsl your computer can use
  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);

  glutDisplayFunc(drawscene);//displays callback draws the shapes
   glutKeyboardFunc( keyboard );
  
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}

//---------------------------------------------------------------------------------------------------------