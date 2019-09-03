//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#import <SFMapFoundation/SFMapFoundation.h>
#import <CoreLocation/CoreLocation.h>
#import "XYMMapPlatform.h"

typedef void* me_mapengine;
typedef void* me_projection;


#define LMKMMapCorePlatformAnimationDidStopNotification		@"LMKMMapCorePlatformAnimationDidStopNotification"
#define LMKMMapCorePlatformAnimationDidFinishNotification @"LMKMMapCorePlatformAnimationDidFinishNotification"
#define MOVEANIMATIONTIME_NORMAL 400
#define MOVEANIMATIONTIME_LONG 500


@interface XYMapPlatformTools : NSObject

@property (nonatomic, assign) XYMMapPlatformView *platfromView;
@property (nonatomic) CGFloat maxZoomInLevel;

- (me_mapengine)getMapEngine;

- (me_projection)getProjection;
- (me_projection)createProjection;
- (void)saveProjection;
- (void)loadProjection;
- (void)destroySavedProjection;
- (void)setProjetionToMapEngine:(me_projection)projection;

- (void)setAnimationDuration:(int)duration; //ms
- (void)mapAngleAnimation:(float)mAngle andCameraAngle:(float)cAngle;
- (void)zoomAnimation:(float)startLevel andEndLevel:(float)endLevel withFixedScreenPos:(CGPoint)pos;
- (void)zoomOutAnimation:(float)startLevel andEndLevel:(float)endLevel;
- (void)zoomAnimation:(float)endLevel withCenterGeoPos:(LNPoint)center;
- (void)zoomAnimation:(float)startLevel andEndLevel:(float)endLevel withFixedScreenPos:(CGPoint)pos withDuration:(double)duration;
- (void)zoomOutAnimation:(float)startLevel andEndLevel:(float)endLevel withDuration:(double)duration;
- (void)zoomAnimation:(float)endLevel withCenterGeoPos:(LNPoint)center withDuration:(double)duration;
- (void)panAnimation:(LNPoint)geoPoint andAngle:(float)angle andHeadAngle:(float)headAngle andLevel:(float)level;
- (void)moveAnimation:(LNPoint)geoPoint withDuration: (double)duration;
- (void)moveAnimation:(LNPoint)geoPoint; // 内部直接调用使用时间参数得moveAnimation接口
- (void)zoomAnimation:(float)endLevel andMapAngle:(float)mAngle andCameraAngle:(float)cAngle;

- (void)stopAnimation;
- (void)stopAnimationWithoutNofity;
- (void)doAnimation;
- (void)finishAnimation;

- (LNPoint)getPixel20Pnt:(CGPoint)screenPnt;

- (void)setMaxFPS:(NSUInteger)maxFPS; // value 0 ~ 60. If value == 0, will call stopRenderMap. For other values, will call startRenderMap if map render is stopped
- (NSUInteger)maxFPS;

- (GLuint)loadTexture:(unsigned char *)textureBuffer dataSize:(int)dataSize textureID:(GLuint *)textureID;

- (void)setMapParameter:(int)paramName parameter:(void*)parameter;

- (void)showBuilding:(BOOL)visible;
- (void)showLabel:(BOOL)visible;
- (void)showSatellite:(BOOL)visible;
- (void)showTraffic:(BOOL)visible;

- (void)pauseRender:(BOOL)pause;

+ (BOOL)isAllGridsRenderOver;

@end
