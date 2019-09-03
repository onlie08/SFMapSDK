//
//  LMKOverlay.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKAnnotation.h"
#import "LMKGeometry.h"

/*!
 @brief 该类是地图覆盖物的基类，所有地图的覆盖物需要继承自此类
 */
@protocol LMKOverlay <LMKAnnotation>
@required

/*!
 @brief 返回区域中心坐标.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/*!
 @brief 区域外接矩形
 */
@property (nonatomic, readonly) LMKMapRect boundingMapRect;

@end
