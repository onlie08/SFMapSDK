//
//  LMKCircleView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKCircle.h"
#import "LMKOverlayPathView.h"

/*!
 @brief 该类是LMKCircle的显示圆view,可以通过LMKOverlayPathView修改其fill和stroke attributes
 */
@interface LMKCircleView : LMKOverlayPathView

/*!
 @brief 根据指定圆生成对应的View
 @param circle 指定的LMKCircle model
 @return 生成的View
 */
- (id)initWithCircle:(LMKCircle *)circle;

/*!
 @brief 关联的LMKCircle model
 */
@property (nonatomic, readonly) LMKCircle *circle;

@end
