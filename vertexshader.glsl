 #version 130

uniform mat4 modelMatrix;// transformed model matrix
uniform mat4 projectionMatrix;

in vec3 vertexarray;

in vec4 colorarray;
out vec4 pass_color;

void main(){
 //gl_Position=projectionMatrix*modelMatrix*vec4(vertexarray,1); 
gl_Position=modelMatrix*vec4(vertexarray,1); 
  //gl_Position=vec4(vertexarray,1);
  pass_color=colorarray;
}
