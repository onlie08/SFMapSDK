#ifndef _WXMAPCORE_DEFINES_H_
#define _WXMAPCORE_DEFINES_H_

#ifndef DYNAMIC_VBO_MACRO
#define DYNAMIC_VBO_MACRO
#endif


#ifndef FONT_MODEL_CACHE_MACRO
#define FONT_MODEL_CACHE_MACRO
#endif


#define DELETE_PTR(pPtr) { if(pPtr) delete pPtr; pPtr = NULL; }
#define FREE_PTR(pPtr) { if(pPtr) free(pPtr); pPtr = NULL; }


#endif //_WXMAPCORE_DEFINES_H_
