#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform vec3  diffuseL;
uniform vec3  directionLight;

uniform sampler2D u_sampler0;
uniform sampler2D u_normalMap;

void main(void)
{
    vec4 texColor=texture2D(u_sampler0, v_texCoord);
    vec3 normal=texture2D(u_normalMap, v_texCoord).rgb;
	normal=normal*2.0-1.0;
	normal.y=-normal.y;

	vec4 lightDir=normalize(vec4(directionLight, 1.0));
	vec3 posToLight=-lightDir.xyz;
	float normDotPosToLight=max(0.0,dot(normal,posToLight));
	vec4 diffuse=vec4(normDotPosToLight*diffuseL,1.0);
	vec4 ambient=vec4(0.5,0.5,0.5,1);
	gl_FragColor=texColor*vec4(vec3(diffuse+ambient),diffuse.a);
	// gl_FragColor = vec4(diffuseL, 1.0);
}
