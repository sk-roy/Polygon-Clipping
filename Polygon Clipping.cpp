#include<graphics.h>
#include<bits/stdc++.h>
using namespace std;

typedef long double ld;
const int figX = 1000;
const int figY = 500;

struct vertex{
    ld x;
    ld y;

    bool operator == (vertex kv){
        if(kv.x==x && kv.y==y) return true;
        else return false;
    }
    bool operator != (vertex kv){
        if(kv.x==x && kv.y==y) return false;
        else return true;
    }
};

ld xMax, xMin, yMax, yMin;
ld kx, ky, xxMax, xxMin, yyMax, yyMin;
int Left, Right, Top, Bottom;

char order[4];
map <char, string> d;
vector <vertex> polygon, figure;

void default_figure(){
    line(kx+xMin, 0, kx+xMin, figY);
    line(kx+xMax, 0, kx+xMax, figY);
    line(0, ky-yMin, figX, ky-yMin);
    line(0, ky-yMax, figX, ky-yMax);

    for(int i=1; i<figure.size(); i++){
        line(figure[i-1].x+kx, figure[i-1].y*(-1)+ky,
             figure[i].x+kx, figure[i].y*(-1)+ky);
    }
}

void clipping_figure(){
    int arr[polygon.size()*2];
    for(int i=0,j=0; i<polygon.size(); i++){
        arr[j++] = polygon[i].x + kx;
        arr[j++] = polygon[i].y*(-1) + ky;
    }
    fillpoly(polygon.size(), arr);
}

void store(vector <vertex> temp){
    polygon.clear();
    for(int i=0; i<temp.size(); i++){
        if(i && temp[i]==temp[i-1]) continue;
        polygon.push_back(temp[i]);
    }
    if(!polygon.empty() && polygon[0] != polygon[polygon.size()-1]) {
        polygon.push_back(polygon[0]);
    }
}

void left_clip(){
    vector <vertex> temp;
    ld x, y, x1, x2, y1, y2;

    x = xMin;
    for(int i=1; i<polygon.size(); i++){
        x1 = polygon[i-1].x;
        y1 = polygon[i-1].y;
        x2 = polygon[i].x;
        y2 = polygon[i].y;

        if(x1>=xMin && x2>=xMin){ // in-in
            temp.push_back(polygon[i]);
        }else if(x1<xMin && x2>=xMin){ // out-in
            y = (((x-x1)*(y1-y2)) / (x1-x2)) + y1;
            temp.push_back({x, y});
            temp.push_back(polygon[i]);
        }else if(x1>=xMin && x2<xMin){ // in-out
            y = (((x-x1)*(y1-y2)) / (x1-x2)) + y1;
            temp.push_back({x, y});
        }
    }
    store(temp);
    setcurrentwindow(Left);
    default_figure();
    clipping_figure();

    return ;
}

void right_clip(){
    vector <vertex> temp;
    ld x, y, x1, x2, y1, y2;

    x = xMax;
    for(int i=1; i<polygon.size(); i++){
        x1 = polygon[i-1].x;
        y1 = polygon[i-1].y;
        x2 = polygon[i].x;
        y2 = polygon[i].y;

        if(x1<=xMax && x2<=xMax){ // in-in
            temp.push_back(polygon[i]);
        }else if(x1>=xMax && x2<xMax){ // out-in
            y = (((x-x1)*(y1-y2)) / (x1-x2)) + y1;
            temp.push_back({x, y});
            temp.push_back(polygon[i]);
        }else if(x1<xMax && x2>=xMax){ // in-out
            y = (((x-x1)*(y1-y2)) / (x1-x2)) + y1;
            temp.push_back({x, y});
        }
    }
    store(temp);
    setcurrentwindow(Right);
    default_figure();
    clipping_figure();

    return ;
}

void top_clip(){
    vector <vertex> temp;
    ld x, y, x1, x2, y1, y2;

    y = yMax;
    for(int i=1; i<polygon.size(); i++){
        x1 = polygon[i-1].x;
        y1 = polygon[i-1].y;
        x2 = polygon[i].x;
        y2 = polygon[i].y;

        if(y1<=yMax && y2<=yMax){ // in-in
            temp.push_back(polygon[i]);
        }else if(y1>yMax && y2<=yMax){ // out-in
            x = (((x1-x2)*(y-y1)) / (y1-y2)) + x1;
            temp.push_back({x, y});
            temp.push_back(polygon[i]);
        }else if(y1<=yMax && y2>yMax){ // in-out
            x = (((x1-x2)*(y-y1)) / (y1-y2)) + x1;
            temp.push_back({x, y});
        }
    }
    store(temp);
    setcurrentwindow(Top);
    default_figure();
    clipping_figure();

    return ;
}

void bottom_clip(){
    vector <vertex> temp;
    ld x, y, x1, x2, y1, y2;

    y = yMin;
    for(int i=1; i<polygon.size(); i++){
        x1 = polygon[i-1].x;
        y1 = polygon[i-1].y;
        x2 = polygon[i].x;
        y2 = polygon[i].y;

        if(y1>=yMin && y2>=yMin){ // in-in
            temp.push_back(polygon[i]);
        }else if(y1<yMin && y2>=yMin){ // out-in
            x = (((x1-x2)*(y-y1)) / (y1-y2)) + x1;
            temp.push_back({x, y});
            temp.push_back(polygon[i]);
        }else if(y1>=yMin && y2<yMin){ // in-out
            x = (((x1-x2)*(y-y1)) / (y1-y2)) + x1;
            temp.push_back({x, y});
        }
    }
    store(temp);
    setcurrentwindow(Bottom);
    default_figure();
    clipping_figure();

    return ;
}

void sutherland_hodgman(){

    xxMin = polygon[0].x;
    yyMin = polygon[0].y*(-1);
    for(int i=1; i<polygon.size(); i++){
        xxMin = min(xxMin, polygon[i].x);
        yyMin = min(yyMin, polygon[i].y*(-1));
    }
    kx = 50-xxMin;
    ky = 50-yyMin;

    cout<<"Xmin = "<<xMin<<endl;
    cout<<"Xmax = "<<xMax<<endl;
    cout<<"Ymin = "<<yMin<<endl;
    cout<<"Ymax = "<<yMax<<endl;
    cout<<"Clipping  edge sequence: ";
    cout<<order[0]<<" "<<order[1]<<" "<<order[2]<<" "<<order[3]<<endl;
    cout<<"No. of vertices in the polygon = "<<polygon.size()<<endl;
    for(int i=0; i<polygon.size(); i++){
        cout<<"P"<<i+1<<" : ("<<polygon[i].x<<", "<<polygon[i].y<<")"<<endl;
    }

    Left = initwindow(figX, figY, "Left Clipping");
    Right = initwindow(figX, figY, "Right Clipping");
    Top = initwindow(figX, figY, "Top Clipping");
    Bottom = initwindow(figX, figY, "Bottom Clipping");

    store(polygon);
    figure = polygon;
    for(int i=0; i<4; i++){
        if(order[i]=='L') left_clip();
        if(order[i]=='R') right_clip();
        if(order[i]=='T') top_clip();
        if(order[i]=='B') bottom_clip();

        cout<<endl;
        cout<<"Clipping with respect to "<<d[order[i]]<<" edge..."<<endl;
        cout<<"New Sequence : ";
        for(int j=0; j<polygon.size()-1; j++){
            cout<<" ("<<polygon[j].x<<", "<<polygon[j].y<<")";
        }
        cout<<endl;
    }

    getch();
    closegraph();

    return ;
}


int main(){
    //freopen("input.txt", "r", stdin);

    d['L'] = "LEFT"; d['R'] = "RIGHT";
    d['T'] = "TOP"; d['B'] = "BOTTOM";

    cin>>xMin>>xMax>>yMin>>yMax;
    for(int i=0; i<4; i++){
        cin>>order[i];
    }
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        ld x,y;
        cin>>x>>y;
        polygon.push_back({x,y});
    }

    sutherland_hodgman();

    return 0;
}
