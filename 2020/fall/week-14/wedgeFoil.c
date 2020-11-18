//                                   Andy Torres
//                               CFAL@UCF, Fall 2020

//                                   wedgeFoil.c
//                                  =============
// 
// Simple program to tweak the geometry in the wedgeFoil case. 
// This is accomplished by generating the blockMeshDict file required
// for different wedge angles and tunnel numbers. 

// Tunnel Number:= Wind Tunnel Area (side view) / wedgeFoil area (side view)

#include <stdio.h>
#include <stdlib.h>

typedef struct WindTunnel
{
    double tunnel_number;
    double wedge_angle;
    double scale;
} WindTunnel;

void printHeader(FILE *blockMeshDict)
{
    fputs("/*--------------------------------*- C++ -*----------------------------------*\\\n"
            , blockMeshDict);
    fputs("| =========                 |                                                 |\n"
            , blockMeshDict);
    fputs("| \\\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |\n"
            , blockMeshDict);
    fputs("|  \\\\    /   O peration     | Version:  v1912                                 |\n"
            , blockMeshDict);
    fputs("|   \\\\  /    A nd           | Website:  www.openfoam.com                      |\n"
            , blockMeshDict);
    fputs("|    \\\\/     M anipulation  |                                                 |\n"
            , blockMeshDict);
    fputs("\\*---------------------------------------------------------------------------*/\n"
            , blockMeshDict);

    fputs("FoamFile\n", blockMeshDict);
    fputs("{\n", blockMeshDict);
    fputs("    version     2.0;\n", blockMeshDict);
    fputs("    format      ascii;\n", blockMeshDict);
    fputs("    class       dictionary;\n", blockMeshDict);
    fputs("    object      blockMeshDict;\n", blockMeshDict);
    fputs("}\n", blockMeshDict);
    fputs("// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n\n"
            , blockMeshDict);

    return;
}

void printParameters(FILE *blockMeshDict, WindTunnel *mesh)
{

    return;
}

void printVertices(FILE *blockMeshDict)
{
    return;
}


void printHexBlocks(FILE *blockMeshDict)
{
    return;
}


void printEdges(FILE *blockMeshDict)
{
    return;
}


void printPatches(FILE *blockMeshDict)
{
    return;
}

WindTunnel *createWindTunnel(double tunnel_number, double wedge_angle, double scale)
{
    WindTunnel *mesh = calloc(1, sizeof(WindTunnel));

    if (mesh == NULL)
    {
        return NULL;
    }

    mesh->tunnel_number = tunnel_number;
    mesh->wedge_angle = wedge_angle;
    mesh->scale = scale;

    return mesh;
}


int main(void)
{
    FILE *blockMeshDict = fopen("blockMeshDict", "w");

    printHeader(blockMeshDict);
    // printParameters();
    // printVertices();
    // printHexBlocks();
    // printEdges();
    // printPatches();
    // printFunctions();

    fclose(blockMeshDict);
    return 0;
}
