//
//  LMKMapServices.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @brief 地图服务类
 */
@interface LMKMapServices : NSObject

/*!
 @brief SDK版本号
 */
@property (nonatomic, copy) NSString *SDKVersion;

/*!
 @brief apiKey
 */
@property (nonatomic, copy) NSString *apiKey;

#pragma mark - 方法
/*!
 @brief LMKMapServices单例构造方法
 */
+ (instancetype)sharedServices;

@end
