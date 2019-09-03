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

typedef void (*wxmMapCallback_mapcreate)(void* pCallerObj);
typedef void (*wxmMapCallback_processEvent)(void* pCallerObj);
typedef void (*wxmMapCallback_render)(void* pCallerObj,int renderstate);
typedef void (*wxmMapCallback_orthorender)(void* pCallerObj,void* orthoProjection);
typedef void (*wxmMapCallback_initmapview)(void* pCallerObj,int mapWidth,int mapHeight);
typedef void (*wxmMapCallback_destorymap)(void* pCallerObj);
typedef void (*wxmMapCallback_referencechanged)(void* pCallerObj,char* preGridName,char* newGridName);
typedef void (*wxmMapCallback_clearcache)(void* pCallerObj);

#import "WXMBaseView.h"

typedef struct {
/*0*/	UIGestureRecognizerState	state;
/*1*/	CGPoint						location;
/*2*/	CGFloat						scale;
/*3*/	CGFloat						rotation;
/*4*/	CGFloat						velocity_float;
/*5*/	CGPoint						velocity_point;
} LMKMMapCorePlatformGestureInfo;

typedef enum {
	XYMapCorePlatformSingleTapGesture = 1,		/*0, 1*/
	XYMapCorePlatformDoubleTapGesture,			/*0, 1*/
	XYMapCorePlatformZoominTapGesture,			/*0, 1*/
	XYMapCorePlatformZoomoutTapGesture,			/*0*/
	XYMapCorePlatformMoveGesture,				/*0, 1, 5*/
	XYMapCorePlatformZoomGesture,				/*0, 2, 4*/
	XYMapCorePlatformRotationGesture,			/*0, 3, 4*/
	XYMapCorePlatformCameraHeaderGesture,		/*0, 1, 5*/
	XYMapCorePlatformLongpressGesture,			/*0, 1*/
	XYMapCorePlatformSingleZoomGesture			/*0, 2*/
} LMKMMapCorePlatformGestureType;

@class XYMMapPlatformView;

@protocol LMKMMapCorePlatformPlugin <NSObject>
#pragma mark init and release Plugin
//- (void)initPluginWithMapEngine:(me_mapengine)mapengine;
/**
 * @brief	获取绘制回调入口
 *
 * @return	返回主绘制回调函数
 */
- (wxmMapCallback_render)renderCallback;

/**
 * @brief	获取正交绘制回调入口
 *
 * @return	返回正交绘制回调函数
 */
- (wxmMapCallback_orthorender)orthoRenderCallback;

/**
 * @brief	获取图块引用变化回调入口
 *
 * @return	返回图块引用变化回调函数
 */
- (wxmMapCallback_referencechanged)referenceChangedCallback;

- (void)initMapState:(void *)projection;
- (void)releasePlugin;

#pragma mark Gestures
/**
 * @brief	默认手势执行前的动作
 *
 * @param	gestureInfo	处理手势所需要的信息, 根据不同类型使用其中的不同成员
 * @param	gestureType	手势类型
 *
 * @return	是否需要继续处理默认手势动作
 */
- (BOOL)actionBeforeGesture:(LMKMMapCorePlatformGestureInfo)gestureInfo gestureType:(LMKMMapCorePlatformGestureType)gestureType;

/**
 * @brief	默认手势执行后的动作
 *
 * @param	gestureInfo	处理手势所需要的信息, 根据不同类型使用其中的不同成员
 * @param	gestureType	手势类型
 */
- (void)actionAfterGesture:(LMKMMapCorePlatformGestureInfo)gestureInfo gestureType:(LMKMMapCorePlatformGestureType)gestureType;

#pragma mark Enter & Exit

- (BOOL)isRendering;
- (BOOL)isPrepareOK;
- (BOOL)needExit;

@end

@class XYMap3DView;
@interface XYMMapPlatformView : UIView<UIGestureRecognizerDelegate>

@property (nonatomic, retain) id<LMKMMapCorePlatformPlugin> defaultPlugin;
@property (nonatomic, assign) XYMap3DView *map3dView;
@property (nonatomic, copy) NSString *styleFileName;//用户设置的style样式文件路径
@property (nonatomic, copy) NSString *iconsFileName;//用户设置的icons样式文件路径

- (id)initWithFrame:(CGRect)frame mapView:(XYMap3DView *)map3dView;
- (void)addPlugin:(id<LMKMMapCorePlatformPlugin>)plugin identifier:(NSString *)identifier;
- (void)removePlugin:(NSString *)identifier;

- (BOOL)canEnterPlugin:(NSString *)identifier;
- (void)enterPlugin:(NSString *)identifier;

- (BOOL)needExitPlugin;
- (void)exitPlugin;

- (void)startRenderMap;
- (void)startRenderMapWhenBecomeActive;
- (void)stopRenderMap;
- (void)stopRenderMapWhenResignActive;
- (void)pauseRender:(BOOL)pause;

- (void)setMaxFPS:(NSUInteger)maxFPS;
- (NSUInteger)maxFPS;
- (NSInteger)increaseAnimationCount;
- (NSInteger)decreaseAnimationCount;


// 手势
- (void)setLongPressDuration:(double)time;

- (void)setScrollEnabled:(BOOL)enabled;
- (void)setZoomEnabled:(BOOL)enabled;
- (void)setRotateEnabled:(BOOL)enabled;
- (void)setCameraEnabled:(BOOL)enabled;
//style and icons setter
- (void)setStyleFileName:(NSString *)styleFileName andIconsFileName:(NSString *)iconsFileName;
@end
