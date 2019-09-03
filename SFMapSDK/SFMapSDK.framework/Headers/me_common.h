#ifndef __ME_COMMON_H__
#define __ME_COMMON_H__

#include "me_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 公用的数据类型 */

typedef signed char     ME_CHAR;
typedef unsigned char   ME_UCHAR;
typedef signed short    ME_SHORT;
typedef unsigned short  ME_USHORT;
typedef signed int		ME_INT;
typedef unsigned int    ME_UINT;
typedef signed long		ME_LONG;
typedef unsigned long   ME_ULONG;
typedef float			ME_FLOAT;
typedef double			ME_DOUBLE;
typedef void			ME_VOID;
typedef signed char     ME_INT8;
typedef unsigned char   ME_UINT8;
typedef signed short    ME_INT16;
typedef unsigned short  ME_UINT16;
typedef signed int		ME_INT32;//iOS兼容数据64位
typedef unsigned int    ME_UINT32; //iOS兼容数据64位
typedef unsigned long long  ME_UINT64;
typedef long long       ME_INT64;
typedef char			ME_ARM_INT8;
typedef char			ME_ARM_CHAR;
typedef unsigned short ME_WCHAR;

#define ME_SPRINTF sprintf

/* TCHAR数据类型 */
#ifdef _WIN32_WCE
typedef ME_USHORT		ME_TCHAR;
#else
typedef ME_CHAR			ME_TCHAR;
#endif



/* 公用的宏 */
#define ME_PI			3.1415927

#define ME_NULL			0
#define ME_BOOL			ME_CHAR
#define ME_TRUE			1
#define ME_FALSE		0
#define ME_EXTERN		extern
#define ME_COLOR        ME_INT32
#define ME_U64			U64
#define ME_LCD_WIDTH	240
#define ME_LCD_HEIGHT   320
#define ME_TILE_WIDTH	64
#define ME_TILE_HEIGHT  64
#define ME_TILE_SIZE	ME_TILE_WIDTH*ME_TILE_HEIGHT*2

/* 消息类型 */
#define ME_MSG_KEYDOWN		0
#define ME_MSG_KEYUP		1
#define ME_MSG_PENDOWN		2
#define ME_MSG_PENUP		3
#define ME_MSG_PENMOVE		4

/* 键盘编号 */
#define ME_KEY_0			48 /* KEY_0 */
#define ME_KEY_1			49 /* KEY_1 */
#define ME_KEY_2			50 /* KEY_2 */
#define ME_KEY_3			51 /* KEY_3 */
#define ME_KEY_4			52 /* KEY_4 */
#define ME_KEY_5			53 /* KEY_5 */
#define ME_KEY_6			54 /* KEY_6 */
#define ME_KEY_7			55 /* KEY_7 */
#define ME_KEY_8			56 /* KEY_8 */
#define ME_KEY_9			57 /* KEY_9 */
#define ME_KEY_LSK			58 /* KEY_LSK */
#define ME_KEY_RSK			59 /* KEY_RSK */
#define ME_KEY_CSK			60 /* KEY_CSK */
#define ME_KEY_UP_ARROW		61 /* KEY_UP_ARROW */
#define ME_KEY_DOWN_ARROW	62 /* KEY_DOWN_ARROW */
#define ME_KEY_LEFT_ARROW	63 /* KEY_LEFT_ARROW */
#define ME_KEY_RIGHT_ARROW	64 /* KEY_RIGHT_ARROW */
#define ME_KEY_SEND			65 /* KEY_SEND */
#define ME_KEY_END			66 /* KEY_END */
#define ME_KEY_CLEAR		67 /* KEY_CLEAR */
#define ME_KEY_STAR			42 /* KEY_STAR */
#define ME_KEY_POUND		35 /* KEY_POUND */
#define ME_KEY_VOL_UP		70 /* KEY_VOL_UP */
#define ME_KEY_VOL_DOWN		71 /* KEY_VOL_DOWN */
#define ME_KEY_QUICK_ACS	72 /* KEY_QUICK_ACS	*/
#define ME_KEY_CAMERA		73 /* KEY_CAMERA */
#define ME_KEY_IP			76 /* KEY_ENTER */
#define ME_KEY_WAP			75 /* KEY_WAP */
#define ME_KEY_ENTER		74 /* KEY_IP */
#define ME_KEY_EXTRA_1		77 /* KEY_EXTRA_1 */
#define ME_KEY_EXTRA_2		78 /* KEY_EXTRA_2 */
#define ME_KEY_PLAY_STOP	79 /* KEY_PLAY_STOP */
#define ME_KEY_FWD			80 /* KEY_FWD */
#define ME_KEY_BACK			81 /* KEY_BACK */
#define ME_KEY_POWER		82 /* KEY_POWER */
#define ME_MAX_KEYS			83 /* MAX_KEYS */

/* 公用的结构体 */

typedef struct {
	ME_LONG		m_x;
	ME_LONG		m_y;
} ME_Point;

typedef struct {
	ME_LONG		m_x;
	ME_LONG		m_y;
	ME_LONG		m_z;
} ME_Point3D;

typedef ME_Point*	ME_PointPtr;

/* 短点 */
typedef struct {
	ME_INT16		m_x;
	ME_INT16		m_y;
} ME_SPoint;

typedef ME_SPoint*	ME_SPointPtr;

/** 点集合结构  */
typedef struct 
{
    ME_Point* pointList;
    /* 共有多少个节点 */
    ME_UINT16 _size;
    /* 有效节点数 */
    ME_UINT16 nPntCount;
} ME_PointList;

typedef ME_PointList* ME_PointListPtr;

typedef struct {
	ME_LONG		m_width;
	ME_LONG		m_height;
} ME_Size;

typedef ME_Size*	ME_SizePtr;

typedef struct {
	ME_LONG		m_x;
	ME_LONG		m_y;
	ME_LONG		m_width;
	ME_LONG		m_height;	
} ME_Rect;
    
typedef struct {
    ME_DOUBLE		m_x;
    ME_DOUBLE		m_y;
    ME_FLOAT		m_width;
    ME_FLOAT		m_height;
} ME_Rectangle;

typedef ME_Rect*	ME_RectPtr;
typedef void *SkImagePtr;
 
#ifdef __cplusplus
}
#endif

#endif
