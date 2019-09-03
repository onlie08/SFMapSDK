//
//  GLKMathUtils.h
//  GLKit
//
//  Copyright (c) 2011, Apple Inc. All rights reserved.
//

#ifndef __GLK_MATH_UTILS_H
#define __GLK_MATH_UTILS_H

#include <math.h>
#include <stdbool.h>

#include "GLKMathTypes.h"
#include "GLKVector4.h"
#include "GLKMatrix4.h"

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static __inline__ float GLKMathDegreesToRadians(float degrees) { return degrees * (M_PI / 180); };
static __inline__ float GLKMathRadiansToDegrees(float radians) { return radians * (180 / M_PI); };
    
GLKVector3 GLKMathProject(GLKVector3 object, GLKMatrix4 model, GLKMatrix4 projection, int *viewport) {
	GLKVector4 vector = GLKVector4MakeWithVector3(object, 1.0f);
	
	vector = GLKMatrix4MultiplyVector4(model, vector);
	vector = GLKMatrix4MultiplyVector4(projection, vector);
	
#if defined(__STRICT_ANSI__)
	if (vector.v[3] == 0.0f)
#else
	if (vector.w == 0.0f)
#endif
		return GLKVector3Make(0.0f, 0.0f, 0.0f);
	
#if defined(__STRICT_ANSI__)
	vector = GLKVector4DivideScalar(vector, vector.v[3]);
#else
	vector = GLKVector4DivideScalar(vector, vector.w);
#endif
	
#if defined(__STRICT_ANSI__)
	vector.v[0] = (vector.v[0] + 1.0f) * (float)viewport[2];
	vector.v[1] = (vector.v[1] + 1.0f) * (float)viewport[3];
	vector.v[2] = (vector.v[2] + 1.0f);
	vector = GLKVector4MultiplyScalar(vector, 0.5f);
	
	vector.v[0] += (float)viewport[0];
	vector.v[1] += (float)viewport[1];
#else
	vector.x = (vector.x + 1.0f) * (float)viewport[2];
	vector.y = (vector.y + 1.0f) * (float)viewport[3];
	vector.z = (vector.z + 1.0f);
	vector = GLKVector4MultiplyScalar(vector, 0.5f);
	
	vector.x += (float)viewport[0];
	vector.y += (float)viewport[1];
#endif

	return GLKVector3MakeWithArray(vector.v);
}

GLKVector3 GLKMathUnproject(GLKVector3 window, GLKMatrix4 model, GLKMatrix4 projection, int *viewport, bool *success) {
	bool _success;
	GLKVector4 vector;
	GLKMatrix4 matrix = GLKMatrix4Invert(GLKMatrix4Multiply(projection, model), &_success);
	
	if (_success == false) {
		if (success)
			*success = _success;
		return GLKVector3MakeWithArray(vector.v);
	}
	
#if defined(__STRICT_ANSI__)
	vector.v[0] = ((window.v[0] - (float)viewport[0]) / (float)viewport[2]);
	vector.v[1] = ((window.v[1] - (float)viewport[1]) / (float)viewport[3]);
	vector.v[2] = window.v[2];
	vector.v[3] = 1.0f;
	
	vector = GLKVector4MultiplyScalar(vector, 2.0f);
	vector = GLKVector4SubtractScalar(vector, 1.0f);
	
	vector = GLKMatrix4MultiplyVector4(matrix, vector);
	if (vector.v[2] == 0.0f) {
		if (success)
			*success = false;
		return GLKVector3MakeWithArray(vector.v);
	}
	
	vector = GLKVector4DivideScalar(vector, vector.v[3]);
#else
	vector.x = ((window.x - (float)viewport[0]) / (float)viewport[2]);
	vector.y = ((window.y - (float)viewport[1]) / (float)viewport[3]);
	vector.z = window.z;
	vector.w = 1.0f;
	
	vector = GLKVector4MultiplyScalar(vector, 2.0f);
	vector = GLKVector4SubtractScalar(vector, 1.0f);
	
	vector = GLKMatrix4MultiplyVector4(matrix, vector);
	if (vector.z == 0.0f) {
		if (success)
			*success = false;
		return GLKVector3MakeWithArray(vector.v);
	}
	
	vector = GLKVector4DivideScalar(vector, vector.w);
#endif

	return GLKVector3MakeWithArray(vector.v);
}

#ifdef __OBJC__
NSString * NSStringFromGLKMatrix2(GLKMatrix2 matrix) {
	return [NSString stringWithFormat:
			@"{{%g, %g}, {%g, %g}}",
#if defined(__STRICT_ANSI__)
			matrix.m[0], matrix.m[1],
			matrix.m[2], matrix.m[3]
#else
			matrix.m00, matrix.m01,
			matrix.m10, matrix.m11
#endif
			];
}

NSString * NSStringFromGLKMatrix3(GLKMatrix3 matrix) {
	return [NSString stringWithFormat:
			@"{{%g, %g, %g}, {%g, %g, %g}, {%g, %g, %g}}",
#if defined(__STRICT_ANSI__)
			matrix.m[0], matrix.m[1], matrix.m[2],
			matrix.m[3], matrix.m[4], matrix.m[5],
			matrix.m[6], matrix.m[7], matrix.m[8]
#else
			matrix.m00, matrix.m01, matrix.m02,
			matrix.m10, matrix.m11, matrix.m12,
			matrix.m20, matrix.m21, matrix.m22
#endif
			];
}

NSString * NSStringFromGLKMatrix4(GLKMatrix4 matrix) {
	return [NSString stringWithFormat:
			@"{{%g, %g, %g, %g}, {%g, %g, %g, %g}, {%g, %g, %g, %g}, {%g, %g, %g, %g}}",
#if defined(__STRICT_ANSI__)
			matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
			matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
			matrix.m[8], matrix.m[9], matrix.m[10],matrix.m[11]
#else
			matrix.m00, matrix.m01, matrix.m02, matrix.m03,
			matrix.m10, matrix.m11, matrix.m12, matrix.m13,
			matrix.m20, matrix.m21, matrix.m22, matrix.m23,
			matrix.m30, matrix.m31, matrix.m32, matrix.m33
#endif
			];
}

NSString * NSStringFromGLKVector2(GLKVector2 vector) {
	return [NSString stringWithFormat:
			@"{%g, %g}",
#if defined(__STRICT_ANSI__)
			vector.v[0], vector.v[1]
#else
			vector.x, vector.y
#endif
			];
}

NSString * NSStringFromGLKVector3(GLKVector3 vector) {
	return [NSString stringWithFormat:
			@"{%g, %g, %g}",
#if defined(__STRICT_ANSI__)
			vector.v[0], vector.v[1], vector.v[2]
#else
			vector.x, vector.y, vector.z
#endif
			];
}

NSString * NSStringFromGLKVector4(GLKVector4 vector) {
	return [NSString stringWithFormat:
			@"{%g, %g, %g, %g}",
#if defined(__STRICT_ANSI__)
			vector.v[0], vector.v[1], vector.v[2], vector.v[3]
#else
			vector.x, vector.y, vector.z, vector.w
#endif
			];
}

NSString * NSStringFromGLKQuaternion(GLKQuaternion quaternion) {
	return [NSString stringWithFormat:
			@"{{%g, %g, %g}, %g}",
#if defined(__STRICT_ANSI__)
			quaternion.q[0], quaternion.q[1], quaternion.q[2], quaternion.q[3]
#else
			quaternion.x, quaternion.y, quaternion.z, quaternion.w
#endif
			];
}
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_MATH_UTILS_H */
