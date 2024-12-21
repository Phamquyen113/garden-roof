#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <vector>
#include <vector_matrix.h>
#include <string>
using namespace std;

// Mảng dữ liệu

typedef struct
{
    float xyzw[4];
    float rgba[4];
    float normal[4];
} Vertex;
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
    // Mảng dữ liệu


Vertex Vertices[] =
{
    // v0-v1-v2 (front)
    { {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
    { { -0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
    { { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
    // v2-v3-v0
    { { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
    { {  0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
    { {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },

    // v0-v3-v4 (right)
    { { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
    { { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
    { { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
    // v4-v5-v0
    { { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
    { { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
    { { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },

    // v0-v5-v6 (top)
    { {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
    { {  0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
    { { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
    // v6-v1-v0
    { { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
    { { -0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
    { {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },

    // v1-v6-v7 (left)
    { { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
    { { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
    { { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
    // v7-v2-v1
    { { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
    { { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
    { { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },

    // v7-v4-v3 (bottom)
    { { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
    { {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
    { {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
    // v3-v2-v7
    { {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
    { { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
    { { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },

    // v4-v7-v6 (back)
    { {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
    { { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
    { { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
    // v6-v5-v4
    { { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
    { {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
    { {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } }
};



const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba);

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4
//cpp
modelcpp,
model_mat,
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;
mat4 model3;
mat4 model2;
mat4 model1;
//model
int
location,
model_mat_location,
view_mat_location,
projection_mat_location;
#include <GL/glut.h>
string ReadShaderSourceFile(string fileName) {
    fstream reader(fileName.c_str());
    string line;
    string code = "";
    while (getline(reader, line)) {
        code += line + "\n";
    }
    reader.close();
    return code;
}

// ------------------------------------------
bool CompileShader(GLuint shaderID) {
    cout << "Compiling shader" << shaderID << "..." << endl;
    glCompileShader(shaderID);
    int result = -1;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        cout << "Shader " << shaderID << " compile failed" << endl;
        int maxLength = 2048;
        int realLength = 0;
        char log[2048];
        glGetShaderInfoLog(shaderID, maxLength, &realLength, log);
        cout << log << endl;
        return false;
    }
    cout << "Shader " << shaderID << " compile successful" << endl;
    return true;
}


void CreatVaoVbo()
{
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1, &VboId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);	// position
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); //color
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); //normal

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}
// ------------------------------------------
void CreatShaders()
{
    string vertexSrc = ReadShaderSourceFile("./vs.shader");
    string fragmentSrc = ReadShaderSourceFile("./fs.shader");

    const GLchar* VertexShader = vertexSrc.c_str();
    const GLchar* FragmentShader = fragmentSrc.c_str();

    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
    glCompileShader(VertexShaderId);

    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
    glCompileShader(FragmentShaderId);

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);
    glUseProgram(ProgramId);
}
// ------------------------------------------
void CloseFunc()
{
    glUseProgram(0);

    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);
}


///-----------------------CAMERA-----------------------
// Camera variables

//float cameraX = 0.0f, cameraY = 1.0f, cameraZ = 5.0f;
float cameraX = 0.0f, cameraY = 5.0f, cameraZ = 20;//mặc định
float cameraYaw = -90.0f, cameraPitch = 0.0f;
float camSpeed = 0.1f;
float sensitivity = 0.06f;
bool mouseCaptured = true;

// Last mouse positions
int lastMouseX = 400, lastMouseY = 300;
int windowWidth = 800, windowHeight = 600;

//-----------------------MATERIAL HANDLER-----------------------
void setMaterial(int r, int g, int b, float shininess = 32.0f) {
    GLfloat normalizedR = r / 255.0f;
    GLfloat normalizedG = g / 255.0f;
    GLfloat normalizedB = b / 255.0f;

    GLfloat matAmbient[] = { normalizedR, normalizedG, normalizedB, 1.0f };
    GLfloat matDiffuse[] = { normalizedR, normalizedG, normalizedB, 1.0f };
    GLfloat matSpecular[] = { normalizedR, normalizedG, normalizedB, 1.0f };
    GLfloat matShininess[] = { shininess };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}
// Hàm thiết lập ánh sáng
void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Sử dụng nguồn sáng số 0

    GLfloat lightPos[] = { 1.0f, 1.0f, 2.0f, 1.0f }; // Vị trí nguồn sáng
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Ánh sáng môi trường
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Ánh sáng khuếch tán
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Ánh sáng phản xạ

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glShadeModel(GL_SMOOTH);
}

// Hàm cập nhật camera
void updateCamera() {
    float frontX = cosf(cameraYaw * M_PI / 180.0f) * cosf(cameraPitch * M_PI / 180.0f);
    float frontY = sinf(cameraPitch * M_PI / 180.0f);
    float frontZ = sinf(cameraYaw * M_PI / 180.0f) * cosf(cameraPitch * M_PI / 180.0f);

    gluLookAt(cameraX, cameraY, cameraZ,
        cameraX + frontX, cameraY + frontY, cameraZ + frontZ,
        0.0f, 1.0f, 0.0f);
}
//---------------------------------------CÁC HÀM BIẾN ĐỔI------------------------------------------

// Hàm Scale: s(x, y, z)
void s(float x, float y, float z) {
    glScalef(x, y, z);
}

// Hàm Rotate quanh trục X: rx(angle)
void rx(float angle) {
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
}

// Hàm Rotate quanh trục Y: ry(angle)
void ry(float angle) {
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
}

// Hàm Rotate quanh trục Z: rz(angle)
void rz(float angle) {
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
}

// Hàm Translate: t(x, y, z)
void t(float x, float y, float z) {
    glTranslatef(x, y, z);
}

// ---------------------------------------CÁC HÌNH KHỐI----------------------------------------


// Hàm vẽ hình cầu (Sphere)
void drawSphere(float radius, int slices = 20, int stacks = 20) {
    glutSolidSphere(radius, slices, stacks);
}

// Hàm vẽ hình trụ (Cylinder)
void drawCylinder(float baseRadius, float topRadius, float height, int slices = 20, int stacks = 20) {
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, baseRadius, topRadius, height, slices, stacks);
    gluDeleteQuadric(quad);
}

// Hàm vẽ hình trụ với 2 đầu bịt kín
void drawClosedCylinder(float baseRadius, float topRadius, float height, int slices = 20, int stacks = 20) {
    GLUquadric* quad = gluNewQuadric();

    // Vẽ phần thân hình trụ
    gluCylinder(quad, baseRadius, topRadius, height, slices, stacks);

    // Vẽ nắp dưới
    glPushMatrix();
    glRotatef(180, 1.0f, 0.0f, 0.0f); // Lật ngược mặt dưới
    gluDisk(quad, 0.0, baseRadius, slices, 1);
    glPopMatrix();

    // Vẽ nắp trên
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height); // Di chuyển đến đỉnh hình trụ
    gluDisk(quad, 0.0, topRadius, slices, 1);
    glPopMatrix();

    gluDeleteQuadric(quad);
}


// Hàm vẽ hình nón (Cone)
void drawCone(float baseRadius, float height, int slices = 20, int stacks = 20) {
    glutSolidCone(baseRadius, height, slices, stacks);
}

// Hàm vẽ hình hộp (Cube)
void drawCube(float size) {
    glutSolidCube(size);
}
// Hàm vẽ hình hộp chữ nhật với chiều dài, rộng và cao tùy chỉnh
void drawRectangularBox(float length, float width, float height) {
    glPushMatrix();

    // Vẽ 6 mặt của hình hộp chữ nhật
    glBegin(GL_QUADS);

    // Mặt trước
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-length / 2, -height / 2, width / 2);
    glVertex3f(length / 2, -height / 2, width / 2);
    glVertex3f(length / 2, height / 2, width / 2);
    glVertex3f(-length / 2, height / 2, width / 2);

    // Mặt sau
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-length / 2, -height / 2, -width / 2);
    glVertex3f(length / 2, -height / 2, -width / 2);
    glVertex3f(length / 2, height / 2, -width / 2);
    glVertex3f(-length / 2, height / 2, -width / 2);

    // Mặt trái
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-length / 2, -height / 2, -width / 2);
    glVertex3f(-length / 2, -height / 2, width / 2);
    glVertex3f(-length / 2, height / 2, width / 2);
    glVertex3f(-length / 2, height / 2, -width / 2);

    // Mặt phải
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(length / 2, -height / 2, -width / 2);
    glVertex3f(length / 2, -height / 2, width / 2);
    glVertex3f(length / 2, height / 2, width / 2);
    glVertex3f(length / 2, height / 2, -width / 2);

    // Mặt trên
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-length / 2, height / 2, -width / 2);
    glVertex3f(length / 2, height / 2, -width / 2);
    glVertex3f(length / 2, height / 2, width / 2);
    glVertex3f(-length / 2, height / 2, width / 2);

    // Mặt dưới
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-length / 2, -height / 2, -width / 2);
    glVertex3f(length / 2, -height / 2, -width / 2);
    glVertex3f(length / 2, -height / 2, width / 2);
    glVertex3f(-length / 2, -height / 2, width / 2);

    glEnd();
    glPopMatrix();
}

// Hàm vẽ hình bán cầu (Hemisphere)
void drawHemisphere(float radius, int slices = 20, int stacks = 10) {
    GLUquadric* quad = gluNewQuadric();
    gluPartialDisk(quad, 0, radius, slices, stacks, 0, 180);
    gluDeleteQuadric(quad);
}

// Hàm vẽ hình mặt phẳng (Plane)
void drawPlane(float width, float depth) {
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f); // Pháp tuyến hướng lên trục Y
    glVertex3f(-width / 2, 0.0f, -depth / 2);
    glVertex3f(width / 2, 0.0f, -depth / 2);
    glVertex3f(width / 2, 0.0f, depth / 2);
    glVertex3f(-width / 2, 0.0f, depth / 2);
    glEnd();
}

// Hàm vẽ hình Torus (vòng xuyến)
void drawTorus(float innerRadius, float outerRadius, int nsides = 20, int rings = 20) {
    glutSolidTorus(innerRadius, outerRadius, nsides, rings);
}

// Hàm vẽ hình đĩa (Disk)
void drawDisk(float innerRadius, float outerRadius, int slices = 20, int loops = 20) {
    GLUquadric* quad = gluNewQuadric();
    gluDisk(quad, innerRadius, outerRadius, slices, loops);
    gluDeleteQuadric(quad);
}


//-----------------------OBJECTS-----------------------

//-------------------------------------Mái che---------------------------------------
bool isClosing = true;       // Trạng thái mặc định là đang đóng
float canopySpeed = 0.01f;   // Tốc độ đóng/mở
float leftCanopyScale = 1.0f, rightCanopyScale = 1.0f; // Ban đầu mở hoàn toàn

// Biến trạng thái cho cửa
bool isDoorClosing = true;    // Mặc định cửa đang đóng
float doorSpeed = 0.01f;      // Tốc độ đóng/mở cửa
float leftDoorScale = 1.0f, rightDoorScale = 1.0f; // Tỉ lệ thu nhỏ của cửa
void House() {

    setMaterial(202, 225, 255, 128);

    //mái nghiêng trái
    glPushMatrix();
    t(-3.3, 4.1, 0);
    rz(30);
    drawRectangularBox(1.5, 12, 0.1);
    glPopMatrix();

    //mái nghiêng phải
    glPushMatrix();
    t(3.3, 4.1, 0);
    rz(-30);
    drawRectangularBox(1.5, 12, 0.1);
    glPopMatrix();

    //sàn
    glPushMatrix();
    t(0, -0.5, 0);
    drawRectangularBox(8, 12, 0.1);
    glPopMatrix();

    //tường trái
    glPushMatrix();
    t(-4 + 0.05, 2, 0);
    drawRectangularBox(0.1, 12, 5);
    glPopMatrix();

    //tường phải
    glPushMatrix();
    t(4 - 0.05, 2, 0);
    drawRectangularBox(0.1, 12, 5);
    glPopMatrix();

    //MÁI CHE



  // Mái che trái
    glPushMatrix();
    float leftShift = (4.5 * (1.0f - leftCanopyScale)) / 2.0f; // Tính dịch chuyển ra ngoài
    t(-2.2 - leftShift, 4.5, 0);                              // Dịch chuyển sang trái
    s(leftCanopyScale, 1.0f, 1.0f);                             // Thu nhỏ theo trục X
    drawRectangularBox(4.5, 12, 0.1);                             // Vẽ mái che trái
    glPopMatrix();

    // Mái che phải
    glPushMatrix();
    float rightShift = (4.5 * (1.0f - rightCanopyScale)) / 2.0f; // Tính dịch chuyển ra ngoài
    t(2.2 + rightShift, 4.5, 0);                                // Dịch chuyển sang phải
    s(rightCanopyScale, 1.0f, 1.0f);                             // Thu nhỏ theo trục X
    drawRectangularBox(4.5, 12, 0.1);                            // Vẽ mái che phải
    glPopMatrix();





    /// Tự động đóng hoặc mở mái che
    if (isClosing) {
        leftCanopyScale -= canopySpeed;
        rightCanopyScale -= canopySpeed;

        // Giới hạn đóng tối thiểu
        if (leftCanopyScale < 0.4f) leftCanopyScale = 0.4f;
        if (rightCanopyScale < 0.4f) rightCanopyScale = 0.4f;
    }
    else {
        leftCanopyScale += canopySpeed;
        rightCanopyScale += canopySpeed;

        // Giới hạn mở tối đa
        if (leftCanopyScale > 1.0f) leftCanopyScale = 1.0f;
        if (rightCanopyScale > 1.0f) rightCanopyScale = 1.0f;
    }



    //tường sau

    glPushMatrix();
    t(0, 2, -6 + 0.05);
    drawRectangularBox(8, 0.1, 5);
    glPopMatrix();

    // Cửa trái
    glPushMatrix();
    float leftDoorShift = (4.0f * (1.0f - leftDoorScale)) / 2.0f; // Tính dịch chuyển vào trong
    t(-1.9 - leftDoorShift, 2.0f, 6.0f - 0.05f);                // Giữ rìa trái cố định
    s(leftDoorScale, 1.0f, 1.0f);                                // Co/giãn theo trục X
    drawRectangularBox(4.0f, 0.1f, 5.0f);                        // Vẽ cửa trái
    glPopMatrix();

    // Cửa phải
    glPushMatrix();
    float rightDoorShift = (4.0f * (1.0f - rightDoorScale)) / 2.0f; // Tính dịch chuyển vào trong
    t(1.9 + rightDoorShift, 2.0f, 6.0f - 0.05f);                  // Giữ rìa phải cố định
    s(rightDoorScale, 1.0f, 1.0f);                                 // Co/giãn theo trục X
    drawRectangularBox(4.0f, 0.1f, 5.0f);                          // Vẽ cửa phải
    glPopMatrix();




    // Tự động đóng/mở cửa
    if (isDoorClosing) {
        leftDoorScale -= doorSpeed;
        rightDoorScale -= doorSpeed;

        // Giới hạn đóng tối thiểu
        if (leftDoorScale < 0.1f) leftDoorScale = 0.1f;
        if (rightDoorScale < 0.1f) rightDoorScale = 0.1f;
    }
    else {
        leftDoorScale += doorSpeed;
        rightDoorScale += doorSpeed;

        // Giới hạn mở tối đa
        if (leftDoorScale > 1.0f) leftDoorScale = 1.0f;
        if (rightDoorScale > 1.0f) rightDoorScale = 1.0f;
    }



}
//-----------------------Vẽ lớp đất-----------------------
void Ground() {
    //lớp đất
    glPushMatrix();
    setMaterial(139, 69, 19);
    t(0, -0.6, 0);
    drawRectangularBox(20, 25, 0.5);
    glPopMatrix();
    //lớp cỏ
    glPushMatrix();
    setMaterial(0, 205, 0);
    t(0, -0.35, 0);
    drawRectangularBox(20, 25, 0.1);
    glPopMatrix();
}

//-----------------------Vẽ hàng rào-----------------------
void drawFence(float width, float height, float postWidth, float spacing) {
    // Vẽ các thanh dọc của hàng rào
    int numPosts = static_cast<int>(width / (postWidth + spacing));
    for (int i = 0; i < numPosts; ++i) {
        glPushMatrix();
        t(i * (postWidth + spacing) - width / 2, height / 2, 0.0f);
        drawRectangularBox(postWidth, 0.1f, height);
        glPopMatrix();
    }

    // Vẽ thanh ngang dưới
    glPushMatrix();
    t(-0.2f, height * 0.2f, 0.0f);
    drawRectangularBox(width, 0.2f, 0.1f);
    glPopMatrix();

    // Vẽ thanh ngang trên
    glPushMatrix();
    t(-0.2f, height * 0.8f, 0.0f);
    drawRectangularBox(width, 0.2f, 0.1f);
    glPopMatrix();
}

// Biến trạng thái và góc xoay cửa
bool isGateOpen = false; // Cửa đang đóng
float gateAngle = 0.0f;  // Góc mở cửa
float gateSpeed = 2.0f;  // Tốc độ mở cửa

// Hàm vẽ cửa hai cánh
void drawGate(float width, float height, float postWidth) {
    // Vẽ khung cửa (không di chuyển)
    setMaterial(160, 82, 45); // Màu nâu đậm
    glPushMatrix();
    t(-width / 2, height / 2, 0.0f); // Thanh bên trái
    drawRectangularBox(postWidth, 0.1f, height);
    glPopMatrix();

    glPushMatrix();
    t(width / 2, height / 2, 0.0f); // Thanh bên phải
    drawRectangularBox(postWidth, 0.1f, height);
    glPopMatrix();



    // Vẽ cánh cửa bên trái
    setMaterial(210, 105, 30); // Màu nâu nhạt
    glPushMatrix();
    t(-width / 2 + postWidth / 2, 0.0f, postWidth / 2 - 0.1); // Điểm bản lề bên trái
    glRotatef(gateAngle, 0.0f, 1.0f, 0.0f);             // Xoay theo trạng thái
    t(width / 4 - postWidth / 2, height / 2, 0.0f);     // Điều chỉnh vị trí
    drawRectangularBox(width / 2, 0.05f, height);
    glPopMatrix();

    // Vẽ cánh cửa bên phải
    glPushMatrix();
    t(width / 2 - postWidth / 2, 0.0f, postWidth / 2 - 0.1);  // Điểm bản lề bên phải
    glRotatef(-gateAngle, 0.0f, 1.0f, 0.0f);           // Xoay theo trạng thái
    t(-(width / 4 - postWidth / 2), height / 2, 0.0f); // Điều chỉnh vị trí
    drawRectangularBox(width / 2, 0.05f, height);
    glPopMatrix();
}

// Hàm cập nhật góc mở cửa
void updateGate() {
    if (isGateOpen && gateAngle < 90.0f) {
        gateAngle += gateSpeed;
        if (gateAngle > 90.0f) gateAngle = 90.0f; // Giới hạn góc mở
    }
    else if (!isGateOpen && gateAngle > 0.0f) {
        gateAngle -= gateSpeed;
        if (gateAngle < 0.0f) gateAngle = 0.0f; // Giới hạn góc đóng
    }
}
void FinalFence() {
    //Mặt trước
    // Vẽ hàng rào front-left-right
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(-5.0f, -0.3f, 10); // Đặt vị trí hàng rào trái
    drawFence(4.0f, 2.0f, 0.1f, 0.3f);
    glPopMatrix();

    // Vẽ hàng rào front-left
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(-7.0f, -0.3f, 10); // Đặt vị trí hàng rào trái
    drawFence(4.0f, 2.0f, 0.1f, 0.3f);
    glPopMatrix();

    // Vẽ hàng rào front-right-left
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(5, -0.3f, 10); // Đặt vị trí hàng rào trái
    drawFence(4.0f, 2.0f, 0.1f, 0.3f);
    glPopMatrix();

    // Vẽ hàng rào front-right
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(7, -0.3f, 10); // Đặt vị trí hàng rào trái
    drawFence(4.0f, 2.0f, 0.1f, 0.3f);
    glPopMatrix();


    //Mặt sau
    // Vẽ hàng rào behind-left
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(-7.0f, -0.3f, -10); // Đặt vị trí hàng rào trái
    drawFence(4.0f, 2.0f, 0.1f, 0.3f);
    glPopMatrix();

    // Vẽ hàng rào behind-left-right
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(-5.0f, -0.3f, -10); // Đặt vị trí hàng rào trái
    drawFence(4.0f, 2.0f, 0.1f, 0.3f);
    glPopMatrix();



    // Vẽ hàng rào behind-right-left
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(5, -0.3f, -10); // Đặt vị trí hàng rào trái
    drawFence(4.0f, 2.0f, 0.1f, 0.3f);
    glPopMatrix();

    // Vẽ hàng rào behind-right
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(7, -0.3f, -10); // Đặt vị trí hàng rào trái
    drawFence(4.0f, 2.0f, 0.1f, 0.3f);
    glPopMatrix();
    // Vẽ hàng rào behind-bettween
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(0, -0.3f, -10); // Đặt vị trí hàng rào trái
    drawFence(6, 2.0f, 0.1f, 0.3f);
    glPopMatrix();


    //bên trái

      // Vẽ hàng rào trái
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(-9, -0.3f, 0); // Đặt vị trí hàng rào trái
    ry(90);
    drawFence(20, 2.0f, 0.1f, 0.3f);
    glPopMatrix();
    // Vẽ hàng rào phải
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(9, -0.3f, 0); // Đặt vị trí hàng rào trái
    ry(90);
    drawFence(20, 2.0f, 0.1f, 0.3f);
    glPopMatrix();
    // Vẽ cửa

    glPushMatrix();
    ry(180);
    t(0.2, -0.3, -10.2);
    drawGate(5.8, 2, 0);
    glPopMatrix();

    // Cập nhật chuyển động cửa
    updateGate();
}


//----------------------------------Cây-------------------------------------------
float treeTime = 0.0f;

// Biến điều khiển chuyển động của tán lá
float leafSwingAngle = 0.0f;

// Hàm vẽ cây với tán lá đung đưa
void drawTree() {
    // Vẽ thân cây
    setMaterial(139, 69, 19); // Màu nâu
    glPushMatrix();
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // Quay đứng thân cây
    drawCylinder(0.1f, 0.08f, 1.5f); // Thân cây
    glPopMatrix();

    // Hiệu ứng đung đưa cho tán lá
    float swayAmount = 5.0f; // Góc nghiêng tối đa
    float swaySpeed = 0.01f;
    leafSwingAngle += swaySpeed;
    float swayOffset = sin(leafSwingAngle * M_PI / 180.0f) * swayAmount;

    // Vẽ tán lá trên cao
    setMaterial(34, 139, 34); // Màu xanh lá cây
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 0.0f); // Vị trí tán cây
    glRotatef(swayOffset, 1.0f, 0.0f, 0.0f); // Đung đưa qua lại
    drawSphere(0.5f); // Hình cầu tán cây chính

    // Các tán nhỏ hơn nằm dưới tán lớn
    glPushMatrix();
    glTranslatef(-0.3f, -0.4f, 0.0f);
    drawSphere(0.3f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f, -0.4f, 0.0f);
    drawSphere(0.3f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.4f, -0.3f);
    drawSphere(0.3f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.3f);
    drawSphere(0.3f);
    glPopMatrix();

    glPopMatrix(); // Kết thúc tán lá
}

void drawPineTree(float time) {
    // Vẽ thân cây
    setMaterial(139, 69, 19); // Màu nâu
    glPushMatrix();
    t(0, -0.5, 0);
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // Quay thân cây đứng thẳng
    drawCylinder(0.1f, 0.1f, 1.0f); // Thân cây hình trụ
    glPopMatrix();

    // Vẽ các tầng lá hình nón với hiệu ứng đung đưa
    setMaterial(34, 139, 34); // Màu xanh lá cây

    // Giảm góc đung đưa
    float scaleFactor = 0.2f; // Hệ số giảm biên độ dao động

    // Tầng lá trên cùng
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f); // Đưa lên đỉnh thân cây
    float angleTop = 5.0f * sin(time * 2.0f) * scaleFactor; // Giảm biên độ
    glRotatef(angleTop, 0.0f, 0.0f, 1.0f); // Đung đưa quanh trục Z
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // Xoay hình nón thẳng đứng
    drawCone(0.3f, 0.6f);
    glPopMatrix();

    // Tầng lá giữa
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f); // Dưới tầng trên cùng
    float angleMiddle = 7.5f * sin(time * 1.5f) * scaleFactor; // Giảm biên độ
    glRotatef(angleMiddle, 0.0f, 0.0f, 1.0f); // Đung đưa quanh trục Z
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // Xoay hình nón thẳng đứng
    drawCone(0.5f, 0.6f);
    glPopMatrix();

    // Tầng lá dưới cùng
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f); // Dưới tầng giữa
    float angleBottom = 10.0f * sin(time) * scaleFactor; // Giảm biên độ
    glRotatef(angleBottom, 0.0f, 0.0f, 1.0f); // Đung đưa quanh trục Z
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // Xoay hình nón thẳng đứng
    drawCone(0.7f, 0.6f);
    glPopMatrix();
}


void FinalTree() {
    //  Vẽ cây
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, -3.0f); // Đặt cây ở vị trí dễ nhìn hơn
    drawTree();
    glPopMatrix();
}

void FinalPineTree() {
    treeTime += 0.01f; // Tăng dần thời gian để tạo hiệu ứng chuyển động

    glPushMatrix();

    t(2, 0, 0);
    drawPineTree(treeTime); // Gọi hàm vẽ cây với hiệu ứng đung đưa
    glPopMatrix();

}
//nhiều cây
float MovePineTree_left;
float MovePineTree_right;
void FinalPineTrees() {



    glPushMatrix();
    t(MovePineTree_left, 0, 0);
    glPushMatrix();
    t(-10.5, 0, 4);
    s(2, 3, 2);
    FinalPineTree();
    glPopMatrix();

    glPushMatrix();
    t(-10.5, 0, -2);
    s(2, 3, 2);
    FinalPineTree();
    glPopMatrix();
    glPopMatrix();

    //phải
    glPushMatrix();
    t(MovePineTree_right, 0, 0);

    glPushMatrix();
    t(2.5, 0, 4);
    s(2, 3, 2);
    FinalPineTree();
    glPopMatrix();

    glPushMatrix();
    t(2.5, 0, -2);
    s(2, 3, 2);
    FinalPineTree();
    glPopMatrix();
    glPopMatrix();


}
//nhiều câu
void FinalTrees() {
    glPushMatrix();
    t(-1.5, 0.5, -1);
    FinalTree();
    glPopMatrix();

    glPushMatrix();
    t(-3, 0.5, -1);
    FinalTree();
    glPopMatrix();

    glPushMatrix();
    t(1.5, 0.5, -1);
    FinalTree();
    glPopMatrix();

    glPushMatrix();
    t(3, 0.5, -1);
    FinalTree();
    glPopMatrix();


    /////////////
    glPushMatrix();
    t(-1.5, 0.5, 1);
    FinalTree();
    glPopMatrix();

    glPushMatrix();
    t(-3, 0.5, 1);
    FinalTree();
    glPopMatrix();

    glPushMatrix();
    t(1.5, 0.5, 1);
    FinalTree();
    glPopMatrix();

    glPushMatrix();
    t(3, 0.5, 1);
    FinalTree();
    glPopMatrix();
}
void IdleObject() {
    FinalTrees();
}
//-----------------------Hoa-----------------------

float flowerRotationAngle = 0.0f; // Góc xoay của hoa

// Hàm vẽ cây hoa chi tiết
void drawFlowerTree() {
    glPushMatrix();
    // Thân cây
    setMaterial(139, 69, 19); // Màu nâu gỗ
    glPushMatrix();
    t(0.0f, -0.8f, 0.0f);
    rx(-90);
    drawClosedCylinder(0.05f, 0.04f, 2.5f, 20, 20);
    glPopMatrix();

    // Nhánh chính bên trái
    glPushMatrix();
    t(0.0f, 1.2f, 0.0f); // Dịch chuyển lên đỉnh thân cây
    ry(-45.0f); // Xoay nhánh
    drawClosedCylinder(0.03f, 0.02f, 0.7f, 20, 20);
    glPopMatrix();

    // Nhánh chính bên phải
    glPushMatrix();
    t(0.0f, 1.0f, 0.0f); // Dịch chuyển lên đỉnh thân cây
    ry(45.0f); // Xoay nhánh
    drawClosedCylinder(0.03f, 0.014f, 0.7f, 20, 20);
    glPopMatrix();

    // Lá trên nhánh
    glPushMatrix();
    setMaterial(34, 139, 34); // Màu xanh lá cây
    t(0.1, 1.7f, 0.0f); // Dịch chuyển đến vị trí lá
    rx(45.0f);
    drawSphere(0.2f); // Lá hình cầu đơn giản
    glPopMatrix();

    // Hoa 1
    glPushMatrix();
    t(-0.55, 1.2, -1.5);
    rx(90);
    setMaterial(255, 0, 255); // Màu tím
    for (int i = 0; i < 5; ++i) {
        glPushMatrix();
        t(0.0f, 2.0f, 0.0f); // Dịch chuyển lên đỉnh nhánh
        ry(flowerRotationAngle); // Xoay hoa quanh trục y
        ry(i * 72.0f); // Xoay hoa thành hình tròn
        t(0.2f, 0.0f, 0.0f); // Dịch chuyển vị trí cánh hoa
        drawCone(0.1f, 0.2f); // Cánh hoa hình nón
        glPopMatrix();
    }

    // Nhụy hoa
    setMaterial(255, 255, 0); // Màu vàng
    glPushMatrix();
    t(0.0f, 2.0f, 0.0f);
    drawSphere(0.1f); // Nhụy hoa hình cầu
    glPopMatrix();
    glPopMatrix();


    // Hoa 2
    glPushMatrix();
    t(0.55, 1, -1.5);
    rx(90);
    setMaterial(255, 0, 255); // Màu tím
    for (int i = 0; i < 5; ++i) {
        glPushMatrix();
        t(0.0f, 2.0f, 0.0f); // Dịch chuyển lên đỉnh nhánh
        ry(flowerRotationAngle); // Xoay hoa quanh trục y

        ry(i * 72.0f); // Xoay hoa thành hình tròn
        t(0.2f, 0.0f, 0.0f); // Dịch chuyển vị trí cánh hoa
        drawCone(0.1f, 0.2f); // Cánh hoa hình nón
        glPopMatrix();
    }

    // Nhụy hoa
    setMaterial(255, 255, 0); // Màu vàng
    glPushMatrix();
    t(0.0f, 2.0f, 0.0f);
    drawSphere(0.1f); // Nhụy hoa hình cầu
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}
void updateFlowerRotation() {
    flowerRotationAngle += 0.5f; // Tăng góc xoay mỗi khung hình
    if (flowerRotationAngle > 360.0f) {
        flowerRotationAngle -= 360.0f; // Đảm bảo góc không vượt quá 360 độ
    }
}

void FinalPinkFlower() {
    glPushMatrix();
    t(0.0f, 0.0f, -2.0f); // Đặt cây ở vị trí phía trước người chơi
    drawFlowerTree();
    glPopMatrix();
    updateFlowerRotation();
}
void FinalPinkFlowers() {

    glPushMatrix();
    t(-3, -0.3, 2);
    s(0.8f, 0.8f, 0.9f);
    FinalPinkFlower();
    glPopMatrix();

    glPushMatrix();
    t(-3, -0.3, 3);
    s(0.8f, 0.8f, 0.9f);
    FinalPinkFlower();
    glPopMatrix();


    glPushMatrix();
    t(-1.5, -0.3, 2);
    s(0.8f, 0.8f, 0.9f);
    FinalPinkFlower();
    glPopMatrix();

    glPushMatrix();
    t(-1.5, -0.3, 3);
    s(0.8f, 0.8f, 0.9f);
    FinalPinkFlower();
    glPopMatrix();


    //////

    glPushMatrix();
    t(3, -0.3, 2);
    s(0.8f, 0.8f, 0.9f);
    FinalPinkFlower();
    glPopMatrix();

    glPushMatrix();
    t(3, -0.3, 3);
    s(0.8f, 0.8f, 0.9f);
    FinalPinkFlower();
    glPopMatrix();


    glPushMatrix();
    t(1.5, -0.3, 2);
    s(0.8f, 0.8f, 0.9f);
    FinalPinkFlower();
    glPopMatrix();

    glPushMatrix();
    t(1.5, -0.3, 3);
    s(0.8f, 0.8f, 0.9f);
    FinalPinkFlower();
    glPopMatrix();
}


//-----------------------ROSE----------------------------

// Vẽ cành cây (Stem)
void drawStem() {

    glPushMatrix();
    t(0, 1, 0);
    rx(90);
    setMaterial(139, 69, 19); // Màu nâu
    drawClosedCylinder(0.01f, 0.02f, 2.0f);
    glPopMatrix();
}

// Vẽ lá
void drawLeaf() {
    setMaterial(34, 139, 34, 0); // Màu xanh lá
    glPushMatrix();
    t(0.0f, -0.2f, 0.0f);
    s(0.2f, 0.4f, 0.2f);
    drawSphere(0.5f);
    glPopMatrix();
}

// Vẽ bông hoa hồng
void drawRose() {
    setMaterial(255, 0, 0); // Màu đỏ
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        ry(i * 72.0f); // Xoay để tạo các cánh hoa
        t(0.0f, 0.0f, 0.15f);
        s(0.4f, 0.4f, 0.2f);
        drawSphere(0.5f);
        glPopMatrix();
    }
    setMaterial(255, 20, 147);
    drawSphere(0.2f);
}
void drawRoseTree() {
    glPushMatrix();

    // Vẽ thân cây
    drawStem();

    // Vẽ lá

    glPushMatrix();
    t(0.0f, 0.5f, 0);
    rz(-120);
    drawLeaf();
    glPopMatrix();

    glPushMatrix();
    t(0.0f, 0.6f, 0);
    rz(120);

    drawLeaf();
    glPopMatrix();

    // Vẽ hoa
    glPushMatrix();
    t(0.0f, 1.0f, 0.0f);
    drawRose();
    glPopMatrix();

    glPopMatrix();
}
void FinalRose() {
    glPushMatrix();

    glPushMatrix();
    t(-3, -0.3, 3.2);
    drawRoseTree();
    glPopMatrix();

    glPushMatrix();
    t(-3, -0.3, 4.2);
    drawRoseTree();
    glPopMatrix();


    ////
    glPushMatrix();
    t(-1.5, -0.3, 3.2);
    drawRoseTree();
    glPopMatrix();

    glPushMatrix();
    t(-1.5, -0.3, 4.2);
    drawRoseTree();
    glPopMatrix();
    //////////////////////////////////////////////
    glPushMatrix();
    t(3, -0.3, 3.2);
    drawRoseTree();
    glPopMatrix();

    glPushMatrix();
    t(3, -0.3, 4.2);
    drawRoseTree();
    glPopMatrix();


    ////
    glPushMatrix();
    t(1.5, -0.3, 3.2);
    drawRoseTree();
    glPopMatrix();

    glPushMatrix();
    t(1.5, -0.3, 4.2);
    drawRoseTree();
    glPopMatrix();
    ///




    glPopMatrix();

}


//-----------------------Mặt trời----------------------------

// Hàm vẽ mặt trời
// Biến toàn cục để điều chỉnh chuyển động
float sunAngle = 0.0f;  // Góc quay của mặt trời
float sunPosition = 0.0f;  // Vị trí di chuyển ngang của mặt trời

void drawSun() {
    glPushMatrix();

    // Di chuyển mặt trời theo chiều ngang để tạo cảm giác trái đất quay
    glTranslatef(sunPosition, 0.0f, -5.0f); // Tịnh tiến mặt trời ra xa để nhìn rõ

    // Vẽ mặt trời (màu vàng sáng)
    setMaterial(255, 215, 0, 100.0f);
    drawSphere(0.5f);

    // Vẽ các tia nắng quay quanh mặt trời
    setMaterial(255, 223, 0, 50.0f);
    rx(90);
    for (int i = 0; i < 360; i += 15) {
        glPushMatrix();
        glRotatef(sunAngle + i, 0.0f, 1.0f, 0.0f); // Xoay tia nắng theo góc hiện tại
        glTranslatef(0.0f, 0.0f, 0.8f); // Đẩy tia nắng ra xa tâm
        drawCone(0.05f, 0.4f); // Tia nắng hình nón
        glPopMatrix();
    }

    glPopMatrix();
}

// Khai báo thêm biến vận tốc
float sunVelocity = 0.00001f; // Tốc độ di chuyển của mặt trời

// Hàm cập nhật góc xoay và vị trí mặt trời
void updateSun(int value) {
    sunAngle += 0.0005f; // Tăng góc quay của các tia nắng
    if (sunAngle >= 360.0f) sunAngle -= 360.0f;

    sunPosition += sunVelocity; // Di chuyển mặt trời theo vận tốc
    // Đổi hướng di chuyển khi chạm giới hạn
    if (sunPosition > 3.0f || sunPosition < -3.0f) {
        sunVelocity = -sunVelocity; // Đảo ngược hướng
    }

    glutTimerFunc(16, updateSun, 0); // Gọi lại sau 16ms (~60 FPS)
}

void FinalSun() {
    // Vẽ mặt trời
    glPushMatrix();
    t(2.0f, 10.0f, -3.0f); // Đặt vị trí mặt trời
    drawSun();
    updateSun(0);
    glPopMatrix();
}


// //-----------------------Cloud-----------------------
float childSizes[4];


float cloudRadius = 3.0f;    // Bán kính quỹ đạo mây mẹ
float cloudAngle = 0.0f;     // Góc hiện tại của mây mẹ
float cloudSpeed = 0.001f;    // Tốc độ mây mẹ di chuyển
void drawCloud() {
    // Tính vị trí mây mẹ
    float cloudX = cloudRadius * cosf(cloudAngle);
    float cloudZ = cloudRadius * sinf(cloudAngle);

    // Cập nhật góc quay của mây mẹ
    cloudAngle += cloudSpeed;
    if (cloudAngle > 2.0f * M_PI) {
        cloudAngle -= 2.0f * M_PI; // Đặt lại góc quay khi hoàn thành một vòng
    }

    // Vẽ mây mẹ

    glPushMatrix();
    t(cloudX, 2.0f, cloudZ); // Đặt vị trí mây mẹ trên cao
    setMaterial(255, 255, 255); // Màu trắng cho mây
    drawSphere(0.5f);          // Mây mẹ có bán kính 0.5
    glPopMatrix();

    // Vẽ các mây con xung quanh mây mẹ
    float childSizes[4] = { 0.3f, 0.25f, 0.35f, 0.18f }; // Kích thước ngẫu nhiên cho 4 mây con
    for (int i = 0; i < 4; ++i) {
        float angle = i * (M_PI / 3); // Góc lệch giữa các mây con
        float childX = 0.5f * cosf(angle); // Mây con nằm quanh mây mẹ
        float childZ = 0.5f * sinf(angle);

        glPushMatrix();
        t(cloudX + childX, 2.0f, cloudZ + childZ); // Tính vị trí mây con
        drawSphere(childSizes[i]); // Vẽ mây con với kích thước khác nhau
        glPopMatrix();

    }
}
void generateRandomChildSizes(float* sizes, int count) {
    for (int i = 0; i < count; ++i) {
        sizes[i] = 0.15f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.1f));
    }
}

void FinalCloud() {
    glPushMatrix();
    t(0, 5, 0);
    glPushMatrix();
    s(0.8f, 0.8f, 0.8f);
    drawCloud();
    glPopMatrix();

    glPushMatrix();
    s(0.5f, 0.5f, 0.5f);

    t(0.2f, 0.5f, 0.3f);
    drawCloud();

    glPopMatrix();
    glPopMatrix();
}
///-----------------------Bird-----------------------

// Hàm vẽ đầu con chim
void drawBirdHead() {
    glPushMatrix();

    // Đầu con chim (hình cầu)
    setMaterial(118, 238, 198);
    drawSphere(0.3f);

    // Mỏ trên (hình nón dẹp hơn)
    glPushMatrix();
    setMaterial(0, 0, 0);
    t(0.0f, -0.02f, 0.25f); // Dịch chuyển mỏ trên ra phía trước
    rx(-15); // Nghiêng mỏ xuống một chút
    s(1.0f, 0.2f, 1.0f); // Làm dẹp mỏ theo chiều dọc
    drawCone(0.1f, 0.2f); // Vẽ mỏ
    glPopMatrix();

    // Mỏ dưới (hình nón dẹp hơn)
    glPushMatrix();
    t(0.0f, -0.04f, 0.22f); // Dịch chuyển mỏ dưới ra phía trước
    rx(25); // Nghiêng mỏ dưới lên một chút
    s(1.0f, 0.1f, 1.0f); // Làm dẹp mỏ dưới theo chiều dọc
    drawCone(0.08f, 0.2f); // Vẽ mỏ dưới
    glPopMatrix();

    // Mắt trái (hình cầu nhỏ)
    glPushMatrix();
    setMaterial(0, 0, 0); // Màu đen cho mắt
    t(-0.15f, 0.1f, 0.22f); // Dịch chuyển mắt lên phía trên bên trái
    drawSphere(0.05f);
    glPopMatrix();

    // Mắt phải (hình cầu nhỏ)
    glPushMatrix();
    t(0.15f, 0.1f, 0.22f); // Dịch chuyển mắt lên phía trên bên phải
    drawSphere(0.05f);
    glPopMatrix();

    glPopMatrix();
}

// Hàm vẽ thân (ellipse)
void drawEllipse(float rx, float ry, float rz) {
    glPushMatrix();
    glScalef(rx, ry, rz); // Tạo hình ellipse bằng cách co giãn hình cầu
    drawSphere(1.0f); // Bán kính cơ sở là 1
    glPopMatrix();
}

// Hàm vẽ chim (không có cánh)


// Hàm vẽ bàn chân
void drawFoot() {
    glPushMatrix();

    // Đế bàn chân (hình cầu)
    setMaterial(200, 100, 50); // Màu nâu
    t(0.0f, -0.9f, 0.0f);

    glPushMatrix();
    t(0.0f, -0.1f, 0.0f);
    drawSphere(0.08f); // Bán kính hình cầu
    glPopMatrix();

    // Ngón chân thứ nhất
    glPushMatrix();
    t(0, -0.1f, 0.0f); // Dịch chuyển ngón chân ra phía trước bên phải
    ry(120); // Xoay ngón chân để tạo góc 120 độ
    rx(15); // Điều chỉnh góc nghiêng
    setMaterial(200, 100, 50); // Màu giống đế
    s(1, 0.5, 1);
    drawCone(0.05f, 0.3f);
    glPopMatrix();

    // Ngón chân thứ hai
    glPushMatrix();
    t(0, -0.1f, 0.0f); // Dịch chuyển ngón chân ra phía trước bên trái
    ry(-120); // Xoay ngón chân để tạo góc 120 độ
    rx(15); // Điều chỉnh góc nghiêng
    setMaterial(200, 100, 50); // Màu giống đế
    s(1, 0.5, 1);
    drawCone(0.05f, 0.3f);
    glPopMatrix();

    // Ngón chân thứ ba
    glPushMatrix();
    t(0.0f, -0.1f, 0); // Dịch chuyển ngón chân ra phía sau
    ry(0); // Không cần xoay
    rx(15); // Điều chỉnh góc nghiêng
    setMaterial(200, 100, 50); // Màu giống đế
    s(1, 0.5, 1);
    drawCone(0.05f, 0.3f);
    glPopMatrix();

    glPopMatrix();
}
// Hàm vẽ một chân chim
void drawBirdLeg() {
    // Đùi

    glPushMatrix();
    rx(70);
    t(0, 1, 0);
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu
    t(0.0f, 0.29f, 0.056f);      // Đặt vị trí đùi
    rx(30.0f);                // Xoay đùi hướng ra trước
    drawClosedCylinder(0.08f, 0.07f, 0.4f);
    glPopMatrix();

    // Cẳng chân
    glPushMatrix();
    setMaterial(205, 133, 63); // Màu nâu sáng
    t(0.0f, 0.1f, 0.35f);      // Dịch xuống dưới đùi (theo vị trí đã xoay)
    rx(-30.0f);                // Xoay cẳng chân hướng xuống
    drawClosedCylinder(0.06f, 0.05f, 0.4f);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    t(0.0f, 0.8f, 1.5f);
    drawFoot();
    glPopMatrix();


}

// Hàm vẽ toàn bộ 2 chân chim
void drawBirdLegs() {
    // Chân trái
    glPushMatrix();
    t(-0.2f, -1.0f, 0.0f); // Đặt vị trí chân trái
    drawBirdLeg();
    glPopMatrix();

    // Chân phải
    glPushMatrix();
    t(0.2f, -1.0f, 0.0f); // Đặt vị trí chân phải
    drawBirdLeg();
    glPopMatrix();
}





// Biến toàn cục để điều chỉnh chuyển động cánh
float wingAngle = 0.0f;
bool wingDirection = true; // true: cánh đi lên, false: cánh đi xuống

// Hàm vẽ cánh chim
void drawBirdWing(bool isLeft) {
    glPushMatrix();

    // Xác định vị trí gốc của cánh
    if (isLeft) {
        t(-0.35f, 0.4f, 0.0f);
    }
    else {
        t(0.35f, 0.4f, 0.0f);
    }

    // Đập cánh
    if (isLeft) {
        glRotatef(-wingAngle, 0.0f, 0.0f, 1.0f);
    }
    else {
        glRotatef(wingAngle, 0.0f, 0.0f, 1.0f);
    }

    // Vẽ cánh (ellipse dẹt)
    setMaterial(30, 144, 255);
    glPushMatrix();
    s(0.8f, 0.1f, 0.4f); // Làm dẹt hình cầu thành ellipse
    s(2.0f, 2.0f, 2.0f);
    drawSphere(0.5f);
    glPopMatrix();

    glPopMatrix();
}

// Hàm cập nhật chuyển động của cánh
void updateWing() {
    if (wingDirection) {
        wingAngle += 1.0f;
        if (wingAngle >= 30.0f) {
            wingDirection = false;
        }
    }
    else {
        wingAngle -= 1.0f;
        if (wingAngle <= -30.0f) {
            wingDirection = true;
        }
    }
}

// Tích hợp cánh vào chim
void drawBirdWithWings() {


    // Vẽ cánh trái
    glPushMatrix();
    t(-0.3, 0.0f, 0.0f);
    drawBirdWing(true);
    glPopMatrix();

    // Vẽ cánh phải
    glPushMatrix();
    t(0.3, 0.0f, 0.0f);

    drawBirdWing(false);
    glPopMatrix();
}
void drawBird() {
    glPushMatrix();
    s(2.0f, 2.0f, 2.0f);
    t(0.0f, 0.9f, 0.5f);
    setMaterial(99, 184, 255);

    // Vẽ thân (hình ellipse)
    glPushMatrix();
    ry(90);
    t(0, 0, 0); // Vị trí của thân
    drawEllipse(0.4f, 0.3f, 0.3f); // Hình ellipse làm thân
    glPopMatrix();

    // Vẽ đầu con chim
    glPushMatrix();
    s(0.6f, 0.6f, 0.6f);
    t(0.0f, 0.6f, 0.5); // Dịch chuyển vị trí của đầu chim ra xa camera
    drawBirdHead();
    glPopMatrix();

    // Vẽ đuôi
    glPushMatrix();
    setMaterial(139, 69, 19); // Màu nâu cho đuôi
    t(0, 0.4, -0.25);
    ry(180);
    t(0, -0.4, 0); // Dịch đuôi ra cuối thân
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        float angle = -30 + i * 15; // Góc xoay giữa các tia đuôi
        ry(angle); // Xoay theo trục Y
        s(1.0f, 0.5f, 1.0f);
        drawCone(0.1f, 0.5f); // Hình nón làm tia đuôi
        glPopMatrix();
    }
    glPopMatrix();

    glPopMatrix();

    // Vẽ chân chim
    glPushMatrix();
    t(0.0f, 2.0f, 0.0f); // Đặt vị trí toàn bộ chân chim
    drawBirdLegs();
    glPopMatrix();

    glPushMatrix();
    t(0.0f, 1.25, 1); // Dịch chim ra xa

    drawBirdWithWings();
    glPopMatrix();


}


float birdTime = 0.0f; // Thời gian cho quỹ đạo
float birdSpeed = 0.01f; // Tốc độ di chuyển
void updateBirdPosition() {
    birdTime += birdSpeed; // Tăng thời gian theo mỗi khung hình
    if (birdTime > 2 * M_PI) {
        birdTime -= 2 * M_PI; // Đảm bảo thời gian không vượt quá chu kỳ
    }
}
void drawBirdMoving() {
    glPushMatrix();

    // Tính toán vị trí dựa trên quỹ đạo hình số 8
    float a = 2.0f; // Bán kính theo trục x
    float b = 1.0f; // Bán kính theo trục y
    float x = a * sin(birdTime);
    float y = b * cos(birdTime) * sin(birdTime);

    // Dịch chuyển chim đến vị trí mới
    t(x, y, 0.0f);

    // Vẽ chim
    glPushMatrix();
    t(0, 8, -17);
    drawBird();

    glPopMatrix();

    glPopMatrix();
}

void FinalBird() {

    // Cập nhật vị trí chim
    updateBirdPosition();

    // Vẽ chim đang bay
    drawBirdMoving();
}

//------------------------Đèn led-----------------------

bool isLightOn = false; // Mặc định là bật đèn

// Hàm vẽ đầu đèn LED
void drawLEDBulb() {
    glPushMatrix();

    // Phần bóng đèn LED
    if (isLightOn) {
        setMaterial(255, 255, 0); // Màu vàng nhạt khi bật
    }
    else {
        setMaterial(220, 220, 220); // Màu xám khi tắt
    }
    drawSphere(0.2f); // Bóng đèn là hình cầu

    // Phần vỏ bọc trên bóng đèn
    glPushMatrix();
    rx(-90);
    t(0.0f, 0, 0.15f); // Đặt phần vỏ bọc bên trên bóng
    setMaterial(100, 100, 100); // Màu xám
    drawClosedCylinder(0.15f, 0.1f, 0.2f); // Vỏ bọc là hình trụ thu nhỏ
    glPopMatrix();

    glPopMatrix();
}

// Hàm vẽ sợi dây treo
void drawHangingWire() {
    glPushMatrix();

    // Dây treo
    rx(90);
    setMaterial(50, 50, 50); // Màu đen hoặc xám đậm
    drawCylinder(0.02f, 0.02f, 1.0f); // Sợi dây là một hình trụ mỏng và dài

    glPopMatrix();
}

void FinalLedLight() {

    // Vẽ dây treo
    glPushMatrix();
    t(0.0f, 1.0f, 0.0f); // Đặt dây treo từ một vị trí cao hơn
    drawHangingWire();
    glPopMatrix();

    // Vẽ bóng đèn LED
    glPushMatrix();

    t(0.0f, 0.0f, 0.0f); // Đặt bóng đèn ngay dưới sợi dây
    drawLEDBulb();
    glPopMatrix();

}

void FinalLedLights() {

    ///hàng giữa
    glPushMatrix();


    t(0, 3, 0);
    //bóng
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();


    //dây
    glPushMatrix();
    t(-4, 3.9, 0);
    ry(90);
    drawCylinder(0.02, 0.02, 8);
    glPopMatrix();


    glPushMatrix();
    t(-1.5, 3, 0);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(-3, 3, 0);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(1.5, 3, 0);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(3, 3, 0);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    ///hàng sau
    glPushMatrix();


    //dây
    glPushMatrix();
    t(-4, 3.9, -3);
    ry(90);
    drawCylinder(0.02, 0.02, 8);
    glPopMatrix();

    t(0, 3, -3);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(-1.5, 3, -3);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(-3, 3, -3);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(1.5, 3, -3);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(3, 3, -3);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    ///hàng trước
    glPushMatrix();

    //dây
    glPushMatrix();
    t(-4, 3.9, 3);
    ry(90);
    drawCylinder(0.02, 0.02, 8);
    glPopMatrix();

    t(0, 3, 3);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(-1.5, 3, 3);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(-3, 3, 3);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(1.5, 3, 3);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

    glPushMatrix();
    t(3, 3, 3);
    s(0.9, 0.9, 0.9);
    FinalLedLight();
    glPopMatrix();

}
//-----------------------Máy phun nước tự động-----------------------

// Biến toàn cục lưu góc xoay
float angleX = 0.0f;
float angleY = 0.0f;

// Cấu trúc hạt nước
struct WaterParticle {
    float x, y, z;     // Vị trí
    float velocityX, velocityY, velocityZ; // Vận tốc
    float lifetime;    // Thời gian tồn tại
};

// Biến quản lý vòi phun nước
std::vector<WaterParticle> particles;
int maxParticles = 200; // Số lượng giọt nước tối đa
float gravity = -0.005f; // Trọng lực

bool isFountainActive = true; // Biến kiểm soát trạng thái vòi phun nước

// Hàm tạo tia nước
float sprayRadius = 1.0f;
void createParticle() {
    if (!isFountainActive) return; // Không tạo hạt nếu máy phun nước tắt
    if (particles.size() < maxParticles) {
        WaterParticle p;
        float angle = (rand() % 360) * M_PI / 180.0f; // Góc phóng ngẫu nhiên
        float phi = (rand() % 180) * M_PI / 180.0f;   // Góc độ cao ngẫu nhiên
        float speed = sprayRadius * (0.05f + (rand() % 50) / 1000.0f);


        p.x = 0.0f; // Vị trí xuất phát tại gốc
        p.y = 0.0f;
        p.z = 0.0f;
        p.velocityX = speed * sin(phi) * cos(angle); // Vận tốc theo X
        p.velocityY = speed * cos(phi);             // Vận tốc theo Y
        p.velocityZ = speed * sin(phi) * sin(angle); // Vận tốc theo Z
        p.lifetime = 0.5f; // Thời gian tồn tại
        particles.push_back(p);
    }
}

// Hàm cập nhật trạng thái các tia nước
void updateParticles() {
    if (!isFountainActive) return; // Không cập nhật hạt nếu máy phun nước tắt
    for (size_t i = 0; i < particles.size();) {
        particles[i].x += particles[i].velocityX;
        particles[i].y += particles[i].velocityY;
        particles[i].z += particles[i].velocityZ;

        particles[i].velocityY += gravity; // Áp dụng trọng lực
        particles[i].lifetime -= 0.02f;    // Giảm thời gian tồn tại

        if (particles[i].lifetime <= 0.0f) {
            particles.erase(particles.begin() + i);
        }
        else {
            ++i;
        }
    }
    createParticle(); // Tạo thêm tia nước
}

// Hàm vẽ tia nước
void drawParticles() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    setMaterial(135, 206, 250, 30);
    for (const auto& p : particles) {
        glPushMatrix();
        glTranslatef(p.x, p.y, p.z);
        drawSphere(0.02f); // Tia nước là hình cầu nhỏ
        glPopMatrix();
    }
    glDisable(GL_BLEND);
}

// Hàm vẽ trục vòi phun
void drawFountainBase() {
    glPushMatrix();

    setMaterial(74, 112, 139, 30);

    glTranslatef(0.0f, -0.5f, 0.0f);
    rx(90);
    drawCylinder(0.02f, 0.06f, 1.2f); // Trục to
    glTranslatef(0.0f, 0, -0.5f);

    drawCylinder(0.02f, 0.02f, 1.0f); // Trục nhỏ
    glPopMatrix();
}

void FinalWaterMachine() {

    glPushMatrix();
    drawFountainBase(); // Vẽ trục vòi phun
    glPopMatrix();
    drawParticles();    // Vẽ các tia nước

}
void FinalWaterMachines() {
    glPushMatrix();
    t(0, 2, 1);
    s(1, 2, 1);
    FinalWaterMachine();
    glPopMatrix();

    glPushMatrix();
    t(0, 2, -3);
    s(1, 2, 1);
    FinalWaterMachine();
    glPopMatrix();

    glPushMatrix();
    t(0, 2, 4);
    s(1, 2, 1);
    FinalWaterMachine();
    glPopMatrix();


    updateParticles();  // Cập nhật trạng thái tia nước
}

//-----------------------OUTPUT-----------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    updateCamera();
    //-----------------------DISPLAY OBJECT-----------------------
    House();
    Ground();
    FinalFence();

    FinalRose();
    FinalSun();
    FinalCloud();
    FinalBird();

    FinalPinkFlowers();
    FinalPineTrees();
    FinalTrees();

    FinalLedLights();
    FinalWaterMachines();



    glutSwapBuffers();
}
///-----------------------INPUT-----------------------

// Hàm xử lý chuyển động của camera
void processInput(unsigned char key, int x, int y) {
    float cameraSpeed = camSpeed;
    float frontX = cosf(cameraYaw * M_PI / 180.0f);
    float frontZ = sinf(cameraYaw * M_PI / 180.0f);

    if (key == 'w') {
        cameraX += frontX * cameraSpeed;
        cameraZ += frontZ * cameraSpeed;
    }
    if (key == 's') {
        cameraX -= frontX * cameraSpeed;
        cameraZ -= frontZ * cameraSpeed;
    }
    if (key == 'd') {
        cameraX -= frontZ * cameraSpeed;
        cameraZ += frontX * cameraSpeed;
    }
    if (key == 'a') {
        cameraX += frontZ * cameraSpeed;
        cameraZ -= frontX * cameraSpeed;
    }
    if (key == 'q') { // Di chuyển lên
        cameraY += cameraSpeed;
    }
    if (key == 'e') { // Di chuyển xuống
        cameraY -= cameraSpeed;
    }





    if (key == 'u') {
        isDoorClosing = !isDoorClosing; // Đổi trạng thái đóng/mở  cửa mái che
    }
    if (key == 'g') { // Đóng/mở cửa hàng rào
        isGateOpen = !isGateOpen;
    }






    if (key == 27) { // ESC key
        mouseCaptured = !mouseCaptured;
        if (mouseCaptured) {
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(lastMouseX, lastMouseY);
        }
        else {
            glutSetCursor(GLUT_CURSOR_INHERIT);
        }
    }

    if (key == 'y') {
        isClosing = !isClosing; // trạng thái đóng/mở mái che
    }

    if (key == 'b') {

        isLightOn = !isLightOn;


    }
    if (key == '=') {
        sprayRadius += 0.1f;
    }
    else if (key == '-') {
        sprayRadius -= 0.1f;
        if (sprayRadius < 0.1f) {
            sprayRadius = 0.1f; // Giới hạn bán kính tối thiểu
        }
    }
    else if (key == 'n') { // Bật/tắt máy phun nước
        isFountainActive = !isFountainActive;
        if (!isFountainActive) {
            particles.clear(); // Xóa tất cả hạt nước khi máy phun nước tắt
        }
    }
    if (key == 'o') { // Tăng độ nhạy chuột
        sensitivity += 0.01f;
        if (sensitivity > 1.0f) {
            sensitivity = 1.0f; // Giới hạn độ nhạy tối đa
        }
    }
    else if (key == 'p') { // Giảm độ nhạy chuột
        sensitivity -= 0.01f;
        if (sensitivity < 0.01f) {
            sensitivity = 0.01f; // Giới hạn độ nhạy tối thiểu
        }
    }
    //dc hàng cây bên trái sang trái
    if (key == 'h') MovePineTree_left -= 0.1;
    if (key == 'j') MovePineTree_left += 0.1;
    if (key == 'k') MovePineTree_right -= 0.1;
    if (key == 'l') MovePineTree_right += 0.1;


}

// Hàm xử lý chuột để xoay camera
void mouseMove(int x, int y) {
    if (mouseCaptured) {
        int dx = x - windowWidth / 2;
        int dy = windowHeight / 2 - y;
        glutWarpPointer(windowWidth / 2, windowHeight / 2); // Cố định chuột ở giữa màn hình

        cameraYaw += dx * sensitivity;
        cameraPitch += dy * sensitivity;

        if (cameraPitch > 89.0f) cameraPitch = 89.0f;
        if (cameraPitch < -89.0f) cameraPitch = -89.0f;
    }
}

//-----------------------INIT-----------------------
// Khởi tạo OpenGL
void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
    setupLighting();
}

// Thiết lập khung nhìn
void reshape(int w, int h) {
    if (h == 0) h = 1; // Tránh chia cho 0
    float aspect = static_cast<float>(w) / static_cast<float>(h); // Tỷ lệ khung hình

    windowWidth = w;
    windowHeight = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.1, 100.0); // FOV 60 độ, phù hợp cho FPS
    glMatrixMode(GL_MODELVIEW);
}
// Hàm tự động làm mới khung hình
void timer(int value) {
    updateWing(); // Gọi hàm updateWing trước khi vẽ lại
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}
// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Valorant Style FPS Camera");

    initOpenGL();
    glutDisplayFunc(display);
    glutIdleFunc(IdleObject);


    glutReshapeFunc(reshape);
    glutKeyboardFunc(processInput);
    glutPassiveMotionFunc(mouseMove);

    glutSetCursor(GLUT_CURSOR_NONE); // Ẩn con trỏ chuột
    glutWarpPointer(windowWidth / 2, windowHeight / 2);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
    return 0;
}