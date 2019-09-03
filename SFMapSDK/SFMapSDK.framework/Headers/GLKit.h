//
//  GLKit.h
//  GLKit
//
//  Copyright (c) 2011, Apple Inc. All rights reserved.
//

#include "GLKMathTypes.h"
//#include "GLKMathUtils.h"
#include "GLKMatrix3.h"
#include "GLKMatrix4.h"
#include "GLKVector2.h"
#include "GLKVector3.h"
#include "GLKVector4.h"
#include "GLKQuaternion.h"

static __inline__ float GLKMathDegreesToRadians(float degrees) { return degrees * (M_PI / 180); };
static __inline__ float GLKMathRadiansToDegrees(float radians) { return radians * (180 / M_PI); };