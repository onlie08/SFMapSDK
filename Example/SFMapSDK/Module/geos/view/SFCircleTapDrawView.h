//
//  SFCircleTapDrawView.h
//  SFMapDemo
//
//  Created by 龚聪(Cong Gong)-顺丰科技 on 2019/2/20.
//  Copyright © 2019年 龚聪(Cong Gong)-顺丰科技. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void(^SFCircleTapDrawScreenPoints)(NSArray *screenPoints);

NS_ASSUME_NONNULL_BEGIN

@interface SFCircleTapDrawView : UIView

@property(nonatomic,copy)SFCircleTapDrawScreenPoints endCircleBlock;

@property(nonatomic,assign)CGPoint itemPoint;

- (void)cleanCircle;

@end

NS_ASSUME_NONNULL_END
