//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SFMapFoundation/SFMapFoundation.h>

#define MAX_LENGTH      10000

#define VIEWID_BASEVIEW_BASE     0      //起始的View的VIEWID
#define VIEWID_BASEPOPUP_BASE    1000   //起始的PopupView的VIEWID

@interface WXMBaseView : UIView
{
    int           _viewId;
    BOOL                _bModelView;
}

@property (nonatomic, assign) int viewId;
@property (nonatomic, assign) BOOL bModelView;

- (void)reloadNMData;
- (void)updateNMTheme;
- (void)updateToPortraitSize; //竖屏状态的View大小
- (void)updateToLandscapeSize; //横屏状态的View大小
- (void)updateLayoutSize; //手动更新触发布局位置

@end


@interface LDMBaseMapComponentView : WXMBaseView {
    BOOL    _fromTop;
}

@property (nonatomic, assign) BOOL fromTop;

- (void) setFrame:(CGRect)frame;
- (void) setHidden:(BOOL)hidden;
- (void) removeFromSuperview;

@end

@interface LDMMoveContentView : WXMBaseView
{
    
}
@end


@interface LDMMapClipView : WXMBaseView
{
}

@property (nonatomic, assign) CGPoint offset;

- (LNPoint) viewG20Point;

@end
