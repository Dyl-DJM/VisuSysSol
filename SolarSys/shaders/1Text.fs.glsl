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
uniform vec3 uAmbientLight;

// View Coordinates
in vec4 vVertexPositionVC;
in vec4 vVertexNormalVC;

in vec2 vFragText;

out vec4 fFragColor;



// Computes the fragment color
vec3 blinnPhong(){
  vec3 wi = normalize(uLightPos - vVertexPositionVC.xyz);
  float d = distance(uLightPos, vVertexPositionVC.xyz);
  vec3 li = uLightIntensity / (d * 1);
  vec3 wo = normalize(-vVertexPositionVC.xyz);
  vec3 halfV = (wo + wi) / 2;
  vec3 n = normalize(vVertexNormalVC.xyz);

  vec3 a = uKd * dot(wi, n);  // Diffuse component
  vec3 b = uKs * pow(dot(halfV, n), uShininess);  // Specular component
  vec3 formula = li * (a + b);

  // Not really an ambient light but closer to a minimum light factor
  formula.x = (formula.x < uAmbientLight.x) ? uAmbientLight.x : formula.x;
  formula.y = (formula.y < uAmbientLight.y) ? uAmbientLight.y : formula.y;
  formula.z = (formula.z < uAmbientLight.z) ? uAmbientLight.z : formula.z;

  return formula;
}


void main() {
    // Own code
    vec4 text = texture(uTexture, vFragText);
    vec4 color_norm = normalize(vVertexNormalVC);

    if(uIsLighted != 0){
      fFragColor = text * vec4(blinnPhong() , 1);
    }else{
      fFragColor =  text;
    }
}