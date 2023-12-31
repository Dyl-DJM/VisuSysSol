#version 330 core

uniform sampler2D uTexture;

// Material
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

// Light
uniform int uIsLighted;
uniform vec3 uLightPos;
uniform vec3 uLightIntensity;

// View Coordinates
in vec4 vVertexPositionVC;
in vec4 vVertexNormalVC;

in vec2 vFragText;

out vec4 fFragColor;


void main() {
    // Own code
    vec4 text = texture(uTexture, vFragText);
    vec4 color_norm = normalize(vVertexNormalVC);
    fFragColor =  text;
}