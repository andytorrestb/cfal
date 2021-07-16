gcc -lm cavityMeshDict.c -o cavityMeshDict
mv cavityMeshDict case/system
cd case/system
./cavityMeshDict 3 1 1 10
cd ..
blockMesh