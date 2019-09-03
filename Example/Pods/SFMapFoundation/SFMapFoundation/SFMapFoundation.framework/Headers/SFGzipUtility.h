//
//  SFGzipUtility.h
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SFGzipUtility : NSObject

// 数据压缩
+ ( NSData *)sfCompressData:( NSData *)uncompressedData;

// 数据解压缩
+ ( NSData *)deSfCompressData:( NSData *)compressedData;

@end
