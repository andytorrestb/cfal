/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
     \\/     M anipulation  |
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

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "psiThermo.H"
#include "turbulentFluidThermoModel.H"
#include "fixedRhoFvPatchScalarField.H"
#include "directionInterpolate.H"
#include "localEulerDdtScheme.H"
#include "fvcSmooth.H"

// This is a function declaration; this method will calculate some scalar value
// given the current time, location in space x, and a reference point x0. The
// function also accepts a scaling factor, scale.
// The actual implementation, or definition, is below.
scalar calculatePressure(scalar t, vector x, vector x0, scalar scale);

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
	#include "createFields.H"

    volScalarField p // note that pressure is a scalar field
	(
		IOobject
		(
		    "p", // name of the field
		    runTime.timeName(), // name of the current time, i.e. the time folder to read from
		    mesh,
		    IOobject::MUST_READ, // always gets imported, will throw an error if the field is missing
		    IOobject::AUTO_WRITE // will get saved automatically when the controlDict parameters will request it
		),
		mesh // initialises the field to match the size of the mesh with default (0) values
	);

    while(runTime.loop())
    {
        // p = fvc::grad(p)*dimensionedScalar("tmp",dimTime,1.);
        runTime.write();
    }

    Info << "Finished!" << endl;

    Info<< "End\n" << endl;

    return 0;
}

// definition of the custom function
scalar calculatePressure(scalar t, vector x, vector x0, scalar scale)
{
	// Calculates the distance between the base point and x, which is given by the magnitude (hence the name mag)
	// of the vector between x0 and x. The value is scaled by the passed factor, with the intention of making
	// it vary between 0 and 1.
	scalar r (mag(x-x0)/scale);

	// Calculate the inverse of r and apply a limiter to avoid dividing by zero.
	scalar rR (1./(r+1e-12));

	// definition of a frequency
	scalar f (1.);

	// Return a sinusoidally varying pressure with maximum at x0.
	// Note how we call the OpenFOAM sin method by referring to the Foam namespace.
	// This is done to differentiate between the native C++ implementation of a method with the same name
	// and thus avoid an ambiguous expression.
	return Foam::sin(2.*Foam::constant::mathematical::pi*f*t)*rR;
}

// ************************************************************************* //
