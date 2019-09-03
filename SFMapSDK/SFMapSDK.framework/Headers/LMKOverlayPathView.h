//
//  LMKOverlayPathView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LMKOverlayView.h"

/*!
 @brief 该类提供使用CGPathRef来绘制overlay,默认的操作是将fill attributes, stroke attributes设置到CAShapeLayer中, 可以使用该类的子类LMKCircleView, LMKPolylineView, LMKPolygonView或者继承该类, 如果继承该类，需要重载-(void)createPath方法
 */
@interface LMKOverlayPathView : LMKOverlayView

/*!
 @brief 填充颜色,默认是kLMKOverlayViewDefaultFillColor
 */
@property (retain) UIColor *fillColor;

/*!
 @brief 笔触颜色,默认是kLMKOverlayViewDefaultStrokeColor
 */
@property (retain) UIColor *strokeColor;

/*!
 @brief 笔触宽度,默认是0
 */
@property CGFloat lineWidth;

/*!
 @brief LineJoin,默认是kLMKLineJoinBevel
 */
@property LMKLineJoinType lineJoinType;

/*!
 @brief LineCap,默认是kLMKLineCapButt
 */
@property LMKLineCapType lineCapType;

/*!
 @brief MiterLimit,默认是10.f
 */
@property CGFloat miterLimit;

/*!
 @brief 是否绘制成虚线, 默认是NO
 */
@property BOOL lineDash;

@end
