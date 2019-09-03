//
//  LMKPointAnnotation.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <CoreLocation/CLLocation.h>
#import "LMKAnnotation.h"
/*!
 @brief 标注点annotation
 */
@interface LMKPointAnnotation : NSObject <LMKAnnotation>

/*!
 @brief 经纬度
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

/*!
 @brief annotation标题
 */
@property (nonatomic, copy) NSString *title;

/*!
 @brief annotation副标题
 */
@property (nonatomic, copy) NSString *subtitle;

@end

