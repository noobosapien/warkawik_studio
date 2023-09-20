#ifndef OBJ_H
#define OBJ_H

struct OBJ_Geometry_data
{
    std::vector<float> mPosition;
    std::vector<float> mTexCoord;
    std::vector<float> mNormal;
    std::vector<float> mColor;
};

struct OBJ_Geometry
{
    std::string mObject;
    std::vector<std::string> mGroups;
    std::string mMaterial;

    OBJ_Geometry_data mData;
};

class OBJ
{
public:
    OBJ(std::string text);
    ~OBJ();

    void newGeometry();
    void setGeometry();
    void addVertex(std::string vert);

private:
    std::vector<std::vector<float>> mObjPositions;
    std::vector<std::vector<float>> mObjTexCoords;
    std::vector<std::vector<float>> mObjNormals;
    std::vector<std::vector<float>> mObjColors;

    std::vector<std::vector<std::vector<float>>> mObjVertexdata;

    // std::vector<std::vector<float>> mVertexData;
    std::vector<std::vector<std::vector<float>>> mGLVertexData;

    std::vector<std::string> mMaterialLibs;
    std::vector<std::string> mGroups;
    std::string mMaterial;
    std::string mObject;

    std::vector<OBJ_Geometry *> mGeometries;
    OBJ_Geometry *mGeometry;
};

#endif