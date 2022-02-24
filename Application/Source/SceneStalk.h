#ifndef SCENE_STALK_H
#define SCENE_STALK_H

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
#include "Hitbox.h"


class SceneStalk : public Scene
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
        GEO_GLASS,
        GEO_BPORTAL,
        GEO_OPORTAL,
        GEO_BUTTON,
        GEO_DOOR,
        GEO_WALL,
        GEO_NIGHTSTAND,
        GEO_TOILET,
        GEO_COMCUBE,
        GEO_BED,
        GEO_BENCH,
        GEO_TEXT,
        GEO_PERSON,
        GEO_EXIT,
        GEO_PORTALGUN,
        GEO_RADIO,
        GEO_SINK,
        GEO_LAYOUT,
        GEO_REDOOR,
        GEO_DOOR1,
        GEO_WALLS,
        GEO_WALLWALL,
        GEO_WINDOW,
        GEO_TV,
        GEO_TABLE,
        GEO_SEAT,
        GEO_LAPTOP,
        GEO_BOOKS,
        GEO_MOUSE,
        GEO_DOC,
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

    float FPS;
    bool bLightEnabled;
    bool pickup;
    bool pickup1;
    bool switcher;
    float cx, cy, cz;
    int RenderE1;
    int RenderE2;
    int RenderE3;
    int RenderE4;
    int RenderE5;
    int RenderE6;
    int RenderE7;
    int RenderE8;
    int RenderE9;
    int RenderE10;
    int Echeck1;
    int Echeck2;
    int Echeck3;
    int Echeck4;
    int Echeck5;
    int Echeck6;
    int Echeck7;
    int Echeck8;
    int Echeck9;
    int Echeck10;
    int Qpickup;
    int pushdown;
    int doorlock;
    int dooropen;

    bool nextscene;
    

    Vector3 view;
    Vector3 right;
    Vector3 TempPos;
    Vector3 TempTarget;
    Vector3 TempUp;

    Mesh* meshList[NUM_GEOMETRY];
    Light light[4];
    std::ifstream fileStream;
    unsigned textMaxWidth;
    unsigned textSpacing[256];


    std::vector<Hitbox> hitbox;
    void InitHitboxes();



    void RenderSkybox();
    void RenderMesh(Mesh* mesh, bool enableLight);
    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
    
    

public:
    SceneStalk();
    ~SceneStalk();

    
    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
    virtual void CurrentScene();
    virtual int NextScene();
};
#endif