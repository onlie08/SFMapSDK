//
//  LMKMapView.h
//  SFMapSDK
//
//  Copyright © 2016年 sfmap. All rights reserved.
//

#import "LMKAnnotation.h"
#import "LMKAnnotationView.h"
#import "LMKGeometry.h"
#import "LMKOverlayView.h"
#import "LMKUserLocation.h"
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

@class LMKMarker;
@class LMKCustomDrawOverlay;

/*!
 @brief 地图类型，支持标准地图和导航地图
 */
typedef NS_ENUM(NSUInteger, LMKMapType) {
    LMKMapTypeStandardDay,   //! 标准地图（白天模式）
    LMKMapTypeStandardNight, //! 标准地图（夜间模式）
    LMKMapTypeNaviDay,       //! 导航地图（白天模式）
    LMKMapTypeNaviNight,     //! 导航地图（夜间模式）
    LMKMapTypeDIYDay,        //！自定义地图样式（白天模式）
    LMKMapTypeSatellite,     //!卫星地图，使用该类型地图需要专业版SDK权限
};

/*!
 @brief TMC颜色类型，支持标准地图和导航地图
 */
typedef NS_ENUM(NSUInteger, LMKTMCColorType) {
    LMKTMCColorNormal = 0,      //! 标准地图（普通模式）
    LMKTMCColorNaviDay = 1,     //! 标准地图（导航白天模式）
    LMKTMCColorNaviNight = 2,   //! 标准地图（导航夜间模式）
};

@protocol LMKMapViewDelegate;

/*!
 @brief 地图view。（说明：多实例地图设置地图属性需要在mapViewRenderOver:回调之后执行，否则无效（非第一个创建的地图实例））
 */
@interface LMKMapView : UIView

/*!
 @brief 地图初始化方法，默认的initWithFrame方法显示墨卡托投影的矢量地图
 
 @param frame 当前地图实例的尺寸
 @param type 投影类型：墨卡托投影和4326投影
 @param hiddenVectorMap 隐藏矢量地图，默认不隐藏
 @return 当前实例
 */
- (instancetype)initWithFrame:(CGRect)frame
               projectionType:(LMKMapProjectionType)type
              hiddenVectorMap:(BOOL)hiddenVectorMap;

/*!
 @brief LMKMapViewDelegate 代理
 */
@property (nonatomic, weak) id<LMKMapViewDelegate> delegate;

/*!
 @brief 地图类型，支持普通地图和夜间地图
 */
@property (nonatomic) LMKMapType mapType;

/*!
 @brief 地图旋转角度，当前可使用的范围为－180～180度，大于 0度 时为逆时针旋转
 */
@property (nonatomic) CGFloat rotation;

/*!
 @brief 地图俯视角度，俯视角度 0 - 45度，0度为：视角从正上方，向下看
 */
@property (nonatomic) CGFloat overlooking;

/*!
 @brief 设置地图可放大的最大级别，取值区间为[19,22]，默认为19。
 */
@property (nonatomic) CGFloat maxZoomInLevel;

/*!
 @brief 地图比例尺级别，可使用的地图比例尺级别的取值区间在3到maxZoomInLevel之间。
 */
@property (nonatomic) CGFloat zoomLevel;

/*!
 @brief 当前地图的中心点，改变该值时，地图的比例尺级别不会发生变化
 */
@property (nonatomic) CLLocationCoordinate2D centerCoordinate;

/*!
 @brief 将经纬度坐标设置为地图中心点
 @param centerCoordinate 经纬度坐标
 @param animated 是否开启动画
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate animated:(BOOL)animated;

/*!
 @brief 显示指南针标志位，为YES时显示，默认是YES
 */
@property (nonatomic, assign) BOOL showsCompass;

/*!
 @brief 设置指南针的位置
 @param screenPoint 指南针的位置
 @param animated 是否开启动画
 */
- (void)setCompassScreenPoint:(CGPoint)screenPoint animated:(BOOL)animated;
/*!
 @brief 是否在地图左下角显示logo
 */
@property (nonatomic) BOOL showsLogo;
/*!
 @brief 是否显示蓝色路网，蓝色路网：用于表示地图中存在实景数据的路段。
 */
@property (nonatomic) BOOL showsBlueRoadNet;
/*!
 @brief 是否显示用户位置
 */
@property (nonatomic) BOOL showsUserLocation;

/*!
 @brief 是否支持单击地图获取POI信息，默认为YES。
 对应的回调是 - (void)mapView:(LMKMapView *)mapView didTouchPois:(NSArray *)pois
 */
@property (nonatomic) BOOL touchPOIEnabled;
/*!
 @brief 当前的位置数据
 */
@property (nonatomic, readonly) LMKUserLocation* userLocation;

/*!
 @brief logo位置, 必须在mapView.bounds之内，否则会被忽略
 */
@property (nonatomic) CGPoint logoCenter;

/*!
 @brief 地图的视图锚点。坐标系归一化，(0, 0)为LMKMapView左上角，(1, 1)为右下角。默认为(0.5, 0.5)，即当前地图的视图中心。
 */
@property (nonatomic, readonly) CGPoint screenAnchor;

/*!
 @brief logo的宽高
 */
@property (nonatomic, readonly) CGSize logoSize;

/*!
 @brief 是否显示比例尺
 */
@property (nonatomic) BOOL showsScale;

/*!
 @brief 是否显示交通
 */
@property (nonatomic, getter=isShowTraffic) BOOL showTraffic;

/*!
 @brief 比例尺右下角原点位置，设置的值如果比例尺显示超出bounds范围则不生效
 */
@property (nonatomic) CGPoint scaleRightBottomOrigin;

/*!
 @brief 当前地图的平面投影（20级像素坐标）可视范围
 */
@property (nonatomic) LMKMapRect visibleMapRect;

/*!
 @brief 设置地图的平面投影（20级像素坐标）可视范围
 @param visibleMapRect 可视范围
 @param animated 是否开启动画
 */
- (void)setVisibleMapRect:(LMKMapRect)visibleMapRect animated:(BOOL)animated;

/*!
 @brief 将经纬度转换为指定view坐标系的坐标
 @param coordinate 经纬度坐标
 @param view       view
 @return 指定view的坐标
 */
- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(UIView*)view;

/*!
 @brief 将指定view坐标系的坐标转换为经纬度
 @param point 屏幕点坐标
 @param view  指定view
 @return 经纬度坐标
 */
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(UIView*)view;

/*!
 @brief 初始化Map View，暂不支持多实例
 @param frame frame的 witdth 和 height 如果为 0，则返回全屏幕大小View，否则返回正常大小View
 @return LMKMapView
 */
- (instancetype)initWithFrame:(CGRect)frame;

/*!
 @brief 支持Scroll手势，默认YES
 */
- (void)setScrollEnabled:(BOOL)enabled;

/*!
 @brief 支持Zoom手势，默认YES
 */
- (void)setZoomEnabled:(BOOL)enabled;

/*!
 @brief 支持Rotate手势，默认YES
 */
- (void)setRotateEnabled:(BOOL)enabled;

/*!
 @brief 支持Camera（视角）手势，默认YES
 */
- (void)setCameraEnabled:(BOOL)enabled;

/*!
 @brief 支持用户设置地图的样式文件
 @param styleFileName   style样式文件的全路径
 @param iconsFileName   icons样式文件的全路径
 */
- (void)setStyleFileName:(NSString *)styleFileName  andIconsFileName:(NSString *)iconsFileName;

/*!
 @brief 返回专业版权限检验结果，使用专业版功能前请将鉴权文件product.sn和deviceid.dat放入LDMap.bundle主目录下
 */
- (BOOL)getverifyResult;

@end

#pragma mark - LMKMapView (Tools)
/*!
 @brief 地图view工具类的类别(geo,20级像素坐标;lnglat,精度纬度;map,地图opengl坐标；win,屏幕坐标)
 */
@interface LMKMapView (Tools)

/*!
 @brief 20级像素坐标转经纬度坐标

 @param pixel20X 20级像素坐标经度
 @param pixel20Y 20级像素坐标纬度
 @param outLon   输出经度
 @param outLat   输出纬度
 */
- (void)geo2lonlat_withPixel20X:(int)pixel20X pixel20Y:(int)pixel20Y
                            lon:(double *)outLon lat:(double *)outLat;

/*!
 @brief 经纬度坐标转20级像素坐标

 @param lon         经度
 @param lat         纬度
 @param outPixel20X 输出20级像素坐标经度
 @param outPixel20Y 输出20级像素坐标纬度
 */
- (void)lonlat2geo_withLon:(double)lon lat:(double)lat
                      geoX:(int *)outPixel20X geoY:(int *)outPixel20Y;

/*!
 @brief 20级像素坐标转地图opengl坐标

 @param pixel20X 20级像素坐标经度
 @param pixel20Y 20级像素坐标纬度
 @param outMapX  输出地图opengl坐标X
 @param outMapY  输出地图opengl坐标Y
 */
- (void)geo2map_withPixel20X:(int)pixel20X pixel20Y:(int)pixel20Y
                        mapX:(float *)outMapX mapY:(float *)outMapY;

/*!
 @brief 地图opengl坐标转20级像素坐标

 @param mapX        地图opengl坐标X
 @param mapY        地图opengl坐标Y
 @param outPixel20X 输出20级像素坐标经度
 @param outPixel20Y 输出20级像素坐标纬度
 */
- (void)map2geo_withMapX:(float)mapX mapY:(float)mapY
                    geoX:(int *)outPixel20X geoY:(int *)outPixel20Y;

/*!
 @brief 屏幕坐标转地图opengl坐标

 @param winX    屏幕坐标X
 @param winY    屏幕坐标Y
 @param outMapX 输出地图opengl坐标X
 @param outMapY 输出地图opengl坐标Y
 */
- (void)win2map_withWinX:(double)winX winY:(double)winY
                    mapX:(float *)outMapX mapY:(float *)outMapY;

/*!
 @brief 地图opengl坐标转屏幕坐标

 @param mapX    地图opengl坐标X
 @param mapY    地图opengl坐标Y
 @param outWinX 输出屏幕坐标X
 @param outWinY 输出屏幕坐标Y
 */
- (void)map2win_withMapX:(float)mapX mapY:(float)mapY
                    winX:(double *)outWinX winY:(double *)outWinY;

/*!
 @brief 根据屏幕像素Len获得地图opengl长度

 @param winPixelLen 屏幕像素Len
 @param winY        屏幕坐标的Y值

 @return 地图opengl长度
 */
- (float)getMapLenWithWinLen:(int)winPixelLen byY:(int)winY;

/*!
 @brief 根据屏幕像素Len获得地图opengl长度

 @param winPixelLen 屏幕像素Len

 @return 地图opengl长度
 */
- (float)getMapLenWithWinLen:(int)winPixelLen;

/*!
 @brief 根据20级像素Len获得地图opengl长度

 @param geoPixelLen 20级像素坐标长度

 @return 地图opengl长度
 */
- (float)getMapLenWithGeoLen:(int)geoPixelLen;

/*!
 @brief 根据屏幕坐标Len获得20级像素坐标长度

 @param winPixelLen 屏幕坐标长度

 @return 20级像素坐标长度
 */
- (float)getGeoLenWithWinLen:(int)winPixelLen;

/*!
 @brief 根据20级像素坐标设置地图中心点
 
 @param x x轴20级像素坐标
 
 @param y y轴20级像素坐标
 */
- (void)setMapcenterByGeoPointX:(int)x Y:(int)y;

/*!
 @brief 根据地图中心点获取该点对应的20级像素坐标
 
 @param x x轴20级像素坐标
 
 @param y y轴20级像素坐标
 */
- (void)getMapcenterWithGeoPointX:(int*)x Y:(int*)y;

/*!
 @brief 获取地图缩放级别
 @return 地图缩放级别
 */
- (float)getMapZoomer;
/*!
 @brief 计算A点和B点之间的直线与正北方向（顺时针旋转）的夹角（弧度），其中A点为直线的起点，返回值区间为[0,2π)。
 @param pointA  由A点经纬度构成的结构体
 @param pointB  由B点经纬度构成的结构体
 */

- (CGFloat)calculatePointA:(CLLocationCoordinate2D)pointA  andPointB:(CLLocationCoordinate2D)pointB;

/*!
 @brief 计算A点和B点之间的直线与C点和D点之间的直线（顺时针旋转）的夹角（弧度），其中A点、C点分别为两条直线的起点，返回值区间为[0,2π)。
 @param pointA  由A点经纬度构成的结构体
 @param pointB  由B点经纬度构成的结构体
 @param pointC  由C点经纬度构成的结构体
 @param pointD  由D点经纬度构成的结构体
 */
- (CGFloat)calculatePointA:(CLLocationCoordinate2D)pointA  andPointB:(CLLocationCoordinate2D)pointB  andPointC:(CLLocationCoordinate2D)pointC  andPointD:(CLLocationCoordinate2D)pointD;

@end

#pragma mark - LMKMapView (Snapshot)
/*!
 @brief 地图view关于截图的类别
 */
@interface LMKMapView (Snapshot)

/*!
 @brief 在指定区域内截图(默认会包含该区域内的annotationView)
 @param rect 指定的区域
 @return 截图image
 */
- (UIImage *)takeSnapshotInRect:(CGRect)rect;

@end

#pragma mark - LMKMapView (Annotation)

/*!
 @brief 地图View关于标注的类别
 */
@interface LMKMapView (Annotation)

/*!
 设置地图使其可以显示数组中所有的annotation, 如果数组中只有一个则直接设置地图中心为annotation的位置。
 @param annotations 需要显示的annotation
 @param animated    是否执行动画
 */
- (void)showAnnotations:(NSArray*)annotations animated:(BOOL)animated;

/*!
 @brief 向地图窗口添加标注，需要实现LMKMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 @param annotation 要添加的标注
 */
- (void)addAnnotation:(id<LMKAnnotation>)annotation;

/*!
 @brief 向地图窗口添加一组标注，需要实现LMKMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 @param annotations 要添加的标注数组
 */
- (void)addAnnotations:(NSArray*)annotations;

/*!
 @brief 移除标注
 @param annotation 要移除的标注
 */
- (void)removeAnnotation:(id<LMKAnnotation>)annotation;

/*!
 @brief 移除一组标注
 @param annotations 要移除的标注数组
 */
- (void)removeAnnotations:(NSArray*)annotations;

/*!
 @brief 标注数组
 */
@property (nonatomic, readonly) NSArray* annotations;

#pragma mark - Annotation system delegate

/*!
 @brief 当选中一个annotation view时，调用此接口
 @param view 选中的annotation view
 */
- (void)didSelectAnnotationView:(LMKAnnotationView*)view;

/*!
 @brief 当取消选中一个annotation view时，调用此接口
 @param view 取消选中的annotation view
 */
- (void)didDeselectAnnotationView:(LMKAnnotationView*)view;

/*!
 @brief 拖动annotation view时view的状态变化
 @param view annotation view
 @param newState 新状态
 @param oldState 旧状态
 */
- (void)annotationView:(LMKAnnotationView*)view
    didChangeDragState:(LMKAnnotationViewDragState)newState
          fromOldState:(LMKAnnotationViewDragState)oldState;

/*!
 @brief 标注view的accessory view(必须继承自UIControl)被点击时，触发该回调
 @param annotationView callout所属的标注view
 @param control 对应的control
 */
- (void)annotationView:(LMKAnnotationView*)annotationView calloutAccessoryControlTapped:(UIControl*)control;

/*!
 @brief 标注view的calloutview整体点击时，触发改回调。
 @param annotationView calloutView所属的annotationView
 */
- (void)didAnnotationViewCalloutTapped:(LMKAnnotationView*)annotationView;

/*!
 @brief 从复用内存池中获取制定复用标识的annotation view
 @param identifier 复用标识
 @return annotation view
 */
- (LMKAnnotationView*)dequeueReusableAnnotationViewWithIdentifier:(NSString*)identifier;
@end

/*!
 @brief 绘制overlay的层级，暂不支持，默认LMKOverlayLevelAboveLabels
 */
typedef NS_ENUM(NSInteger, LMKOverlayLevel) {
    LMKOverlayLevelAboveRoads = 0, // 在地图底图标注和兴趣点图标之下绘制overlay
    LMKOverlayLevelAboveLabels // 在地图底图标注和兴趣点图标之上绘制overlay
};

/*!
 @brief 地图view关于overlay类别
 */
@interface LMKMapView (Overlay)

/*!
 @brief Overlay数组
 */
@property (nonatomic, readonly) NSArray* overlays;

/*!
 @brief 向地图窗口添加Overlay
 @param overlay 要添加的overlay
 */
- (void)addOverlay:(id<LMKOverlay>)overlay;

/*!
 @brief 向地图窗口添加一组Overlay
 默认添加层级：LMKOverlayLevelAboveLabels
 
 @param overlays 要添加的overlay数组
 */
- (void)addOverlays:(NSArray*)overlays;

/*!
 @brief 移除Overlay
 @param overlay 要移除的overlay
 */
- (void)removeOverlay:(id<LMKOverlay>)overlay;

/*!
 @brief 移除一组Overlay
 @param overlays 要移除的overlay数组
 */
- (void)removeOverlays:(NSArray*)overlays;

/*!
 @brief 在指定的Overlay之上插入一个overlay
 @param overlay 带添加的Overlay
 @param sibling 用于指定相对位置的Overlay
 */
- (void)insertOverlay:(id<LMKOverlay>)overlay aboveOverlay:(id<LMKOverlay>)sibling;

/*!
 @brief 在指定的Overlay之下插入一个overlay
 @param overlay 带添加的Overlay
 @param sibling 用于指定相对位置的Overlay
 */
- (void)insertOverlay:(id<LMKOverlay>)overlay belowOverlay:(id<LMKOverlay>)sibling;

/*!
 @brief 在指定的索引处添加一个Overlay
 @param overlay 要添加的overlay
 @param index 指定的索引
 */
- (void)insertOverlay:(id<LMKOverlay>)overlay atIndex:(NSUInteger)index;

/*!
 @brief 交换指定索引处的Overlay
 @param index1 索引1
 @param index2 索引2
 */
- (void)exchangeOverlayAtIndex:(NSUInteger)index1 withOverlayAtIndex:(NSUInteger)index2;

@end

/*!
 @brief 地图view关于自定义OpenGL绘制 overlay类别
 */
@interface LMKMapView (CustomDrawOverlay)

/*!
 @brief 添加自定义OpenGL绘制 overlay
 @param customOverlay 绘制实例，需要实现glRender方法来绘制需要的图形
 */
- (void)addCustomDrawOverlay:(LMKCustomDrawOverlay *)customOverlay;

/*!
 @brief 添加自定义OpenGL绘制 overlays数组
 @param customOverlays LMKCustomDrawOverlay数组
 */
- (void)addCustomDrawOverlays:(NSArray *)customOverlays;

/*!
 @brief 移除自定义OpenGL绘制 overlay
 @param customOverlay 绘制实例
 */
- (void)removeCustomDrawOverlay:(LMKCustomDrawOverlay *)customOverlay;

/*!
 @brief 移除所有自定义OpenGL绘制的overlay
 */
- (void)removeAllCustomDrawOverlays;

@end


#pragma mark - LMKMapViewDelegate

/*!
 @brief 地图view的delegate
 */
@protocol LMKMapViewDelegate <NSObject>
@optional

/*!
 @brief 地图实例渲染完成的回调，多实例设置地图属性需要在该回调之后执行，否则无效
 @param mapView 地图View
 */
- (void)mapViewRenderOver:(LMKMapView *)mapView;

/*!
 @brief 地图实例每次旋转或俯视的回调
 @param mapView 地图View
 */
- (void)mapViewPostRender:(LMKMapView *)mapView;

/*!
 @brief 地图实例每次缩放或者移动之后的回调
 @param mapView 地图View
 */
- (void)mapViewZoomOrMoveFinish:(LMKMapView *)mapView;

/*!
 @brief 地图实例每次缩放或者移动时的回调
 @param mapView 地图View
 */
- (void)mapViewZoomingOrMoveing:(LMKMapView *)mapView;

/*!
 @brief 根据anntation生成对应的View
 @param mapView 地图View
 @param annotation 指定的标注
 @return 生成的标注View
 */
- (LMKAnnotationView*)mapView:(LMKMapView*)mapView viewForAnnotation:(id<LMKAnnotation>)annotation;

/*!
 @brief 当mapView新添加annotation views时，调用此接口
 @param mapView 地图View
 @param views 新添加的annotation views
 */
- (void)mapView:(LMKMapView*)mapView didAddAnnotationViews:(NSArray*)views;

/*!
 @brief 当选中一个annotation view时，调用此接口
 @param mapView 地图View
 @param view 选中的annotation view
 */
- (void)mapView:(LMKMapView*)mapView didSelectAnnotationView:(LMKAnnotationView*)view;

/*!
 @brief 当取消选中一个annotation view时，调用此接口
 @param mapView 地图View
 @param view 取消选中的annotation view
 */
- (void)mapView:(LMKMapView*)mapView didDeselectAnnotationView:(LMKAnnotationView*)view;

/*!
 @brief 标注view的accessory view(必须继承自UIControl)被点击时，触发该回调
 @param mapView 地图View
 @param view annotationView
 @param control 对应的control
 */
- (void)mapView:(LMKMapView*)mapView annotationView:(LMKAnnotationView*)view calloutAccessoryControlTapped:(UIControl*)control;

/*!
 @brief 标注view的calloutview整体点击时，触发该回调
 @param mapView 地图的view
 @param view calloutView所属的annotationView
 */
- (void)mapView:(LMKMapView*)mapView didAnnotationViewCalloutTapped:(LMKAnnotationView*)view;

/*!
 @brief 拖动annotation view时view的状态变化
 @param mapView 地图View
 @param view annotationView
 @param newState 新状态
 @param oldState 旧状态
 */
- (void)mapView:(LMKMapView*)mapView annotationView:(LMKAnnotationView*)view didChangeDragState:(LMKAnnotationViewDragState)newState fromOldState:(LMKAnnotationViewDragState)oldState;

/*!
 @brief 根据overlay生成对应的View
 @param mapView 地图View
 @param overlay 指定的overlay
 @return 生成的LMKOverlayView
 */
- (LMKOverlayView*)mapView:(LMKMapView*)mapView viewForOverlay:(id<LMKOverlay>)overlay;

/*!
 @brief 当mapView新添加overaly views时，调用此接口
 @param mapView 地图View
 @param views 新添加的ovrlay views
 */
- (void)mapView:(LMKMapView*)mapView didAddOverlayViews:(NSArray*)views;

/*!
@brief 单击地图回调，返回经纬度
@param mapView 地图View
@param coordinate 经纬度
*/
- (void)mapView:(LMKMapView*)mapView didSingleTappedAtCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 @brief 长按地图，返回经纬度
 @param mapView 地图View
 @param coordinate 经纬度
 */
- (void)mapView:(LMKMapView*)mapView didLongPressedAtCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 @brief 地图手势
 @param mapView 地图View
 @param gesture 移动、缩放、旋转等手势
 */
- (void)mapView:(LMKMapView*)mapView didMoveGesture:(UIPanGestureRecognizer*)gesture;
- (void)mapView:(LMKMapView*)mapView didZoomGesture:(UIGestureRecognizer*)gesture;
- (void)mapView:(LMKMapView*)mapView didRotateGesture:(UIRotationGestureRecognizer*)gesture;
- (void)mapView:(LMKMapView*)mapView didCameraGesture:(UIPanGestureRecognizer*)gesture;

/*!
 @brief 若属性showsUserLocation为YES，用户位置更新后，会调用此函数
 @param mapView 地图View
 @param userLocation 用户定位信息(用户位置经纬度)
 @param updatingLocation 标示是否是location数据更新, YES:location数据更新 NO:无数据更新
 */
- (void)mapView:(LMKMapView*)mapView didUpdateUserLocation:(LMKUserLocation*)userLocation updatingLocation:(BOOL)updatingLocation;

/*!
 @brief 当touchPOIEnabled == YES时，单击地图使用该回调获取POI信息
 @param mapView 地图View
 @param pois 获取到的poi数组(由LMKTouchPoi组成)
 */
- (void)mapView:(LMKMapView *)mapView didTouchPois:(NSArray *)pois;

/*!
 @brief 点击Layer线条
 @param mapView 地图View
 @param lineOverlays 获取到的线条数组(由XYMap3DLineOverlay组成)
 */
- (void)mapView:(LMKMapView *)mapView didTouchLines:(NSArray *)lineOverlays;

/*!
 @brief 点击地图marker后的回调
 @param mapView 地图View
 @param marker 点击的Marker
 */
- (void)mapView:(LMKMapView *)mapView didTouchOnMarker:(LMKMarker *)marker;

/*!
 @brief 回调栅格取图所需地址，根据回传的数据拼接需要的请求串
 @param mapView 当前地图实例
 @param tileX tileX回传
 @param tileY tileY回传
 @param tileZ tileZ回传
 @param proj 投影类型回传
 @return 拼接的URL请求串
 */
- (NSString *)mapView:(LMKMapView *)mapView requireTileURLWithTileX:(int)tileX tileY:(int)tileY tileZ:(int)tileZ projection:(LMKMapProjectionType)proj;

@end
