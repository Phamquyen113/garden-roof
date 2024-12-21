#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
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
float cameraX = 0.0f, cameraY = 1.0f, cameraZ = 5.0f;
float cameraYaw = -90.0f, cameraPitch = 0.0f;
float speed = 0.06f;
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
//code các đối tượng ở đây

// CLOUDS
// //-----------------------CLOUD VARIABLES-----------------------
float childSizes[4];


float cloudRadius = 3.0f;    // Bán kính quỹ đạo mây mẹ
float cloudAngle = 0.0f;     // Góc hiện tại của mây mẹ
float cloudSpeed = 0.0001f;    // Tốc độ mây mẹ di chuyển
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



//-----------------------OUTPUT-----------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    updateCamera();
    glPushMatrix();
    s(0.8f, 0.8f, 0.8f);
    drawCloud();
    glPopMatrix();

    glPushMatrix();
    s(0.5f, 0.5f, 0.5f);

    t(0.2f, 0.5f, 0.3f);
    drawCloud();

    glPopMatrix();
    glutSwapBuffers();
}
///-----------------------INPUT-----------------------

// Hàm xử lý chuyển động của camera
void processInput(unsigned char key, int x, int y) {
    float cameraSpeed = speed;
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
    if (key == 'a') {
        cameraX -= frontZ * cameraSpeed;
        cameraZ += frontX * cameraSpeed;
    }
    if (key == 'd') {
        cameraX += frontZ * cameraSpeed;
        cameraZ -= frontX * cameraSpeed;
    }
    if (key == 'q') { // Di chuyển lên
        cameraY += cameraSpeed;
    }
    if (key == 'e') { // Di chuyển xuống
        cameraY -= cameraSpeed;
    }

    if (key == 'p') { // Tăng độ nhạy chuột
        sensitivity += 0.01f;
        if (sensitivity > 1.0f) sensitivity = 1.0f; // Giới hạn độ nhạy tối đa
    }
    if (key == 'P') { // Giảm độ nhạy chuột
        sensitivity -= 0.01f;
        if (sensitivity < 0.01f) sensitivity = 0.01f; // Giới hạn độ nhạy tối thiểu
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

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Valorant Style FPS Camera");

    initOpenGL();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(processInput);
    glutPassiveMotionFunc(mouseMove);

    glutSetCursor(GLUT_CURSOR_NONE); // Ẩn con trỏ chuột
    glutWarpPointer(windowWidth / 2, windowHeight / 2);
    generateRandomChildSizes(childSizes, 4);
    glutMainLoop();
    return 0;
}