//
//  LMKMapView+Private.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LMKMapView.h"
#import "XYMap3DOverlays.h"
#import "LMKMarker.h"
#import "LMKOfflineMap.h"

@interface LMKMapView (Private)

- (void *)getMapEngine;

- (void *)getProjection;

- (void)renderOverlayWithState:(int)state;

- (XYMap3DLayerManager *)getMap3DLayerManager;

- (void)setCenterCoordinate_private:(CLLocationCoordinate2D)centerCoordinate;

#pragma mark - LMKMapView (Marker)

// offset:(0.5,0)，标示以底部中心点为锚点（默认为（0，0））
- (void)registerMarkerWithTextureImage:(UIImage *)image
                      markerIdentifier:(NSString *)markerIdentifier
                                offset:(CGPoint)offset
                             followMap:(BOOL)followMap;
- (void)unregisterMarkerWithMarkerIdentifier:(NSString *)markerIdentifier;
- (void)addMarker:(LMKMarker *)marker;
- (void)addMarkers:(NSArray *)markersArray;
- (void)removeMarker:(LMKMarker *)marker;
- (void)removeAllMarkers;

@end

@interface LDMapVewManager : NSObject

@property (nonatomic, assign) LMKMapView *currentMapView;

+ (LDMapVewManager *)sharedManager;
- (void)addMapView:(LMKMapView *)mapView;
- (void)removeMapView:(LMKMapView *)mapView;

@end

@interface LMKOfflineMap (Private)
+ (void)destroyOfflineMap;
- (NSInteger)getIsDownloadingItemsCount;
@end
