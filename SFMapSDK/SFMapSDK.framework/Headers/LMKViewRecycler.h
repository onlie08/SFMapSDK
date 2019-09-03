//
//  LMKViewRecycler.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "LMKAnnotationView.h"

@protocol LMKRecyclableView;

@interface LMKViewRecycler : NSObject

@property (nonatomic, retain) NSMutableDictionary *reuseIdentifiersToRecycledViews;

- (UIView<LMKRecyclableView> *)dequeueReusableViewWithIdentifier:(NSString *)reuseIdentifier;

- (void)recycleView:(UIView<LMKRecyclableView> *)view;

- (void)removeAllViews;
- (void)removeAnnotationView:(LMKAnnotationView *)view;

@end

@protocol LMKRecyclableView <NSObject>

@optional

@property (nonatomic, readonly) NSString *reuseIdentifier;
- (void)prepareForReuse;

@end

