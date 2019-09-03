//
//  LMKTileOverlay.h
//  SFMapSDK
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/2/13.
//  Copyright © 2019年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LMKOverlay.h"
#import "LMKMarker.h"

#define LMKTileOverlayCacheName @"SFMAP_LMKTileOverlayView"

typedef struct {
    NSInteger x;
    NSInteger y;
    NSInteger z;
    CGFloat contentScaleFactor;
} LMKTileOverlayPath;

//单个瓦片
@interface LMKImageTile : LMKMarker {
    LMKMapRect frame;
}

@property (nonatomic, assign, readonly) LMKMapRect frame;
@property (nonatomic, assign) NSUInteger urlHash;
@property (nonatomic, assign) CLLocationCoordinate2D ltCoor;    //左上
@property (nonatomic, assign) CLLocationCoordinate2D rbCoor;    //右下
@property (nonatomic, assign) LNPoint ltPoint;    //左上
@property (nonatomic, assign) LNPoint rbPoint;    //右下
@property (nonatomic, copy) NSURL *url;

- (instancetype)initWithFrame:(LMKMapRect)frame;

@end

/*!
 @brief 该类是覆盖在球面墨卡托投影上的图片tiles的数据源
 */
@interface LMKTileOverlay : NSObject<LMKOverlay>


// @param URLTemplate是一个包含"{x}","{y}","{z}","{scale}"的字符串,"{x}","{y}","{z}","{scale}"会被tile path的值所替换，并生成用来加载tile图片数据的URL 。例如： http://server/path?x={x}&y={y}&z={z}&scale={scale}。暂不支持
///*!
// @brief 根据指定的URLTemplate生成tileOverlay
// @param URLTemplate是一个包含"{bbox}"的字符串，包括两角经纬度点,"{bbox}"会被tile path的值所替换，并生成用来加载tile图片数据的URL 。例如： http://server/path?bbox={bbox}，例如bbox=114.43359374999935,30.453409130203877,114.4363403320306,30.455776769375138。
// @return 以指定的URLTemplate字符串生成tileOverlay
// */
- (instancetype)initWithURLTemplate:(NSString *)URLTemplate;

/*!
 @brief 默认tileSize 256x256
 */
@property (nonatomic, assign) CGSize tileSize;
//
/////*!
//// @brief overlay可以渲染的最大/最小缩放级别。当0级时，一个tile覆盖整个世界范围，1级时覆盖 1/4th 世界，2级时1/16th，以此类推。
//// */
@property (nonatomic, assign)NSInteger minimumZ;
@property (nonatomic, assign)NSInteger maximumZ;

@property (nonatomic, readonly) NSString *URLTemplate;

///*!
// @brief 区域外接矩形，可用来设定tileOverlay的可渲染区域
// */
@property (nonatomic, assign) LMKMapRect boundingMapRect;

/*!
 @brief 清除所有缓存
 */
+ (void)removeAllTileCache;

@end

/*!
 @brief 记录某特定tile的据结构。contentScaleFactor根据设备的ScrennScale而定, 为1.0或2.0。
 */
//
///*!
// @brief 子类可覆盖CustomLoading中的方法来自定义加载MATileOverlay的行为。
// */
//@interface LMKTileOverlay (CustomLoading)
//
///*!
// @brief 以tile path生成URL。用于加载tile, 此方法默认填充URLTemplate
// @param tile path
// @return path相应的url
// */
//- (NSURL *)URLForTilePath:(LMKTileOverlayPath)path;
//
///*!
// @brief 加载被请求的tile, 并以tile数据或加载tile失败error访问回调block; 默认实现为首先用 -URLForTilePath 去获取URL, 然后用异步NSURLConnection加载tile数据。当绘制大面积的tileOverlay时，建议重写此函数并实现缓存机制。
// @param tile path
// @param 用来传入tile数据或加载tile失败的error访问的回调block
// */
//- (void)loadTileAtPath:(LMKTileOverlayPath)path result:(void (^)(NSData *tileData, NSError *error))result;
//
//@end
