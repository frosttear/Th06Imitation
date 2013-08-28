#include ".\TextRender.h"

TextRender::TextRender(D3DXFONT_DESC d3dFontDesc,LPCSTR text)
{
	m_d3dFontDesc = d3dFontDesc;
	m_text		  = text;
}

void TextRender::render(LPDIRECT3DDEVICE9 device,RECT rect, D3DCOLOR color)
{
	ID3DXFont* font = NULL;
	D3DXCreateFontIndirect(device,&m_d3dFontDesc,&font);
	font->DrawText(NULL, m_text,-1,  &rect, DT_TOP | DT_LEFT, color);
	font->Release();
	font = NULL;
}