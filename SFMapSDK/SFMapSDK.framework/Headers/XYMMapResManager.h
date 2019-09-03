//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XYMGetMapDataTaskManager.h"

#define STYLE_DATA_UPDATE_OVER		@"style_data_update_over"
#define ICONS_DATA_UPDATE_OVER		@"icons_data_update_over"

typedef int AStyleDataType;
#define STYLE_DATA		1
#define ICONS_DATA		2

typedef enum {
    EStyleStateStyleDayState = 0,
    EStyleStateStyleNightState = 1,
    EStyleStateStyleStiState = 2,
    EStyleStateStyleNaviDayState = 3,
    EStyleStateStyleNaviNightState = 4,
    EStyleStateStyleDIYDayState = 5,
    EStyleStateIconDayState = 6,
    EStyleStateIconNightState = 7,
    EStyleStateStateCount = 8,
} StyleState;

#define LDNAVI_DATA_PATH_NAME  @"LDNavi/data"
#define SFMAP_PATH_NAME  @"sfmap"
#define MAP_OFFLIINE_DATA_PATH_NAME  @"off"
#define MAP_CACHE_DATA_PATH_NAME  @"cache"
#define MAP_ONLINE_RES_PATH_NAME  @"res"
#define MAP_ONLINE_TILES_PATH_NAME  @"buff"
#define MAP_UPDATE_RECORD_FILE_NAME  @"style-icons-upate-recorder.data"
#define MAP_OFFLINE_SATELLITE_DATA_PATH_NAME  @"sati"

//#define LDNAVI_DATA_PATH_NAME  @"LDNavi/data"
//#define SFMAP_PATH_NAME  @"sfmap"
//#define MAP_OFFLIINE_DATA_PATH_NAME  @"vmap"
//#define MAP_CACHE_DATA_PATH_NAME  @"cache"
//#define MAP_ONLINE_RES_PATH_NAME  @"vmap4res"
//#define MAP_ONLINE_TILES_PATH_NAME  @"vmap4tiles"
//#define MAP_UPDATE_RECORD_FILE_NAME  @"style-icons-upate-recorder.data"
//#define MAP_OFFLINE_SATELLITE_DATA_PATH_NAME  @"sati"


#ifdef DEBUG
//# define DebugLog(fmt, ...) NSLog((@"\n[文件名:%s]\n""[函数名:%s]\n""[行号:%d] \n" fmt), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);
//#define DebugLog(fmt, ...) NSLog((@"\n     [函数名:%s] [行号:%d] " fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__);
#define DebugLog(...);
#else
#define DebugLog(...);
#endif

@interface XYMMapResManager : NSObject

@property (nonatomic, retain) XYMGetMapDataTaskManager *getMapdataTaskManager;

#ifdef TEST_CHANPIN
- (void)reInit; //测试使用
#endif

 //ldnavi/data
- (NSString *)getBaseMapPath;

 //ldnavi/data
- (const char *)getBaseMapCharPath;
//ldnavi/data/cache
- (NSString *)getMapDataCache; //cache
//ldnavi/data/cache/vmap4tiles
- (NSString *)getMapDataOnlinePath;
 //ldnavi/data/vmap
- (NSString *)getMapDataOfflinePath;
//ldnavi/data/cache/vmap4res
- (NSString *)getExtResPath;

- (const char *)getVmap4Bundle;

- (NSData*) getStyleData:(NSString*)defFileName checkUpdate:(BOOL)checkUpdate;

- (NSData*) getIconsData:(NSString*)defFileName checkUpdate:(BOOL)checkUpdate;

- (NSData*) getOtherResData:(NSString*)defFileName;

- (NSData*) getOtherResData:(NSString*)fileNameFormat nightMode:(BOOL)nightMode;

- (void)addTimeKey:(NSString*)fileName;

- (NSData*) getStyleData:(EMapMode)mode  style:(EMapStyle)style;
- (NSData*) getStyleDataWithState:(StyleState)state;
- (NSData*) getStyleData:(BOOL)nightMode;
- (NSData*) getStiStyleData;
- (NSData*) getIconsDataWithState:(StyleState)state;
- (NSData*) getIconsData:(BOOL)nightMode;
- (NSData*) getIconsDataWithMode:(EMapMode)mode  style:(EMapStyle)style;
-(void)deleteSingleExtData:(NSString*)fileName;

//- (void)start;
@end
