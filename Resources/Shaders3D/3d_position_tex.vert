
uniform mat4 u_MVPMatrix;

attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;

void main(void)
{
    vec4 normalproj = u_MVPMatrix * vec4(a_normal, 0);
    gl_Position = u_MVPMatrix * a_position;
    v_texCoord = a_texCoord;
    v_texCoord.y = 1.0 - v_texCoord.y;
}
