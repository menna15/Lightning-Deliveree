#version 330 core

out vec4 frag_color;

//TODO: Define uniforms for the center and the side-length
uniform vec2 center;
uniform float side_length;
uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

void main(){
    //TODO: Write code that will draw the diamond
    // Getting the manhattan distance between the current fragment and the circle's center
    float max_dist = abs(gl_FragCoord.x - center.x) + abs(gl_FragCoord.y - center.y);
    // If this fragment is inside the region of the diamond, then makes its color = the color of the diamond.
    if( max_dist <= side_length / 2){
        frag_color = inside_color;
    }
    // Otherwise, it's considered a background so its color = background color.
    else {
        frag_color = outside_color;
    }
}