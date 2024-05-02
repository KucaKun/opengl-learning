#shader vertex
#version 330 core

layout(location = 0) in vec4 i_position;
layout(location = 1) in ivec4 i_color;
uniform mat4 u_mvp;
out vec4 v_color;

void main() {
    gl_Position = u_mvp*i_position;
    v_color = i_color/255.0;
}

#shader fragment
#version 330 core

in vec4 v_color;
layout(location = 0) out vec4 color;


void main() {
    color = v_color;
}
