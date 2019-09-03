//
//  LMKWeakMapView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKMapView.h"
#import <Foundation/Foundation.h>

@interface LMKWeakMapView : NSObject

+ (LMKWeakMapView*)sharedWeakMapView;

@property (nonatomic, weak) LMKMapView* mapView;

@end
