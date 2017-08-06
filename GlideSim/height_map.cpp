#include "height_map.h"

#include "core.h"

void HeightMap::create_chunk(vec3 pos)
{
	Chunk new_chunk;

	new_chunk.position = pos;

	vector<vec3> vertices;
	vector<vec3> colors;
	vector<unsigned int> indices;

	float step = chunk_size / segments;

	for (int x = 0; x < segments + 1; x++)
	{
		for (int z = 0; z < segments + 1; z++)
		{
			float amplitude = ((float)rand() / RAND_MAX) * map_amplitude - map_amplitude*0.5f;

			vertices.push_back(vec3(x*step, amplitude, z*step));

			vec3 color = vec3(1, 0, 0) * amplitude + vec3(0, 1, 0)*(1.0f - amplitude / map_amplitude);

			colors.push_back(color);
		}
	}

	for (int x = 0; x < segments; x++)
	{
		for (int z = 0; z < segments; z++)
		{
			indices.push_back((x + 0)*(segments + 1) + (z + 0));
			indices.push_back((x + 0)*(segments + 1) + (z + 1));
			indices.push_back((x + 1)*(segments + 1) + (z + 0));

			indices.push_back((x + 0)*(segments + 1) + (z + 1));
			indices.push_back((x + 1)*(segments + 1) + (z + 1));
			indices.push_back((x + 1)*(segments + 1) + (z + 0));
		}
	}

	new_chunk.indices = indices.size();

	glGenVertexArrays(1, &new_chunk.vao);
	glBindVertexArray(new_chunk.vao);

	glGenBuffers(1, &new_chunk.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, new_chunk.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &new_chunk.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, new_chunk.vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &new_chunk.cbo);
	glBindBuffer(GL_ARRAY_BUFFER, new_chunk.cbo);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, new_chunk.vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, new_chunk.cbo);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	chunks.push_back(new_chunk);
}

HeightMap::HeightMap()
{
	chunk_size = 500;

	segments = 60;

	map_amplitude = 12.0;
}

void HeightMap::update()
{
	vec3 cam_pos = core::renderer.cam.getPos();

	int chunk_pos_x = floorf(cam_pos.x / chunk_size) * chunk_size;
	int chunk_pos_z = floorf(cam_pos.z / chunk_size) * chunk_size;


	bool chunk_exists = false;

	for (int i = 0; i < chunks.size(); i++)
	{
		if (chunk_pos_x == chunks[i].position.x && chunk_pos_z == chunks[i].position.z)
		{
			chunk_exists = true;
			break;
		}
	}

	if (chunk_exists == false)
		create_chunk(vec3(chunk_pos_x,0, chunk_pos_z));
}

void HeightMap::render(Shader * shader)
{
	int MvpID = glGetUniformLocation(shader->getID(), "MVP");

	glm::mat4 vp = core::renderer.cam.getViewProj();

	for (int i = 0; i < chunks.size(); i++)
	{
		glm::mat4 model_mat = glm::mat4(1.0f);

		model_mat = glm::translate(model_mat, chunks[i].position);

		glm::mat4 mvp = core::renderer.cam.getViewProj() * model_mat;

		glUniformMatrix4fv(MvpID, 1, GL_FALSE, &mvp[0][0]);

		glBindVertexArray(chunks[i].vao);

		glDrawElements(GL_TRIANGLES,chunks[i].indices,GL_UNSIGNED_INT,(void*)0);
	}
}
