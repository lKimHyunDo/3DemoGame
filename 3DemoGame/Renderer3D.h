#pragma once

#include "Matrix4X4.h"
#include "Vec3.h"
#include "Polygon.h"
#include<vector>

using namespace std;

class SDL_Surface;
class SDL_Renderer;
class Camera;
class GameObject3D;

class Renderer3D
{
#pragma region Singleton
private:
	static Renderer3D* inst;
public:
	static Renderer3D* Instance() {
		if (inst == 0)
			inst = new Renderer3D;
		return inst;
	}
	static Renderer3D* DeleteInstance() {
		if (inst != 0) {
			delete inst;
			inst = 0;
		}
	}
#pragma endregion

private:
	SDL_Renderer * m_pRenderer;
	SDL_Surface * m_pScreenBuffer = 0;
	float* m_pDepthBuffer = 0;
	Camera* m_pCamera;

	int m_screenW;
	int m_screenH;

	//원근투영 행렬
	Matrix4X4 m_matProj;
	//카메라 좌표계 행렬
	Matrix4X4 m_matLootAt;
	//뷰포트 행렬
	Matrix4X4 m_matViewport;

	Vec3 m_light = { 0,0,0 };

public:
	~Renderer3D();

	bool Init(SDL_Renderer* pRenderer, Camera* pCamera, Vec3 light, int screenW, int screenH);
	void Rendering(GameObject3D* pGameObject3D);
	void Render3DPresent();

private:
	void WorldSpace(GameObject3D* pGameObject,vector<Polygon>& polys);
	void ViewSpace(vector<Polygon>& polys);
	void BackfaceCulling(vector<Polygon>& polys, vector<Polygon>& culledPolys);
	void Shading();
	void Projection();
	void Viewport();
	void Texturing();

};