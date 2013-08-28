#include ".\dxmanager.h"

dxManager::dxManager(void)
{
	pD3D = NULL;
 	pd3dDevice = NULL;

	m_bFullScreen = false;
	screen_width = 640;
	screen_height = 512;
}

dxManager::~dxManager(void)
{
}

/********************************************************************
* init
* Initializes DirectX
********************************************************************/
bool dxManager::init(HWND hwnd, bool isFullScreen)
{
	m_bFullScreen = isFullScreen;

	if( NULL == ( pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		lastResult = E_FAIL;
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	if (m_bFullScreen)
	{
		d3dpp.Windowed = FALSE;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	}else
	{
		d3dpp.Windowed = TRUE;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferCount  = 1;
	d3dpp.BackBufferHeight = screen_height;
	d3dpp.BackBufferWidth  = screen_width;
//	d3dpp.hDeviceWindow    = GetModuleHandle(NULL);//hwnd;
//	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
  //  d3dpp.EnableAutoDepthStencil = TRUE;

    if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &pd3dDevice ) ) )
    {
		lastResult = E_FAIL;
        return false;
    }

	D3DXVECTOR3 vEyePt( 0.0f, 3.0f,15.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    pd3dDevice->SetTransform( D3DTS_VIEW, &matView );	
//pd3dDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	//pd3dDevice->SetRenderState(D3DRS_FOGTABLEMODE,	D3DFOG_LINEAR);
	//pd3dDevice->SetRenderState(D3DRS_FOGSTART,		50);
	//pd3dDevice->SetRenderState(D3DRS_FOGEND,		200);
	//pd3dDevice->SetRenderState(D3DRS_FOGCOLOR, 0xFFAA8888);

	//pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	//pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	//pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	//pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(255,255, 255, 255));


	//pd3dDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE); 
	//pd3dDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);
//	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	
//	pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
//	pd3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
//	pd3dDevice->SetRenderState( D3DRS_LIGHTING,     TRUE);
//	pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));

	/*D3DLIGHT9 light;
    D3DXVECTOR3 vDir( 0.3f, -1.0f, 1.0f );
    light.Type         = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r    = light.Diffuse.g  = light.Diffuse.b  = 1.0f;
    light.Specular.r   = light.Specular.g = light.Specular.b = 0.0f;
    light.Ambient.r    = light.Ambient.g  = light.Ambient.b  = 0.3f;
    light.Position     = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vDir );
    light.Attenuation0 = light.Attenuation1 = light.Attenuation2 = 0.0f;
    light.Range        = sqrtf(FLT_MAX);
    pd3dDevice->SetLight(0, &light );
    pd3dDevice->LightEnable(0, TRUE );

	pd3dDevice->SetRenderState( D3DRS_ZENABLE,      TRUE );*/
	if (FAILED(D3DXCreateSprite(pd3dDevice, &pSprite)))
		return false;
	return true;
}

/********************************************************************
* shutdown
* Releases the DirectX interfaces
********************************************************************/
void dxManager::shutdown(void)
{
    if( pd3dDevice != NULL) 
	{
        pd3dDevice->Release();
		pd3dDevice = NULL;
	}
    if( pD3D != NULL)
	{
        pD3D->Release();
		pD3D = NULL;
	}
	if (pSprite != NULL)
	{
		pSprite->Release();
		pSprite = NULL;
	}
}

/********************************************************************
* beginRender
* Prepares DirectX for rendering each frame
********************************************************************/
void dxManager::beginRender()
{
	if( NULL == pd3dDevice )
        return;

    // Clear the backbuffer to a black color
    HRESULT hr = pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(55,55,55), 1.0f, 0 );
	pd3dDevice->BeginScene();
//if (pSprite)
	//	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

/********************************************************************
* endRender
* Called after rendering has completed. Presents the result to the
* screen.
********************************************************************/
void dxManager::endRender(void)
{	
	//if (pSprite)
		//pSprite->End();
	pd3dDevice->EndScene();
	// Present the backbuffer contents to the display
    pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

/********************************************************************
* getSurfaceFromBitmap
* Utility function to load in a bitmap
********************************************************************/
IDirect3DSurface9* dxManager::getSurfaceFromBitmap(std::string filename)
{
	HRESULT hResult;
	IDirect3DSurface9* surface = NULL;
	D3DXIMAGE_INFO imageInfo;

	// Get the width and height info from this bitmap
	hResult = D3DXGetImageInfoFromFile(filename.c_str(), &imageInfo);
	if FAILED (hResult)
		return NULL;

	hResult = pd3dDevice->CreateOffscreenPlainSurface(imageInfo.Width, imageInfo.Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	if (FAILED(hResult))
		return NULL;

	hResult = D3DXLoadSurfaceFromFile(surface, NULL, NULL, filename.c_str(), NULL, D3DX_FILTER_NONE, 0, NULL);
	if (FAILED(hResult))
		return NULL;

	return surface;
}

/********************************************************************
* getBackBuffer
* Utility function used to return a pointer to the current back
* buffer
********************************************************************/
IDirect3DSurface9* dxManager::getBackBuffer(void)
{
	IDirect3DSurface9* backbuffer = NULL;

	if (!pd3dDevice)
		return NULL;

	HRESULT hResult = pd3dDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	if (FAILED(hResult))
		return NULL;
	else
		return backbuffer;
}

/********************************************************************
* blitToSurface
* Utility function used to copy an off screen surface to the back
* buffer
********************************************************************/
void dxManager::blitToSurface(IDirect3DSurface9* srcSurface, const RECT *srcRect, const RECT *destRect)
{
	if (pd3dDevice)
		pd3dDevice->StretchRect(srcSurface, srcRect, getBackBuffer(), destRect, D3DTEXF_NONE);
}
