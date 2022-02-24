#ifndef SCENE_SceneMinigame1_H
#define SCENE_SceneMinigame1_H

#include "Scene.h"
#include "SceneInvestigation.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include <fstream>
#include <vector>


class SceneMinigame1 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_QUAD,
        GEO_CUBE,
        GEO_CIRCLE,
        GEO_RING,
        GEO_SPHERE,
        GEO_HEMISPHERE,
        GEO_CYLINDER,
        GEO_CONE,
        GEO_TORUS,
        GEO_LIGHTBALL,
        GEO_LEFT,
        GEO_RIGHT,
        GEO_TOP,
        GEO_BOTTOM,
        GEO_FRONT,
        GEO_BACK,
        GEO_BLEND,
        GEO_GROUND,
        GEO_TEXT,
        GEO_ADS1,
        GEO_ADS2,
        GEO_ADS3,
        GEO_ADS4,
        GEO_ADS5,
        GEO_WEBSITE,
        NUM_GEOMETRY,
    };
    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_MODELVIEW,
        U_MODELVIEW_INVERSE_TRANSPOSE,
        U_MATERIAL_AMBIENT,
        U_MATERIAL_DIFFUSE,
        U_MATERIAL_SPECULAR,
        U_MATERIAL_SHININESS,
        U_LIGHTENABLED,
        U_LIGHT0_POSITION,
        U_LIGHT0_COLOR,
        U_LIGHT0_POWER,
        U_LIGHT0_KC,
        U_LIGHT0_KL,
        U_LIGHT0_KQ,
        U_LIGHT0_TYPE,
        U_LIGHT0_SPOTDIRECTION,
        U_LIGHT0_COSCUTOFF,
        U_LIGHT0_COSINNER,
        U_LIGHT0_EXPONENT,
        U_LIGHT1_POSITION,
        U_LIGHT1_COLOR,
        U_LIGHT1_POWER,
        U_LIGHT1_KC,
        U_LIGHT1_KL,
        U_LIGHT1_KQ,
        U_LIGHT1_TYPE,
        U_LIGHT1_SPOTDIRECTION,
        U_LIGHT1_COSCUTOFF,
        U_LIGHT1_COSINNER,
        U_LIGHT1_EXPONENT,
        U_LIGHT2_POSITION,
        U_LIGHT2_COLOR,
        U_LIGHT2_POWER,
        U_LIGHT2_KC,
        U_LIGHT2_KL,
        U_LIGHT2_KQ,
        U_LIGHT2_TYPE,
        U_LIGHT2_SPOTDIRECTION,
        U_LIGHT2_COSCUTOFF,
        U_LIGHT2_COSINNER,
        U_LIGHT2_EXPONENT,
        U_LIGHT3_POSITION,
        U_LIGHT3_COLOR,
        U_LIGHT3_POWER,
        U_LIGHT3_KC,
        U_LIGHT3_KL,
        U_LIGHT3_KQ,
        U_LIGHT3_TYPE,
        U_LIGHT3_SPOTDIRECTION,
        U_LIGHT3_COSCUTOFF,
        U_LIGHT3_COSINNER,
        U_LIGHT3_EXPONENT,
        U_NUMLIGHTS,
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,
        U_TOTAL,
    };
    MS modelStack, viewStack, projectionStack;
    Camera3 camera;
private:
    unsigned m_vertexArrayID;
    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];
    clock_t start = clock();
    float FPS;
    float timing;
    bool bLightEnabled;
    bool pickup;
    bool pause = false;
    bool gamestart = false;
    bool gamewon = false;
    bool gamelost = false;
    float translateX = 0;
    float PlayerX = 0;
    float translateY = -23;
    float AD1X;
    float AD1Y;
    float AD2X;
    float AD2Y;
    float AD3X;
    float AD3Y;
    float AD4X;
    float AD4Y;
    float AD5X;
    float AD5Y;
    bool enemy1 = true;
    bool enemy2 = true;
    bool enemy3 = true;
    bool enemy4 = true;
    bool enemy5 = true;
    bool leftbounce = false;
    bool rightbounce = false;
    bool topbounce = false;
    bool lowerbounce = false;
    bool hitplayer = false;
    bool hitenemyleft = false;
    bool hitenemyright = false;
    bool hitenemytop = false;
    bool hitenemydown = false;
    bool pickup1;
    bool switcher;
    bool nextScene;
    float cx, cy, cz;
    Vector3 view;
    Vector3 right;


    Mesh* meshList[NUM_GEOMETRY];
    Light light[4];
    std::ifstream fileStream;
    unsigned textMaxWidth;
    unsigned textSpacing[256];

    std::vector<Hitbox> hitbox;


    void InitHitbox();




    void RenderSkybox();
    void RenderMesh(Mesh* mesh, bool enableLight);
    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);



public:
    SceneMinigame1();
    ~SceneMinigame1();


    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
    virtual void CurrentScene();
    virtual int NextScene();
};
#endif