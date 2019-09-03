//
//  LMKOverlayFloor.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LMKOverlayView.h"

@interface LMKOverlayFloor : UIView

- (void)drawOverlaysWithIsGroundOverlayFlag:(BOOL)isGroundOverlayFlag;

- (void)referenceDidChange;

@end
