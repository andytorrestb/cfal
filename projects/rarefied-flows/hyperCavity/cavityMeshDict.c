//                                    Andy Torres
//                               CFAL@UCF, Spring 2021

//                                  cavityMeshDict
//                                 =================
//
// Generates blockMeshDict file required for a 2D simulation of external flow around a cavity of different configurations.
// These configurations are based on the following parameters. 
//          1. L := L/D := length to ddepth ratio
//          2. R := R/F := rear to forward wall height ratio
//          3. theta := forward inclination angle.

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

// Command line constants
#define NUM_ARGS 4

// Error Constants
#define NULL_POINTER_ERR -10000000

// Stores dimensional parameters for cavity
typedef struct Cavity
{
    double L;
    double R;
    double theta;
    int grading;
} Cavity;

// Stores data to parametrize blockMesh. 
typedef struct FlowDomain
{
    float x0;
    float x1;
    float x2;
    float x3;
    float x4;

    float y0;
    float y1;
    float y2;

    int g;
    int g_2;
    int g_l;

    Cavity *cavity;
} FlowDomain;

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

// Writes constants used as reference for coordinates. 
void printParameters(FILE *blockMeshDict, FlowDomain *mesh)
{
    // (TODO ?): update scale according to user input)
    // Default everything to the mm scale.
    fprintf(blockMeshDict, "scale   %1.1e;\n\n", 0.001);

    // Print coordinate constants.
    fprintf(blockMeshDict, "// From diagram.\n");
    fprintf(blockMeshDict, "x_0 %f;\n", mesh->x0);
    fprintf(blockMeshDict, "x_1 %f;\n", mesh->x1);
    fprintf(blockMeshDict, "x_2 %f;\n", mesh->x2);
    fprintf(blockMeshDict, "x_3 %f;\n\n", mesh->x3);
    fprintf(blockMeshDict, "x_4 %f;\n\n", mesh->x4);

    fprintf(blockMeshDict, "y_0 %f;\n", mesh->y0);
    fprintf(blockMeshDict, "y_1 %f;\n", mesh->y1);
    fprintf(blockMeshDict, "y_2 %f;\n", mesh->y2);
    
    fprintf(blockMeshDict, "zmin 0;\n");
    fprintf(blockMeshDict, "zmax 0.05;\n\n");

    // Print grading constants.
    fprintf(blockMeshDict, "g %d;\n", mesh->g);
    fprintf(blockMeshDict, "g_2 %d;\n", mesh->g_2);
    fprintf(blockMeshDict, "g_l %d;\n", mesh->g_l);

    return;
}

// Produces vertices required according to constants printed in printParameters.
void printVertices(FILE *blockMeshDict)
{

    fputs("vertices\n", blockMeshDict);
    fputs("(\n", blockMeshDict);
    
    // block 0
    fputs("    // block 0\n", blockMeshDict);
    fputs("    ($x_0 $y_1 $zmin) // 0\n", blockMeshDict);
    fputs("    ($x_1 $y_1 $zmin) // 1\n", blockMeshDict);
    fputs("    ($x_1 $y_2 $zmin) // 2\n", blockMeshDict);
    fputs("    ($x_0 $y_2 $zmin) // 3\n\n", blockMeshDict);

    fputs("    ($x_0 $y_1 $zmax) // 4\n", blockMeshDict);
    fputs("    ($x_1 $y_1 $zmax) // 5\n", blockMeshDict);
    fputs("    ($x_1 $y_2 $zmax) // 6\n", blockMeshDict);
    fputs("    ($x_0 $y_2 $zmax) // 7\n\n", blockMeshDict);

    // block 1
    fputs("    // block 1 (extra needed)\n", blockMeshDict);
    fputs("    ($x_3 $y_1 $zmin) // 8\n", blockMeshDict);
    fputs("    ($x_3 $y_2 $zmin) // 9\n", blockMeshDict);

    fputs("    ($x_3 $y_1 $zmax) // 10\n", blockMeshDict);
    fputs("    ($x_3 $y_2 $zmax) // 11\n\n", blockMeshDict);

    // block 2
    fputs("    // block 2 (extra needed)\n", blockMeshDict);
    fputs("    ($x_4 $y_1 $zmin) // 12\n", blockMeshDict);
    fputs("    ($x_4 $y_2 $zmin) // 13\n", blockMeshDict);

    fputs("    ($x_4 $y_1 $zmax) // 14\n", blockMeshDict);
    fputs("    ($x_4 $y_2 $zmax) // 15\n\n", blockMeshDict);

    // block 3
    fputs("    // block 3 (extra needed)\n", blockMeshDict);
    fputs("    ($x_2 $y_0 $zmin) // 16\n", blockMeshDict);
    fputs("    ($x_3 $y_0 $zmin) // 17\n", blockMeshDict);

    fputs("    ($x_2 $y_0 $zmax) // 18\n", blockMeshDict);
    fputs("    ($x_3 $y_0 $zmax) // 19\n", blockMeshDict);

    fputs(");\n\n", blockMeshDict);

    return;
}

void printHexBlocks(FILE *blockMeshDict)
{
    fputs("blocks\n", blockMeshDict);
    fputs("(\n", blockMeshDict);
    fputs("    hex (0 1 2 3 4 5 6 7) ($g $g_2 1) simpleGrading (1 1 1) // 0\n", blockMeshDict);
    fputs("    hex (1 8 9 2 5 10 11 6) ($g_l $g_2 1) simpleGrading (1 1 1) // 1\n", blockMeshDict);
    fputs("    hex (8 12 13 9 10 14 15 11) ($g $g_2 1) simpleGrading (1 1 1) // 2\n", blockMeshDict);
    fputs("    hex (16 17 8 1 18 19 10 5) ($g_l $g 1) simpleGrading (1 1 1) // 3\n", blockMeshDict);
    fputs(");\n\n", blockMeshDict);
    return;
}

// TODO: update
void printPatches(FILE *blockMeshDict)
{
    fputs("boundary\n", blockMeshDict);
    fputs("(\n", blockMeshDict);

    // inlet patch
    fputs("    inlet\n", blockMeshDict);
    fputs("    {\n", blockMeshDict);
    fputs("        type patch;\n", blockMeshDict);
    fputs("        faces\n", blockMeshDict);
    fputs("        (\n", blockMeshDict);

    fputs("            // Front of tunnel\n", blockMeshDict);
    fputs("            (4 7 3 0)\n", blockMeshDict);

    fputs("        );\n", blockMeshDict);
    fputs("    }\n\n", blockMeshDict);

    // outlet patch
    fputs("    outlet\n", blockMeshDict);
    fputs("    {\n", blockMeshDict);
    fputs("        type patch;\n", blockMeshDict);
    fputs("        faces\n", blockMeshDict);
    fputs("        (\n", blockMeshDict);

    fputs("            // Back of tunnel\n", blockMeshDict);
    fputs("            (14 12 13 15)\n", blockMeshDict);

    fputs("            // Top of tunnel\n", blockMeshDict);
    fputs("            (6 2 3 7)\n", blockMeshDict);
    fputs("            (11 9 2 6)\n", blockMeshDict);
    fputs("            (15 13 9 11)\n", blockMeshDict);


    // add top of tunnel ? (3 faces)

    fputs("        );\n", blockMeshDict);
    fputs("    }\n\n", blockMeshDict);

    // wall patch
    fputs("    wall\n", blockMeshDict);
    fputs("    {\n", blockMeshDict);
    fputs("        type patch;\n", blockMeshDict);
    fputs("        faces\n", blockMeshDict);
    fputs("        (\n", blockMeshDict);

    fputs("            // leading floor\n", blockMeshDict);
    fputs("            (4 0 1 5)\n", blockMeshDict);

    fputs("            // leading wall\n", blockMeshDict);
    fputs("            (5 1 16 18)\n", blockMeshDict);

    fputs("            // cavity floor\n", blockMeshDict);
    fputs("            (18 16 17 19)\n", blockMeshDict);

    fputs("            // trailing wall\n", blockMeshDict);
    fputs("            (8 10 19 17)\n", blockMeshDict);

    fputs("            // trailing floor\n", blockMeshDict);
    fputs("            (10 8 14 12)\n", blockMeshDict);

    fputs("        );\n", blockMeshDict);
    fputs("    }\n\n", blockMeshDict);

    // frontAndBack patch
    fputs("    frontAndBack\n", blockMeshDict);
    fputs("    {\n", blockMeshDict);
    fputs("        type empty;\n", blockMeshDict);
    fputs("        faces\n", blockMeshDict);
    fputs("        (\n", blockMeshDict);

    fputs("            (3 2 1 0)\n", blockMeshDict);
    fputs("            (2 9 8 1)\n", blockMeshDict);
    fputs("            (9 13 12 8)\n", blockMeshDict);
    fputs("            (1 8 17 16)\n", blockMeshDict);

    fputs("            (6 7 4 5)\n", blockMeshDict);
    fputs("            (11 6 5 10)\n", blockMeshDict);
    fputs("            (15 11 10 14)\n", blockMeshDict);
    fputs("            (5 18 19 10)\n", blockMeshDict);

    fputs("        );\n", blockMeshDict);
    fputs("    }\n\n", blockMeshDict);
 

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

// Sets up Cavity struct.
Cavity *createCavity(double L, double R, double theta, int grading)
{
    Cavity *cavity = calloc(1, sizeof(Cavity));
    cavity->L = L;
    cavity->R = R;
    cavity->theta = theta;
    cavity->grading = grading;
    return cavity;
}

// Sets coordinates for creatings FlowDomain according to values stored in Cavity struct
void setCoordinates(FlowDomain *mesh)
{
    Cavity *cavity = mesh->cavity;
    double L = cavity->L;
    double R = cavity->R;
    double theta = cavity->theta;

    // Depth of channel
    double D = 10.0;
    
    mesh->x0 = 0;
    mesh->y0 = 0;

    mesh->x1 = D;
    mesh->y1 = D;

    mesh->x2 = D * (1 + 1 / tan(theta));
    mesh->y2 = 3 * D;


    mesh->x3 = D * (1 + 1 / tan(theta) + L);
    mesh->x4 = D * (2 + 1 / tan(theta) + L);

    return;
}

void setGrading(FlowDomain *mesh)
{
    int grading = mesh->cavity->grading;

    mesh->g = grading;
    mesh->g_2 = 2 * grading;
    mesh->g_l = mesh->cavity->L * grading;

    return;
}

int validCavity(Cavity *cavity)
{
    return (cavity == NULL) ? 0 : 1;
}

// Sets up FlowDomain struct.
FlowDomain *createFlowDomain(Cavity *cavity)
{   
    FlowDomain *d = calloc(1, sizeof(FlowDomain));

    if (!validCavity(cavity))
    {
        printf("Invalid cavity\n");
        return NULL;
    }

    if (d == NULL)
    {
        return NULL;
    }

    d->cavity = cavity;

    setCoordinates(d);
    setGrading(d);

    return d;
}

void printSyntaxHelper()
{
    printf("\n          Seems like you've entered the wrong syntax.\n");
    printf("       Try running the program with the following flags\n");
    printf("      $ ./CavityMeshDict <L> <R> <theta>\n\n");
}

void printToFile(FILE *blockMeshDict, FlowDomain *mesh)
{
    // To do: N/A
    printHeader(blockMeshDict);
    // To do: must be compatible with changes in createFlowDomain 
    // Done.
    printParameters(blockMeshDict, mesh);
    // To do: update verticies
    // Done
    printVertices(blockMeshDict);
    // To do: update blocks
    printHexBlocks(blockMeshDict);
    // To do: update patches
    printPatches(blockMeshDict);
    // To do: N/A
    printPatchPairs(blockMeshDict);
    // To do: N/A
    printFooter(blockMeshDict);

    return;
}

int main(int argc, char **argv)
{
    int i;
    double L, R, theta;
    int grading;
    char *eptr; // needed for strtod();
    Cavity *cavity;
    FlowDomain *mesh;
    FILE *blockMeshDict;

    // Check that user used proper syntax when running the program.
    for (i = 1; i <= NUM_ARGS; i++)
    {
        if (argv[i] == NULL)
        {
            // TODO: Update
            printSyntaxHelper();
            return -1;
        }
    }

    // Convert command line argumnets from strings to numbers.
    L = strtod(argv[1], &eptr);
    R = strtod(argv[2], &eptr);
    theta = strtod(argv[3], &eptr);
    grading = atoi(argv[4]);

    // Build necessary structs for customizing blockMeshDict.
    cavity = createCavity(L, R, theta, grading);
    mesh = createFlowDomain(cavity);

    if (mesh == NULL)
    {
        printf("Error: mesh == NULL");
        return -2;
    }

    // Print required contents for blockMeshDict 
    blockMeshDict = fopen("blockMeshDict", "w");
    printToFile(blockMeshDict, mesh);
    fclose(blockMeshDict);
    free(mesh);

    printf("Success, process exited with code: 0\n");
    return 0;
}