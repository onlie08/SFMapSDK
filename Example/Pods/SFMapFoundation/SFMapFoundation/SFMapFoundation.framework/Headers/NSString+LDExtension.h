//
//  NSString+LDExtension.h
//  LDExtensionExample
//
//  Created by LD Lee on 15/6/7.
//  Copyright (c) 2015年 小码哥. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LDExtensionConst.h"

@interface NSString (LDExtension)
/**
 *  驼峰转下划线（loveYou -> love_you）
 */
- (NSString *)LD_underlineFromCamel;
/**
 *  下划线转驼峰（love_you -> loveYou）
 */
- (NSString *)LD_camelFromUnderline;
/**
 * 首字母变大写
 */
- (NSString *)LD_firstCharUpper;
/**
 * 首字母变小写
 */
- (NSString *)LD_firstCharLower;

- (BOOL)LD_isPureInt;

- (NSURL *)LD_url;

@end
