/********************************************************************************
*  This file is part of CinoLib                                                 *
*  Copyright(C) 2022: Marco Livesu                                              *
*                                                                               *
*  The MIT License                                                              *
*                                                                               *
*  Permission is hereby granted, free of charge, to any person obtaining a      *
*  copy of this software and associated documentation files (the "Software"),   *
*  to deal in the Software without restriction, including without limitation    *
*  the rights to use, copy, modify, merge, publish, distribute, sublicense,     *
*  and/or sell copies of the Software, and to permit persons to whom the        *
*  Software is furnished to do so, subject to the following conditions:         *
*                                                                               *
*  The above copyright notice and this permission notice shall be included in   *
*  all copies or substantial portions of the Software.                          *
*                                                                               *
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR   *
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,     *
*  FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE *
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER       *
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING      *
*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS *
*  IN THE SOFTWARE.                                                             *
*                                                                               *
*  Author(s):                                                                   *
*                                                                               *
*     Marco Livesu (marco.livesu@gmail.com)                                     *
*     http://pers.ge.imati.cnr.it/livesu/                                       *
*                                                                               *
*     Italian National Research Council (CNR)                                   *
*     Institute for Applied Mathematics and Information Technologies (IMATI)    *
*     Via de Marini, 6                                                          *
*     16149 Genoa,                                                              *
*     Italy                                                                     *
*                                                                               *
*     Fabrizio Corda (cordafab@gmail.com)                                       *
*     http://www.fabriziocorda.com                                              *
*                                                                               *
*     University of Cagliari                                                    *
*     Via Ospedale, 72                                                          *
*     09124 Cagliari,                                                           *
*     Italy                                                                     *                                                                               *
*********************************************************************************/
#ifndef CINO_OVERHANGS_H
#define CINO_OVERHANGS_H

#include <cinolib/meshes/abstract_polygonmesh.h>
#include <cinolib/meshes/trimesh.h>
#include <cinolib/geometry/vec_mat.h>

namespace cinolib
{

template<class M, class V, class E, class P>
CINO_INLINE
void overhangs(const Trimesh<M,V,E,P>  & m,
               const float               thresh, // degrees
               const vec3d             & build_dir,
                     std::vector<uint> & polys_hanging);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// for each overhang returns also the ID of the first triangle below it along the
// direction of projection. If there is no such triangle, it returns the same ID
// of the hanging triangle. For example:
//
//   (x,y) => triangle with id y is below hanging triangle with id x,
//            supports will emanate from triangle y
//
//   (x,x) => triangle with id x has no other triangles below it,
//            supports will emanate from the building platform
//
// Triangles below overhangs are computed via ray casting, throwing one ray from
// the center of the offending element towards the opposite of the build direction.
// The cluster of rays being shoot is therefore quite sparse, and some triangle
// may be missed. Nevertheless, assuming a uniform tessellation, this method
// should allow to detect a decent approximation of the surface lying below
// the overhangs
//
template<class M, class V, class E, class P>
CINO_INLINE
void overhangs(const Trimesh<M,V,E,P>                  & m,
               const float                               thresh, // degrees
               const vec3d                             & build_dir,
                     std::vector<std::pair<uint,uint>> & polys_hanging);
}

#ifndef  CINO_STATIC_LIB
#include "overhangs.cpp"
#endif

#endif // CINO_OVERHANGS_H