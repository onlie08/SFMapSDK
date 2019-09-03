//
//  LDASIInputStream.h
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LDASIHTTPRequest;

// This is a wrapper for NSInputStream that pretends to be an NSInputStream itself
// Subclassing NSInputStream seems to be tricky, and may involve overriding undocumented methods, so we'll cheat instead.
// It is used by LDASIHTTPRequest whenever we have a request body, and handles measuring and throttling the bandwidth used for uploading

@interface LDASIInputStream : NSObject<NSStreamDelegate>

+ (id)inputStreamWithFileAtPath:(NSString *)path request:(LDASIHTTPRequest *)request;
+ (id)inputStreamWithData:(NSData *)data request:(LDASIHTTPRequest *)request;
- (id)initWithInputStream:(NSInputStream *)stream;

@property (assign, nonatomic) LDASIHTTPRequest *request;
@end
