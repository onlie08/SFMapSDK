//
//  LMKTouchPoi.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface LMKTouchPoi : NSObject

/*!
 @brief id
 */
@property (nonatomic, copy) NSString *poiId;

/*!
 @brief 名称
 */
@property (nonatomic, copy) NSString *name;

/*!
 @brief 经纬度坐标
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end
