//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <SFMapFoundation/SFMapFoundation.h>
#import <QuartzCore/CADisplayLink.h>
#import "XYMap3DDefines.h"
#import "XYMMapPlatform.h"
#import "LMKGeometry.h"
#import "XYMMapPlatformTools.h"
#import "LMKMarker.h"


typedef enum
{
    Day=0,
    Night=1
}
EMapStyle;

typedef enum
{
    Default=0,
    Satellite=1,
    NaviCar=2
}
EMapMode;
typedef enum {
	XYMap3DGestureSingleTap = 0,
	XYMap3DGestureMove,
	XYMap3DGestureSingleZoom,
	XYMap3DGestureTapZoomIn,
	XYMap3DGestureTapZoomOut,
	XYMap3DGestureZoomPinch,
	XYMap3DGestureRotation,
	XYMap3DGestureCamera,
	XYMap3DGestureLongpress,
	XYMap3DGestureFromLeftSwipe,
	XYMap3DGestureFromRightSwipe,
} XYMap3DGestureType;

@protocol XYMap3DViewDelegate;

@class XYMap3DViewInternal, XYMMapResManager, XYMap3DLayerManager, XYMap3DOverlayTextureManager, LDDataProviderManager;

@interface XYMap3DView : UIView <UIAccelerometerDelegate> {
	id<XYMap3DViewDelegate>		_delegate;
}

@property (nonatomic, assign) id<XYMap3DViewDelegate> delegate;
@property (nonatomic, readonly) BOOL additionLog;

@property (nonatomic, retain) XYMMapPlatformView *internal;
@property (nonatomic, retain) XYMapPlatformTools *platformTools;
@property (nonatomic, retain) XYMMapResManager *resManager;
@property (nonatomic, retain) XYMap3DLayerManager *layermanager;
@property (nonatomic, retain) XYMap3DOverlayTextureManager *overlayTextureManager;
@property (nonatomic, retain) LDDataProviderManager *dataProviderManager;

@property (nonatomic, copy) NSString *styleFileName;//用户设置的style样式文件路径
@property (nonatomic, copy) NSString *iconsFileName;//用户设置的icons样式文件路径

@property (nonatomic, assign) int projection_type;

@property (nonatomic, assign) kSFFoundationAuthResultType authResult;

@property (nonatomic, assign) CGFloat maxZoomInLevel;//地图放大最大级别

- (id)initWithFrame:(CGRect)frame andProjectionType:(int)type;

- (void)destroyMapView;
+ (XYMap3DView *)sharedMapView;
//- (void)closeAllMapFileHandle;
//- (void)restoreAllMapFileHandle;
- (BOOL)mapCoreDestoried;

- (void)startRenderMap;
- (void)stopRenderMap;

- (void)setMaxFPS:(NSUInteger)maxFPS; // 0 ~ 60. 为0时,将调用stopRenderMap. 为其他值时, 将调用startRenderMap如果地图停止渲染
- (NSUInteger)maxFPS;
//zoom level
- (void)setZoomLevel:(float)level;
- (float)zoomLevel;

//map center
- (void)setMapCenterWithG20Point:(LNPoint)G20Point;
- (void)setMapCenterWithG20Point:(NSInteger)x y:(NSInteger)y;
- (void)setMapCenterWithScreenPoint:(CGPoint)screenPoint;
- (void)setMapCenterWithScreenPoint:(CGPoint)screenPoint level:(float)level;
- (void)setMapCenterWithScreenPoint:(NSInteger)x y:(NSInteger)y;
- (void)setMapCenterWithScreenPoint:(NSInteger)x y:(NSInteger)y level:(float)level;
- (BOOL)isG20PointInCurScreen:(LNPoint)G20Point;
- (BOOL)isG20PointInCurScreen:(LNPoint)G20Point ScreenRect:(CGRect)rect;

- (void)setMapCenter:(NSInteger)x y:(NSInteger)y level:(float)level;

- (void)setMapCenterWithG20Rect:(LNRect)G20Rect;

- (void)animateToG20Point:(LNPoint)G20Point;
- (void)animateToG20Point:(NSInteger)x y:(NSInteger)y;
- (void)animateToG20Point:(NSInteger)x y:(NSInteger)y withOffsetOfScreen:(NSInteger)offset;
- (void)animateToScreenPoint:(CGPoint)screenPoint;
- (void)animateToScreenPoint:(CGPoint)screenPoint level:(float)level;
- (void)animateToScreenPoint:(NSInteger)x y:(NSInteger)y;
- (void)animateToScreenPoint:(NSInteger)x y:(NSInteger)y level:(float)level;

- (void)animateToG20Point:(NSInteger)x y:(NSInteger)y level:(float)level;
- (void)animateToG20Point:(NSInteger)x y:(NSInteger)y angle:(float)angle level:(float)level;

- (void)setAnimationTime:(NSInteger)ms; //millisecond 10^-3 s.

- (LNPoint)mapCenter;
- (LNPoint)mapCenterWithAvailableMapRect:(NSInteger)x y:(NSInteger)y;
//touchPOI
- (void)setTouchPOIEnabled:(BOOL)touchPOIEnabled;
//map rect
- (LNRect)mapG20Rect;
- (void)setMapG20Rect:(LMKMapRect)G20Rect animated:(BOOL)animated;
- (LNRect)mapG20RectWithAvailableMapRect;
- (void)setAvailableMapRectWithOffsetY:(CGFloat)offsetY height:(CGFloat)height;
- (CGRect)availableMapRect;

- (NSDictionary *)calcMapInfosWithLocations:(NSArray *)locations;
- (NSDictionary *)calcMapInfosWithLocations:(NSArray *)locations mapRect:(CGRect)mapRect;
// mapRect  : max map area, eg: CGRectMake(20, 20, 280, 400);
// mapLevel : key @"mapLevel", NSNumber with float value ()
// mapCenter: key @"mapCenter", NSValue with LNPoint value

- (UIColor *)mapBackgroundColor;

- (CGPoint)getScreenPntBy20Point:(LNPoint)G20Point; //默认加入3D模型计算
- (CGPoint)getScreenPntBy20Point:(LNPoint)G20Point isCalCamera:(BOOL)isCalCamera;
- (CGPoint)getScreenPntBy20Pixel:(int)pixelX pixelY:(int)pixelY;
- (CGPoint)getScreenPntBy20Pixel:(int)pixelX pixelY:(int)pixelY isCalCamera:(BOOL)isCalCamera;
//- (CGPoint)getScreenPntBy20PixelAngle0:(int)pixelX pixelY:(int)pixelY center:(LNPoint)center level:(int)level;
//- (CGPoint)getScreenPntBy20Pixel:(int)pixelX pixelY:(int)pixelY center:(LNPoint)center level:(int)level;
- (LNPoint)getPixel20Pnt:(CGPoint)ascreenPnt cx:(int)cx cy:(int)cy;
- (LNPoint)getPixel20Pnt:(CGPoint)ascreenPnt;

//traffic
- (void)showTraffic:(bool)show;
- (bool)trafficShowing;
//unit
- (void)showUnit:(bool)show pwd:(NSString *)pwd;
- (bool)unitShowing;
//AOI
- (void)showAOIBounds:(bool)show;
- (bool)AOIBoundsShowing;
//水印
- (void)showWatermark:(bool)show mark:(NSString *)mark;
- (BOOL)watermarkShowing;
//Satellite
- (void)showSatellite:(bool)show;
- (bool)satelliteShowing;

- (UIImage *)createMapThumbWithScreenRect:(CGRect)screenRect;

- (void)pushMapStatus;

- (void)popMapStatus; //default without animation
- (void)popMapStatusAnimated:(BOOL)animated; 

- (void)locationTo:(LNPoint)center animated:(BOOL)animated;
- (void)resetMapStatus; //default with animation
- (void)resetMapStatusAnimated:(BOOL)animated;
- (BOOL)mapStatusNeedReset;
- (void)changeMapToSpecial; //default with animation
- (void)changeMapToSpecialAnimated:(BOOL)animated;
- (void)changeMapTo3DNorthFrontAnimated:(BOOL)animated; //只改变视角为3D，地图角为0

- (void)setCameraAngle:(CGFloat)cameraAngle;
- (CGFloat)cameraAngle;
- (void)setMapAngle:(CGFloat)mapAngle;
- (void)setMapAngle:(CGFloat)mapAngle rotateScreenCenter:(CGPoint)rotateScreenCenter;
- (CGFloat)mapAngle;

- (void)setAllowMapDegreeChange:(BOOL)allow;
- (BOOL)isAllowMapDegreeChange;

- (void)setAllowMapRotationChange:(BOOL)allow;
- (BOOL)isAllowMapRotationChange;

- (void)set3DMapMode:(BOOL)mode;
- (BOOL)is3DMapMode;

- (void)setMapNeedOffsetYForNavi:(int)naviOffsetY;
- (void)setMapNeedOffsetXForNavi:(int)naviOffsetX;

- (void)setMapNeedForceDrawLabelForNavi:(BOOL)forceDraw;

- (void)setScaleLineBottomPadding:(NSInteger)padding;
- (void)setScaleLineHorizontalPadding:(NSInteger)padding;
- (void)showScaleLine; // show scale line at left
- (void)showScaleLineAtLeft:(BOOL)left;
- (void)hideScaleLine;



- (void)showCompass;
- (void)hideCompass;
- (void)setCompassScreenPoint:(CGPoint)screenPoint animated:(BOOL)animated;

- (void)showUserLocation:(BOOL)show;

- (void)setNightMode:(BOOL)nightMode;
- (void)setTrafficStyle:(BOOL)normalStyle;
- (void)setTMCColorStyle:(int)style;
- (void)startProfessionalFunctions;
- (void)stopDownloadMapData;
- (void)startDownloadMapData;
- (void)setShowsBlueRoadNet:(BOOL)showsBlueRoadNet;
- (void)setShowTileMap:(BOOL)showsTileMap;
- (void)setHideVectorMap:(BOOL)hideVectorMap;

- (NSArray *)currentGrids;

- (void)enableSwipeGestureRecognizer:(BOOL)enable;
- (void)setSwipeGestureRecoginzeLimit:(CGFloat)limitWidth; // default is 320 (full screen width)
- (void)setSwipeGestureRecognizerLimit:(CGFloat)limitWidth; // default is 320 (full screen width) old one spell incorrect

- (void)setLongPressGestureDuration:(CGFloat)duration; // default is 0.5

- (void)addCustomGesture:(UIGestureRecognizer *)gesture type:(XYMap3DGestureType)type;

- (void)removeAllInternalGesture;
- (void)restoreInternalGesture;

- (int)fps;

- (void)renderWithScreenImage:(BOOL)imageMode;

- (void)closeEngineDB;
- (void)restoreEngineDB;

- (BOOL)firstRenderOver;

//style and icons setter method
- (void)setStyleFileName:(NSString *)styleFileName  andIconsFileName:(NSString *)iconsFileName;

//mapType setter
- (void)setMapType:(int)type;
//maxZoomInLevel
- (void)setMaxZoomInLevel:(CGFloat)maxZoomInLevel;
#pragma mark tools
- (CGPoint)pointForMapPoint:(LMKMapPoint)mapPoint;
- (LMKMapPoint)mapPointForPoint:(CGPoint)point;
//app 所需方法
-(void)setMode:(EMapMode)mode style:(EMapStyle)style;

#pragma mark - XYMap3DView (Marker)

// offset:（默认为（0，0）），(0.5,0)，标示以底部中心点为锚点
- (void)registerMarkerWithTextureImage:(UIImage *)image
                      markerIdentifier:(NSString *)markerIdentifier
                                offset:(CGPoint)offset
                             followMap:(BOOL)followMap;
- (void)unregisterMarkerWithMarkerIdentifier:(NSString *)markerIdentifier;
- (void)addMarker:(LMKMarker *)marker;
- (void)addMarkers:(NSArray *)markersArray;
- (void)removeMarker:(LMKMarker *)marker;
- (void)removeMarkers:(NSArray * )markers;
- (void)addMarker:(LMKMarker *)marker withAnimateType:(int)type;// 0:none; 1:drop  2:grow
- (void)removeMarkersWithIdentifier:(NSString *)markerIdentifier;
- (void)removeAllMarkers;
- (BOOL)touchMarkerAtPoint:(CGPoint)location;

@end

@interface XYMap3DView (ServerSetting)
- (void)setMapServer:(NSString *)mapServer;			//default
@end

@protocol XYMap3DViewDelegate <NSObject>
@optional
// 自定义绘制
- (void)mapViewCustomDrawing;
- (void)mapViewPreRender:(XYMap3DView *)mapView;  //before main render
- (void)mapViewPostRender:(XYMap3DView *)mapView; //after main render
- (void)mapViewRenderOver:(XYMap3DView *)mapView; //render over
- (void)mapViewCenterChanged;
- (void)mapViewZoomOrMoveFinish;
- (void)mapViewAnyTouchInvoked:(XYMap3DView *)mapView;

- (void)mapViewReceiveMoveGesture:(UIPanGestureRecognizer *)gesture;
- (void)mapViewReceiveZoomGesture:(UIGestureRecognizer *)gesture;
- (void)mapViewReceiveRotationGesture:(UIRotationGestureRecognizer *)gesture;
- (void)mapViewReceiveCameraGesture:(UIPanGestureRecognizer *)gesture;
- (void)mapViewReceiveLongPressGesture:(UILongPressGestureRecognizer *)gestureRecognizer;
- (void)mapViewReceiveSingleTapGesture:(CGPoint)location;

- (void)mapViewNetworkActivityChange:(BOOL)downloading;

- (void)mapViewReceiveSwipeGesuture:(BOOL)fromLeft;
- (void)mapViewReceiveLeftRightPanGesuture:(BOOL)fromLeft moveDistance:(CGFloat)moveDistance;

- (void)mapViewdidUpdateUserLocation:(CLLocation *)userLocation;
- (void)touchOnLabel:(NSString*)poiId lableName:(NSString*)labelName location:(LNPoint)location;
- (void)touchOnLines:(NSArray *)lineOverlays;
// marker, 点击了某个marker，回调
- (void)touchOnMarker:(LMKMarker *)marker;

/*!
 @brief 回调栅格取图所需地址，根据回传的数据拼接需要的请求串
 */
- (NSString *)mapViewRequireTileX:(int)tileX tileY:(int)tileY tileZ:(int)tileZ projection:(LMKMapProjectionType)proj;

@end
