//
//  SF3DESEncryptUtil.h
//  SFMapFoundation
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2018/8/24.
//  Copyright © 2018年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SFEncryptionHelper.h"

@interface SF3DESEncryptUtil : NSObject

// 加密方法
+ (NSData *)encryptToDataBy:(NSString *)plainText key:(NSString *)key;
//加密成Base64编码
+ (NSString *)encryptToBase64By:(NSString*)plainText key:(NSString *)key;
//加密成16进制字符串
+ (NSString *)encryptToHexBy:(NSString*)plainText key:(NSString *)key;

//解密方法
+ (NSString *)decryptData:(NSData *)encryptData key:(NSString *)key;
// Base64字符串解密方法
+ (NSString *)decryptBase64:(NSString *)encryptText key:(NSString *)key;
// 16进制字符串解密方法
+ (NSString *)decryptHex:(NSString *)hexText key:(NSString *)key;

@end
