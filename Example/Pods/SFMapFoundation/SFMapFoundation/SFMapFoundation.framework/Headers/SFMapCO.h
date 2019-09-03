//
//  SFMapCO.h
//  SFMapFoundation
//
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SFMapCO : NSObject

+(SFMapCO *)sharedSFMapCO;

//- (int)sfCOX:(double)x Y:(double)y A:(double *)a B:(double *)b;
//- (int)sfDeCOX:(double)x Y:(double)y A:(double *)a B:(double *)b;

//添加参数含义明确的转换公式
- (int)sfCOLat:(double)lat lng:(double)lng outLat:(double *)outLat outLng:(double *)outLng;
- (int)sfDeCOLat:(double)lat lng:(double)lng outLat:(double *)outLat outLng:(double *)outLng;

@end
