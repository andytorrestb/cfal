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

extern "C" void codeStream_abe860124d5a9844e36359eae3df59301da97466(Ostream& os, const dictionary& dict)
{
//{{{ begin code
    pointField points(19);
        points[0]  = point(0.75, 0, -0.5);
        points[1] = point(1, 0, -0.5);
        points[2] = point(1, 0.25, -0.5);
        points[3] = point(0.75, 0.25, -0.5);
        points[4] = point(0.75, 0.5, -0.5);
        points[5] = point(1, 0.5, -0.5);
        points[6] = point(1, 1, -0.5);
        points[7] = point(0.75, 1, -0.5);
        points[8] = point(0.5, 1, -0.5);
        points[9] = point(0.6, 0.5, -0.5);
        points[10] = point(0.6, 0.25, -0.5);
        points[11] = point(0.55, 0.2, -0.5);
        points[12] = point(0.45, 0.4, -0.5);
        points[13] = point(0.45, 1, -0.5);
        points[14] = point(0, 1, -0.5);
        points[15] = point(0, 0.4, -0.5);
        points[16] = point(0, 0, -0.5);
        points[17] = point(0.25, 0, -0.5);
        points[18] = point(0.5, 0, -0.5);
        )

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

