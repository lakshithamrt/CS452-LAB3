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

GLint modelmatrixLoc, projectionmatrixLoc, viewmodelLoc, projectionLoc;

GLfloat  fovy = 0;  // Field-of-view in Y direction angle (in degrees)
GLfloat  aspect;       // Viewport aspect ratio
GLfloat  zNear = 0.5, zFar = 3.0;

GLuint program_shader;


 int flag=0;

float pi=3.141592;
float theta =0;
float R=0.5;

float counter=0;//counter to increase how many vertices are going to be drawn at a given time
int j=0;


  float x1,y11,z1;
  float angle,zn,zf,r;

  float counter1=1;
  float counter3=1;
  float counter4=1;
  float counter5=1;



  mat4 ctm, projmatrix;
  mat4 mp1,mp2;




GLuint vao, vbo;//vao and vbo names


//---------------------------------------------------------------------------------------------------
//Colors for the vertices of the phyramid
vec4 colorarray[]={
    vec4 (0.5,0.0,0.5,1),vec4 (0.0,-0.5,0.5,1),vec4 (-0.5,0.5,0.0,1),
    vec4 (0.5,0.5,0.5,1),vec4 (0.5,0.5,0.5,1),vec4 (0.5,-0.5,-0.5,1),
    vec4 (0.5,0.5,0.5,1),vec4 (0,0,1,1),vec4 (0.5,0.5,0.5,1),
    vec4 (0.5,0.5,0.5,1),vec4 (0,0,1,1),vec4 (-0.5,0.5,-0.5,1),
    vec4 (0.5,0.5,0.5,1),vec4 (0,0,1,1),vec4 (-0.5,0.5,-0.5,1),
    vec4 (-0.5,0.5,0.5,1),vec4 (0,0,1,1),vec4 (0.5,0.5,-0.5,1)
};


//---------------------------------------------------------------------------------------------------

void init(void){


    vec3 vertexarray[]={
    vec3 (0.5,-0.5,-0.5),vec3 (0.5,-0.5,0.5),vec3 (-0.5,-0.5,-0.5),
    vec3 (-0.5,-0.5,0.5),vec3 (-0.5,-0.5,-0.5),vec3 (0.5,-0.5,-0.5),
    vec3 (0.5,-0.5,-0.5),vec3 (0,0.4,0),vec3 (0.5,-0.5,0.5),
    vec3 (0.5,-0.5,0.5),vec3 (0,0.4,0),vec3 (-0.5,-0.5,0.5),
    vec3 (-0.5,-0.5,0.5),vec3 (0,0.4,0),vec3 (-0.5,-0.5,-0.5),
    vec3 (-0.5,-0.5,-0.5),vec3 (0,0.4,0),vec3 (0.5,-0.5,-0.5)
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

  glVertexAttribPointer(vPositionID, 3, GL_FLOAT, GL_TRUE, 0,0);
  glVertexAttribPointer( vColorID, 4, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(sizeof(vertexarray)));
 
  glEnableVertexAttribArray( vPositionID );
  glEnableVertexAttribArray( vColorID );

 modelmatrixLoc = glGetUniformLocation(program_shader,"modelMatrix"); // getting the corresponding location in the vertex shader
 viewmodelLoc = glGetUniformLocation(program_shader,"viewmodelMatrix");
 projectionLoc= glGetUniformLocation(program_shader,"projectionMatrix");

}

//-----------------------------------------------------------------------------------------------------
void drawscene(){
  glClear(GL_COLOR_BUFFER_BIT);

  
    vec4    eye( 0.0,0.0,0.0,1.0);
    vec4    at( 0.0, 0.0, -1.0, 1.0 );
    vec4    up( 0.0, 1.0, 0.0, 1.0 );

  angle=45;
  float a= PI/180*angle;
  fovy= a;
  aspect=1;
  zNear=0.5;
  zFar=3.0;

  mat4  mv = LookAt( eye, at, up );
  mat4  p = Perspective( fovy, aspect, zNear, zFar );  
  mat4 pj = projection();

   glUniformMatrix4fv(modelmatrixLoc,1,GL_TRUE,ctm);//trr the CTM to the relevant location in vertex shader

   glUniformMatrix4fv(viewmodelLoc,1,GL_TRUE,mv);
   glUniformMatrix4fv( projectionLoc, 1, GL_TRUE, pj );
  
 

  cout<<"hello"<<endl;  

  for(int i=0;i<4;i++){

    cout<<mp1[3][i]<<endl;
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
    {counter1=counter1+0.1;

      x1=(counter1);
      y11=(counter1);
      z1=(counter1);

     ctm=ScaleMatrix(x1,y11,z1); 

    }  
    break;
    case 'E':
    {
      
      counter1 = abs(counter1-0.1);
      x1=counter1;
      y11=counter1;
      z1=counter1;
      ctm=ScaleMatrix(x1,y11,z1);
    }
    break;
    case 'W':
    {
     counter3 = counter3+0.1;
     y11=counter3;
      z1=0;
      x1=0;
      ctm=translate(x1,y11,z1);

    }
    break;
    case 'A':
    {

      counter4= counter4-0.1;
      y11=0;
      z1=0;
      x1=counter4;
      ctm=translate(x1,y11,z1);
    }
    break;
    case 'S':
    {
      counter3 = counter3-0.1;
      y11=counter3;
      z1=0;
      x1=0;
      ctm=translate(x1,y11,z1);
    }
    break;
    case 'D':
    {counter4 = counter4+0.1;
      y11=0;
      z1=0;
      x1=counter4;
      ctm=translate(x1,y11,z1);
    }
    break;

    case 'I':{


      counter5=counter5-0.5;
      float angle= counter5;

       if (sin(angle) == -1)
        counter5 = 0;

      mp1=translate(0.0,0.0,0.0);
      ctm=mp1*Rotx(angle);
    }
    break;

    case 'L':{
      counter=counter+0.5;
      float angle= counter;

      if (sin(angle) == 1)
        counter = 0;

     mp2=Roty(angle);
     ctm = mp2;
    }
    break;

    case 'K':{
      counter5=counter5+0.5;
      float angle= counter5;

      if (sin(angle) == 1)
        counter5 = 0;
      mp1=translate(0.0,0.0,0.0);
      ctm=Rotx(angle);
    }
    break;

    case 'J':{
      counter= counter-0.5;
      float angle= counter;
      if (sin(angle) == -1)
        counter = 0;
      ctm=Roty(angle);
    }
    break;
    
    case 'X':{
      exit( EXIT_SUCCESS );
    }
    break;
  }

 glutPostRedisplay();

}

//-------------------------------------------------------------------------------------------------------

int main(int argc,char ** argv){

  glutInit(&argc, argv);
  
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