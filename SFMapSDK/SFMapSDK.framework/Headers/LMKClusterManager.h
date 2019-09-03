//
//  LMKClusterManager.h
//  SFMapSDK
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2018/10/19.
//  Copyright © 2018年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LMKCluster.h"
#import "LMKClusterQuadtree.h"

@interface LMKClusterManager : NSObject

//聚合距离（像素，默认200）
@property (nonatomic, assign) float dpDistance;

@property (nonatomic, assign) float zoomMin;    //最小缩放级别，默认3，设置最小不能超过3
@property (nonatomic, assign) float zoomMax;    //最大缩放级别，默认19，设置最大不能超过21

//塞入数据
- (void)setAnnoDataArray:(NSArray<LMKQuadItem *> *)dataArray;
//清空数据
- (void)clearClusterItems;
//获取地图缩放级别对应的聚合
- (NSArray<LMKCluster *> *)getClusters:(CGFloat)zoomLevel;

@end
