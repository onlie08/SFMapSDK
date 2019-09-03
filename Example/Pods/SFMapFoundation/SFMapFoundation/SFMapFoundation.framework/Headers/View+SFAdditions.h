//
//  UIView+SFAdditions.h
//  SFMasonry
//
//  Created by Jonas Budelmann on 20/07/13.
//  Copyright (c) 2013 cloudling. All rights reserved.
//

#import "SFUtilities.h"
#import "SFConstraintMaker.h"
#import "SFViewAttribute.h"

/**
 *	Provides constraint maker block
 *  and convience methods for creating SFViewAttribute which are view + NSLayoutAttribute pairs
 */
@interface SF_VIEW (SFAdditions)

/**
 *	following properties return a new SFViewAttribute with current view and appropriate NSLayoutAttribute
 */
@property (nonatomic, strong, readonly) SFViewAttribute *sf_left;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_top;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_right;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_bottom;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_leading;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_trailing;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_width;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_height;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_centerX;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_centerY;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_baseline;
@property (nonatomic, strong, readonly) SFViewAttribute *(^sf_attribute)(NSLayoutAttribute attr);

#if TARGET_OS_IPHONE || TARGET_OS_TV

@property (nonatomic, strong, readonly) SFViewAttribute *sf_leftMargin;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_rightMargin;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_topMargin;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_bottomMargin;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_leadingMargin;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_trailingMargin;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_centerXWithinMargins;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_centerYWithinMargins;

#endif

/**
 *	a key to associate with this view
 */
@property (nonatomic, strong) id sf_key;

/**
 *	Finds the closest common superview between this view and another view
 *
 *	@param	view	other view
 *
 *	@return	returns nil if common superview could not be found
 */
- (instancetype)sf_closestCommonSuperview:(SF_VIEW *)view;

/**
 *  Creates a SFConstraintMaker with the callee view.
 *  Any constraints defined are added to the view or the appropriate superview once the block has finished executing
 *
 *  @param block scope within which you can build up the constraints which you wish to apply to the view.
 *
 *  @return Array of created SFConstraints
 */
- (NSArray *)sf_makeConstraints:(void(^)(SFConstraintMaker *make))block;

/**
 *  Creates a SFConstraintMaker with the callee view.
 *  Any constraints defined are added to the view or the appropriate superview once the block has finished executing.
 *  If an existing constraint exists then it will be updated instead.
 *
 *  @param block scope within which you can build up the constraints which you wish to apply to the view.
 *
 *  @return Array of created/updated SFConstraints
 */
- (NSArray *)sf_updateConstraints:(void(^)(SFConstraintMaker *make))block;

/**
 *  Creates a SFConstraintMaker with the callee view.
 *  Any constraints defined are added to the view or the appropriate superview once the block has finished executing.
 *  All constraints previously installed for the view will be removed.
 *
 *  @param block scope within which you can build up the constraints which you wish to apply to the view.
 *
 *  @return Array of created/updated SFConstraints
 */
- (NSArray *)sf_remakeConstraints:(void(^)(SFConstraintMaker *make))block;

@end
