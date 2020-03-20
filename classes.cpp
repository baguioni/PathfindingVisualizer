enum nodeType{START, END, WALL};
class Node{
    int x, y, f, g ,h;

    public:
    void setCoordinate(int xI, int yI);
    void setDistance(int gI);
    void setHeuristic(int hI);
    void setCost();
    int getX();
    int getY();
    int getDistance();
    int getHeuristic();
    int equal(Node a, Node b);
};

void Node::setCoordinate(int xI, int yI){
    this->x = xI;
    this->y = yI;
}

void Node::setDistance(int gI){
    g = gI;
}

void Node::setHeuristic(int hI){
    h = hI;
}

void Node::setCost(){
    f = g + h;
}

int Node::getX(){
    return x;
}

int Node::getY(){
    return y;
}

int Node::getDistance(){
    return g;
}

int Node::getHeuristic(){
    return h;
}

int Node::equal(Node a, Node b){
    if(a.getX() == b.getX() && a.getY() == b.getY())
        return 2;
    else
        return 0;
}