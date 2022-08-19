#ifndef LIGHTING_TECHNIQUE_17_H
#define LIGHTING_TECHNIQUE_17_H

#include "technique.h"
#include "ogldev_math_3d.h"
#include "ogldev_material.h"
#include "ogldev_world_transform.h"

class BaseLight
{
public:
    Vector3f Color = Vector3f(1.0f, 1.0f, 1.0f);
    float AmbientIntensity = 0.7f;
    float DiffuseIntensity = 1.0f;
};


class DirectionalLight : public BaseLight
{
public:
    Vector3f WorldDirection = Vector3f(0.0f, 0.0f, 0.0f);

    void CalcLocalDirection(const Matrix4f& World);

    const Vector3f& GetLocalDirection() const { return LocalDirection; }

private:
    Vector3f LocalDirection = Vector3f(0.0f, 0.0f, 0.0f);
};

struct LightAttenuation
{
    float Constant = 1.0f;
    float Linear = 0.0f;
    float Exp = 0.0f;
};


class PointLight : public BaseLight
{
public:
    Vector3f WorldPosition = Vector3f(0.0f, 0.0f, 0.0f);
    LightAttenuation Attenuation;

    void CalcLocalPosition(const WorldTrans& worldTransform);

    const Vector3f& GetLocalPosition() const { return LocalPosition; }

private:
    Vector3f LocalPosition = Vector3f(0.0f, 0.0f, 0.0f);
};


class LightingTechnique : public Technique
{
public:

    static const unsigned int MAX_POINT_LIGHTS = 2;

    LightingTechnique();

    virtual bool Init();

    void SetWVP(const Matrix4f& WVP);
    void SetTextureUnit(unsigned int TextureUnit);
    void SetSpecularExponentTextureUnit(unsigned int TextureUnit);
    void SetDirectionalLight(const DirectionalLight& Light);
    void SetPointLights(unsigned int NumLights, const PointLight* pLights);
    void SetCameraLocalPos(const Vector3f& CameraLocalPos);
    void SetMaterial(const Material& material);

private:

    GLuint WVPLoc;
    GLuint samplerLoc;
    GLuint samplerSpecularExponentLoc;
    GLuint CameraLocalPosLoc;
    GLuint NumPointLightsLocation;

    struct {
        GLuint AmbientColor;
        GLuint DiffuseColor;
        GLuint SpecularColor;
    } materialLoc;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Direction;
        GLuint DiffuseIntensity;
    } dirLightLoc;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Position;
        GLuint DiffuseIntensity;

        struct
        {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } PointLightsLocation[MAX_POINT_LIGHTS];
};


#endif  /* LIGHTING_TECHNIQUE_H */
