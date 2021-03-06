/*
Rice_GX - RenderTexture.h
Copyright (C) 2002 Rice1964
Copyright (C) 2010, 2011, 2012 sepp256 (Port to Wii/Gamecube/PS3)
Wii64 homepage: http://www.emulatemii.com
email address: sepp256@gmail.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef _TEXTURE_BUFFER_H_
#define _TEXTURE_BUFFER_H_



class CRenderTexture;
typedef struct {
    CRenderTexture *pRenderTexture;
    SetImgInfo  CI_Info;

    uint32      bufferWidth;
    uint32      bufferHeight;
    uint32      N64Width;
    uint32      N64Height;
    float       scaleX;
    float       scaleY;

    int         maxUsedHeight;
    uint32      updateAtFrame;
    uint32      updateAtUcodeCount;

    bool        isUsed;
    uint32      knownHeight;

    uint32      crcInRDRAM;
    uint32      crcCheckedAtFrame;

    TxtrCacheEntry txtEntry;
} RenderTextureInfo;


class CRenderTexture
{
public:
    friend class CGraphicsContext;
    friend class CDXGraphicsContext;
    friend class FrameBufferManager;
    friend class DXFrameBufferManager;
    friend class OGLFrameBufferManager;
#if 0//def __GX__
    friend class GXFrameBufferManager;
#endif //__GX__
    CRenderTexture(int width, int height, RenderTextureInfo* pInfo, TextureUsage usage)
    {
        m_beingRendered = false;
        m_width = m_height = 0;
        m_pTexture = NULL;
        m_pInfo = pInfo;
        m_usage = usage;
    }
    virtual ~CRenderTexture() {}

    virtual bool SetAsRenderTarget(bool enable)=0;
    virtual void LoadTexture(TxtrCacheEntry* pEntry)=0;

    virtual void StoreToRDRAM(int infoIdx) {};

    void GetDimension(int &width, int &height)
    {
        width = m_width;
        height = m_height;
    }

    bool IsBeingRendered()
    {
        return m_beingRendered;
    }

    TextureUsage GetUsage() {return m_usage;}


protected:
    int     m_width;
    int     m_height;
    bool    m_beingRendered;
    TextureUsage m_usage;

    CTexture* m_pTexture;
    RenderTextureInfo* m_pInfo;
};


class COGLRenderTexture : public CRenderTexture
{
    // Haven't implemented yet
public:
    COGLRenderTexture(int width, int height, RenderTextureInfo* pInfo, TextureUsage usage);
    ~COGLRenderTexture();

    bool SetAsRenderTarget(bool enable);
    void LoadTexture(TxtrCacheEntry* pEntry);
    void StoreToRDRAM(int infoIdx);

protected:
    bool InitPBuffer(void);
    void ShutdownPBuffer(void);

    int     m_widthCreated;
    int     m_heightCreated;

#ifndef XENON
    COGLTexture *m_pOGLTexture;
#else
    CxeTexture *m_pxeTexture;
#endif
};

#if 0//def __GX__
class CGXRenderTexture : public CRenderTexture
{
public:
	friend class COGLGraphicsContext;
	CGXRenderTexture(int width, int height, RenderTextureInfo* pInfo, TextureUsage usage);
	~CGXRenderTexture();

	bool SetAsRenderTarget(bool enable);
	void LoadTexture(TxtrCacheEntry* pEntry);
	void StoreToRDRAM(int infoIdx);

#ifdef _DEBUG
//	void Display(int idx);
#endif

protected:
//	MYLPDIRECT3DSURFACE m_pColorBufferSave;
//	MYLPDIRECT3DSURFACE m_pDepthBufferSave;
};
#endif //__GX__


#endif



