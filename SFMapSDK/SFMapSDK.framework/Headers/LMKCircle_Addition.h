//
//  LMKCircleView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKCircle.h"

@interface LMKCircle ()

@property (nonatomic) LMKMapPoint *mapPoints;

@property (nonatomic) NSUInteger pointsCount;

@property (nonatomic, readwrite) CLLocationCoordinate2D coordinate;

@property (nonatomic, readwrite) CLLocationDistance radius;

@property (nonatomic, readwrite) LMKMapRect boundingMapRect;

@end
