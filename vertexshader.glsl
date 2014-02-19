 #version 130

uniform mat4 modelMatrix;// transformed model matrix
uniform mat4 projectionMatrix;
uniform mat4 viewmodelMatrix;
uniform mat4 rot;

mat4 view;
in vec3 vertexarray;

in vec4 colorarray;
out vec4 pass_color;

void main(){
 gl_Position=projectionMatrix*viewmodelMatrix*modelMatrix*vec4(vertexarray,1); //matrix tranformation

  //gl_Position=viewmodelMatrix*modelMatrix*vec4(vertexarray,1); 
  //gl_Position= modelMatrix*vec4(vertexarray,1);
  pass_color=colorarray;
}
