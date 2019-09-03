#ifndef _WXMAPTOOLS_API_H_INCLUDED_
#define _WXMAPTOOLS_API_H_INCLUDED_
#include "me_defines.h"
#include "me_mapapi.h"

#ifdef __cplusplus
extern "C"
{
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef void* me_linebuilder;
    me_linebuilder me_linebuilder_new();
    void me_linebuilder_destroy(me_linebuilder linebuilder);
    void me_linebuilder_moveto(me_linebuilder linebuilder, me_float x, me_float y);
    void me_linebuilder_lineto(me_linebuilder linebuilder, me_float x, me_float y);
    void me_linebuilder_reset(me_linebuilder linebuilder);
	void me_linebuilder_setVexOffset(me_linebuilder linebuilder, me_int offset);
    void me_linebuilder_setwidth(me_linebuilder linebuilder, me_float width);
	me_bool me_linebuilder_canBuildLine(me_linebuilder linebuilder);
    void me_linebuilder_build(me_linebuilder linebuilder);
    void me_linebuilder_setTexInfo(me_linebuilder linebuilder, float x1, float y1, float x2, float y2, float glstart, float glTexLen);
    me_uint8* me_linebuilder_getVexBuffer(me_linebuilder linebuilder, me_int* nBufferSize, me_int* vexSize);
    me_uint16* me_linebuilder_getIndexBuffer(me_linebuilder linebuilder, me_int* nBufferSize, me_int* indexSize);
    void me_linebuilder_setRoundCapTexInfo(me_linebuilder linebuilder, float x1, float y1, float x2, float y2);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    typedef void* me_arrowlinebuilder;
    me_arrowlinebuilder me_arrowlinebuilder_new();
    void me_arrowlinebuilder_destroy(me_arrowlinebuilder linebuilder);
    void me_arrowlinebuilder_moveto(me_arrowlinebuilder linebuilder, me_float x, me_float y);
    void me_arrowlinebuilder_lineto(me_arrowlinebuilder linebuilder, me_float x, me_float y);
    void me_arrowlinebuilder_reset(me_arrowlinebuilder linebuilder);
    void me_arrowlinebuilder_setwidth(me_arrowlinebuilder linebuilder, me_float width);
    void me_arrowlinebuilder_build(me_arrowlinebuilder linebuilder);
    me_uint8* me_arrowlinebuilder_getVexBuffer(me_arrowlinebuilder linebuilder, me_int* nBufferSize, me_int* vexSize);
    me_uint16* me_arrowlinebuilder_getIndexBuffer(me_arrowlinebuilder linebuilder, me_int* nBufferSize, me_int* indexSize);
    me_uint8* me_arrowlinebuilder_getSideVexBuffer(me_arrowlinebuilder linebuilder, me_int* nBufferSize, me_int* vexSize);
    me_uint16* me_arrowlinebuilder_getSideIndexBuffer(me_arrowlinebuilder linebuilder, me_int* nBufferSize, me_int* indexSize);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    typedef void* me_polygonbuilder;
    me_polygonbuilder me_polygonbuilder_new();
    void me_polygonbuilder_destroy(me_polygonbuilder polygonbuilder);
    void me_polygonbuilder_moveto(me_polygonbuilder polygonbuilder, me_float x, me_float y);
    void me_polygonbuilder_lineto(me_polygonbuilder polygonbuilder, me_float x, me_float y);
    void me_polygonbuilder_reset(me_polygonbuilder polygonbuilder);
    void me_polygonbuilder_build(me_polygonbuilder polygonbuilder);
    me_uint8* me_polygonbuilder_getVexBuffer(me_polygonbuilder polygonbuilder, me_int* nBufferSize, me_int* vexSize);
    me_uint16* me_polygonbuilder_getIndexBuffer(me_polygonbuilder polygonbuilder, me_int* nBufferSize, me_int* indexSize);

#ifdef __cplusplus
}
#endif

#endif /* def _WXMAPTOOLS_API_H_INCLUDED_ */
