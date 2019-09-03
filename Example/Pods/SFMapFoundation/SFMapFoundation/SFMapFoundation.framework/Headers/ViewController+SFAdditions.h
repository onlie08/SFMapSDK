//
//  UIViewController+SFAdditions.h
//  SFMasonry
//
//  Created by Craig Siemens on 2015-06-23.
//
//

#import "SFUtilities.h"
#import "SFConstraintMaker.h"
#import "SFViewAttribute.h"

#ifdef SF_VIEW_CONTROLLER

@interface SF_VIEW_CONTROLLER (SFAdditions)

/**
 *	following properties return a new SFViewAttribute with appropriate UILayoutGuide and NSLayoutAttribute
 */
@property (nonatomic, strong, readonly) SFViewAttribute *sf_topLayoutGuide;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_bottomLayoutGuide;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_topLayoutGuideTop;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_topLayoutGuideBottom;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_bottomLayoutGuideTop;
@property (nonatomic, strong, readonly) SFViewAttribute *sf_bottomLayoutGuideBottom;


@end

#endif
