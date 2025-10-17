#include "Voxel.h"

MarchingCubes::MarchingCubes(int X, int Y, int Z){
    voxelData = new int[X * Y * Z]
    
    size_x = X;
    size_y = Y;
    size_z = Z;

    size_xy = x*y;
}

MarchingCubes::~MarchingCubes(){
    delete voxelData;
}

int MarchingCubes::voxelAt(int index){
    return voxelData[index]
}


/*
       z
       |
       6------7
      /|     /|
     4------5 |
     | |    | |
     | 2----|-3 --> x
     |/     |/
     0------1
    /
   -y (negative y)
*/

void MarchingCubes::calculateConfiguration(int index, int& config){
    int v0 = voxelData[index];
    int v1 = voxelData[index + 1];
    int v2 = voxelData[index + size_x];
    int v3 = voxelData[index + 1 + size_x];
    int v4 = voxelData[index + size_xy ];
    int v5 = voxelData[index + size_xy + 1];
    int v6 = voxelData[index + size_xy + size_x];
    int v7 = voxelData[index + size_xy + 1 + size_x]; //triangle of doom?

    config = ((v0 > 0) << 0) | ((v1 > 0) << 1) | ((v2 > 0) << 2) | ((v3 > 0) << 3) | ((v4 > 0) << 4) | ((v5 > 0) << 5) | ((v6 > 0) << 6) | ((v7 > 0) << 7);
}

void MarchingCubes::generate(){
    meshData.clear();
    
    int index = 0;
    
    for(int z = 0; z < size_z-2; i++){
        for(int y = 0; y < size_y-2; i++){
            for(int x = 0; x < size_x-2; i++){
                
                int configuration;

                calculateConfiguration(index, configuration);

                for(int i = 0; i < 15;i += 3){
                    int a = triangleTable[configuration][i]

                    if(a != -1){
                        int b = triangleTable[configuration][i + 1]
                        int c = triangleTable[configuration][i + 2]

                        indexData.push_back(a);
                        indexData.push_back(b);
                        indexData.push_back(c);

                        

                    }else{
                        break;
                    }
                }

                index ++
            }
        }
    }
}