#include "../line_batch.h"
#include <glad/glad.h>

struct LineVertex3D
{
	vec3 position;
	vec3 color;
};

LineBatch3D::LineBatch3D(unsigned int size)
{
	BATCH_SIZE = size;

	m_VertexArray = new float[BATCH_SIZE * 2 * sizeof(LineVertex3D)/sizeof(float)];

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, BATCH_SIZE * 2 * sizeof(LineVertex3D), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex3D), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex3D), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

LineBatch3D::~LineBatch3D()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete[] m_VertexArray;
}

void LineBatch3D::Begin()
{
	m_BatchOpen = true;
	m_StackTop = 0;
}

bool LineBatch3D::AddLine(const Line3D& line)
{
	if(m_StackTop >= BATCH_SIZE || !m_BatchOpen)
		return false;

	unsigned int vertex_size = sizeof(LineVertex3D)/sizeof(float);
	unsigned int array_top = m_StackTop * 2 * vertex_size;

	m_VertexArray[array_top + 0] = line.begin.x;
	m_VertexArray[array_top + 1] = line.begin.y;
	m_VertexArray[array_top + 2] = line.begin.z;

	m_VertexArray[array_top + 3] = line.color.x;
	m_VertexArray[array_top + 4] = line.color.y;
	m_VertexArray[array_top + 5] = line.color.z;

	m_VertexArray[array_top + 6] = line.end.x;
	m_VertexArray[array_top + 7] = line.end.y;
	m_VertexArray[array_top + 8] = line.end.z;

	m_VertexArray[array_top + 9] = line.color.x;
	m_VertexArray[array_top +10] = line.color.y;
	m_VertexArray[array_top +11] = line.color.z;

	m_StackTop++;
	return true;
}

void LineBatch3D::End()
{
	m_BatchOpen = false;
}

void LineBatch3D::DrawBatch()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_StackTop * 2 * sizeof(LineVertex3D), m_VertexArray);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_LINES, 0, 2 * m_StackTop);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindVertexArray(0);
}