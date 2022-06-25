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
in vec2 fTex;

uniform float utime;
uniform sampler2D utex;
uniform sampler2D utex2;

void main(){
    // gl_FragColor = texture(utex, fTex) * vec4(fCol.x, abs(sin(utime)), abs(cos(utime)),  fCol.w);
    // vec2 tpos = vec2(fTex.x + tan(utime), fTex.y + tan(utime));
    vec2 tpos = fTex;
    gl_FragColor = mix(texture(utex2, tpos), texture(utex, tpos), abs(sin(utime)));
}
