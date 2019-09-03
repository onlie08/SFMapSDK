//
//  LDNaviKit
//
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#ifndef _CCOORDCONVERT_H
#define _CCOORDCONVERT_H

#import "LNGeometry.h"
#import <CoreLocation/CLLocation.h>

#ifdef __cplusplus
extern "C" {
#endif
void LNLonlatTo20Pixel(double lat, double lon, int* xp, int* yp); //default with offset
void LNLonlatTo20PixelEx(double lat, double lon, int* xp, int* yp, int needOffset);
void LN20PixelToLonlat(int pixelX, int pixelY, double* dLon, double* dLat);
#ifdef __cplusplus
};
#endif

@interface LNCoordConvert : NSObject {
}

+ (LNPoint)locationCoordToG20:(CLLocationCoordinate2D)locationCoordinate; //default with offset
+ (LNPoint)locationToG20:(CLLocation *)location; //default with offset

+ (LNPoint)locationCoordToG20:(CLLocationCoordinate2D)locationCoordinate needOffset:(BOOL)needOffset;
+ (LNPoint)locationToG20:(CLLocation *)location needOffset:(BOOL)needOffset;

+ (CLLocationCoordinate2D)G20ToLocationCoord:(LNPoint)G20Location;
+ (CLLocation *)G20ToLocation:(LNPoint)G20Location;

@end

#endif
