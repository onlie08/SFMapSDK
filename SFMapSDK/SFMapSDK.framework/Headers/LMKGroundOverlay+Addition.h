//
//  LMKGroundOverlay+Addition.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKGroundOverlay.h"

@interface LMKGroundOverlay ()

@property (nonatomic ) LMKMapPoint *mapPoints;

@property (nonatomic ) NSUInteger pointsCount;

@property (nonatomic, readwrite)LMKMapRect boundingMapRect;

@property (nonatomic, readwrite)CLLocationCoordinate2D coordinate;

@end
