//
//  NSData+Base64Additions.h
//  RockPaperScissors
//
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface NSData (Base64Additions)

+ (id)decodeBase64ForString:(NSString *)decodeString;
+ (id)decodeWebSafeBase64ForString:(NSString *)decodeString;

- (NSString *)encodeBase64ForData;
- (NSString *)encodeWebSafeBase64ForData;
- (NSString *)encodeWrappedBase64ForData;

@end
