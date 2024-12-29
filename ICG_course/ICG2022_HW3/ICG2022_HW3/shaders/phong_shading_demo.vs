#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;


// --------------------------------------------------------
// Add more uniform variables if needed.
// --------------------------------------------------------
// Transformation matrix.
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 normalMatrix;
uniform mat4 MVP;


// --------------------------------------------------------
// Add your data for interpolation.
// --------------------------------------------------------
// Data pass to fragment shader.
out vec3 iNormalView;
out vec2 iTexCoord;
out vec3 iPosView;

void main()
{
    // --------------------------------------------------------
    // Add your implementation.
    // --------------------------------------------------------
    gl_Position = MVP * vec4(Position, 1.0);
    iNormalView = (normalMatrix * vec4(Normal, 0.0)).xyz;
    iTexCoord = TexCoord;
    
    // Pass vertex attributes.
    vec4 positionTmp = viewMatrix * worldMatrix * vec4(Position, 1.0);
    iPosView = positionTmp.xyz / positionTmp.w;
    
}