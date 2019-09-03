//
//  LMKGroundOverlayView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "LMKShape.h"
#import "LMKOverlay.h"

/*!
 @brief 该类用于确定覆盖在地图上的图片，及其覆盖区域, 通常LMKGroundOverlay是LMKGroundOverlayView的model
 */
@interface LMKGroundOverlay : LMKShape<LMKOverlay>

/*!
 @brief 绘制在地图上的覆盖图片
 */
@property (nonatomic, readonly) UIImage *icon;

/*!
 @brief 透明度. 最终透明度 = 纹理透明度 * alpha. 有效范围为[0.f, 1.f], 默认为1.f
 */
@property (nonatomic) CGFloat alpha;

/*!
 @brief 覆盖图片在地图尺寸等同于其像素的zoom值
 */
@property (nonatomic, readonly) CGFloat zoomLevel;

/*!
 @brief 图片在地图中的覆盖范围
 */
@property (nonatomic, readonly) LMKCoordinateBounds bounds;

/*!
 @brief 根据bounds值和icon生成GroundOverlay
 @param bounds 图片的在地图的覆盖范围
 @param icon 覆盖图片
 @return 根据bounds和icon 新生成的GroundOverlay
 */
+ (instancetype)groundOverlayWithBounds:(LMKCoordinateBounds)bounds
                                   icon:(UIImage *)icon;

/*!
 @brief 根据coordinate,icon,zoomLevel生成GroundOverlay
 @param coordinate 图片的在地图上的中心点
 @param zoomLevel 图片在地图尺寸等同于像素的zoom值
 @param icon 覆盖图片
 @return 根据coordinate,icon,zoomLevel 新生成的GroundOverlay
 */
+ (instancetype)groundOverlayWithCoordinate:(CLLocationCoordinate2D)coordinate
                                  zoomLevel:(CGFloat)zoomLevel
                                       icon:(UIImage *)icon;
@end