#include "../headers/gamepch.h"

OBJ::OBJ(std::string text) : mGeometry(nullptr)
{
}

OBJ::~OBJ()
{
    for (auto geo : mGeometries)
    {
        delete geo;
    }
}

void OBJ::newGeometry()
{
    if (mGeometry && mGeometry->mData.mPosition.size())
    {
        mGeometry = nullptr;
    }
}

void OBJ::setGeometry()
{
    if (!mGeometry)
    {
        std::vector<float> position;
        std::vector<float> texcoord;
        std::vector<float> normal;
        std::vector<float> color;

        mGLVertexData[0].push_back(position); // *
        mGLVertexData[0].push_back(texcoord);
        mGLVertexData[0].push_back(normal);
        mGLVertexData[0].push_back(color);

        mGeometry = new OBJ_Geometry{
            mObject,
            mGroups,
            mMaterial,
            OBJ_Geometry_data{
                position,
                texcoord,
                normal,
                color}};

        mGeometries.push_back(mGeometry);
    }
}

void OBJ::addVertex(std::string vert)
{
    std::vector<std::string> ptn = Utils::splitString(vert, '/');

    for (int i = 0; i < ptn.size(); i++)
    {
        std::string objIndexStr = ptn[i];

        if (objIndexStr == "")
        {
            return;
        }

        int objIndex = std::stoi(objIndexStr);

        int index = objIndex + (objIndex >= 0 ? 0 : mObjVertexdata[i].size()); //*

        mGLVertexData[i].push_back(mObjVertexdata[i][index]);

        if (i == 0 && mObjColors.size() > 1)
        {
            mGeometry->mData.mColor = mObjColors[index]; // *
        }
    }
}