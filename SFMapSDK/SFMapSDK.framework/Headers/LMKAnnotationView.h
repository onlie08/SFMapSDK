//
//  LMKAnnotationView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>


typedef NS_ENUM(NSInteger, LMKAnnotationViewDragState)
{
    LMKAnnotationViewDragStateNone = 0,      ///0 : 静止状态
    LMKAnnotationViewDragStateStarting,      ///1 : 开始拖动
    LMKAnnotationViewDragStateDragging,      ///2 : 拖动中
    LMKAnnotationViewDragStateCanceling,     ///3 : 取消拖动
    LMKAnnotationViewDragStateEnding         ///4 : 拖动结束
};

@class LMKCalloutView;
@protocol LMKAnnotation;
@protocol LMKRecyclableView;

/*!
 @brief 标注view
 */
@interface LMKAnnotationView : UIView

/*!
 @brief 初始化并返回一个annotation view
 @param annotation 关联的annotation对象
 @param reuseIdentifier 如果要重用view,传入一个字符串,否则设为nil,建议重用view
 @return 初始化成功则返回annotation view,否则返回nil
 */
- (instancetype)initWithAnnotation:(id <LMKAnnotation>)annotation reuseIdentifier:(NSString *)reuseIdentifier;


/*!
 @brief 复用标志
 */
@property (nonatomic, copy) NSString *reuseIdentifier;
/*!
 @brief 气泡   
 */
@property (nonatomic, strong) LMKCalloutView *calloutView;

/*!
 @brief 当view从reuse队列里取出时被调用,默认不做任何事
 */
- (void)prepareForReuse;

/*! 
 @brief 关联的annotation
 */
@property (nonatomic, strong) id <LMKAnnotation> annotation;

/*! 
 @brief annotation view显示的图像
 */
@property (nonatomic, strong) UIImage *image;

/*! 
 @brief 默认情况下, annotation view的中心位于annotation的坐标位置，可以设置centerOffset改变view的位置，正的偏移使view朝右下方移动，负的朝左上方
 */
@property (nonatomic) CGPoint centerOffset;

/*!
 @brief 默认情况下, 弹出的气泡位于view正中上方，可以设置calloutOffset改变view的位置，正的偏移使view朝右下方移动，负的朝左上方
*/
@property (nonatomic) CGPoint calloutOffset;

/*! 
 @brief 默认为YES，当为NO时view忽略触摸事件
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/*!
 @brief 默认为NO，当view被点中时被设为YES
 */
@property (nonatomic, getter=isSelected) BOOL selected;

/*!
 @brief 设定view的选中状态
 @param selected 如果view需要显示为选中状态，该值为YES
 @param animated 如果需要动画效果，该值为YES,暂不支持
 */
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;

/*!
 @brief 当为YES时，view被选中时会弹出气泡，默认为YES
*/
@property (nonatomic) BOOL canShowCallout;

/*! 
 @brief显示在气泡左侧的view(使用默认气泡时，view的width最大值为44，height最大值为44，大于则使用最大值）
*/
@property (strong, nonatomic) UIView *leftCalloutAccessoryView;

/*! 
 @brief 显示在气泡右侧的view(使用默认气泡时，view的width最大值为44，height最大值为44，大于则使用最大值）
 */
@property (strong, nonatomic) UIView *rightCalloutAccessoryView;

/*! 
 @brief 是否支持拖动
 */
@property (nonatomic, getter=isDraggable) BOOL draggable;

/*! 
 @brief 当前view的拖动状态
 */
@property (nonatomic) LMKAnnotationViewDragState dragState;

/*! 
 @brief 设置拖动状态，支持动画
 */
- (void)setDragState:(LMKAnnotationViewDragState)newDragState animated:(BOOL)animated;
/*!
 @brief 设置是否选中
 */


@end
