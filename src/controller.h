#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QList>
#include "global.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class controller
{
public:
    controller();

    QMap<Point, QList<Point>> sourceGraph;
    QList<Obstacle> obstacles;

    /**
     * @brief configure: reads in the settings.json file and sets parameters accordingly
     */
    void configure();

    /**
     * @brief setup: does some initial setup stuff like creating obstacles
     */
    void setup();

    /**
     * @brief nearest: locates the closes node in the tree to the random point passed into it
     * @return
     */
    Point nearest(Point rand);

    /**
     * @brief valid: this function checks to see if the point passed into the function
     * is in an obstacle.
     * @return true if the point is not in an obstacle and false if it is.
     */
    bool valid(Point sample);

    /**
     * @brief throughObstacle
     * @param nearestNode: this is the point that is closest to the random point selected
     * @param rand: this is the random point selected
     * @return true if the path goes through an obstacle, false if it goes through clear space
     */
    bool throughObstacle(Point nearestNode, Point rand);

    /**
     * @brief getRandom: returns a random point in the arena
     * @return Random point
     */
    Point getRandom();

    /**
     * @brief connect: this function inserts the new point into the graph. It will take care
     *      of accounting for the epsilon value
     * @param nearest: this is the node in the graph closest to the random point
     * @param rand: this is the random point in the environment
     * @param success: a bool that represents whether the node was inserted or not
     * @return Returns the point that was insterted into the graph
     */
    Point connect(Point nearest, Point rand, bool &success);

    /**
     * @brief reachedGoal: checks to see if the new point is in the goal area
     * @param test: the point that was inserted into the graph
     * @return true if we have reached goal area, false otherwise
     */
    bool reachedGoal(Point test);
    /**
     * @brief rrt: this function is the high level RRT algorithm.
     * @return: True if a path was made from start to end, false otherwise
     */
    bool rrt();

private:
    int iterations = 0;
    int width_cm = 0;
    int height_cm = 0;
    double epsilon = 0;
    int num_obstacles = 0;
    int obstacle_width = 0;
    int obstacle_height = 0;
    int step = 0;
    double tolerance_x = 0;
    double tolerance_y = 0;
    double bias = 0;
    Point start;
    Point goal;
};

#endif // CONTROLLER_H
