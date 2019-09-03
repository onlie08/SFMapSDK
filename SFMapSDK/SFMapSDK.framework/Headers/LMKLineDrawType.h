//
//  LMKLineDrawType.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#ifndef SFMapSDK_static_LDLineDrawType_h
#define SFMapSDK_static_LDLineDrawType_h

enum LMKLineJoinType {
    kLMKLineJoinBevel, ///0 : 接合点为斜角
    kLMKLineJoinMiter, ///1 : 接合点为尖角
    kLMKLineJoinRound  ///2 : 接合点为圆角
};
typedef enum LMKLineJoinType LMKLineJoinType;

enum LMKLineCapType {
    kLMKLineCapButt,   ///0 : 向线条的每个末端添加平直的边缘
    kLMKLineCapSquare, ///1 : 向线条的每个末端添加正方形线帽
    kLMKLineCapArrow,  ///2 : 向线条的每个末端添加箭头型线帽
    kLMKLineCapRound   ///3 :向线条的每个末端添加圆形线帽
};
typedef enum LMKLineCapType LMKLineCapType;

#endif
