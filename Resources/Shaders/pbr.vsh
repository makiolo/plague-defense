#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif


#ifndef HAS_TANGENT
#define HAS_TANGENT 1
#endif

#ifndef CALCULATE_BINORMAL
#define CALCULATE_BINORMAL 1
#endif


uniform mat4 u_MVPMatrix;
uniform mat4 u_MVMatrix;
uniform mat3 u_NormalMatrix;



attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec3 a_tangent;
attribute vec3 a_binormal;
attribute vec2 a_texCoord;



varying vec3 v_normal;
varying vec3 v_tangent;
varying vec3 v_binormal;
varying vec2 v_texCoord;
varying vec3 view_position;
varying vec3 light_direction;


void main(void)
{
    // https://www.gamasutra.com/blogs/RobertBasler/20131122/205462/Three_Normal_Mapping_Techniques_Explained_For_the_Mathematically_Uninclined.php?print=1

    vec3 light_pos = vec3(5.0, 2.0, 5.0);
    vec3 light_color = vec3(1.0, 1.0, 1.0);
    float light_energy = 3000.0;

    gl_Position = u_MVPMatrix * a_position;
    v_texCoord = a_texCoord;
    view_position = (u_MVMatrix * a_position).xyz;

#if HAS_TANGENT
    // Use tangent space
    // convert from "local space" to viewspace
    vec3 n = normalize(u_NormalMatrix * a_normal);
    vec3 t = normalize(u_NormalMatrix * a_tangent);
#if CALCULATE_BINORMAL
    vec3 b = normalize(u_NormalMatrix * cross(a_normal, a_tangent));
#else
    vec3 b = normalize(u_NormalMatrix * a_binormal);
#endif

    // TANGENT SPACE -> transpose does: from "view space" to "tangent space"
    //mat3 TBN = transpose(mat3( t, b, n ));
    // hand transpose, no transpose() in glsl 1.0 ...
    mat3 TBN = mat3(    t[0], b[0], n[0],  // first column
                        t[1], b[1], n[1],  // second column
                        t[2], b[2], n[2] );

    // VIEW SPACE
    //mat3 TBN = mat3( t, b, n ) -> normal does: convert "tangent space" in "view space"
    light_direction = TBN * ((u_MVMatrix * vec4(light_pos, 1.0)).xyz - view_position);

    // convert to tangent space
    view_position = TBN * view_position;
#else
    // Use view space
    v_normal = normalize(u_NormalMatrix * a_normal);
    light_direction = light_pos - view_position;
#endif
}
