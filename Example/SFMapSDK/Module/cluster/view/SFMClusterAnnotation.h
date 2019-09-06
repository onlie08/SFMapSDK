//
//  SFMClusterAnnotation.h
//  SFMapSDK_Example
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/9/3.
//  Copyright © 2019年 ggggggc. All rights reserved.
//

#import <SFMapSDK/LMKMapKit.h>

static NSString *SFMClusterAnnoIdentifier = @"com.SF.ClusterAnnotation";

@interface SFMClusterAnnotation : LMKPointAnnotation

@property (nonatomic, assign) NSInteger size;
@property (nonatomic, assign) BOOL isCircleInner;

@end
