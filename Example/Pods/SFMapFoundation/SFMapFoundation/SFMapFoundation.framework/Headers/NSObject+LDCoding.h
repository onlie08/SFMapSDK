//
//  NSObject+LDCoding.h
//  LDExtension
//
//  Created by LD on 14-1-15.
//  Copyright (c) 2014年 小码哥. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LDExtensionConst.h"

/**
 *  Codeing协议
 */
@protocol LDCoding <NSObject>
@optional
/**
 *  这个数组中的属性名才会进行归档
 */
+ (NSArray *)LD_allowedCodingPropertyNames;
/**
 *  这个数组中的属性名将会被忽略：不进行归档
 */
+ (NSArray *)LD_ignoredCodingPropertyNames;
@end

@interface NSObject (LDCoding) <LDCoding>
/**
 *  解码（从文件中解析对象）
 */
- (void)LD_decode:(NSCoder *)decoder;
/**
 *  编码（将对象写入文件中）
 */
- (void)LD_encode:(NSCoder *)encoder;
@end

/**
 归档的实现
 */
#define LDCodingImplementation \
- (id)initWithCoder:(NSCoder *)decoder \
{ \
if (self = [super init]) { \
[self LD_decode:decoder]; \
} \
return self; \
} \
\
- (void)encodeWithCoder:(NSCoder *)encoder \
{ \
[self LD_encode:encoder]; \
}

#define LDExtensionCodingImplementation LDCodingImplementation