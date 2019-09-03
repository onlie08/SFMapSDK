//
//  SFConstraint.h
//  SFMasonry
//
//  Created by Jonas Budelmann on 22/07/13.
//  Copyright (c) 2013 cloudling. All rights reserved.
//

#import "SFUtilities.h"

/**
 *	Enables Constraints to be created with chainable syntax
 *  Constraint can represent single NSLayoutConstraint (SFViewConstraint)
 *  or a group of NSLayoutConstraints (SFComposisteConstraint)
 */
@interface SFConstraint : NSObject

// Chaining Support

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects SFConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeTop, NSLayoutAttributeLeft, NSLayoutAttributeBottom, NSLayoutAttributeRight
 */
- (SFConstraint * (^)(SFEdgeInsets insets))insets;

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects SFConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeWidth, NSLayoutAttributeHeight
 */
- (SFConstraint * (^)(CGSize offset))sizeOffset;

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects SFConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeCenterX, NSLayoutAttributeCenterY
 */
- (SFConstraint * (^)(CGPoint offset))centerOffset;

/**
 *	Modifies the NSLayoutConstraint constant
 */
- (SFConstraint * (^)(CGFloat offset))offset;

/**
 *  Modifies the NSLayoutConstraint constant based on a value type
 */
- (SFConstraint * (^)(NSValue *value))valueOffset;

/**
 *	Sets the NSLayoutConstraint multiplier property
 */
- (SFConstraint * (^)(CGFloat multiplier))multipliedBy;

/**
 *	Sets the NSLayoutConstraint multiplier to 1.0/dividedBy
 */
- (SFConstraint * (^)(CGFloat divider))dividedBy;

/**
 *	Sets the NSLayoutConstraint priority to a float or SFLayoutPriority
 */
- (SFConstraint * (^)(SFLayoutPriority priority))priority;

/**
 *	Sets the NSLayoutConstraint priority to SFLayoutPriorityLow
 */
- (SFConstraint * (^)())priorityLow;

/**
 *	Sets the NSLayoutConstraint priority to SFLayoutPriorityMedium
 */
- (SFConstraint * (^)())priorityMedium;

/**
 *	Sets the NSLayoutConstraint priority to SFLayoutPriorityHigh
 */
- (SFConstraint * (^)())priorityHigh;

/**
 *	Sets the constraint relation to NSLayoutRelationEqual
 *  returns a block which accepts one of the following:
 *    SFViewAttribute, UIView, NSValue, NSArray
 *  see readme for more details.
 */
- (SFConstraint * (^)(id attr))equalTo;

/**
 *	Sets the constraint relation to NSLayoutRelationGreaterThanOrEqual
 *  returns a block which accepts one of the following:
 *    SFViewAttribute, UIView, NSValue, NSArray
 *  see readme for more details.
 */
- (SFConstraint * (^)(id attr))greaterThanOrEqualTo;

/**
 *	Sets the constraint relation to NSLayoutRelationLessThanOrEqual
 *  returns a block which accepts one of the following:
 *    SFViewAttribute, UIView, NSValue, NSArray
 *  see readme for more details.
 */
- (SFConstraint * (^)(id attr))lessThanOrEqualTo;

/**
 *	Optional semantic property which has no effect but improves the readability of constraint
 */
- (SFConstraint *)with;

/**
 *	Optional semantic property which has no effect but improves the readability of constraint
 */
- (SFConstraint *)and;

/**
 *	Creates a new SFCompositeConstraint with the called attribute and reciever
 */
- (SFConstraint *)left;
- (SFConstraint *)top;
- (SFConstraint *)right;
- (SFConstraint *)bottom;
- (SFConstraint *)leading;
- (SFConstraint *)trailing;
- (SFConstraint *)width;
- (SFConstraint *)height;
- (SFConstraint *)centerX;
- (SFConstraint *)centerY;
- (SFConstraint *)baseline;

#if TARGET_OS_IPHONE || TARGET_OS_TV

- (SFConstraint *)leftMargin;
- (SFConstraint *)rightMargin;
- (SFConstraint *)topMargin;
- (SFConstraint *)bottomMargin;
- (SFConstraint *)leadingMargin;
- (SFConstraint *)trailingMargin;
- (SFConstraint *)centerXWithinMargins;
- (SFConstraint *)centerYWithinMargins;

#endif


/**
 *	Sets the constraint debug name
 */
- (SFConstraint * (^)(id key))key;

// NSLayoutConstraint constant Setters
// for use outside of sf_updateConstraints/sf_makeConstraints blocks

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects SFConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeTop, NSLayoutAttributeLeft, NSLayoutAttributeBottom, NSLayoutAttributeRight
 */
- (void)setInsets:(SFEdgeInsets)insets;

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects SFConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeWidth, NSLayoutAttributeHeight
 */
- (void)setSizeOffset:(CGSize)sizeOffset;

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects SFConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeCenterX, NSLayoutAttributeCenterY
 */
- (void)setCenterOffset:(CGPoint)centerOffset;

/**
 *	Modifies the NSLayoutConstraint constant
 */
- (void)setOffset:(CGFloat)offset;


// NSLayoutConstraint Installation support

#if TARGET_OS_MAC && !(TARGET_OS_IPHONE || TARGET_OS_TV)
/**
 *  Whether or not to go through the animator proxy when modifying the constraint
 */
@property (nonatomic, copy, readonly) SFConstraint *animator;
#endif

/**
 *  Activates an NSLayoutConstraint if it's supported by an OS. 
 *  Invokes install otherwise.
 */
- (void)activate;

/**
 *  Deactivates previously installed/activated NSLayoutConstraint.
 */
- (void)deactivate;

/**
 *	Creates a NSLayoutConstraint and adds it to the appropriate view.
 */
- (void)install;

/**
 *	Removes previously installed NSLayoutConstraint
 */
- (void)uninstall;

@end


/**
 *  Convenience auto-boxing macros for SFConstraint methods.
 *
 *  Defining SF_SHORTHAND_GLOBALS will turn on auto-boxing for default syntax.
 *  A potential drawback of this is that the unprefixed macros will appear in global scope.
 */
#define sf_equalTo(...)                 equalTo(SFBoxValue((__VA_ARGS__)))
#define sf_greaterThanOrEqualTo(...)    greaterThanOrEqualTo(SFBoxValue((__VA_ARGS__)))
#define sf_lessThanOrEqualTo(...)       lessThanOrEqualTo(SFBoxValue((__VA_ARGS__)))

#define sf_offset(...)                  valueOffset(SFBoxValue((__VA_ARGS__)))


#ifdef SF_SHORTHAND_GLOBALS

#define equalTo(...)                     sf_equalTo(__VA_ARGS__)
#define greaterThanOrEqualTo(...)        sf_greaterThanOrEqualTo(__VA_ARGS__)
#define lessThanOrEqualTo(...)           sf_lessThanOrEqualTo(__VA_ARGS__)

#define offset(...)                      sf_offset(__VA_ARGS__)

#endif


@interface SFConstraint (AutoboxingSupport)

/**
 *  Aliases to corresponding relation methods (for shorthand macros)
 *  Also needed to aid autocompletion
 */
- (SFConstraint * (^)(id attr))sf_equalTo;
- (SFConstraint * (^)(id attr))sf_greaterThanOrEqualTo;
- (SFConstraint * (^)(id attr))sf_lessThanOrEqualTo;

/**
 *  A dummy method to aid autocompletion
 */
- (SFConstraint * (^)(id offset))sf_offset;

@end
