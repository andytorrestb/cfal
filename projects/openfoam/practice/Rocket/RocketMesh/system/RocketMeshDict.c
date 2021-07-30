//                                   Andy Torres
//                               CFAL@UCF, Fall 2020

//                                  RocketMeshDict.c
//                                 =================
// 

// Generates blockMeshDict file required for a 2D simulation of external flow around a simple 
// rocket based on user input. User can enter Tunnel Number (Tu), the rocket's diameter (D), 
// height (H), and Nose Cone Ratio (Nc).

// proper syntax for running the program is: 
//      ./RocketMeshDict <Tu> <D> <H> <Nc>

// Tunnel Number := Wind Tunnel Length / Rocket Height

// Nose Cone Ratio := Height of Nose Cone / Radius of Rocket 

// Jump all the way to the bottom for main function. Read through other functions as necessary.

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

// Command line constants
#define NUM_ARGS 4

// Error Constants
#define NULL_POINTER_ERR -10000000

// WindTunnel Constants
#define UPWIND_PERCENTAGE 0.05

// Rocket Engine Constants
#define HEIGHT_PERCENTAGE 0.01
#define THROAT_PERCENTAGE 0.125
#define EXIT_PERCENTAGE 0.125

// Nose Cone Constants
#define REFINEMENT 0.0005
#define M_PI 3.14159265358979323846


// Stores dimensional parameters for rocket.
typedef struct Rocket
{
    double diameter;
    double height;
    double noseConeRatio;
} Rocket;

// Stores data to create coordinates for mesh.
typedef struct WindTunnel
{
    double tunnel_number;

    double x0;
    double x1;
    double x2;
    double x3;
    double x4;
    double x5;

    double y0;
    double y1;
    double y2;
    double y3;
    double y4;
    double y5;
    double y6;
    double y7;
    double y8;

    Rocket *rocket;
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

    // Weird trailing zero crap. Not sure if it's importnt to get rid of. 
    // Can probably just keep it as a string. As I don't need it for any math. 
    fprintf(blockMeshDict, "scale   %f;\n\n", 1.0);
    fprintf(blockMeshDict, "// From diagram.\n");
    fprintf(blockMeshDict, "x_0 %f;\n", mesh->x0);
    fprintf(blockMeshDict, "x_1 %f;\n", mesh->x1);
    fprintf(blockMeshDict, "x_2 %f;\n", mesh->x2);
    fprintf(blockMeshDict, "x_3 %f;\n\n", mesh->x3);
    fprintf(blockMeshDict, "x_4 %f;\n\n", mesh->x4);
    fprintf(blockMeshDict, "x_5 %f;\n\n", mesh->x5);

    fprintf(blockMeshDict, "y_0 %f;\n", mesh->y0);
    fprintf(blockMeshDict, "y_1 %f;\n", mesh->y1);
    fprintf(blockMeshDict, "y_2 %f;\n", mesh->y2);
    fprintf(blockMeshDict, "y_3 %f;\n", mesh->y3);
    fprintf(blockMeshDict, "y_4 %f;\n\n", mesh->y4);
    fprintf(blockMeshDict, "y_5 %f;\n\n", mesh->y5);
    fprintf(blockMeshDict, "y_6 %f;\n\n", mesh->y6);
    fprintf(blockMeshDict, "y_7 %f;\n\n", mesh->y7);
    fprintf(blockMeshDict, "y_8 %f;\n\n", mesh->y8);
    

    fprintf(blockMeshDict, "zmin 0;\n");
    fprintf(blockMeshDict, "zmax 0.05;\n\n");

    return;
}

void printVertices(FILE *blockMeshDict)
{
    fputs("vertices\n", blockMeshDict);
    fputs("(\n", blockMeshDict);

    // block 0
    fputs("    // block 0\n", blockMeshDict);
    fputs("    ($x_0 $y_4 $zmin) // 0\n", blockMeshDict);
    fputs("    ($x_1 $y_4 $zmin) // 1\n", blockMeshDict);
    fputs("    ($x_1 $y_8 $zmin) // 2\n", blockMeshDict);
    fputs("    ($x_0 $y_8 $zmin) // 3\n\n", blockMeshDict);

    fputs("    ($x_0 $y_4 $zmax) // 4\n", blockMeshDict);
    fputs("    ($x_1 $y_4 $zmax) // 5\n", blockMeshDict);
    fputs("    ($x_1 $y_8 $zmax) // 6\n", blockMeshDict);
    fputs("    ($x_0 $y_8 $zmax) // 7\n\n", blockMeshDict);

    // block 1
    fputs("    // block 1 (extra needed)\n", blockMeshDict);
    fputs("    ($x_2 $y_7 $zmin) // 8\n", blockMeshDict);
    fputs("    ($x_2 $y_8 $zmin) // 9\n", blockMeshDict);

    fputs("    ($x_2 $y_7 $zmax) // 10\n", blockMeshDict);
    fputs("    ($x_2 $y_8 $zmax) // 11\n\n", blockMeshDict);
    
    // block 2
    fputs("    // block 2 (extra needed)\n", blockMeshDict);
    fputs("    ($x_3 $y_7 $zmin) // 12\n", blockMeshDict);
    fputs("    ($x_3 $y_8 $zmin) // 13\n", blockMeshDict);

    fputs("    ($x_3 $y_7 $zmax) // 14\n", blockMeshDict);
    fputs("    ($x_3 $y_8 $zmax) // 15\n\n", blockMeshDict);

    // block 3
    fputs("    // block 3 (extra needed)\n", blockMeshDict);
    fputs("    ($x_4 $y_7 $zmin) // 16\n", blockMeshDict);
    fputs("    ($x_4 $y_8 $zmin) // 17\n", blockMeshDict);

    fputs("    ($x_4 $y_7 $zmax) // 18\n", blockMeshDict);
    fputs("    ($x_4 $y_8 $zmax) // 19\n", blockMeshDict);

    // block 4
    fputs("    // block 4 (extra needed)\n", blockMeshDict);
    fputs("    ($x_5 $y_7 $zmin) // 20\n", blockMeshDict);
    fputs("    ($x_5 $y_8 $zmin) // 21\n", blockMeshDict);

    fputs("    ($x_5 $y_7 $zmax) // 22\n", blockMeshDict);
    fputs("    ($x_5 $y_8 $zmax) // 23\n\n", blockMeshDict);

    // block 5 
    fputs("    // block 5 (extra needed)\n", blockMeshDict);
    fputs("    ($x_4 $y_6 $zmin) // 24\n", blockMeshDict);
    fputs("    ($x_3 $y_5 $zmin) // 25\n", blockMeshDict);
    
    fputs("    ($x_4 $y_6 $zmax) // 26\n", blockMeshDict);
    fputs("    ($x_3 $y_5 $zmax) // 27\n\n", blockMeshDict);

    // block 6
    fputs("    // block 6 (extra needed)\n", blockMeshDict);
    fputs("    ($x_5 $y_6 $zmin) // 28\n", blockMeshDict);

    fputs("    ($x_5 $y_6 $zmax) // 29\n\n", blockMeshDict);

    // block 7
    fputs("    // block 7 (extra needed)\n", blockMeshDict);
    fputs("    ($x_5 $y_2 $zmin) // 30\n", blockMeshDict);
    fputs("    ($x_4 $y_2 $zmin) // 31\n", blockMeshDict);

    fputs("    ($x_5 $y_2 $zmax) // 32\n", blockMeshDict);
    fputs("    ($x_4 $y_2 $zmax) // 33\n", blockMeshDict);

    // block 8
    fputs("    // block 8 (extra needed)\n", blockMeshDict);
    fputs("    ($x_5 $y_1 $zmin) // 34\n", blockMeshDict);
    fputs("    ($x_4 $y_1 $zmin) // 35\n", blockMeshDict);

    fputs("    ($x_5 $y_1 $zmax) // 36\n", blockMeshDict);
    fputs("    ($x_4 $y_1 $zmax) // 37\n", blockMeshDict);

    // block 9
    fputs("    // block 9 (extra needed)\n", blockMeshDict);
    fputs("    ($x_3 $y_3 $zmin) // 38\n", blockMeshDict);
    fputs("    ($x_3 $y_1 $zmin) // 39\n", blockMeshDict);

    fputs("    ($x_3 $y_3 $zmax) // 40\n", blockMeshDict);
    fputs("    ($x_3 $y_1 $zmax) // 41\n", blockMeshDict);

    // block 10
    fputs("    // block 10 (extra needed)\n", blockMeshDict);
    fputs("    ($x_5 $y_0 $zmin) // 42\n", blockMeshDict);
    fputs("    ($x_4 $y_0 $zmin) // 43\n", blockMeshDict);

    fputs("    ($x_5 $y_0 $zmax) // 44\n", blockMeshDict);
    fputs("    ($x_4 $y_0 $zmax) // 45\n", blockMeshDict);
    
    // block 11
    fputs("    // block 11 (extra needed)\n", blockMeshDict);
    fputs("    ($x_3 $y_0 $zmin) // 46\n", blockMeshDict);

    fputs("    ($x_3 $y_0 $zmax) // 47\n", blockMeshDict);

    // block 12
    fputs("    // block 12 (extra needed)\n", blockMeshDict);
    fputs("    ($x_2 $y_1 $zmin) // 48\n", blockMeshDict);
    fputs("    ($x_2 $y_0 $zmin) // 49\n", blockMeshDict);

    fputs("    ($x_2 $y_1 $zmax) // 50\n", blockMeshDict);
    fputs("    ($x_2 $y_0 $zmax) // 51\n", blockMeshDict);
       
    // block 13
    fputs("    // block 13 (extra needed)\n", blockMeshDict);
    fputs("    ($x_1 $y_0 $zmin) // 52\n", blockMeshDict);

    fputs("    ($x_1 $y_0 $zmax) // 53\n", blockMeshDict);

    // block 14
    fputs("    // block 14 (extra needed)\n", blockMeshDict);
    fputs("    ($x_0 $y_0 $zmin) // 52\n", blockMeshDict);

    fputs("    ($x_0 $y_0 $zmax) // 53\n", blockMeshDict);  
    fputs(");\n\n", blockMeshDict);

    return;
}


void printHexBlocks(FILE *blockMeshDict)
{
    fputs("blocks\n", blockMeshDict);
    fputs("(\n", blockMeshDict);
    fputs("    hex (0 1 2 3 4 5 6 7) (10 10 1) simpleGrading (1 1 1) // 0\n", blockMeshDict);
    fputs("    hex (1 8 9 2 5 10 11 6) (10 10 1) simpleGrading (1 1 1) // 1\n", blockMeshDict);
    fputs("    hex (8 12 13 9 10 14 15 11) (10 10 1) simpleGrading (1 1 1) // 2\n", blockMeshDict);
    fputs("    hex (12 16 17 13 14 18 19 15) (10 10 1) simpleGrading (1 1 1) // 3\n", blockMeshDict);
    fputs("    hex (16 20 21 17 18 22 23 19) (10 10 1) (1 1 1) // 4\n", blockMeshDict);
    fputs("    hex (25 24 16 12 27 26 18 14) (10 10 1) simpleGrading (1 1 1) // 5\n", blockMeshDict);
    fputs("    hex (24 28 20 16 26 29 22 18) (10 10 1) simpleGrading (1 1 1) // 6\n", blockMeshDict);
    fputs("    hex (31 30 28 24 33 32 29 26) (10 10 1) simpleGrading (1 1 1) // 7\n", blockMeshDict);
    fputs("    hex (35 34 30 31 37 36 32 33) (10 10 1) simpleGrading (1 1 1) // 8\n", blockMeshDict);
    fputs("    hex (39 35 31 38 41 37 33 40) (10 10 1) simpleGrading (1 1 1) // 9\n", blockMeshDict);
    fputs("    hex (43 42 34 35 45 44 36 37) (10 10 1) simpleGrading (1 1 1) // 10\n", blockMeshDict);
    fputs("    hex (46 43 35 39 47 45 37 41) (10 10 1) simpleGrading (1 1 1) // 11\n", blockMeshDict);
    fputs("    hex (49 46 39 48 51 47 41 50) (10 10 1) simpleGrading (1 1 1) // 12\n", blockMeshDict);
    fputs("    hex (52 49 48 1 53 51 50 5) (10 10 1) simpleGrading (1 1 1) // 13\n", blockMeshDict);
    fputs("    hex (54 52 1 0 55 53 5 4) (10 10 1) simpleGrading (1 1 1) // 14\n", blockMeshDict);
    fputs(");\n", blockMeshDict);
    return;
}

double vonKarman(double x, WindTunnel *mesh)
{   
    Rocket *rocket;

    double theta, radius, length;
    if (mesh == NULL)
    {
        printf("NULL WindTunnel pointer in vonKarman()\n");
        return NULL_POINTER_ERR;
    }

    rocket = mesh->rocket;

    if (rocket == NULL)
    {
        printf("NULL Rocket pointer in vonKarman()\n");
        return NULL_POINTER_ERR;
    }

    radius = mesh->y7 - mesh->y4;
    length = mesh->x2 - mesh->x1;
    theta = acos(1 - 2 * x / length);

    return (radius / sqrt(M_PI)) * sqrt(theta - 0.5 * sin(2 * theta));
}

void printEdges(FILE *blockMeshDict, WindTunnel *mesh)
{
    Rocket *rocket;
    double noseConeLength, x, delta_x = REFINEMENT;

    if (blockMeshDict == NULL)
    {
        printf("NULL FILE pointer in printEdges()\n");
        return;
    }

    rocket = mesh->rocket;

    if (rocket == NULL)
    {
        printf("NULL Rocket pointer in printEdges()\n");
        return;
    }

    // edges
    fputs("edges\n", blockMeshDict);
    fputs("(\n", blockMeshDict);

    // Upper edge of Nose Cone
    fputs("    // Upper edge of Nose Cone\n", blockMeshDict);
    fputs("    BSpline 1 8\n", blockMeshDict);
    fputs("    (\n", blockMeshDict);

    noseConeLength = 0.5* rocket->diameter * rocket->noseConeRatio;

    for (x = delta_x; x < noseConeLength; x += delta_x)
    {
        fprintf(blockMeshDict, "        (%f %f 0)\n", mesh->x1 + x, mesh->y4 + vonKarman(x, mesh));
    }

    fputs("    )\n\n", blockMeshDict);

    fputs("    BSpline 5 10\n", blockMeshDict);
    fputs("    (\n", blockMeshDict);

    for (x = delta_x; x < noseConeLength; x += delta_x)
    {
        fprintf(blockMeshDict, "        (%f %f 0.05)\n", mesh->x1 + x, mesh->y4 + vonKarman(x, mesh));
    }

    fputs("    )\n\n", blockMeshDict);

    // Lower edge of Nose Cone
    fputs("    // Lower edge of Nose Cone\n", blockMeshDict);
    fputs("    BSpline 1 48\n", blockMeshDict);
    fputs("    (\n", blockMeshDict);

    for (x = delta_x; x < noseConeLength; x += delta_x)
    {
        fprintf(blockMeshDict, "        (%f %f 0)\n", mesh->x1 + x, mesh->y4 - vonKarman(x, mesh));
    }

    fputs("    )\n\n", blockMeshDict);

    fputs("    BSpline 5 50\n", blockMeshDict);
    fputs("    (\n", blockMeshDict);

    for (x = delta_x; x < noseConeLength; x += delta_x)
    {
        fprintf(blockMeshDict, "        (%f %f 0.05)\n", mesh->x1 + x, mesh->y4 - vonKarman(x, mesh));
    }

    fputs("    )\n\n", blockMeshDict);


    fputs(");\n\n", blockMeshDict);
    return;
}


void printPatches(FILE *blockMeshDict)
{
    fputs("boundary\n", blockMeshDict);
    fputs("(\n", blockMeshDict);

    // // flow patch
    // fputs("    flow\n", blockMeshDict);
    // fputs("    {\n", blockMeshDict);
    // fputs("        type patch;\n", blockMeshDict);
    // fputs("        faces\n", blockMeshDict);
    // fputs("        (\n", blockMeshDict);
    // fputs("            // Front of tunnel\n", blockMeshDict);
    // fputs("            (4 7 3 0)\n", blockMeshDict);
    // fputs("            (31 4 0 30)\n\n", blockMeshDict);

    // fputs("            // Top of tunnel\n", blockMeshDict);
    // fputs("            (7 6 2 3)\n", blockMeshDict);
    // fputs("            (6 10 8 2)\n", blockMeshDict);
    // fputs("            (10 15 13 8)\n\n", blockMeshDict);

    // fputs("            // Back of tunnel\n", blockMeshDict);
    // fputs("            (12 13 15 14)\n", blockMeshDict);
    // fputs("            (17 12 14 19)\n", blockMeshDict);
    // fputs("            (21 17 19 23)\n", blockMeshDict);
    // fputs("            (25 21 23 27)\n\n", blockMeshDict);

    // fputs("            // Bottom of tunnel\n", blockMeshDict);
    // fputs("            (24 25 27 26)\n", blockMeshDict);
    // fputs("            (28 24 26 29)\n", blockMeshDict);
    // fputs("            (30 28 29 31)\n", blockMeshDict);
    // fputs("        );\n", blockMeshDict);
    // fputs("    }\n\n", blockMeshDict);

    // // obstacle patch
    // fputs("    obstacle\n", blockMeshDict);
    // fputs("    {\n", blockMeshDict);
    // fputs("        type wall;\n", blockMeshDict);
    // fputs("        faces\n", blockMeshDict);
    // fputs("        (\n", blockMeshDict);
    // fputs("            (1 9 11 5)\n", blockMeshDict);
    // fputs("            (18 11 9 16)\n", blockMeshDict);
    // fputs("            (22 18 16 20)\n", blockMeshDict);
    // fputs("            (20 1 5 22)\n", blockMeshDict);
    // fputs("        );\n", blockMeshDict);
    // fputs("    }\n\n", blockMeshDict);

    // // frontAndBack patch
    // fputs("    frontAndBack\n", blockMeshDict);
    // fputs("    {\n", blockMeshDict);
    // fputs("        type empty;\n", blockMeshDict);
    // fputs("        faces\n", blockMeshDict);
    // fputs("        (\n", blockMeshDict);
    // fputs("            // Upper back\n", blockMeshDict);
    // fputs("            (0 3 2 1)\n", blockMeshDict);
    // fputs("            (1 2 8 9)\n", blockMeshDict);
    // fputs("            (9 8 13 12)\n", blockMeshDict);
    // fputs("            (16 9 12 17)\n\n", blockMeshDict);

    // fputs("            // Lower back\n", blockMeshDict);
    // fputs("            (30 0 1 28)\n", blockMeshDict);
    // fputs("            (28 1 20 24)\n", blockMeshDict);
    // fputs("            (24 20 21 25)\n", blockMeshDict);
    // fputs("            (20 16 17 21)\n\n", blockMeshDict);

    // fputs("            // Upper front\n", blockMeshDict);
    // fputs("            (5 6 7 4)\n", blockMeshDict);
    // fputs("            (11 10 6 5)\n", blockMeshDict);
    // fputs("            (14 15 10 11)\n", blockMeshDict);
    // fputs("            (19 14 11 18)\n\n", blockMeshDict);

    // fputs("            // Lower front\n", blockMeshDict);
    // fputs("            (29 5 4 31)\n", blockMeshDict);
    // fputs("            (26 22 5 29)\n", blockMeshDict);
    // fputs("            (27 23 22 26)\n", blockMeshDict);
    // fputs("            (23 19 18 22)\n", blockMeshDict);
    // fputs("        );\n", blockMeshDict);
    // fputs("    }\n", blockMeshDict);
    fputs(");\n\n", blockMeshDict);

    return;
}

void printPatchPairs(FILE *blockMeshDict)
{
    fputs("mergePatchPairs\n", blockMeshDict);
    fputs("(\n", blockMeshDict);
    fputs(");\n\n", blockMeshDict);

    return;
}

void printFooter(FILE *blockMeshDict)
{
    fputs("// ************************************************************************* //\n", blockMeshDict);
}

Rocket *createRocket(double diameter, double height, double noseConeRatio)
{
    Rocket *rocket = calloc(1, sizeof(Rocket));
    rocket->diameter = diameter;
    rocket->height = height;
    rocket->noseConeRatio = noseConeRatio;
    return rocket;
}

// Set coordinates for blockMeshDict according to data stored in mesh.
// x coordinates are established first, then y coordinates. 
void setCoordinates(WindTunnel *mesh)
{
    Rocket *rocket;

    if (mesh == NULL)
    {
        printf("NULL pointer in setCoordinates()\n");
        return;
    }

    rocket = mesh->rocket;

    // x - coordinates

    // front of mesh.
    mesh->x0 = 0;

    // back of of mesh. (i. e. length).
    mesh->x5 = mesh->tunnel_number * rocket->height;


    // tip of nose cone. (only 5% of mesh should come before the tip.)
    mesh->x1 = UPWIND_PERCENTAGE * mesh->x5;

    // base of nose cone. (tip + length )
    mesh->x2 = mesh->x1 + 0.5 * rocket->diameter * rocket->noseConeRatio;

    // base of rocket body.
    mesh->x3 = mesh->x2 + rocket->height;

    // base of engine (height is some small percentage of over all height)
    mesh->x4 = mesh->x3 + HEIGHT_PERCENTAGE * rocket->height;

    // y - coordinates

    // bottom of mesh.
    mesh->y0 = 0;

    // top of mesh (half of length)
    mesh->y8 = 0.5 * mesh->x5; 

    // centerline of rocket (half of height)
    mesh->y4 = 0.5 * mesh->y8;

    // upper edge of rocket (center line + radius)
    mesh->y7 = mesh->y4 + 0.5 * rocket->diameter;

    // lower edge of rocket (center line - radius)
    mesh->y1 = mesh->y4 - 0.5 * rocket->diameter;

    // lower edge of engine exit (lower edge + exit percentage)
    mesh->y2 = mesh->y1 + EXIT_PERCENTAGE * rocket->diameter;

    // upper edge of engine exit (upper edge - exit percentage)
    mesh->y6 = mesh->y7 - EXIT_PERCENTAGE * rocket->diameter;

    // lower edge of engine throat (lower edge + throat percentage)
    mesh->y3 =  mesh->y1 + THROAT_PERCENTAGE * rocket->diameter;

    // upper edge of engine throat (upper edge - throat percentage)
    mesh->y5 = mesh->y7 - THROAT_PERCENTAGE * rocket->diameter; 

    return;
}

WindTunnel *createWindTunnel(double tunnel_number, double diameter, double height, double noseConeRatio)
{
    WindTunnel *mesh = calloc(1, sizeof(WindTunnel));

    if (mesh == NULL)
    {
        return NULL;
    }

    mesh->tunnel_number = tunnel_number;
    mesh->rocket = createRocket(diameter, height, noseConeRatio);

    if (mesh->rocket == NULL)
    {
        return NULL;
    }
    
    setCoordinates(mesh);

    return mesh;
}

void printSyntaxHelper()
{
    printf("\n          Seems like you've entered the wrong syntax.\n");
    printf("       Try running the program with the following flags\n");
    printf("      $ ./RocketMeshDict <Tu> <D> <H> <Nc>\n\n");
}

int main(int argc, char **argv)
{
    int i;
    double tunnel_number, diameter, height, noseConeRatio;
    WindTunnel *mesh;
    FILE *blockMeshDict;
    char *eptr; // needed for strtod();

    // Check that user used proper syntax when running the program.
    for (i = 1; i <= NUM_ARGS; i++)
    {
        if (argv[i] == NULL)
        {
            // To do: Update
            printSyntaxHelper();
            return -1;
        }
    }

    // Convert command line argumnets from strings to doubles.
    tunnel_number = strtod(argv[1], &eptr);
    diameter = strtod(argv[2], &eptr);
    height = strtod(argv[3], &eptr);
    noseConeRatio = strtod(argv[4], &eptr);

    // To do: Update to handle storing data in new struct definiton. 
    // Done
    mesh = createWindTunnel(tunnel_number, diameter, height, noseConeRatio);

    if (mesh == NULL)
    {
        printf("Error: mesh == NULL");
        return -2;
    }

    blockMeshDict = fopen("blockMeshDict", "w");
    
    // To do: N/A
    printHeader(blockMeshDict);
    // To do: must be compatible with changes in createWindTunnel 
    // Done.
    printParameters(blockMeshDict, mesh);
    // To do: update verticies
    // Done
    printVertices(blockMeshDict);
    // To do: update blocks
    printHexBlocks(blockMeshDict);
    // To do: must be compatible with changes in createWindTunnel 
    printEdges(blockMeshDict, mesh);
    // To do: update patches
    printPatches(blockMeshDict);
    // To do: N/A
    printPatchPairs(blockMeshDict);

    // To do: N/A
    printFooter(blockMeshDict);

    fclose(blockMeshDict);
    free(mesh);
    return 0;
}


// Here in case future self has a need for a bunch of fputs statements
// Please copy, do not delete. 

// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);
// fputs("\n", blockMeshDict);