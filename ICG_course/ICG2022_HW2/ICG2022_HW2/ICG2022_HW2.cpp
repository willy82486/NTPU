#include <Windows.h>

#include "headers.h"
#include "trianglemesh.h"
#include "camera.h"
#include "shaderprog.h"
#include "light.h"

#define MAX_BUFFER_SIZE     1024
#define LOAD_MODEL_EVENT       1

// Global variables.
int screenWidth = 800;
int screenHeight = 800;
// Triangle mesh.
TriangleMesh* mesh = nullptr;
// Lights.
DirectionalLight* dirLight = nullptr;
PointLight* pointLight = nullptr;
SpotLight* spotLight = nullptr;
vec3 dirLightDirection = vec3(0.0f, 0.0f, -1.0f);
vec3 dirLightRadiance = vec3(0.6f, 0.6f, 0.6f);
vec3 pointLightPosition = vec3(0.8f, 0.0f, 0.8f);
vec3 pointLightIntensity = vec3(0.5f, 0.1f, 0.1f);
vec3 spotLightPosition = vec3(0.0f, 1.0f, 0.0f);
vec3 spotLightDirection = vec3(0.0f, -1.0f, 0.0f);
vec3 spotLightIntensity = vec3(0.5f, 0.5f, 0.1f);
float spotLightCutoffStartInDegree = 30.0f;
float spotLightTotalWidthInDegree = 45.0f;
vec3 ambientLight = vec3(0.2f, 0.2f, 0.2f);
// Camera.
Camera* camera = nullptr;
vec3 cameraPos = vec3(0.0f, 1.0f, 5.0f);
vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
float fovy = 30.0f;
float zNear = 0.1f;
float zFar = 1000.0f;
// Shaders.
FillColorShaderProg* fillColorShader = nullptr;
PhongShadingDemoShaderProg* phongShadingShader = nullptr;
// UI.
const float lightMoveSpeed = 0.2f;

// SceneObject.
struct SceneObject
{
    SceneObject() {
        mesh = nullptr;
        worldMatrix = mat4x4(1.0f);
    }
    TriangleMesh* mesh;
    mat4x4 worldMatrix;
};
SceneObject sceneObj;

// ScenePointLight (for visualization of a point light).
struct ScenePointLight
{
    ScenePointLight() {
        light = nullptr;
        worldMatrix = mat4x4(1.0f);
        visColor = vec3(1.0f, 1.0f, 1.0f);
    }
    PointLight* light;
    mat4x4 worldMatrix;
    vec3 visColor;
};
ScenePointLight pointLightObj;
ScenePointLight spotLightObj;

// Function prototypes.
void ReleaseResources();
// Callback functions.
void RenderSceneCB();
void ReshapeCB(int, int);
void ProcessSpecialKeysCB(int, int, int);
void ProcessKeysCB(unsigned char, int, int);
void SetupRenderState();
void LoadObjects(const string&);
//void LoadObjects();
void CreatePopUpMenu();
void ProcessMenuEvents(int);
string GetOpenModelFilePath();
void CreateCamera();
void CreateShaderLib();
void CreateLights();


void ReleaseResources()
{
    // ----------------------------------------------------
    // You do not need to change the code.
    // ----------------------------------------------------

    // Delete scene objects and lights.
    for (int i = 0; i < mesh->GetNumSubMeshes(); i++) {
        if (mesh->GetSubMeshes(i).material != nullptr) {
            mesh->ReleaseMaterialinSubmesh(i);
        }
    }
    if (mesh != nullptr) {
        delete mesh;
        mesh = nullptr;
    }
    if (pointLight != nullptr) {
        delete pointLight;
        pointLight = nullptr;
    }
    if (spotLight != nullptr) {
        delete spotLight;
        spotLight = nullptr;
    }
    if (dirLight != nullptr) {
        delete dirLight;
        dirLight = nullptr;
    }
    // Delete camera.
    if (camera != nullptr) {
        delete camera;
        camera = nullptr;
    }
    // Delete shaders.
    if (fillColorShader != nullptr) {
        delete fillColorShader;
        fillColorShader = nullptr;
    }
    if (phongShadingShader != nullptr) {
        delete phongShadingShader;
        phongShadingShader = nullptr;
    }
}

static float curRotationY = 0.0f;
const float rotStep = 0.25f;
void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Render a triangle mesh with Phong shading. ------------------------------------------------
    TriangleMesh* mesh = sceneObj.mesh;
    if (sceneObj.mesh != nullptr) {
        // Update transform.
        curRotationY += rotStep;
        mat4x4 S = scale(mat4x4(1.0f), vec3(1.5f, 1.5f, 1.5f));
        mat4x4 R = rotate(mat4x4(1.0f), radians(curRotationY), vec3(0, 1, 0));
        sceneObj.worldMatrix = S * R;
        // -------------------------------------------------------
		// Note: if you want to compute lighting in the View Space, 
        //       you might need to change the code below.
		// -------------------------------------------------------
       // mat4x4 normalMatrix = transpose(inverse(sceneObj.worldMatrix));
        mat4x4 normalMatrix = transpose(inverse(camera->GetViewMatrix() * sceneObj.worldMatrix));
        mat4x4 MVP = camera->GetProjMatrix() * camera->GetViewMatrix() * sceneObj.worldMatrix;
        
        // -------------------------------------------------------
		// Add your rendering code here.
		// -------------------------------------------------------
        phongShadingShader->Bind();

        // Transformation matrix.
        glUniformMatrix4fv(phongShadingShader->GetLocM(), 1, GL_FALSE, value_ptr(sceneObj.worldMatrix));
        glUniformMatrix4fv(phongShadingShader->GetLocV(), 1, GL_FALSE, value_ptr(camera->GetViewMatrix()));
        glUniformMatrix4fv(phongShadingShader->GetLocNM(), 1, GL_FALSE, value_ptr(normalMatrix));
        glUniformMatrix4fv(phongShadingShader->GetLocMVP(), 1, GL_FALSE, value_ptr(MVP));
        
        // Light data.
        if (dirLight != nullptr) {
            glUniform3fv(phongShadingShader->GetLocDirLightDir(), 1, value_ptr(dirLight->GetDirection()));
            glUniform3fv(phongShadingShader->GetLocDirLightRadiance(), 1, value_ptr(dirLight->GetRadiance()));
        }
        if (pointLight != nullptr) {
            glUniform3fv(phongShadingShader->GetLocPointLightPos(), 1, value_ptr(pointLight->GetPosition()));
            glUniform3fv(phongShadingShader->GetLocPointLightIntensity(), 1, value_ptr(pointLight->GetIntensity()));
        }
        if (spotLight != nullptr) {
            glUniform3fv(phongShadingShader->GetLocSpotLightPos(), 1, value_ptr(spotLight->GetPosition()));
            glUniform3fv(phongShadingShader->GetLocSpotLightDir(), 1, value_ptr(spotLight->GetDirection()));
            glUniform1f(phongShadingShader->GetLocSpotLightCutoffStart(), cos(radians(spotLight->GetCutoffStart())));
            glUniform1f(phongShadingShader->GetLocSpotLightTotalWidth(), cos(radians(spotLight->GetTotalWidth())));
            glUniform3fv(phongShadingShader->GetLocspotLightIntensity(), 1, value_ptr(spotLight->GetIntensity()));

        }
        glUniform3fv(phongShadingShader->GetLocAmbientLight(), 1, value_ptr(ambientLight));
        glUniformMatrix4fv(phongShadingShader->GetLocCameraPos(), 1, GL_FALSE, value_ptr(camera->GetCameraPos()));

        for (int i = 0; i < mesh->GetNumSubMeshes(); i++) {
            // Material properties.
            glUniform3fv(phongShadingShader->GetLocKa(), 1, value_ptr( mesh->GetSubMeshesMaterialKa(i)) );
            glUniform3fv(phongShadingShader->GetLocKd(), 1, value_ptr( mesh->GetSubMeshesMaterialKd(i)) );
            glUniform3fv(phongShadingShader->GetLocKs(), 1, value_ptr( mesh->GetSubMeshesMaterialKs(i)) );
            glUniform1f(phongShadingShader->GetLocNs(), mesh->GetSubMeshesMaterialNs(i) );
            // Render the mesh.
            mesh->Draw(mesh->GetSubMeshes(i));
        }
        phongShadingShader->UnBind();
    }
    
    // Visualize the light with fill color. ------------------------------------------------------
    // ----------------------------------------------------
    // You do not need to change the code.
    // ----------------------------------------------------
    PointLight* pointLight = pointLightObj.light;
    if (pointLight != nullptr) {
        mat4x4 T = translate(mat4x4(1.0f), pointLight->GetPosition());
        pointLightObj.worldMatrix = T;
        mat4x4 MVP = camera->GetProjMatrix() * camera->GetViewMatrix() * pointLightObj.worldMatrix;
        fillColorShader->Bind();
        glUniformMatrix4fv(fillColorShader->GetLocMVP(), 1, GL_FALSE, value_ptr(MVP));
        glUniform3fv(fillColorShader->GetLocFillColor(), 1, value_ptr(pointLightObj.visColor));
        // Render the point light.
        pointLight->Draw();
        fillColorShader->UnBind();
    }
    SpotLight* spotLight = (SpotLight*)(spotLightObj.light);
    if (spotLight != nullptr) {
        mat4x4 T = translate(mat4x4(1.0f), spotLight->GetPosition());
        spotLightObj.worldMatrix = T;
        mat4x4 MVP = camera->GetProjMatrix() * camera->GetViewMatrix() * spotLightObj.worldMatrix;
        fillColorShader->Bind();
        glUniformMatrix4fv(fillColorShader->GetLocMVP(), 1, GL_FALSE, value_ptr(MVP));
        glUniform3fv(fillColorShader->GetLocFillColor(), 1, value_ptr(spotLightObj.visColor));
        // Render the point light.
        spotLight->Draw();
        fillColorShader->UnBind();
    }
    // -------------------------------------------------------------------------------------------

    glutSwapBuffers();
}

void ReshapeCB(int w, int h)
{
    // ----------------------------------------------------
    // You do not need to change the code.
    // ----------------------------------------------------

    // Update viewport.
    screenWidth = w;
    screenHeight = h;
    glViewport(0, 0, screenWidth, screenHeight);
    // Adjust camera and projection.
    float aspectRatio = (float)screenWidth / (float)screenHeight;
    camera->UpdateProjection(fovy, aspectRatio, zNear, zFar);
}

void ProcessSpecialKeysCB(int key, int x, int y)
{
    // ----------------------------------------------------
    // You do not need to change the code.
    // ----------------------------------------------------
    
    // Handle special (functional) keyboard inputs such as F1, spacebar, page up, etc. 
    switch (key) {
    case GLUT_KEY_F1:
        // Render with point mode.
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
    case GLUT_KEY_F2:
        // Render with line mode.
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case GLUT_KEY_F3:
        // Render with fill mode.
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    
    // Point light control.
    case GLUT_KEY_LEFT:
        if (pointLight != nullptr)
            pointLight->MoveLeft(lightMoveSpeed);
        break;
    case GLUT_KEY_RIGHT:
        if (pointLight != nullptr)
            pointLight->MoveRight(lightMoveSpeed);
        break;
    case GLUT_KEY_UP:
        if (pointLight != nullptr)
            pointLight->MoveUp(lightMoveSpeed);
        break;
    case GLUT_KEY_DOWN:
        if (pointLight != nullptr)
            pointLight->MoveDown(lightMoveSpeed);
        break;

    default:
        break;
    }
}

void ProcessKeysCB(unsigned char key, int x, int y)
{
    // ----------------------------------------------------
    // You do not need to change the code.
    // ----------------------------------------------------
    
    // Handle other keyboard inputs those are not defined as special keys.
    if (key == 27) {
        // Release memory allocation if needed.
        ReleaseResources();
        exit(0);
    }
    // Spot light control.
    if (spotLight != nullptr) {
        if (key == 'a')
            spotLight->MoveLeft(lightMoveSpeed);
        if (key == 'd')
            spotLight->MoveRight(lightMoveSpeed);
        if (key == 'w')
            spotLight->MoveUp(lightMoveSpeed);
        if (key == 's')
            spotLight->MoveDown(lightMoveSpeed);
        if (key == 'z')
            spotLight->MoveForward(lightMoveSpeed);
        if (key == 'x')
            spotLight->MoveBackward(lightMoveSpeed);
    }
}

void SetupRenderState()
{
    // ----------------------------------------------------
    // You do not need to change the code.
    // ----------------------------------------------------
    
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    vec4 clearColor = vec4(0.44f, 0.57f, 0.75f, 1.00f);
    glClearColor(
        (GLclampf)(clearColor.r), 
        (GLclampf)(clearColor.g), 
        (GLclampf)(clearColor.b), 
        (GLclampf)(clearColor.a)
    );
}

void LoadObjects(const string& modelPath)
{
    // -------------------------------------------------------
	// Note: you can change the code below if you want to load
    //       the model dynamically.
	// -------------------------------------------------------
    
    if (modelPath.empty())
        return;

    // Release previous mesh data.
    if (mesh != nullptr) {
        delete mesh;
        mesh = nullptr;
    }
    // Load a model from obj file.
    mesh = new TriangleMesh();
    //mesh->LoadFromFile("models/ColorCube/ColorCube.obj", true);
    //mesh->LoadFromFile("models/Bunny/Bunny.obj", true);
    //mesh->LoadFromFile("models/Rose/Rose.obj", true);
    //mesh->LoadFromFile("models/Pillows/Pillows.obj", true);
    //mesh->LoadFromFile("models/Forklift/Forklift.obj", true);
    //mesh->LoadFromFile("models/Koffing/Koffing.obj", true);
    //mesh->LoadFromFile("models/Soccer/Soccer.obj", true);
    mesh->LoadFromFile(modelPath, true);
    mesh->ShowInfo();
    mesh->CreateBuffers();
    sceneObj.mesh = mesh;    
}

void CreatePopUpMenu()
{
    int menu = glutCreateMenu(ProcessMenuEvents);
    glutAddMenuEntry("Load 3D Model", LOAD_MODEL_EVENT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
// Callback function for glutCreateMenu.
void ProcessMenuEvents(int option)
{
    switch (option) {
    case LOAD_MODEL_EVENT:
        if (mesh != nullptr) {
            delete mesh;
            mesh = nullptr;
        }
        string filePath = GetOpenModelFilePath();
        LoadObjects(filePath);
        break;
    }
}

string GetOpenModelFilePath()
{
    OPENFILENAME openfile_name;       // common dialog box structure.
    wchar_t szFile[260];    // buffer for file name.
    HWND hwnd;              // owner window.
    HANDLE hf;              // file handle.

    hwnd = GetForegroundWindow();

    // Initialize OPENFILENAME
    ZeroMemory(&openfile_name, sizeof(openfile_name));
    openfile_name.lStructSize = sizeof(openfile_name);
    openfile_name.hwndOwner = hwnd;
    openfile_name.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    openfile_name.lpstrFile[0] = '\0';
    openfile_name.nMaxFile = sizeof(szFile);
    openfile_name.lpstrFilter = L".\0*.obj\0";
    openfile_name.nFilterIndex = 1;
    openfile_name.lpstrFileTitle = NULL;
    openfile_name.nMaxFileTitle = 0;
    openfile_name.lpstrInitialDir = NULL;
    openfile_name.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box. 
    if (GetOpenFileName(&openfile_name) == TRUE) {
        wstring ws(szFile);
        string str(ws.begin(), ws.end());
        return str;
    }
    return "";
}

void CreateLights()
{
    // ----------------------------------------------------
    // You do not need to change the code.
    // ----------------------------------------------------
    
    // Create a directional light.
    dirLight = new DirectionalLight(dirLightDirection, dirLightRadiance);
    // Create a point light.
    pointLight = new PointLight(pointLightPosition, pointLightIntensity);
    pointLightObj.light = pointLight;
    pointLightObj.visColor = normalize((pointLightObj.light)->GetIntensity());
    // Create a spot light.
    spotLight = new SpotLight(spotLightPosition, spotLightIntensity, spotLightDirection, 
            spotLightCutoffStartInDegree, spotLightTotalWidthInDegree);
    spotLightObj.light = spotLight;
    spotLightObj.visColor = normalize((spotLightObj.light)->GetIntensity());
}

void CreateCamera()
{
    // ----------------------------------------------------
    // You do not need to change the code.
    // ----------------------------------------------------
    
    // Create a camera and update view and proj matrices.
    camera = new Camera((float)screenWidth / (float)screenHeight);
    camera->UpdateView(cameraPos, cameraTarget, cameraUp);
    float aspectRatio = (float)screenWidth / (float)screenHeight;
    camera->UpdateProjection(fovy, aspectRatio, zNear, zFar);
}

void CreateShaderLib()
{
    // ----------------------------------------------------
    // You do not need to change the code.
    // ----------------------------------------------------

    fillColorShader = new FillColorShaderProg();
    if (!fillColorShader->LoadFromFiles("shaders/fixed_color.vs", "shaders/fixed_color.fs"))
        exit(1);

    phongShadingShader = new PhongShadingDemoShaderProg();
    if (!phongShadingShader->LoadFromFiles("shaders/phong_shading_demo.vs", "shaders/phong_shading_demo.fs"))
        exit(1);
}

int main(int argc, char** argv)
{
    // Setting window properties.
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 4);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("HW2: Lighting and Shading");

    // Initialize GLEW.
    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        std::cerr << "GLEW initialization error: " 
                  << glewGetErrorString(res) << std::endl;
        return 1;
    }

    // Initialization.
    SetupRenderState();
    LoadObjects("");

    // Create menu.
    CreatePopUpMenu();
    CreateLights();
    CreateCamera();
    CreateShaderLib();

    // Register callback functions.
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(RenderSceneCB);
    glutReshapeFunc(ReshapeCB);
    glutSpecialFunc(ProcessSpecialKeysCB);
    glutKeyboardFunc(ProcessKeysCB);

    // Start rendering loop.
    glutMainLoop();

    return 0;
}
