/*
 * CPolygonBuilder.h
 */

#ifndef CPOLYGONBUILDER_H_
#define CPOLYGONBUILDER_H_

#include "me_defines.h"
#include "PVRTVector.h"
#include "glues.h"
#include "CLineBuilder.h"

class CPolygonBuilder
{
    public:
        CPolygonBuilder();
        virtual ~CPolygonBuilder();

    private:
        CPointList m_ll;


    public:
        unsigned int total_vertex_num;
        unsigned int total_index_num;
        PVRTVec3* vertexBuffer;
        GLushort* indexBuffer;

    public:
        void Reset();
        void MoveTo(GLfloat glx, GLfloat gly);
        void LineTo(GLfloat glx, GLfloat gly);
        void DoBuilderPolygon();

        //   void Draw(PVRTVec4 color);

};

#endif /* CPOLYGONBUILDER_H_ */
