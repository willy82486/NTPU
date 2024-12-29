#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

// Transformation matrix.
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 normalMatrix;
uniform mat4 MVP;
// --------------------------------------------------------
// Add more uniform variables if needed.
// --------------------------------------------------------

// Data pass to fragment shader.
// --------------------------------------------------------
// Add your data for interpolation.
// --------------------------------------------------------
out vec3 iPosView;
out vec3 iNormalView;

void main()
{
    // --------------------------------------------------------
    // Add your implementation.
    // --------------------------------------------------------
    gl_Position = MVP * vec4(Position, 1.0);

    // Pass vertex attributes.
    vec4 positionTmp = viewMatrix * worldMatrix * vec4(Position, 1.0);
    iPosView = positionTmp.xyz / positionTmp.w;
    iNormalView = (normalMatrix * vec4(Normal, 0.0)).xyz;
}