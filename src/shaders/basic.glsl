#shader vertex
#version 330 core

layout(location = 0) in vec4 i_position;
layout(location = 1) in vec2 i_tex_coords;

uniform mat4 u_mvp;

out vec2 v_tex_coords;

void main() {
    gl_Position = u_mvp * i_position;
    v_tex_coords = i_tex_coords;
}

#shader fragment
#version 330 core

in vec2 v_tex_coords;

layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main() {
    vec4 tex_color = texture(u_texture, v_tex_coords);
    color = tex_color;
}
