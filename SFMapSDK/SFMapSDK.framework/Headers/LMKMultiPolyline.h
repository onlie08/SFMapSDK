//
//  LMKMultiPolyline.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKPolyline.h"

/*!
 @brief 此类用于定义一个由多个点相连的多段线，绘制时支持分段采用不同颜色（纹理）绘制，点与点之间尾部相连但第一点与最后一个点不相连
 */
@interface LMKMultiPolyline : LMKPolyline

/*!
 @brief 绘制索引数组(纹理、颜色索引数组), 成员为NSNumber, 且为非负数
 */
@property (nonatomic, strong, readonly) NSArray *drawStyleIndexes;

/*!
 @brief 分段绘制，根据经纬度坐标数据生成多段线
 
 @param coords 指定的经纬度坐标点数组
 @param count 坐标点的个数
 @param drawStyleIndexes 纹理索引数组(颜色索引数组), 成员为NSNumber, 且为非负数
 @return 生成的折线对象
 */
+ (instancetype)polylineWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count drawStyleIndexes:(NSArray*) drawStyleIndexes;

@end

