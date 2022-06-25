#vertex
#version 330 core
layout(location=0) in vec3 vPos;
layout(location=1) in vec4 vCol;
layout(location=2) in vec2 vTex;

out vec4 fCol;
out vec2 fTex;

void main(){
    gl_Position = vec4(vPos, 1.0);
    fCol = vCol;
    fTex = vTex;
}

#fragment
#version 330 core
in vec4 fCol;

uniform float utime;
uniform sampler2D utex;

void main(){
    gl_FragColor = vec4(fCol.x, abs(sin(utime)), abs(cos(utime)),  fCol.w);
}
