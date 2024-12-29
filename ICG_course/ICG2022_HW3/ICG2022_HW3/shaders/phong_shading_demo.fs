#version 330 core

// Data from vertex shader.
// -------------------------------------------------------------
// Add your data for interpolation.
// -------------------------------------------------------------
in vec3 iNormalView;
in vec2 iTexCoord;
in vec3 iPosView;
// -------------------------------------------------------------
// Add your uniform variables.
// -------------------------------------------------------------
// Transformation matrix.
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 normalMatrix;
uniform mat4 MVP;

// Material properties.
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ns;
// Texture data
uniform sampler2D mapKd;
uniform float textureFile_Flag;

// Light data.
uniform vec3 ambientLight;
uniform vec3 dirLightDir;
uniform vec3 dirLightRadiance;
uniform vec3 pointLightPos;
uniform vec3 pointLightIntensity;

uniform vec3 spotLightPos;
uniform vec3 spotLightDir;
uniform float spotLightCutoffStart;
uniform float spotLightTotalWidth;
uniform vec3 spotLightIntensity;

out vec4 FragColor;

vec3 Diffuse(vec3 Kd, vec3 I, vec3 N, vec3 lightDir)
{
    return Kd * I * max(0, dot(N, lightDir));
}

vec3 Specular(vec3 Ks, vec3 I, vec3 viewDir, vec3 lightReflectDir)
{
    return Ks * I * pow( max(0, dot(viewDir, lightReflectDir)), Ns);
}



void main()
{
    // -------------------------------------------------------------
    // add your implementation.
    // -------------------------------------------------------------
    // check whether using texture or not.
    vec3 new_Kd = Kd;
    if(textureFile_Flag > 0.0){
        new_Kd = texture2D(mapKd, iTexCoord).rgb;
    }
    // Compute vertex lighting in view space.
    vec3 N = normalize(iNormalView);
    vec3 viewDir = normalize(-iPosView);
    // -------------------------------------------------------------
    // Ambient light.
    vec3 ambient = Ka * ambientLight;
    // -------------------------------------------------------------
    // Directional light.
    vec3 vsDirectionalLightDir = (viewMatrix * vec4(-dirLightDir, 0.0)).xyz;
    vsDirectionalLightDir = normalize(vsDirectionalLightDir);
    // Diffuse.
    vec3 diffuse = Diffuse(new_Kd, dirLightRadiance, N, vsDirectionalLightDir);
    // Specular.
    //vec3 DirectionalLightReflectDir = reflect(vsDirectionalLightDir, N);
    //vec3 DirectionalLightReflectDir = normalize(vsDirectionalLightDir);
    vec3 DirectionalLightReflectDir = 2 * dot(N, vsDirectionalLightDir) * N - vsDirectionalLightDir;
    //vec3 specular = Specular(Ks, dirLightRadiance, N, DirectionalLightReflectDir);
    DirectionalLightReflectDir = normalize(DirectionalLightReflectDir);
    vec3 specular = Specular(Ks, dirLightRadiance, viewDir, DirectionalLightReflectDir);
    vec3 dirLight = diffuse + specular;
    // -------------------------------------------------------------
    // Point light.
    vec4 tmpPos = viewMatrix * vec4(pointLightPos, 1.0);
    vec3 vsPointLightPos = tmpPos.xyz / tmpPos.w;

    vec3 LightDir = normalize(vsPointLightPos - iPosView);
    float distSurfaceToLight = distance(vsPointLightPos, iPosView);
    float attenuation = 1.0f / (distSurfaceToLight * distSurfaceToLight);
    vec3 radiance = pointLightIntensity * attenuation;
    // Diffuse.
    diffuse = Diffuse(new_Kd, radiance, N, LightDir);
    // Specular.
    //vec3 PointLightReflectDir = reflect(LightDir, N);
    //vec3 PointLightReflectDir = normalize(LightDir);
    vec3 PointLightReflectDir = 2 * dot(N, LightDir) * N - LightDir; 
    //specular = Specular(Ks, radiance, N, PointLightReflectDir);
    PointLightReflectDir = normalize(PointLightReflectDir);
    specular = Specular(Ks, radiance, viewDir, PointLightReflectDir);
    vec3 pointLight = diffuse + specular;
    // -------------------------------------------------------------
    // Spot light.
    tmpPos = viewMatrix * vec4(spotLightPos, 1.0);
    vec3 vsSpotLightPos = tmpPos.xyz / tmpPos.w;

    LightDir = normalize(vsSpotLightPos - iPosView);
    vec3 SpotLightDir = (viewMatrix * vec4(-spotLightDir, 0.0)).xyz;

    float theta = dot(LightDir, normalize(SpotLightDir));
    float epsion = spotLightCutoffStart - spotLightTotalWidth;
    float spotLightDistance = distance(vsSpotLightPos, iPosView);
    attenuation = clamp((theta - spotLightTotalWidth) / epsion, 0.0, 1.0) / (spotLightDistance *spotLightDistance);
    radiance = spotLightIntensity * attenuation;
    // Diffuse.
    diffuse = Diffuse(new_Kd, radiance, N, LightDir);
    // Specular.
    //vec3 SpotLightReflectDir = normalize(LightDir);
    vec3 SpotLightReflectDir = 2 * dot(N, LightDir) * N - LightDir;
    SpotLightReflectDir = normalize(SpotLightReflectDir);
    specular = Specular(Ks, radiance, viewDir, SpotLightReflectDir);
    vec3 spotLight = diffuse + specular;


    // -------------------------------------------------------------
    //vec3 n = normalize(iNormalView);
    //vec3 viscolor = 0.5 * n + 0.5;
    //FragColor = vec4(viscolor, 1.0);
    vec3 LightingColor = ambient + dirLight + pointLight + spotLight;
    FragColor = vec4(LightingColor, 1.0);
}
