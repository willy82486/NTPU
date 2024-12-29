// My headers.
#include "trianglemesh.h"

#define MAX_BUFFER_SIZE     1024
#define LOAD_MODEL_EVENT       1

// Global variables.
const int screenWidth = 600;
const int screenHeight = 600; 
GLuint vbo;
GLuint ibo;
TriangleMesh* mesh = nullptr;

// Function prototypes.
void SetupRenderState();
void SetupScene(const string&);
void ReleaseResources();
void RenderSceneCB();
void ProcessSpecialKeysCB(int, int, int);
void ProcessKeysCB(unsigned char, int, int);
void CreatePopUpMenu();
void ProcessMenuEvents(int);
string GetOpenModelFilePath();
void ReshapeCB(int, int);

// Callback function for glutDisplayFunc.
void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the triangle mesh.
    // ---------------------------------------------------------------------------
    // Add your implementation.
    // ---------------------------------------------------------------------------
    if (mesh != nullptr) {
        mesh->Draw();
        /*glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPTN), 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, mesh->GetSizeOfvertexIndices(), GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);*/
        
    }
    glutSwapBuffers();
}

// Callback function for glutSpecialFunc.
void ProcessSpecialKeysCB(int key, int x, int y)
{
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
    default:
        break;
    }
}

// Callback function for glutKeyboardFunc.
void ProcessKeysCB(unsigned char key, int x, int y)
{
    // Handle other keyboard inputs those are not defined as special keys.
    if (key == 27) {
        // Release memory allocation if needed.
        ReleaseResources();
        exit(0);
    }
}

void ReleaseResources()
{
    // Release dynamically allocated resources.
    // ---------------------------------------------------------------------------
    if (mesh != nullptr) {
        delete mesh;
        mesh = nullptr;
    }
    // Add your implementation.
    // ---------------------------------------------------------------------------
}

void SetupRenderState()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    vec4 clearColor = vec4(0.44f, 0.57f, 0.75f, 1.00f);
    glClearColor(
        (GLclampf)(clearColor.r),
        (GLclampf)(clearColor.g),
        (GLclampf)(clearColor.b),
        (GLclampf)(clearColor.a)
    );
}

void SetupScene(const string& modelPath)
{
    // ---------------------------------------------------------------------------
    // Add your implementation.
    //mesh->LoadFromFile(".\\Koffing.obj", true);
    //mesh->LoadFromFile(".\\Bunny.obj", true);
    //mesh->LoadFromFile(".\\Cube.obj", true);
    //mesh->LoadFromFile(".\\Teapot.obj", true);
    //mesh->ShowInfo();
    // ---------------------------------------------------------------------------
    if (modelPath.empty())
        return;

    // Release previous mesh data.
    if (mesh != nullptr) {
        delete mesh;
        mesh = nullptr;
    }

    // Load a model from obj file.
    mesh = new TriangleMesh();
    mesh->LoadFromFile(modelPath);
    mesh->ShowInfo();

    // Build transformation matrices.
    mat4x4 M(1.0f);

    vec3 cameraPos = vec3(0.0f, 0.5f, 2.0f);
    vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
    vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
    mat4x4 V = lookAt(cameraPos, cameraTarget, cameraUp);

    float fov = 40.0f;
    float aspectRatio = (float)screenWidth / (float)screenHeight;
    float zNear = 0.1f;
    float zFar = 100.0f;
    mat4x4 P = perspective(radians(fov), aspectRatio, zNear, zFar);

    // Apply CPU transformation.
    mat4x4 MVP = P * V * M;

    mesh->ApplyTransformCPU(MVP);

    // Create vertex and index buffer.
    // ---------------------------------------------------------------------------
    // Add your implementation.
    // ---------------------------------------------------------------------------
    mesh->CreateBuffers();
    /*glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPTN) * mesh->GetnumKindsOfVertices(), mesh->GetFirstPositionOfvertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->GetSizeOfvertexIndices(), mesh->GetFirstPositionOfvertexIndices(), GL_STATIC_DRAW);*/
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
        ReleaseResources();
        string filePath = GetOpenModelFilePath();
        SetupScene(filePath);
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

// Callback function for glutReshapeFunc.
void ReshapeCB(int w, int h)
{
    // Adjust camera and projection here.
    // Implemented in HW2.
}

int main(int argc, char** argv)
{
    // Setting window properties.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("HW1: OBJ Loader");

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
    SetupScene("");

    // Create menu.
    CreatePopUpMenu();

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
