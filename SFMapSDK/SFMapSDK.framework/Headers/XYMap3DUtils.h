//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#ifdef BUILD_OGLES
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#elif BUILD_OGLES2
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif
#import <SFMapFoundation/SFMapFoundation.h>

@interface XYMap3DUtils : NSObject {

}

+ (LNPoint)G20LocationFromGLCoordinate:(CGPoint)GLCoordinate;
+ (CGPoint)GLCoordinateFromG20Location:(LNPoint)G20Location;

//if textureId not gen before, please set origin textureId to -1, otherwise, this funciton will gen new texture Id for this text
+ (BOOL)genStringTexture:(NSString *)text textureSize:(CGPoint *)textureSize textureId:(GLuint *)textureId;

+ (GLfloat)GLUnitFromScreen:(CGFloat)screenUnit;
//+ (CGFloat)screenUnitFromGL:(GLfloat)GLUnit;

+ (CGPoint)GLCoordinateFromScreenPoint:(CGPoint)screenPoint;
+ (CGPoint)screenPointFromGLCoordinate:(CGPoint)GLCoordinate;

+ (GLfloat)GLUnitFromG20:(int)G20Unit;

@end
