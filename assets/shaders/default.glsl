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
    gl_Position = proj * view * vec4(vPos - vec3(0.0, 3* sin(utime) ,0.0), 1.0);
    fCol = vCol;
    fTex = vTex;
}

#fragment
#version 330 core

#define PI 3.1415

in vec4 fCol;
in vec2 fTex;

uniform float utime;
uniform sampler2D utex;
uniform sampler2D utex2;

vec4 alpha1, alpha2;
float off;

void main(){
    
    // utime; utex; utex2;
    // gl_FragColor = vec4(sin(utime), cos(utime), fTex.y, 1.0);
    off = sin(utime) + cos(fTex.y * PI * 10)/50;
    vec2 tpos = fTex;
    alpha1 = texture(utex2, tpos); alpha2 = texture(utex, tpos);
    gl_FragColor = mix(alpha1, alpha2, abs(sin(utime)));
}
