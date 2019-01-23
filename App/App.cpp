//
// Created by Kringle on 25/10/2018.
//

#include "App.h"
#include "AI.h"
App::App()
{
    sf::RenderWindow window;
    unitCount = 0;



    mapCopyObjects();
    gameRun = false;
    nowhere = new Nowhere(map);
    if(!entity_buffer.loadFromFile("MusicAndSound/Sound/DeathSound.wav"))
    {
        std::cout << "Failed to load sound" << std::endl;
    }

}
void App::deleteInstance()
{

    while(!Objects.empty())
    {
        auto last = Objects.back();
        Objects.pop_back();
        delete(last);
        last = nullptr;
    }

    Spaces.clear();
    Nodes.clear();
     while(!Entities.empty())
    {
        Entities.pop_back();
    }while(!Interfaces.empty())
    {
        auto last = Interfaces.back();
        Interfaces.pop_back();
        delete(last);
        last = nullptr;
    }while(!Teams.empty())
    {
        auto last = Teams.back();
        Teams.pop_back();
        delete(last);
        last = nullptr;
    }
    while(!Buttons.empty())
    {
        auto last = Buttons.back();
        Buttons.pop_back();
        delete(last);
        last = nullptr;
    }
    spawns.clear();
    Unit::Types.clear();
    Building::Types.clear();
    Upgrade::Types.clear();
    Ability::Abilities.clear();
    vertices.clear();
    paths.clear();
    unitCount = 0;
    Object::ResetId();
    Entity::ResetId();
    Space::ResetId();
    Team::ResetId();
    pathid.resetIds();

}
void App::makeMap()
{
    std::string filename = "res/Maps.json";
    Json::Reader reader;
    Json::Value root;

    std::ifstream file(filename);

    bool parsingSuccessful = reader.parse(file, root);

    int c = root["choice"].asInt();
    if(!parsingSuccessful)
        std::cerr << "failed to load world data";

    for(Json::Value& n: root["map"][c]["nodes"])
        CreateNode(n);

    for(Json::Value& l: root["map"][c]["lanes"])
        CreateLane(l);

    Routing();

    for(Json::Value& s: root["map"][c]["spawns"])
        spawns.push_back(s.asInt());
    std::vector<int> vec;
}
void App::Routing()
{
    for(auto n: Nodes)
    {
        auto nodeVertex = new pth::pathVertex(n->pos(),50, n->SId(), 0);
        vertices.push_back(*nodeVertex);
        n->NodeVertex(*nodeVertex);

        for(auto v: n->getNeighboors())
        {

            vertices.emplace_back(v.second,GetSpace(v.first-1)->Width(), n->SId(), v.first);
        }

    }
    //second pass to connect vertices
    for(auto& t: vertices)
    {
        for(auto n: vertices)
        {
            if(t == n)
                continue;
            if(t.nodeId != n.nodeId && t.laneId != n.laneId )
                continue;
            if(t.laneId == 0 && n.laneId == 0)
                continue;
            sf::Vector2f path = t.pos - n.pos;
            sf::Vector2f norm;
            sf::Vector2f perp;
            sf::Vector2f a, b;

            float len = thor::length(path);
            t.width = 20;

            norm    = path/len;

            perp.x = -norm.y;
            perp.y =  norm.x;
            sf::Vector2f adj = perp * 20.0f;
            a = n.pos + adj;
            b = n.pos - adj;
            t.boundaries[n.Id] = {a,b,norm,perp};
        }
    }
    //Establish routes
    for(auto nStart: Nodes)
    {
        for(auto nEnd: Nodes)
        {
            if(nStart == nEnd)
                continue;
            pf pathfinder(vertices);

            std::vector<int> intPath = pathfinder.findPath(nStart->NodeVertex().Id,nEnd->NodeVertex().Id);

            pth::Path newPath(intPath, vertices);
            paths[nStart->SId()][nEnd->SId()] = std::move(newPath);
        }
    }

}
void App::CreateNode(Json::Value& val)
{
    sf::Vector2f pos = {val[0].asFloat(),val[1].asFloat()};
    int size = val[2].asInt();
    auto node = new Node(pos, size, map);
    Objects.push_back(node);
    Nodes.push_back(node);
    Spaces.push_back(node);
}
void App::CreateLane(Json::Value& val)
{
    Node& node1 = *Nodes[val[0].asInt()];
    Node& node2 = *Nodes[val[1].asInt()];
    int width = val[2].asInt();
    float rot, length, x_diff, y_diff;
    sf::Vector2f n1pos, n2pos;

    x_diff  = node2.X_pos() - node1.X_pos();
    y_diff  = node2.Y_pos() - node1.Y_pos();
    length = (int)sqrt(pow(x_diff,2)+pow(y_diff,2))- node1.Radius() - node2.Radius();
    rot = atan2(y_diff,x_diff);
    auto rotCos = cos(rot);
    auto rotSin = sin(rot);

    n1pos = {node1.X_pos()+rotCos* node1.Radius(),node1.Y_pos()+rotSin* node1.Radius()};
    n2pos = {node2.X_pos()-rotCos* node2.Radius(),node2.Y_pos()-rotSin* node2.Radius()};

    Lane* lane = new Lane(n1pos, width, map);

    Objects.push_back(lane);
    Spaces.push_back(lane);

    lane->Attach_Space(node1.SId(),n1pos);
    lane->Attach_Space(node2.SId(),n2pos);

    node1.Attach_Space(lane->SId(), n1pos);
    node2.Attach_Space(lane->SId(), n2pos);

    node1.Neighbours(&node2);
    node2.Neighbours(&node1);
}

void App::ImportUnit()//Imported from Json
{
    std::string filename = "res/Units.json";
    Json::Reader reader;
    Json::Value root;

    std::ifstream file(filename);

    bool parsingSuccessful = reader.parse(file, root);

    if(!parsingSuccessful)
        std::cerr << "failed to load units";
    int i= 0;
    for(Json::Value& u :root["units"])
    {
        Unit_t u_t = u;
        u_t.type_Id = i;
        Unit::Types[i] = u_t;
        i++;
    }

}
void App::ImportBuilding()//Imported from Json
{
    std::string filename = "res/Units.json";
    Json::Reader reader;
    Json::Value root;

    std::ifstream file(filename);

    bool parsingSuccessful = reader.parse(file, root);

    if(!parsingSuccessful)
        std::cerr << "failed to load buildings";


    for(Json::Value b :root["buildings"])
    {
        Building::Types[b["Id"].asInt()] = b;
    }

}
void App::ImportAbility()//Imported from Json
{
    std::string filename = "res/Effects.json";
    Json::Reader reader;
    Json::Value root;

    std::ifstream file(filename);

    bool parsingSuccessful = reader.parse(file, root);

    if(!parsingSuccessful)
        std::cerr << "failed to load buildings";


    for(Json::Value a :root["abilities"])
    {
        Ability::Abilities[a["Id"].asInt()] = a;
    }

}
void App::ImportUpgrade()//Imported from Json
{
    std::string filename = "res/Effects.json";
    Json::Reader reader;
    Json::Value root;

    std::ifstream file(filename);

    bool parsingSuccessful = reader.parse(file, root);

    if(!parsingSuccessful)
        std::cerr << "failed to load buildings";


    for(Json::Value u :root["upgrades"])
    {
        Upgrade::Types[u["Id"].asInt()] = u;
    }

}

void App::CreateTeam()
{

    auto team = new Team(100, 1, spawns[0], *this);
    Teams.push_back(team);
    std::cout << "Team" << team->GetId() << " Spawn:" << team->GetSpawn()->SId() << std::endl;

    int i = 0;
    for(auto b_t :Building::Types)
    {
        if (b_t.first == 0)
            continue;
        team->CreateButton(b_t,38, 38, 1.0f,b_t.second.color, team->uiset[i].x, team->uiset[i].y, team->keys[i]);
        i++;
    }
    i = 0;
    auto ai = new AI(100, 1, spawns[1], *this);
    for(auto b_t :Building::Types)
    {

        if (b_t.first == 0)
            continue;
        ai->CreateButton(b_t,38, 38, 1.0f,b_t.second.color, 0, 0,  sf::Keyboard::Unknown);
        i++;
    }
    Teams.push_back(ai);
    std::cout << "Team " << ai->GetId() << " Spawn:" << ai->GetSpawn()->SId() << std::endl;

}




void App::CreateButton(sf::Vector2f pos, int x_size, int y_size, sf::Color color, std::string texture)
{
    auto button = new ButtonTexture(pos, x_size, y_size, color, std::move(texture), map);
    Buttons.push_back(button);
}

void App::mapTick(sf::RenderWindow &window, std::list<std::shared_ptr<Object>> &objects, float deltaTime)
{
    for (auto& mapObject: mapObjects)
    {
        mapObject->process(deltaTime);
        mapObject->draw(window);
    }
}

void App::mapCopyObjects()
{
    std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(mapObjects));
    std::copy(map.getSprites().begin(), map.getSprites().end(), std::back_inserter(mapObjects));
}