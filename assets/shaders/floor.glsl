#vertex
#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTex;

uniform mat4 view;
uniform mat4 proj;

out vec2 fTex;

void main(){
    gl_Position = proj * view * vec4(vPos, 1.0);
    fTex = vTex;
}

#fragment
#version 330 core

in vec2 fTex;

uniform float utime;
uniform sampler2D tex;

void main(){
    gl_FragColor = texture(tex, fTex);
}
