xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Line {
 <00e4d09b-7fb7-4e48-838b-eb3a6d452db4>
 DWORD start;
 DWORD end;
}

template Wire {
 <f562f616-410d-44d8-a1ff-2adfb722f4dd>
 DWORD nVerticies;
 array Vector verticies[nVerticies];
 DWORD nLines;
 array Line lines[nLines];
 [...]
}


Frame Frame_SCENE_ROOT {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame Frame1_wire_test {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Mesh Mesh_wire_test {
   24;
   1.095238;-0.571429;-1.904762;,
   1.095238;-0.571429;-1.904762;,
   1.095238;-0.571429;-1.904762;,
   1.936508;-0.571429;-1.904762;,
   1.936508;-0.571429;-1.904762;,
   1.936508;-0.571429;-1.904762;,
   1.936508;-0.571429;-1.238095;,
   1.936508;-0.571429;-1.238095;,
   1.936508;-0.571429;-1.238095;,
   1.095238;-0.571429;-1.238095;,
   1.095238;-0.571429;-1.238095;,
   1.095238;-0.571429;-1.238095;,
   1.095238;0.555556;-1.904762;,
   1.095238;0.555556;-1.904762;,
   1.095238;0.555556;-1.904762;,
   1.936508;0.555556;-1.904762;,
   1.936508;0.555556;-1.904762;,
   1.936508;0.555556;-1.904762;,
   1.936508;0.555556;-1.238095;,
   1.936508;0.555556;-1.238095;,
   1.936508;0.555556;-1.238095;,
   1.095238;0.555556;-1.238095;,
   1.095238;0.555556;-1.238095;,
   1.095238;0.555556;-1.238095;;
   6;
   4;0,12,15,3;,
   4;4,16,18,6;,
   4;9,7,19,21;,
   4;1,10,22,13;,
   4;14,23,20,17;,
   4;2,5,8,11;;

   MeshNormals {
    24;
    0.000000;0.000000;-1.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;;
    6;
    4;0,12,15,3;,
    4;4,16,18,6;,
    4;9,7,19,21;,
    4;1,10,22,13;,
    4;14,23,20,17;,
    4;2,5,8,11;;
   }

   MeshTextureCoords {
    24;
    0.826536;0.816857;,
    0.826536;0.816857;,
    0.826536;0.816857;,
    0.795668;0.740731;,
    0.795668;0.740731;,
    0.795668;0.740731;,
    0.795668;0.675093;,
    0.795668;0.675093;,
    0.795668;0.675093;,
    0.826536;0.750354;,
    0.826536;0.750354;,
    0.826536;0.750354;,
    0.675288;0.817713;,
    0.675288;0.817713;,
    0.675288;0.817713;,
    0.705535;0.741080;,
    0.705535;0.741080;,
    0.705535;0.741080;,
    0.705535;0.675406;,
    0.705535;0.675406;,
    0.705535;0.675406;,
    0.675288;0.751292;,
    0.675288;0.751292;,
    0.675288;0.751292;;
   }

   VertexDuplicationIndices {
    24;
    22;
    0,
    0,
    0,
    3,
    3,
    3,
    6,
    6,
    6,
    9,
    9,
    9,
    12,
    12,
    12,
    15,
    15,
    15,
    18,
    18,
    18,
    21,
    21,
    21;
   }

   MeshMaterialList {
    2;
    6;
    1,
    1,
    1,
    1,
    1,
    1;

    Material {
     0.941176;0.000000;0.023529;1.000000;;
     51.200001;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;
    }

    Material {
     1.000000;1.000000;1.000000;1.000000;;
     51.200001;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "Reflect.tga";
     }
    }
   }
  }

  Wire Wire_wire_test {
   8;
   -0.380017;0.345507;-0.297281;,
   0.370273;0.345507;-0.297281;,
   0.370273;0.345507;0.300353;,
   -0.380017;0.345507;0.300353;,
   -0.380017;1.176997;-0.297281;,
   0.370273;1.176997;-0.297281;,
   0.370273;1.176997;0.300353;,
   -0.380017;1.176997;0.300353;;
   12;
   0;1;,
   3;2;,
   0;3;,
   1;2;,
   0;4;,
   1;5;,
   4;5;,
   2;6;,
   5;6;,
   7;6;,
   3;7;,
   4;7;;

   MeshTextureCoords {
    8;
    0.000000;1.000000;,
    0.000000;1.000000;,
    0.000000;1.000000;,
    0.000000;1.000000;,
    0.000000;1.000000;,
    0.000000;1.000000;,
    0.000000;1.000000;,
    0.000000;1.000000;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material {
     0.941176;0.000000;0.023529;1.000000;;
     51.200001;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;
    }
   }
  }
 }
}