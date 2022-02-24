#ifndef SCENE_SCENEINVESTIGATION_H
#define SCENE_SCENEINVESTIGATION_H

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

class SceneInvestigation : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_QUAD,
        GEO_CUBE,
        GEO_LIGHTBALL,
        GEO_LEFT,
        GEO_RIGHT,
        GEO_TOP,
        GEO_BOTTOM,
        GEO_FRONT,
        GEO_BACK,
        GEO_GROUND,
        GEO_TEXT,
        GEO_WALLET,
        GEO_POSTER1,
        GEO_POSTER2,
        GEO_NPC1,
        GEO_NPC2,
        GEO_NPC3,
        GEO_NPC4,
        GEO_NPC5,
        GEO_INTRO,
        GEO_RESULTS,
        GEO_DIALOGUE,
        GEO_BUILDING1,
        GEO_BUILDING2,
        GEO_BUILDING3,
        GEO_BUILDING4,
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

    float FPS, touchRefresh;
    bool bLightEnabled, dialogueOn;
    int npcNum, objectNum, timeLimit, score;
    bool infoAttained[5];
    bool win;
    bool nextScene;
    std::string info[5];
    Vector3 view;
    Vector3 right;
    

    Mesh* meshList[NUM_GEOMETRY];
    Light light[2];
    std::ifstream fileStream;
    unsigned textMaxWidth;
    unsigned textSpacing[256];
    //game variables
    int gameStage, dialogueNum;
    std::vector <std::string> NPC1dialogue;
    std::vector <std::string> NPC2dialogue;
    std::vector <std::string> NPC3dialogue;
    std::vector <std::string> NPC4dialogue;
    std::vector <std::string> NPC5dialogue;
    std::vector <std::string> WalletDialogue;
    std::vector <std::string> Poster1Dialogue;
    std::vector <std::string> Poster2Dialogue;
    //for timer
    clock_t start;
    float timing;

    std::vector<Hitbox> hitbox;
    void InitHitbox();

    void RenderSkybox();
    void RenderIntro();
    void RenderCityObjects();
    void RenderMinigameUI();
    void RenderGameEndUI();
    void MinigameInteractions();
    void IntroAndResultInteractions();
    void RenderResults();
    void RenderMesh(Mesh* mesh, bool enableLight);
    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
    
public:
    SceneInvestigation();
    ~SceneInvestigation();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
    virtual void CurrentScene();
    virtual int NextScene();
};
#endif