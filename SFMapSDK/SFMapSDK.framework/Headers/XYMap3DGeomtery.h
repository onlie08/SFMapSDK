//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XYMap3DOverlays.h"

#define VISIBLERECT_TOP     1
#define VISIBLERECT_BOTTOM  2
#define VISIBLERECT_LEFT    4
#define VISIBLERECT_RIGHT   8

typedef struct {
    int minX;
    int minY;
    int maxX;
    int maxY;
} VNRect;

static int LNGetVisibleState(VNRect rect, LNPoint point) {
    int visibleState = 0;
    
    if (point.x < rect.minX) {
        visibleState |= VISIBLERECT_LEFT;
    } else if (point.x > rect.maxX) {
        visibleState |= VISIBLERECT_RIGHT;
    }
    
    if (point.y < rect.minY) {
        visibleState |= VISIBLERECT_TOP;
    } else if (point.y > rect.maxY) {
        visibleState |= VISIBLERECT_BOTTOM;
    }
    
    return visibleState;
}

static LNPoint LNClipPoint(VNRect rect, double k, WXMLPoint p) {
    double pos = 0;
    
    LNPoint clipPoint = LNPointZero;
    
    if (k != 0) {
        if ((p.inRect & VISIBLERECT_TOP) != 0) {
            pos = (rect.minY - p.point.y) / k + p.point.x;
            if ((pos < rect.maxX) && (pos > rect.minX)) {
                clipPoint = LNPointMake(pos, rect.minY);
            }
        } else if ((p.inRect & VISIBLERECT_BOTTOM) != 0) {
            pos = (rect.maxY - p.point.y) / k + p.point.x;
            if ((pos < rect.maxX) && (pos > rect.minX)) {
                clipPoint = LNPointMake(pos, rect.maxY);
            }
        }
    }
    
    if (k != DBL_MAX) {
        if ((p.inRect & VISIBLERECT_LEFT) != 0) {
            pos = (rect.minX - p.point.x) * k + p.point.y;
            if ((pos < rect.maxY) && (pos > rect.minY)) {
                clipPoint = LNPointMake(rect.minX, pos);
            }
        } else if ((p.inRect & VISIBLERECT_RIGHT) != 0) {
            pos = (rect.maxX - p.point.x) * k + p.point.y;
            if ((pos < rect.maxY) && (pos > rect.minY)) {
                clipPoint = LNPointMake(rect.maxX, pos);
            }
        }
    }
    
    return clipPoint;
}


static bool linesegmentRectIntersect(LNPoint pt1, LNPoint pt2, VNRect rect)
{
    
    int left = rect.minX;
    int top = rect.minY;
    int right = rect.maxX;
    int bottom = rect.maxY;
    
    if ((pt1.x < left && pt2.x < left)
        ||(pt1.x > right && pt2.x > right)
        ||(pt1.y < top && pt2.y < top)
        ||(pt1.y > bottom && pt2.y > bottom))
    {
        return false;
    }
    
    unsigned char spCode = 0, epCode = 0;
    
    int xl = rect.minX,
    xr = rect.maxX,
    yt = rect.minY,
    yb = rect.maxY;
    
    int sx = pt1.x,
    sy = pt1.y,
    ex = pt2.x,
    ey = pt2.y;
    
    if(sx < xl)		spCode |= 1;
    if(sx > xr)		spCode |= 2;
    if(sy < yt)		spCode |= 4;
    if(sy > yb)		spCode |= 8;
    
    if(ex < xl)		epCode |= 1;
    if(ex > xr)		epCode |= 2;
    if(ey < yt)		epCode |= 4;
    if(ey > yb)		epCode |= 8;
    
    if(spCode == 0 || epCode == 0)
        return true;
    
//    if(spCode & epCode)
//        return false;
    
    if(	((spCode | epCode) == 0x0C) ||
       ((spCode | epCode) == 0x03))
        return true;
    
//    bool direct;
//    double k = (double)(ey - sy) / (ex - sx);
//    
//    direct = (yt - sy - k * (xl - sx) > 0.F);			//(xl,yt)
//    if(	direct != (yt - sy - k * (xr - sx) > 0.F) ||	//(xr,yt)
//       direct != (yb - sy - k * (xr - sx) > 0.F) ||	//(xr,yb)
//       direct != (yb - sy - k * (xl - sx) > 0.F) )		//(xl,yb)
//        return true;
    
    double k = (double)(ey - sy) / (ex - sx);
    double rk = (double)(1/k);

    int ml = sy + k * (xl - sx);
    if (ml >= yt && ml <= yb) {
        return true;
    }
    
    int mr = sy + k *(xr - sx);
    if (mr >= yt && mr <= yb) {
        return true;
    }
    
    int mt = sx + rk * (yt - sy);
    if (mt <= xr && mt >= xl) {
        return true;
    }
    
    int mb = sx + rk * (yb - sy);
    if (mb <= xr && mb >= xl) {
        return true;
    }

    return false;
}


@interface XYMapWidthLine : NSObject

@property (nonatomic, assign) XYMap3DView *map3dView;
- (void)setLineTexture:(int)textureId andWidth:(float)width andColorStart:(int)colorStart
    andColorComponents:(GLfloat*)colorComponents;
- (void)beginLine;
- (void)moveToX:(GLfloat)x andY:(GLfloat)y;
- (void)lineToX:(GLfloat)x andY:(GLfloat)y;
- (void)endLine;
- (void)reset;
- (void)draw;
- (void)drawBgColor:(GLfloat*)color;
- (void)drawWithTexture:(int)textureId andColor:(GLfloat*)color;

@end

@interface XYMapArrowLine : NSObject

@property (nonatomic, assign) XYMap3DView *map3dView;
- (void)setLineColor:(GLfloat*)color andSideColor:(GLfloat*)sideColor;
- (void)setWidth:(float)width;
- (void)moveToX:(GLfloat)x andY:(GLfloat)y;
- (void)lineToX:(GLfloat)x andY:(GLfloat)y;
- (void)endLine;
- (void)reset;
- (void)draw;

@end

@interface XYMapPolygon : NSObject

@property (nonatomic, assign) XYMap3DView *map3dView;
- (void)setColor:(GLfloat*)color;
- (void)beginPolygon;
- (void)moveToX:(GLfloat)x andY:(GLfloat)y;
- (void)lineToX:(GLfloat)x andY:(GLfloat)y;
- (void)endPolygon;
- (void)reset;
- (void)draw;

@end
