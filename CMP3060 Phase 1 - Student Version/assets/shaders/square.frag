#version 330 core

out vec4 frag_color;

//TODO: Define uniforms for the center and the side-length
uniform vec2 center;
uniform float side_length;
uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

void main(){
    //TODO: Write code that will draw the square
    //get the difference between the frag-coord " 0,0 at lower left" and the center of the square.
    vec4 dist = abs(gl_FragCoord - vec4(center,0,0));

    float max_dist = max(dist.x,dist.y);
    
    if( max_dist <= side_length/2){
        frag_color = inside_color;
    } else {
        frag_color = outside_color;
    }
}
