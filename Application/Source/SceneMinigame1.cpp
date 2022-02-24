#include "SceneMinigame1.h"
#include "GL\glew.h"
#include <GLFW/glfw3.h>
#include "Mtx44.h"
#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"
#include <fstream>
#include <sstream>


SceneMinigame1::SceneMinigame1()
{
	timing = 0.0;
}

SceneMinigame1::~SceneMinigame1()
{
}

void SceneMinigame1::InitHitbox()
{
	//Hitboxes, pos xyz, scale xyz
	//invisable wall
	hitbox.push_back(Hitbox(25.f, 0.f, 100.f, 1.f, 20.f, 50.f));
	hitbox.push_back(Hitbox(-25.f, 0.f, 100.f, 1.f, 20.f, 50.f));
	hitbox.push_back(Hitbox(0.f, 0.f, 125.f, 50.f, 20.f, 1.f));
	hitbox.push_back(Hitbox(0.f, 0.f, 75.f, 50.f, 20.f, 1.f));
}



void SceneMinigame1::Init()
{
	// Init VBO here
	InitHitbox();

	pickup = false;

	start = clock();

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

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 30, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
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

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);


	camera.Init(Vector3(-10.2, 9.5, 100.07), Vector3(0, 9.5, -0.07), Vector3(0, 1, 0));

	for (int i = 0; i < NUM_GEOMETRY; i++)	meshList[i] = nullptr;

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//R(6).tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//R(6).tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//R(6).tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//R(6).tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//R(6).tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//R(6).tga");

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

	meshList[GEO_ADS1] = MeshBuilder::GenerateQuad("ADS", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_ADS1]->textureID = LoadTGA("Image//th.tga");

	meshList[GEO_ADS2] = MeshBuilder::GenerateQuad("ADS", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_ADS2]->textureID = LoadTGA("Image//th_1.tga");

	meshList[GEO_ADS3] = MeshBuilder::GenerateQuad("ADS", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_ADS3]->textureID = LoadTGA("Image//th_2.tga");

	meshList[GEO_ADS4] = MeshBuilder::GenerateQuad("ADS", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_ADS4]->textureID = LoadTGA("Image//th_4.tga");

	meshList[GEO_ADS5] = MeshBuilder::GenerateQuad("ADS", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_ADS5]->textureID = LoadTGA("Image//th_5.tga");

	meshList[GEO_WEBSITE] = MeshBuilder::GenerateQuad("Website", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_WEBSITE]->textureID = LoadTGA("Image//website.tga");

	meshList[GEO_GROUND] = MeshBuilder::GenerateFloor("floor", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//R(6).tga");



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

void SceneMinigame1::Update(double dt)
{
	camera.Update(dt, hitbox);
	FPS = 1 / (float)dt;
	view = (camera.target - camera.position).Normalized();

	if (pause == false)
	{
		timing = (float)((double)clock() - start) / (double)CLOCKS_PER_SEC;
	}

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

	if (Application::IsKeyPressed('Q'))
	{
		gamestart = true;
		start = clock();
	}

	if (gamestart == true)
	{
		translateX += (float)(50 * dt);



		if (translateX >= 59)
		{
			leftbounce = true;
			rightbounce = false;
			hitplayer = false;
			hitenemydown = false;
			hitenemytop = false;
			hitenemyleft = false;
			hitenemyright = false;
		}

		if (translateX <= -59)
		{
			leftbounce = false;
			rightbounce = true;
			hitplayer = false;
			hitenemydown = false;
			hitenemytop = false;
			hitenemyleft = false;
			hitenemyright = false;
		}

		if (leftbounce == true)
		{
			translateX -= (float)(100 * dt);
		}

		translateY += (float)(50 * dt);
		if (translateY >= 39)
		{
			topbounce = true;
			lowerbounce = false;
			hitplayer = false;
			hitenemydown = false;
			hitenemytop = false;
			hitenemyleft = false;
			hitenemyright = false;
		}

		if (topbounce == true)
		{
			translateY -= (float)(100 * dt);
		}

		if (translateY <= -35)
		{
			if (gamewon == true)
			{
				gamelost = false;
				topbounce = false;
				lowerbounce = true;
				hitplayer = false;
				hitenemydown = false;
				hitenemytop = false;
				hitenemyleft = false;
				hitenemyright = false;
			}
			else
			{
				gamelost = true;
				topbounce = false;
				lowerbounce = true;
				hitplayer = false;
				hitenemydown = false;
				hitenemytop = false;
				hitenemyleft = false;
				hitenemyright = false;
				pause = true;
			}
		}

		if (Application::IsKeyPressed(VK_LEFT))
		{
			PlayerX -= (float)(50 * dt);
			if ((PlayerX - 15) <= -60)
			{
				PlayerX += (float)(50 * dt);
			}
		}

		if (Application::IsKeyPressed(VK_RIGHT))
		{
			PlayerX += (float)(50 * dt);
			if ((PlayerX + 15) >= 60)
			{
				PlayerX -= (float)(50 * dt);
			}
		}

		if ((translateX <= PlayerX + 15 and translateX >= PlayerX and translateY <= -25) or (translateX >= PlayerX - 15 and translateX <= PlayerX and translateY <= -25))
		{
			hitplayer = true;
			hitenemydown = false;
			hitenemytop = false;
			hitenemyleft = false;
			hitenemyright = false;
		}

		if (gamewon == false and timing >= 10)
		{
			gamelost = true;
			pause = true;
		}

		if (gamelost == false)
		{
			if (enemy1 == true)
			{
				//AD 1 hitbox
				if (translateX <= AD1X + 13.5 and translateX >= AD1X and translateY >= AD1Y - 20 and translateY <= AD1Y)
				{
					hitenemydown = true;
					enemy1 = false;
				}

				if (translateX >= AD1X - 13.5 and translateX <= AD1X and translateY >= AD1Y - 20 and translateY <= AD1Y)
				{
					hitenemydown = true;
					enemy1 = false;
				}

				if (translateX <= AD1X + 13.5 and translateX >= AD1X and translateY <= AD1Y + 20 and translateY >= AD1Y)
				{
					hitenemytop = true;
					enemy1 = false;
				}

				if (translateX >= AD1X - 13.5 and translateX <= AD1X and translateY <= AD1Y + 20 and translateY >= AD1Y)
				{
					hitenemytop = true;
					enemy1 = false;
				}

				if (translateY <= AD1Y + 18.5 and translateY >= AD1Y and translateX >= AD1X - 15 and translateX <= AD1X)
				{
					hitenemyleft = true;
					enemy1 = false;
				}

				if (translateY >= AD1Y - 18.5 and translateY <= AD1Y and translateX >= AD1X - 15 and translateX <= AD1X)
				{
					hitenemyleft = true;
					enemy1 = false;
				}

				if (translateY <= AD1Y + 18.5 and translateY >= AD1Y and translateX <= AD1X + 15 and translateX >= AD1X)
				{
					hitenemyright = true;
					enemy1 = false;
				}

				if (translateY >= AD1Y - 18.5 and translateY <= AD1Y and translateX <= AD1X + 15 and translateX >= AD1X)
				{
					hitenemyright = true;
					enemy1 = false;
				}
			}

			if (enemy2 == true)
			{
				//AD 2 hitbox
				if (translateX <= AD2X + 5 and translateX >= AD2X and translateY >= AD2Y - 15 and translateY <= AD2Y)
				{
					hitenemydown = true;
					enemy2 = false;
				}

				if (translateX >= AD2X - 5 and translateX <= AD2X and translateY >= AD2Y - 15 and translateY <= AD2Y)
				{
					hitenemydown = true;
					enemy2 = false;
				}

				if (translateX <= AD2X + 5 and translateX >= AD2X and translateY <= AD2Y + 15 and translateY >= AD2Y)
				{
					hitenemytop = true;
					enemy2 = false;
				}

				if (translateX >= AD2X - 5 and translateX <= AD2X and translateY <= AD2Y + 15 and translateY >= AD2Y)
				{
					hitenemytop = true;
					enemy2 = false;
				}

				if (translateY <= AD2Y + 13.5 and translateY >= AD2Y and translateX >= AD2X - 7.5 and translateX <= AD2X)
				{
					hitenemyleft = true;
					enemy2 = false;
				}

				if (translateY >= AD2Y - 13.5 and translateY <= AD2Y and translateX >= AD2X - 7.5 and translateX <= AD2X)
				{
					hitenemyleft = true;
					enemy2 = false;
				}

				if (translateY <= AD2Y + 13.5 and translateY >= AD2Y and translateX <= AD2X + 7.5 and translateX >= AD2X)
				{
					hitenemyright = true;
					enemy2 = false;
				}

				if (translateY >= AD2Y - 13.5 and translateY <= AD2Y and translateX <= AD2X + 7.5 and translateX >= AD2X)
				{
					hitenemyright = true;
					enemy2 = false;
				}
			}
			if (enemy3 == true)
			{
				//AD 3 hitbox
				if (translateX <= AD3X + 8.5 and translateX >= AD3X and translateY >= AD3Y - 10 and translateY <= AD3Y)
				{
					hitenemydown = true;
					enemy3 = false;
				}

				if (translateX >= AD3X - 8.5 and translateX <= AD3X and translateY >= AD3Y - 10 and translateY <= AD3Y)
				{
					hitenemydown = true;
					enemy3 = false;
				}

				if (translateX <= AD3X + 8.5 and translateX >= AD3X and translateY <= AD3Y + 10 and translateY >= AD3Y)
				{
					hitenemytop = true;
					enemy3 = false;
				}

				if (translateX >= AD3X - 8.5 and translateX <= AD3X and translateY <= AD3Y + 10 and translateY >= AD3Y)
				{
					hitenemytop = true;
					enemy3 = false;
				}

				if (translateY <= AD3Y + 8.5 and translateY >= AD3Y and translateX >= AD3X - 10 and translateX <= AD3X)
				{
					hitenemyleft = true;
					enemy3 = false;
				}

				if (translateY >= AD3Y - 8.5 and translateY <= AD3Y and translateX >= AD3X - 10 and translateX <= AD3X)
				{
					hitenemyleft = true;
					enemy3 = false;
				}

				if (translateY <= AD3Y + 8.5 and translateY >= AD3Y and translateX <= AD3X + 10 and translateX >= AD3X)
				{
					hitenemyright = true;
					enemy3 = false;
				}

				if (translateY >= AD3Y - 8.5 and translateY <= AD3Y and translateX <= AD3X + 10 and translateX >= AD3X)
				{
					hitenemyright = true;
					enemy3 = false;
				}
			}

			if (enemy4 == true)
			{
				//AD 4 hitbox
				if (translateX <= AD4X + 8.5 and translateX >= AD4X and translateY >= AD4Y - 10 and translateY <= AD4Y)
				{
					hitenemydown = true;
					enemy4 = false;
				}

				if (translateX >= AD4X - 8.5 and translateX <= AD4X and translateY >= AD4Y - 10 and translateY <= AD4Y)
				{
					hitenemydown = true;
					enemy4 = false;
				}

				if (translateX <= AD4X + 8.5 and translateX >= AD4X and translateY <= AD4Y + 10 and translateY >= AD4Y)
				{
					hitenemytop = true;
					enemy4 = false;
				}

				if (translateX >= AD4X - 8.5 and translateX <= AD4X and translateY <= AD4Y + 10 and translateY >= AD4Y)
				{
					hitenemytop = true;
					enemy4 = false;
				}

				if (translateY <= AD4Y + 8.5 and translateY >= AD4Y and translateX >= AD4X - 10 and translateX <= AD4X)
				{
					hitenemyleft = true;
					enemy4 = false;
				}

				if (translateY >= AD4Y - 8.5 and translateY <= AD4Y and translateX >= AD4X - 10 and translateX <= AD4X)
				{
					hitenemyleft = true;
					enemy4 = false;
				}

				if (translateY <= AD4Y + 8.5 and translateY >= AD4Y and translateX <= AD4X + 10 and translateX >= AD4X)
				{
					hitenemyright = true;
					enemy4 = false;
				}

				if (translateY >= AD4Y - 8.5 and translateY <= AD4Y and translateX <= AD4X + 10 and translateX >= AD4X)
				{
					hitenemyright = true;
					enemy4 = false;
				}
			}
			if (enemy5 == true)
			{
				//AD 5 hitbox
				if (translateX <= AD5X + 8.5 and translateX >= AD5X and translateY >= AD5Y - 10 and translateY <= AD5Y)
				{
					hitenemydown = true;
					enemy5 = false;
				}

				if (translateX >= AD5X - 8.5 and translateX <= AD5X and translateY >= AD5Y - 10 and translateY <= AD5Y)
				{
					hitenemydown = true;
					enemy5 = false;
				}

				if (translateX <= AD5X + 8.5 and translateX >= AD5X and translateY <= AD5Y + 10 and translateY >= AD5Y)
				{
					hitenemytop = true;
					enemy5 = false;
				}

				if (translateX >= AD5X - 8.5 and translateX <= AD5X and translateY <= AD5Y + 10 and translateY >= AD5Y)
				{
					hitenemytop = true;
					enemy5 = false;
				}

				if (translateY <= AD5Y + 8.5 and translateY >= AD5Y and translateX >= AD5X - 10 and translateX <= AD5X)
				{
					hitenemyleft = true;
					enemy5 = false;
				}

				if (translateY >= AD5Y - 8.5 and translateY <= AD5Y and translateX >= AD5X - 10 and translateX <= AD5X)
				{
					hitenemyleft = true;
					enemy5 = false;
				}

				if (translateY <= AD5Y + 8.5 and translateY >= AD5Y and translateX <= AD5X + 10 and translateX >= AD5X)
				{
					hitenemyright = true;
					enemy5 = false;
				}

				if (translateY >= AD5Y - 8.5 and translateY <= AD5Y and translateX <= AD5X + 10 and translateX >= AD5X)
				{
					hitenemyright = true;
					enemy5 = false;
				}
			}
		}
		if (hitplayer == true)
		{
			topbounce = false;
			lowerbounce = true;
		}

		if (hitenemydown == true)
		{
			topbounce = true;
			lowerbounce = false;
		}

		if (hitenemytop == true)
		{
			topbounce = false;
			lowerbounce = true;
		}

		if (hitenemyright == true)
		{
			leftbounce = false;
			rightbounce = true;
		}

		if (hitenemyleft == true)
		{
			leftbounce = true;
			rightbounce = false;
		}

		if (enemy1 == false and enemy2 == false and enemy3 == false and enemy4 == false and enemy5 == false)
		{
			gamewon = true;
			pause = true;
		}
	}

}
void SceneMinigame1::RenderSkybox() {
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
void SceneMinigame1::RenderMesh(Mesh* mesh, bool enableLight)
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
void SceneMinigame1::RenderText(Mesh* mesh, std::string text, Color color)
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
void SceneMinigame1::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void SceneMinigame1::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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





void SceneMinigame1::Render()
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
	if (gamestart == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-40, 42, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "Controls", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-40, 38, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "W - Move forward", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-40, 34, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "A - Move Right", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-40, 30, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "S - Move backwards", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-40, 26, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "D - Move Left", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-40, 22, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "Right arrow keys - move the brick right", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-40, 18, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "Left arrow keys - move the brick left", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-40, 14, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "Q - start the game", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-40, 10, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "Your computer is full of ads after researching on Melon and it's overheating your CPU", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-40, 6, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "Complete a game of brick breaker to clear the ads and", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-40, 2, 40);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], "stop your computer from overheating before its too late!", Color(1, 0, 0));
		modelStack.PopMatrix();
	}

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



	// player paddle
	if (gamestart == false)
	{
	}

	if (gamestart == true)
	{

		std::ostringstream words;
		words.str("");
		words << "time : " << 10 - (int)timing;
		RenderTextOnScreen(meshList[GEO_TEXT], words.str(), Color(0, 0, 0), 5, 3, 50);

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -50);
		modelStack.Scale(120, 80, 1);
		RenderMesh(meshList[GEO_WEBSITE], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(PlayerX, -30, -49);
		modelStack.Scale(30, 5, 1);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
	}

	if (gamestart == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(translateX, translateY, -49);
		modelStack.Scale(5, 5, 1);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();

		if (enemy1 == true)
		{
			// tampon bullet hole ad
			AD1X = 20;
			AD1Y = 10;
			modelStack.PushMatrix();
			modelStack.Translate(AD1X, AD1Y, -49);
			modelStack.Scale(30, 40, 10);
			RenderMesh(meshList[GEO_ADS1], false);
			modelStack.PopMatrix();
		}


		if (enemy2 == true)
		{
			AD2X = -20;
			AD2Y = 25;
			//lawyer ad
			modelStack.PushMatrix();
			modelStack.Translate(-20, 25, -49);
			modelStack.Scale(15, 30, 10);
			RenderMesh(meshList[GEO_ADS2], false);
			modelStack.PopMatrix();
		}

		if (enemy3 == true)
		{
			AD3X = -20;
			AD3Y = 5;
			//wrinkle ad
			modelStack.PushMatrix();
			modelStack.Translate(AD3X, AD3Y, -49);
			modelStack.Scale(20, 20, 10);
			RenderMesh(meshList[GEO_ADS3], false);
			modelStack.PopMatrix();
		}

		if (enemy4 == true)
		{
			AD4X = -40;
			AD4Y = 30;
			//pringle ad
			modelStack.PushMatrix();
			modelStack.Translate(AD4X, AD4Y, -49);
			modelStack.Scale(20, 20, 10);
			RenderMesh(meshList[GEO_ADS4], false);
			modelStack.PopMatrix();
		}

		if (enemy5 == true)
		{
			AD5X = 30;
			AD5Y = -15;
			//toyota car
			modelStack.PushMatrix();
			modelStack.Translate(AD5X, AD5Y, -49);
			modelStack.Scale(20, 20, 10);
			RenderMesh(meshList[GEO_ADS5], false);
			modelStack.PopMatrix();
		}
	}

	if (gamelost == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(translateX, translateY, -49);
		modelStack.Scale(5, 5, 1);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();

		RenderTextOnScreen(meshList[GEO_TEXT], "Game over", Color(1, 1, 0), 10, 25, 25);
	}

	if (gamewon == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(translateX, translateY, -49);
		modelStack.Scale(5, 5, 1);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();

		RenderTextOnScreen(meshList[GEO_TEXT], "You Win!", Color(1, 1, 0), 10, 25, 25);
	}

	RenderMeshOnScreen(meshList[GEO_QUAD], 40, 30, 20, 10);

	std::ostringstream ss;
	ss.str("");
	ss.precision(4);
	ss << "FPS: " << FPS;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 4, 0, 0);


}

void SceneMinigame1::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; i++)	delete meshList[i];
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneMinigame1::CurrentScene()
{
}

int SceneMinigame1::NextScene()
{
	return 0;
}
