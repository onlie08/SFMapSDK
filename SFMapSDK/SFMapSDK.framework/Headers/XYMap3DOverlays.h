//
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import <Foundation/Foundation.h>
#ifdef BUILD_OGLES
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#elif BUILD_OGLES2
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif
#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CLLocation.h>
#import <SFMapFoundation/SFMapFoundation.h>
#import "XYMap3DView.h"
#import "LMKCustomDrawOverlay.h"

typedef void* me_mapengine;
typedef void* me_projection;

#define DRAW_LINE_WIDTH     4.0f
#define DRAW_LINE_LIMT      1.9f

typedef enum {
	XYMap3DOverlayDefaultPriority = 0,
	XYMap3DOverlayMaxPriority = 999,
} XYMap3DOverlayPriority;

typedef enum {
	XYMap3DOverlayTextureTypeNone = 0,
	XYMap3DOverlayTextureTypePin = 1,
	XYMap3DOverlayTextureTypeGPSIcon,
	XYMap3DOverlayTextureTypeGPSBreathe,
	XYMap3DOverlayTextureTypeLocationDirection,
	XYMap3DOverlayTextureTypeCompass,
	XYMap3DOverlayTextureTypeCar,
    XYMap3DOverlayTextureTypeCarDirection,
	XYMap3DOverlayTextureTypeTaxi,
    XYMap3DOverlayTextureTypeGPSROUND,
    XYMap3DOverlayTextureTypeGPSNaviSimple,
	XYMap3DOverlayTextureTypeDefaultLastOne,
    
	XYMap3DOverlayTextureTypeCustomBase = 100,
} XYMap3DOverlayTextureType;

#define XYMAP3DDEFAULTTEXTURE_NONE				@"DEFAULTTEXTURE_NONE"
#define XYMAP3DDEFAULTTEXTURE_DIY               @"DEFAULTTEXTURE_DIY"   //新增的自定义图层（整图）
#define XYMAP3DDEFAULTTEXTURE_PIN				@"DEFAULTTEXTURE_PIN"
#define XYMAP3DDEFAULTTEXTURE_GPSICON			@"DEFAULTTEXTURE_LOCATIONICON"
#define XYMAP3DDEFAULTTEXTURE_GPSROUND			@"DEFAULTTEXTURE_LOCATIONICONROUND"
#define XYMAP3DDEFAULTTEXTURE_GPSBREATHE			@"DEFAULTTEXTURE_LOCATIONBREATHE"
#define XYMAP3DDEFAULTTEXTURE_GPSDIRECTION		@"DEFAULTTEXTURE_LOCATIONDIRECTION"
#define XYMAP3DDEFAULTTEXTURE_COMPASS			@"DEFAULTTEXTURE_COMPASS"
#define XYMAP3DDEFAULTTEXTURE_CAR				@"DEFAULTTEXTURE_CAR"
#define XYMAP3DDEFAULTTEXTURE_CAR_DIRECTION     @"DEFAULTTEXTURE_CAR_DIRECTION"
#define XYMAP3DDEFAULTTEXTURE_TAXI				@"DEFAULTTEXTURE_TAXI"
#define XYMAP3DDEFAULTTEXTURE_DIRECTION_WHEEL	@"DEFAULTTEXTURE_DIRECTION_WHEEL"

//gongcong 20181213 add:新增步行导航GPS纹理
#define XYMAP3DDEFAULTTEXTURE_GPSNAVI_SIMPLE    @"DEFAULTTEXTURE_GPSNAVI_SIMPLE"

@class XYMap3DView;
@class XYMapWidthLine;

#pragma mark -
#pragma mark XYMap3DOverlayTexture
@interface XYMap3DOverlayTexture : NSObject {
	NSString		*_identifier;
	GLuint			_textureId;

	BOOL			_multiTexture;
	
	int				_verticeCount;
	
	GLuint			_vboVerticeBuffer;
	GLuint			_vboTexCoordBuffer;

	CGPoint			_offset;
	BOOL			_canBeTouch;
	
	CGFloat			_aspectRatio;	//	width/height
	BOOL			_followMapRotation;
	BOOL			_followMapCamera;
}

@property (nonatomic, copy) NSString *identifier;
@property (nonatomic, assign) GLuint textureId;
@property (nonatomic, assign) BOOL multiTexture;

@property (nonatomic, assign) int verticeCount;
@property (nonatomic, readonly) GLuint vboVerticeBuffer;
@property (nonatomic, readonly) GLuint vboTexCoordBuffer;

@property (nonatomic, assign) CGPoint offset;
@property (nonatomic, assign) BOOL canBeTouch;
@property (nonatomic, assign) CGFloat aspectRatio;
@property (nonatomic, assign) BOOL followMapRotation;
@property (nonatomic, assign) BOOL followMapCamera;

- (id)initWithIdentifier:(NSString *)identifier textureId:(GLuint)textureId isMultiTexture:(BOOL)multiTexture verticeCount:(int)verticeCount verticeTextureBuffer:(float *)verticeTextureBuffer;

- (void)drawOnMap:(XYMap3DView *)mapView fromGLCoordinate:(CGPoint)GLCoordinate drawSize:(CGSize)drawSize alpha:(CGFloat)alpha;
- (void)drawOnMap:(XYMap3DView *)mapView fromGLCoordinate:(CGPoint)GLCoordinate drawHeight:(CGFloat)drawHeight alpha:(CGFloat)alpha;
- (void)drawOnMap:(XYMap3DView *)mapView fromGLCoordinate:(CGPoint)GLCoordinate drawWidth:(CGFloat)drawWidth alpha:(CGFloat)alpha;

- (void)drawOnMap:(XYMap3DView *)mapView fromGLCoordinate:(CGPoint)GLCoordinate drawSize:(CGSize)drawSize;
- (void)drawOnMap:(XYMap3DView *)mapView fromGLCoordinate:(CGPoint)GLCoordinate drawHeight:(CGFloat)drawHeight;
- (void)drawOnMap:(XYMap3DView *)mapView fromGLCoordinate:(CGPoint)GLCoordinate drawWidth:(CGFloat)drawWidth;

- (void)drawOnMap:(XYMap3DView *)mapView fromG20Location:(LNPoint)G20Location drawSize:(CGSize)drawSize;
- (void)drawOnMap:(XYMap3DView *)mapView fromG20Location:(LNPoint)G20Location drawHeight:(CGFloat)drawHeight;
- (void)drawOnMap:(XYMap3DView *)mapView fromG20Location:(LNPoint)G20Location drawWidth:(CGFloat)drawWidth;

- (void)drawOnOrtho:(XYMap3DView *)mapView fromGLCoordinate:(CGPoint)GLCoordinate glLen:(CGFloat)glLen
              alpha:(CGFloat)alpha;
@end

#pragma mark -
#pragma mark XYMap3DOverlayTextureManager
@interface XYMap3DOverlayTextureManager : NSObject {
	GLuint					*_textureIDs;
	BOOL					*_textureStates;
    NSMutableArray          *_textureDynamicIDs;
	NSMutableDictionary		*_overlayTextures;
	NSArray					*_defaultTextureIdentifiers;
    
    GLuint                  _scalelineTextureID;
    GLuint                  _arrowlineTextureID;
    GLuint                  _arrowonlylineTextureID;
    GLuint                  _linkdottTextureID;
//    GLuint                  _colorlineTextureID;
    GLuint                  _clineRedTextureID;
    GLuint                  _clineOrangeTextureID;
    GLuint                  _clineGreenTextureID;
    GLuint                  _clineBlueTextureID;
    GLuint                  _clineGrayTextureID;
    GLuint                  _clineCyanTextureID;
    GLuint                  _clinePureGrayTextureID;
    
    GLuint                  _lineroundTextureID;
    GLuint                  _clineGrayRedTextureID;
}

- (instancetype)initWithMap3dView:(XYMap3DView *)map3dView;
- (GLuint)getTextureID;

- (BOOL)addTexture:(XYMap3DOverlayTexture *)texture;

- (XYMap3DOverlayTexture *)addTextureWithIdentifier:(NSString *)identifier image:(UIImage *)image isMultiTexture:(BOOL)multiTexture verticeCount:(int)verticeCount verticeTextureBuffer:(float *)verticeTextureBuffer;
- (XYMap3DOverlayTexture *)addTextureWithIdentifier:(NSString *)identifier textureFile:(NSString *)textureFile isMultiTexture:(BOOL)multiTexture verticeCount:(int)verticeCount verticeTextureBuffer:(float *)verticeTextureBuffer;

- (XYMap3DOverlayTexture *)addCircleTextureWithIdentifier:(NSString *)identifier textureParams:(NSDictionary*)paramsDict isMultiTexture:(BOOL)multiTexture verticeCount:(int)verticeCount verticeTextureBuffer:(float *)verticeTextureBuffer;

- (BOOL)containsTexture:(NSString *)identifier;

- (XYMap3DOverlayTexture *)textureWithIdentifier:(NSString *)identifier;

- (void)removeTexture:(XYMap3DOverlayTexture *)texture;
- (void)removeTextureWithIdentifier:(NSString *)identifier;

- (void)removeAllTexture;

//Additional
- (void)reloadArrowLineTextre:(BOOL)isNight;

@property (nonatomic, assign) GLuint    scalelineTextureID;
@property (nonatomic, assign) GLuint    arrowlineTextureID;
@property (nonatomic, assign) GLuint    arrowonlylineTextureID;
@property (nonatomic, assign) GLuint    linkdottTextureID;
//@property (nonatomic, assign) GLuint    colorlineTextureID;
@property (nonatomic, assign) GLuint    clineRedTextureID;
@property (nonatomic, assign) GLuint    clineOrangeTextureID;
@property (nonatomic, assign) GLuint    clineGreenTextureID;
@property (nonatomic, assign) GLuint    clineBlueTextureID;
@property (nonatomic, assign) GLuint    clineGrayTextureID;
@property (nonatomic, assign) GLuint    clineCyanTextureID;
@property (nonatomic, assign) GLuint    clinePureGrayTextureID;
@property (nonatomic, assign) GLuint    clineGrayRedTextureID;

@property (nonatomic, assign) GLuint    lineroundTextureID;
@property (nonatomic, assign) XYMap3DView *map3DView;
@end

typedef struct {
	CGFloat		width;		//max width is 32
	CGFloat		length;
	CGColorRef	color;
} ANDashPattern;

CG_INLINE ANDashPattern ANDashPatternMake(CGFloat width, CGFloat length, CGColorRef color);

CG_INLINE ANDashPattern ANDashPatternMake(CGFloat width, CGFloat length, CGColorRef color)
{
	ANDashPattern pattern; pattern.width = width; pattern.length = length; pattern.color = color; return pattern;
}

@interface NSValue (NSValueDashPatternExtensions)
+ (NSValue *)valueWithANDashPattern:(ANDashPattern)pattern;
- (ANDashPattern)ANDashPatternValue;
@end

#pragma mark -
#pragma mark XYMap3DDashTexture
@interface XYMap3DDashTextureImage : NSObject {
}

// 纹理图片尺寸 64 x 64
+ (GLuint)dashTextureWithDashPatterns:(NSArray *)dashPatterns; // 总长度必须等于 64.
+ (GLuint)dashTextureWithDashPatterns:(NSArray *)dashPatterns textureId:(GLuint)textureId;
+ (GLuint)circleTextureWithDict:(NSDictionary *)paramsDict;

@end


#pragma mark -
#pragma mark XYMap3DOverlay
@interface XYMap3DOverlay : NSObject {
	BOOL					_visible;
	BOOL					_canBeTouch;
	XYMap3DOverlayPriority	_priorityBeforeChange;
	XYMap3DOverlayPriority	_priority;

	CGRect					_touchArea;
}

@property (nonatomic, assign) BOOL visible;
@property (nonatomic, assign) BOOL canBeTouch;
@property (nonatomic, assign) XYMap3DOverlayPriority priority;

@property (nonatomic, readonly) CGRect touchArea;

@property (nonatomic, assign) XYMap3DView *map3dView;

- (BOOL)touchMe:(CGPoint)point;
- (void)restorePriority;

- (void)drawOnMap:(me_projection)proj;

@end

#pragma mark -
#pragma mark XYMap3DPointOverlay

typedef NS_OPTIONS(NSUInteger, XYMap3DPointAnimation) {
	XYMap3DPointAnimationNone				= 0,
	XYMap3DPointAnimationDrop				= 1,
	XYMap3DPointAnimationGrow				= 2,
	XYMap3DPointAnimationMove				= 3,	//用于 gps
};

typedef NS_OPTIONS(NSUInteger, XYMap3DPointAnimationOption) {
	XYMap3DPointAnimationOptionNone		= 0,
	XYMap3DPointAnimationOptionDelay		= 1,
};

typedef struct {
	CGFloat		phaseTime;

	CGSize		beginSizeRatio;
	CGSize		endSizeRatio;

	CGPoint		beginPosOffset;
	CGPoint		endPosOffset;

	CGFloat		beginAplha;
	CGFloat		endAplha;
} XYMap3DPointAnimationPhase;

#pragma mark -
#pragma mark XYMap3DPointAnimationPhase Prototypes
#pragma mark -
static __inline__ void sfMapAnimationPhaseInitial(XYMap3DPointAnimationPhase *phase);

#pragma mark -
#pragma mark XYMap3DPointAnimationPhase Implementations
#pragma mark -

static __inline__ void sfMapAnimationPhaseInitial(XYMap3DPointAnimationPhase *phase)
{
	phase->phaseTime = 0;
	phase->beginPosOffset = phase->endPosOffset = CGPointMake(0, 0);
	phase->beginSizeRatio = phase->endSizeRatio = CGSizeMake(1, 1);
	phase->beginAplha = phase->endAplha = 1;
}

@interface XYMap3DPointOverlay : XYMap3DOverlay {
	CGPoint						_calloutOffset;
	
	LNPoint						_fromLocation;
	NSMutableArray				*_haveTextures;
	
	CGSize						_overlaySize;
	
	NSInteger					_overlayIndex;
	
	XYMap3DPointAnimation		_animationType;
	XYMap3DPointAnimationOption	_animationOption;
	NSUInteger					_animationPhase;
	NSUInteger					_animationPhaseCount;
	XYMap3DPointAnimationPhase	*_animationPhaseList;
	NSDate						*_animationTimestamp;
	NSTimeInterval				_animationDelayTime;
	BOOL						_needTellAnimationFinish;
}

@property (nonatomic, assign) CGPoint calloutOffset;

@property (nonatomic, assign, setter=moveToLocation:) LNPoint fromLocation;
@property (nonatomic) CGSize overlaySize;

@property (nonatomic, assign) NSInteger overlayIndex;

- (id)initWithPointIndex:(NSInteger)index fromLocation:(LNPoint)fromLocation mapView:(XYMap3DView*)mapView; //无动画
- (id)initWithPointIndex:(NSInteger)index fromLocation:(LNPoint)fromLocation dropAnimated:(BOOL)dropAnimated mapView:(XYMap3DView*)mapView;
- (id)initWithPointIndex:(NSInteger)index fromLocation:(LNPoint)fromLocation animationType:(XYMap3DPointAnimation)type mapView:(XYMap3DView*)mapView;
- (id)initWithPointIndex:(NSInteger)index fromLocation:(LNPoint)fromLocation animationType:(XYMap3DPointAnimation)type animationOption:(XYMap3DPointAnimationOption)option mapView:(XYMap3DView*)mapView;


+ (id)pointOverlayWithPointIndex:(NSInteger)index fromLocation:(LNPoint)fromLocation mapView:(XYMap3DView*)mapView; //无动画
+ (id)pointOverlayWithPointIndex:(NSInteger)index fromLocation:(LNPoint)fromLocation dropAnimated:(BOOL)dropAnimated mapView:(XYMap3DView*)mapView;
+ (id)pointOverlayWithPointIndex:(NSInteger)index fromLocation:(LNPoint)fromLocation animationType:(XYMap3DPointAnimation)type mapView:(XYMap3DView*)mapView;
+ (id)pointOverlayWithPointIndex:(NSInteger)index fromLocation:(LNPoint)fromLocation animationType:(XYMap3DPointAnimation)type animationOption:(XYMap3DPointAnimationOption)option mapView:(XYMap3DView*)mapView;


- (void)addTexture:(XYMap3DOverlayTexture *)texture;

- (void)moveToLocation:(LNPoint)location;

- (void)setOverlaySizeWithOverlayWidth:(CGFloat)overlayWidth;
- (void)setOverlaySizeWithOverlayHeight:(CGFloat)overlayHeight;

// > 0 大， ＝ 0 相等  < 0 小
- (int)compareWithPoint:(XYMap3DPointOverlay *)pOvlay;

@end

#pragma mark -
#pragma mark XYMap3DCarOverlay
@interface XYMap3DCarOverlay : XYMap3DPointOverlay {
	float				_shadow_alpha;
	float				_shadow_alpha_fade;

	float				_directionAngle;
    float               _carDirection;
    CGSize              _carDirectionSize;// 方向尺寸
}

@property (nonatomic, assign) float directionAngle; // 地图正北方向偏移角度 默认 0
@property (nonatomic, assign) float carDirection;   // 车头方向，默认是0，需要外部设置
@property (nonatomic, assign) BOOL  carDirectionVisible;// 默认YES

- (void)showMapDirection:(BOOL)showFlag;// 是否显示“东西南北”方向
//- (void)showCarWithGPS:(BOOL)haveGPS;
- (void)setCarDirectionSize:(CGSize)carDirectionSize;

@end

#pragma mark -
#pragma mark XYMap3DTaxiCarOverlay

@interface XYMap3DTaxiCarOverlay : XYMap3DPointOverlay {
	float				_directionAngle;
}

@property (nonatomic, assign) float directionAngle;

@end

#pragma mark -
#pragma mark XYMap3DGPSOverlay
#define CIRCLE_SEGMENT 722

@interface XYMap3DGPSOverlay : XYMap3DPointOverlay {
	CLLocationAccuracy	_radius;
	GLfloat				_circleVertices[CIRCLE_SEGMENT*3];
	float				_shadow_alpha;
	float				_shadow_alpha_fade;
	float				_compassAngle;
	float				_compassAccuracy;
	int				    _directionMode;
    
	CGSize				_directionOverlaySize;
	
	LNPoint				_animationNeedMoveDistance;
	LNPoint				_animationBeginLocation;
    int              _unitWin2P20Len;
    float            _oldzoomer;
}

@property (nonatomic, assign) float compassAngle;
@property (nonatomic, assign) float compassAccuracy;
@property (nonatomic, assign) BOOL showDirectionWheel;
@property (nonatomic, assign) CGSize wheelSize;
@property (nonatomic, copy  ) UIColor *circleColor;
@property (nonatomic, copy  ) UIColor *circleBorderColor;

- (void)updateGPSLocation:(LNPoint)gpsLocation radius:(CLLocationAccuracy)radius renderMap:(BOOL)render;//默认有动画
- (void)updateGPSLocation:(LNPoint)gpsLocation radius:(CLLocationAccuracy)radius animated:(BOOL)animated renderMap:(BOOL)render;
- (void)changeToDirectionMode;
- (void)changeToNormalMode;
- (void)changeToGPSSimpleNaviMode;
- (void)drawGps:(me_projection)proj;
- (bool)isNeedUpdateGpsLocation:(LNPoint)gpsLocation;
@end

#pragma mark -
#pragma mark XYMap3DMoveableOverlay
@interface XYMap3DMoveableOverlay : XYMap3DPointOverlay {
	BOOL		_isMoving;
	
	CGFloat		_movingLeaveHeight;
	CGFloat		_maxMovingLeaveHeight;
	
	BOOL		_toNormalAnimated;
	CGFloat		_animatedPos;
	CGFloat		_animatedPosChange;
}

@property (nonatomic, readonly) BOOL isMoving;
@property (nonatomic, assign) CGFloat movingLeaveHeight;

- (id)initWithfromLocation:(LNPoint)fromLocation mapView:(XYMap3DView*)mapView; //无动画
- (id)initWithfromLocation:(LNPoint)fromLocation dropAnimated:(BOOL)dropAnimated mapView:(XYMap3DView*)mapView;
- (id)initWithfromLocation:(LNPoint)fromLocation animationType:(XYMap3DPointAnimation)type mapView:(XYMap3DView*)mapView;
- (id)initWithfromLocation:(LNPoint)fromLocation animationType:(XYMap3DPointAnimation)type animationOption:(XYMap3DPointAnimationOption)option mapView:(XYMap3DView*)mapView;

+ (id)overlayWithfromLocation:(LNPoint)fromLocation mapView:(XYMap3DView*)mapView; //无动画
+ (id)overlayWithfromLocation:(LNPoint)fromLocation dropAnimated:(BOOL)dropAnimated mapView:(XYMap3DView*)mapView;
+ (id)overlayWithfromLocation:(LNPoint)fromLocation animationType:(XYMap3DPointAnimation)type mapView:(XYMap3DView*)mapView;
+ (id)overlayWithfromLocation:(LNPoint)fromLocation animationType:(XYMap3DPointAnimation)type animationOption:(XYMap3DPointAnimationOption)option mapView:(XYMap3DView*)mapView;

- (void)changeToMove;
- (void)changeToNormal;

@end

#pragma mark -
#pragma mark XYMap3DCompassOverlay

@interface XYMap3DCompassOverlay : XYMap3DPointOverlay {
	CGPoint			_screenPoint;
	CGPoint			_screenPointStart;
	CGPoint			_screenPointFinal;
	NSTimeInterval	_screenPointAnimationTime;
	NSDate			*_screenPointAnimationTimeStamp;

	CGFloat			_alpha;
	CGFloat			_alphaChangeStep;
}

@property (nonatomic, assign) CGPoint screenPoint;
@property (nonatomic, assign) CGFloat alpha;

- (void)setScreenPoint:(CGPoint)screenPoint; //无动画
- (void)setScreenPoint:(CGPoint)screenPoint animated:(BOOL)animated; //默认动画时长为0.2秒
- (void)setScreenPoint:(CGPoint)screenPoint animated:(BOOL)animated animationTime:(NSTimeInterval)animationTime;
- (void)hideWithAnimated;

@end

#pragma mark -
#pragma mark XYMap3DCalloutOverlay

@interface XYMap3DCalloutOverlay : XYMap3DOverlay {
	CGPoint			_screenPoint;
}

@property (nonatomic, assign) CGPoint screenPoint;

@end

#pragma mark -
#pragma mark XYMap3DLineOverlay

typedef struct {
	LNPoint		point;
	CGPoint		GLCoordinate;
	BOOL		skip;
	BOOL		inRect;
} WXMLPoint;

typedef enum {
	XYMap3DLineNormal		= -1,	// 需要设置颜色
	XYMap3DLineRed			= 0,
	XYMap3DLineOrange		= 1,
	XYMap3DLineGreen			= 2,
	XYMap3DLineBlue			= 3,
	XYMap3DLineGray			= 4,
	XYMap3DLineCyan			= 5,
	XYMap3DLinePureGray		= 6,
    XYMap3DLineGrayRed       = 7,
	XYMap3DLineWithArrow		= 1001,
	XYMap3DLineOnlyArrow		= 1002,
	XYMap3DLineDashes		= 1003,
    XYMap3DLineDashesGray   = 1004,
    XYMap3DLineCustomDash	= 1005,
    XYMap3DLineWithArrowRev	= 1006,
} XYMap3DLineType;

@interface XYMap3DLineOverlay : XYMap3DOverlay {
	NSMutableArray			*_widthLines;
	CGFloat					_calcZoomer;

	NSInteger				_pointsCount;
	WXMLPoint				*_linePoints;

	NSMutableArray			*_allUsingPoints;
	LNRect					_calcG20Rect;

	CGFloat					_lineWidth;
	
	XYMap3DLineType			_lineType;

	GLfloat					_colorComponents[4];
    GLfloat                 _bgColorComponents[4];
    
    int                     _lineTmpIdx;
}

@property (nonatomic, readonly) XYMap3DLineType lineType;
@property (nonatomic, assign) NSInteger touchAreaEnlargeTimes; //默认值为6

- (id)initWithG20Points:(NSArray *)G20Points lineColor:(UIColor *)lineColor; // 默认线宽 4.0f;
- (id)initWithG20Points:(NSArray *)G20Points lineColor:(UIColor *)lineColor lineWidth:(CGFloat)lineWidth;
- (id)initWithG20Points:(NSArray *)G20Points lineColor:(UIColor *)lineColor lineType:(XYMap3DLineType)lineType;
- (id)initWithG20Points:(NSArray *)G20Points lineType:(XYMap3DLineType)lineType;
- (id)initWithG20Points:(NSArray *)G20Points lineType:(XYMap3DLineType)lineType lineWidth:(CGFloat)lineWidth;
- (id)initWithG20Points:(NSArray *)G20Points customDashTexture:(GLuint)textureId;
- (id)initWithG20Points:(NSArray *)G20Points customDashTexture:(GLuint)textureId lineWidth:(CGFloat)lineWidth;
- (id)initWithG20Points:(NSArray *)G20Points lineColor:(UIColor *)lineColor lineWidth:(CGFloat)lineWidth lineType:(XYMap3DLineType)lineType;

+ (id)lineOverlayWithG20Points:(NSArray *)G20Points lineColor:(UIColor *)lineColor;
+ (id)lineOverlayWithG20Points:(NSArray *)G20Points lineColor:(UIColor *)lineColor lineWidth:(CGFloat)lineWidth;
+ (id)lineOverlayWithG20Points:(NSArray *)G20Points lineColor:(UIColor *)lineColor lineType:(XYMap3DLineType)lineType;
+ (id)lineOverlayWithG20Points:(NSArray *)G20Points lineType:(XYMap3DLineType)lineType;
+ (id)lineOverlayWithG20Points:(NSArray *)G20Points lineType:(XYMap3DLineType)lineType lineWidth:(CGFloat)lineWidth;
+ (id)lineOverlayWithG20Points:(NSArray *)G20Points customDashTexture:(GLuint)textureId;
+ (id)lineOverlayWithG20Points:(NSArray *)G20Points customDashTexture:(GLuint)textureId lineWidth:(CGFloat)lineWidth;
+ (id)lineOverlayWithG20Points:(NSArray *)G20Points lineColor:(UIColor *)lineColor lineWidth:(CGFloat)lineWidth lineType:(XYMap3DLineType)lineType;

- (void)setNeedRecalc;
- (void)setLineColor:(UIColor *)lineColor lineWidth:(CGFloat)lineWidth;
- (void)setLineType:(XYMap3DLineType)lineType lineWidth:(CGFloat)lineWidth;
- (void)setLineType:(XYMap3DLineType)lineType lineColor:(UIColor *)lineColor lineWidth:(CGFloat)lineWidth;

//- (void)resetTouchTestBuffer;
- (void)calcOnMap:(me_projection)proj;

- (BOOL)touchLine:(WXMLPoint*)points ofCount:(NSInteger)count atPoint:(CGPoint)point;
- (XYMapWidthLine*)getNewLine:(XYMap3DLineType)lineType WithColor:(GLfloat[4])color ofWidth:(GLfloat)width;

@end

#pragma mark -
#pragma mark XYMap3DRainbowOverlay
@interface XYMap3DRainbowOverlay : XYMap3DLineOverlay {
}

@property (nonatomic, assign) BOOL highlight;

- (id)initWithRainbow:(NSArray *)rainbow; //rainbow: {{Point1, Point2, ..., Color}, {Point1, Point2, ..., Color}, ...}
- (id)initWithRainbow:(NSArray *)rainbow lineWidth:(CGFloat)lineWidth;

+ (id)rainbowOverlayWithRainbow:(NSArray *)rainbow;
+ (id)rainbowOverlayWithRainbow:(NSArray *)rainbow lineWidth:(CGFloat)lineWidth;

@end

#pragma mark -
#pragma mark XYMap3DNaviOverlay
@interface XYMap3DNaviOverlay : XYMap3DLineOverlay {
	BOOL					_needRecalc;

	CGFloat					_overColorComponents[4];
	CGFloat					_nextColorComponents[4];

	CGFloat					_leaveColorComponents[4];
	CGFloat					_leaveLineWidth;
	CGFloat					_leaveLineSegLength;
	
	LNPoint					_gpsLocation;
	NSInteger				_snapToIndex;
	BOOL					_snapIsSegmentFirst;
	LNPoint					_snapToLocation;
	
	GLfloat					*_deviatedLineVertices;
}

+ (id)naviOverlayWithG20Points:(NSArray *)G20Points overColor:(UIColor *)overColor nextColor:(UIColor *)nextColor;
+ (id)naviOverlayWithG20Points:(NSArray *)G20Points overColor:(UIColor *)overColor nextColor:(UIColor *)nextColor lineWidth:(CGFloat)lineWidth;

- (id)initWithG20Points:(NSArray *)G20Points overColor:(UIColor *)overColor nextColor:(UIColor *)nextColor; //默认线宽4.0f;
- (id)initWithG20Points:(NSArray *)G20Points overColor:(UIColor *)overColor nextColor:(UIColor *)nextColor lineWidth:(CGFloat)lineWidth;

//默认颜色为黑色, 默认线宽为_lineWidth/2, 默认seg长度为_lineWidth*4
- (void)setLeaveLineColor:(UIColor *)leaveLineColor leaveLineWidth:(CGFloat)leaveLineWidth leaveLineSegLength:(CGFloat)leaveLineSegLength;

- (void)carAtLocation:(LNPoint)G20Location snapToIndex:(NSInteger)snapToIndex snapToLocation:(LNPoint)snapToLocation snapIsSegmentFirst:(BOOL)snapIsSegmentFirst;

- (void)setNeedRecalc;

- (void)setRouteArrowColor:(UIColor *)color1 color2:(UIColor *)color2;
- (void)setRouteArrowWidth:(CGFloat)arrowWidth;
- (void)showRouteArrow:(NSArray *)arrowPoints;

@end

#pragma mark -
#pragma mark XYMap3DArrowOverlay
@interface XYMap3DArrowOverlay : XYMap3DLineOverlay {
}

@property (nonatomic, assign) BOOL highlight;
- (id)initWithG20Points:(NSArray *)G20Points;
- (id)initWithG20Points:(NSArray *)G20Points topColor:(UIColor *)topColor sideColor:(UIColor *)sideColor;
- (id)initWithG20Points:(NSArray *)G20Points arrowWidth:(CGFloat)arrowWidth sideHeight:(CGFloat)sideHeight;
- (id)initWithG20Points:(NSArray *)G20Points topColor:(UIColor *)topColor sideColor:(UIColor *)sideColor arrowWidth:(CGFloat)arrowWidth sideHeight:(CGFloat)sideHeight;

+ (id)arrowOverlayWithG20Points:(NSArray *)G20Points;
+ (id)arrowOverlayWithG20Points:(NSArray *)G20Points topColor:(UIColor *)topColor sideColor:(UIColor *)sideColor;
+ (id)arrowOverlayWithG20Points:(NSArray *)G20Points arrowWidth:(CGFloat)arrowWidth sideHeight:(CGFloat)sideHeight;
+ (id)arrowOverlayWithG20Points:(NSArray *)G20Points topColor:(UIColor *)topColor sideColor:(UIColor *)sideColor arrowWidth:(CGFloat)arrowWidth sideHeight:(CGFloat)sideHeight;

- (void)setArrowG20Points:(NSArray *)G20Points;
- (void)setTopColor:(UIColor *)topColor sideColor:(UIColor *)sideColor;
- (void)setArrowWidth:(CGFloat)arrowWidth sideHeight:(CGFloat)sideHeight;
- (void)setTopColor:(UIColor *)topColor sideColor:(UIColor *)sideColor arrowWidth:(CGFloat)arrowWidth sideHeight:(CGFloat)sideHeight;
- (void)setMinDisplayZoomer:(CGFloat)minDisplayZoomer; //default 16

@end

#pragma mark -
#pragma mark XYMap3DPolygonOverlay
@interface XYMap3DPolygonOverlay : XYMap3DOverlay {
	GLfloat			_colorComponents[4];

	LNPoint			*_G20Points;
	NSInteger		_pointsCount;
	
	CGFloat			_calcZoomer;
	LNRect			_calcG20Rect;
	BOOL			_needRecalc;
}

+ (id)polygonOverlayWithG20Points:(NSArray *)G20Points color:(UIColor *)color;

- (id)initWithG20Points:(NSArray *)G20Points color:(UIColor *)color;

- (void)setNeedRecalc;

@end

#pragma mark - XYMap3DNoCoverPointOverlay

@interface XYMap3DNoCoverPointOverlay : XYMap3DPointOverlay
{
    NSInteger   _noCoverLevel;
}

@property (nonatomic, assign) NSInteger noCoverIdentify;
@property (nonatomic, assign) NSInteger noCoverLevel;
@property (nonatomic, assign) BOOL iconVisible;
@property (nonatomic, assign) BOOL contentVisible;
@property (nonatomic, assign) BOOL currentContentVisible;

- (void)addIconTexture:(XYMap3DOverlayTexture *)texture;
- (void)addContentTexture:(XYMap3DOverlayTexture *)texture;
- (void)showContentTexture:(BOOL)shown;
- (CGRect)iconTexturesRect;
- (CGRect)contentTextureRect;

- (void)setHighlightedTextureHeight:(CGFloat)height;

@end

#pragma mark -
#pragma mark XYMap3DLayerManager
@protocol XYMap3DLayerManagerDelegate;
@class XYMap3DScaleLineOverlay;

@interface XYMap3DLayerManager : NSObject {
	id<XYMap3DLayerManagerDelegate>	_delegate;
	NSMutableDictionary				*_layersList;

	NSMutableArray					*_allPointOverlays;
	NSMutableArray					*_allLineOverlays;
	NSMutableArray					*_allPolygonOverlays;
    NSMutableArray                  *_allCustomOverlays;

	XYMap3DPointOverlay				*_highlightOverlayPoint;
	
    XYMap3DScaleLineOverlay          *_scaleLineOverlay;
	XYMap3DGPSOverlay				*_gpsOverlay;
	XYMap3DCompassOverlay			*_compassOverlay;
	XYMap3DPointOverlay				*_labelOverlay;
    XYMap3DCarOverlay               *_carOverlay;
	
	char							_referenceGridName[32];
}

@property (nonatomic, assign) id<XYMap3DLayerManagerDelegate> delegate;
@property (nonatomic, retain) XYMap3DPointOverlay *highlightOverlayPoint;
@property (nonatomic, retain) XYMap3DScaleLineOverlay  *scaleLineOverlay;
@property (nonatomic, retain) XYMap3DGPSOverlay *gpsOverlay;
@property (nonatomic, retain) XYMap3DCarOverlay *carOverlay;
@property (nonatomic, retain) XYMap3DCompassOverlay *compassOverlay;
@property (nonatomic, assign) XYMap3DView *map3dView;

- (instancetype)initWithMap3dView:(XYMap3DView *)map3dView;

- (BOOL)addOverlay:(XYMap3DOverlay *)overlay toLayer:(NSString *)layerIdentifier;
- (BOOL)removeOverlay:(XYMap3DOverlay *)overlay fromLayer:(NSString *)layerIdentifier;
- (NSArray *)overlaysOnLayer:(NSString *)layerIdentifier;
- (BOOL)containsLayer:(NSString *)layerIdentifier;

- (void)removeLayer:(NSString *)layerIdentifier;
- (void)removeAllLayer;

- (void)drawOrthoLayers:(void *)proj;
- (void)drawBeforeLabel:(void *)proj;
- (void)drawAfterLabel:(void *)proj;

- (BOOL)inNaviMode;

- (void)showLayer:(NSString *)layerIdentifier;
- (void)showLayers:(NSArray *)layerIdentifiersArray;

- (void)hideLayer:(NSString *)layerIdentifier;
- (void)hideAllLayers;

- (void)setLayer:(NSString*)layerIdentifier maxShownCount:(NSInteger)maxCount;

- (NSArray *)touchLinesTest:(CGPoint)point;

- (BOOL)touchAtPoint:(CGPoint)point;

- (void)highlightOverlayPoint:(NSInteger)overlayIndex ofLayer:(NSString *)layerIdentifier;
- (void)highlightOverlayRainbow:(XYMap3DRainbowOverlay *)rainbowOverlay ofLayer:(NSString *)layerIdentifier;
- (void)highlightGPSPoint;
- (void)unHighlightedOverlayPoint;

- (void)setLockHighlightPoint:(BOOL)locked;

- (void)addCustomDrawOverlay:(LMKCustomDrawOverlay *)customOverlay;
- (void)addCustomDrawOverlays:(NSArray *)customOverlays;
- (void)removeCustomDrawOverlay:(LMKCustomDrawOverlay *)customOverlay;
- (void)removeAllCustomDrawOverlays;
@end

@protocol XYMap3DLayerManagerDelegate <NSObject>
@optional
- (void)touchOnLabel:(NSString *)poiId lableName:(NSString *)labelName location:(LNPoint)location; //location is G20 location
- (void)touchOnLines:(NSArray *)lineOverlays;
- (void)highlightPoint:(XYMap3DPointOverlay *)pointOverlay inLayer:(NSString *)layerIdentifier;
- (void)unHighlightPoint;
- (void)unHighlightPointFromLayer:(NSString *)layerIdentifier overlayIndex:(NSInteger)overlayIndex;
- (void)tappedOnCompass;
- (void)pointOverlayAnimationFinish:(XYMap3DPointOverlay *)pointOverlay;
@end

@interface XYMap3DRainbowNaviOverlay : XYMap3DRainbowOverlay

- (void)setRouteArrowColor:(UIColor *)color1 color2:(UIColor *)color2;
- (void)setRouteArrowWidth:(CGFloat)arrowWidth;
- (void)showRouteArrow:(NSArray *)arrowPoints;

@end
