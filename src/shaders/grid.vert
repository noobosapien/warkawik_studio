attribute vec2 a_position;

uniform mat4 u_model;
uniform mat4 u_viewproj;

void main(void){
    gl_Position=u_model*vec4(a_position,0.,1.);
}