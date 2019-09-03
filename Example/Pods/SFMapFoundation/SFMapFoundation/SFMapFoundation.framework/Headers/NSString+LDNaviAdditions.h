//
//  LDNaviKit
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSString (LDNaviAdditions)
+ (NSString *)urlEncode:(NSString *)originalString stringEncoding:(NSStringEncoding)stringEncoding;
- (NSString *)urlEncodeWithEncoding:(NSStringEncoding)stringEncoding;
@end
