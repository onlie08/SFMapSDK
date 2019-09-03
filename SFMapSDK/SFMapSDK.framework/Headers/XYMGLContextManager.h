//
//  XYMGLContextManager.h
//  SFMapSDK
//
//  Created by sfmap on 16/9/6.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenGLES/EAGL.h>

@interface XYMGLContextManager : NSObject

+ (XYMGLContextManager *)sharedManager;

@property (nonatomic, strong) EAGLContext *context;
- (void)addReferenceForContext;
- (void)removeReferenceForContext;

@end
