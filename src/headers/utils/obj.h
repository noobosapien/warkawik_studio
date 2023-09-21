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

struct OBJ_Function
{
    OBJ_Function(class OBJ *obj) : mOBJ(obj) {}
    virtual ~OBJ_Function() {}

    virtual void execute(std::vector<std::string> parts, std::string unparsed_args = "") = 0;

protected:
    class OBJ *mOBJ;
};

struct OBJ_V : public OBJ_Function
{
    OBJ_V(class OBJ *obj) : OBJ_Function(obj) {}
    virtual ~OBJ_V() override {}

    virtual void execute(std::vector<std::string> parts, std::string unparsed_args = "") override;
};

struct OBJ_VN : public OBJ_Function
{
    OBJ_VN(class OBJ *obj) : OBJ_Function(obj) {}
    virtual ~OBJ_VN() override {}

    virtual void execute(std::vector<std::string> parts, std::string unparsed_args = "") override;
};

struct OBJ_VT : public OBJ_Function
{
    OBJ_VT(class OBJ *obj) : OBJ_Function(obj) {}
    virtual ~OBJ_VT() override {}

    virtual void execute(std::vector<std::string> parts, std::string unparsed_args = "") override;
};

struct OBJ_F : public OBJ_Function
{
    OBJ_F(class OBJ *obj) : OBJ_Function(obj) {}
    virtual ~OBJ_F() override {}

    virtual void execute(std::vector<std::string> parts, std::string unparsed_args = "") override;
};

struct OBJ_S : public OBJ_Function
{
    OBJ_S(class OBJ *obj) : OBJ_Function(obj) {}
    virtual ~OBJ_S() override {}

    virtual void execute(std::vector<std::string> parts, std::string unparsed_args = "") override;
};

struct OBJ_G : public OBJ_Function
{
    OBJ_G(class OBJ *obj) : OBJ_Function(obj) {}
    virtual ~OBJ_G() override {}

    virtual void execute(std::vector<std::string> parts, std::string unparsed_args = "") override;
};

struct OBJ_O : public OBJ_Function
{
    OBJ_O(class OBJ *obj) : OBJ_Function(obj) {}
    virtual ~OBJ_O() override {}

    virtual void execute(std::vector<std::string> parts, std::string unparsed_args = "") override;
};

struct OBJ_mtllib : public OBJ_Function
{
    OBJ_mtllib(class OBJ *obj) : OBJ_Function(obj) {}
    virtual ~OBJ_mtllib() override {}

    virtual void execute(std::vector<std::string> parts, std::string unparsed_args = "") override;
};

struct OBJ_usemtl : public OBJ_Function
{
    OBJ_usemtl(class OBJ *obj) : OBJ_Function(obj) {}
    virtual ~OBJ_usemtl() override {}

    virtual void execute(std::vector<std::string> parts, std::string unparsed_args = "") override;
};

class OBJ
{
public:
    OBJ(std::string text);
    ~OBJ();

    void newGeometry();
    void setGeometry();
    void addVertex(std::string vert);

    friend struct OBJ_Function; // this is enough
    friend struct OBJ_V;        // bs I don wan to do this man
    friend struct OBJ_VN;
    friend struct OBJ_VT;
    friend struct OBJ_F;
    friend struct OBJ_S;
    friend struct OBJ_G;
    friend struct OBJ_O;

    friend struct OBJ_mtllib;
    friend struct OBJ_usemtl;

private:
    bool init(std::string loc);

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

    std::map<std::string, OBJ_Function *> mFunctions;
};

#endif