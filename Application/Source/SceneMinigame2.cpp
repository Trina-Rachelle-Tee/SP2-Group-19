#include "SceneMinigame2.h"
#include "GL\glew.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include "Mtx44.h"
#include "shader.hpp"
#include "Application.h";
#include "MeshBuilder.h";
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"


SceneMinigame2::SceneMinigame2()
{
	
}

SceneMinigame2::~SceneMinigame2()
{
}

void SceneMinigame2::Init()
{
	start = clock();
	timing = 0.0;
	basketLength = 3.5;
	heartLength = 2.5;
	coolDown = heartScore = gameStage = basketCoord.x = basketCoord.y = 0.0;
	basketCoord.z = -30;
	nextScene = false;

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

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	glUseProgram(m_programID);
	glUniform1i(m_parameters[U_NUMLIGHTS], 4);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 0, 10);
	light[0].color.Set(1, 1, 1);
	light[0].power = (float) 1.2;
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


	camera.Init(Vector3(0, 0, 5), Vector3(0, 0,-5), Vector3(0, 1, 0));

	for (int i = 0; i < NUM_GEOMETRY; i++)	meshList[i] = nullptr;

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//R(6).tga");

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//DimboFont.tga");

	meshList[GEO_HEART] = MeshBuilder::GenerateOBJ("building 1", "OBJ//heart.obj");
	meshList[GEO_HEART]->textureID = LoadTGA("Image//heart.tga");

	meshList[GEO_INTRO] = MeshBuilder::GenerateQuad("Post", (1, 1, 1),10, 10);
	meshList[GEO_INTRO]->textureID = LoadTGA("Image//minigame_2_intro.tga");

	meshList[GEO_RESULTS] = MeshBuilder::GenerateQuad("Post", (1, 1, 1), 10, 10);
	meshList[GEO_RESULTS]->textureID = LoadTGA("Image//minigame_2_results.tga");

	meshList[GEO_BASKET] = MeshBuilder::GenerateOBJ("basket", "OBJ//basket.obj");
	meshList[GEO_BASKET]->textureID = LoadTGA("Image//basket colour.tga");



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

void SceneMinigame2::Update(double dt)
{
	FPS = 1 / (float)dt;
	view = (camera.target - camera.position).Normalized();

	timing = (float)((double)clock() - start) / (double)CLOCKS_PER_SEC;

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
}

bool SceneMinigame2::touch(float alength, float blength, float ax, float ay, float bx, float by)
{
	float aRight, aLeft, aTop, aBottom, bRight, bLeft, bTop, bBottom;
	aRight = ax + (alength / 2);
	aLeft = ax - (alength / 2);
	bRight = bx + (blength / 2);
	bLeft = bx - (blength / 2);

	aTop = ay;
	aBottom = ay - 3.5;
	bTop = ay + 2.5;
	bBottom = by;
	if (((bLeft < aLeft) && (aLeft < bRight)) ||((bLeft< aRight) && (aRight < bRight)))//cheecks if x values intersect
	{
		if (((aBottom < bTop) && (bTop < aTop)) || ((aBottom < bBottom) && (bBottom < aTop)))//checks if y values intersect
		{
			return true;
		}
	}
	return false;
}

void SceneMinigame2::RenderIntro()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -0.05, 0);
	modelStack.Scale(5.5, 4.3, 5);
	RenderMesh(meshList[GEO_INTRO], false);
	modelStack.PopMatrix();
	if (Application::IsKeyPressed('E'))
	{
		gameStage = 1;
		start = clock();
	}
}

void SceneMinigame2::RenderResults()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -0.05, 0);
	modelStack.Scale(5.5, 4.3, 5);
	RenderMesh(meshList[GEO_RESULTS], false);
	modelStack.PopMatrix();
	std::ostringstream words;
	words << heartScore << "/300 likes";
	RenderTextOnScreen(meshList[GEO_TEXT], words.str(), Color(1, 1, 1), 6, 31, 22);
	words.str("");
	if (heartScore >= 300)
	{
		words << "Success! Press [RETURN] to proceed";
		RenderTextOnScreen(meshList[GEO_TEXT], words.str(), Color(1, 1, 1), 5, 15, 10);

		if (Application::IsKeyPressed(VK_RETURN))
		{
			nextScene = true;
		}
	}
	else
	{
		words << "Fail. Press E to replay";
		RenderTextOnScreen(meshList[GEO_TEXT], words.str(), Color(1, 1, 1), 7, 20, 10);
		if (Application::IsKeyPressed('E'))
		{
			heartScore = 0;
			gameStage = 1;
			start = clock();
		}
	}

	
}
void SceneMinigame2::RenderSkybox() {
	const float OFFSET = 499;
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -OFFSET);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

}

void SceneMinigame2::RenderHearts()
{
	coolDown += 1;
	if (coolDown > 30)//new heart is rendered
	{
		float randX = rand() % 30 + (-15);
		heartCoord.push_back(Position(randX, 25, -30));
		coolDown = 0;
	}

	if (gameStage == 1 && timing >= 30)//checks if its time for the minigame to end
	{
		gameStage = 2;
		heartCoord.clear();
	}
	else//if not, the hearts are rendered
	{

		int x = 0;
		for (auto i = heartCoord.begin(); i != heartCoord.end(); i++, x++)//loops it so all hearts are rendered
		{
			if (i->y < -17)
			{
				i = heartCoord.erase(i);
				modelStack.PushMatrix();
				modelStack.Translate(i->x, i->y, i->z);
				modelStack.Rotate(-90, 90, 0, 0);
				modelStack.Scale(0.1, 0.1, 0.1);
				RenderMesh(meshList[GEO_HEART], false);
				modelStack.PopMatrix();
				i->y -= (float)0.2;//lowers heart position
			}
			else
			{
				modelStack.PushMatrix();
				modelStack.Translate(i->x, i->y, i->z);
				modelStack.Rotate(-90, 90, 0, 0);
				modelStack.Scale(0.1, 0.1, 0.1);
				RenderMesh(meshList[GEO_HEART], false);
				modelStack.PopMatrix();
				i->y -= (float)0.2;//lowers heart position
			}
		}
	}
}
void SceneMinigame2::RenderBasketCatch()
{
	if (Application::IsKeyPressed('A') && basketCoord.x > -16)
	{
		basketCoord.x -= (float)0.3;
	}
	if (Application::IsKeyPressed('D') && basketCoord.x < 16)
	{
		basketCoord.x += (float)0.3;
	}
	if (Application::IsKeyPressed('W') && basketCoord.y < 7)
	{
		basketCoord.y += (float)0.3;
	}
	if (Application::IsKeyPressed('S') && basketCoord.y > -14)
	{
		basketCoord.y -= (float)0.3;
	}
	modelStack.PushMatrix();
	modelStack.Translate(basketCoord.x, basketCoord.y, basketCoord.z);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_BASKET], true);
	modelStack.PopMatrix();

	std::ostringstream words;

	words.str("Catch hearts to gain likes!");
	RenderTextOnScreen(meshList[GEO_TEXT], words.str(), Color(1, 0, 0), 5, 20, 55);

	words.str("");
	words << heartScore << " people liked the post";
	RenderTextOnScreen(meshList[GEO_TEXT], words.str(), Color(1, 0, 0), 5, 22, 2);

	words.str("");
	words << "time : " << 30 - (int)timing;
	RenderTextOnScreen(meshList[GEO_TEXT], words.str(), Color(0, 0, 0), 5, 3, 48);

	for (auto i = heartCoord.begin(); i != heartCoord.end(); i++)
	{
		if (touch(basketLength, heartLength, basketCoord.x, basketCoord.y, i->x, i->y) == true)
		{
			heartScore += 10;
			i = heartCoord.erase(i);
		}
	}
}

void SceneMinigame2::RenderMesh(Mesh* mesh, bool enableLight)
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
void SceneMinigame2::RenderText(Mesh* mesh, std::string text, Color color)
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
void SceneMinigame2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void SceneMinigame2::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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





void SceneMinigame2::Render()
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

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	if (gameStage == 0)
	{
		RenderIntro();
	}

	else if (gameStage == 1)
	{

	RenderSkybox();
	RenderBasketCatch();
	RenderHearts();
	}

	else
	{
		RenderResults();
	}


	RenderMeshOnScreen(meshList[GEO_QUAD], 40, 30, 20, 10);

	std::ostringstream ss;
	ss.str("");
	ss.precision(4);
	ss << "FPS: " << FPS;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 4, 0, 0);


}

void SceneMinigame2::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		delete meshList[i];
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneMinigame2::CurrentScene()
{
}

int SceneMinigame2::NextScene()
{
	if (nextScene == true)
	{
		return 2;
	}
	return 0;
}
