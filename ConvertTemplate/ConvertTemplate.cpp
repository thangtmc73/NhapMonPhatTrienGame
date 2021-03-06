// ConvertTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

int** readBackgroundFile(const char* a_filePath, int &mapArrayWidth, int &mapArrayHeight) {
	FILE *pFile = fopen(a_filePath, "r");

	if (pFile == NULL)
	{
		printf("Can't open background file!");
	}
	int **mapArray;
	fscanf(pFile, "%d %d", &mapArrayWidth, &mapArrayHeight);
	mapArray = new int*[mapArrayHeight];
	for (int i = 0; i < mapArrayHeight; i++)
	{
		mapArray[i] = new int[mapArrayWidth];
	}
	for (int i = 0; i < mapArrayHeight; i++)
	{
		for (int j = 0; j < mapArrayWidth; j++)
		{
			fscanf(pFile, "%d", &mapArray[i][j]);
			if (j == mapArrayWidth - 1)
			{
				fseek(pFile, 1, SEEK_CUR);
			}
		}
	}
	fclose(pFile);
	return mapArray;
}

void writeBackgroundFile(const char* a_filePath, int **mapArray, int mapArrayWidth, int mapArrayHeight) {
	FILE *pFile = fopen(a_filePath, "w");

	if (pFile == NULL)
	{
		printf("Can't open file!");
	}
	int start_x = 16;
	int start_y = 395;
	for (int i = 0; i < mapArrayHeight; i++)
	{
		for (int j = 0; j < mapArrayWidth; j++)
		{
			std::string temp = "<background x=\"" + std::to_string(start_x + 32 * j) + "\" y=\"" + std::to_string(start_y - (32 * i)) + "\" index=\"" + std::to_string(mapArray[i][j]) + "\" zIndex=\"0\" />\n";
			try {
				fputs(temp.c_str(), pFile);
			}
			catch (std::exception& e) {
				printf("ddd");
			}
		}
	}
	fclose(pFile);
}

void loadObjectFile(const char *a_fileInput, const char *a_fileOutput) {
	FILE *pFileInput = fopen(a_fileInput, "r");
	int numberGround, numberObject;

	if (pFileInput == NULL)
	{
		printf("Can't open input object file!");
		return;
	}

	FILE *pFileOutput = fopen(a_fileOutput, "w");
	fscanf(pFileInput, "%d %d", &numberGround, &numberObject);
	if (pFileOutput == NULL)
	{
		printf("Can't open output file!");
	}

	int n_objects, n_grounds, type, x, y, column, row, leftDirection;

	for (int i = 0; i < numberGround; i++) {
		fscanf(pFileInput, "%d %d %d %d %d", &x, &y, &type, &column, &row);
		std::string temp = "<ground x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) + "\" type=\"" + std::to_string(900 + type) + "\" cols=\"" + std::to_string(column) + "\" rows=\"" + std::to_string(row) + "\" zIndex=\"0\" />\n";

		fputs(temp.c_str(), pFileOutput);
	}

	for (int i = 0; i < numberObject; i++) {
		fscanf(pFileInput, "%d %d %d %d", &type, &x, &y, &leftDirection);
		std::string temp = "<object x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) + "\" type=\"" + std::to_string(type) + "\" left_direction=\"" + std::to_string(leftDirection) + "\" zIndex=\"0\" />\n";

		fputs(temp.c_str(), pFileOutput);
	}

	fclose(pFileInput);
	fclose(pFileOutput);
}

int main()
{
	int **map = NULL;
	int mapHeight, mapWidth;
	map = readBackgroundFile("Stage2_1BG.txt", mapWidth, mapHeight);
	writeBackgroundFile("Stage2_1BG.xml", map, mapWidth, mapHeight);
	loadObjectFile("Stage2_1GO.txt", "Stage2_1GO.xml");
    return 0;
}

