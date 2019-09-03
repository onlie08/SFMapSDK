//
//  LMKPinAnnotationView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKAnnotationView.h"
#import <UIKit/UIKit.h>

// 颜色后续要改
typedef NS_ENUM(NSUInteger, LMKPinAnnotationColor){
    LMKPinAnnotationColorDefault,
    LMKPinAnnotationColorAzure,
    LMKPinAnnotationColorBlue,
    LMKPinAnnotationColorGreen,
    LMKPinAnnotationColorMagenta,
    LMKPinAnnotationColorRed,
    LMKPinAnnotationColorRose,
    LMKPinAnnotationColorViolet,
    LMKPinAnnotationColorYellow,
};

/*!
 @brief 提供类似大头针效果的annotation view
 */
@interface LMKPinAnnotationView : LMKAnnotationView

/*!
 @brief 大头针的颜色
 */
@property (nonatomic) LMKPinAnnotationColor pinColor;

/*!
 @brief 动画效果
 */
@property (nonatomic) BOOL animatesDrop;

@end
