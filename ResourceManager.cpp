//--------------------------------------------------------------------------------------    
//File		:  ResourceManager.cpp
//Path		:  D:\MYPROJECTS\TH06-LIKE\TH06-LIKE\
//Author    :  Liu.zhenxing
//CreateTime:  2010/9/15 8:58
//Description: Encapsulates Textures,Sound and BGM resources.Offers Load and Get operation
//--------------------------------------------------------------------------------------
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	m_bIsReady = false;
}
ResourceManager::~ResourceManager()
{
	//Release Textures
	for (int i = 0 ; i < TEXTURE_NUM; ++i)
	{
		if (m_pTextures[i] != NULL)
			m_pTextures[i]->Release();
	}
	//Release Sound
	/*for (int i = 0; i < SOUND_NUM; ++i)
	{
		if (m_soundBuffers[i] != NULL)
		{
			m_soundBuffers[i]->Release();
		}
	}*/
	//Release BGM
	//for (int i = 0; i < BGM_NUM; ++i)
	//{
	//	if (m_bgmBuffers[i] != NULL)
	//	{
	//		m_bgmBuffers[i]->Release();
	//	} 
	//}
}

void ResourceManager::LoadResource()
{
	LoadTexture();
	LoadSound();
	m_bIsReady = true;
}

void ResourceManager::LoadTexture(void)
{
	for (int i = 0 ; i < TEXTURE_NUM; i ++)
	{
		if (FAILED(D3DXCreateTextureFromFile(dxMgr.getD3DDevice(),(TEXTURE_PATH + TEXTURE_FILENAME[i]).c_str(),&m_pTextures[i])))
		{
			MessageBox(NULL, ("unable to load texture from file" + TEXTURE_FILENAME[i]).c_str(), "ERROR", MB_OK);
		}
	}
}

void ResourceManager::LoadSound(void)
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		m_soundBuffers[i]	= dsMgr.LoadWaveToSoundBuffer(SOUND_PATH + SOUND_FILENAME[i]);

	}

	for (int i = 0; i < BGM_NUM; i ++)
	{
		m_bgmBuffers[i]	= dsMgr.LoadWaveToSoundBuffer(BGM_PATH + BGM_FILENAME[i]);
	}
}
RECT	ResourceManager::GetRectOfDigit(int digit)
{
	RECT rect;
	int width  = 16;
	int height = 16;

	SetRect(&rect, 0 + width * digit, 48,0 + width * (digit + 1), 48 + height);
	return rect;
}
RECT	ResourceManager::GetRectOfAscii(char ch)
{
	int width	= 16;
	int height	= 16;

	RECT rect;
	//numbers
	if (ch >= '0' && ch <= '9')
	{
		rect = GetRectOfDigit(ch - '0');
	}else
	{
		//letters

		if (ch >= 'a' && ch <= 'z')
		{
			if (ch <= 'o')
			{
				SetRect(&rect,width + (ch - 'a') * width, 96, width * (ch - 'a' + 2), 96 + height);
			}else
			{
				SetRect(&rect, (ch - 'p') * width, 112, width * (ch - 'p' + 1), 128);
			}

		}else
		{
			if (ch >= 'A' && ch <= 'Z')
			{
				if (ch <= 'O')
				{
					SetRect(&rect, width + (ch - 'A') * width, 64, width * (ch - 'A' + 2), 64 + height);
				}else
				{
					SetRect(&rect, (ch - 'P') * width, 80, width * (ch - 'P' + 1), 96);
				}
			}
			else
			{//other chars
				switch (ch)
				{
				case ' ':
					SetRect(&rect, 0, 32, 16, 48);
					break;
				case '!' :
					SetRect(&rect, 16, 32, 32 , 48);
					break;
				case '"':
					SetRect(&rect, 32, 32, 48, 48);
					break;
				case '#':
					SetRect(&rect, 48, 32, 64, 48);
					break;
				case '$':
					SetRect(&rect, 64, 32, 80, 48);
					break;
				case '%':
					SetRect(&rect, 80, 32, 96, 48);
					break;
				case '&':
					SetRect(&rect, 96, 32, 112, 48);
					break;
				case '\'':
					SetRect(&rect, 112, 32, 128, 48);
					break;
				case '(':
					SetRect(&rect, 128, 32, 144, 48);
					break;
				case ')':
					SetRect(&rect, 144, 32, 160, 48);
					break;
				case '*':
					SetRect(&rect, 160, 32, 176, 48);
					break;
				case '+':
					SetRect(&rect, 176, 32, 192, 48);
					break;
				case ',':
					SetRect(&rect, 192, 32, 208, 48);
					break;
				case '-':
					SetRect(&rect, 208, 32, 224, 48);
					break;
				case '.':
					SetRect(&rect, 224, 32, 240, 48);
					break;
				case '\\':
					SetRect(&rect, 240, 32, 256, 48);
					break;
				case ':':
					SetRect(&rect, 160, 48, 176, 64);
					break;
				case ';':
					SetRect(&rect, 176, 48, 192, 64);
					break;
				case '<':
					SetRect(&rect, 192, 48, 208, 64);
					break;
				case '=':
					SetRect(&rect, 208, 48, 224, 64);
					break;
				case '>':
					SetRect(&rect, 224, 48, 240, 64);
					break;
				case '?':
					SetRect(&rect, 240, 48, 256, 64);
					break;
				case '[':
					SetRect(&rect, 176, 64, 192, 80);
					break;
				case 'гд':
					SetRect(&rect, 192, 64, 208, 80);
					break;
				case ']':
					SetRect(&rect, 208, 64, 224, 80);
					break;
				case '^':
					SetRect(&rect, 224, 64, 240, 80);
					break;
				case '_':
					SetRect(&rect, 240, 64, 256, 80);
					break;
				case '{':
					SetRect(&rect, 176, 96, 192, 112);
					break;
				case '|':
					SetRect(&rect, 192, 96, 208, 112);
					break;
				case '}':
					SetRect(&rect, 208, 96, 224, 112);
					break;
				case '~':
					SetRect(&rect, 224, 96, 240, 112);
					break;
				default:
					SetRect(&rect, 240, 96, 256, 112);
					break;
				}
			}
		}
	}

	return rect;
}