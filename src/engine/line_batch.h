#pragma once
#include "vmath.h"

struct Line3D
{
	vec3 begin;
	vec3 end;
	vec3 color;
};

class LineBatch3D
{
public:
	LineBatch3D(unsigned int size);
	~LineBatch3D();

	void Begin();
	bool AddLine(const Line3D& line);
	void End();

	void DrawBatch();

private:
	bool m_BatchOpen = false;
	unsigned int m_StackTop = 0;

	unsigned int VAO, VBO;
	float *m_VertexArray;

	unsigned int BATCH_SIZE;
};