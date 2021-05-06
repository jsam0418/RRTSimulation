#include "controller.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <math.h>

controller::controller()
{

}

void controller::configure()
{
    QString text;
    QFile settings;
    settings.setFileName("../config/settings.json");
    settings.open(QIODevice::ReadOnly | QIODevice::Text);
    text = settings.readAll();
    settings.close();
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8());
    QJsonObject obj = doc.object();
    QJsonValue val = obj.value(QString("iterations"));
    iterations = val.toInt();
    val = obj.value(QString("width_cm"));
    width_cm = val.toDouble();
    val = obj.value(QString("height_cm"));
    height_cm = val.toDouble();
    val = obj.value(QString("epsilon"));
    epsilon = val.toDouble();
    val = obj.value(QString("num_obstacles"));
    num_obstacles = val.toInt();
    val = obj.value(QString("obstacle_width"));
    obstacle_width = val.toDouble();
    val = obj.value(QString("obstacle_height"));
    obstacle_height = val.toInt();
    val = obj.value(QString("step"));
    step = val.toInt();
    val = obj.value(QString("bias"));
    step = val.toInt();

//start
    val = obj.value(QString("start"));
    QJsonObject indent = val.toObject();
    val = indent.value(QString("x"));
    start.x = val.toDouble();
    val = indent.value(QString("y"));
    start.y = val.toDouble();

//goal
    val = obj.value(QString("goal"));
    indent = val.toObject();
    val = indent.value(QString("x"));
    goal.x = val.toDouble();
    val = indent.value(QString("y"));
    goal.y = val.toDouble();

//tolerance
    val = obj.value(QString("tolerance"));
    indent = val.toObject();
    val = indent.value(QString("x"));
    tolerance_x = val.toDouble();
    val = indent.value(QString("y"));
    tolerance_y = val.toDouble();
}

void controller::setup()
{
    srand(time(NULL));
    for(int i = 0; i < num_obstacles; i++){
        Obstacle newObstacle;
        newObstacle.width = obstacle_width;
        newObstacle.height = obstacle_height;
        newObstacle.center = getRandom();
        while(reachedGoal(newObstacle.center)){
            newObstacle.center = getRandom();
        }
        obstacles.append(newObstacle);
    }
}

Point controller::getRandom()
{
    Point ret;
    int biasChance = rand() % 100;
    if(biasChance <= bias){
        return goal;
    }
    else{
        ret.x = rand() % width_cm;
        ret.y = rand() % height_cm;
        return ret;
    }
}

bool controller::rrt()
{
    sourceGraph.clear();
    sourceGraph.insert(start, {});
    for(int i =0; i < iterations; i++){
        Point rand = getRandom();
        if(!valid(rand)){
            continue;
        }
        Point near = nearest(rand);
        bool inserted = false;
        Point newVertex = connect(near, rand, inserted);
        if(!inserted){
            continue;
        }
        if(reachedGoal(newVertex)){
            return true;
        }
    }
    return false;
}

bool controller::valid(Point sample)
{
    for(Obstacle obs : obstacles){
        if(sample.x > obs.center.x-obs.width/2 &&
                sample.x < obs.center.x+obs.width/2 &&
                sample.y > obs.center.y-obs.height/2 &&
                sample.y < obs.center.y+obs.height/2){
            return false;
        }
    }
    return true;
}

Point controller::nearest(Point rand)
{
    Point nearest = start;
    double minDist = -1;
    for(Point vertex : sourceGraph.keys()){
        double vertexDist = sqrt(pow(vertex.x-rand.x,2)+pow(vertex.y-rand.y, 2));
        if(minDist < 0 || vertexDist < minDist){
            minDist = vertexDist;
            nearest = vertex;
        }
    }
    return nearest;
}

Point controller::connect(Point nearestNode, Point rand, bool &success)
{
    Point newNode;
    double vertexDist = sqrt(pow(nearestNode.x-rand.x,2)+pow(nearestNode.y-rand.y, 2));
    if(vertexDist > epsilon){
        double deltaX = rand.x - nearestNode.x;
        double deltaY = rand.y - nearestNode.y;
        double theta = atan2(deltaY, deltaX);
        newNode.x = nearestNode.x + epsilon*cos(theta);
        newNode.y = nearestNode.y + epsilon*sin(theta);
    } else {
        newNode = rand;
    }
    success = !throughObstacle(nearestNode, newNode);
    if(success){
        sourceGraph.insert(newNode, {nearestNode});
        sourceGraph[nearestNode].append(newNode);
    }
    return newNode;
    //Insert into graph
}

bool controller::throughObstacle(Point nearestNode, Point rand)
{
    double vertexDist = sqrt(pow(nearestNode.x-rand.x,2)+pow(nearestNode.y-rand.y, 2));
    double deltaX = rand.x - nearestNode.x;
    double deltaY = rand.y - nearestNode.y;
    double theta = atan2(deltaY, deltaX);
    double stepSize = vertexDist/step;
    Point test = nearestNode;
    for(int i = 1; i < step; i++){
        test.x += stepSize*cos(theta);
        test.y += stepSize*sin(theta);
        if(!valid(test)){
            return true;
        }
    }
    return false;
}

bool controller::reachedGoal(Point test)
{
    return (test.x > goal.x-tolerance_x/2.0 && test.x < goal.x+tolerance_x/2.0
            && test.y > goal.y-tolerance_y/2.0 && test.y < goal.y+tolerance_y/2.0);
}
