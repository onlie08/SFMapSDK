//
//  LMKTileOverlayView.h
//  SFMapSDK
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/2/13.
//  Copyright © 2019年 sfmap. All rights reserved.
//

#import "LMKOverlayView.h"
#import "LMKTileOverlay.h"

@interface LMKTileOverlayView : LMKOverlayView

/*!
 @brief 覆盖在球面墨卡托投影上的图片tiles的数据源
 */
@property (nonatomic ,readonly) LMKTileOverlay *tileOverlay;

/*!
 @brief 根据指定的tileOverlay生成LMKOverlayView
 @param overlay 数据源
 @return 初始化成功则返回overlayView,否则返回nil
 */
- (id)initWithTileOverlay:(LMKTileOverlay *)overlay;

/*!
 @brief 清除所有tile的缓存，并刷新overlay
 */
- (void)reloadData;

@end
