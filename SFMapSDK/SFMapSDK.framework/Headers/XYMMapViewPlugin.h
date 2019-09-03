//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "XYMMapPlatform.h"

@class XYMEDCallbackManager;
@interface XYMMapViewPlugin : NSObject<LMKMMapCorePlatformPlugin>

@property (nonatomic, retain) XYMEDCallbackManager *callbackManager;

@end
