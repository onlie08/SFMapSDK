//
//  LMKMultiPoint.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LMKShape.h"
#import "LMKGeometry.h"

/*!
 @brief 该类是个由多个点组成的虚基类, 不能直接实例化对象, 要使用其子类LMKPolyline,LMKPolygon来实例化
 */
@interface LMKMultiPoint : LMKShape {
    @package
    LMKMapPoint *_points;
    NSUInteger _pointCount;
    LMKMapRect _boundingRect;
}

/*!
 @brief 坐标点数组
 */
@property (nonatomic, readonly) LMKMapPoint *points;

/*!
 @brief 坐标点的个数
 */
@property (nonatomic, readonly) NSUInteger pointCount;

/*!
 @brief 将内部的坐标点数据转化为经纬度坐标并拷贝到coords内存中
 @param coords 调用者提供的内存空间, 该空间长度必须大于等于要拷贝的坐标点的个数（range.length）
 @param range 要拷贝的数据范围
 */

- (void)getCoordinates:(CLLocationCoordinate2D *)coords range:(NSRange)range;
/*!
 @brief 初始化坐标和坐标点数
 @param coords 调用者提供的内存空间, 该空间长度必须大于等于要拷贝的坐标点的个数（range.length）
 @param count 坐标的点数
 */
- (id)initWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

@end
