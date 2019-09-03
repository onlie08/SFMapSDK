//
//  SFConstraint.h
//  SFMasonry
//
//  Created by Jonas Budelmann on 20/07/13.
//  Copyright (c) 2013 cloudling. All rights reserved.
//

#import "SFViewAttribute.h"
#import "SFConstraint.h"
#import "SFLayoutConstraint.h"
#import "SFUtilities.h"

/**
 *  A single constraint.
 *  Contains the attributes neccessary for creating a NSLayoutConstraint and adding it to the appropriate view
 */
@interface SFViewConstraint : SFConstraint <NSCopying>

/**
 *	First item/view and first attribute of the NSLayoutConstraint
 */
@property (nonatomic, strong, readonly) SFViewAttribute *firstViewAttribute;

/**
 *	Second item/view and second attribute of the NSLayoutConstraint
 */
@property (nonatomic, strong, readonly) SFViewAttribute *secondViewAttribute;

/**
 *	initialises the SFViewConstraint with the first part of the equation
 *
 *	@param	firstViewAttribute	view.sf_left, view.sf_width etc.
 *
 *	@return	a new view constraint
 */
- (id)initWithFirstViewAttribute:(SFViewAttribute *)firstViewAttribute;

/**
 *  Returns all SFViewConstraints installed with this view as a first item.
 *
 *  @param  view  A view to retrieve constraints for.
 *
 *  @return An array of SFViewConstraints.
 */
+ (NSArray *)installedConstraintsForView:(SF_VIEW *)view;

@end
