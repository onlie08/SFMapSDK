//
//  LDNaviKit
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

//#import <Foundation/Foundation.h>
#import <CoreGraphics/CGBase.h>
//#import <UIKit/UIKit.h>

#ifndef LNGeometry
#define LNGeometry
/* Points. */

struct LNPoint {
	int x;
	int y;
};
typedef struct LNPoint LNPoint;

/* Sizes. */

struct LNSize {
	int width;
	int height;
};
typedef struct LNSize LNSize;

/* Rectangles. */

struct LNRect {
	LNPoint origin;
	LNSize size;
};
typedef struct LNRect LNRect;

/* The "zero" point -- equivalent to LNPointMake(0, 0). */ 

CG_EXTERN const LNPoint LNPointZero;

/* The "zero" size -- equivalent to LNSizeMake(0, 0). */ 

CG_EXTERN const LNSize LNSizeZero;

/* The "zero" rectangle -- equivalent to LNRectMake(0, 0, 0, 0). */ 

CG_EXTERN const LNRect LNRectZero;

/* Make a point from `(x, y)'. */

CG_INLINE LNPoint LNPointMake(int x, int y);

/* Make a size from `(width, height)'. */

CG_INLINE LNSize LNSizeMake(int width, int height);

/* Make a rect from `(x, y; width, height)'. */

CG_INLINE LNRect LNRectMake(int x, int y, int width, int height);

/* Return the leftmost x-value of `rect'. */

CG_EXTERN int LNRectGetMinX(LNRect rect);

/* Return the midpoint x-value of `rect'. */

CG_EXTERN int LNRectGetMidX(LNRect rect);

/* Return the rightmost x-value of `rect'. */

CG_EXTERN int LNRectGetMaxX(LNRect rect);

/* Return the bottommost y-value of `rect'. */

CG_EXTERN int LNRectGetMinY(LNRect rect);

/* Return the midpoint y-value of `rect'. */

CG_EXTERN int LNRectGetMidY(LNRect rect);

/* Return the topmost y-value of `rect'. */

CG_EXTERN int LNRectGetMaxY(LNRect rect);

/* Return the width of `rect'. */

CG_EXTERN int LNRectGetWidth(LNRect rect);

/* Return the height of `rect'. */

CG_EXTERN int LNRectGetHeight(LNRect rect);

/* Return true if `point1' and `point2' are the same, false otherwise. */

CG_EXTERN bool LNPointEqualToPoint(LNPoint point1, LNPoint point2);

/* Return true if `size1' and `size2' are the same, false otherwise. */

CG_EXTERN bool LNSizeEqualToSize(LNSize size1, LNSize size2);

/* Return true if `rect1' and `rect2' are the same, false otherwise. */

CG_EXTERN bool LNRectEqualToRect(LNRect rect1, LNRect rect2);

/* Return true if `rect' is empty (that is, if it has zero width or height),
 false otherwise. A null rect is defined to be empty. */

CG_EXTERN bool LNRectIsEmpty(LNRect rect);

/* Return true if `point' is contained in `rect', false otherwise. */

CG_EXTERN bool LNRectContainsPoint(LNRect rect, LNPoint point);

/*** Definitions of inline functions. ***/

CG_INLINE LNPoint LNPointMake(int x, int y)
{
	LNPoint p; p.x = x; p.y = y; return p;
}

CG_INLINE LNSize LNSizeMake(int width, int height)
{
	LNSize size; size.width = width; size.height = height; return size;
}

CG_INLINE LNRect LNRectMake(int x, int y, int width, int height)
{
	LNRect rect;
	rect.origin.x = x; rect.origin.y = y;
	rect.size.width = width; rect.size.height = height;
	return rect;
}

CG_INLINE bool __LNPointEqualToPoint(LNPoint point1, LNPoint point2)
{
	return point1.x == point2.x && point1.y == point2.y;
}
#define LNPointEqualToPoint __LNPointEqualToPoint

CG_INLINE bool __LNSizeEqualToSize(LNSize size1, LNSize size2)
{
	return size1.width == size2.width && size1.height == size2.height;
}
#define LNSizeEqualToSize __LNSizeEqualToSize

CG_INLINE bool __LNRectEqualToRect(LNRect rect1, LNRect rect2)
{
	return LNPointEqualToPoint(rect1.origin, rect2.origin) && LNSizeEqualToSize(rect1.size, rect2.size);
}
#define LNRectEqualToRect __LNRectEqualToRect

#endif
