/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::diffusivityModel

Description
    Diffusivity model for multispecies binary diffusion coefficients 

SourceFiles
    diffusivityModel.C

\*---------------------------------------------------------------------------*/

#ifndef diffusivityModel_H
#define diffusivityModel_H

#include "binaryDiffusivityModel.H"
#include "porosityModelList.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                    Class diffusivityModel Declaration
\*---------------------------------------------------------------------------*/

class diffusivityModel
{

protected:

    // Protected data
    
        //- Transport propertied dictionary
        const IOdictionary dic_;

        //- Pressure [Pa]
        const volScalarField& p_;

        //- Temperature [K]
        const volScalarField& T_;

        //- Porosity (if present)
//         scalar eps_;
        volScalarField eps_;

        //- Tortuosity (if present)
//         scalar tau_;
        volScalarField tau_;

        const porosityModelList& pZones_;

        //- Species
        wordList species_;

        //- Binary diffusivity models 
        PtrList<binaryDiffusivityModel> DijModels_;   

        //- Binary diffusion coefficients
        PtrList<volScalarField> Dij_;  


    // Private Member Functions

        //- Disallow copy construct
        diffusivityModel(const diffusivityModel&);

        //- Disallow default bitwise assignment
        void operator=(const diffusivityModel&);


public:

    //- Runtime type information
    TypeName("diffusivityModel");

    // Constructors

        //- Construct from components
        diffusivityModel
        (
            const volScalarField& p,
            const volScalarField& T,
            const porosityModelList& pZones,
            const wordList& species
        );


    // Destructor

        virtual ~diffusivityModel()
        {}


    // Member Functions

        inline const volScalarField& D(label i, label j) const
        {
            label iStar = min(i,j);
            label jStar = max(i,j);
            label k = species_.size()*iStar+jStar-0.5*iStar*(iStar+1);
            return Dij_[k];
        }

        //- Update the diffusion coefficients
        virtual void update();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
