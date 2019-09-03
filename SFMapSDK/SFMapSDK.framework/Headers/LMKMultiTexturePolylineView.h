//
//  LMKMultiTexturePolylineView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKOverlayPathView.h"
#import "LMKMultiPolyline.h"

@interface LMKMultiTexturePolylineView : LMKOverlayPathView

/*!
 @brief 根据指定的LMKMultiPolyline生成一个多段线Renderer
 @param multiPolyline 指定LMKMultiPolyline
 @return 新生成的多段线Renderer
 */
- (instancetype)initWithMultiPolyline:(LMKMultiPolyline *)multiPolyline;

/*!
 @brief 关联的LMKMultiPolyline model
 */
@property (nonatomic, readonly) LMKMultiPolyline *multiPolyline;

/*!
 @brief  取分段纹理id
 @return 分段纹理id数组
 */
@property (nonatomic, strong, readonly) NSArray * strokeTextureIDs;

/*!
 加载分段绘制的纹理图片
 需要分段纹理绘制时，必须设置。否则使用默认纹理绘制。
 @param textureImages 必须为UIImage数组，纹理图片（需满足：长宽相等，且宽度值为2的次幂）。若为nil，则清空原有纹理。
 @return 是否成功，若纹理加载失败返回0。
 */
- (BOOL)loadStrokeTextureImages:(NSArray *)textureImages;

@end
