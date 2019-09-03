//
//  LMKOverlayFloor.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKOverlayView.h"
#import "LMKGroundOverlay.h"

/*!
 @brief 此类是将LMKGroundOverlay中的覆盖图片显示在地图上的view;
 */
@interface LMKGroundOverlayView : LMKOverlayView

/*!
 @brief groundOverlay 具有覆盖图片，以及图片覆盖的区域
 */
@property (nonatomic ,readonly) LMKGroundOverlay *groundOverlay;

/*!
 @brief 根据指定的GroundOverlay生成将图片显示在地图上View
 @param groundOverlay 制定了覆盖图片，以及图片的覆盖区域的groundOverlay
 @return 根据GroundOverlay新生成的View
 */
- (id)initWithGroundOverlay:(LMKGroundOverlay *)groundOverlay;

@end
