#pragma once

#include <string.h>

typedef struct Matrix4
{
	float matrix_data[16];
} Matrix4;

Matrix4 Matrix4_Identity();
Matrix4 Matrix4_Orthographic(float left, float right, float bottom, float top, float near, float far);
Matrix4 Matrix4_Translate(Matrix4 matrix, float x, float y, float z);
Matrix4 Matrix4_Scale(Matrix4 matrix, float size_x, float size_y, float size_z);
Matrix4 Matrix4_Multiply(Matrix4 m1, Matrix4 m2);