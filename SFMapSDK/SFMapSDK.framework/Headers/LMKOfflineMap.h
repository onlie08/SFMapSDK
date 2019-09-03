//
//  LMKOfflineMap.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKOfflineItemMunicipality.h"
#import "LMKOfflineItemNationWide.h"
#import "LMKOfflineProvince.h"
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, LMKOfflineMapDownloadStatus) {
    LMKOfflineMapDownloadStatusWaiting,///0 : 以插入队列，等待中.
    LMKOfflineMapDownloadStatusStart,///1 : 开始下载.
    LMKOfflineMapDownloadStatusProgress,///2 : 下载过程中.
    LMKOfflineMapDownloadStatusCompleted,///3 : 下载成功.
    LMKOfflineMapDownloadStatusCancelled,///4 : 取消.
    LMKOfflineMapDownloadStatusUnzip,///5 : 解压缩.
    LMKOfflineMapDownloadStatusFinished,///6 : 全部顺利完成.
    LMKOfflineMapDownloadStatusError ///7 : 发生错误.
};///离线下载过程中的状态

/* 当downloadStatus == LMKOfflineMapDownloadStatusProgress 时, info参数是个NSDictionary,
 如下两个key用来获取已下载和总和的数据大小(单位byte), 对应的是NSNumber(long long) 类型.
 当downloadStatus == LMKOfflineMapDownloadStatusError 时, info参数是NSError. */

extern NSString* const LMKOfflineMapDownloadReceivedSizeKey;///已接受的数据大小

extern NSString* const LMKOfflineMapDownloadExpectedSizeKey;///总大小

typedef void (^LMKOfflineMapDownloadBlock)(LMKOfflineItem* downloadItem, LMKOfflineMapDownloadStatus downloadStatus, id info); ///下载过程中的回调block
typedef void (^LMKOfflineMapPauseBlock)(LMKOfflineItem* downloadItem); ///暂停下载后的回调block
typedef void (^LMKOfflineMapDeleteBlock)(LMKOfflineItem* downloadItem); ///删除地图后的回调block
typedef void (^LMKOfflineMapNewestVersionBlock)(BOOL hasNewestVersion); ///自定义地图版本比较完成后的回调block

/*!
 @brief 离线地图
 */
@interface LMKOfflineMap : NSObject

/*!
 @brief 获取LMKOfflineMap 单例
 @return LMKOfflineMap
 */
+ (LMKOfflineMap *)sharedOfflineMap;

/*!
 @brief 省份数组(每个元素均是LMKOfflineProvince类型)
 */
@property (nonatomic, readonly) NSArray* provinces;

/*!
 @brief 直辖市数组(每个元素均是LMKOfflineItemMunicipality类型)
 */
@property (nonatomic, readonly) NSArray* municipalities;

/*!
 @brief 港澳地区数组(每个元素均是LMKOfflineItem类型)
 */
@property (nonatomic, readonly) NSArray* specialCities;

/*!
 @brief 全国概要图
 */
@property (nonatomic, readonly) LMKOfflineItemNationWide* nationWide;

/*!
 @brief 城市数组, 包括普通城市与直辖市.
 */
@property (nonatomic, readonly) NSArray* cities;

/*!
 @brief 离线数据的版本号(由年月日组成, 如@"20130715")
 */
@property (nonatomic, copy) NSString* version;

/*!
 @brief 启动下载
 @param item 数据
 @param downloadBlock 下载过程block
 */
- (void)downloadItem:(LMKOfflineItem *)item downloadBlock:(LMKOfflineMapDownloadBlock)downloadBlock;

/*!
 @brief 监测是否正在下载
 @param item 条目
 @return 是否在下载
 */
- (BOOL)isDownloadingForItem:(LMKOfflineItem *)item;

/*!
 @brief 暂停下载
 @param item 条目
 @param pauseBlock 暂停后的作为回调的block
 */
- (void)pauseItem:(LMKOfflineItem *)item pauseBlock:(LMKOfflineMapPauseBlock)pauseBlock;

/*!
 @brief 删除item对应离线地图数据
 @param item 条目
 @param deleteType 要删除的文件类型
 @param deleteBlock 删除离线地图文件后的回调
 */
- (void)deleteItem:(LMKOfflineItem *)item type:(LMKOfflineDeleteType)deleteType deleteBlock:(LMKOfflineMapDeleteBlock)deleteBlock;

/*!
 @brief 取消全部下载
 */
- (void)cancelAll;

/*!
 @brief 清除所有在磁盘上的离线地图数据
 */
- (void)clearCache;

/*!
 @brief 监测新版本
 @param newestVersionBlock 回调block
 */
- (void)checkNewestVersion:(LMKOfflineMapNewestVersionBlock)newestVersionBlock;

@end
