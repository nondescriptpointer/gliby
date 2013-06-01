#version 430

precision mediump float;

uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform sampler2D textureUnit;

smooth in vec2 vTex;
smooth in vec3 vNorm;
smooth in vec3 vLightDir;

out vec4 gl_FragColor;

void main(void){
    float diff = max(0.0, dot(normalize(vNorm), normalize(vLightDir)));
    gl_FragColor = diff * diffuseColor; 
    gl_FragColor += ambientColor;
    gl_FragColor *= vec4(texture(textureUnit,vTex));
}
