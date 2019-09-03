//
//  SFCompositeConstraint.h
//  SFMasonry
//
//  Created by SFmap on 16/4/20.
//  Copyright © 2016年 SFmap. All rights reserved.
//

#import "SFConstraint.h"
#import "SFUtilities.h"

/**
 *	A group of SFConstraint objects
 */
@interface SFCompositeConstraint : SFConstraint

/**
 *	Creates a composite with a predefined array of children
 *
 *	@param	children	child SFConstraints
 *
 *	@return	a composite constraint
 */
- (id)initWithChildren:(NSArray *)children;

@end
