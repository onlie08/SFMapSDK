//
//  LMKPolylineView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//


#import <UIKit/UIKit.h>

#import "LMKPolyline.h"
#import "LMKOverlayPathView.h"

/*!
 @brief 此类是LMKPolyline的显示多段线view,可以通过LMKOverlayPathView修改其fill和stroke attributes
 */
@interface LMKPolylineView : LMKOverlayPathView

/*!
 @brief 根据指定的LMKPolyline生成一个多段线view
 @param polyline 指定LMKPolyline
 @return 新生成的多段线View
 */
- (id)initWithPolyline:(LMKPolyline *)polyline;

/*!
 @brief 关联的LMKPolyline model
 */
@property (nonatomic, readonly) LMKPolyline *polyline;

@end
