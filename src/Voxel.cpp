#include "Voxel.h"

float randomFloat(float low, float high) {
    return low + static_cast<float>(rand()) * (high - low) / RAND_MAX;
}

MarchingCubes::MarchingCubes(int X, int Y, int Z){
    srand(time(0));

    voxelData = new float[X * Y * Z]();

    size_x = X;
    size_y = Y;
    size_z = Z;

    size_xz = X*Z;

    for(int i = 0; i < X*Y*Z; i++){
        voxelData[i] = -1;
    }

    for(int z = 1; z < Z - 2; z++){
        for(int y = 1; y < Y - 2; y++){
            for(int x = 1; x < X - 2; x++){
                voxelData[x + (y*size_x) + (z*size_x*size_y)] =  -std::sqrt(((z -4) * (z -4)) + ((y -4) * (y -4)) + ((x -4) * (x -4)))/3; //randomFloat(-1.0f,1.0f);
            }
        }
    }
}

MarchingCubes::~MarchingCubes(){
    delete[] voxelData;
}

/*
      y
      |
      4------5
     /|     /|
    7------6 |
    | |    | |
    | 0----|-1 --> x
    |/     |/
    3------2
   /
  z
*/

glm::vec3 MarchingCubes::interpolate(glm::vec3 p0, glm::vec3 p1, float v0, float v1){
    float t = (surfaceCutoff - v0)/(v1-v0);
    return (t * (p1 - p0)) + p0;
}   

void MarchingCubes::generate(){
    vertexData.clear();
    indexData.clear();
    
    for(int y = 0; y < size_y-2; y++){
        for(int z = 0; z < size_z-2; z++){
            for(int x = 0; x < size_x-2; x++){
                
                int index = x + (z*size_x) + (y*size_x*size_z);

                float currentVerticies[8] = {
                    voxelData[index],
                    voxelData[index + 1],
                    voxelData[index + size_x + 1],
                    voxelData[index + size_x],
                    voxelData[index + size_xz],
                    voxelData[index + size_xz + 1],
                    voxelData[index + size_xz + size_x + 1],
                    voxelData[index + size_xz + size_x]
                };

                int config = 0;
                for (int i = 0; i < 8; i++) {
                    //std::cout << currentVerticies[i] << "\n";
                    if (currentVerticies[i] > surfaceCutoff) {
                        config |= (1 << i);
                    }
                }

                glm::vec3 tempVertBuffer[12];

                for(int i = 0; i < 12; i++){
                    if (edgeTable[config] & (1 << i)) {
                        std::pair<int, int> currentEdge = edgeToVertices[i];
                        tempVertBuffer[i] = interpolate(vertexPositions[currentEdge.first], 
                                                        vertexPositions[currentEdge.second],
                                                        currentVerticies[currentEdge.first], 
                                                        currentVerticies[currentEdge.second]);
                    }
                }
                   
                for(int i = 0; i < 15;i += 3){
                    int a = triangleTable[config][i];

                    if(a != -1){
                        int b = triangleTable[config][i + 1];
                        int c = triangleTable[config][i + 2];
                        
                        addTriangle(tempVertBuffer[a], tempVertBuffer[b], tempVertBuffer[c],glm::vec3(x,y,z));
                    }else{
                        break;
                    }
                }
            }
        }
    }
}

void MarchingCubes::addTriangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 offset){
    int lengthOfVerticies = vertexData.size()/8;

    p0 += offset;
    p1 += offset;
    p2 += offset;

    indexData.push_back(lengthOfVerticies);
    indexData.push_back(lengthOfVerticies + 1);
    indexData.push_back(lengthOfVerticies + 2);

    // 3f , 3f , 2f
    //vert,norm,tex

    glm::vec3 edge1 = p1 - p0;
    glm::vec3 edge2 = p2 - p0;

    glm::vec3 normal = glm::cross(edge1, edge2);
    
    //vertex 1
    vertexData.push_back(p0.x);
    vertexData.push_back(p0.y);
    vertexData.push_back(p0.z);

    vertexData.push_back(normal.x);
    vertexData.push_back(normal.y);
    vertexData.push_back(normal.z);

    vertexData.push_back(0.0f);
    vertexData.push_back(0.0f);

    //vertex 2
    vertexData.push_back(p1.x);
    vertexData.push_back(p1.y);
    vertexData.push_back(p1.z);

    vertexData.push_back(normal.x);
    vertexData.push_back(normal.y);
    vertexData.push_back(normal.z);

    vertexData.push_back(1.0f);
    vertexData.push_back(0.0f);

    //vertex 3
    vertexData.push_back(p2.x);
    vertexData.push_back(p2.y);
    vertexData.push_back(p2.z);

    vertexData.push_back(normal.x);
    vertexData.push_back(normal.y);
    vertexData.push_back(normal.z);

    vertexData.push_back(0.0f);
    vertexData.push_back(1.0f);
}   