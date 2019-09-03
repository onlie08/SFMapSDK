//
//  LMKPolygonView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "LMKPolygon.h"
#import "LMKOverlayPathView.h"

/*!
 @brief 此类是LMKPolygon的显示多边形view,可以通过LMKOverlayPathView修改其fill和stroke attributes
 */
@interface LMKPolygonView : LMKOverlayPathView

/*!
 @brief 根据指定的多边形生成一个多边形View
 @param polygon 指定的多边形数据对象
 @return 新生成的多边形View
 */
- (id)initWithPolygon:(LMKPolygon *)polygon;

/*!
 @brief 关联的LMKPolygon model
 */
@property (nonatomic, readonly) LMKPolygon *polygon;

@end
