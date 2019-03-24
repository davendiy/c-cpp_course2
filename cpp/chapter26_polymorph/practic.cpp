// Created by David Zashkolny on 23.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <vector>

using namespace std;


class Drawable{
public:
    virtual void draw() = 0;
};


class MyDrawable : public Drawable
{
public:
    virtual void draw();
    MyDrawable();
    ~MyDrawable();

private:
    int *_my_data;
};

MyDrawable::MyDrawable(){
    _my_data = new int;
}

MyDrawable::~MyDrawable() {
    delete _my_data;
}

void MyDrawable::draw() {

}


class Ship : public Drawable
{
public:
    virtual void draw();
};

void Ship::draw() {

}


class Enemy : public Drawable
{
public:
    virtual void draw();
};

void Enemy::draw() {

}


int main(){

    vector<Drawable*> drawables;
    drawables.push_back(new Ship);
    drawables.push_back(new Enemy);

    for (vector<Drawable*>::iterator itr = drawables.begin(), end = drawables.end(); itr != end; ++itr){
        (*itr)->draw();
    }
}
