//
//  SFEncryptionHelper.h
//  SFMapFoundation
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2018/10/23.
//  Copyright © 2018年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SFEncryptionHelper : NSObject

+ (NSString *)sf_parseByte2HexString:(NSData *) myData;
+ (NSData *)sf_hexStringToData:(NSString *)hexString;

@end
