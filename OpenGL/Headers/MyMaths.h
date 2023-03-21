#pragma once
#pragma once
#pragma once
#include <cmath>
#include <string>
#include <iostream>
#include <vector>


constexpr auto MY_PI = 3.14159265358979323846;
#define DEG2RAD MY_PI / 180.0f
#define RAD2DEG 180.0f / MY_PI


//==============================================================================================================
//                  VECTOR 2
//==============================================================================================================

namespace Core
{
    namespace Maths
    {
        class Vector2
        {
        private:

        public:
            struct
            {
                float x;
                float y;
            };

            Vector2();
            Vector2(const float _x, const float _y);

            ~Vector2() {}

            float GetMagnitude() const;
            Vector2 Normalize() const;
            float DotProduct(const Vector2& vec) const;

            void operator=(const Vector2& vec);
            void operator+=(const Vector2& vec);
            void operator-=(const Vector2& vec);
            void operator*=(const Vector2& vec);
            void operator/=(const Vector2& vec);
            void operator*=(const float a);
            void operator/=(const float a);

            friend bool operator==(const Vector2& str, const Vector2& vec);
            friend Vector2 operator+(const Vector2& str, const Vector2& vec);
            friend Vector2 operator-(const Vector2& str, const Vector2& vec);
            friend Vector2 operator*(const Vector2& str, const float m);
            friend Vector2 operator*(const float m, const Vector2& str);
            friend Vector2 operator*(const Vector2& str, const Vector2& vec);
            friend Vector2 operator/(const Vector2& str, const float m);
        };

        //==============================================================================================================
        //                  VECTOR 3
        //==============================================================================================================

        class Vector3
        {
        private:

        public:
            struct
            {
                float x;
                float y;
                float z;
            };

            Vector3();
            Vector3(const float _x, const float _y, const float _z);

            ~Vector3() {}

            float GetMagnitude() const;
            Vector3 Normalize() const;
            Vector3 CrossProduct(const Vector3& vec) const;
            float DotProduct(const Vector3& vec) const;

            void operator=(const Vector3& vec);
            void operator+=(const Vector3& vec);
            void operator-=(const Vector3& vec);
            void operator*=(const Vector3& vec);
            void operator/=(const Vector3& vec);
            void operator*=(const float a);
            void operator/=(const float a);

            friend bool operator==(const Vector3& str, const Vector3& vec);
            friend bool operator!=(const Vector3& str, const Vector3& vec);
            friend Vector3 operator+(const Vector3& str, const Vector3& vec);
            friend Vector3 operator-(const Vector3& str, const Vector3& vec);
            friend Vector3 operator*(const Vector3& str, const float m);
            friend Vector3 operator*(const float m, const Vector3& str);
            friend Vector3 operator*(const Vector3& str, const Vector3& vec);
            friend Vector3 operator/(const Vector3& str, const float m);
        };

        //==============================================================================================================
        //                  VECTOR 4
        //==============================================================================================================

        class Vector4
        {
        private:

        public:
            union
            {
                struct
                {
                    float x;
                    float y;
                    float z;
                    float w;
                };

                Vector3 xyz;
            };

            Vector4();
            Vector4(const float _x, const float _y, const float _z, const float _w);
            Vector4(const float _n);
            Vector4(const Vector3& vector, float _w);

            ~Vector4() {}

            void Homogenize();
            float GetMagnitude() const;
            void Normalize();

            float GetCoor(int n);

            void operator=(const Vector4& vec);
            void operator+=(const Vector4& vec);
            void operator-=(const Vector4& vec);
            void operator*=(const Vector4& vec);
            void operator/=(const Vector4& vec);
            void operator*=(const float a);
            void operator/=(const float a);

            friend bool operator==(const Vector4& str, const Vector4& vec);
            friend Vector4 operator+(const Vector4& str, const Vector4& vec);
            friend Vector4 operator-(const Vector4& str, const Vector4& vec);
            friend Vector4 operator*(const Vector4& str, float m);
            friend Vector4 operator*(float m, const Vector4& str);
            friend Vector4 operator*(const Vector4& str, const Vector4& vec);
            friend Vector4 operator/(const Vector4& str, const float m);
        };

        //==============================================================================================================
        //                  MATRIX 3
        //==============================================================================================================

        class Matrix3
        {
        private:

        public:
            float matrix[3][3] = { 0 };

            Matrix3();
            Matrix3(const float a[3][3]);
            Matrix3(
                const float a, const float b, const float c,
                const float d, const float e, const float f,
                const float g, const float h, const float i
            );

            ~Matrix3() {};

            void operator=(const Matrix3& mat);
            void operator*=(const Matrix3& mat);
            void operator*=(const float a);
            void operator/=(const float a);

            friend bool operator==(const Matrix3& mat1, const Matrix3& mat2);
            friend Matrix3 operator*(const Matrix3& mat1, const Matrix3& mat2);
            friend Vector3 operator*(const Matrix3& mat, const Vector3& vec);
            friend Matrix3 operator*(const Matrix3& mat, const float a);
            friend Matrix3 operator/(const Matrix3& mat, const float a);

            static Matrix3 GetIdentity();
            void PrintMatrix();

            static Matrix3 CreateTranslationMatrix(const Vector2& translation);
            static Matrix3 CreateScaleMatrix(const Vector2& scale);
            static Matrix3 CreateXRotationMatrix(const float angle);
            static Matrix3 CreateYRotationMatrix(const float angle);
            static Matrix3 CreateZRotationMatrix(const float angle);
            static Matrix3 CreateRotation(const Vector3& rotation);
            static Matrix3 CreateTransformMatrix(const Vector2& position, const Vector3& rotation, const Vector2& scale);

            Matrix3 GetTransposeMatrix() const;
            void TransposeMatrix();

            float DeterminantMatrix3();

            Matrix3 AdjugateMatrix3();
            Matrix3 GetInverse() const;
        };

        //==============================================================================================================
        //                  MATRIX 4
        //==============================================================================================================

        class Matrix4
        {
        private:

        public:
            float matrix[4][4] = { 0 };

            Matrix4();
            Matrix4(const float a[4][4]);
            Matrix4(
                const float a, const float b, const float c, const float d,
                const float e, const float f, const float g, const float h,
                const float i, const float j, const float k, const float l,
                const float m, const float n, const float o, const float p
            );

            ~Matrix4() {};

            void operator=(const Matrix4& mat);
            void operator*=(const Matrix4& mat);
            void operator*=(const float a);
            void operator/=(const float a);

            friend bool operator==(const Matrix4& mat1, const Matrix4& mat2);
            friend Matrix4 operator*(const Matrix4& mat1, const Matrix4& mat2);
            friend Vector4 operator*(const Matrix4& mat, const Vector4& vec);
            friend Matrix4 operator*(const Matrix4& mat, const float a);
            friend Matrix4 operator/(const Matrix4& mat, const float a);

            static Matrix4 GetIdentity();
            void PrintMatrix();

            static Matrix4 CreateTranslationMatrix(const Vector3& translation);
            static Matrix4 CreateScaleMatrix(const Vector3& scale);
            static Matrix4 CreateXRotationMatrix(const float angle);
            static Matrix4 CreateYRotationMatrix(const float angle);
            static Matrix4 CreateZRotationMatrix(const float angle);
            static Matrix4 CreateRotation(const Vector3& rotation);
            static Matrix4 CreateTransformMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale);
            static Matrix4 CreatePerspectiveMatrix(float near, float far, float fov, float cameraWidth, float cameraHeight);
            static Matrix4 LookAt(Vector3  const& eye, Vector3  const& center, Vector3 const& up);

            Matrix4 GetTransposeMatrix() const;
            void TransposeMatrix();

            float DeterminantMatrix4();

            const float* ptr();

            Matrix4 AdjugateMatrix4();
            Matrix4 GetInverse() const;
        };

        //==============================================================================================================
        //                  HELPFUL FUNCTIONS
        //==============================================================================================================

        Vector3 Barycentre(const Vector3& point0, const Vector3& point1, const Vector3& point2);
        float TriangleArea(const Vector3& point0, const Vector3& point1, const Vector3& point2);
        Vector3 GetSphericalCoords(const float r, const float theta, const float phi);
        int sign(float f);

        Vector3 min3Vec3(const Vector3& a, const Vector3& b, const Vector3& c, const char coor);
        Vector3 max3Vec3(const Vector3& a, const Vector3& b, const Vector3& c, const char coor);


        //==============================================================================================================
        //                  HELPFUL STRUCTS
        //==============================================================================================================

        struct Transform
        {
            Transform(Vector3 position = Vector3(), Vector3 rotation = Vector3(), Vector3 scale = Vector3(1, 1, 1));

            Vector3 position = Vector3(0, 0, 0);
            Vector3 rotation = Vector3(0, 0, 0);
            Vector3 scale = Vector3(1, 1, 1);
        };

        struct Vertex
        {
            Vertex() {};
            Vertex(Vector3 position, Vector3 normal, Vector2 textureUV);

            Vector3 position = { 0, 0, 0 };
            Vector3 normal = { 0, 0, 0 };
            Vector2 textureUV = { 0, 0 };
        };

        //==============================================================================================================
        //                  PRIMITIVE FUNCTION
        //==============================================================================================================

        void CreateQuad(const Vector3& p0, const  Vector3& p1, const  Vector3& p2, const  Vector3& p3, std::vector<Vertex>& mesh);
        std::vector<Vertex> CreateCube(float size);
        std::vector<Vertex> CreateSphere(const float radius);

        std::vector<Vertex> CreateCapsule(const float radius, const float height, const float lat, const float sectorCount);
    }
}
