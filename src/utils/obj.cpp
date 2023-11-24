#include "../headers/gamepch.h"

OBJ::OBJ(std::string text) : mGeometry(nullptr)
{
    mFunctions["v"] = new OBJ_V(this);
    mFunctions["vn"] = new OBJ_VN(this);
    mFunctions["vt"] = new OBJ_VT(this);
    mFunctions["f"] = new OBJ_F(this);
    mFunctions["s"] = new OBJ_S(this);
    mFunctions["g"] = new OBJ_G(this);
    mFunctions["o"] = new OBJ_O(this);
    mFunctions["mtllib"] = new OBJ_mtllib(this);
    mFunctions["usemtl"] = new OBJ_usemtl(this);

    bool success = init(text);
}

OBJ::~OBJ()
{
    for (auto geo : mGeometries)
    {
        delete geo;
    }

    std::map<std::string, OBJ_Function *>::iterator it;

    for (it = mFunctions.begin(); it != mFunctions.end(); it++)
    {
        delete it->second;
    }

    mFunctions.clear();
}

bool OBJ::init(std::string loc)
{

    std::string text;
    std::string fileLine;
    std::ifstream file(loc.c_str());

    if (file.is_open())
    {
        while (getline(file, fileLine))
        {
            text += fileLine + '\n';
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open the OBJ file." << std::endl;
        return false;
    }

    auto const regex = std::regex("(\\w*)(?: )*(.*)");
    std::vector<std::string> lines = Utils::splitString(text, '\n');

    for (int lineNo = 0; lineNo < lines.size(); lineNo++)
    {
        std::string line = lines[lineNo];

        if (line == "" || line[0] == '#')
        {
            continue;
        }

        auto searchedResult = std::smatch();
        bool m = std::regex_search(line, searchedResult, regex);

        if (!m)
            continue;

        std::vector<std::string> parts = Utils::splitString(line, std::string(" "));
        parts.erase(parts.begin());

        std::string keyword = searchedResult[1];
        std::string unparsed_args = searchedResult[2];

        if (!mFunctions.count(keyword))
        {
            std::cout << "Handler not defined for keyword: " << keyword << std::endl;
            continue;
        }

        OBJ_Function *handler = mFunctions[keyword];

        if (handler)
            handler->execute(parts, unparsed_args);
    }

    return true;
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

void OBJ_V::execute(std::vector<std::string> parts, std::string unparsed_args)
{
    std::vector<float> positions;
    std::vector<float> colors;

    if (parts.size() > 3)
    {
        for (int i = 0; i < 3; i++)
        {
            // std::cout << parts[i] << std::endl;
            positions.push_back(std::stof(parts[i]));
            colors.push_back(std::stof(parts[i + 3]));
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            positions.push_back(std::stof(parts[i]));
        }
    }

    if (colors.size())
    {
        mOBJ->mObjColors.push_back(colors);
    }

    mOBJ->mObjPositions.push_back(positions);
}

void OBJ_VN::execute(std::vector<std::string> parts, std::string unparsed_args)
{
    std::vector<float> normals;

    for (int i = 0; i < 3; i++)
    {
        // std::cout << parts[i] << std::endl;
        normals.push_back(std::stof(parts[i]));
    }

    mOBJ->mObjNormals.push_back(normals);
}

void OBJ_VT::execute(std::vector<std::string> parts, std::string unparsed_args)
{
    std::vector<float> texcoords;

    for (int i = 0; i < parts.size(); i++)
    {
        // std::cout << parts[i] << std::endl;
        texcoords.push_back(std::stof(parts[i]));
    }

    mOBJ->mObjTexCoords.push_back(texcoords);
}

void OBJ_F::execute(std::vector<std::string> parts, std::string unparsed_args)
{
    // mOBJ->setGeometry();
    int numTriangles = parts.size() - 2;

    for (auto part : parts)
    {
        std::cout << part << std::endl;
    }
    std::cout << std::endl;

    for (int tri = 0; tri < numTriangles; ++tri)
    {

        // mOBJ->addVertex(parts[0]);
        // mOBJ->addVertex(parts[tri + 1]);
        // mOBJ->addVertex(parts[tri + 2]);
    }
}

void OBJ_S::execute(std::vector<std::string> parts, std::string unparsed_args)
{
}

void OBJ_G::execute(std::vector<std::string> parts, std::string unparsed_args)
{
    mOBJ->mGroups = parts;
    mOBJ->newGeometry();
}

void OBJ_O::execute(std::vector<std::string> parts, std::string unparsed_args)
{
    mOBJ->mObject = unparsed_args;
    mOBJ->newGeometry();
}

void OBJ_mtllib::execute(std::vector<std::string> parts, std::string unparsed_args)
{
    mOBJ->mMaterialLibs.push_back(unparsed_args);
}

void OBJ_usemtl::execute(std::vector<std::string> parts, std::string unparsed_args)
{
    mOBJ->mMaterial = unparsed_args;
    mOBJ->newGeometry();
}