#ifndef _WXMAPCORE_API_H_INCLUDED_
#define _WXMAPCORE_API_H_INCLUDED_

#include "me_defines.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#define ME_DATA_ROAD           0        //基础地图
#define ME_DATA_GEO_BUILDING   1        //楼块地图数据
#define ME_DATA_BMP_BASEMAP    2        //基础栅格地图数据 <14级使用
#define ME_DATA_SATELLITE      3        //卫星影像数据
#define ME_DATA_VEC_TMC        4        //矢量实时交通数据
#define ME_DATA_SCREEN         5        //当前屏幕图块
#define ME_DATA_MODEL          6        //3DObject 模型
#define ME_DATA_STANDARD       7        //背景数据
#define ME_DATA_POI            8        //POI数据
#define ME_DATA_VERSION        9        //版本查询数据
#define ME_DATA_INDOOR         10       //室内地图数据
#define ME_DATA_PANORAMA       11       //实景数据
#define ME_DATA_YAML_SOURCE    12       //YAML数据
#define ME_DATA_TILE_SOURCE    13       //栅格数据定义的数据源（3857，900913）
    
#define MAPRENDER_ENTER             0
#define MAPRENDER_BASEMAPBEGIN      1
#define MAPRENDER_BUILDINGBEGIN     2
#define MAPRENDER_LABELSBEGIN       3
#define MAPRENDER_LABELSEND         4
#define MAPRENDER_RENDEROVER        5
//#define MAPRENDER_NOMORENEEDRENDER    6
#define MAPRENDER_ORTHOPROJECTION   7
    
    
#define 	MAPRENDER_CAN_STOP_AND_FULLSCREEN_RENDEROVER    999
#define 	MAPRENDER_CAN_STOP   9999
#define 	MAPRENDER_GRID_CAN_FILL    11

    
#define ME_MAXPOIIDLEN 256
#define ME_MAXLABELTXTLEN   256
#define ME_MAXFONTVERSIONLEN   64
#define ME_MAXFOLDERLEN   256
#define ME_MAX_TILENAMELEN   32        //Tile名称最大长度，之前20级像素坐标长度最大为20，目前改为32
#define ME_MAX_PARAMSTRVALUELEN   64
#define ME_MAX_CAMERAHEADERANGLE   45
    
    typedef unsigned short	me_wchar;
    typedef char	me_char;
    typedef float	me_float;
    typedef int	me_int;
    typedef int	me_color;
    typedef long	me_long;
    typedef unsigned char	me_bool;
    typedef unsigned char	me_uint8;
    typedef unsigned short	me_uint16;
    typedef char	me_int8;
    typedef double me_double;
    typedef unsigned long long me_u_long_long;
    
#define me_true   1
#define me_false   0
    
    // 纹理索引定义
    typedef enum {
        TEXTURE_ICON=0,
        TEXTURE_BACKGROUND=1,
        TEXTURE_ROADARROW=2,
        TEXTURE_ROADROUND=3,
        TEXTURE_TMC_RED=4,    //TMC-拥堵-红
        TEXTURE_TMC_YELLOW=5, //TMC-缓行-黄
        TEXTURE_TMC_GREEN=6,  //TMC-畅通-绿
        TEXTURE_TMC_BLACK=7,  //TMC-严重拥堵-黑红
        TEXTURE_RAILWAY=8,    //就是dash
        TEXTURE_TIANQIAO=9,   //天桥
        TEXTURE_CHANGDUAN=10,  //长短虚线
        
        TEXTURE_GJ_GAOSU_GUIDE_BOARD=11,
        TEXTURE_SHENG_GAOSU_GUIDE_BOARD=12,
        TEXTURE_GUODAO_GUIDE_BOARD=13,
        TEXTURE_SHENGDAO_GUIDE_BOARD=14,
        TEXTURE_XIANDAO_GUIDE_BOARD=15,
        TEXTURE_XIANGDAO_GUIDE_BOARD=16,
        TEXTURE_HK_GAOSU_GUIDE_BOARD=17,
        
        TEXTURE_TMC_GRAY=18,   //TMC-关闭-灰
        
        TEXTURE_SUBWAY_ICON=21,
        
        TEXTURE_ROAD_BOARD_BATCH = 51,  //路牌批量资源
        TEXTURE_TMC_BATCH = 52,         //TMC批量资源
        TEXTURE_ROAD_BATCH = 53,        //道路相关资源
        
    } me_texture_t;
    
#define ME_PARAMETERNAME_PROCESS_BUILDING  1021 //
#define ME_PARAMETERNAME_PROCESS_3DOBJECT  1022
#define ME_PARAMETERNAME_PROCESS_LABEL     1024
#define ME_PARAMETERNAME_FORCE_NAVI_LABEL  1900
#define ME_PARAMETERNAME_TRAFFIC           2010
#define ME_PARAMETERNAME_SATELLITE         2011  //卫星图控制参数
#define ME_PARAMETERNAME_PANORAMA          2013  //实景图层控制参数
#define ME_PARAMETERNAME_TILE_MAP          2015  //栅格地图（目前支持：900913 4326）
#define ME_PARAMETERNAME_HIDE_VECTOR_MAP   2030  //隐藏自有矢量图层（只展示栅格）
//当外部通过控制绘制循环来改变FPS时, 请设置最大FPS以保证文字显示等动画的效果. pIntValue1 = maxfps (0~60), 默认是60
#define ME_PARAMETERNAME_SET_TMCCOLOR      2202  //设置TMC颜色
#define ME_PARAMETERNAME_MAXFPS            2301
#define	ME_PARAMETERNAME_NIGHT             2401
#define ME_PARAMETERNAME_ON_OFF_ASYN_TASK  2501 //停止或者启动后台线程
#define ME_PARAMETERNAME_ON_OFF_DBLITE     2601 //停止或启动读写数据库
#define ME_PARAMETERNAME_CACHE             2602 //保存在线缓存索引文件
#define ME_PARAMETERNAME_HALF_LEVEL_ZOOM   4001 //半级缩放
#define ME_PARAMETERNAME_NETWORK           5001 //设置网络状态
#define ME_PARAMETERNAME_OFFLINE           8002 //设置SDK是否是离线应用
#define ME_PARAMETERNAME_PROFESSIONAL      8003 //开通专业版功能
#define ME_PARAMETERNAME_UNIT              8004 //是否显示单元区域以及点
#define ME_PARAMETERNAME_WAYBILL_COUNT     8005 //是否显示工单件量
#define ME_PARAMETERNAME_AOI_BOUNDS        8006 //是否显示AOI区域
    
    // 投影类型
    typedef enum _me_projection_type {
        me_projection_type_mercator = 0,
        me_projection_type_g4326 = 1
    }me_projection_type;
    
    typedef struct me_parameter_struct
    {
        me_int pIntValue1;
        me_int pIntValue2;
        me_int pIntValue3;
        me_int pIntValue4;
        me_char pStrValue1[ME_MAX_PARAMSTRVALUELEN];
        me_char pStrValue2[ME_MAX_PARAMSTRVALUELEN];
    }me_parameter;
    
    typedef struct me_mapenv_struct
    {
        me_char mapdatapath[ME_MAXFOLDERLEN];
        me_char fontversion[ME_MAXFONTVERSIONLEN];
    }me_mapenv;
    
    
    
    typedef struct me_maptile_struct
    {
        me_char sName[ME_MAX_TILENAMELEN];
    }me_maptile;
    
    typedef struct me_mappoi_struct
    {
        me_int winx;
        me_int winy;
        me_int mapx;
        me_int mapy;
        me_int iconXmin,iconXmax,iconYmin,iconYmax;
        //me_u_long_long poiid;
        me_char poiid[ME_MAXPOIIDLEN];
        me_wchar name[ME_MAX_PARAMSTRVALUELEN];
        me_uint8 nameLen;
        
    }me_mappoi;
    
    //自定义图层结构
    typedef struct me_custom_layer_struct
    {
        me_int     layerId;        //图层唯一ID
        me_int     minZoomLevel;   //最小显示级别（3-22，不在范围，设置为3）
        me_int     maxZoomLevel;   //最大显示级别（3-22，不在范围，设置为22）
        me_bool    isNeedCached;   //是否需要缓存（TMC，不需要缓存）
        me_bool    isTransparent;  //是否是透明图层（实景需要透明）
    }me_custom_layer;
    
    typedef void* me_mapengine;
    typedef void* me_projection;
    
    typedef void (*wxmMapCallback_mapcreate)(void* pCallerObj);
    typedef void (*wxmMapCallback_processEvent)(void* pCallerObj);
    typedef void (*wxmMapCallback_render)(void* pCallerObj,me_int renderstate);
    typedef void (*wxmMapCallback_orthorender)(void* pCallerObj,me_projection orthoProjection);
    typedef void (*wxmMapCallback_initmapview)(void* pCallerObj,me_int mapWidth,me_int mapHeight);
    typedef void (*wxmMapCallback_destorymap)(void* pCallerObj);
    typedef void (*wxmMapCallback_mapdatarequired)(void* pCallerObj,me_int datasource,me_maptile* tiles,me_int tileSize);
    typedef void (*wxmMapCallback_labelsrequired)(void* pCallerObj,me_wchar* labels,me_int nSize);
    typedef void (*wxmMapCallback_getasciicharwidths)(void* pCallerObj,me_uint8* pBuffer,me_int nCharFontSize);
    typedef void (*wxmMapCallback_getCharsWidths)(void* pCallerObj,me_wchar* pBuffer,me_int charSize,me_int nCharFontSize ,unsigned char* results);
    typedef void (*wxmMapCallback_referencechanged)(void* pCallerObj,me_char* preGridName,me_char* newGridName);
    typedef void (*wxmMapCallback_clearcache)(void* pCallerObj);
    
    typedef void (*wxmMapCallback_networkactivitychange)(void* pCallerObj,me_bool bActivity);
#if defined(TARGET_OS_IPHONE)
    typedef void (*wxmMapCallback_downloaddata)(void* pCallerObj,me_int downloadState,me_char* pUrlHash,me_long nDataSize,void* pError);
#else
    typedef void (*wxmMapCallback_downloaddata)(void* pCallerObj,me_int downloadState,me_char* pUrlHash,me_long nDataSize);
#endif
    //me_mapengine
    me_mapengine me_mapengine_new(me_mapenv* mapenv,me_projection_type type);
    
    void me_mapengine_set_styledata(me_mapengine mapengine,me_uint8* pbuffer,me_int datalen,me_int styleType);
    
    void me_mapengine_set_internaltexture(me_mapengine mapengine,me_uint8* pbuffer,me_int datalen,me_texture_t textureType);
    
    void me_mapengine_destroy(me_mapengine mapengine);
    
    void me_mapengine_surface_create(me_mapengine mapengine);
    
    void me_mapengine_surface_rendermap(me_mapengine mapengine);
    
    void me_mapengine_surface_initmap(me_mapengine mapengine,me_int width,me_int height);
    
    void me_mapengine_set_mapstate(me_mapengine mapengine,me_projection projection);
    
    me_projection me_mapengine_get_mapstate(me_mapengine mapengine);
    
    void me_mapengine_setparameter(me_mapengine mapengine,me_int paramName,me_parameter* parameter);
    
    me_uint8* me_mapengine_get_asciiwidths(me_mapengine mapengine);
    me_mappoi*  me_mapengine_selectmappois(me_mapengine mapengine,me_int winx,me_int winy,me_int radius,me_int* selectedSize);
    
    me_int me_mapengine_putmapdata(me_mapengine mapengine,me_int datatype,me_uint8* pBuffer,me_int asize);
    
    me_int me_mapengine_putcharbitmap(me_mapengine mapengine,me_wchar wch,me_uint8* pBuffer);
    
    
    void me_mapengine_setcitybound(me_mapengine mapengine,me_uint8* pbuffer,me_int datalen);
    
    me_bool me_mapengine_canStopMapRender(me_mapengine mapengine);
    
    void me_mapengine_changeMapEnv(me_mapengine mapengine,me_mapenv* mapenv);
    
    //mapengine call back
    void me_mapengine_set_fn_mapcreate(me_mapengine mapengine,wxmMapCallback_mapcreate func,void* pCallObj);
    
    void me_mapengine_set_fn_processevent(me_mapengine mapengine,wxmMapCallback_processEvent func,void* pCallObj);
    
    void me_mapengine_set_fn_renderer(me_mapengine mapengine,wxmMapCallback_render func,void* pCallObj);
    
    void me_mapengine_set_fn_orthorender(me_mapengine mapengine,wxmMapCallback_orthorender func,void* pCallObj);
    
    void me_mapengine_set_fn_initmapview(me_mapengine mapengine,wxmMapCallback_initmapview func,void* pCallObj);
    
    void me_mapengine_set_fn_destorymap(me_mapengine mapengine,wxmMapCallback_destorymap func,void* pCallObj);
    
    void me_mapengine_set_fn_mapdatarequired(me_mapengine mapengine,wxmMapCallback_mapdatarequired func,void* pCallObj);
    
    void me_mapengine_set_fn_labelsrequired(me_mapengine mapengine,wxmMapCallback_labelsrequired func,void* pCallObj);
    
    void me_mapengine_set_fn_getasciicharwidths(me_mapengine mapengine,wxmMapCallback_getasciicharwidths func,void* pCallObj);
    
    void me_mapengine_set_fn_getCharsWidth(me_mapengine mapengine,wxmMapCallback_getCharsWidths func,void* pCallObj);
    
    void me_mapengine_set_fn_referencechanged(me_mapengine mapengine,wxmMapCallback_referencechanged func,void* pCallObj);
    
    void me_mapengine_set_fn_networkactivitychange(me_mapengine mapengine, wxmMapCallback_networkactivitychange func, void* pCallObj);
    
    void me_mapengine_set_fn_downloaddata(me_mapengine mapengine, wxmMapCallback_downloaddata func, void* pCallObj);
    
    void me_mapengine_set_fn_clearcache(me_mapengine mapengine,wxmMapCallback_clearcache func,void* pCallObj);
    
    //me_projection
    
    
    me_projection me_projection_create(me_mapengine mapengine);
    
    void me_projection_destroy(me_projection projection);
    
    void me_projection_get_bound(me_projection projection,me_int* width,me_int* height);
    
    void me_projection_get_geocenter(me_projection projection,me_int* x,me_int* y);
    
    void me_projection_set_geocenter(me_projection projection,me_int x,me_int y);
    
    void me_projection_get_mapcenter(me_projection projection,me_float* fx,me_float* fy);
    
    void me_projection_set_mapcenter(me_projection projection,me_float fx,me_float fy);
    
    me_float me_projection_get_mapzoomermax();
    
    me_float me_projection_get_mapzoomermin();
    
    me_float me_projection_get_mapzoomer(me_projection projection);
    
    void me_projection_set_mapzoomer(me_projection projection,me_float zoomer);
    
    me_float me_projection_get_mapangle(me_projection projection);
    
    void me_projection_set_mapangle(me_projection projection,me_float angle);
    
    me_float me_projection_get_cameraHeaderAngle(me_projection projection);
    
    void me_projection_set_cameraHeaderAngle(me_projection projection,me_float angle);
    
    void me_projection_geo2map(me_projection projection,me_int pixel20X,me_int pixel20Y,me_float* fx,me_float* fy);
    
    void me_projection_map2win(me_projection projection,me_float mapx,me_float mapy,me_double* winx,me_double* winy);
    
    void me_projection_win2map(me_projection projection,me_double winx,me_double winy,me_float* mapx,me_float* mapy);
    
    me_float me_projection_get_mapLenWithWinbyY(me_projection projection,me_int WinPixelLen,me_int winY);
    
    me_float me_projection_get_mapLenWithWin(me_projection projection,me_int WinPixelLen);
    
    me_float me_projection_get_geoLenWithWin(me_projection projection,me_int WinPixelLen);
    
    me_float me_projection_get_mapLenWithGeo(me_projection projection,me_int GeoPixelLen);
    
    void me_projection_map2geo(me_projection projection,me_float mapx,me_float mapy,me_int* geox,me_int* geoy);
    
    void me_projection_setcenter_withmap(me_projection projection,me_float mapx,me_float mapy);
    
    void me_projection_getcenter_map(me_projection projection,me_float* mapx,me_float* mapy);
    
    void me_projection_lonlat2geo(me_double lon,me_double lat,me_int* px,me_int* py,me_projection_type type);
    
    void me_projection_geo2lonlat(me_int px,me_int py,me_double* lon,me_double* lat,me_projection_type type);
    
    void me_projection_get_cameraInfo(me_projection projection, me_float cameraFrom[3], me_float cameraTo[3], me_float cameraUp[3]);
    
    me_float* me_projection_get_viewMatrix(me_projection projection);
    
    me_float* me_projection_get_projectionMatrix(me_projection projection);
    
    void me_projection_recalculate(me_projection projection);
    
    // add param datasource to func,let usr to choose which type of data to get tiles info
    void me_mapengine_get_screentiles(me_mapengine,me_uint8* pBuffer,int datasource);
    
    // utils
    void me_util_quadKey2tile(char* quadKey,int *x,int *y, int *level,me_projection_type type);
    void me_util_tile2quardkey(int x,int y, int level,me_projection_type type, char *quadKey);
    
    // custom layer operation
    me_custom_layer *me_mapengine_create_customlayer_withid(me_int layerId);
    
    void me_mapengine_delete_customlayer(me_custom_layer *customLayer);
    
    me_bool me_mapengine_add_customlayer(me_mapengine mapengine, me_custom_layer *customLayer);
    
    me_bool me_mapengine_remove_customlayer(me_mapengine mapengine, me_int layerId);
    
#ifdef __cplusplus
}
#endif

#endif /* def _WXMAPCORE_API_H_INCLUDED_ */
