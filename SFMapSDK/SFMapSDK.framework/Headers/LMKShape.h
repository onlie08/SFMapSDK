//
//  LMKShape.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LMKAnnotation.h"
#import "LMKMapView.h"

/*!
 @brief 该类为一个抽象类，定义了基于LMKAnnotation的LMKShape类的基本属性和行为，不能直接使用，必须子类化之后才能使用
 */
@interface LMKShape : NSObject <LMKAnnotation> {

    NSString *_title;
    NSString *_subtitle;
}

/*!
 @brief 标题
 */
@property (copy) NSString *title;

/*!
 @brief 副标题
 */
@property (copy) NSString *subtitle;

/*!
 @brief 投影类型
 */
@property (nonatomic, assign) NSUInteger projection_type;

/*!
 @brief 构建数据
 @param projectionType 投影类型
 */
- (void)buildDataWithType:(LMKMapProjectionType)projectionType;

@end
