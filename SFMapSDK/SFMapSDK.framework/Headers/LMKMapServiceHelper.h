//
//  LMKMapServiceHelper.h
//  SFMapSDK
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2018/12/20.
//  Copyright © 2018年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @brief 服务配置
 */
@interface LMKMapServiceConfig : NSObject

/*!
 @brief 数据源
 */
@property (nonatomic, copy) NSString *urlHost;

/*!
 @brief apiKey
 */
@property (nonatomic, copy) NSString *apiKey;

/*!
 @brief appCerSha1
 */
@property (nonatomic, copy) NSString *appCerSha1;

/*!
 @brief 配置创建
 */
+ (instancetype)configWithUrlHost:(NSString *)urlHost
                           apiKey:(NSString *)apiKey
                       appCerSha1:(NSString *)appCerSha1;

@end

@interface LMKMapServiceHelper : NSObject

/*!
 @brief 数据源
 */
@property (nonatomic, copy) NSString *mapDataUrl;

/*!
 @brief 路况源
 */
@property (nonatomic, copy) NSString *tmcUrl;

/*!
 @brief 地理编码url
 */
@property (nonatomic, copy) NSString *geoUrl;

/*!
 @brief 逆地理编码url
 */
@property (nonatomic, copy) NSString *rgeoUrl;

/*!
 @brief LMKMapServices单例构造方法
 */
+ (instancetype)shared;

/*!
 @brief 获取url加密类型
 */
+ (int)getUrlEncryptTypeWithUrl:(NSString *)url;

/*!
 @brief 添加配置（重复的进行覆盖）
 @param config 配置model
 */
- (void)addConfig:(LMKMapServiceConfig *)config;

/*!
 @brief 获取配置
 @param url 请求地址
 @return 返回参数：配置
 */
- (LMKMapServiceConfig *)getConfigWithUrl:(NSString *)url;

/*!
 @brief 加密
 @param url 请求地址
 @param param 要加密的参数
 @return 返回参数：加密后的字典
 */
- (NSDictionary *)getEncryptRequestParamByUrl:(NSString *)url
                                        param:(NSDictionary *)param;
/*!
 @brief 加密
 @param url 请求地址
 @param param 要加密的参数
 @return 返回参数：加密后的字典json
 */
- (NSString *)getEncryptRequestParamStrByUrl:(NSString *)url
                                       param:(NSDictionary *)param;

@end
