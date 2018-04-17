#ifndef CULLING_CLIPPING_H_INCLUDED
#define CULLING_CLIPPING_H_INCLUDED

#include "myvector.h"

/* v1, v2, v3 are vertices of the primitive, lightdir normalized direction of light
 * return value, >0 means the primitive is visible, otherwise invisible. */
float backfaceCulling(vector3f v1, vector3f v2, vector3f v3, vector3f lightdir);

#endif // CULLING_CLIPPING_H_INCLUDED
