//
//  LMKOverlayView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKGeometry.h"
#import "LMKLineDrawType.h"
#import "LMKOverlay.h"
#import <UIKit/UIKit.h>

@class LMKMapView;

#define kLMKOverlayViewDefaultStrokeColor [UIColor colorWithRed:0.3 green:0.63 blue:0.89 alpha:0.8]
#define kLMKOverlayViewDefaultFillColor [UIColor colorWithRed:0.77 green:0.88 blue:0.94 alpha:0.8]

/*!
 @brief 该类是地图覆盖物View的基类, 提供绘制overlay的接口但并无实际的实现
 */
@interface LMKOverlayView : UIView

/*!
 @brief 初始化并返回一个overlay view
 @param overlay 关联的overlay对象
 @return 初始化成功则返回overlay view,否则返回nil
 */
- (id)initWithOverlay:(id<LMKOverlay>)overlay;

/*!
 @brief 关联的overlay对象
 */
@property (nonatomic, readonly, strong) id<LMKOverlay> overlay;

/*!
 @brief 关联的地图对象
 */
@property (nonatomic, weak) LMKMapView *lmkMapView;

/*!
 @brief 将LMKMapPoint转化为相对于receiver的本地坐标
 @param mapPoint 要转化的LMKMapPoint
 @return 相对于receiver的本地坐标
 */
- (CGPoint)pointForMapPoint:(LMKMapPoint)mapPoint;

/*!
 @brief 将相对于receiver的本地坐标转化为LMKMapPoint
 @param point 要转化的相对于receiver的本地坐标
 @return LMKMapPoint
 */
- (LMKMapPoint)mapPointForPoint:(CGPoint)point;

/*!
 @brief 将LMKMapRect转化为相对于receiver的本地rect
 @param mapRect 要转化的LMKMapRect
 @return 相对于receiver的本地rect
 */
- (CGRect)rectForMapRect:(LMKMapRect)mapRect;

/*!
 @brief 将相对于receiver的本地rect转化为LMKMapRect
 @param rect 要转化的相对于receiver的本地rect
 @return LMKMapRect
 */
- (LMKMapRect)mapRectForRect:(CGRect)rect;

/*!
 @brief 绘制overlay view的内容
 @param mapRect 该LMKMapRect范围内需要更新
 @param zoomScale 当前的缩放比例值
 @param context 绘制操作的graphics context
 */
- (void)drawMapRect:(LMKMapRect)mapRect
          zoomScale:(CGFloat)zoomScale
          inContext:(CGContextRef)context;

/*!
 @brief 缓存的G20坐标
 */
@property (nonatomic) int* g20MapPoints;

/*!
 @brief 缓存的G20坐标 个数
 */
@property (nonatomic) NSUInteger g20MapPointCount;

/*!
 @brief 批量将LMKMapPoint转换为opengles可以直接使用的坐标
 @param mapPoints LMKMapPoint坐标数据指针
 @param count 个数
 @return opengles 直接支持的坐标数据指针(需要调用者手动释放)
 */
- (int*)g20PointsForMapPoints:(LMKMapPoint*)mapPoints count:(NSUInteger)count;

/*!
 @brief 将屏幕尺寸转换为OpenGLES尺寸
 @param windowWidth 屏幕尺寸
 @return OpenGLES尺寸
 */
- (CGFloat)glWidthForWindowWidth:(CGFloat)windowWidth;

/*!
 @brief OpenGLES坐标系发生改变, 重新计算缓存的OpenGLES坐标
 */
- (void)referenceDidChange;
/*!
 @brief 使用OpenGLES 绘制区域
 @param points OpenGLES坐标系点指针, 参考- (CGPoint)glPointForMapPoint:(LMKMapPoint)mapPoint, - (CGPoint *)glPointsForMapPoints:(LMKMapPoint *)mapPoints count:(NSUInteger)count
 @param pointCount 点个数
 @param fillColor 填充颜色
 @param usingTriangleFan 若必为凸多边形输入YES，可能为凹多边形输入NO
 */
- (void)renderRegionWithPoints:(int *)points
                    pointCount:(NSUInteger)pointCount
                     fillColor:(UIColor *)fillColor
              usingTriangleFan:(BOOL)usingTriangleFan;
/*!
 @brief 使用OpenGLES 绘制图片
 @param textureID OpenGLES纹理ID
 @param points OpenGLES坐标系点指针,纹理矩形的四个顶点坐标,其第一个坐标为图片左上角，依次顺时针传入其他顶点 ,参考- (CGPoint)glPointForMapPoint:(LMKMapPoint)mapPoint, - (CGPoint *)glPointsForMapPoints:(LMKMapPoint *)mapPoints count:(NSUInteger)count ，
 */
- (void)renderIconWithTextureID:(GLuint)textureID points:(int *)points;
/*!
 @brief 使用OpenGLES 绘制线
 @param points OpenGLES坐标系点指针, 参考- (CGPoint)glPointForMapPoint:(LMKMapPoint)mapPoint, - (CGPoint *)glPointsForMapPoints:(LMKMapPoint *)mapPoints count:(NSUInteger)count
 @param pointCount 点个数
 @param strokeColor 线颜色
 @param lineWidth OpenGLES支持线宽尺寸, 参考 - (CGFloat)glWidthForWindowWidth:(CGFloat)windowWidth
 @param looped 是否闭合, 如polyline会设置NO, polygon会设置YES.
 */
- (void)renderLinesWithPoints:(int*)points
                   pointCount:(NSUInteger)pointCount
                  strokeColor:(UIColor*)strokeColor
                    lineWidth:(CGFloat)lineWidth
                       looped:(BOOL)looped;

/*!
 使用OpenGLES 绘制线
 @param points       OpenGLES坐标系点指针, 参考- (CGPoint)glPointForMapPoint:(LMKMapPoint)mapPoint, - (CGPoint *)glPointsForMapPoints:(LMKMapPoint *)mapPoints count:(NSUInteger)count
 @param pointCount   点个数
 @param strokeColor  线颜色
 @param lineWidth    OpenGLES支持线宽尺寸, 参考 - (CGFloat)glWidthForWindowWidth:(CGFloat)windowWidth
 @param looped       是否闭合, 如polyline会设置NO, polygon会设置YES.
 @param lineJoinType 线连接点样式
 @param lineCapType  线端点样式
 @param lineDash     是否是虚线
 */
- (void)renderLinesWithPoints:(int*)points
                   pointCount:(NSUInteger)pointCount
                  strokeColor:(UIColor*)strokeColor
                    lineWidth:(CGFloat)lineWidth
                       looped:(BOOL)looped
                 LineJoinType:(LMKLineJoinType)lineJoinType
                  LineCapType:(LMKLineCapType)lineCapType
                     lineDash:(BOOL)lineDash;

/*!
   使用OpenGLES 绘制线
 
   @param points        OpenGLES坐标系点指针, 参考- (CGPoint)glPointForMapPoint:(LMKMapPoint)mapPoint, - (CGPoint *)glPointsForMapPoints:(LMKMapPoint *)mapPoints count:(NSUInteger)count
   @param pointCount    点个数
   @param strokeColor   线颜色
   @param lineWidth     OpenGLES支持线宽尺寸, 参考 - (CGFloat)glWidthForWindowWidth:(CGFloat)windowWidth
   @param lineTextureID OpenGLES纹理ID
   @param texLen        纹理长度
   @param looped        是否闭合, 如polyline会设置NO, polygon会设置YES.
   @param complex       是否是复杂纹理
 */
- (void)renderLinesWithPoints:(int*)points
                   pointCount:(NSUInteger)pointCount
                  strokeColor:(UIColor*)strokeColor
                    lineWidth:(CGFloat)lineWidth
                lineTextureID:(GLint)lineTextureID
                       texLen:(CGFloat)texLen
                       looped:(BOOL)looped
                      complex:(BOOL)complex;
/*!
 使用OpenGLES 绘制线
 @param points       OpenGLES坐标系点指针, 参考- (CGPoint)glPointForMapPoint:(LMKMapPoint)mapPoint, - (CGPoint *)glPointsForMapPoints:(LMKMapPoint *)mapPoints count:(NSUInteger)count
 @param pointCount   点个数
 @param strokeColor  线颜色
 @param lineWidth    OpenGLES支持线宽尺寸, 参考 - (CGFloat)glWidthForWindowWidth:(CGFloat)windowWidth
 @param looped       是否闭合, 如polyline会设置NO, polygon会设置YES.
 @param lineDash     是否是虚线
 @param complex       是否是复杂纹理
 */
- (void)renderLinesWithPoints:(int*)points
                   pointCount:(NSUInteger)pointCount
                  strokeColor:(UIColor*)strokeColor
                    lineWidth:(CGFloat)lineWidth
                       looped:(BOOL)looped
                     lineDash:(BOOL)lineDash
                      complex:(BOOL)complex;

/*!
 @brief 绘制函数(子类需要重载来实现)
 */
- (void)glRender;

#pragma mark - draw property

/*!
 @brief 笔触纹理id
 修改纹理id参考 - (GLuint)loadStrokeTextureImage:(UIImage *)textureImage;
 */
@property (nonatomic, readonly) GLuint strokeTextureID;

/*!
 加载纹理图片，纹理ID存储在成员strokeTextureID中。纹理图片为nil时，清空原有纹理。
 @param textureImage 纹理图片（需满足：长宽相等，且宽度值为2的次幂）。若为nil，则清空原有纹理。
 @return openGL纹理ID, 若纹理加载失败返回0。
 */
- (GLuint)loadStrokeTextureImage:(UIImage*)textureImage;

@end
