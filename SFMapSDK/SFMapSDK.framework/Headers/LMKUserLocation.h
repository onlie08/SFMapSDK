//
//  LMKUserLocation.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLLocation;

/*!
 @brief 定位信息类
 */
@interface LMKUserLocation : NSObject

/*!
 @brief 位置信息，如果用户不允许定位，或者尚未定位成功，则该值为nil
 */
@property (readwrite, nonatomic) CLLocation *location;



@end
