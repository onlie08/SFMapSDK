//
//  LMKCustomDrawOverlay.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef _LMKCustomDrawOverlay_H_
#define _LMKCustomDrawOverlay_H_
/*!
 @brief 用户自定义OpenGL绘制类
 */
@interface LMKCustomDrawOverlay : NSObject

/*!
 @brief 用户自定义OpenGL绘制类的绘制级别：1，在Label之前绘制；2，在Label之后绘制
 */
@property (nonatomic, assign) int drawLevel;


/*!
 @brief 子类需要实现的绘制方法，需要实现自绘制的代码
 */
- (void)glRender;

@end

#endif
