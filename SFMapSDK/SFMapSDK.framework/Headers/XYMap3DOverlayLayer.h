//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>

@class XYMap3DOverlay;

@interface XYMap3DOverlayLayer : NSObject {
	NSString				*_groupIdentifier;
	NSMutableArray			*_overlays;
	BOOL					_visible;
}

@property (nonatomic, copy) NSString *identifier;
@property (nonatomic, readonly) NSMutableArray *overlays;
@property (nonatomic, readonly) BOOL isVisible;

- (id)initWithIdentifier:(NSString *)identifier;

- (void)addOverlay:(XYMap3DOverlay *)overlay;
- (void)removeOverlay:(XYMap3DOverlay *)overlay;

- (void)showOverlays;
- (void)hideOverlays;

- (void)touchAtPoint:(CGPoint)point;

@end
