#vertex
#version 330 core
layout(location=0) in vec3 vPos;

out vec3 fPos;

int main(){
    gl_Position = vec4(vPos, 0.0);
    fPos = vPos;
}

#fragment
#version 330 core
in vec3 fPos;

int main(){
    gl_FragColor = vec4(fPos, 1.0);
}
