//
//  LMKArc.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LMKMultiPoint.h"
#import "LMKOverlay.h"

/*!
 @brief 该类用于定义一段弧线, 通常LMKArc是LMKArcView的model
 */
@interface LMKArc : LMKMultiPoint <LMKOverlay>

/*!
 @brief  构建弧线数据的类
 @param  startCoords 起点坐标
 @param  midCoords   中间点坐标
 @param  endCoords   终点坐标
 @return 生成的弧线model
 */
+ (instancetype)arcWithStartCoordinates:(CLLocationCoordinate2D)startCoords
                         midCoordinates:(CLLocationCoordinate2D)midCoords
                         endCoordinates:(CLLocationCoordinate2D)endCoords;

@end
