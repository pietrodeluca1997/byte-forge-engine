#include "Math/Matrix4.h"

Matrix4 Matrix4_Identity()
{
	Matrix4 matrix = { 0 };
	memset(matrix.matrix_data, 0, sizeof(matrix.matrix_data));

	matrix.matrix_data[0] = 1;
	matrix.matrix_data[5] = 1;
	matrix.matrix_data[10] = 1;
	matrix.matrix_data[15] = 1;

	return matrix;
}

Matrix4 Matrix4_Orthographic(float left, float right, float bottom, float top, float near, float far)
{
    Matrix4 result = { 0 };

    result.matrix_data[0] = 2.0f / (right - left);
    result.matrix_data[5] = 2.0f / (top - bottom);
    result.matrix_data[10] = -2.0f / (far - near);
    result.matrix_data[15] = 1.0f;
        
    result.matrix_data[12] = -(right + left) / (right - left);
    result.matrix_data[13] = -(top + bottom) / (top - bottom);
    result.matrix_data[14] =- -(far + near) / (far - near);

    return result;
}

Matrix4 Matrix4_Translate(Matrix4 matrix, float x, float y, float z)
{
    matrix.matrix_data[12] = x;
    matrix.matrix_data[13] = y;
    matrix.matrix_data[14] = z;

    return matrix;
}

Matrix4 Matrix4_Scale(Matrix4 matrix, float size_x, float size_y, float size_z)
{
    matrix.matrix_data[0] = size_x;
    matrix.matrix_data[5] = size_y;
    matrix.matrix_data[10] = size_z;

    return matrix;
}

Matrix4 Matrix4_Multiply(Matrix4 m1, Matrix4 m2)
{
    Matrix4 result = { 0 };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.matrix_data[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++) {
                result.matrix_data[i * 4 + j] += m1.matrix_data[i * 4 + k] * m2.matrix_data[k * 4 + j];
            }
        }
    }

    return result;
}
