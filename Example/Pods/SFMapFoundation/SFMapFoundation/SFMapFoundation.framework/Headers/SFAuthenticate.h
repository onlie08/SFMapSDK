//
//  SFAuthenticate.h
//  LeadorMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    kSFFoundationAuthResultNormal,//初始状态
    kSFFoundationAuthResultFailure,//失败
    kSFFoundationAuthResultSuccess,//成功
    kSFFoundationAuthResultTimeOut,//三次鉴权都超时
} kSFFoundationAuthResultType;//鉴权结果的类型

typedef void (^SFFoundationAuthBlock)(kSFFoundationAuthResultType authResultType);

@interface SFAuthenticate : NSObject

/**
*  初始化方法
*
*  @param apiKey        apiKey
*  @param apiVersion    apiVersion SDK | APP version
*  @param publickKeyStr publickKeyStr RSA Key
*  @param paltformStr   platform 平台：MAP_SDK_iOS or Other
*
*  @return SFAuthenticate
*/
- (instancetype)initWithApiVersion:(NSString *)apiVersion publicKey:(NSString *)publickKeyStr platformStr:(NSString *)platform;

/*!
 @brief  发送鉴权请求，异步请求，结果通过completion回调通知
 */
- (void)authenticateWithCompletionBlock:(SFFoundationAuthBlock)completion;

@end
