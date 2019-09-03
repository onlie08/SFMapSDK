//
//  LMKMarker.h
//  SFMapSDK
//
//  Created by sfmap on 16/10/12.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <SFMapFoundation/SFMapFoundation.h>

// 区别于annotation，使用OpenGL绘制，不是view，没有弹出气泡
@interface LMKMarker : NSObject

@property (nonatomic, assign) CLLocationCoordinate2D location;
@property (nonatomic, copy)   NSString *markerIdentifier;
@property (nonatomic, assign) CGSize overlaySize;
@property (nonatomic, assign) BOOL canBeTouch;
@property (nonatomic, assign) int animateType;

+ (instancetype)createMarkerWithLocation:(CLLocationCoordinate2D)location identifier:(NSString *)identifier overlaySize:(CGSize)overlaySize;

- (LNPoint)LNPointValue;

@end
