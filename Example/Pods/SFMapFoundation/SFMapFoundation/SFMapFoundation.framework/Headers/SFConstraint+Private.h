//
//  SFConstraint+Private.h
//  SFMasonry
//
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "SFConstraint.h"

@protocol SFConstraintDelegate;


@interface SFConstraint ()

/**
 *  Whether or not to check for an existing constraint instead of adding constraint
 */
@property (nonatomic, assign) BOOL updateExisting;

/**
 *	Usually SFConstraintMaker but could be a parent SFConstraint
 */
@property (nonatomic, weak) id<SFConstraintDelegate> delegate;

/**
 *  Based on a provided value type, is equal to calling:
 *  NSNumber - setOffset:
 *  NSValue with CGPoint - setPointOffset:
 *  NSValue with CGSize - setSizeOffset:
 *  NSValue with SFEdgeInsets - setInsets:
 */
- (void)setLayoutConstantWithValue:(NSValue *)value;

@end


@interface SFConstraint (Abstract)

/**
 *	Sets the constraint relation to given NSLayoutRelation
 *  returns a block which accepts one of the following:
 *    SFViewAttribute, UIView, NSValue, NSArray
 *  see readme for more details.
 */
- (SFConstraint * (^)(id, NSLayoutRelation))equalToWithRelation;

/**
 *	Override to set a custom chaining behaviour
 */
- (SFConstraint *)addConstraintWithLayoutAttribute:(NSLayoutAttribute)layoutAttribute;

@end


@protocol SFConstraintDelegate <NSObject>

/**
 *	Notifies the delegate when the constraint needs to be replaced with another constraint. For example
 *  A SFViewConstraint may turn into a SFCompositeConstraint when an array is passed to one of the equality blocks
 */
- (void)constraint:(SFConstraint *)constraint shouldBeReplacedWithConstraint:(SFConstraint *)replacementConstraint;

- (SFConstraint *)constraint:(SFConstraint *)constraint addConstraintWithLayoutAttribute:(NSLayoutAttribute)layoutAttribute;

@end
