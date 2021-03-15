/********************************************************************************
*  This file is part of CinoLib                                                 *
*  Copyright(C) 2016: Marco Livesu                                              *
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
*     Luca Pitzalis (lucapizza@gmail.com)                                       *
*     University of Cagliari                                                    *
*                                                                               *
*                                                                               *
*     Marco Livesu (marco.livesu@gmail.com)                                     *
*     http://pers.ge.imati.cnr.it/livesu/                                       *
*                                                                               *
*     Italian National Research Council (CNR)                                   *
*     Institute for Applied Mathematics and Information Technologies (IMATI)    *
*     Via de Marini, 6                                                          *
*     16149 Genoa,                                                              *
*     Italy                                                                     *
*********************************************************************************/
#ifndef CINO_HEX_TRANSITION_INSTALL_H
#define CINO_HEX_TRANSITION_INSTALL_H

#include <cinolib/hex_transition.h>

namespace cinolib
{

/* This function installs the hex transition schemes defined in hex_transition_schemes.h
 * to turn an adaptive grid with hanging nodes into a conformin all hexahedral mesh. The
 * function takes 3 parameters:
 * -m                => The input grid (must be a polyhedral mesh since the schemes are composed of generic polyhedra)
 * -transition_verts => vector of booleans with true values in correspondence of transition vertices. A transition
 * 			vertex in the grid is a vertex with 8 different hexahedra, four with size n and four with size n-1.
 * 			The transition vertices must be selected carefully in order achieve a correct installation.
 * -out 	     => The output mesh with schemes installed.
 */

template<class M, class V, class E, class F, class P>
CINO_INLINE
void hex_transition_install(const Polyhedralmesh<M,V,E,F,P> & m,
                            const std::vector<bool>         & transition_verts,
                                  Polyhedralmesh<M,V,E,F,P> & out);
}

#ifndef  CINO_STATIC_LIB
#include "hex_transition_install.cpp"
#endif

#endif // CINO_HEX_TRANSITION_INSTALL_H
