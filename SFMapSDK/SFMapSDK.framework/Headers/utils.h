//
//  utils.h
//
#include <pthread.h>
#include <unistd.h>
#import "XYMap3DEngine/me_common.h"
#include <CoreGraphics/CoreGraphics.h>
#include <sys/xattr.h>
#ifdef BUILD_OGLES
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#elif BUILD_OGLES2
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif


const int scaleLineLengths[] = {49, 39, 39/*95*/,39/*95*/,31/*75*/,31/*75*/,31/*75*/,38/*90*/,50/*98*/,50/*97*/,50/*98*/,40/*78*/,40/*78*/,40/*78*/,32/*61*/,32/*61*/,32/*61*/,32/*115*/,26/*93*/,26/*93*/};
const int scales[] = {5000000/*1*/, 2000000/*2*/, 1000000/*3*/, 500000/*4*/,  200000/*5*/,  100000/*6*/,  50000/*7*/,   30000/*8*/,   20000/*9*/,   10000/*10*/,   5000/*11*/,    2000/*12*/,    1000/*13*/,    500/*14*/,     200/*15*/,     100/*16*/,     50/*17*/,      25/*18*/,       10/*19*/,      5/*20*/,    2.5/*21*/, 1/*22*/, };

extern "C" const float scaleFactor();

extern "C" ME_INT GetNearstSize2NU(ME_INT n);

extern "C" float GetScaleLineLengthWithLatitudeU(float zoomer, double latitude);
extern "C" int GetScaleMeterLengthU(int scaleIndex);
extern "C" NSString *getScaleStringU(int index);
extern "C" ME_UINT8 *GetScaleStringBitmapU(int scaleIndex, int *width, int *height);

extern "C" CGFloat *rgbColorComponentU(CGColorRef color); //need free buffer external

extern "C" void tellMapViewCenterChanged();

const BOOL isPhone6();
const BOOL isPhone6plus() ;
