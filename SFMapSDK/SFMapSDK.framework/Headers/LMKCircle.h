//
//  LMKCircle.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKShape.h"
#import "LMKOverlay.h"
#import "LMKGeometry.h"

/*!
 @brief 该类用于定义一个圆, 通常LMKCircle是LMKCircleView的model
 */
@interface LMKCircle : LMKShape <LMKOverlay> {
    @package
    CLLocationCoordinate2D _coordinate;
    CLLocationDistance _radius;
}

/*!
 @brief 根据中心点和半径生成圆
 @param coord 中心点的经纬度坐标
 @param radius 半径，单位：米
 @return 新生成的圆
 */
-(instancetype)initWithWithCenterCoordinate:(CLLocationCoordinate2D)coord
                                     radius:(CLLocationDistance)radius;

/*!
 @brief 中心点经纬度坐标
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/*!
 @brief 半径，单位：米
 */
@property (nonatomic, readonly) CLLocationDistance radius;

@end
