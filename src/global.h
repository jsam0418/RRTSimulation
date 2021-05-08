#ifndef GLOBAL_H
#define GLOBAL_H

#define ON 1
#define OFF 0
#define ENABLE_GRAPHICS ON //set this to 0 to disable graphics

class Point
{
public:
    Point(){};
    Point(double xPos, double yPos){
        x = xPos;
        y = yPos;
    }
    ~Point(){}
    double x = 0.0;
    double y = 0.0;

    bool operator<(const Point &p) const{
        Point ret;
        if(this->x < p.x and this->y < p.y){
            return true;
        } else if(this->x+this->y < p.x + p.y){
            return true;
        } else {
            return false;
        }
    }

    bool operator==(const Point &p) const{
        return this->x==p.x && this->y==p.y;
    }
};

class Obstacle
{
public:
    Obstacle(){}
    ~Obstacle(){}
    Point center;
    double width;
    double height;
};

#endif // GLOBAL_H
