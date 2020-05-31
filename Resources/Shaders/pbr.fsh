// http://glslsandbox.com/e#54592.0
// https://en.wikibooks.org/wiki/GLSL_Programming/Unity/Specular_Highlights_at_Silhouettes

#ifdef GL_ES
//precision mediump int;
//precision mediump float;
#endif


#ifndef USE_ALBEDO_MAP
#define USE_ALBEDO_MAP 0
#endif

#ifndef USE_NORMAL_MAP
#define USE_NORMAL_MAP 0
#endif

#ifndef USE_AMBIENT_MAP
#define USE_AMBIENT_MAP 0
#endif

#ifndef USE_ROUGHNESS_MAP
#define USE_ROUGHNESS_MAP 0
#endif

#ifndef USE_METALLIC_MAP
#define USE_METALLIC_MAP 0
#endif



//uniform mat4 u_MVPMatrix;
//uniform mat4 u_MVMatrix;
//uniform mat4 u_PMatrix;
uniform mat3 u_NormalMatrix;


// uniform sampler2D prevFrame;
// uniform sampler2D prevPass;

#if USE_ALBEDO_MAP
uniform sampler2D texture0;
#else
uniform vec3 albedo_color;
#endif

#if USE_NORMAL_MAP
uniform sampler2D texture1;
#endif

#if USE_AMBIENT_MAP
uniform sampler2D texture2;
#endif
uniform vec3 ambient_color;

#if USE_ROUGHNESS_MAP
uniform sampler2D texture4;
#else
uniform float roughness;
#endif

#if USE_METALLIC_MAP
uniform sampler2D texture3;
#else
uniform float metallic;
#endif

varying vec3 v_normal;
varying vec3 v_tangent;
varying vec3 v_binormal;
varying vec2 v_texCoord;
varying vec3 view_position;
varying vec3 light_direction;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define PHONG
//#define BLINN
#define COOK

//#define SCHLICK
//#define SMITH
#define NEUMAN

//#define FRESNEL_APROXIMATION
//#define FRESNEL_GAUSSIAN
#define FRESNEL_CUSTOM

//#define COOK_BLINN
//#define COOK_BECKMANN
#define COOK_GGX


////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define PI 3.1415926


vec3 SchlickFresnelApproximation(vec3 specular, float VdotH)
{
    return specular + (vec3(1.0, 1.0, 1.0) - specular) * pow(1.0 - VdotH, 5.0);
}

//Schlick Gaussian Fresnel
//specular  = the rgb specular color value of the pixel
//VdotH     = the dot product of the camera view direction and the half vector
vec3 SchlickGaussianFresnel(vec3 specular, float VdotH)
{
    float sphericalGaussian = pow(2.0, float((-5.55473 * VdotH - 6.98316) * VdotH));
    return specular + (vec3(1.0, 1.0, 1.0) - specular) * sphericalGaussian;
}

vec3 SchlickFresnelCustom(vec3 specular, float LdotH)
{
    float ior = 0.25;
    float airIor = 1.000277;
    float f0 = (ior - airIor) / (ior + airIor);
    float max_ior = 2.5;
    f0 = clamp(f0 * f0, 0.0, (max_ior - airIor) / (max_ior + airIor));
    return specular * (f0  + (1.0 - f0) * pow(2.0, float((-5.55473 * LdotH - 6.98316) * LdotH)));
}


vec3 SchlickFresnel(vec3 specular, float direction)
{
#ifdef FRESNEL_APROXIMATION
    return SchlickFresnelApproximation(specular, direction);
#endif

#ifdef FRESNEL_GAUSSIAN
    return SchlickGaussianFresnel(specular, direction);
#endif

#ifdef FRESNEL_CUSTOM
    return SchlickFresnelCustom(specular, direction);
#endif
}


// following functions are copies of UE4
// for computing cook-torrance specular lighting terms

float D_blinn(float roughness, float NdH)
{
    float m = roughness * roughness;
    float m2 = m * m;
    float n = 2.0 / (m2 - 2.0);
    return (n + 2.0) / (2.0 * PI) * pow(NdH, n);
}

float D_beckmann(float roughness, float NdH)
{
    float m = roughness * roughness;
    float m2 = m * m;
    float NdH2 = NdH * NdH;
    return exp((NdH2 - 1.0) / (m2 * NdH2)) / (PI * m2 * NdH2 * NdH2);
}

float D_GGX(float roughness, float NdH)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float denom = NdH * NdH * (a2 - 1.0) + 1.0;
    denom = PI * denom * denom;
    return a2 / max(denom, 0.0000001);
}

float G_schlick(float roughness, float NdV, float NdL)
{
    float k = roughness * roughness * 0.5;
    float V = NdV * (1.0 - k) + k;
    float L = NdL * (1.0 - k) + k;
    return 0.25 / (V * L);
}

float G_smith(float roughness, float NdV, float NdL)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    float ggx1 = NdV / (NdV * (1.0 - k) + k);
    float ggx2 = NdL / (NdL * (1.0 - k) + k);
    return ggx1 * ggx2;
}

float NeumannVisibility(float NdotV, float NdotL)
{
    return NdotL * NdotV / max(1e-7, max(NdotL, NdotV));
}


// simple phong specular calculation with normalization
vec3 phong_specular(vec3 V, vec3 L, vec3 N, vec3 specular, float roughness)
{
    vec3 R = reflect(-L, N);
    float spec = max(0.0, dot(V, R));

    float k = 1.999 / (roughness * roughness);

    return min(1.0, 3.0 * 0.0398 * k) * pow(spec, min(10000.0, k)) * specular;
}

// simple blinn specular calculation with normalization
vec3 blinn_specular(float NdH, vec3 specular, float roughness)
{
    float k = 1.999 / (roughness * roughness);

    return min(1.0, 3.0 * 0.0398 * k) * pow(NdH, min(10000.0, k)) * specular;
}

vec3 CustomLambertianDiffuse(vec3 diffuseColor, float NdotV, float roughness)
{
    return diffuseColor * (1.0 / PI) * pow(NdotV, 0.5 + (0.3 * roughness));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main(void)
{
    vec3 light_pos = vec3(5.0, 2.0, 5.0);
    vec3 light_color = vec3(1.0, 1.0, 1.0);
    float light_energy = 3000.0;

    vec3 normal = v_normal;
    //vec3 tangent = v_tangent;
    //vec3 binormal = v_binormal;
    vec2 texcoord = v_texCoord * 16.0;

#if USE_METALLIC_MAP
    float meta = texture2D(texture3, texcoord).y;
#else
    float meta = metallic;
#endif

#if USE_ALBEDO_MAP
    vec3 base = texture2D(texture0, texcoord).xyz;
#else
    vec3 base = albedo_color;
#endif

    // mix between metal and non-metal material, for non-metal
    // constant base specular factor of 0.04 grey is used
    vec3 baseReflectivity = mix(vec3(0.04), base, meta);

    // light attenuation
    vec3 eye_direction = -view_position;
    float light_distance = length(light_direction);
    float A = light_energy / (light_distance * light_distance);
    vec3 light_radiance = light_color * A;

    // L, V, H vectors
    vec3 L = normalize(light_direction);
    vec3 V = normalize(eye_direction);
    vec3 H = normalize(L + V);

#if USE_NORMAL_MAP
    vec3 normal_map = texture2D(texture1, texcoord).xyz * 2.0 - 1.0;
    vec3 N = normalize(normal_map);
#else
    vec3 N = normalize(normal);
#endif

#if USE_ROUGHNESS_MAP
    float rough = texture2D(texture4, texcoord).y;
#else
    float rough = roughness;
#endif

    // compute material reflectance
    float NdV = max(0.0000001, dot(N, V));
    float NdL = max(0.0000001, dot(N, L));
    float HdV = max(0.0, dot(H, V));
    float NdH = max(0.0, dot(N, H));
    float LdV = max(0.0000001, dot(L, V));

#ifdef PHONG
    // specular reflectance with PHONG
    vec3 specfresnel = SchlickFresnel(baseReflectivity, NdV);
    vec3 specref = phong_specular(V, L, N, specfresnel, rough);
    specref *= vec3(NdL);
#endif

#ifdef BLINN
    // specular reflectance with BLINN
    vec3 specfresnel = SchlickFresnel(baseReflectivity, HdV);
    vec3 specref = blinn_specular(NdH, specfresnel, rough);
    specref *= vec3(NdL);
#endif

#ifdef COOK

    #ifdef COOK_BLINN
        float D = D_blinn(rough, NdH);
    #endif

    #ifdef COOK_BECKMANN
        float D = D_beckmann(rough, NdH);
    #endif

    #ifdef COOK_GGX
        float D = D_GGX(rough, NdH);
    #endif

    #ifdef SCHLICK
        float G = G_schlick(rough, NdV, NdL);
    #endif
    #ifdef SMITH
        float G = G_smith(rough, NdV, NdL);
    #endif
    #ifdef NEUMAN
        float G = NeumannVisibility(NdV, NdL);
    #endif

    // specular reflectance with COOK-TORRANCE
    vec3 F = SchlickFresnel(baseReflectivity, HdV);

    vec3 specular = (D * G * F) / (4.0 * NdV * NdL);

    // conservation energy
    vec3 kD = vec3(1.0) - F;

    kD *= 1.0 - meta;

    vec3 specref = (kD * base / PI + specular) * light_radiance * NdL;

    // Toon shading ?
    //specular = floor(specref / 0.3);
#endif

#if USE_AMBIENT_MAP
    vec3 ambient = texture2D(texture2, texcoord).xyz * ambient_color;
#else
    vec3 ambient = ambient_color;
#endif
    ambient = CustomLambertianDiffuse(ambient, NdV, rough);

    vec3 color = ambient * base + specref;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamm correct
    color = pow(color, vec3(1.0 / 2.2));

    gl_FragColor = vec4(color, 1.0);
}
