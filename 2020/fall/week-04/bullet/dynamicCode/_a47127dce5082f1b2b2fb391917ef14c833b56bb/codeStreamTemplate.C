/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) YEAR AUTHOR, AFFILIATION
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Description
    Template for use with codeStream.

\*---------------------------------------------------------------------------*/

#include "dictionary.H"
#include "Ostream.H"
#include "Pstream.H"
#include "unitConversion.H"

//{{{ begin codeInclude
#include "pointField.H"
//}}} end codeInclude

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //

//{{{ begin localCode

//}}} end localCode


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

extern "C" void codeStream_a47127dce5082f1b2b2fb391917ef14c833b56bb(Ostream& os, const dictionary& dict)
{
//{{{ begin code
    pointField points(19);
        points[0]  = point(25, 0, -0.5);
        points[1] = point(26, 0, -0.5);
        points[2] = point(26, 3.74, -0.5);
        points[3] = point(25, 3.74, -0.5);
        points[4] = point(25, 4.74, -0.5);
        points[5] = point(26, 4.74, -0.5);
        points[6] = point(26, 5.74, -0.5);
        points[7] = point(25, 5.74, -0.5);
        points[8] = point(24, 5.74, -0.5);
        points[9] = point(24, 4.74, -0.5);
        points[10] = point(24, 3.74, -0.5);
        points[11] = point(12.8, 2.58, -0.5);
        points[12] = point(11.72, 3.66, -0.5);
        points[13] = point(11.72, 5.74, -0.5);
        points[14] = point(0, 5.74, -0.5);
        points[15] = point(0, 3.66, -0.5);
        points[16] = point(0, 0, -0.5);
        points[17] = point(1, 0, -0.5);
        points[18] = point(2, 0, -0.5);


        // Duplicate z points
        label sz = points.size();
        points.setSize(2*sz);
        for (label i = 0; i < sz; i++)
        {
            const point& pt = points[i];
            points[i+sz] = point(pt.x(), pt.y(), -pt.z());
        }

        os  << points;
//}}} end code
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //

