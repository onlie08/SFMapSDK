//
//  LMKPolyline.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKMultiPoint.h"
#import "LMKOverlay.h"

/*!
 @brief 此类用于定义一个由多个点相连的多段线，点与点之间尾部相连但第一点与最后一个点不相连, 通常LMKPolyline是LMKPolylineView的model
 */
@interface LMKPolyline : LMKMultiPoint <LMKOverlay>

/*!
 @brief 根据经纬度坐标数据生成多段线
 @param coords 经纬度坐标数据,coords对应的内存会拷贝,调用者负责该内存的释放
 @param count 经纬度坐标个数
 @return 生成的多段线
 */
+ (instancetype)polylineWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;


@end
