#vertex
#version 330 core
layout(location=0) in vec3 vPos;
layout(location=1) in vec4 vCol;
layout(location=2) in vec2 vTex;

uniform mat4 proj;
uniform mat4 view;

uniform float utime;

out vec4 fCol;
out vec2 fTex;

void main(){
    gl_Position = proj * view * vec4(vPos, 1.0);
    fCol = vCol;
    fTex = vTex;
}

#fragment
#version 330 core

#define PI 3.1415

in vec4 fCol;
in vec2 fTex;

uniform float utime;
uniform sampler2D utex[2];

vec4 alpha1, alpha2;
float off;

void main(){
    
    // utime; utex; utex2;
    // gl_FragColor = vec4(sin(utime), cos(utime), fTex.y, 1.0);
    off = sin(utime) + cos(fTex.y * PI * 10)/50;
    vec2 tpos = fTex;
    alpha1 = texture(utex[0], tpos); alpha2 = texture(utex[1], tpos);
    gl_FragColor = mix(alpha1, alpha2, abs(sin(utime)));
}
