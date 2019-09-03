//
//  LMKOfflineProvince.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKOfflineItem.h"

/*!
 @brief 省份
 */
@interface LMKOfflineProvince : LMKOfflineItem

/* 包含的城市数组(都是LMKOfflineItemCommonCity类型). */
@property (nonatomic, strong, readwrite) NSArray *cities;
/* 该省已下载的城市数组，且该数组内的元素不支持下载功能(都是LMKOfflineItemCommonCity类型). */
@property (nonatomic, strong, readwrite) NSMutableArray *downloadedCities;

/*!
 @brief 省份字典转模型的方法
 @param dict 要转换的字典
 @return LMKOfflineProvince类型的对象
 */
+(instancetype)provinceWithDict:(NSDictionary*)dict;

@end
