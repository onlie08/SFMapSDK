#ifndef _WXMAP_PRIVATE_API_H_
#define _WXMAP_PRIVATE_API_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "me_defines.h"
#include "me_mapapi.h"
#if defined(TARGET_OS_IPHONE)
#include <OpenGLES/gltypes.h>
#endif

typedef enum {
    POI_FILTER_RIGHT = 0,
    POI_FILTER_LEFT = 1, 
    POI_FILTER_CENTER = 2,          
} me_poi_filter_anchor;

typedef struct me_poi_filter_rect_struct
{
	int m_geoX; //20级像素坐标
	int m_geoY; //20级别像素坐标
	int m_anchor; //锚点 
	me_float m_screenWidth;//显示宽度 屏幕坐标系
	me_float m_screenHeight;//显示高度 屏幕坐标系
	me_char m_keyName[ME_MAXPOIIDLEN]; //根据目前位数可以改小 当做key使用
}me_poi_filter;
  

#if defined(TARGET_OS_IPHONE)
void me_mapengine_private_fillscreengridlistbuffer(me_mapengine mapengine, me_uint8* pbuffer, me_int datasource);
void me_mapengine_private_loadtexture(me_mapengine mapengine, me_uint8* pbuffer, me_int datalen, GLuint* textureID);
#endif

me_int me_projection_private_get_pixelOnLevel20WithGlUnit(me_projection projection, me_float glUnit);

void me_projection_private_get_screenMapBoundPixel20(me_projection projection, me_long* x, me_long* y, me_long* width, me_long* height);

me_float me_projection_private_get_zoomScale(me_projection projection);

/*
*添加一个filter
*/
void me_mapengine_private_addPoiFilter(me_mapengine mapengine,me_poi_filter* poiFilter);

/*
*删除一个filter
*/
void me_mapengine_private_removePoiFilter(me_mapengine mapengine,me_char poiid[ME_MAXPOIIDLEN]);

/*
*清空所有filter
*/
void me_mapengine_private_clearPoiFilter(me_mapengine mapengine);


#ifdef __cplusplus
}
#endif
#endif /* _WXMAP_PRIVATE_API_H_ */
