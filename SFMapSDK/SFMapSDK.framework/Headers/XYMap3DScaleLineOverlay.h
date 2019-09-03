//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "XYMap3DOverlays.h"
#import "XYMap3DEngine/me_mapapi.h"

@interface XYMap3DScaleLineOverlay : XYMap3DPointOverlay {
    float   _scaleLineBottomPadding;
    float   _scaleLineHorizontalPadding;
    BOOL    _bScaleLineAtLeft;
}
- (instancetype)initWithMap3dView:(XYMap3DView *)map3dView;
- (void)drawOnMap:(me_projection)proj;

@property (nonatomic, assign) float scaleLineBottomPadding;
@property (nonatomic, assign) float scaleLineHorizontalPadding;
@property (nonatomic, assign) BOOL  bScaleLineAtLeft;

@end
