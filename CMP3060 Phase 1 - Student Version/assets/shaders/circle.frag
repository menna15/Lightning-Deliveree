#version 330 core

out vec4 frag_color;

//TODO: Define uniforms for the center and the radius
uniform vec2 center;
uniform float radius;

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

void main(){
    //TODO: Write code that will draw the circle
    float diff_x = gl_FragCoord.x - center[0];
    float diff_y = gl_FragCoord.y - center[1];
    float dist = pow((pow(diff_x, 2) + pow(diff_y, 2)), 0.5);
    
    if(dist <= radius){
        frag_color = inside_color;
    } else {
        frag_color = outside_color;
    }
}