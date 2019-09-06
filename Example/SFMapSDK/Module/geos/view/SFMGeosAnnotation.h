//
//  SFMGeosAnnotation.h
//  SFMapSDK_Example
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/9/6.
//  Copyright © 2019年 ggggggc. All rights reserved.
//

#import <SFMapSDK/LMKMapKit.h>

static NSString *SFMGeosAnnoIdentifier = @"com.SF.GeosAnnotation";

@interface SFMGeosAnnotation : LMKPointAnnotation

@property(nonatomic,assign)BOOL isInCircle;

@end
