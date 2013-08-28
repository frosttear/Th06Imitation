#pragma once
#include <d3dx9.h>

class TextRender
{
public:
	TextRender(D3DXFONT_DESC d3dFontDesc,LPCSTR text);
	void render(LPDIRECT3DDEVICE9 device,RECT rect, D3DCOLOR color);
	inline void SetText(LPCSTR text) {m_text = text;};
	inline D3DXFONT_DESC getFontDesc(){return m_d3dFontDesc;}
	void	SetFontDesc(D3DXFONT_DESC &d3dFontDesc){ m_d3dFontDesc = d3dFontDesc;}
	~TextRender();
private:
	D3DXFONT_DESC m_d3dFontDesc;
	LPCSTR m_text;

};