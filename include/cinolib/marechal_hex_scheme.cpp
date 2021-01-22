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
*     Marco Livesu (marco.livesu@gmail.com)                                     *
*     http://pers.ge.imati.cnr.it/livesu/                                       *
*                                                                               *
*     Italian National Research Council (CNR)                                   *
*     Institute for Applied Mathematics and Information Technologies (IMATI)    *
*     Via de Marini, 6                                                          *
*     16149 Genoa,                                                              *
*     Italy                                                                     *
*********************************************************************************/
#include <cinolib/marechal_hex_scheme.h>

namespace cinolib
{

template<class M, class V, class E, class F, class P>
CINO_INLINE
void marechal(AbstractPolyhedralMesh<M,V,E,F,P> & m,
              uint                                bot[5][5],
              uint                                top[3][3])
{
    std::vector<vec3d> verts;
    std::vector<std::vector<uint>> faces;
    std::vector<std::vector<uint>> polys;
    marechal(m, bot, top, verts, faces, polys);

    for(auto v : verts) m.vert_add(v);
    for(auto f : faces) m.face_add(f);
    for(auto p : polys) m.poly_add(p, std::vector<bool>(p.size(),true));
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F, class P>
CINO_INLINE
void marechal(const AbstractPolyhedralMesh<M,V,E,F,P> & m,
              const uint                                bot[5][5],
              const uint                                top[3][3],
                    std::vector<vec3d>                & verts,
                    std::vector<std::vector<uint>>    & faces,
                    std::vector<std::vector<uint>>    & polys)
{
    // create inner points
    vec3d up = (m.vert(top[1][1]) - m.vert(bot[2][2]))*0.5;
    verts.push_back(m.vert(bot[0][2]) + up);
    verts.push_back(m.vert(bot[2][0]) + up);
    verts.push_back(m.vert(bot[2][1]) + up*0.6);
    verts.push_back(m.vert(bot[2][2]) + up*0.6);
    verts.push_back(m.vert(top[1][1]) - up);
    verts.push_back(m.vert(bot[2][3]) + up*0.6);
    verts.push_back(m.vert(bot[2][4]) + up);
    verts.push_back(m.vert(bot[4][2]) + up);
    //
    std::map<uint,uint> map;
    uint v_off = m.num_verts();
    map[bot[0][2]] = v_off;
    map[bot[2][0]] = v_off+1;
    map[bot[2][1]] = v_off+2;
    map[bot[2][2]] = v_off+3;
    map[top[1][1]] = v_off+4;
    map[bot[2][3]] = v_off+5;
    map[bot[2][4]] = v_off+6;
    map[bot[4][2]] = v_off+7;

    // floor
    // THESE ARE ASSUMED TO BE ALREADY IN THE INPUT MESH
    int b00 = m.face_id({bot[0][0], bot[0][1], bot[1][1], bot[1][0]}); assert(b00>=0);
    int b01 = m.face_id({bot[1][1], bot[0][1], bot[0][2], bot[1][2]}); assert(b01>=0);
    int b02 = m.face_id({bot[1][2], bot[0][2], bot[0][3], bot[1][3]}); assert(b02>=0);
    int b03 = m.face_id({bot[1][3], bot[0][3], bot[0][4], bot[1][4]}); assert(b03>=0);
    int b10 = m.face_id({bot[1][0], bot[1][1], bot[2][1], bot[2][0]}); assert(b10>=0);
    int b11 = m.face_id({bot[2][1], bot[1][1], bot[1][2], bot[2][2]}); assert(b11>=0);
    int b12 = m.face_id({bot[2][2], bot[1][2], bot[1][3], bot[2][3]}); assert(b12>=0);
    int b13 = m.face_id({bot[2][3], bot[1][3], bot[1][4], bot[2][4]}); assert(b13>=0);
    int b20 = m.face_id({bot[3][0], bot[2][0], bot[2][1], bot[3][1]}); assert(b20>=0);
    int b21 = m.face_id({bot[3][1], bot[2][1], bot[2][2], bot[3][2]}); assert(b21>=0);
    int b22 = m.face_id({bot[3][2], bot[2][2], bot[2][3], bot[3][3]}); assert(b22>=0);
    int b23 = m.face_id({bot[3][3], bot[2][3], bot[2][4], bot[3][4]}); assert(b23>=0);
    int b30 = m.face_id({bot[4][0], bot[3][0], bot[3][1], bot[4][1]}); assert(b30>=0);
    int b31 = m.face_id({bot[3][1], bot[3][2], bot[4][2], bot[4][1]}); assert(b31>=0);
    int b32 = m.face_id({bot[4][2], bot[3][2], bot[3][3], bot[4][3]}); assert(b32>=0);
    int b33 = m.face_id({bot[4][3], bot[3][3], bot[3][4], bot[4][4]}); assert(b33>=0);

    // ceiling
    // THESE ARE ASSUMED TO BE ALREADY IN THE INPUT MESH
    int t00 = m.face_id({top[0][0], top[1][0], top[1][1], top[0][1]}); assert(t00>=0);
    int t01 = m.face_id({top[0][1], top[0][2], top[1][2], top[1][1]}); assert(t01>=0);
    int t10 = m.face_id({top[1][0], top[1][1], top[2][1], top[2][0]}); assert(t10>=0);
    int t11 = m.face_id({top[2][1], top[2][2], top[1][2], top[1][1]}); assert(t11>=0);

    // triangular flaps attached to base (from face 0 to face 9)
    faces.push_back({bot[1][0], bot[2][0], map.at(bot[2][0])});
    faces.push_back({bot[2][0], bot[3][0], map.at(bot[2][0])});
    faces.push_back({bot[1][1], bot[2][1], map.at(bot[2][1])});
    faces.push_back({bot[2][1], bot[3][1], map.at(bot[2][1])});
    faces.push_back({bot[1][2], bot[2][2], map.at(bot[2][2])});
    faces.push_back({bot[3][2], bot[2][2], map.at(bot[2][2])});
    faces.push_back({bot[1][3], bot[2][3], map.at(bot[2][3])});
    faces.push_back({bot[3][3], bot[2][3], map.at(bot[2][3])});
    faces.push_back({bot[1][4], bot[2][4], map.at(bot[2][4])});
    faces.push_back({bot[3][4], bot[2][4], map.at(bot[2][4])});

    // rectangular flaps attached to base (from face 10 to face 13)
    faces.push_back({bot[2][0], bot[2][1], map.at(bot[2][1]), map.at(bot[2][0])});
    faces.push_back({bot[2][1], bot[2][2], map.at(bot[2][2]), map.at(bot[2][1])});
    faces.push_back({bot[2][2], bot[2][3], map.at(bot[2][3]), map.at(bot[2][2])});
    faces.push_back({bot[2][3], bot[2][4], map.at(bot[2][4]), map.at(bot[2][3])});

    // rectangular lids of the lower prism (from face 14 to face 21)
    faces.push_back({bot[1][0], bot[1][1], map.at(bot[2][1]), map.at(bot[2][0])});
    faces.push_back({bot[3][0], bot[3][1], map.at(bot[2][1]), map.at(bot[2][0])});
    faces.push_back({bot[1][1], bot[1][2], map.at(bot[2][2]), map.at(bot[2][1])});
    faces.push_back({bot[3][1], bot[3][2], map.at(bot[2][2]), map.at(bot[2][1])});
    faces.push_back({bot[1][2], bot[1][3], map.at(bot[2][3]), map.at(bot[2][2])});
    faces.push_back({bot[3][2], bot[3][3], map.at(bot[2][3]), map.at(bot[2][2])});
    faces.push_back({bot[1][3], bot[1][4], map.at(bot[2][4]), map.at(bot[2][3])});
    faces.push_back({bot[3][3], bot[3][4], map.at(bot[2][4]), map.at(bot[2][3])});

    // other internal faces (from face 22 to face 37)
    faces.push_back({       bot[4][2],         bot[4][3],  map.at(bot[4][2])});
    faces.push_back({       bot[0][2],         bot[0][3],  map.at(bot[0][2])});
    faces.push_back({       bot[4][2],         bot[4][1],  map.at(bot[4][2])});
    faces.push_back({       bot[0][2],         bot[0][1],  map.at(bot[0][2])});
    faces.push_back({map.at(bot[2][2]), map.at(bot[2][3]), map.at(top[1][1])});
    faces.push_back({map.at(bot[2][2]), map.at(bot[2][1]), map.at(top[1][1])});
    faces.push_back({map.at(bot[4][2]), map.at(top[1][1]),        top[1][1],         top[2][1]});
    faces.push_back({map.at(bot[0][2]), map.at(top[1][1]),        top[1][1],         top[0][1]});
    faces.push_back({map.at(top[1][1]), map.at(bot[2][3]), map.at(bot[2][4]),        top[1][2],         top[1][1]});
    faces.push_back({map.at(top[1][1]), map.at(bot[2][1]), map.at(bot[2][0]),        top[1][0],         top[1][1]});
    faces.push_back({map.at(bot[2][2]),        bot[3][2],         bot[4][2],  map.at(bot[4][2]), map.at(top[1][1])});
    faces.push_back({map.at(bot[2][3]),        bot[3][3],         bot[4][3],  map.at(bot[4][2]), map.at(top[1][1])});
    faces.push_back({map.at(bot[2][2]),        bot[1][2],         bot[0][2],  map.at(bot[0][2]), map.at(top[1][1])});
    faces.push_back({map.at(bot[2][3]),        bot[1][3],         bot[0][3],  map.at(bot[0][2]), map.at(top[1][1])});
    faces.push_back({map.at(bot[2][1]),        bot[3][1],         bot[4][1],  map.at(bot[4][2]), map.at(top[1][1])});
    faces.push_back({map.at(bot[2][1]),        bot[1][1],         bot[0][1],  map.at(bot[0][2]), map.at(top[1][1])});

    // lateral faces (excluded exposed faces of triangular prisms) (from face 38 to face 45)
    faces.push_back({bot[0][0], bot[0][1], map.at(bot[0][2]), top[0][1],        top[0][0]});
    faces.push_back({bot[0][4], bot[0][3], map.at(bot[0][2]), top[0][1],        top[0][2]});
    faces.push_back({bot[4][0], bot[4][1], map.at(bot[4][2]), top[2][1],        top[2][0]});
    faces.push_back({bot[4][4], bot[4][3], map.at(bot[4][2]), top[2][1],        top[2][2]});
    faces.push_back({bot[1][0], bot[0][0],        top[0][0],  top[1][0], map.at(bot[2][0])});
    faces.push_back({bot[1][4], bot[0][4],        top[0][2],  top[1][2], map.at(bot[2][4])});
    faces.push_back({bot[3][0], bot[4][0],        top[2][0],  top[1][0], map.at(bot[2][0])});
    faces.push_back({bot[3][4], bot[4][4],        top[2][2],  top[1][2], map.at(bot[2][4])});

    uint off = m.num_faces();

    // elements in the lower prism
    polys.push_back({ off+0, off+2, off+10, off+14, (uint)b10 });
    polys.push_back({ off+1, off+3, off+10, off+15, (uint)b20 });
    polys.push_back({ off+2, off+4, off+11, off+16, (uint)b11 });
    polys.push_back({ off+3, off+5, off+11, off+17, (uint)b21 });
    polys.push_back({ off+4, off+6, off+12, off+18, (uint)b12 });
    polys.push_back({ off+5, off+7, off+12, off+19, (uint)b22 });
    polys.push_back({ off+6, off+8, off+13, off+20, (uint)b13 });
    polys.push_back({ off+7, off+9, off+13, off+21, (uint)b23 });

    // custom elements
    polys.push_back({ off+19, off+22, off+32, off+33, off+26, (uint)b32 });
    polys.push_back({ off+18, off+26, off+23, off+34, off+35, (uint)b02 });
    polys.push_back({ off+17, off+32, off+24, off+36, off+27, (uint)b31 });
    polys.push_back({ off+16, off+27, off+34, off+25, off+37, (uint)b01 });
    polys.push_back({ off+21, off+33, off+45, off+41, off+28, off+30, (uint)t11, (uint)b33 });
    polys.push_back({ off+20, off+35, off+30, off+43, off+39, off+29, (uint)t01, (uint)b03 });
    polys.push_back({ off+15, off+36, off+28, off+44, off+40, off+31, (uint)t10, (uint)b30 });
    polys.push_back({ off+14, off+37, off+29, off+31, off+42, off+38, (uint)t00, (uint)b00 });
}

}