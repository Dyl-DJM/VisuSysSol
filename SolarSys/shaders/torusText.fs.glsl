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

    // Repeat the texture twice (above and below the torus)
    // Note that there is no need to handle the mirroring of the texture as the mode is set to GL_MIRRORED_REPEAT
    // In other words, once the coordinates goes over 1, the texture is repeated in a mirrored way.
    vec2 repeatText = vFragText * 2;

    // Switching the texture coordinates so that it is applied horizontally along the torus and not vertically
    float temp = repeatText.y;
    repeatText.x = repeatText.y;
    repeatText.y = temp;


    vec4 text = texture(uTexture, repeatText);
    vec4 color_norm = normalize(vVertexNormalVC);

    if(uIsLighted != 0){
      fFragColor = text * vec4(blinnPhong() , 1);
    }else{
      fFragColor =  text;
    }
}