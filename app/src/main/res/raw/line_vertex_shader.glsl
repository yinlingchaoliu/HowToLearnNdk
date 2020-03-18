attribute vec4 a_Position;
uniform mat4 u_ModelMatrix;
uniform mat4 u_ProMatrix;
uniform mat4 u_ViewMatrix;
void main(){
    gl_Position =  u_ProMatrix * u_ViewMatrix * u_ModelMatrix * a_Position;
    gl_PointSize = 30.0;
}
