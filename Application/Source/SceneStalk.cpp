#include "SceneStalk.h"
#include "GL\glew.h"
#include <GLFW/glfw3.h>
#include "Mtx44.h"
#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"
#include "SceneInvestigation.h"
#include <fstream>
#include <sstream>
#include "Hitbox.h"


SceneStalk::SceneStalk()
{
}
SceneStalk::~SceneStalk()
{
}

void SceneStalk::InitHitboxes()
{
	//door                                           
	hitbox.push_back(Hitbox(25.f, -1.f, 48.f, 200.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(0.f, -1.f, -26.f, 200.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(-9.f, -1.f, 48.f, 200.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(-10.5f, -1.f, 120.f, 200.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(24.f, -1.f, 120.f, 200.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(78.5f, -1.f, 123.f, 200.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(-60.5f, -1.f, 195.f, 200.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(-26.f, -1.f, 195.f, 200.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(8.5f, -1.f, 195.f, 200.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(43.f, -1.f, 195.f, 200.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(63.f, -1.f, 265.f, 400.f, 20.f, 2.f));

	//walls
	hitbox.push_back(Hitbox(-63.f, -1.f, 8.f, 50.f, 20.f, 100.f));
	hitbox.push_back(Hitbox(55.f, -1.f, 8.f, 50.f, 20.f, 100.f));
	//first room ^^^
	// SECOND ROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOM
	hitbox.push_back(Hitbox(123.f, -1.f, 90.f, 50.f, 20.f, 400.f));
	hitbox.push_back(Hitbox(-113.f, -1.f, 90.f, 50.f, 20.f, 400.f));

	/*hitbox.push_back(Hitbox(16.f, -1.f, 48.f, 25.f, 20.f, 45.f));
	hitbox.push_back(Hitbox(-40.f, -1.f, -25.5f, 75.f, 25.f, 45.f));
	hitbox.push_back(Hitbox(35.f, -1.f, -27.5f, 75.f, 20.f, 45.f));
	hitbox.push_back(Hitbox(-39.f, -1.f, 49.5f, 75.f, 25.f, 45.f));
	hitbox.push_back(Hitbox(100.f, -1.f, 48.f, 75.f, 25.5f, 45.f));
	hitbox.push_back(Hitbox(-18.7f, -1.f, 48.f, 75.f, 25.5f, 45.f));
	hitbox.push_back(Hitbox(100.f, 32.f, 50.f, 75.f, 32.f, 45.f));

	hitbox.push_back(Hitbox(-95.f, 32., 123.f, 75.f, 32.f, 45.f));
	hitbox.push_back(Hitbox(-95.f, -10.5f, 123.f, 75.f, 33.f, 45.f));

	hitbox.push_back(Hitbox(-20.5f, 19.f, 123.f, 120.f, 10.f, 45.f));
	hitbox.push_back(Hitbox(-10.5f, -1.f, 123.f, 25.f, 20.f, 45.f));
	hitbox.push_back(Hitbox(24.f, -1.f, 123.f, 45.f, 20.f, 45.f));
	hitbox.push_back(Hitbox(78.5f, -1.f, 123.f, 20.f, 20.f, 45.f));*/
}


void SceneStalk::Init()
{
	// Init VBO here
	InitHitboxes();

	pickup = false;

	

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights"); //in case you missed out practical 7
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");;
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	glUseProgram(m_programID);
	glUniform1i(m_parameters[U_NUMLIGHTS], 4);

	/*light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(15, 26, 30);
	light[0].color.Set(1, 1, 1);
	light[0].power = 10;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);


	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(0, 26, 20);
	light[1].color.Set(1, 1, 1);
	light[1].power = 10;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);


	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[1].exponent);*/

	light[2].type = Light::LIGHT_DIRECTIONAL;
	light[2].position.Set(-15, 26, 115);
	light[2].color.Set(1, 1, 1);
	light[2].power = 1;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);


	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[2].exponent);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);


	camera.Init(Vector3(-10.2, 9.5, -0.07), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));

	for (int i = 0; i < NUM_GEOMETRY; i++)	meshList[i] = nullptr;

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1000, 1000, 1000);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("light", Color(1, 1, 1), 50, 100);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 50, 100);
	meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateHemiSphere("hemisphere", Color(1, 1, 1), 50, 100);
	meshList[GEO_TORUS] = MeshBuilder::GenerateTorus("torus", Color(0.7, 0.7, 0.7), 50, 50, 15, 1);
	meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("cylinder", Color(0.1, 0.1, 0.1), 50, 1);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("light ball", Color(1, 1, 1), 50, 100);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0., 0., 0.), 1.f, 1.f, 1.f);

	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(1, 0.8196, 0.8627), 50.f, 1.f, 1.f);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//DimboFont.tga");

	meshList[GEO_GROUND] = MeshBuilder::GenerateFloor("floor", Color(0, 0, 0), 1.f, 1.f);
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//wood.tga");

	meshList[GEO_BUTTON] = MeshBuilder::GenerateCylinder("cylinder", Color(1, 0, 0), 50, 1);

	meshList[GEO_WALLWALL] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//floorHalf.obj", "OBJ//floorHalf.mtl");

	meshList[GEO_WINDOW] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//wallWindow.obj", "OBJ//wallWindow.mtl");

	/*meshList[GEO_LAYOUT] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//Doortime.obj", "OBJ//Doortime.mtl"); */

	/*meshList[GEO_REDOOR] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//RedDoor2test.obj", "OBJ//RedDoor2test.mtl");*/

	meshList[GEO_DOOR1] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//doorway.obj", "OBJ//doorway.mtl");

	meshList[GEO_WALLS] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//wall.obj", "OBJ//wall.mtl");

	meshList[GEO_TV] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//televisionModern.obj", "OBJ//televisionModern.mtl");

	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//tableCloth.obj", "OBJ//tableCloth.mtl");

	meshList[GEO_SEAT] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//loungeChairRelax.obj", "OBJ//loungeChairRelax.mtl");

	meshList[GEO_LAPTOP] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//laptop.obj", "OBJ//laptop.mtl");

	meshList[GEO_BOOKS] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//books.obj", "OBJ//books.mtl");

	meshList[GEO_MOUSE] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//computerMouse.obj", "OBJ//computerMouse.mtl");

	meshList[GEO_DOC] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//Documents.obj", "OBJ//Documents.mtl");

	/*meshList[GEO_PHONE] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//3d-model.obj", "OBJ//3d-model.mtl");*/

	/*meshList[GEO_PHONE]->textureID = LoadTGA("Image//wood.tga");*/

	/*meshList[GEO_GROUND] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//floorHalf.obj", "OBJ//floorHalf.mtl");*/


	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	glEnable(GL_DEPTH_TEST);

	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], m_parameters[U_MATERIAL_DIFFUSE], m_parameters[U_MATERIAL_SPECULAR], m_parameters[U_MATERIAL_SHININESS]);

	bLightEnabled = true;

	FPS = 0;

	textMaxWidth = 64; //initial value

	RenderE1 = 0;
	RenderE2 = 0;
	RenderE3 = 0;
	RenderE4 = 0;
	RenderE5 = 0;
	RenderE6 = 0;
	RenderE7 = 0;
	RenderE9 = 0;
	RenderE10 = 0;
	Echeck10 = 10;

	Echeck1 = 0;
	Echeck2 = 0;
	Echeck3 = 0;
	Echeck4 = 0;
	Echeck5 = 0;
	Echeck6 = 0;
	Echeck7 = 0;
	Echeck8 = 0;
	Echeck9 = 0;
	dooropen = 0;
	doorlock = 0;

	Qpickup = 0;
	pushdown = 0;
	nextscene = false;

	//for text spacing (check)
	const char* file_path;
	file_path = "Image//FontData.csv"; //name of font data csv file
	fileStream.open(file_path, std::ios::binary);
	if (!fileStream.is_open())
	{
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
	}
	else {
		while (!fileStream.eof()) { //took from LoadOBJ
			std::string buf;
			std::getline(fileStream, buf, ' ');
			if (buf == "Char") {
				std::getline(fileStream, buf, ' ');
				unsigned i = stoi(buf);
				std::getline(fileStream, buf, ',');
				if (buf == "Base Width") {
					std::getline(fileStream, buf);
					unsigned width = stoi(buf);
					textSpacing[i] = width;
				}
				else {
					std::getline(fileStream, buf);
				}
			}
			else if (buf == "Cell") {
				std::getline(fileStream, buf, ',');
				if (buf == "Width") {
					std::getline(fileStream, buf);
					textMaxWidth = stoi(buf);
				}
				else {
					std::getline(fileStream, buf);
				}
			}
			else {
				std::getline(fileStream, buf);
			}
		}
		fileStream.close();
	}
}

void SceneStalk::Update(double dt)
{
	camera.Update(dt, hitbox);
	FPS = 1 / (float)dt;
	view = (camera.target - camera.position).Normalized();

	right = view.Cross(camera.up);
	right.y = 0;
	right.Normalize();

	float LSPEED = 10.0;
	static int maxShoulder = 0;
	static int maxThigh = 0;
	static int counter = 0;
	static int spin = 0;
	static int startSpin = 0;
	static int timer = 0;
	static int temp = 0;
	static float CAMERA_SPEED = 30.f;

	/*if (Application::IsKeyPressed('I'))	light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))	light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))	light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))	light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))	light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))	light[0].position.y += (float)(LSPEED * dt);*/

	if (Application::IsKeyPressed('1')) glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3')) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4')) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	if (Application::IsKeyPressed('5'))
	{
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('9'))		 bLightEnabled = false;
	else if (Application::IsKeyPressed('0')) bLightEnabled = true;

	//Mouse Inputs
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		//Converting Viewport space to UI space
		double x, y;

		Application::GetCursorPos(&x, &y);
		unsigned w = Application::GetWindowWidth();
		unsigned h = Application::GetWindowHeight();

		float BUTTON_TOP = 1;
		float BUTTON_BOTTOM = 0;
		float BUTTON_LEFT = 0;
		float BUTTON_RIGHT = 1;

		float posX = (x / w) * 80; //convert (0,800) to (0,80)
		float posY = 60 - ((y / h) * 60); //convert (600,0) to (0,60)
		std::cout << "posX:" << posX << " , posY:" << posY << std::endl;
		if (posX > BUTTON_LEFT && posX < BUTTON_RIGHT && posY > BUTTON_BOTTOM && posY < BUTTON_TOP)
		{
			std::cout << "Hit!" << std::endl;
			//trigger user action or function
		}
		else
		{
			std::cout << "Miss!" << std::endl;
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}
	//first left door
	if ((camera.position.x > 14 && camera.position.x < 27) && (camera.position.z > 37 && camera.position.z < 46))
	{
		RenderE1 = 1;
		if (Application::IsKeyPressed('Q'))
		{
			if (Echeck1 == 0)
			{
				
				camera.Init(Vector3(20.8, 9.5, 58), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));
				
			}
			
		}
		else
		{
			
		}
	}
	else
	{
		RenderE1 = 0;
	}
	

	FPS = dt;
	camera.Update(dt, hitbox);

	if ((camera.position.x > -19 && camera.position.x < -8) && (camera.position.z > 37 && camera.position.z < 46))
	{
		RenderE2 = 1;
		if (Application::IsKeyPressed('Q'))
		{
			if (Echeck1 == 0)
			{
				
				camera.Init(Vector3(-10.2, 9.5, -0.07), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));
				
			}
			
		}
		else
		{
			
		}
	}
	else
	{
		RenderE2 = 0;
	}

	if ((camera.position.x > 60.5 && camera.position.x < 85) && (camera.position.z > 108 && camera.position.z < 120))
	{
		RenderE3 = 1;
		if (Application::IsKeyPressed('Q'))
		{
			if (Echeck1 == 0)
			{

				camera.Init(Vector3(-10.2, 9.5, -0.07), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));

			}

		}
		else
		{

		}
	}
	else
	{
		RenderE3 = 0;
	}


	if ((camera.position.x > 11 && camera.position.x < 25) && (camera.position.z > 108 && camera.position.z < 120))
	{
		RenderE4 = 1;
		if (Application::IsKeyPressed('Q'))
		{
			if (Echeck1 == 0)
			{

				camera.Init(Vector3(-10.2, 9.5, -0.07), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));

			}

		}
		else
		{

		}
	}
	else
	{
		RenderE4 = 0;
	}

	if ((camera.position.x > -23 && camera.position.x < -8) && (camera.position.z > 108 && camera.position.z < 120))
	{
		RenderE5 = 1;
		if (Application::IsKeyPressed('Q'))
		{
			if (Echeck1 == 0)
			{

				camera.Init(Vector3(-14.2, 9.5, 130), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));

			}

		}
		else
		{

		}
	}
	else
	{
		RenderE5 = 0;
	}

	if ((camera.position.x > 31 && camera.position.x < 44) && (camera.position.z > 182 && camera.position.z < 191))
	{
		RenderE6 = 1;
		if (Application::IsKeyPressed('Q'))
		{
			if (Echeck1 == 0)
			{

				camera.Init(Vector3(-10.2, 9.5, -0.07), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));

			}

		}
		else
		{

		}
	}
	else
	{
		RenderE6 = 0;
	}

	if ((camera.position.x > -3 && camera.position.x < 9) && (camera.position.z > 182 && camera.position.z < 191))
	{
		RenderE7 = 1;
		if (Application::IsKeyPressed('Q'))
		{
			if (Echeck1 == 0)
			{

				camera.Init(Vector3(-30.2, 9.5, 201), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));

			}

		}
		else
		{

		}
	}
	else
	{
		RenderE7 = 0;
	}

	if ((camera.position.x > -39 && camera.position.x < -25) && (camera.position.z > 182 && camera.position.z < 191))
	{
		RenderE8 = 1;
		if (Application::IsKeyPressed('Q'))
		{
			if (Echeck1 == 0)
			{

				camera.Init(Vector3(-10.2, 9.5, -0.07), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));

			}

		}
		else
		{

		}
	}
	else
	{
		RenderE8 = 0;
	}

	if ((camera.position.x > -75 && camera.position.x < -57) && (camera.position.z > 182 && camera.position.z < 191))
	{
		RenderE9 = 1;
		if (Application::IsKeyPressed('Q'))
		{
			if (Echeck1 == 0)
			{

				camera.Init(Vector3(-10.2, 9.5, -0.07), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));

			}

		}
		else
		{

		}
	}
	else
	{
		RenderE9 = 0;
	}

	if ((camera.position.z > 244 && camera.position.z < 255) && (camera.position.x > -58 && camera.position.x < -47.5))
	{
		RenderE10 = 1;
		if (Application::IsKeyPressed('X'))
		{
			pushdown = -1000;
			Qpickup = 1;
		}
	}
	else
	{
		RenderE10 = 0;
		/*Qpickup = 2;*/
	}
	/*if ((camera.position.x > 0.6 && camera.position.x < -9.2) && (camera.position.z > 259 && camera.position.z < 264))*/
	
	if (Qpickup == 1)
	{
		RenderE10 = 0;
		if ((camera.position.x > -9.5 && camera.position.x < 4.37) && (camera.position.z > 259 && camera.position.z < 265))
		{
			dooropen = 1;
			if (Application::IsKeyPressed('Q'))
			{
				
				nextscene = true;
			}
			
		
		}
		else
		{
			dooropen = 0;
		}
		
	}
	else if (Qpickup == 0)
	{
		if ((camera.position.x > -9.5 && camera.position.x < 4.37) && (camera.position.z > 259 && camera.position.z < 265))
		{
			doorlock = 1;
		}
		else
		{
			doorlock = 0;
		}
	}
}

void SceneStalk::RenderSkybox() {
	const float OFFSET = 499;
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -OFFSET);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, OFFSET);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-OFFSET, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(OFFSET, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, OFFSET, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -OFFSET, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

}
void SceneStalk::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0) {
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else {
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
void SceneStalk::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	float offset = 0.f;
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(offset, 0, i * 0.001f); //slightly increase z val
		offset += (textSpacing[(int)(text[i])] / (float)textMaxWidth);
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
}
void SceneStalk::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	float offset = 0.f;
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + offset, 0.5f, 0);
		offset += (textSpacing[(int)(text[i])] / (float)textMaxWidth);
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
}
void SceneStalk::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//to do: scale and translate accordingly
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}





void SceneStalk::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[2].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[2].position.x, light[2].position.y, light[2].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[2].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[2].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[3].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[3].position.x, light[3].position.y, light[3].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[3].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[3].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
	}

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	RenderSkybox();

	//RenderMesh(meshList[GEO_AXES], false);
	


	std::ostringstream Xcoords;
	Xcoords.str("");
	Xcoords.precision(3);
	Xcoords << "X : " << camera.position.x;
	RenderTextOnScreen(meshList[GEO_TEXT], Xcoords.str(), Color(0, 0, 1), 2, 0, 54);

	std::ostringstream Zcoords;
	Zcoords.str("");
	Zcoords.precision(3);
	Zcoords << "Z : " << camera.position.z;
	RenderTextOnScreen(meshList[GEO_TEXT], Zcoords.str(), Color(0, 0, 1), 2, 0, 52);

	modelStack.PushMatrix();
	modelStack.Translate(100, -1, -100);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_GROUND], true);
	modelStack.PopMatrix();

	

	//////////////////////////////////////////////////////////////////beginning of rooms
	modelStack.PushMatrix();
	modelStack.Translate(25, -1, 48);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //left door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -1, -26);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //backdoor
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-9, -1, 48);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //right door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(35, -1, 20);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(40, 20, 30);
	RenderMesh(meshList[GEO_TABLE], true); //table
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(26, 5.5, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(270, 0, 1, 0);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_LAPTOP], true); //table
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(26, 5.5, -1);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_MOUSE], true); //mouse
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-20, -1, -15);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(20, 20, 30);
	RenderMesh(meshList[GEO_SEAT], true); //table
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(26, 5, -2);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	/*modelStack.Rotate(90, 0, 1, 0);*/
	modelStack.Scale(30, 30, 30);
	RenderMesh(meshList[GEO_BOOKS], true); //table
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(0, 5, 0);
	///*modelStack.Rotate(180, 1, 0, 0);
	//modelStack.Rotate(180, 0, 0, 1);*/
	///*modelStack.Rotate(90, 0, 1, 0);*/
	//modelStack.Scale(3, 3, 3);
	//RenderMesh(meshList[GEO_PHONE], true); //table
	//modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	modelStack.Translate(0, -1, 6);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(30, 30, 15);
	RenderMesh(meshList[GEO_WALLWALL], true); 
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	modelStack.Translate(150, 35, -100);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(10000, 10000, 1);
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(25, 19, 48);
	modelStack.Scale(75, 10, 45);
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	

	modelStack.PushMatrix();
	modelStack.Translate(16, -1, 48);
	modelStack.Scale(25, 20, 45);
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-40, -1, -25.5);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(75, 25, 45);
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(35, -1, -27.5);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(75, 25, 45);
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-39, -1, 49.5);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(75, 25, 45);
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(100, -1, 48);
	modelStack.Rotate(360, 0, 1, 0);
	modelStack.Scale(75, 25.5, 45);
	RenderMesh(meshList[GEO_WALLS], true); //side wall
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-18.7, -1, 48);
	modelStack.Rotate(360, 0, 1, 0);
	modelStack.Scale(75, 25.5, 45);
	RenderMesh(meshList[GEO_WALLS], true); //right side wall
	modelStack.PopMatrix();

	/// <summary>
	/// /////////////////////////////////////////////////2nd room
	/// </summary>

	modelStack.PushMatrix();
	modelStack.Translate(100, 32, 50);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(75, 32, 45);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-95, 32, 123);
	modelStack.Rotate(90, 0, -1, 0);
	modelStack.Rotate(180, -1, 0, 0);
	modelStack.Scale(75, 32, 45);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-95, -10.5, 123);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(75, 33, 45);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-10.5, -1, 120);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //right door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-20.5, 19, 123);		
	modelStack.Scale(120, 10, 45);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_WALLS], true); //rightdoor wall up
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-10.5, -1, 123);
	modelStack.Scale(25, 20, 45);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_WALLS], true); //rightdoor wall up
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(24, -1, 120);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //right door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(24, -1, 123);
	modelStack.Scale(45, 20, 45);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_WALLS], true); //rightdoor wall up
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(78.5, -1, 120);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //right door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(78.5, -1, 123);
	modelStack.Scale(20, 20, 45);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_WALLS], true); //rightdoor wall up
	modelStack.PopMatrix();

	
	/// <summary>
	/// //////////////////////////////////////////////////////////////////////// third room
	/// </summary>\
	
	modelStack.PushMatrix();
	modelStack.Translate(100, 32, 125);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(75, 32, 45);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(-95, 32, 197);
	modelStack.Rotate(90, 0, -1, 0);
	modelStack.Rotate(180, -1, 0, 0);
	modelStack.Scale(75, 32, 55);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-95, -10.5, 197);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(25, 33, 45);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-60.5, -1, 195);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //right door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-80.5, 19, 197);
	modelStack.Scale(180, 10, 45);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_WALLS], true); //rightdoor wall up
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-60.5, -10.5, 197);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(25, 33, 45);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-26, -1, 195);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //right door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-26, -10.5, 197);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(25, 33, 45);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(8.5, -1, 195);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //right door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(8.5, -10.5, 197);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(25, 33, 45);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(43, -1, 195);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //right door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(43, -10.5, 197);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(55, 33, 45);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	//the fourth room //////////////////////////////////////////////////////////////

	modelStack.PushMatrix();
	modelStack.Translate(100, 32, 200);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(80, 32, 45);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-95, 32, 270);
	modelStack.Rotate(90, 0, -1, 0);
	modelStack.Rotate(180, -1, 0, 0);
	modelStack.Scale(80, 32, 55);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-95, -10.5, 270);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(200, 32, 55);      //wall first of 2nd room
	RenderMesh(meshList[GEO_WALLS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.5, -1, 266.5);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_DOOR1], true); //right door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, -1, 250);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(20, 20, 30);
	RenderMesh(meshList[GEO_TABLE], true); //table
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-35, -1, 250);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(20, 20, 30);
	RenderMesh(meshList[GEO_TABLE], true); //table
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-44, 6, 250);
	modelStack.Translate(0, 0, pushdown);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_DOC], true); //table
	modelStack.PopMatrix();

	/// <summary>
	/// ///////////////////////////////////////////
	/// </summary>
	modelStack.PushMatrix();
	modelStack.Translate(-5, 30, -25);
	modelStack.Scale(7, 7, 7);
	RenderText(meshList[GEO_TEXT], "Con-heist", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(34, 25, -10);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "Instructions:", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(34, 23, -10);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "It would seem that your target Melon Tusk has entered through one of these doors...", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(34, 21, -10);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "Pick the correct door.... ", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(34, 19, -10);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "It is most advisable to not pick the wrong door. ", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(96, 19, 70);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "SO IT seems that you have made it past the first door correctly...", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(96, 17, 70);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "If you had chosen the wrong door, you would have been sent back...", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(96, 15, 70);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "So don't choose the wrog door LAD...!", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(96, 19, 70);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], " ", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(92, 22, 147);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "(67)NeuralNetwork OVERLOADI%#@#$^!$@", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(96 , 20, 147);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "(68)NeuralNetwork OVERLOADI%#@#$^!$@", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(93, 15, 147);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "^@&()@*PICK THE FINAL DOOR", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(93, 15, 227);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "Good job, you've made it past the doors.", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(93, 13, 227);             //(dist from left wall, height from ground, where on wall)
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "Find the Documents and you may leave.", Color(1, 0, 0));
	modelStack.PopMatrix();

	if (RenderE1 == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to Interact", Color(0, 0, 0), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (RenderE2 == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to Interact", Color(0, 0, 0), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (RenderE3 == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to Interact", Color(0, 0, 0), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (RenderE4 == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to Interact", Color(0, 0, 0), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (RenderE5 == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to Interact", Color(0, 0, 0), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (RenderE6 == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to Interact", Color(0, 0, 0), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (RenderE7 == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to Interact", Color(0, 0, 0), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (RenderE8 == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to Interact", Color(0, 0, 0), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (RenderE9 == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to Interact", Color(0, 0, 0), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (RenderE10 == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press X to Pick up Documents", Color(1, 1, 1), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (doorlock == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Find the documents before leaving the room.", Color(1, 1, 1), 5, 12, 10);
		modelStack.PopMatrix();
	}

	if (dooropen == 1)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Q to open", Color(1, 1, 1), 5, 12, 10);
		modelStack.PopMatrix();
	}

	RenderMeshOnScreen(meshList[GEO_QUAD], 40, 30, 20, 10);

	std::ostringstream ss;
	ss.str("");
	ss.precision(4);
	ss << "FPS: " << FPS;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 4, 0, 0);

}

void SceneStalk::Exit()
{
	// Cleanup VBO here
	delete meshList[GEO_QUAD];
	delete meshList[GEO_AXES];
	delete meshList[GEO_CUBE];
	delete meshList[GEO_CIRCLE];
	delete meshList[GEO_SPHERE];
	delete meshList[GEO_TORUS];
	delete meshList[GEO_CYLINDER];
	delete meshList[GEO_HEMISPHERE];
	delete meshList[GEO_CONE];
	delete meshList[GEO_LEFT];
	delete meshList[GEO_RIGHT];
	delete meshList[GEO_TOP];
	delete meshList[GEO_BOTTOM];
	delete meshList[GEO_FRONT];
	delete meshList[GEO_BACK];
	delete meshList[GEO_GLASS];
	delete meshList[GEO_BPORTAL];
	delete meshList[GEO_OPORTAL];
	delete meshList[GEO_TEXT];
	delete meshList[GEO_TOILET];
	delete meshList[GEO_COMCUBE];
	delete meshList[GEO_BED];
	delete meshList[GEO_NIGHTSTAND];
	delete meshList[GEO_WALL];
	delete meshList[GEO_DOOR];
	delete meshList[GEO_BUTTON];
	delete meshList[GEO_PERSON];
	delete meshList[GEO_EXIT];
	delete meshList[GEO_RADIO];
	delete meshList[GEO_SINK];
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
void SceneStalk::CurrentScene()
{

}
int SceneStalk::NextScene()
{
	return 0;
}