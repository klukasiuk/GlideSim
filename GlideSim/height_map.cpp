#include "height_map.h"

#include "core.h"

vector<int> HeightMap::find_neighbours(vec3 chunk_pos)
{
	vector<int> neighbours;

	for (int a = 0; a < chunks.size(); a++)
	{
		float distance;


		vec3 dir = chunks[a].position - chunk_pos;

		distance = glm::length(dir);

		if (fabs(distance - chunk_size) > 0.01)
			continue;

		neighbours.push_back(a);
	}

	return neighbours;
}

void HeightMap::create_chunk(vec3 pos)
{
	Chunk new_chunk;

	new_chunk.position = pos;

	vector<vec3> vertices;
	vector<vec3> normals;
	vector<vec3> colors;
	vector<unsigned int> indices;

	float step = chunk_size / segments;

	for (int x = 0; x < segments + 1; x++)
	{
		for (int z = 0; z < segments + 1; z++)
		{
			float amplitude = ((float)rand() / RAND_MAX) * map_amplitude - map_amplitude*0.5f;

			vertices.push_back(vec3(x*step, amplitude, z*step));

			vec3 color = vec3(13.0/255, 181.0/255, 55.0/255);

			//vec3 color = vec3(1, 0, 0) * (amplitude / map_amplitude) + vec3(0, 1, 0)*(1.0f - amplitude / map_amplitude);

			colors.push_back(color);
		}
	}

	vector<int> neighbours = find_neighbours(pos);

	for (int i = 0; i < neighbours.size(); i++)
	{
		int id = neighbours[i];

		vec3 dir = chunks[id].position - pos;

		dir = glm::normalize(dir);

		if ((int)dir.x == 1)
		{
			for (int i = 0; i < segments + 1; i++)
			{
				vertices[(segments + 1)*(segments)+i].y = chunks[id].border_down[i];
			}
		}

		if ((int)dir.x == -1)
		{
			for (int i = 0; i < segments + 1; i++)
			{
				vertices[i].y = chunks[id].border_top[i];
			}
		}

		if ((int)dir.z == -1)
		{
			for (int i = 0; i < segments + 1; i++)
			{
				vertices[(segments + 1) * i].y = chunks[id].border_right[i];
			}
		}

		if ((int)dir.z == 1)
		{
			for (int i = 0; i < segments + 1; i++)
			{
				vertices[(segments + 1) * i + (segments)].y = chunks[id].border_left[i];
			}
		}
	}

	for (int i = 0; i < (segments + 1); i++)
	{
		new_chunk.border_top.push_back(vertices[(segments + 1)*(segments) + i].y);
	}

	for (int i = 0; i < (segments + 1); i++)
	{
		new_chunk.border_down.push_back(vertices[i].y);
	}

	for (int i = 0; i < (segments + 1); i++)
	{
		new_chunk.border_left.push_back(vertices[(segments + 1) * i].y);
	}

	for (int i = 0; i < (segments + 1); i++)
	{
		new_chunk.border_right.push_back(vertices[(segments + 1) * i + (segments)].y);
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

	for (unsigned int i = 0; i < indices.size() / 3; i++)
	{
		vec3 v1 = vertices[indices[i*3 + 0]];
		vec3 v2 = vertices[indices[i*3 + 1]];
		vec3 v3 = vertices[indices[i*3 + 2]];

		vec3 edge1 = v2 - v1;
		vec3 edge2 = v3 - v1;

		vec3 normal = cross(edge1, edge2);
		normal = normalize(normal);

		normals.push_back(normal);
	}

	new_chunk.indices = indices.size();

	glGenVertexArrays(1, &new_chunk.vao);
	glBindVertexArray(new_chunk.vao);

	glGenBuffers(1, &new_chunk.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, new_chunk.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &new_chunk.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, new_chunk.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &new_chunk.normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, new_chunk.normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &new_chunk.color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, new_chunk.color_buffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, new_chunk.vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, new_chunk.normal_buffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, new_chunk.color_buffer);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	chunks.push_back(new_chunk);
}

bool HeightMap::check_if_chunk_exist(vec3 pos)
{
	int chunk_pos_x = (int)(floorf(pos.x / chunk_size) * chunk_size);
	int chunk_pos_z = (int)(floorf(pos.z / chunk_size) * chunk_size);


	for (unsigned int i = 0; i < chunks.size(); i++)
	{
		if (chunk_pos_x == chunks[i].position.x && chunk_pos_z == chunks[i].position.z)
		{
			return true;
		}
	}

	return false;
}


HeightMap::HeightMap()
{
	chunk_size = 200;

	segments = 50;

	map_amplitude = 8.0;
}

void HeightMap::update()
{
	vec3 cam_pos = core::camera.getPos();

	int chunk_pos_x = (int)(floorf(cam_pos.x / chunk_size) * chunk_size);
	int chunk_pos_z = (int)(floorf(cam_pos.z / chunk_size) * chunk_size);

	for (int x = -3; x < 4; x++)
	for (int z = -3; z < 4; z++)
	{
		vec3 new_chunk_pos = vec3(chunk_pos_x + x*chunk_size, 0, chunk_pos_z + z*chunk_size);

		if (check_if_chunk_exist(new_chunk_pos) == false)
		{
			create_chunk(new_chunk_pos);

		}
	}
}

void HeightMap::render(Shader * shader)
{
	glm::mat4 vp = core::camera.getViewProj();

	for (unsigned int i = 0; i < chunks.size(); i++)
	{
		glm::mat4 model_mat = glm::mat4(1.0f);

		model_mat = glm::translate(model_mat, chunks[i].position);

		shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		shader->setVec3("lightPos", core::renderer.pointLight.position);

		glm::mat4 MVP = core::camera.getProj() * core::camera.getView() * model_mat;

		shader->setMat4("M", model_mat);
		shader->setMat4("V", core::camera.getView());
		shader->setMat4("MVP", MVP);

		glBindVertexArray(chunks[i].vao);

		glDrawElements(GL_TRIANGLES,chunks[i].indices,GL_UNSIGNED_INT,(void*)0);
	}
}
