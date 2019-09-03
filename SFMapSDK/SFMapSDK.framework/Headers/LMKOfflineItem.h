//
//  LMKOfflineItem.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, LMKOfflineItemStatus) {
    LMKOfflineItemStatusNone = 0,  /* 不存在. */
    LMKOfflineItemStatusInstalled, /* 已安装. */
    LMKOfflineItemStatusCached,    /* 缓存状态. */
    LMKOfflineItemStatusExpireds   /* 已过期. */

};

typedef NS_ENUM(NSInteger, LMKOfflineDeleteType) {
    LMKOfflineItemAll,  /* 删除该item对应的所有离线地图文件。 */
    LMKOfflineItemZip,  /* 删除该item对应的后缀名为.zip的离线地图文件。 */
    LMKOfflineItemDat,  /* 删除该item对应的后缀名为.dat的离线地图文件，该文件为zip包解压后所得。 */
    
};

/*!
 @brief 该类是离线地图模型的基类
 */
@interface LMKOfflineItem : NSObject<NSCoding,NSCopying>

/*!
 @brief 名字
 */
@property (nonatomic, copy, readwrite) NSString* name;

/*!
 @brief 简拼
 */
@property (nonatomic, copy, readwrite) NSString* jianpin;

/*!
 @brief 拼音
 */
@property (nonatomic, copy, readwrite) NSString* pinyin;

/*!
 @brief 区域编码
 */
@property (nonatomic, copy, readwrite) NSString* adcode;

/*!
 @brief 离线数据大小
 */
@property (nonatomic, assign, readwrite) long long size;

/*!
 @brief 状态
 */
@property (nonatomic, assign, readwrite) LMKOfflineItemStatus itemStatus;

/*!
 @brief 已下载大小(当itemStatus == LMKOfflineItemStatusCached 时有效)
 */
@property (nonatomic, assign, readwrite) long long downloadedSize;

/*!
 @brief 下载地址
 */
@property (nonatomic, copy, readwrite) NSString* url;

/*!
 @brief 城市编码
 */
@property (nonatomic, copy, readwrite) NSString* citycode;

/*!
 @brief 版本号
 */
@property (nonatomic, copy, readwrite) NSString* version;

/*!
 @brief MD5编码
 */
@property (nonatomic, copy, readwrite) NSString* md5;
/*!
 @brief 备用标识符，用户可根据需求确定是否使用
 */
@property (nonatomic, assign) BOOL itemChecked;
/*!
 @brief LMKOfflineItem初始化方法
 @param adcode         区域编码
 @param name           城市名称
 @param url            下载地址
 @param citycode       城市编码
 @param jianpin        简拼
 @param pinyin         拼音
 @param version        版本号
 @param size           离线数据大小
 @param md5            MD5编码
 @param status         状态
 @param downloadedSize 已下载大小
 @return 初始化后的LMKOfflineItem
 */
- (id)initWithAdCode:(NSString*)adcode
            cityName:(NSString*)name
           urlString:(NSString*)url
            cityCode:(NSString*)citycode
             jianPin:(NSString*)jianpin
              pinYin:(NSString*)pinyin
             version:(NSString*)version
                size:(long long)size
                 MD5:(NSString*)md5
          itemStatus:(LMKOfflineItemStatus)status
      downloadedSize:(long long)downloadedSize;


@end
