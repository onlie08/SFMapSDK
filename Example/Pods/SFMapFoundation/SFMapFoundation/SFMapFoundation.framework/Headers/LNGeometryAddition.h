//
//  LDNaviKit
//
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "LNGeometry.h"

#ifndef LNGeometryADDITION
#define LNGeometryADDITION

@interface NSValue (NSValueLNGeometryExtensions)

+ (NSValue *)valueWithLNPoint:(LNPoint)point;
+ (NSValue *)valueWithLNSize:(LNSize)size;
+ (NSValue *)valueWithLNRect:(LNRect)rect;

- (LNPoint)LNPointValue;
- (LNSize)LNSizeValue;
- (LNRect)LNRectValue;

@end

#endif	//LNGeometryADDITION
