//
//  LMKCalloutView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 LMKCalloutArrowDirectionMode,显示气泡的箭头方向，默认是向下
 */
typedef enum LMKCalloutArrowDirectionMode {
    LMKCalloutArrowDirectionModeDown,
    LMKCalloutArrowDirectionModeUp,
} LMKCalloutArrowDirectionMode;

@interface LMKCalloutView : UIView

// * 标题
@property (nonatomic, copy) NSString *title;

// * 副标题
@property (nonatomic, copy) NSString *subTitle;

// * leftAccessoryView
@property (nonatomic, strong) UIView *leftAccessoryView;

// * rightAccessoryView
@property (nonatomic, strong) UIView *rightAccessoryView;

// * calloutOffset偏移
@property (nonatomic) CGPoint calloutOffset;

/**
 *  展示CalloutView
 *
 *  @param view     view
 *  @param mode     箭头方向，暂时只支持向下的箭头
 *  @param animated 是否动画，暂时不支持
 */
- (void)presentCalloutinView:(id)view
    permittedArrowDirections:(LMKCalloutArrowDirectionMode)mode
                    animated:(BOOL)animated;
/**
 * 隐藏
 *
 *  @param animated 默认NO，不支持动画
 */
- (void)hideCalloutAnimated:(BOOL)animated;

@end
