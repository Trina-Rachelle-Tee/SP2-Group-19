#include "SceneHouseGame.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"
#include <fstream>
#include <sstream>


SceneHouseGame::SceneHouseGame()
{
}

SceneHouseGame::~SceneHouseGame()
{
}

void SceneHouseGame::InitHitbox()
{
	//Hitboxes, pos xyz, scale xyz

	//entities
	entities.push_back(new Object("Passport",	0.f, Vector3(32.6, 5, 68.2), Vector3(0, 0, 1), 500.f));
	hitbox.push_back(Hitbox(32.6f, 5.f, 68.2f, 3.f, 3.f, 3.f));

	entities.push_back(new Object("Documents",	0.f, Vector3(19.2, 6, 19.4), Vector3(0, 0, 1), 400.f));
	hitbox.push_back(Hitbox(19.2f, 6.f, 19.4f, 3.f, 3.f, 3.f));

	entities.push_back(new Object("Clothes",	0.f, Vector3(-13, 5, 77.8), Vector3(0, 0, 1), 100.f));
	hitbox.push_back(Hitbox(-13.f, 5.f, 77.8f, 3.f, 3.f, 3.f));

	entities.push_back(new Object("Money",		0.f, Vector3(-22.8, 5, 87.1), Vector3(0, 0, 1), 200.f));
	hitbox.push_back(Hitbox(-22.8f, 5.f, 87.1f, 3.f, 3.f, 3.f));

	entities.push_back(new Object("Hard drive", 0.f, Vector3(15.8, 5, 72.3), Vector3(0, 0, 1), 600.f));
	hitbox.push_back(Hitbox(15.8f, 5.f, 72.3f, 3.f, 3.f, 3.f));

	entities.push_back(new Object("Wallet",		0.f, Vector3(-10, 5, 10), Vector3(0, 0, 1), 400.f));
	hitbox.push_back(Hitbox(-10.f, 5.f, 10.f, 3.f, 3.f, 3.f));

	entities.push_back(new Object("Phone",		0.f, Vector3(33.5, 6., 21.7), Vector3(0, 0, 1), 600.f));
	hitbox.push_back(Hitbox(33.5f, 6.f, 21.7f, 3.f, 3.f, 3.f));

	entities.push_back(new Object("Evidence1",	0.f, Vector3(30.7, 5, 68), Vector3(0, 0, 1), 300.f));
	hitbox.push_back(Hitbox(30.7f, 5.f, 68.f, 3.f, 3.f, 3.f));

	entities.push_back(new Object("Evidence2",	0.f, Vector3(-10.8, 4, 49.), Vector3(0, 0, 1), 300.f));
	hitbox.push_back(Hitbox(-10.8f, 4.f, 49.f, 3.f, 3.f, 3.f));

	entities.push_back(new Object("Medication", 0.f, Vector3(22, 9.5, 64), Vector3(0, 0, 1), 200.f));
	hitbox.push_back(Hitbox(22.f, 9.5f, 64.f, 3.f, 3.f, 3.f));

	//objs
	//pc [10]
	hitbox.push_back(Hitbox(21.2f, 0.f, 68.2f, 3.f, 10.f, 3.f));

	//door [11]
	hitbox.push_back(Hitbox(6.5f, 0.f, 1.5f, 6.f, 10.f, 1.5f));

	//box [12]
	hitbox.push_back(Hitbox(34.6f, 0.f, 87.4f, 5.f, 5.f, 5.f));

	

	//walls
	hitbox.push_back(Hitbox(-25.f, 0.f, 45.f, 0.5f, 20.f, 90.f));
	hitbox.push_back(Hitbox(40.f, 0.f, 45.f, 0.5f, 20.f, 90.f));
	hitbox.push_back(Hitbox(0.f, 0.f, 90.f, 80.f, 20.f, 0.5f));
	hitbox.push_back(Hitbox(0.f, 0.f, 00.f, 80.f, 20.f, 0.5f));

	hitbox.push_back(Hitbox(13.5f, 0.f, 47.f, 0.5f, 20.f, 16.f));
	hitbox.push_back(Hitbox(13.5f, 0.f, 69.5f, 0.5f, 20.f, 17.f));
	hitbox.push_back(Hitbox(-10.f, 0.f, 65.5f, 28.f, 20.f, .5f));
	hitbox.push_back(Hitbox(24.5f, 0.f, 65.5f, 29.f, 20.f, .5f));
	hitbox.push_back(Hitbox(25.5f, 0.f, 39.5f, 27.f, 20.f, .5f));

	//kitchen
	hitbox.push_back(Hitbox(-9.5f, 0.f, 16.5f, 11.f, 20.f, 16.f));
	hitbox.push_back(Hitbox(19.f, 0.f, 11.f, 6.f, 20.f, 20.f));
	hitbox.push_back(Hitbox(33.f, 0.f, 19.f, 1.f, 20.f, 38.f));
	hitbox.push_back(Hitbox(26.f, 0.f, 6.f, 12.f, 20.f, 1.f));
	hitbox.push_back(Hitbox(-22.5f, 0.f, 49.5f, 2.f, 20.f, 10.f));
	hitbox.push_back(Hitbox(-18.f, 0.f, 78.f, 12.f, 20.f, 12.f));
	hitbox.push_back(Hitbox(1.5f, 0.f, 43.f, 4.f, 20.f, 16.f));
	hitbox.push_back(Hitbox(-4.2f, 0.f, 37.f, 16.f, 20.f, 4.f));
	hitbox.push_back(Hitbox(-12.f, 0.f, 50.5f, 5.f, 20.f, 10.f));
	hitbox.push_back(Hitbox(23.f, 0.f, 78.1f, 3.f, 20.f, 3.f));
	hitbox.push_back(Hitbox(24.f, 0.f, 64.f, 2.f, 20.f, 2.f));
	hitbox.push_back(Hitbox(22.f, 0.f, 42.f, 14.f, 20.f, 5.f));
	hitbox.push_back(Hitbox(17.f, 0.f, 49.f, 5.f, 20.f, 5.f));
}


void SceneHouseGame::Init()
{
	// Init VBO here
	InitHitbox();

	canInteractPC = false;
	canPickup = false;
	incomingCall = true;
	gameStart = false;
	canUnload = false;
	boxFull = false;
	canPickBox = false;
	renderBox = true;
	atDoor = false;
	lose = false;
	win = false;
	index = 0.f;
	totalScore = 0.f;
	timeRemaining = 60.f;

	//dialogue
	BossDialogue.push_back("Hey...");
	BossDialogue.push_back("Listen we don't have much time...");
	BossDialogue.push_back("An anonymous tipped our scam off to Melon Tusk.");
	BossDialogue.push_back("Your IP address has been leaked and the cops are on their way.");
	BossDialogue.push_back("Try to dispose of any evidence and pack your bags.");
	BossDialogue.push_back("You have 1 minute to pack your things into a box.");
	BossDialogue.push_back("**Pick up the floating objects using [E]**");
	BossDialogue.push_back("**You can carry up to 3 items at once**");
	BossDialogue.push_back("**Pack 10 items into the box and leave the apartment with the box**");
	BossDialogue.push_back("*Hangs up...*");

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

	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");

	m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
	m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	glUseProgram(m_programID);
	glUniform1i(m_parameters[U_NUMLIGHTS], 5);

	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(21, 13, 22);
	light[0].color.Set(1, 1, 1);
	light[0].power = .8;
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

	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(-9, 13, 22);
	light[1].color.Set(1, 1, 1);
	light[1].power = .8;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);


	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	light[2].type = Light::LIGHT_POINT;
	light[2].position.Set(-9, 13, 50);
	light[2].color.Set(1, 1, 1);
	light[2].power = .8;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);


	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	light[3].type = Light::LIGHT_POINT;
	light[3].position.Set(-8, 13, 80);
	light[3].color.Set(1, 1, 1);
	light[3].power = .8;
	light[3].kC = 1.f;
	light[3].kL = 0.01f;
	light[3].kQ = 0.001f;
	light[3].cosCutoff = cos(Math::DegreeToRadian(45));
	light[3].cosInner = cos(Math::DegreeToRadian(30));
	light[3].exponent = 3.f;
	light[3].spotDirection.Set(0.f, 1.f, 0.f);


	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);

	light[4].type = Light::LIGHT_POINT;
	light[4].position.Set(28, 13, 80);
	light[4].color.Set(1, 1, 1);
	light[4].power = .8;
	light[4].kC = 1.f;
	light[4].kL = 0.01f;
	light[4].kQ = 0.001f;
	light[4].cosCutoff = cos(Math::DegreeToRadian(45));
	light[4].cosInner = cos(Math::DegreeToRadian(30));
	light[4].exponent = 3.f;
	light[4].spotDirection.Set(0.f, 1.f, 0.f);


	glUniform1i(m_parameters[U_LIGHT4_TYPE], light[4].type);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &light[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], light[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], light[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], light[4].kQ);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], light[4].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], light[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], light[4].exponent);


	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);


	camera.Init(Vector3(1, 9.5, 5), Vector3(0, 9.5, 1), Vector3(0, 1, 0));

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
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1., 1., 1.), 1.f, 1.f, 1.f);
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(1, 0.8196, 0.8627), 50.f, 1.f, 1.f);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//DimboFont.tga");

	//objs
	meshList[GEO_HOUSE] = MeshBuilder::GenerateOBJMTL("PC", "OBJ//house.obj", "OBJ//house.mtl");

	meshList[GEO_WALL] = MeshBuilder::GenerateOBJMTL("wall", "OBJ//wall.obj", "OBJ//wall.mtl");
	meshList[GEO_DOORWAY] = MeshBuilder::GenerateOBJMTL("doorway", "OBJ//wallDoorway.obj", "OBJ//wallDoorway.mtl");
	meshList[GEO_BED] = MeshBuilder::GenerateOBJMTL("bed", "OBJ//bedDouble.obj", "OBJ//bedDouble.mtl");

	meshList[GEO_PC] = MeshBuilder::GenerateOBJMTL("PC", "OBJ//computerScreen.obj", "OBJ//computerScreen.mtl");
	meshList[GEO_KB] = MeshBuilder::GenerateOBJMTL("KB", "OBJ//computerKeyboard.obj", "OBJ//computerKeyboard.mtl");
	meshList[GEO_MOUSE] = MeshBuilder::GenerateOBJMTL("Mouse", "OBJ//computerMouse.obj", "OBJ//computerMouse.mtl");
	meshList[GEO_CORNERDESK] = MeshBuilder::GenerateOBJMTL("Table", "OBJ//deskCorner.obj", "OBJ//deskCorner.mtl");
	meshList[GEO_DESK] = MeshBuilder::GenerateOBJMTL("desk", "OBJ//desk.obj", "OBJ//desk.mtl");
	meshList[GEO_PCCHAIR] = MeshBuilder::GenerateOBJMTL("pc chair", "OBJ//chairDesk.obj", "OBJ//chairDesk.mtl");

	meshList[GEO_SPEAKER] = MeshBuilder::GenerateOBJMTL("Speaker", "OBJ//speaker.obj", "OBJ//speaker.mtl");
	meshList[GEO_TV] = MeshBuilder::GenerateOBJMTL("TV", "OBJ//televisionModern.obj", "OBJ//televisionModern.mtl");
	meshList[GEO_COUCH] = MeshBuilder::GenerateOBJMTL("couch", "OBJ//loungeDesignSofa.obj", "OBJ//loungeDesignSofa.mtl");
	meshList[GEO_LONGCOUCH] = MeshBuilder::GenerateOBJMTL("long couch", "OBJ//loungeDesignSofaCorner.obj", "OBJ//loungeDesignSofaCorner.mtl");
	meshList[GEO_TOILET] = MeshBuilder::GenerateOBJMTL("toilet", "OBJ//toilet.obj", "OBJ//toilet.mtl");
	meshList[GEO_BATHTUB] = MeshBuilder::GenerateOBJMTL("bathtub", "OBJ//bathtub.obj", "OBJ//bathtub.mtl");
	meshList[GEO_SINK] = MeshBuilder::GenerateOBJMTL("sink", "OBJ//bathroomCabinetDrawer.obj", "OBJ//bathroomCabinetDrawer.mtl");
	meshList[GEO_MIRROR] = MeshBuilder::GenerateOBJMTL("mirror", "OBJ//bathroomMirror.obj", "OBJ//bathroomMirror.mtl");
	meshList[GEO_FRIDGE] = MeshBuilder::GenerateOBJMTL("fridge", "OBJ//kitchenFridge.obj", "OBJ//kitchenFridge.mtl");
	meshList[GEO_KITCHENUPPER] = MeshBuilder::GenerateOBJMTL("cabinet", "OBJ//kitchenCabinetUpperDouble.obj", "OBJ//kitchenCabinetUpperDouble.mtl");
	meshList[GEO_KITCHENSINK] = MeshBuilder::GenerateOBJMTL("kitchen sink", "OBJ//kitchenSink.obj", "OBJ//kitchenSink.mtl");
	meshList[GEO_KITCHENCABINET] = MeshBuilder::GenerateOBJMTL("kitchen cabinet", "OBJ//kitchenCabinet.obj", "OBJ//kitchenCabinet.mtl");
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJMTL("table", "OBJ//table.obj", "OBJ//table.mtl");
	meshList[GEO_CHAIR] = MeshBuilder::GenerateOBJMTL("chair", "OBJ//chair.obj", "OBJ//chair.mtl");
	meshList[GEO_COFFEETABLE] = MeshBuilder::GenerateOBJMTL("coffeetable", "OBJ//tableCoffeeGlass.obj", "OBJ//tableCoffeeGlass.mtl");
	meshList[GEO_TVTABLE] = MeshBuilder::GenerateOBJMTL("Tv table", "OBJ//cabinetTelevision.obj", "OBJ//cabinetTelevision.mtl");
	meshList[GEO_BEDSIDE] = MeshBuilder::GenerateOBJMTL("bed table", "OBJ//cabinetBed.obj", "OBJ//cabinetBed.mtl");
	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJMTL("model1", "OBJ//doorway.obj", "OBJ//doorway.mtl");
	//meshList[GEO_KITCHENSTOVE] = MeshBuilder::GenerateOBJMTL("kitchen stove", "OBJ//kitchenStove", "OBJ//kitchenStove"); doesnt work


	meshList[GEO_BOXCLOSED] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//cardboardBoxClosed.obj", "OBJ//cardboardBoxClosed.mtl");
	meshList[GEO_BOXOPEN] = MeshBuilder::GenerateOBJMTL("box open", "OBJ//cardboardBoxOpen.obj", "OBJ//cardboardBoxOpen.mtl");

	meshList[GEO_GROUND] = MeshBuilder::GenerateFloor("floor", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//woodFloor.tga");

	//entities
	meshList[GEO_PASSPORT] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//passport1.obj", "OBJ//passport1.mtl");
	meshList[GEO_DOCUMENTS] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//Documents.obj", "OBJ//Documents.mtl");
	meshList[GEO_CLOTHES] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//shirt-2.obj", "OBJ//shirt-2.mtl");
	meshList[GEO_MONEY] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//Moneyrecent.obj", "OBJ//Moneyrecent.mtl");
	meshList[GEO_HARDDRIVE] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//Harddrive.obj", "OBJ//Harddrive.mtl");
	meshList[GEO_WALLET] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//wallet.obj", "OBJ//wallet.mtl");
	meshList[GEO_WALLET]->textureID = LoadTGA("Image//woodFloor.tga");
	meshList[GEO_PHONE] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//phone.obj", "OBJ//phone.mtl");
	meshList[GEO_EVIDENCE1] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//Documents.obj", "OBJ//Documents.mtl");
	meshList[GEO_EVIDENCE2] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//Documents.obj", "OBJ//Documents.mtl");
	meshList[GEO_MEDS] = MeshBuilder::GenerateOBJMTL("box closed", "OBJ//med-pack.obj", "OBJ//med-pack.mtl");

	//hud
	meshList[GEO_DIALOGUE] = MeshBuilder::GenerateQuad("TextBox", Color(0.0, 0.0, 0.0), 1.f, 1.f);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("crosshair", Color(0.0, 0.0, 0.0), 1.f, 1.f);
	meshList[GEO_CROSSHAIR]->textureID = LoadTGA("Image//crosshair.tga");

	meshList[GEO_CALL] = MeshBuilder::GenerateQuad("call", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_CALL]->textureID = LoadTGA("Image//call(1).tga");

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	glEnable(GL_DEPTH_TEST);

	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], m_parameters[U_MATERIAL_DIFFUSE], m_parameters[U_MATERIAL_SPECULAR], m_parameters[U_MATERIAL_SHININESS]);

	bLightEnabled = true;

	FPS = 0;

	textMaxWidth = 64; //initial value

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
void SceneHouseGame::getBossDialogue()
{
	static bool isPressed = false;
	if (Application::IsKeyPressed(VK_RETURN) && playDialogue == true && !isPressed)
	{
		 if(index == 9)
		 {
			 playDialogue = false;
			 gameStart = true;
		 }
		 else
			 index += 1;
		 isPressed = !isPressed;
	}
	else if (!Application::IsKeyPressed(VK_RETURN) && playDialogue == true && isPressed)
	{
		isPressed = false;
	}
}
void SceneHouseGame::pcInteract()
{
	if (camera.PlayerInRange(hitbox, 10) == true)
	{
		canInteractPC = true;
		if (Application::IsKeyPressed('E') && incomingCall == true)
		{
			playDialogue = true;
			incomingCall = false;
		}
	}
	else
		canInteractPC = false;

	getBossDialogue();
}
void SceneHouseGame::unloadInven()
{
	if (camera.PlayerInRange(hitbox, 12) == true)
	{
		canUnload = true;
		static bool isPressed = false;
		if (Application::IsKeyPressed('E') && !isPressed)
		{
			for (int i = 0; i < inventory.size(); i++)
			{
				suitcase.push_back(inventory[i]);
				totalScore += inventory[i]->getPoints();
			}
			inventory.clear();
		}
		else if (!Application::IsKeyPressed('E') && isPressed)
		{
			isPressed = false;
		}
	}
	else
		canUnload = false;
}
void SceneHouseGame::pickBox()
{
	if (camera.PlayerInRange(hitbox, 12) == true && canPickBox == true)
	{
		static bool isPressed = false;
		if (Application::IsKeyPressed('E') && !isPressed)
		{
			renderBox = false;
			hitbox.erase(hitbox.begin() + 12);
		}
		else if (!Application::IsKeyPressed('E') && isPressed)
		{
			isPressed = false;
		}
	}
}
void SceneHouseGame::leaveHouse()
{
	if (camera.PlayerInRange(hitbox, 11) == true && renderBox == false) //11 cause box hitbox deleted so 12 is pushed to 11
	{
		atDoor = true;
		static bool isPressed = false;
		if (Application::IsKeyPressed('E') && !isPressed)
		{
			win = true;
			gameStart = false;
			atDoor = false;
		}
		else if (!Application::IsKeyPressed('E') && isPressed)
		{
			isPressed = false;
		}
	}
}
void SceneHouseGame::updateEntity(float dt)
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->rotate(dt);
	}
}
void SceneHouseGame::pickEntity()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (camera.PlayerInRange(hitbox, i) == true && entities[i]->getPickup() == false && gameStart == true && inventory.size() < 3)
		{
			canPickup = true;
			if (Application::IsKeyPressed('E'))
			{
				entities[i]->updatePickup(true);
				inventory.push_back(entities[i]);
			}
		}
		else
			canPickup = false;
	}
}
void SceneHouseGame::Update(double dt)
{
	camera.Update(dt, hitbox);
	FPS = 1 / (float)dt;
	view = (camera.target - camera.position).Normalized();

	right = view.Cross(camera.up);
	right.y = 0;
	right.Normalize();
	static float LSPEED = 10;
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

	pcInteract();
	pickEntity();
	updateEntity(dt);
	unloadInven();
	pickBox();
	leaveHouse();

	if (gameStart == true)
	{
		if (timeRemaining > 0)
		{
			timeRemaining -= dt;
		}
		else
		{
			lose = true;
			gameStart = false;
		}

	}
	if (suitcase.size() >= 10)
	{
		boxFull = true;
		canUnload = false;
	}
	if (boxFull == true)
	{
		canPickBox = true;
	}

	static int frame = 1;
	static float timer = 0;

	timer += (float)dt;
	if (incomingCall == true)
	{
		if (timer > 1.0 / 24.0)
		{
			std::string callFrame = "Image//call(" + std::to_string(frame) + ").tga";
			meshList[GEO_CALL]->textureID = LoadTGA(callFrame.c_str());
			frame++;
			if (frame > 82)
			{
				frame = 1;
			}
			timer -= 1.0 / 24.0;
		}
	}

	if (win == true && Application::IsKeyPressed(VK_RETURN))
	{
		nextScene = true;
	}
}
void SceneHouseGame::RenderSkybox() {
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
void SceneHouseGame::RenderMesh(Mesh* mesh, bool enableLight)
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
void SceneHouseGame::RenderText(Mesh* mesh, std::string text, Color color)
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
void SceneHouseGame::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void SceneHouseGame::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 0);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
void SceneHouseGame::Render()
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

	if (light[4].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[4].position.x, light[4].position.y, light[4].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[4].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[4].position;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[4].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT4_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[4].position;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
	}

	

	

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	RenderSkybox();

	//RenderMesh(meshList[GEO_AXES], false);



	//house
	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 0, 0);
		modelStack.Rotate(0, 1, 0, 0);
		modelStack.Scale(13, 13, 13);

		
		// bedroom
		// walls
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, 0);
			modelStack.Rotate(0, 1, 0, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(1, 0, 0);
			modelStack.Rotate(0, 1, 0, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_DOORWAY], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(1, 0, 5);
			modelStack.Rotate(0, 1, 0, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_DOORWAY], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 7);
			modelStack.Rotate(00, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(2, 0, 7);
			modelStack.Rotate(00, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(1, 0, 7);
			modelStack.Rotate(00, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(0, 0, 7);
			modelStack.Rotate(00, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-1, 0, 7);
			modelStack.Rotate(00, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 5);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 6);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(1, 0, 5);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-2, 0, 5);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-2, 0, 6);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();
		}
		
		//pc
		modelStack.PushMatrix();
		modelStack.Translate(2, 0, 5.42);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_DESK], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2, 0, 6);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_CORNERDESK], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2, 0, 6);
		modelStack.Rotate(-45, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_PCCHAIR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(1.51, 0.38, 5.17);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_PC], true);

			modelStack.PushMatrix();
			modelStack.Translate(0, 0, -0.2);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_KB], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-0.4, 0,-0.2);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_MOUSE], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
		
		modelStack.PushMatrix();
		modelStack.Translate(-0.9, 0, 6.5);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_BED], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1.65, 0, 6.8);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_BEDSIDE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1.65, 0, 5.5);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_BEDSIDE], true);
		modelStack.PopMatrix();




		// bathroom
		//walls
		{
			modelStack.PushMatrix();
			modelStack.Translate(1, 0, 4);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_DOORWAY], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(1, 0, 3);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(2, 0, 3);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 3);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 3);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 4);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 5);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(2, 0, 5);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();
		}
		
		modelStack.PushMatrix();
		modelStack.Translate(2, -0.05, 4.55);
		modelStack.Rotate(0, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_SINK], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1.9, 0.65, 4.95);
		modelStack.Rotate(0, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_MIRROR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1, 0, 4);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1.05, 1, 1);
		RenderMesh(meshList[GEO_TOILET], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.2, 0, 3);
		modelStack.Rotate(0, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_BATHTUB], true);
		modelStack.PopMatrix();

		//living room
		//walls
		{
			modelStack.PushMatrix();
			modelStack.Translate(-1, 0, 0);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-2, 0, 0);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-2, 0, 1);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-2, 0, 2);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-2, 0, 3);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-2, 0, 4);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-1, 0, 5);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(0, 0, 5);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(2, 0, 0);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 0);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 0);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 1);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 2);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(3, 0, 3);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();
		}
		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 4);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_LONGCOUCH], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.75, 0, 0);
		modelStack.Rotate(0, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_DOOR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 4);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_COFFEETABLE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1.6, 0, 4.2);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_TVTABLE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1.75, 0.3, 3.8);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_TV], true);
		modelStack.PopMatrix();


		modelStack.PushMatrix();
		modelStack.Translate(-0.5, 0, 2);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_TABLE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-0.5, 0, 1.5);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_TABLE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 1.8);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_CHAIR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 1.4);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_CHAIR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 1.0);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_CHAIR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-0.5, 0, 1.6);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_CHAIR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-0.5, 0, 1.2);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_CHAIR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-0.5, 0, .8);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_CHAIR], true);
		modelStack.PopMatrix();

		//kitchen
		modelStack.PushMatrix();
		modelStack.Translate(2.7, 0, 2.5);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_FRIDGE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1.7, 0, 0.5);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENSINK], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.1, 0, 0.5);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENSINK], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0, 0.0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENCABINET], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0, 0.4);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENCABINET], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0, 0.8);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENCABINET], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0, 1.2);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENCABINET], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0, 1.6);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENCABINET], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0, 2.);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENCABINET], true);
		modelStack.PopMatrix();

		//
		modelStack.PushMatrix();
		modelStack.Translate(2.1, 0.8, 0.2);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENUPPER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1.7, 0.8, 0.2);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENUPPER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0.8, 0.0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENUPPER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0.8, 0.4);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENUPPER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0.8, 0.8);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENUPPER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0.8, 1.2);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENUPPER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0.8, 1.6);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENUPPER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.5, 0.8, 2.);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENUPPER], true);
		modelStack.PopMatrix();

		//
		modelStack.PushMatrix();
		modelStack.Translate(1.7, 0, 1.7);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENCABINET], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1.7, 0, 1.3);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENCABINET], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1.7, 0, 0.9);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENCABINET], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1.7, 0, 0.5);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_KITCHENCABINET], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	// ceiling
	modelStack.PushMatrix();
	modelStack.Translate(0, 17, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(200, 1, 200);
	RenderMesh(meshList[GEO_CUBE], true);
	modelStack.PopMatrix();
	
	//entities
	for (int i = 0; i < entities.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(entities[i]->getPosition().x, entities[i]->getPosition().y, entities[i]->getPosition().z);
		modelStack.Rotate(entities[i]->getLookDirection(), 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		if (entities[i]->getRender() == true)
		{
			RenderMesh(meshList[i], true);
		}
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(500, 500, 500);
	RenderMesh(meshList[GEO_GROUND], true);
	modelStack.PopMatrix();


	if (renderBox == true)
	{
		if (!boxFull)
		{
			modelStack.PushMatrix();
			modelStack.Translate(34.6, 0.01, 87.4);
			modelStack.Rotate(0, 1, 0, 0);
			modelStack.Scale(15, 15, 15);
			RenderMesh(meshList[GEO_BOXOPEN], true);
			modelStack.PopMatrix();
		}
		else
		{
			modelStack.PushMatrix();
			modelStack.Translate(34.6, 0.01, 87.4);
			modelStack.Rotate(0, 1, 0, 0);
			modelStack.Scale(15, 15, 15);
			RenderMesh(meshList[GEO_BOXCLOSED], true);
			modelStack.PopMatrix();
		}
	}
	
	modelStack.PushMatrix();
	modelStack.Translate(0, 10, 0);
	modelStack.Scale(3, 3, 3);
	RenderText(meshList[GEO_TEXT], " ", Color(1, 0, 0));
	modelStack.PopMatrix();

	RenderMeshOnScreen(meshList[GEO_CROSSHAIR], 40, 30, 3, 3);

	std::ostringstream ss;
	ss.str("");
	ss.precision(4);
	ss << "FPS: " << FPS;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 57);

	std::ostringstream Xcoords;
	Xcoords.str("");
	Xcoords.precision(3);
	Xcoords << "X : " << camera.position.x;
	RenderTextOnScreen(meshList[GEO_TEXT], Xcoords.str(), Color(0, 1, 0), 2, 0, 54);

	std::ostringstream Zcoords;
	Zcoords.str("");
	Zcoords.precision(3);
	Zcoords << "Z : " << camera.position.z;
	RenderTextOnScreen(meshList[GEO_TEXT], Zcoords.str(), Color(0, 1, 0), 2, 0, 52);

	if (incomingCall == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Current objective: Answer the call", Color(1, 0, 0), 5, 15, 55);
		modelStack.PushMatrix();
		modelStack.Translate(22.17, 7.24, 66.55);
		modelStack.Rotate(-9, 1, 0, 0);
		modelStack.Scale(4.85, 3.2, 1);
		RenderMesh(meshList[GEO_CALL], false);
		modelStack.PopMatrix();

	}

	if (canInteractPC == true && incomingCall == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press [E] to recieve call", Color(0, 1, 0), 5, 25, 5);
	}
	if (gameStart == true)
	{
		if (canUnload == true)
		{
			if (inventory.size() > 0)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press [E] to pack suitcase", Color(0, 1, 0), 5, 25, 5);
			}
			else
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Your hands are empty!", Color(0, 1, 0), 5, 25, 5);
			}
		}
	}
	
	if (canPickBox == true && renderBox == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press [E] to pick up box", Color(0, 1, 0), 5, 25, 5);
	}
	if (atDoor == true && renderBox == false)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press [E] to exit and escape", Color(0, 1, 0), 5, 25, 5);
	}
	if (canPickup == true)
	{		
		RenderTextOnScreen(meshList[GEO_TEXT], "Press [E] to pick up object", Color(0, 1, 0), 5, 25, 5);	
	}
	if (inventory.size() >= 3)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Inventory Full", Color(0, 1, 0), 5, 35, 10);
	}
	

	if (playDialogue == true)
	{
		RenderMeshOnScreen(meshList[GEO_DIALOGUE], 30, 1, 100, 20);
		RenderTextOnScreen(meshList[GEO_TEXT], BossDialogue[index], Color(1, 1, 1), 4, 5, 5);
	}
	std::ostringstream InvenSize;
	InvenSize.str("");
	InvenSize.precision(2);
	InvenSize << "Inventory " << inventory.size() << "/3";
	if (gameStart == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Current objective: Find all the objects", Color(1, 0, 0), 4, 15, 55);
		RenderTextOnScreen(meshList[GEO_TEXT], InvenSize.str() , Color(1, 1, 1), 4, 5, 5);
	}
	std::ostringstream SuitcaseSize;
	SuitcaseSize.str("");
	SuitcaseSize.precision(2);
	SuitcaseSize << "Suitcase " << suitcase.size() << " / 10";
	if (gameStart == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], SuitcaseSize.str(), Color(1, 1, 1), 4, 5, 8);
	}
	std::ostringstream TotalScore;
	TotalScore.str("");
	TotalScore.precision(4);
	TotalScore << "Score: " << totalScore;
	if (gameStart == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], TotalScore.str(), Color(1, 1, 1), 4, 65, 55);
	}
	std::ostringstream Timeleft;
	Timeleft.str("");
	Timeleft.precision(4);
	Timeleft << "Time: " << timeRemaining << "s";
	if (gameStart == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], Timeleft.str(), Color(1, 1, 1), 4, 65, 50);
	}

	if (lose == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "You Lose", Color(1, 0, 0), 4, 15, 55);
	}
	std::ostringstream TimeTaken;
	TimeTaken.precision(4);
	TimeTaken << "Time Taken: " << 60 - timeRemaining << "s";
	if (win == true)
	{
		RenderMeshOnScreen(meshList[GEO_DIALOGUE], 30, 40, 100, 100);
		RenderTextOnScreen(meshList[GEO_TEXT], "You have escaped!", Color(1, 1, 1), 5, 25, 45);
		RenderTextOnScreen(meshList[GEO_TEXT], TimeTaken.str(), Color(1, 1, 1), 5, 25, 35);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press [Return] to continue...", Color(0.5, 0.5, 0.5), 5, 25, 25);
	}
}

void SceneHouseGame::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; i++)	delete meshList[i];

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneHouseGame::CurrentScene()
{
}

int SceneHouseGame::NextScene()
{
	if (nextScene == true)
	{
		return 8;
	}
	return 0;
}
