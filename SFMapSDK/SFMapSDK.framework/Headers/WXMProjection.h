//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <SFMapFoundation/SFMapFoundation.h>

@interface WXMProjection : NSObject
{
    
}

+ (CLLocationCoordinate2D) PixelsToLatLongWithXPiexl: (long) xPixel yPixel:(long) yPixel levelOfDetail:(int) levelOfDetail;
+ (double) ClipWithN:(double) n minValue:(double) minValue maxValue:(double) maxValue;
+ (int) getTileWidth;
+ (LNPoint) LatLongToPixelsWithLong:(int) longitude lat:(int) latitude level:(int) levelOfDetail;
+ (LNPoint) DLatLongToPixelsWithLat:(double) latitude lon:(double) longitude level:(int) levelOfDetail;
+ (LNPoint) PixelsToPixelsWithX:(long) xPixel y:(long) yPixel srcLevel:(int) srcLevel toLevel:(int) toLevel;
+ (LNPoint) PixelsToTileWithX:(long) xPixel y:(long) yPixel;
+ (NSString*) TileToQuadKeyWithX:(long) xTile y:(long) yTile level:(int) levelOfDetail;
+ (LNPoint) QuadKeyToTile:(NSString*) quadKey;
+ (float) computeMeterPerPixelWithX:(int)x y:(int)y;
+ (LNPoint) getDistancePointWithX1:(int)x1 y1:(int)y1 x2:(int)x2 y2:(int)y2 distance:(int)distance;

+ (int) ComputeFormCDWithLat1:(double)lat1  lon1:(double)lon1 lat2:(double)lat2 lon2:(double)lon2;
+ (double) crsdistWithLat1:(double)lat1 lon1:(double)lon1 lat2:(double)lat2 lon2:(double)lon2;
+ (double) crsdist_ellWithGlat1:(double) glat1 glon1:(double) glon1 glat2:(double) glat2 glon2:(double) glon2;
+ (double) acosf:(double) x;
+ (double) modcrs:(double) x;
+ (double) mod:(double) x andY:(double) y;
+ (double) atan2withY:(double) y x:(double) x;

@end
