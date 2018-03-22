#include "OBJLoader.h"


std::vector<Mesh>			OBJLoader::LoadedMeshes;
std::vector<Vertex>			OBJLoader::LoadedVertices;
std::vector<unsigned int>	OBJLoader::LoadedIndices;
std::vector<Material>		OBJLoader::LoadedMaterials;

void OBJLoader::split(const std::string & in, std::vector<std::string>& out, std::string token)
{
	out.clear();

	std::string temp;

	for (int i = 0; i < int(in.size()); i++)
	{
		std::string test = in.substr(i, token.size());

		if (test == token)
		{
			if (!temp.empty())
			{
				out.push_back(temp);
				temp.clear();
				i += (int)token.size() - 1;
			}
			else
			{
				out.push_back("");
			}
		}
		else if (i + token.size() >= in.size())
		{
			temp += in.substr(i, token.size());
			out.push_back(temp);
			break;
		}
		else
		{
			temp += in[i];
		}
	}
}

std::string OBJLoader::tail(const std::string & in)
{
	size_t token_start = in.find_first_not_of(" \t");
	size_t space_start = in.find_first_of(" \t", token_start);
	size_t tail_start = in.find_first_not_of(" \t", space_start);
	size_t tail_end = in.find_last_not_of(" \t");
	if (tail_start != std::string::npos && tail_end != std::string::npos)
	{
		return in.substr(tail_start, tail_end - tail_start + 1);
	}
	else if (tail_start != std::string::npos)
	{
		return in.substr(tail_start);
	}
	return "";
}

std::string OBJLoader::firstToken(const std::string & in)
{
	if (!in.empty())
	{
		size_t token_start = in.find_first_not_of(" \t");
		size_t token_end = in.find_first_of(" \t", token_start);
		if (token_start != std::string::npos && token_end != std::string::npos)
		{
			return in.substr(token_start, token_end - token_start);
		}
		else if (token_start != std::string::npos)
		{
			return in.substr(token_start);
		}
	}
	return "";
}

bool OBJLoader::LoadMaterials(std::string path)
{
	// If the file is not a material file return false
	if (path.substr(path.size() - 4, path.size()) != ".mtl")
		return false;

	std::ifstream file(path);

	if (!file.is_open())
		return false;

	Material tempMaterial;

	bool listening = false;

	std::string line;
	while (std::getline(file, line)) 
	{
		if (firstToken(line) == "newmtl") {
			if (!listening)
			{
				listening = true;

				if (line.size() > 7) {
					tempMaterial.name = tail(line);
				}
				else
				{
					tempMaterial.name = "none";
				}
			}
			else
			{
				// Generate the material

				// Push Back loaded Material
				LoadedMaterials.push_back(tempMaterial);

				// Clear Loaded Material
				tempMaterial = Material();

				if (line.size() > 7)
				{
					tempMaterial.name = tail(line);
				}
				else
				{
					tempMaterial.name = "none";
				}
			}
		}

		//Ambient Colour
		if (firstToken(line) == "Ka") {
			std::vector<std::string> temp;
			split(tail(line), temp, " ");

			if (temp.size() != 3)
				continue;

			tempMaterial.ambientColour.r = std::stof(temp[0]);
			tempMaterial.ambientColour.g = std::stof(temp[1]);
			tempMaterial.ambientColour.b = std::stof(temp[2]);
		}

		//Diffuse Colour
		if (firstToken(line) == "Kd") {
			std::vector<std::string> temp;
			split(tail(line), temp, " ");

			if (temp.size() != 3)
				continue;

			tempMaterial.diffuseColour.r = std::stof(temp[0]);
			tempMaterial.diffuseColour.g = std::stof(temp[1]);
			tempMaterial.diffuseColour.b = std::stof(temp[2]);
		}

		//Specular Colour
		if (firstToken(line) == "Ks") {
			std::vector<std::string> temp;
			split(tail(line), temp, " ");

			if (temp.size() != 3)
				continue;

			tempMaterial.specularColour.r = std::stof(temp[0]);
			tempMaterial.specularColour.g = std::stof(temp[1]);
			tempMaterial.specularColour.b = std::stof(temp[2]);
		}

		//Dissolve
		if (firstToken(line) == "d") {
			tempMaterial.dissolve = std::stof(tail(line));
		}

		if (firstToken(line) == "illum") {
			tempMaterial.illum = std::stoi(tail(line));
		}

		if (firstToken(line) == "map_Ka") {
			tempMaterial.ambientTexName = tail(line);
		}
		if (firstToken(line) == "map_Kd") {
			tempMaterial.diffuseTexName = tail(line);
		}

		if (firstToken(line) == "map_Bump" || firstToken(line) == "map_bump" || firstToken(line) == "bump") {
			tempMaterial.bumpMapName = tail(line);
		}

	}

	// Push Back loaded Material
	LoadedMaterials.push_back(tempMaterial);

	// Test to see if anything was loaded
	// If not return false
	if (LoadedMaterials.empty())
		return false;
	// If so return true
	else
		return true;

}

void OBJLoader::GenVerticesFromRawOBJ(std::vector<Vertex>& oVerts, const std::vector<glm::vec3>& iPositions, const std::vector<glm::vec2>& iTCoords, const std::vector<glm::vec3>& iNormals, std::string icurline)
{
	std::vector<std::string> sface, svert;
	Vertex vVert;
	split(tail(icurline), sface, " ");

	bool noNormal = false;

	// For every given vertex do this
	for (int i = 0; i < int(sface.size()); i++)
	{
		// See What type the vertex is.
		int vtype;

		split(sface[i], svert, "/");

		// Check for just position - v1
		if (svert.size() == 1)
		{
			// Only position
			vtype = 1;
		}

		// Check for position & texture - v1/vt1
		if (svert.size() == 2)
		{
			// Position & Texture
			vtype = 2;
		}

		// Check for Position, Texture and Normal - v1/vt1/vn1
		// or if Position and Normal - v1//vn1
		if (svert.size() == 3)
		{
			if (svert[1] != "")
			{
				// Position, Texture, and Normal
				vtype = 4;
			}
			else
			{
				// Position & Normal
				vtype = 3;
			}
		}

		// Calculate and store the vertex
		switch (vtype)
		{
		case 1: // P
		{
			vVert.position = getElement(iPositions, svert[0]);
			vVert.uv = glm::vec2(0, 0);
			noNormal = true;
			oVerts.push_back(vVert);
			break;
		}
		case 2: // P/T
		{
			vVert.position = getElement(iPositions, svert[0]);
			vVert.uv = getElement(iTCoords, svert[1]);
			noNormal = true;
			oVerts.push_back(vVert);
			break;
		}
		case 3: // P//N
		{
			vVert.position = getElement(iPositions, svert[0]);
			vVert.uv = glm::vec2(0, 0);
			vVert.normal = getElement(iNormals, svert[2]);
			oVerts.push_back(vVert);
			break;
		}
		case 4: // P/T/N
		{
			vVert.position = getElement(iPositions, svert[0]);
			vVert.uv = getElement(iTCoords, svert[1]);
			vVert.normal = getElement(iNormals, svert[2]);
			oVerts.push_back(vVert);
			break;
		}
		default:
		{
			break;
		}
		}
	}

	// take care of missing normals
	// these may not be truly acurate but it is the 
	// best they get for not compiling a mesh with normals	
	if (noNormal)
	{
		glm::vec3 A = oVerts[0].position - oVerts[1].position;
		glm::vec3 B = oVerts[2].position - oVerts[1].position;

		glm::vec3 normal = glm::cross(A, B);

		for (int i = 0; i < int(oVerts.size()); i++)
		{
			oVerts[i].normal = normal;
		}
	}
}

float OBJLoader::angleBetween2Vec(const glm::vec3 a, const glm::vec3 b)
{
	float angle = glm::dot(a,b);
	angle /= (a.length() * b.length());
	return angle = acosf(angle);
}

bool OBJLoader::inTriangle(glm::vec3 point, glm::vec3 tri1, glm::vec3 tri2, glm::vec3 tri3)
{
	// Starting vars
	glm::vec3 u = tri2 - tri1;
	glm::vec3 v = tri3 - tri1;
	glm::vec3 w = point - tri1;
	glm::vec3 n = glm::cross(u, v);

	float y = (glm::dot(glm::cross(u, w), n) / glm::dot(n, n));
	float b = (glm::dot(glm::cross(u, w), n) / glm::dot(n, n));
	float a = 1 - y - b;

	// Projected point
	glm::vec3  p = (a * tri1) + (b * tri2) + (y * tri3);

	if (a >= 0 && a <= 1
		&& b >= 0 && b <= 1
		&& y >= 0 && y <= 1)
	{
		return true;
	}
	else
		return false;
}

void OBJLoader::VertexTriangluation(std::vector<unsigned int>& oIndices, const std::vector<Vertex>& iVerts)
{
	// If there are 2 or less verts,
	// no triangle can be created,
	// so exit
	if (iVerts.size() < 3)
	{
		return;
	}
	// If it is a triangle no need to calculate it
	if (iVerts.size() == 3)
	{
		oIndices.push_back(0);
		oIndices.push_back(1);
		oIndices.push_back(2);
		return;
	}

	// Create a list of vertices
	std::vector<Vertex> tVerts = iVerts;

	while (true)
	{
		// For every vertex
		for (int i = 0; i < int(tVerts.size()); i++)
		{
			// pPrev = the previous vertex in the list
			Vertex pPrev;
			if (i == 0)
			{
				pPrev = tVerts[tVerts.size() - 1];
			}
			else
			{
				pPrev = tVerts[i - 1];
			}

			// pCur = the current vertex;
			Vertex pCur = tVerts[i];

			// pNext = the next vertex in the list
			Vertex pNext;
			if (i == tVerts.size() - 1)
			{
				pNext = tVerts[0];
			}
			else
			{
				pNext = tVerts[i + 1];
			}

			// Check to see if there are only 3 verts left
			// if so this is the last triangle
			if (tVerts.size() == 3)
			{
				// Create a triangle from pCur, pPrev, pNext
				for (int j = 0; j < int(tVerts.size()); j++)
				{
					if (iVerts[j].position == pCur.position)
						oIndices.push_back(j);
					if (iVerts[j].position == pPrev.position)
						oIndices.push_back(j);
					if (iVerts[j].position == pNext.position)
						oIndices.push_back(j);
				}

				tVerts.clear();
				break;
			}
			if (tVerts.size() == 4)
			{
				// Create a triangle from pCur, pPrev, pNext
				for (int j = 0; j < int(iVerts.size()); j++)
				{
					if (iVerts[j].position == pCur.position)
						oIndices.push_back(j);
					if (iVerts[j].position == pPrev.position)
						oIndices.push_back(j);
					if (iVerts[j].position == pNext.position)
						oIndices.push_back(j);
				}

				glm::vec3 tempVec;
				for (int j = 0; j < int(tVerts.size()); j++)
				{
					if (tVerts[j].position != pCur.position
						&& tVerts[j].position != pPrev.position
						&& tVerts[j].position != pNext.position)
					{
						tempVec = tVerts[j].position;
						break;
					}
				}

				// Create a triangle from pCur, pPrev, pNext
				for (int j = 0; j < int(iVerts.size()); j++)
				{
					if (iVerts[j].position == pPrev.position)
						oIndices.push_back(j);
					if (iVerts[j].position == pNext.position)
						oIndices.push_back(j);
					if (iVerts[j].position == tempVec)
						oIndices.push_back(j);
				}

				tVerts.clear();
				break;
			}

			// If Vertex is not an interior vertex
			float angle = angleBetween2Vec(pPrev.position - pCur.position, pNext.position - pCur.position) * (180 / 3.14159265359);
			if (angle <= 0 && angle >= 180)
				continue;

			// If any vertices are within this triangle
			bool inTri = false;
			for (int j = 0; j < int(iVerts.size()); j++)
			{
				if (inTriangle(iVerts[j].position, pPrev.position, pCur.position, pNext.position)
					&& iVerts[j].position != pPrev.position
					&& iVerts[j].position != pCur.position
					&& iVerts[j].position != pNext.position)
				{
					inTri = true;
					break;
				}
			}
			if (inTri)
				continue;

			// Create a triangle from pCur, pPrev, pNext
			for (int j = 0; j < int(iVerts.size()); j++)
			{
				if (iVerts[j].position == pCur.position)
					oIndices.push_back(j);
				if (iVerts[j].position == pPrev.position)
					oIndices.push_back(j);
				if (iVerts[j].position == pNext.position)
					oIndices.push_back(j);
			}

			// Delete pCur from the list
			for (int j = 0; j < int(tVerts.size()); j++)
			{
				if (tVerts[j].position == pCur.position)
				{
					tVerts.erase(tVerts.begin() + j);
					break;
				}
			}

			// reset i to the start
			// -1 since loop will add 1 to it
			i = -1;
		}

		// if no triangles were created
		if (oIndices.size() == 0)
			break;

		// if no more vertices
		if (tVerts.size() == 0)
			break;
	}
}

OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}

bool OBJLoader::LoadFile(std::string Path)
{
	if (Path.substr(Path.size() - 4, 4) != ".obj")
		return false;
	
	std::ifstream file(Path);

	if (!file.is_open())
		return false;

	LoadedMeshes.clear();
	LoadedVertices.clear();
	LoadedIndices.clear();

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::string> meshMatNames;

	bool listening = false;
	std::string meshName;

	Mesh tempMesh;

	std::string line;
	while (std::getline(file, line)) 
	{
		if (firstToken(line) == "o" || firstToken(line) == "g" || line[0] == 'g') {
			if (!listening) {
				listening = true;

				if (firstToken(line) == "o" || firstToken(line) == "g") {
					meshName = tail(line);
				}
				else
				{
					meshName = "Unnamed";
				}
			}
			else
			{
				//Generate Mesh
				if (!indices.empty() && !vertices.empty()) {
					tempMesh = Mesh(vertices, indices);
					tempMesh.name = meshName;

					LoadedMeshes.push_back(tempMesh);

					//Cleanup
					vertices.clear();
					indices.clear();
					meshName.clear();

					meshName = tail(line);
				}
				else
				{
					if (firstToken(line) == "o" || firstToken(line) == "g") {
						meshName = tail(line);
					}
					else
					{
						meshName = "Unnamed";
					}
				}
			}
		}

		if (firstToken(line) == "v") 
		{
			std::vector<std::string> strPos;
			glm::vec3 vecPos;
			split(tail(line), strPos, " ");

			vecPos.x = std::stof(strPos[0]);
			vecPos.y = std::stof(strPos[1]);
			vecPos.z = std::stof(strPos[2]);

			positions.push_back(vecPos);
		}

		if(firstToken(line) == "vt")
		{
			std::vector<std::string> stex;
			glm::vec2 vtex;
			split(tail(line), stex, " ");

			vtex.x = std::stof(stex[0]);
			vtex.y = std::stof(stex[1]);

			uvs.push_back(vtex);
		}
		if (firstToken(line) == "vn") {
			std::vector<std::string> snor;
			glm::vec3 vnor;
			split(tail(line), snor, " ");
			
			vnor.x = std::stof(snor[0]);
			vnor.y = std::stof(snor[1]);
			vnor.z = std::stof(snor[2]);

			normals.push_back(vnor);
		}
		if (firstToken(line) == "f") 
		{
			std::vector<Vertex> vVerts;
			GenVerticesFromRawOBJ(vVerts, positions, uvs, normals, line);

			// Add Vertices
			for (int i = 0; i < int(vVerts.size()); i++)
			{
				vertices.push_back(vVerts[i]);

				LoadedVertices.push_back(vVerts[i]);
			}

			std::vector<unsigned int> iIndices;

			VertexTriangluation(iIndices, vVerts);

			for (int i = 0; i < iIndices.size(); i++) {
				unsigned int indnum = (unsigned int)(vertices.size() - vVerts.size()) + iIndices[i];
				indices.push_back(indnum);

				indnum = (unsigned int)((LoadedVertices.size()) - vVerts.size()) + iIndices[i];
				LoadedIndices.push_back(indnum);
			}
		}

		//Get Mesh Material name
		if (firstToken(line) == "usemtl") {

			tempMesh = Mesh(vertices, indices);
			tempMesh.name = meshName;

			int i = 2;
			while (true)
			{
				tempMesh.name = meshName + "_" + std::to_string(i);

				for (auto &m : LoadedMeshes) {
					if (m.name == tempMesh.name) {
						continue;
					}
				}
				break;
			}

			// Insert Mesh
			LoadedMeshes.push_back(tempMesh);

			// Cleanup
			vertices.clear();
			indices.clear();
		}

		//Load Materials
		if (firstToken(line) == "mtllib") {

			//Generate path to the material file
			std::vector<std::string> temp;
			split(Path, temp, "/");

			std::string pathToMat = "";
			if (temp.size() != 1) {
				for (int i = 0; i < temp.size(); i++) {
					pathToMat += temp[i] + "/";
				}
			}

			pathToMat += tail(line);

			LoadMaterials(pathToMat);
		}
	}

	//Last Mesh
	if (!indices.empty() && !vertices.empty()) {

		tempMesh = Mesh(vertices, indices);
		tempMesh.name = meshName;

		LoadedMeshes.push_back(tempMesh);
	}
	file.close();

	//Set Materials for each mesh
	for (int i = 0; i < meshMatNames.size(); i++) {

		std::string matName = meshMatNames[i];

		for (int j = 0; j < LoadedMaterials.size(); j++) {
			if (LoadedMaterials[j].name == matName) {
				LoadedMeshes[i].meshMaterial = LoadedMaterials[j];
				break;
			}
		}
	}

	if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty()) {
		return false;
	}
	else
	{
		return true;
	}
}
