//
//  LMKGLUtility.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenGLES/ES1/gl.h>
#import "LMKGeometry.h"

typedef void* me_mapengine;
typedef void* me_projection;

@interface LMKGLUtility : NSObject

// sharedUtility
+ (LMKGLUtility *)sharedUtility;

// draw line 需要提供line纹理
- (void)drawLinesWithPoints:(int *)points
                 pointCount:(NSUInteger)pointCount
                strokeColor:(UIColor *)strokeColor
                  lineWidth:(CGFloat)lineWidth
              lineTextureID:(GLint)lineTextureID
                     texLen:(CGFloat)texLen
             withProjection:(me_projection)projection
                     looped:(BOOL)looped
                    complex:(BOOL)complex;

// draw arrowline
- (void)drawArrowLineWithPoints:(int *)points
                     pointCount:(NSUInteger)pointCount
                      lineWidth:(CGFloat)lineWidth
                 clrBorderColor:(UIColor *)clrBorderColor
                    strokeColor:(UIColor *)strokeColor
                 withProjection:(me_projection)projection
                         looped:(BOOL)looped;

// draw region
- (void)drawRegionWithPoints:(int *)points
                  pointCount:(NSUInteger)pointCount
                   fillColor:(UIColor *)fillColor
              withProjection:(me_projection)projection;

//
- (GLuint)getTextureIDFromFilePath:(NSString *)filePath;

- (GLuint)getTextureIDFromImage:(UIImage *)image;

@end
