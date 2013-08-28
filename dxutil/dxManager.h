#pragma once

#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>

class dxManager
{
public:
	~dxManager(void);

	// singleton stuff
	static dxManager& getInstance() { static dxManager pInstance; return pInstance;}
	
	//bool init(HWND hwnd);
	bool init(HWND hwnd,bool bFullScreen = false);
	void shutdown(void);
	void beginRender(void);
	void endRender(void);
	IDirect3DSurface9* getSurfaceFromBitmap(std::string filename);

	IDirect3DSurface9* getBackBuffer(void);
	void blitToSurface(IDirect3DSurface9* srcSurface, const RECT *srcRect, const RECT *destRect);
	LPDIRECT3DDEVICE9 getD3DDevice(void) { 
		return pd3dDevice; 
	}
	ID3DXSprite *	GetSprite(void){return pSprite;}

private:
	dxManager(void);
	bool m_bFullScreen;
	HRESULT                 lastResult;
	LPDIRECT3D9             pD3D;
	LPDIRECT3DDEVICE9       pd3dDevice;
	ID3DXSprite *			pSprite;
/*	D3DMATERIAL9* m_pMeshMaterials;
	DWORD               m_dwNumMaterials;     // Number of materials	

	LPD3DXMESH   pMeshSysMem;
*/
	// screen details
	int screen_width;
	int screen_height;

	// camera details
/*	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	D3DXVECTOR3 position;
	D3DXVECTOR3 lookPos;*/
};

#define SIZEARRAY(x) sizeof(x)/sizeof(x[0]
static dxManager& dxMgr = dxManager::getInstance();