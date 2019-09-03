//
//  SFFoundationHelper.h
//  SFMapFoundation
//
//  Created by 文宝林(Baolin Wen)-顺丰科技 on 2018/8/10.
//  Copyright © 2018年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SFFoundationHelper : NSObject

//获取设备号
+ (NSString *)getDeviceID;
//获取UUID
+ (NSString *)getUUIDString;

#pragma mark - mobileClient功能接口
//获取加密参数结果
+ (NSString *)getParamEncryptByParams:(NSDictionary *)params
                           appCerSha1:(NSString *)appCerSha1;
+ (NSString *)getParamEncryptByParams:(NSDictionary *)params
                           appCerSha1:(NSString *)appCerSha1
                            isProduct:(BOOL)isProduct;
//获取加密参数最终请求param
+ (NSDictionary *)getEncryptRequestParamByParams:(NSDictionary *)params
                                      appCerSha1:(NSString *)appCerSha1
                                          apiKey:(NSString *)apiKey;
+ (NSDictionary *)getEncryptRequestParamByParams:(NSDictionary *)params
                                      appCerSha1:(NSString *)appCerSha1
                                          apiKey:(NSString *)apiKey
                                       isProduct:(BOOL)isProduct;
//获取加密参数最终请求paramStr（param=xx&ak=xx）
+ (NSString *)getEncryptRequestParamStrByParams:(NSDictionary *)params
                                     appCerSha1:(NSString *)appCerSha1
                                         apiKey:(NSString *)apiKey;
+ (NSString *)getEncryptRequestParamStrByParams:(NSDictionary *)params
                                     appCerSha1:(NSString *)appCerSha1
                                         apiKey:(NSString *)apiKey
                                      isProduct:(BOOL)isProduct;
//获取host
+ (NSString *)getMobileClientUrlHost;
+ (NSString *)getMobileClientUrlHost:(BOOL)isProduct;

@end
