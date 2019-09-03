//
//  LDASIAuthenticationDialog.h
//  Created by sfmap on 16/4/20.
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class LDASIHTTPRequest;

typedef enum _LDASIAuthenticationType {
	LDASIStandardAuthenticationType = 0,
    LDASIProxyAuthenticationType = 1
} LDASIAuthenticationType;

@interface LDASIAutorotatingViewController : UIViewController
@end

@interface LDASIAuthenticationDialog : LDASIAutorotatingViewController <UIActionSheetDelegate, UITableViewDelegate, UITableViewDataSource> {
	LDASIHTTPRequest *request;
	LDASIAuthenticationType type;
	UITableView *tableView;
	UIViewController *presentingController;
	BOOL didEnableRotationNotifications;
}
+ (void)presentAuthenticationDialogForRequest:(LDASIHTTPRequest *)request;
+ (void)dismiss;

@property (retain) LDASIHTTPRequest *request;
@property (assign) LDASIAuthenticationType type;
@property (assign) BOOL didEnableRotationNotifications;
@property (retain, nonatomic) UIViewController *presentingController;
@end
