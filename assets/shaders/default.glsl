#vertex
#version 330 core
layout(location=0) in vec3 vPos;
layout(location=1) in vec4 vCol;

uniform float utime;

out vec4 fCol;

void main(){
    gl_Position = vec4(vPos, 1.0);
    fCol = vCol;
}

#fragment
#version 330 core
in vec4 fCol;

uniform float utime;

void main(){
    gl_FragColor = vec4(fCol.x, abs(sin(utime)), abs(cos(utime)),  fCol.w);
}
