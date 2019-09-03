//
//  LDNaviKit
//
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

#ifndef __IPHONE_4_0
#define __IPHONE_4_0 40000
#endif

extern const CLLocationCoordinate2D kLNLocationCoordinate2DInvalid;
#ifdef __cplusplus
extern "C" {
#endif    
CLLocationCoordinate2D LNLocationCoordinate2DMake(CLLocationDegrees latitude, CLLocationDegrees longitude);
BOOL LNLocationCoordinate2DIsValid(CLLocationCoordinate2D coord);
#ifdef __cplusplus
}
#endif

@interface CLLocationManager (LNCoreLocation)
+ (BOOL)LNLocationServicesEnabled;
@end
