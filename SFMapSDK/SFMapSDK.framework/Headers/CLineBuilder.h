
#ifndef __ME_LINEBUILDER3D_H__
#define __ME_LINEBUILDER3D_H__


#include "me_defines.h"
#include "me_common.h"
#include <stdio.h>
#include <math.h>


#define CL_INIT_LINE_POINTCOUNT 16
#define CL_INIT_INDEX_COUNT 16*6


typedef float MeScalar;


struct MePoint {
	MeScalar    fX, fY, fZ;

	static MePoint Make(MeScalar x, MeScalar y) {
		MePoint pt;
		pt.set(x, y);
		return pt;
	}
	
	void set(MeScalar x, MeScalar y) { fX = x; fY = y; fZ = 0;}
	void set(MeScalar x, MeScalar y, MeScalar z) { fX = x; fY = y; fZ = z;}
	MeScalar length() const { return MePoint::Length(fX, fY); }
	bool normalize();
	bool setNormalize(MeScalar x, MeScalar y);
	bool setLength(MeScalar length);
	bool setLength(MeScalar x, MeScalar y, MeScalar z, MeScalar length);
	void scale(MeScalar scale, MePoint* dst) const;
	void scale(MeScalar value) { this->scale(value, this); }
	void rotateCW(MePoint* dst) const;
	void rotateCW() { this->rotateCW(this); }
	void rotateCCW(MePoint* dst) const;
	void rotateCCW() { this->rotateCCW(this); }
	void negate() {
		fX = -fX;
		fY = -fY;
	}
	MeScalar Dot(const MePoint& v)
	{
		 return fX * v.fX + fY * v.fY;
	}
	MePoint operator-() const {
		MePoint neg;
		neg.fX = -fX;
		neg.fY = -fY;
		return neg;
	}

	void operator+=(const MePoint& v) {
		fX += v.fX;
		fY += v.fY;
	}

	void operator-=(const MePoint& v) {
		fX -= v.fX;
		fY -= v.fY;
	}

	bool equals(MeScalar x, MeScalar y) const { return fX == x && fY == y; }

	friend bool operator==(const MePoint& a, const MePoint& b) {
		return a.fX == b.fX && a.fY == b.fY;
	}

	friend bool operator!=(const MePoint& a, const MePoint& b) {
		return a.fX != b.fX || a.fY != b.fY;
	}

	friend MePoint operator-(const MePoint& a, const MePoint& b) {
		MePoint v;
		v.set(a.fX - b.fX, a.fY - b.fY);
		return v;
	}

	friend MePoint operator+(const MePoint& a, const MePoint& b) {
		MePoint v;
		v.set(a.fX + b.fX, a.fY + b.fY);
		return v;
	}

	static MeScalar Length(MeScalar x, MeScalar y);

	static MeScalar Normalize(MePoint* pt);

	static MeScalar Distance(const MePoint& a, const MePoint& b) {
		return Length(a.fX - b.fX, a.fY - b.fY);
	}

	static MeScalar DP(const MePoint& a, const MePoint& b) {
		float tmp = a.fX*b.fX + a.fY*b.fY;
		if (tmp > 1.0f)
		{
			tmp = 1.0f;
		}
		else if (tmp < -1.0f)
		{
			tmp = -1.0f;
		}
		return tmp;
	}


	static MeScalar CP(const MePoint& a, const MePoint& b) {
		return a.fX * b.fY - a.fY*b.fX;
	}
};

typedef MePoint MeVector;

struct MeTexVertex
{
	MePoint m_point;
	MePoint m_texpnt;
};

class CPointList
{
public:
	CPointList();
	~CPointList();
	MePoint* m_points;
	int m_nPointCount ;
	int m_nAlloced;
public:
	void AddPoint(float x,float y, float z);

	void AddPoint(float x,float y)
	{
		AddPoint(x, y, 0);
	}

	void AddPoint(MePoint& pnt)
	{
		AddPoint(pnt.fX,pnt.fY,pnt.fZ);
	}

	MePoint* GetPointFromLast(int index)
	{

		return &m_points[m_nPointCount-index-1];
	}

	int GetPointSize(){return m_nPointCount;};
	void Reset(){m_nPointCount=0;};
	void ReAllocate(int allocatesize);
};
class CTriangleList
{
public:
	MeTexVertex* m_points;
	unsigned short* m_index;

	int m_nPointCount;
	int m_nIndexCount;
	
	int m_nPntAlloced;
	int m_nIndexAlloced;

	int m_nIndexOffset;



private:
	int m_tagOffIndex;
public:
	CTriangleList();
	~CTriangleList();
	void Reset(){
		m_nPointCount=0;m_nIndexCount=0;m_nIndexOffset=0;
	};
	MePoint* GetPointFromLast(int index);
	void BeginAddPoint(){m_tagOffIndex = m_nPointCount;};
	void AddPoint(MePoint* pnt,MePoint* texCoords);
	void AddPoint(MePoint* pnt);
	void AddIndexWithOffset(int offIndex);
	void AddIndexWithOffsetArray(int* offIndexArray,int count)
	{
		for(int i=0;i<count;i++) AddIndexWithOffset(offIndexArray[i]);
	};
	int GetPointSize(){return m_nPointCount;};
	int GetIndexSize(){return m_nIndexCount;};
	

};


enum MeAngleType {
	kSharp_AngleType,
	kShallow_AngleType,
};


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

enum LineCapType
{
	eLineCapCut = 0,
	eLineCapRound = 1
};

class CIntArray
{
public:
	int* m_ints;
	int m_nCount ;
	int m_nAlloced;
public:
	CIntArray();
	virtual ~CIntArray();
	void AddInt(int n);
	void Reset(){m_nCount=0;};
};

class CLineTextureBuilder
{
public:
	float m_texX0,m_texY0,m_texX1,m_texY1;

	float m_caprondX0,m_caprondY0,m_caprondX1,m_caprondY1;


	float m_textureGLStart;
	float m_textureGLLength;
	
	float m_textureLenUsed;

	MePoint m_texCntPntTop,m_texCntPntBottom;
	MeVector m_lineVector;

	float m_lineLen;
	float m_texScale;
	float m_texUsePercent;

	MePoint m_p0,m_p1;
	MePoint m_texStartPnt,m_texEndPnt;
	ME_BOOL m_bpt;

public:
	void Reset()
	{
		m_textureLenUsed=0;
	}
	void SetRoundCapTexInfo(float x0,float y0,float x1,float y1)
	{
		m_caprondX0=x0;
		m_caprondY0=y0;
		m_caprondX1=x1;
		m_caprondY1=y1;

	}
	void SetTexInfo(float x0,float y0,float x1,float y1,float fglStart,float fglTexLen)
	{
		 
		m_texX0=x0;
		 m_texY0=y0;
		 m_texX1=x1;
		 m_texY1=y1;
		

		 (y0==y1)?m_bpt=ME_FALSE:m_bpt=ME_TRUE;

		m_textureGLStart=fglStart;
		m_textureGLLength=fglTexLen;
		m_texCntPntTop.set((x0+x1)/2,y0);
		m_texCntPntBottom.set((x0+x1)/2,y1);
		m_texScale = fglTexLen/(y1-y0);
		m_texUsePercent = ((y1-y0));

	};

	void SetLine(MePoint tp0,MePoint tp1){
		if(!m_bpt)return;
		m_p0.set(tp0.fX,tp0.fY);
		m_p1.set(tp1.fX,tp1.fY);
		m_lineVector = m_p1 - m_p0;
		m_lineLen = m_lineVector.length();
		m_texStartPnt.set((m_texX0 + m_texX1)/2,m_textureLenUsed);

		float tLen=m_lineLen-m_textureGLLength*(int)(m_lineLen/m_textureGLLength);
		m_textureLenUsed +=  tLen /m_texScale;


	};
	void CalTexture(MePoint p,MePoint& outTxtPnt1,ME_BOOL bLeft)
	{
		if(!m_bpt)
		{
			if(bLeft)
			{
				outTxtPnt1.set(m_texX0,m_texY0);
			}else
			{
				outTxtPnt1.set(m_texX1,m_texY1);
			}

		}else{
			MeVector pv=p-m_p0;
			float dotValue = MePoint::DP(m_lineVector,pv);
			float yTex= dotValue/ m_lineVector.length();
			float xTex = m_texX0;
			if(!bLeft) xTex = m_texX1;
			
			outTxtPnt1.set(xTex,m_texStartPnt.fY+(m_texY1-m_texY0)*yTex/m_texScale/m_texUsePercent);
		}
	}
};

class CLineBuilder
{
public:
	CLineBuilder();
	virtual ~CLineBuilder();
public:
	ME_BOOL m_bUseInner ;
public:	
	CPointList m_ll;

	CPointList m_cappoints;
	CPointList m_capvecs;
	CIntArray  m_capFlag;  //标志是否为起点


	CIntArray	m_segStartIndex;
	CIntArray	m_segPointSizes;
	CIntArray	m_segFlag;  //标志是否为主动打断

	CPointList* m_po;
	CPointList* m_pi;

	CTriangleList m_tns;
	CLineTextureBuilder m_textureBuilder;

protected:
	float  m_width,m_halfWidth;
	LineCapType m_captype;
	
	
public:
	void SetWidth(float w){m_width = w;m_halfWidth=m_width/2;}
	void SetLineCapType(LineCapType cap){m_captype = cap;};
	void SetVexOffset(int offset){m_tns.m_nIndexOffset=offset;}
	virtual void MoveTo(float x,float y){ MoveTo(x, y, 0); }
	virtual void LineTo(float x,float y){ LineTo(x, y, 0); }
	virtual void MoveTo(float x,float y, float z);
	virtual void LineTo(float x,float y, float z);	
	void DoBuilderLine();
	void DoInnerBuilderLine(int,int,bool);
	void RotateTextCoors();
	void Reset(){m_ll.Reset();m_tns.Reset();m_po->Reset();m_pi->Reset();m_textureBuilder.Reset();
		m_cappoints.Reset();m_capvecs.Reset();m_capFlag.Reset();
		m_segStartIndex.Reset();m_segPointSizes.Reset();m_segFlag.Reset();};
private:
	void SegInnerReset()
	{
			m_po->Reset();m_pi->Reset();m_textureBuilder.Reset();
			m_cappoints.Reset();m_capvecs.Reset();
			
	}

	void addCap(const MePoint& pp, const MePoint& pv,bool isFirstCap,float capVLen);
	
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

class CArrowLineBuilder : public CLineBuilder
{
public:
	CArrowLineBuilder(){}
	virtual ~CArrowLineBuilder(){}
public:
	void DoBuilderLine();
	void Reset()
	{
		m_ll.Reset();
		m_tns.Reset();
		m_tnsSide.Reset();
		m_po->Reset();
		m_pi->Reset();
		m_textureBuilder.Reset();
	};

	virtual void MoveTo(float x,float y){ MoveTo(x, y, 0); }
	virtual void LineTo(float x,float y){ LineTo(x, y, 0); }
	virtual void MoveTo(float x,float y, float z);
	virtual void LineTo(float x,float y, float z);	
public:
	CTriangleList m_tnsSide;
};


class CLinesArraysTess
{
public:
	CLinesArraysTess();
	virtual ~CLinesArraysTess();
private:


	int m_nVexBufferAlloced;
	int m_nIndBufferAlloced;


	int m_nVexSize;
	int m_nIndexSize;

	ME_UINT8* m_pVexBuffer;
	ME_UINT8* m_pIndBuffer;

public:
	void AddLineBuilderResult(CLineBuilder* plineBuilder);
	ME_UINT8* GetVexBuffer(int& nBufferSize);
	ME_UINT8* GetIndexBuffer(int& nBufferSize);
	int GetVexSize(){return m_nVexSize;};
	int GetIndexSize(){return m_nIndexSize;};
	void Reset();

};




#endif
