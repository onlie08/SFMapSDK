//
//  LMKCluster.h
//  SFMapSDK
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2018/10/19.
//  Copyright © 2018年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LMKQuadItem.h"

@interface LMKCluster : NSObject

@property (nonatomic, assign) CLLocationCoordinate2D coordinate;
@property (nonatomic, strong) NSMutableArray *clusterAnnotations;
@property (nonatomic, strong) NSMutableArray<LMKQuadItem *> *clusterAnnotationItems;
@property (nonatomic, readonly) NSUInteger size;

@end
