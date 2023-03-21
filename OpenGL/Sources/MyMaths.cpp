#include "MyMaths.h"


//==============================================================================================================
//                  VECTOR 2
 //==============================================================================================================

using namespace Core::Maths;

#pragma region Vector2

Vector2::Vector2() { x = y = 0; }

Vector2::Vector2(const float _x, const float _y)
{
    x = _x;
    y = _y;
}

float Vector2::GetMagnitude() const { return sqrt(pow(x, 2) + pow(y, 2)); }

Vector2 Vector2::Normalize() const
{
    Vector2 res;
    float magnitude = GetMagnitude();
    res.x = x / magnitude;
    res.y = y / magnitude;
    return res;
}

float Vector2::DotProduct(const Vector2& vec) const
{
    float res = x * vec.x + y * vec.y;
    return res;
}

void Core::Maths::Vector2::operator=(const Vector2& vec)
{
    x = vec.x;
    y = vec.y;
}

void Core::Maths::Vector2::operator+=(const Vector2& vec)
{
    x = x + vec.x;
    y = y + vec.y;
}

void Core::Maths::Vector2::operator-=(const Vector2& vec)
{
    x = x - vec.x;
    y = y - vec.y;
}

void Core::Maths::Vector2::operator*=(const Vector2& vec)
{
    x = x * vec.x;
    y = y * vec.y;
}

void Core::Maths::Vector2::operator/=(const Vector2& vec)
{
    x = x / vec.x;
    y = y / vec.y;
}

void Core::Maths::Vector2::operator*=(const float a)
{
    x = x * a;
    y = y * a;
}

void Core::Maths::Vector2::operator/=(const float a)
{
    x = x / a;
    y = y / a;
}

bool Core::Maths::operator==(const Vector2& str, const Vector2& vec)
{
    if (str.x == vec.x && str.y == vec.y)
        return true;
    else
        return false;
}

Vector2 Core::Maths::operator+(const Vector2& str, const Vector2& vec)
{
    Vector2 res;
    res.x = str.x + vec.x;
    res.y = str.y + vec.y;
    return res;
}

Vector2 Core::Maths::operator-(const Vector2& str, const Vector2& vec)
{
    Vector2 res;
    res.x = str.x - vec.x;
    res.y = str.y - vec.y;
    return res;
}

Vector2 Core::Maths::operator*(const Vector2& str, const float m)
{
    Vector2 res;
    res.x = str.x * m;
    res.y = str.y * m;
    return res;
}

Vector2 Core::Maths::operator*(const float m, const Vector2& str)
{
    Vector2 res;
    res.x = str.x * m;
    res.y = str.y * m;
    return res;
}

Vector2 Core::Maths::operator*(const Vector2& str, const Vector2& vec)
{
    Vector2 res;
    res.x = str.x * vec.x;
    res.y = str.y * vec.y;
    return res;
}

Vector2 Core::Maths::operator/(const Vector2& str, const float m)
{
    Vector2 res;
    res.x = str.x / m;
    res.y = str.y / m;
    return res;
}

#pragma endregion

//==============================================================================================================
//                  VECTOR 3
 //==============================================================================================================

#pragma region Vector3

Vector3::Vector3() { x = y = z = 0; }

Vector3::Vector3(const float _x, const float _y, const float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

float Vector3::GetMagnitude() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

Vector3 Vector3::Normalize() const
{
    Vector3 res;
    float magnitude = GetMagnitude();
    if (magnitude == 0) return Vector3();
    res.x = x / magnitude;
    res.y = y / magnitude;
    res.z = z / magnitude;
    return res;
}

Vector3 Vector3::CrossProduct(const Vector3& vec) const
{
    Vector3 res;
    res.x = y * vec.z - z * vec.y;
    res.y = z * vec.x - x * vec.z;
    res.z = x * vec.y - y * vec.x;
    return res;
}

float Vector3::DotProduct(const Vector3& vec) const
{
    float res = x * vec.x + y * vec.y + z * vec.z;
    return res;
}

void Core::Maths::Vector3::operator=(const Vector3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

void Core::Maths::Vector3::operator+=(const Vector3& vec)
{
    x = x + vec.x;
    y = y + vec.y;
    z = z + vec.z;
}

void Core::Maths::Vector3::operator-=(const Vector3& vec)
{
    x = x - vec.x;
    y = y - vec.y;
    z = z - vec.z;
}

void Core::Maths::Vector3::operator*=(const Vector3& vec)
{
    x = x * vec.x;
    y = y * vec.y;
    z = z * vec.z;
}

void Core::Maths::Vector3::operator/=(const Vector3& vec)
{
    x = x / vec.x;
    y = y / vec.y;
    z = z / vec.z;
}

void Core::Maths::Vector3::operator*=(const float a)
{
    x = x * a;
    y = y * a;
    z = z * a;
}

void Core::Maths::Vector3::operator/=(const float a)
{
    x = x / a;
    y = y / a;
    z = z / a;
}

bool Core::Maths::operator==(const Vector3& str, const Vector3& vec)
{
    if (str.x == vec.x && str.y == vec.y && str.z == vec.z)
        return true;
    else
        return false;
}

bool Core::Maths::operator!=(const Vector3& str, const Vector3& vec)
{
    if (str.x != vec.x || str.y != vec.y || str.z != vec.z)
        return true;
    else
        return false;
}

Vector3 Core::Maths::operator+(const Vector3& str, const Vector3& vec)
{
    Vector3 res;
    res.x = str.x + vec.x;
    res.y = str.y + vec.y;
    res.z = str.z + vec.z;
    return res;
}

Vector3 Core::Maths::operator-(const Vector3& str, const Vector3& vec)
{
    Vector3 res;
    res.x = str.x - vec.x;
    res.y = str.y - vec.y;
    res.z = str.z - vec.z;
    return res;
}

Vector3 Core::Maths::operator*(const Vector3& str, const float m)
{
    Vector3 res;
    res.x = str.x * m;
    res.y = str.y * m;
    res.z = str.z * m;
    return res;
}

Vector3 Core::Maths::operator*(const float m, const Vector3& str)
{
    Vector3 res;
    res.x = str.x * m;
    res.y = str.y * m;
    res.z = str.z * m;
    return res;
}

Vector3 Core::Maths::operator*(const Vector3& str, const Vector3& vec)
{
    Vector3 res;
    res.x = str.x * vec.x;
    res.y = str.y * vec.y;
    res.z = str.z * vec.z;
    return res;
}

Vector3 Core::Maths::operator/(const Vector3& str, const float m)
{
    Vector3 res;
    res.x = str.x / m;
    res.y = str.y / m;
    res.z = str.z / m;
    return res;
}

#pragma endregion
//==============================================================================================================
//                  VECTOR 4
//===============================================================================================================


#pragma region Vector4

Vector4::Vector4()
{
    x = y = z = 0;
    w = 1.0f;
}

Vector4::Vector4(const float _x, const float _y, const float _z, const float _w = 1.0f)
{
    xyz.x = x = _x;
    xyz.y = y = _y;
    xyz.z = z = _z;
    w = _w;
}

Vector4::Vector4(const float _n)
{
    xyz.x = x = _n;
    xyz.y = y = _n;
    xyz.z = z = _n;
    w = _n;
}

Vector4::Vector4(const Vector3& vector, float _w = 1.0f)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
    w = _w;

    xyz = vector;
}

void Vector4::Homogenize()
{
    if (w != 0)
    {
        x = x / w;
        y = y / w;
        z = z / w;
    }
    return;
}

float Vector4::GetMagnitude() const
{
    Vector4 copy = *this;
    copy.Homogenize();

    return sqrt(pow(copy.x, 2) + pow(copy.y, 2) + pow(copy.z, 2));
}

void Vector4::Normalize()
{
    float magnitude = GetMagnitude();
    x = x / magnitude;
    y = y / magnitude;
    z = z / magnitude;
}

float Vector4::GetCoor(int n)
{
    switch (n % 4)
    {
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    default:
        return x;
    }
}

void Core::Maths::Vector4::operator=(const Vector4& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;
}

void Core::Maths::Vector4::operator+=(const Vector4& vec)
{
    x = x + vec.x;
    y = y + vec.y;
    z = z + vec.z;
    w = w + vec.w;
}

void Core::Maths::Vector4::operator-=(const Vector4& vec)
{
    x = x - vec.x;
    y = y - vec.y;
    z = z - vec.z;
    w = w - vec.w;
}

void Core::Maths::Vector4::operator*=(const Vector4& vec)
{
    x = x * vec.x;
    y = y * vec.y;
    z = z * vec.z;
    w = w * vec.w;
}

void Core::Maths::Vector4::operator/=(const Vector4& vec)
{
    x = x / vec.x;
    y = y / vec.y;
    z = z / vec.z;
    w = w / vec.w;
}

void Core::Maths::Vector4::operator*=(const float a)
{
    x = x * a;
    y = y * a;
    z = z * a;
    w = w * a;
}

void Core::Maths::Vector4::operator/=(const float a)
{
    x = x * a;
    y = y * a;
    z = z * a;
    w = w * a;
}

bool Core::Maths::operator==(const Vector4& str, const Vector4& vec)
{
    if (str.x == vec.x && str.y == vec.y && str.z == vec.z && str.w == vec.w)
        return true;
    else
        return false;
}

Vector4 Core::Maths::operator+(const Vector4& str, const Vector4& vec)
{
    Vector4 res;
    res.x = str.x + vec.x;
    res.y = str.y + vec.y;
    res.z = str.z + vec.z;
    res.w = str.w + vec.w;
    return res;
}

Vector4 Core::Maths::operator-(const Vector4& str, const Vector4& vec)
{
    Vector4 res;
    res.x = str.x - vec.x;
    res.y = str.y - vec.y;
    res.z = str.z - vec.z;
    res.w = str.w - vec.w;
    return res;
}

Vector4 Core::Maths::operator*(const Vector4& str, float m)
{
    Vector4 res;
    res.x = str.x * m;
    res.y = str.y * m;
    res.z = str.z * m;
    res.w = str.w * m;
    return res;
}

Vector4 Core::Maths::operator*(float m, const Vector4& str)
{
    Vector4 res;
    res.x = str.x * m;
    res.y = str.y * m;
    res.z = str.z * m;
    res.w = str.w * m;
    return res;
}

Vector4 Core::Maths::operator*(const Vector4& str, const Vector4& vec)
{
    Vector4 res;
    res.x = str.x * vec.x;
    res.y = str.y * vec.y;
    res.z = str.z * vec.z;
    res.w = str.w * vec.w;
    return res;
}

Vector4 Core::Maths::operator/(const Vector4& str, const float m)
{
    Vector4 res;
    res.x = str.x / m;
    res.y = str.y / m;
    res.z = str.z / m;
    res.w = str.w / m;
    return res;
}

#pragma endregion

//==============================================================================================================
//                  MATRIX 3
//===============================================================================================================

#pragma region Matrix3

Matrix3::Matrix3()
{
    for (int i = 0; i < 3; i++)
    {
        matrix[i][i] = 1;
    }
};

Matrix3::Matrix3(const float a[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[j][i] = a[j][i];
        }
    }
}

Matrix3::Matrix3(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i)
{
    matrix[0][0] = a;
    matrix[1][0] = b;
    matrix[2][0] = c;
    matrix[0][1] = d;
    matrix[1][1] = e;
    matrix[2][1] = f;
    matrix[0][2] = g;
    matrix[1][2] = h;
    matrix[2][2] = i;
}

void Core::Maths::Matrix3::operator=(const Matrix3& mat)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[j][i] = mat.matrix[j][i];
        }
    }
}

void Core::Maths::Matrix3::operator*=(const Matrix3& mat)
{
    Matrix3 copy = matrix;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[j][i] = copy.matrix[i][0] * mat.matrix[0][j] + copy.matrix[i][1] * mat.matrix[1][j] + copy.matrix[i][2] * mat.matrix[2][j];
        }
    }
}

void Core::Maths::Matrix3::operator*=(const float a)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[j][i] *= a;
        }
    }
}

void Core::Maths::Matrix3::operator/=(const float a)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[j][i] /= a;
        }
    }
}

bool Core::Maths::operator==(const Matrix3& mat1, const Matrix3& mat2)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (mat1.matrix[j][i] != mat2.matrix[j][i])
                return false;
        }
    }
    return true;
}

Matrix3 Core::Maths::operator*(const Matrix3& mat1, const Matrix3& mat2)
{
    Matrix3 res;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            res.matrix[j][i] = mat1.matrix[i][0] * mat2.matrix[0][j] + mat1.matrix[i][1] * mat2.matrix[1][j] + mat1.matrix[i][2] * mat2.matrix[2][j];
        }
    }
    return res;
}

Vector3 Core::Maths::operator*(const Matrix3& mat, const Vector3& vec)
{
    Vector3 res;
    res.x = mat.matrix[0][0] * vec.x + mat.matrix[0][1] * vec.y + mat.matrix[0][2];
    res.y = mat.matrix[1][0] * vec.x + mat.matrix[1][1] * vec.y + mat.matrix[1][2];
    res.z = mat.matrix[2][0] * vec.x + mat.matrix[2][1] * vec.y + mat.matrix[2][2];
    return res;
}

Matrix3 Core::Maths::operator*(const Matrix3& mat, const float a)
{
    Matrix3 res;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            res.matrix[j][i] = mat.matrix[j][i] * a;
        }
    }
    return res;
}

Matrix3 Core::Maths::operator/(const Matrix3& mat, const float a)
{
    Matrix3 res;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            res.matrix[j][i] = mat.matrix[j][i] / a;
        }
    }
    return res;
}

Matrix3 Matrix3::GetIdentity()
{
    Matrix3 res;
    return res;
}

void Matrix3::PrintMatrix()
{
    for (int i = 0; i < 3; i++)
    {
        printf("{ ");
        for (int j = 0; j < 2; j++)
            printf("%f, ", matrix[i][j]);
        printf("%f }\n", matrix[i][2]);
    }
    printf("\n\n");
}

Matrix3 Matrix3::CreateTranslationMatrix(const Vector2& translation)
{
    Matrix3 res;
    res.matrix[0][2] = translation.x;
    res.matrix[1][2] = translation.y;
    return res;
}

Matrix3 Matrix3::CreateScaleMatrix(const Vector2& scale)
{
    Matrix3 res;
    res.matrix[0][0] = scale.x;
    res.matrix[1][1] = scale.y;
    return res;
}

Matrix3 Matrix3::CreateXRotationMatrix(const float angle)
{
    Matrix3 res;
    res.matrix[2][2] = res.matrix[1][1] = cosf(angle * DEG2RAD);
    res.matrix[1][2] = sinf(angle * DEG2RAD);
    res.matrix[2][1] = -sinf(angle * DEG2RAD);
    return res;
}

Matrix3 Matrix3::CreateYRotationMatrix(const float angle)
{
    Matrix3 res;
    res.matrix[2][2] = res.matrix[0][0] = cosf(angle * DEG2RAD);
    res.matrix[0][2] = -sinf(angle * DEG2RAD);
    res.matrix[2][0] = sinf(angle * DEG2RAD);
    return res;
}

Matrix3 Matrix3::CreateZRotationMatrix(const float angle)
{
    Matrix3 res;
    res.matrix[0][0] = res.matrix[1][1] = cosf(angle * DEG2RAD);
    res.matrix[0][1] = sinf(angle * DEG2RAD);
    res.matrix[1][0] = -sinf(angle * DEG2RAD);
    return res;
}

Matrix3 Matrix3::CreateRotation(const Vector3& rotation)
{
    Matrix3 matRotX = CreateXRotationMatrix(rotation.x);
    Matrix3 matRotY = CreateYRotationMatrix(rotation.y);
    Matrix3 matRotZ = CreateZRotationMatrix(rotation.z);

    return (matRotY * matRotX * matRotZ);
}

Matrix3 Matrix3::CreateTransformMatrix(const Vector2& position, const Vector3& rotation, const Vector2& scale)
{
    Matrix3 matTranslation = CreateTranslationMatrix(position);
    Matrix3 matRot = CreateRotation(rotation);
    Matrix3 matScale = CreateScaleMatrix(scale);

    Matrix3 transform = matTranslation * matRot * matScale;
    return transform;
}

Matrix3 Matrix3::GetTransposeMatrix() const
{
    Matrix3 res;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            res.matrix[j][i] = matrix[i][j];
        }
    }
    return res;
}

void Matrix3::TransposeMatrix()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[j][i] = matrix[i][j];
        }
    }
}

float Matrix3::DeterminantMatrix3()
{
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
        - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
        + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

Matrix3 Matrix3::AdjugateMatrix3()
{
    Matrix3 res;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Matrix3 copy = *this;
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    if (x == j && y == i)
                    {
                        copy.matrix[y][x] = 1;
                    }
                    else if (x == j || y == i)
                    {
                        copy.matrix[y][x] = 0;
                    }
                }
            }
            res.matrix[i][j] = copy.DeterminantMatrix3();
        }
    }
    return res;
}

Matrix3 Matrix3::GetInverse() const
{
    Matrix3 copy = *this;
    float determinant = copy.DeterminantMatrix3();
    copy = copy.AdjugateMatrix3();
    copy = copy.GetTransposeMatrix();
    if (determinant == 0)
    {
        Matrix3 null;
        return null;
    }
    return copy / determinant;
}

#pragma endregion

//==============================================================================================================
//                  MATRIX 4
//===============================================================================================================

#pragma region Matrix4

Matrix4::Matrix4()
{
    for (int i = 0; i < 4; i++)
    {
        matrix[i][i] = 1;
    }
};

Matrix4::Matrix4(const float a[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[j][i] = a[j][i];
        }
    }
}

Matrix4::Matrix4(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i, const float j, const float k, const float l, const float m, const float n, const float o, const float p)
{
    matrix[0][0] = a;
    matrix[1][0] = b;
    matrix[2][0] = c;
    matrix[3][0] = d;
    matrix[0][1] = e;
    matrix[1][1] = f;
    matrix[2][1] = g;
    matrix[3][1] = h;
    matrix[0][2] = i;
    matrix[1][2] = j;
    matrix[2][2] = k;
    matrix[3][2] = l;
    matrix[0][3] = m;
    matrix[1][3] = n;
    matrix[2][3] = o;
    matrix[3][3] = p;
}

void Core::Maths::Matrix4::operator=(const Matrix4& mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[j][i] = mat.matrix[j][i];
        }
    }
}


void Core::Maths::Matrix4::operator*=(const Matrix4& mat)
{
    Matrix4 copy = matrix;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = copy.matrix[i][0] * mat.matrix[0][j] + copy.matrix[i][1] * mat.matrix[1][j] + copy.matrix[i][2] * mat.matrix[2][j] + copy.matrix[i][3] * mat.matrix[3][j];
        }
    }
}

void Core::Maths::Matrix4::operator*=(const float a)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[j][i] *= a;
        }
    }
}

void Core::Maths::Matrix4::operator/=(const float a)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[j][i] /= a;
        }
    }
}
bool Core::Maths::operator==(const Matrix4& mat1, const Matrix4& mat2)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mat1.matrix[j][i] != mat2.matrix[j][i])
                return false;
        }
    }
    return true;
}

Matrix4 Core::Maths::operator*(const Matrix4& mat1, const Matrix4& mat2)
{
    Matrix4 res;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res.matrix[i][j] = mat1.matrix[i][0] * mat2.matrix[0][j] + mat1.matrix[i][1] * mat2.matrix[1][j] + mat1.matrix[i][2] * mat2.matrix[2][j] + mat1.matrix[i][3] * mat2.matrix[3][j];
        }
    }
    return res;
}

Vector4 Core::Maths::operator*(const Matrix4& mat, const Vector4& vec)
{
    Vector4 res;
    res.x = mat.matrix[0][0] * vec.x + mat.matrix[0][1] * vec.y + mat.matrix[0][2] * vec.z + mat.matrix[0][3] * vec.w;
    res.y = mat.matrix[1][0] * vec.x + mat.matrix[1][1] * vec.y + mat.matrix[1][2] * vec.z + mat.matrix[1][3] * vec.w;
    res.z = mat.matrix[2][0] * vec.x + mat.matrix[2][1] * vec.y + mat.matrix[2][2] * vec.z + mat.matrix[2][3] * vec.w;
    res.w = mat.matrix[3][0] * vec.x + mat.matrix[3][1] * vec.y + mat.matrix[3][2] * vec.z + mat.matrix[3][3] * vec.w;
    return res;
}

Matrix4 Core::Maths::operator*(const Matrix4& mat, const float a)
{
    Matrix4 res;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res.matrix[j][i] = mat.matrix[j][i] * a;
        }
    }
    return res;
}

Matrix4 Core::Maths::operator/(const Matrix4& mat, const float a)
{
    Matrix4 res;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res.matrix[j][i] = mat.matrix[j][i] / a;
        }
    }
    return res;
}

Matrix4 Matrix4::GetIdentity()
{
    Matrix4 res;
    return res;
}

void Matrix4::PrintMatrix()
{
    for (int i = 0; i < 4; i++)
    {
        printf("{ ");
        for (int j = 0; j < 3; j++)
            printf("%f, ", matrix[i][j]);
        printf("%f }\n", matrix[i][3]);
    }
    printf("\n\n");
}


Matrix4 Matrix4::CreateTranslationMatrix(const Vector3& translation)
{
    Matrix4 res;
    res.matrix[0][3] = translation.x;
    res.matrix[1][3] = translation.y;
    res.matrix[2][3] = translation.z;

    return res;
}

Matrix4 Matrix4::CreateScaleMatrix(const Vector3& scale)
{
    Matrix4 res;
    res.matrix[0][0] = scale.x;
    res.matrix[1][1] = scale.y;
    res.matrix[2][2] = scale.z;
    res.matrix[3][3] = 1;
    return res;
}

Matrix4 Matrix4::CreateXRotationMatrix(const float angle)
{
    Matrix4 res;
    res.matrix[2][2] = res.matrix[1][1] = cosf(angle * DEG2RAD);
    res.matrix[1][2] = -sinf(angle * DEG2RAD);
    res.matrix[2][1] = sinf(angle * DEG2RAD);
    return res;
}

Matrix4 Matrix4::CreateYRotationMatrix(const float angle)
{
    Matrix4 res;
    res.matrix[2][2] = res.matrix[0][0] = cosf(angle * DEG2RAD);
    res.matrix[0][2] = sinf(angle * DEG2RAD);
    res.matrix[2][0] = -sinf(angle * DEG2RAD);
    return res;
}

Matrix4 Matrix4::CreateZRotationMatrix(const float angle)
{
    Matrix4 res;
    res.matrix[0][0] = res.matrix[1][1] = cosf(angle * DEG2RAD);
    res.matrix[0][1] = -sinf(angle * DEG2RAD);
    res.matrix[1][0] = sinf(angle * DEG2RAD);
    return res;
}

Matrix4 Matrix4::CreateRotation(const Vector3& rotation)
{
    Matrix4 matRotX = CreateXRotationMatrix(rotation.x);
    Matrix4 matRotY = CreateYRotationMatrix(rotation.y);
    Matrix4 matRotZ = CreateZRotationMatrix(rotation.z);

    return (matRotY * matRotX * matRotZ);
}

Matrix4 Matrix4::CreateTransformMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale)
{
    Matrix4 matTranslation = CreateTranslationMatrix(position);
    Matrix4 matRot = CreateRotation(rotation);
    Matrix4 matScale = CreateScaleMatrix(scale);

    Matrix4 transform = matTranslation * matRot * matScale;
    return transform;
}

Matrix4 Matrix4::GetTransposeMatrix() const
{
    Matrix4 res;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res.matrix[j][i] = matrix[i][j];
        }
    }
    return res;
}

void Matrix4::TransposeMatrix()
{
    Matrix4 copy = matrix;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[j][i] = copy.matrix[i][j];
        }
    }
}

float Matrix4::DeterminantMatrix4()
{
    return ((matrix[0][0] * matrix[1][1] * (matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2]) - matrix[0][0] * matrix[1][2] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1]) + matrix[0][0] * matrix[1][3] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1])) -
        (matrix[0][1] * matrix[1][0] * (matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2]) - matrix[0][1] * matrix[1][2] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) + matrix[0][1] * matrix[1][3] * (matrix[2][0] * matrix[3][2] - matrix[3][0] * matrix[2][2])) +
        (matrix[0][2] * matrix[1][0] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1]) - matrix[0][2] * matrix[1][1] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) + matrix[0][2] * matrix[1][3] * (matrix[2][0] * matrix[3][1] - matrix[3][0] * matrix[2][1])) -
        (matrix[0][3] * matrix[1][0] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1]) - matrix[0][3] * matrix[1][1] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0]) + matrix[0][3] * matrix[1][2] * (matrix[2][0] * matrix[3][1] - matrix[3][0] * matrix[2][1])));
}

Matrix4 Matrix4::AdjugateMatrix4()
{
    Matrix4 res;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Matrix4 copy = *this;
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    if (x == j && y == i)
                    {
                        copy.matrix[y][x] = 1;
                    }
                    else if (x == j || y == i)
                    {
                        copy.matrix[y][x] = 0;
                    }
                }
            }
            res.matrix[i][j] = copy.DeterminantMatrix4();
        }
    }
    return res;
}

Matrix4 Matrix4::GetInverse() const
{
    Matrix4 copy = *this;
    float determinant = copy.DeterminantMatrix4();
    copy = copy.AdjugateMatrix4();
    copy = copy.GetTransposeMatrix();
    if (determinant == 0)
    {
        Matrix4 null;
        return null;
    }
    return copy / determinant;
}

Matrix4 Matrix4::CreatePerspectiveMatrix(float near, float far, float fov, float cameraWidth, float cameraHeight)
{
    float f = 1 / (tanf(fov / 2 * DEG2RAD));
    float aspect = cameraWidth / cameraHeight;
    Matrix4 res;

    // Create Projection matrix
    res.matrix[0][0] = f / aspect;
    res.matrix[1][1] = f;
    res.matrix[2][2] = -((far + near) / (far - near));
    res.matrix[3][2] = -1;
    res.matrix[2][3] = -((2 * far * near) / (far - near));
    res.matrix[3][3] = 0;

    return res;

}

Matrix4 Matrix4::LookAt(Vector3  const& eye, Vector3  const& center, Vector3 const& up)
{
    Vector3  f = (center - eye).Normalize();
    Vector3  u = up;
    Vector3  s = f.CrossProduct(u).Normalize();
    u = s.CrossProduct(f);

    Matrix4 res;
    res.matrix[0][0] = s.x;
    res.matrix[1][0] = s.y;
    res.matrix[2][0] = s.z;
    res.matrix[0][1] = u.x;
    res.matrix[1][1] = u.y;
    res.matrix[2][1] = u.z;
    res.matrix[0][2] = -f.x;
    res.matrix[1][2] = -f.y;
    res.matrix[2][2] = -f.z;
    res.matrix[3][0] = -s.DotProduct(eye);
    res.matrix[3][1] = -u.DotProduct(eye);
    res.matrix[3][2] = f.DotProduct(eye);
    return res;
}

const float* Matrix4::ptr()
{
    return *matrix;
}

#pragma endregion

//==============================================================================================================
//                  HELPFUL FUNCTIONS
//==============================================================================================================

#pragma region Helpful Fuctions

Vector3 Core::Maths::Barycentre(const Vector3& point0, const Vector3& point1, const Vector3& point2)
{
    return { (point0.x + point1.x + point2.x) / 3,
            (point0.y + point1.y + point2.y) / 3,
            0 };
}

float Core::Maths::TriangleArea(const Vector3& point0, const Vector3& point1, const Vector3& point2)
{
    Vector3 vec0 = point1 - point0;
    Vector3 vec1 = point2 - point0;
    return (vec0.x * vec1.y - vec0.y * vec1.x) / 2;
}

Vector3 Core::Maths::GetSphericalCoords(const float r, const float theta, const float phi)
{
    return { r * sinf(theta) * cosf(phi),
            r * cosf(theta),
            r * sinf(theta) * sinf(phi) };
}

int Core::Maths::sign(float f)
{
    if (f < 0)
        return -1;
    else
        return 1;
}

Vector3 Core::Maths::min3Vec3(const Vector3& a, const Vector3& b, const Vector3& c, const char coor)
{
    if (coor == 'x')
    {
        Vector3 min = a;
        if (min.x > b.x)
            min = b;
        if (min.x > c.x)
            min = c;
        return min;
    }
    else if (coor == 'y')
    {
        Vector3 min = a;
        if (min.y > b.y)
            min = b;
        if (min.y > c.y)
            min = c;
        return min;
    }
    else
    {
        Vector3 min = a;
        if (min.z > b.z)
            min = b;
        if (min.z > c.z)
            min = c;
        return min;
    }
}

Vector3 Core::Maths::max3Vec3(const Vector3& a, const Vector3& b, const Vector3& c, const char coor)
{
    if (coor == 'x')
    {
        Vector3 max = a;
        if (max.x < b.x)
            max = b;
        if (max.x < c.x)
            max = c;
        return max;
    }
    else if (coor == 'y')
    {
        Vector3 max = a;
        if (max.y < b.y)
            max = b;
        if (max.y < c.y)
            max = c;
        return max;
    }
    else
    {
        Vector3 max = a;
        if (max.z < b.z)
            max = b;
        if (max.z < c.z)
            max = c;
        return max;
    }
}

#pragma endregion

Core::Maths::Transform::Transform(Vector3 _position, Vector3 _rotation, Vector3 _scale)
{
    position = _position;
    rotation = _rotation;
    scale = _scale;
}

Core::Maths::Vertex::Vertex(Vector3 _position, Vector3 _normal, Vector2 _textureUV)
{
    position = _position;
    normal = _normal;
    textureUV = _textureUV;
}
//==============================================================================================================
//                  PRIMITIVE FUNCTIONS
//==============================================================================================================

void Core::Maths::CreateQuad(const Vector3& p0, const  Vector3& p1, const  Vector3& p2, const  Vector3& p3, std::vector<Vertex>& mesh)
{
    /*Vector3 normal;
    Vector3 vec1 = p1 - p0;
    Vector3 vec2 = p3 - p0;
    normal = vec1.CrossProduct(vec2);*/

    Vector3 n0 = p0 / p0.GetMagnitude();
    Vector3 n1 = p1 / p1.GetMagnitude();
    Vector3 n2 = p2 / p2.GetMagnitude();
    Vector3 n3 = p3 / p3.GetMagnitude();

    mesh.insert(mesh.end(),
        { Vertex(p0, n0, Vector2(0.0f, 1.0f)),
          Vertex(p2, n2, Vector2(1.0f, 0.0f)),
          Vertex(p1, n1, Vector2(1.0f, 1.0f)),

          Vertex(p2, n2, Vector2(1.0f, 0.0f)),
          Vertex(p0, n0, Vector2(0.0f, 1.0f)),
          Vertex(p3, n3, Vector2(0.0f, 0.0f)) });

}

std::vector<Vertex> Core::Maths::CreateCube(float size)
{
    std::vector<Vertex> res;
    size = size / 2.f;

    CreateQuad(
        { - size, - size, + size },
        { - size, + size, + size },
        { + size, + size, + size },
        { + size, - size, + size },
        res);

    CreateQuad(
        { - size, - size, - size },
        { + size, - size, - size },
        { + size, + size, - size },
        { - size, + size, - size },
        res);

    CreateQuad(
        { + size, - size, - size },
        { + size, - size, + size },
        { + size, + size, + size },
        { + size, + size, - size },
        res);

    CreateQuad(
        { - size, - size, - size },
        { - size, + size, - size },
        { - size, + size, + size },
        { - size, - size, + size },
        res);

    CreateQuad(
        { - size, + size, - size },
        { + size, + size, - size },
        { + size, + size, + size },
        { - size, + size, + size },
        res);

    CreateQuad(
        { - size, - size, - size },
        { - size, - size, + size },
        { + size, - size, + size },
        { + size, - size, - size },
        res);
    return res;
}

std::vector<Vertex> Core::Maths::CreateSphere(const float radius)
{
    std::vector<Vertex> res;
    int lon = 10;
    int lat = 10;

    for (int j = 0; j < lat; ++j)
    {
        float theta0 = ((j + 0) / (float)lat) * MY_PI;
        float theta1 = ((j + 1) / (float)lat) * MY_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi0 = ((i + 0) / (float)lon) * 2.f * MY_PI;
            float phi1 = ((i + 1) / (float)lon) * 2.f * MY_PI;

            Vector3 c0 = GetSphericalCoords(radius, theta0, phi0);
            Vector3 c1 = GetSphericalCoords(radius, theta0, phi1);
            Vector3 c2 = GetSphericalCoords(radius, theta1, phi1);
            Vector3 c3 = GetSphericalCoords(radius, theta1, phi0);

            CreateQuad(
                { c3.x, c3.y, c3.z },
                { c2.x, c2.y, c2.z },
                { c1.x, c1.y, c1.z },
                { c0.x, c0.y, c0.z },
                res);
        }
    }
    return res;

}

std::vector<Vertex> Core::Maths::CreateCapsule(const float radius, const float height, const float lat, const float sectorCount)
{
    std::vector<Vertex> res;
    //float newSector = radius * 20;
    //float newLat = height * 20;
    float theta = 2 * MY_PI / sectorCount;
    float omega = MY_PI / 2 / lat;
    for (int i = 0; i < sectorCount; i++)
    {
        float a = radius * cosf((i + 1) * theta);
        float b = radius * sinf((i + 1) * theta);
        float c = radius * cosf(i * theta);
        float d = radius * sinf(i * theta);

        // create cylinder vertex
        CreateQuad(
            Vector3(a, b,  height / 2),
            Vector3(c, d,  height / 2),
            Vector3(c, d, -height / 2),
            Vector3(a, b, -height / 2), 
            res
        );

        for (int j = 0; j < lat; j++)
        {
            float e = cosf((j + 1) * omega);
            float f = radius * sinf((j + 1) * omega) + height / 2;
            float g = cosf(j * omega);
            float h = radius * sinf(j * omega) + height / 2;
               
            // create top semi sphere vertex 
            CreateQuad(
                Vector3( e * a, e * b, f),
                Vector3( e * c, e * d, f),
                Vector3( g * c, g * d, h),
                Vector3( g * a, g * b, h),
                res
            );

            // create bottom semi sphere vertex
            CreateQuad(
                Vector3(e * a, e * b, -f),
                Vector3(e * c, e * d, -f),
                Vector3(g * c, g * d, -h),
                Vector3(g * a, g * b, -h),
                res
            );
        }
    }
    return res;
}