//
//  LMKArcView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LMKArc.h"
#import "LMKOverlayPathView.h"

/*!
 @brief 此类是由LMKArc构建的弧线View类
 */
@interface LMKArcView : LMKOverlayPathView

/*!
 @brief 根据指定的LMKArc生成一个弧线view
 @param arc 指定LMKArc
 @return 新生成的弧线Overlay view
 */
- (id)initWithArc:(LMKArc *)arc;

/*!
 @brief 关联的LMKArc model
 */
@property (nonatomic, readonly) LMKArc *arc;

@end
