//
//  LMKOfflineItemCommonCity.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKOfflineItem.h"
#import "LMKOfflineProvince.h"

/*!
 @brief 普通城市
 */
@interface LMKOfflineItemCommonCity : LMKOfflineItem

/*!
 @brief 所属省份
 */
@property (nonatomic, weak) LMKOfflineProvince *province;


@end
