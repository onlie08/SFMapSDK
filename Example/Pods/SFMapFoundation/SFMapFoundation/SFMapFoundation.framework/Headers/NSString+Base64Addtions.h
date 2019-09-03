//
//  NSString+Base64Addtions.h
//
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface NSString (Base64Additions)

+ (id)decodeBase64:(NSString *)encodedString;
+ (id)decodeWebSafeBase64:(NSString *)encodedString;

- (NSString *)encodeBase64;
- (NSString *)encodeWebSafeBase64;
- (NSString *)encodeWrappedBase64;

@end
