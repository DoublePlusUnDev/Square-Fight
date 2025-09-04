<<<<<<< HEAD
#include "mapmanager.h"

#ifndef CPORTA
#include <SDL3/SDL.h>
#include "wall.h"
#endif // CPORTA

#include <algorithm>

#ifndef CPORTA
#include <filesystem>
#else
#include <dirent.h>
#endif

#include <fstream>
#include <string>
#include <stdexcept>

#include "memtrace.h"

MapManager::MapElement::MapElement(const Vector2& position, const Vector2& scale, const Color& color, const bool deadly, const double bounciness, const Vector2& colliderRatio)
: position(position), scale(scale), color(color), deadly(deadly), bounciness(bounciness), colliderRatio(colliderRatio)
{

}

void MapManager::Map::addElement(const Vector2& position, const Vector2& scale, const Color& color, const bool deadly, const double bounciness, const Vector2& colliderRatio)
{
    elements.push_back(MapElement(position, scale, color, deadly, bounciness, colliderRatio));
}

MapManager::MapManager()
: mapCache(), mapInstance(), loadedMapId(0)
{
    #ifndef CPORTA
    for(auto& p : std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        std::string filename = p.path().filename().string();
        std::string extension = p.path().extension().string();

        std::transform(extension.begin(), extension.end(), extension.begin(), [](char c) -> char { return std::tolower(c, std::locale()); });

        if (extension != ".gamemap")
            continue;

        std::ifstream file(filename);
        if (!file.is_open())
        {
            #ifndef CPORTA
            SDL_Log("MapManager: Failed to open file: %s", filename.c_str());
            #endif
            continue;
        }
    #else
    for (const std::string& filename : getGamemapFiles())
    {
        std::ifstream file(filename);
        if (!file.is_open()) 
        {
            #ifndef CPORTA
            SDL_Log("MapManager: Failed to open file: %s", filename.c_str());
            #endif
            continue;
        }
    #endif

        Map map = Map();
        
        //map height
        double mapHeight;
        file >> mapHeight;
        map.mapHeight = mapHeight;

        //map background color
        //Color backgroundColor;
        int backgroundR, backgroundG, backgroundB;
        file >> backgroundR >> backgroundG >> backgroundB;
        map.backgroundColor = makeColor(backgroundR, backgroundG, backgroundB);
        
        //score to win
        int scoreToWin;
        file >> scoreToWin;
        map.scoreToWin = scoreToWin;

        //player positions
        double player1PosX, player1PosY;
        file >> player1PosX >> player1PosY;
        map.player1Position = {player1PosX, player1PosY};

        double player2PosX, player2PosY;
        file >> player2PosX >> player2PosY;
        map.player2Position = {player2PosX, player2PosY};
        
        //read map elements
        while (!file.eof() && !file.fail())
        {
            double x, y, sizeX, sizeY;
            int r, g, b;
            int deadly;
            double bounciness;
            double colliderRatioX, colliderRatioY;

            file >> x >> y >> sizeX >> sizeY >> r >> g >> b >> deadly >> bounciness >> colliderRatioX >> colliderRatioY;

            map.addElement({x, y}, {sizeX, sizeY}, makeColor(r, g, b), deadly, bounciness, {colliderRatioX, colliderRatioY});
        }

        mapCache.push_back(map);
        #ifndef CPORTA
        SDL_Log("MapManager: Loaded map from file: %s", filename.c_str());
        #endif // CPORTA
        file.close();
    }
}

MapManager::~MapManager()
{
    discardMap();
}

#ifdef CPORTA
std::vector<std::string> MapManager::getGamemapFiles() const
{
    std::vector<std::string> files;
    DIR* dir = opendir(".");
    if (!dir) return files;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        std::string name = entry->d_name;
        if (name.size() >= 8 && name.substr(name.size() - 8) == ".gamemap")
        {
            files.push_back(name);
        }
    }

    closedir(dir);
    return files;
}
#endif

#ifndef CPORTA
void MapManager::initializeMap(const Map& map)
{
    Renderer::setGameHeight(map.mapHeight);
    Renderer::setBackgroundColor(map.backgroundColor);

    for (MapElement element : map.elements)
    {
        Transform* wall;
        if (element.deadly)
            wall = new Wall(Transform(nullptr, element.position, element.scale), element.color, element.bounciness, element.colliderRatio, {ColliderTag::DEADLY});
        else
            wall = new Wall(Transform(nullptr, element.position, element.scale), element.color, element.bounciness, element.colliderRatio);
        mapInstance.push_back(wall);
    }
}
#endif

void MapManager::discardMap()
{
    for (Transform* transform : mapInstance)
    {
        delete transform;
    }
    mapInstance.clear();
}

size_t MapManager::getMapCount() const { return mapCache.size(); }

Vector2 MapManager::getPlayerPosition(const size_t playerId) const
{
    if (loadedMapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    if (playerId >= 2)
        throw std::out_of_range("player id out of range");

    if (playerId == 0)
        return mapCache[loadedMapId].player1Position;
    else
        return mapCache[loadedMapId].player2Position;
}

int MapManager::getScoreToWin() const
{
    if (loadedMapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    return mapCache[loadedMapId].scoreToWin;
}

double MapManager::getMapHeight() const
{
    if (loadedMapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    return mapCache[loadedMapId].mapHeight;
}

#ifndef CPORTA
void MapManager::loadMap(const size_t mapId) 
{
    discardMap();

    if (mapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    loadedMapId = mapId;
    initializeMap(mapCache[mapId]);
}
#endif

void MapManager::unloadMap()
{
    discardMap();
}

#ifdef CPORTA
std::string MapManager::getSerializedMapInfo(const size_t mapId)
{
    if (mapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    std::stringstream stream;

    Map map = mapCache[mapId];
    stream << map.mapHeight << " "
           << static_cast<int>(map.backgroundColor.r) << " "
           << static_cast<int>(map.backgroundColor.g) << " "
           << static_cast<int>(map.backgroundColor.b) << " "
           << map.scoreToWin << " "
           << map.player1Position.x << " "
           << map.player1Position.y << " "
           << map.player2Position.x << " "
           << map.player2Position.y;

    return stream.str();
}

std::string MapManager::getSerializedMapElement(const size_t mapId, const size_t elementId)
{
    if (mapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    if (elementId >= mapCache[mapId].elements.size())
        throw std::out_of_range("element id out of range");

    std::stringstream stream;

    MapElement element = mapCache[mapId].elements[elementId];
    stream << element.position.x << " " << element.position.y << " "
           << element.scale.x << " " << element.scale.y << " "
           << static_cast<int>(element.color.r) << " "
           << static_cast<int>(element.color.g) << " "
           << static_cast<int>(element.color.b) << " "
           << element.deadly << " "
           << element.bounciness << " "
           << element.colliderRatio.x << " "
           << element.colliderRatio.y;

    return stream.str();
}
=======
#include "mapmanager.h"

#ifndef CPORTA
#include <SDL3/SDL.h>
#include "wall.h"
#endif // CPORTA

#include <algorithm>

#ifndef CPORTA
#include <filesystem>
#else
#include <dirent.h>
#endif

#include <cstring>
#include <fstream>
#include <string>
#include <stdexcept>

#include "memtrace.h"

MapManager::MapElement::MapElement(const Vector2& position, const Vector2& scale, const Color& color, const bool deadly, const double bounciness, const Vector2& colliderRatio)
: position(position), scale(scale), color(color), deadly(deadly), bounciness(bounciness), colliderRatio(colliderRatio)
{

}

void MapManager::Map::addElement(const Vector2& position, const Vector2& scale, const Color& color, const bool deadly, const double bounciness, const Vector2& colliderRatio)
{
    elements.push_back(MapElement(position, scale, color, deadly, bounciness, colliderRatio));
}

MapManager::MapManager()
: mapCache(), mapInstance(), loadedMapId(0)
{
    #ifndef CPORTA
    //sort files by alphabetical order, because it's not guaranteed by the directory_iterator
    std::vector<std::filesystem::directory_entry> files;

    for (auto& p : std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        std::string filename = p.path().filename().string();
        std::string extension = p.path().extension().string();

        std::transform(extension.begin(), extension.end(), extension.begin(), [](char c) -> char { return std::tolower(c, std::locale()); });

        if (extension != ".gamemap")
            continue;

        files.push_back(p);
    }

    //the gamemap files get sorted based on ASCII alphabetical order
    std::sort(files.begin(), files.end(),
            [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b)
            {
                return a.path().string() < b.path().string();
            });

    for(auto& p : files)
    {
        std::string filename = p.path().filename().string();
        std::string extension = p.path().extension().string();
        
        std::transform(extension.begin(), extension.end(), extension.begin(), [](char c) -> char { return std::tolower(c, std::locale()); });

        if (extension != ".gamemap")
            continue;

        std::ifstream file(filename);
        if (!file.is_open())
        {
            #ifndef CPORTA
            SDL_Log("MapManager: Failed to open file: %s", filename.c_str());
            #endif
            continue;
        }
    #else
    std::vector<std::string> files = getGamemapFiles();

    std::sort(files.begin(), files.end());

    for (const std::string& filename : files)
    {
        std::ifstream file(filename);
        if (!file.is_open()) 
        {
            #ifndef CPORTA
            SDL_Log("MapManager: Failed to open file: %s", filename.c_str());
            #endif
            continue;
        }
    #endif

        Map map = Map();
        
        //map height
        double mapHeight;
        file >> mapHeight;
        map.mapHeight = mapHeight;

        //map background color
        //Color backgroundColor;
        int backgroundR, backgroundG, backgroundB;
        file >> backgroundR >> backgroundG >> backgroundB;
        map.backgroundColor = makeColor(backgroundR, backgroundG, backgroundB);
        
        //score to win
        int scoreToWin;
        file >> scoreToWin;
        map.scoreToWin = scoreToWin;

        //player positions
        double player1PosX, player1PosY;
        file >> player1PosX >> player1PosY;
        map.player1Position = {player1PosX, player1PosY};

        double player2PosX, player2PosY;
        file >> player2PosX >> player2PosY;
        map.player2Position = {player2PosX, player2PosY};
        
        //read map elements
        while (!file.eof() && !file.fail())
        {
            double x, y, sizeX, sizeY;
            int r, g, b;
            int deadly;
            double bounciness;
            double colliderRatioX, colliderRatioY;

            file >> x >> y >> sizeX >> sizeY >> r >> g >> b >> deadly >> bounciness >> colliderRatioX >> colliderRatioY;

            map.addElement({x, y}, {sizeX, sizeY}, makeColor(r, g, b), deadly, bounciness, {colliderRatioX, colliderRatioY});
        }

        mapCache.push_back(map);
        #ifndef CPORTA
        SDL_Log("MapManager: Loaded map from file: %s", filename.c_str());
        #endif // CPORTA
        file.close();
    }
}

MapManager::~MapManager()
{
    discardMap();
}

#ifdef CPORTA
std::vector<std::string> MapManager::getGamemapFiles() const
{
    std::vector<std::string> files;
    DIR* dir = opendir(".");
    if (!dir) return files;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        std::string name = entry->d_name;
        if (name.size() >= 8 && name.substr(name.size() - 8) == ".gamemap")
        {
            files.push_back(name);
        }
    }

    closedir(dir);
    return files;
}
#endif

#ifndef CPORTA
void MapManager::initializeMap(const Map& map)
{
    Renderer::setGameHeight(map.mapHeight);
    Renderer::setBackgroundColor(map.backgroundColor);

    for (MapElement element : map.elements)
    {
        Transform* wall;
        if (element.deadly)
            wall = new Wall(Transform(nullptr, element.position, element.scale), element.color, element.bounciness, element.colliderRatio, {ColliderTag::DEADLY});
        else
            wall = new Wall(Transform(nullptr, element.position, element.scale), element.color, element.bounciness, element.colliderRatio);
        mapInstance.push_back(wall);
    }
}
#endif

void MapManager::discardMap()
{
    for (Transform* transform : mapInstance)
    {
        delete transform;
    }
    mapInstance.clear();
}

size_t MapManager::getMapCount() const { return mapCache.size(); }

Vector2 MapManager::getPlayerPosition(const size_t playerId) const
{
    if (loadedMapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    if (playerId >= 2)
        throw std::out_of_range("player id out of range");

    if (playerId == 0)
        return mapCache[loadedMapId].player1Position;
    else
        return mapCache[loadedMapId].player2Position;
}

int MapManager::getScoreToWin() const
{
    if (loadedMapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    return mapCache[loadedMapId].scoreToWin;
}

double MapManager::getMapHeight() const
{
    if (loadedMapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    return mapCache[loadedMapId].mapHeight;
}

#ifndef CPORTA
void MapManager::loadMap(const size_t mapId) 
{
    discardMap();

    if (mapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    loadedMapId = mapId;
    initializeMap(mapCache[mapId]);
}
#endif

void MapManager::unloadMap()
{
    discardMap();
}

#ifdef CPORTA
std::string MapManager::getSerializedMapInfo(const size_t mapId)
{
    if (mapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    std::stringstream stream;

    Map map = mapCache[mapId];
    stream << map.mapHeight << " "
           << static_cast<int>(map.backgroundColor.r) << " "
           << static_cast<int>(map.backgroundColor.g) << " "
           << static_cast<int>(map.backgroundColor.b) << " "
           << map.scoreToWin << " "
           << map.player1Position.x << " "
           << map.player1Position.y << " "
           << map.player2Position.x << " "
           << map.player2Position.y;

    return stream.str();
}

std::string MapManager::getSerializedMapElement(const size_t mapId, const size_t elementId)
{
    if (mapId >= getMapCount())
        throw std::out_of_range("map id out of range");

    if (elementId >= mapCache[mapId].elements.size())
        throw std::out_of_range("element id out of range");

    std::stringstream stream;

    MapElement element = mapCache[mapId].elements[elementId];
    stream << element.position.x << " " << element.position.y << " "
           << element.scale.x << " " << element.scale.y << " "
           << static_cast<int>(element.color.r) << " "
           << static_cast<int>(element.color.g) << " "
           << static_cast<int>(element.color.b) << " "
           << element.deadly << " "
           << element.bounciness << " "
           << element.colliderRatio.x << " "
           << element.colliderRatio.y;

    return stream.str();
}
>>>>>>> a04c523 (Idk :3)
#endif