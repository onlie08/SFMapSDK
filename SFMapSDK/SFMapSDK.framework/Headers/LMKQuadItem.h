//
//  LMKQuadItem.h
//  SFMapSDK
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2018/12/20.
//  Copyright © 2018年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreGraphics/CoreGraphics.h>

@interface LMKQuadItem : NSObject

@property (nonatomic, readonly) CGPoint pt;
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end
