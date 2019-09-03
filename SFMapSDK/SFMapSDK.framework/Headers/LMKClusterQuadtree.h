//
//  LMKClusterQuadtree.h
//  SFMapSDK
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2018/10/19.
//  Copyright © 2018年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LMKQuadItem.h"

@interface LMKClusterQuadtree : NSObject

@property (nonatomic, readonly) CGPoint uuupt;
@property (nonatomic, assign) CLLocationCoordinate2D uuucoordinate;

///四叉树区域
@property (nonatomic, assign) CGRect rect;
///所包含LMKQuadItem
@property(nonatomic, readonly) NSMutableArray *quadItems;
- (id)initWithRect:(CGRect) rect;
///添加item
- (void)addItem:(LMKQuadItem*) quadItem;

///清除items
- (void)clearItems;

///获取rect范围内的LMKQuadItem
- (NSArray*)searchInRect:(CGRect) searchRect;

@end
