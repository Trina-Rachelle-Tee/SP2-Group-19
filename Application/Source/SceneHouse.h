#ifndef SCENE_SCENEHOUSE_H
#define SCENE_SCENEHOUSE_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Hitbox.h"
#include <fstream>
#include <vector>

class SceneHouse : public Scene
{
    enum GEOMETRY_TYPE
    {
        //entities
        GEO_PASSPORT,
        GEO_DOCUMENTS,
        GEO_MONEY,
        GEO_CLOTHES,
        GEO_HARDDRIVE,
        GEO_WALLET,
        GEO_PHONE,
        GEO_EVIDENCE1,
        GEO_EVIDENCE2,
        GEO_MEDS,

        //obj
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
        GEO_LOWF,
        GEO_TEXT,
        GEO_DIALOGUE,
        GEO_SUITCASE,
        GEO_CROSSHAIR,
        GEO_DOOR,

        GEO_WALL,
        GEO_DOORWAY,
        GEO_FLOOR,
        GEO_BED,
        GEO_BOXCLOSED,
        GEO_BOXOPEN,

        GEO_PC,
        GEO_KB,
        GEO_MOUSE,
        GEO_CORNERDESK,
        GEO_DESK,
        GEO_PCCHAIR,

        GEO_SPEAKER,
        GEO_TV,
        GEO_COUCH,
        GEO_LONGCOUCH,
        GEO_TOILET,
        GEO_BATHTUB,
        GEO_SINK,
        GEO_MIRROR,
        GEO_FRIDGE,
        GEO_KITCHENUPPER,
        GEO_KITCHENSINK,
        GEO_KITCHENCABINET,
        GEO_KITCHENSTOVE,
        GEO_TABLE,
        GEO_CHAIR,
        GEO_BEDSIDE,

        GEO_COFFEETABLE,
        GEO_TVTABLE,
        GEO_HOUSE,

        GEO_CALL,


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

        U_LIGHT4_POSITION,
        U_LIGHT4_COLOR,
        U_LIGHT4_POWER,
        U_LIGHT4_KC,
        U_LIGHT4_KL,
        U_LIGHT4_KQ,
        U_LIGHT4_TYPE,
        U_LIGHT4_SPOTDIRECTION,
        U_LIGHT4_COSCUTOFF,
        U_LIGHT4_COSINNER,
        U_LIGHT4_EXPONENT,

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

    std::string printing;
    float index;
    int stage;
    bool incomingCall;
    bool canInteractPC;
    bool canPickup;
    bool playDialogue;
    bool atDoor;
    bool canLeave;
    bool nextScene;
    bool startMini1;
    bool startMini2;
    
    std::vector<std::string> BossDialogue;

    float cx, cy, cz;
    Vector3 view;
    Vector3 right;
    

    Mesh* meshList[NUM_GEOMETRY];
    Light light[5];
    std::ifstream fileStream;
    unsigned textMaxWidth;
    unsigned textSpacing[256];

    std::vector<Hitbox> hitbox;
    void InitHitbox();
    void pcInteract();
    void StartMini1();
    void StartMini2();
    void RenderSkybox();
    void RenderMesh(Mesh* mesh, bool enableLight);
    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);

    void getBossDialogue();

public:
    SceneHouse();
    ~SceneHouse();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
    virtual void CurrentScene();
    virtual int NextScene();
};
#endif