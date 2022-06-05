#version 330

// The texture holding the scene pixels
uniform sampler2D tex;

// ref : https://github.com/thoxey/ezPP/blob/master/ezPP/src/ezsharpness.cpp
in vec2 tex_coord;

out vec4 frag_color;


void main(){
    
    float offset = 0.0011;

    float kernel[9];
    vec2 offsets[9];
    vec3 sampleTex[9];
    vec3 col;
    vec4 outColour = texture(tex, tex_coord);
    offsets = vec2[](
    vec2(-offset, offset),  // top-left
    vec2(0.0f,    offset),  // top-center
    vec2(offset,  offset),  // top-right
    vec2(-offset, 0.0f),    // center-left
    vec2(0.0f,    0.0f),    // center-center
    vec2(offset,  0.0f),    // center-right
    vec2(-offset, -offset), // bottom-left
    vec2(0.0f,    -offset), // bottom-center
    vec2(offset,  -offset)  // bottom-right
    );
    kernel = float[](
    -1.0, -1.0, -1.0,
    -1.0,  9.0, -1.0,
    -1.0, -1.0, -1.0
    );
    col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
    sampleTex[i] = vec3(texture(tex, tex_coord + offsets[i]));
    col += sampleTex[i] * kernel[i];
    }
    outColour = vec4(col, 1.0);
    frag_color = outColour;
}