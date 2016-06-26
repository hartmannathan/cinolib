/****************************************************************************
* Italian National Research Council                                         *
* Institute for Applied Mathematics and Information Technologies, Genoa     *
* IMATI-GE / CNR                                                            *
*                                                                           *
* Author: Marco Livesu (marco.livesu@gmail.com)                             *
*                                                                           *
* Copyright(C) 2016                                                         *
* All rights reserved.                                                      *
*                                                                           *
* This file is part of CinoLib                                              *
*                                                                           *
* CinoLib is free software; you can redistribute it and/or modify           *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 3 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
****************************************************************************/
#ifndef VECTOR_FIELD_H
#define VECTOR_FIELD_H

#include "vec3.h"
#include <eigen3/Eigen/Dense>

namespace cinolib
{

class VectorField : public Eigen::VectorXd
{
    public:

        VectorField();
        VectorField(const int size);

        vec3d vec_at(const int pos) const;

        void set(const int pos, const vec3d & vec);

        void normalize();

        // for more info, see:
        // http://eigen.tuxfamily.org/dox/TopicCustomizingEigen.html
        //
        // This method allows you to assign Eigen expressions to VectorField
        //
        template<typename OtherDerived>
        VectorField & operator= (const Eigen::MatrixBase<OtherDerived>& other);

        //
        // This constructor allows you to construct VectorField from Eigen expressions
        //
        template<typename OtherDerived>
        VectorField(const Eigen::MatrixBase<OtherDerived>& other);
};

}

#ifndef  CINO_STATIC_LIB
#include "vector_field.cpp"
#endif


#endif // VECTOR_FIELD_H
