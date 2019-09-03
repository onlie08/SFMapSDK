//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "XYMap3DEngine/me_mapapi.h"
#import <SFMapFoundation/SFMapFoundation.h>

@class XYMEDMapViewInternal;

typedef enum {
	XYMEDGestureTapZoomIn		= 1,
	XYMEDGestureTapZoomOut		= 2,
	XYMEDGestureMove				= 3,
	XYMEDGesturePinchZoom		= 4,
	XYMEDGestureRotation			= 5,
	XYMEDGestureCameraHeader		= 6,
	XYMEDGestureLongPress		= 7,
	XYMEDGestureSingleTap		= 8,
    XYMEDGestureSingleZoom       = 9,
    XYMEDGestureComposed         = 10,
} XYMEDGestureType;

typedef enum {
    XYMEDMapStateChange       = 1,
    XYMEDMapStateRender          ,
    XYMEDMapStateFininsh         ,
} XYMEDMapState;

@protocol XYMapAnimationDelegate <NSObject>

- (void)animationDidStop;

@end

@class XYMap3DView;
@interface XYMEDCallbackManager : NSObject {
    id<XYMapAnimationDelegate>    _animationDelegat;
    int                         _animationDuration;
    int                         _mapMoveOrZoom;
}

@property (nonatomic, assign) int                      animationDuration;
@property (nonatomic, assign) id<XYMapAnimationDelegate> animationDelegat;
@property (nonatomic, assign) int                      mapMoveOrZoom;
@property (nonatomic, retain) UIView *onMapView;
@property (nonatomic, assign) XYMap3DView *map3dView;

- (void)setCallbackForMapEngine:(me_mapengine)mapEngine;
- (void)setURLAdditionParameters;

- (void)gestureBegin;
- (void)gestureChange:(XYMEDGestureType)gestureType state:(UIGestureRecognizerState)state changeValue:(void *)changeValue;

#ifdef ROTATE_RESET_MACRO
- (void)gestureEnd:(XYMEDGestureType)gestureType;
#else
- (void)gestureEnd;
#endif

- (void)renderMap:(int)state;
- (void)orthoRenderMap:(me_projection)projection;
- (void)referenceChanged:(me_char *)preGrid newGrid:(me_char *)newGrid;

@end
