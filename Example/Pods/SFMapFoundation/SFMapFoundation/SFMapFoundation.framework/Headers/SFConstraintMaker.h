//
//  SFConstraintBuilder.h
//  SFMasonry
//
//  Created by Jonas Budelmann on 20/07/13.
//  Copyright (c) 2013 cloudling. All rights reserved.
//

#import "SFConstraint.h"
#import "SFUtilities.h"

typedef NS_OPTIONS(NSInteger, SFAttribute) {
    SFAttributeLeft = 1 << NSLayoutAttributeLeft,
    SFAttributeRight = 1 << NSLayoutAttributeRight,
    SFAttributeTop = 1 << NSLayoutAttributeTop,
    SFAttributeBottom = 1 << NSLayoutAttributeBottom,
    SFAttributeLeading = 1 << NSLayoutAttributeLeading,
    SFAttributeTrailing = 1 << NSLayoutAttributeTrailing,
    SFAttributeWidth = 1 << NSLayoutAttributeWidth,
    SFAttributeHeight = 1 << NSLayoutAttributeHeight,
    SFAttributeCenterX = 1 << NSLayoutAttributeCenterX,
    SFAttributeCenterY = 1 << NSLayoutAttributeCenterY,
    SFAttributeBaseline = 1 << NSLayoutAttributeBaseline,
    
#if TARGET_OS_IPHONE || TARGET_OS_TV
    
    SFAttributeLeftMargin = 1 << NSLayoutAttributeLeftMargin,
    SFAttributeRightMargin = 1 << NSLayoutAttributeRightMargin,
    SFAttributeTopMargin = 1 << NSLayoutAttributeTopMargin,
    SFAttributeBottomMargin = 1 << NSLayoutAttributeBottomMargin,
    SFAttributeLeadingMargin = 1 << NSLayoutAttributeLeadingMargin,
    SFAttributeTrailingMargin = 1 << NSLayoutAttributeTrailingMargin,
    SFAttributeCenterXWithinMargins = 1 << NSLayoutAttributeCenterXWithinMargins,
    SFAttributeCenterYWithinMargins = 1 << NSLayoutAttributeCenterYWithinMargins,

#endif
    
};

/**
 *  Provides factory methods for creating SFConstraints.
 *  Constraints are collected until they are ready to be installed
 *
 */
@interface SFConstraintMaker : NSObject

/**
 *	The following properties return a new SFViewConstraint
 *  with the first item set to the makers associated view and the appropriate SFViewAttribute
 */
@property (nonatomic, strong, readonly) SFConstraint *left;
@property (nonatomic, strong, readonly) SFConstraint *top;
@property (nonatomic, strong, readonly) SFConstraint *right;
@property (nonatomic, strong, readonly) SFConstraint *bottom;
@property (nonatomic, strong, readonly) SFConstraint *leading;
@property (nonatomic, strong, readonly) SFConstraint *trailing;
@property (nonatomic, strong, readonly) SFConstraint *width;
@property (nonatomic, strong, readonly) SFConstraint *height;
@property (nonatomic, strong, readonly) SFConstraint *centerX;
@property (nonatomic, strong, readonly) SFConstraint *centerY;
@property (nonatomic, strong, readonly) SFConstraint *baseline;

#if TARGET_OS_IPHONE || TARGET_OS_TV

@property (nonatomic, strong, readonly) SFConstraint *leftMargin;
@property (nonatomic, strong, readonly) SFConstraint *rightMargin;
@property (nonatomic, strong, readonly) SFConstraint *topMargin;
@property (nonatomic, strong, readonly) SFConstraint *bottomMargin;
@property (nonatomic, strong, readonly) SFConstraint *leadingMargin;
@property (nonatomic, strong, readonly) SFConstraint *trailingMargin;
@property (nonatomic, strong, readonly) SFConstraint *centerXWithinMargins;
@property (nonatomic, strong, readonly) SFConstraint *centerYWithinMargins;

#endif

/**
 *  Returns a block which creates a new SFCompositeConstraint with the first item set
 *  to the makers associated view and children corresponding to the set bits in the
 *  SFAttribute parameter. Combine multiple attributes via binary-or.
 */
@property (nonatomic, strong, readonly) SFConstraint *(^attributes)(SFAttribute attrs);

/**
 *	Creates a SFCompositeConstraint with type SFCompositeConstraintTypeEdges
 *  which generates the appropriate SFViewConstraint children (top, left, bottom, right)
 *  with the first item set to the makers associated view
 */
@property (nonatomic, strong, readonly) SFConstraint *edges;

/**
 *	Creates a SFCompositeConstraint with type SFCompositeConstraintTypeSize
 *  which generates the appropriate SFViewConstraint children (width, height)
 *  with the first item set to the makers associated view
 */
@property (nonatomic, strong, readonly) SFConstraint *size;

/**
 *	Creates a SFCompositeConstraint with type SFCompositeConstraintTypeCenter
 *  which generates the appropriate SFViewConstraint children (centerX, centerY)
 *  with the first item set to the makers associated view
 */
@property (nonatomic, strong, readonly) SFConstraint *center;

/**
 *  Whether or not to check for an existing constraint instead of adding constraint
 */
@property (nonatomic, assign) BOOL updateExisting;

/**
 *  Whether or not to remove existing constraints prior to installing
 */
@property (nonatomic, assign) BOOL removeExisting;

/**
 *	initialises the maker with a default view
 *
 *	@param	view	any SFConstrait are created with this view as the first item
 *
 *	@return	a new SFConstraintMaker
 */
- (id)initWithView:(SF_VIEW *)view;

/**
 *	Calls install method on any SFConstraints which have been created by this maker
 *
 *	@return	an array of all the installed SFConstraints
 */
- (NSArray *)install;

- (SFConstraint * (^)(dispatch_block_t))group;

@end
