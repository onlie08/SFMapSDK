

#ifndef __LMKBezierBuilder__
#define __LMKBezierBuilder__

#include <iostream>
#include <vector>
#include <math.h>

typedef struct {
    double x;
    double y;
} LMKBezierPoint;

static inline LMKBezierPoint LMKBezierPointMake(double x, double y)
{
    return (LMKBezierPoint){x, y};
}

typedef std::vector< LMKBezierPoint > BezierPointVector;

class LMKBezierBuilder
{
public:
    /*!
     @brief 计算贝塞尔曲线圆弧
     @param radian 两点在经度上的跨度，以弧度为单位
     @param originPoint 起始点的坐标
     @param endPoint 起始点的坐标
     @param yflag 南北半球的标识 ：-1 北半球，1 南半球
     @param outVector 输出结果
     @return void
     */
    static void calculateGeodesicPoints(double radian, LMKBezierPoint originPoint, LMKBezierPoint endPoint, int yflag, BezierPointVector &outVector);
    
    /*!
     @brief 计算贝塞尔控制点
     @param start, end, point 输入起点、终点、中间点
     @param distance 中间点到控制点的距离
     @param flag: -1 向上，1 向下
     @return void
     */
    static LMKBezierPoint calculateControlPoint(LMKBezierPoint start, LMKBezierPoint end, LMKBezierPoint point, double distance, int flag);
    
    /*!
     @brief 计算贝塞尔圆弧
     @param controlPoints 输入控制点
     @param w1 贝塞尔有理函数系数
     @param bezierPoints 输出结果
     @return void
     */
    static void calculateArcBezier(const BezierPointVector &controlPoints, BezierPointVector &bezierPoints, double w1);
    
    /*!
     @brief 计算标准贝塞尔曲线，暂时没用到，画贝赛尔曲线会用到
     @param controlPoints 控制点
     @param bezierPoints 输出
     @return void
     */
    static void calculateBezier(const BezierPointVector &controlPoints, BezierPointVector &bezierPoints);

};

#endif /* defined(__LMKBezierBuilder__) */
