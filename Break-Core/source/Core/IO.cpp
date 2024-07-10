#include "Core/IO.h"
#include "Core/Base.h"
#include "Scene/Brick.h"

#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace Break::Core
{
    static std::unordered_map<std::string, Color> colors;

    void IO::Init()
    {
        srand(time(NULL));

        colors["Red"] = RED;
        colors["Orange"] = ORANGE;
        colors["Yellow"] = YELLOW;
        colors["Green"] = GREEN;
        colors["Blue"] = BLUE;
        colors["Purple"] = PURPLE;
    }

    MapFileData IO::ReadMapFile(const char* path)
    {
        MapFileData mapData;

        std::ifstream file(path);
        if (!file.is_open())
        {
            TraceLog(LOG_WARNING, "Failed to read %s!", path);
            return mapData;
        }

        std::string line;
        std::stringstream stream;
        while (std::getline(file, line))
        {
            if (line[0] == '#')
                continue;
            else if (line.find("Rows:") != std::string::npos)
            {
                std::string newLine = line.substr(6);
                mapData.numRows = std::stoi(newLine);
            }
            else if (line.find("Columns:") != std::string::npos)
            {
                std::string newLine = line.substr(9);
                mapData.numCols = std::stoi(newLine);
            }
            else if (line.find("Offset:") != std::string::npos)
            {
                std::string newLine = line.substr(8);
                std::stringstream offsetStream(newLine);
                std::string inputOffset[2];

                offsetStream >> inputOffset[0] >> inputOffset[1];
                mapData.offset = {std::stof(inputOffset[0]), std::stof(inputOffset[1])};
            }
            else if (line.find("Spacing:") != std::string::npos)
            {
                std::string newLine = line.substr(9);
                std::stringstream spacingStream(newLine);
                std::string inputSpacing[2];

                spacingStream >> inputSpacing[0] >> inputSpacing[1];
                mapData.spacing = {std::stof(inputSpacing[0]), std::stof(inputSpacing[1])};
            }
            else if (line.find("Colors:") != std::string::npos)
            {
                std::string newLine = line.substr(8);
                std::stringstream colorStream(newLine);
                std::string inputColors[BRICK_TYPE_COUNT];

                colorStream >> inputColors[0] >> inputColors[1] >> inputColors[2];

                for (u8 i = 0; i < BRICK_TYPE_COUNT; i++)
                    mapData.brickColors[i] = colors[inputColors[i]];
            }
            else
                stream << line;
        }

        mapData.data = stream.str();
        file.close();

        return mapData;
    }
}
