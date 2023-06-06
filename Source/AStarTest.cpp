/*
* date    : 2023/06/06
* autother: joker.mao
* function: shellMap Star Test Main
*/
#include "CAstar.h"

int main()
{
    /*ShellMap map(10, 10);
    map.SetStartEndPoint(Point(1, 1), Point(8, 8));
    map.ShowMap();
    */
    auto star = new CAstar();
    vector< vector<APoint*> > map;
    for (int i = 0; i < MAX_X; i++)
    {
        vector<APoint*> tmp;
        for (int j = 0; j < MAX_Y; j++)
        {
            APoint *point = new APoint();
            point->x = i;
            point->y = j;
            if (star->GetMap().GetMapPtr()[j * MAX_X + i] == BLOCK)
            {
                point->type = AType::ATYPE_BARRIER;
            }
            tmp.push_back(point);
        }
        map.push_back(tmp);
    }

    //开始寻路
    auto point = star->findWay(map[0][0], map[9][9], map);
   
    if (!point)
    {
        return 0;
    }
    
    while (point)
    {
        if (star->GetMap().GetMapPtr()[point->y * MAX_X + point->x] == START || star->GetMap().GetMapPtr()[point->y * MAX_X + point->x] == END) {
            ;
        } else { 
            star->GetMap().GetMapPtr()[point->y * MAX_X + point->x] = PATH;
        }
        point = point->parent;
    }
    star->GetMap().ShowMap();
    //-------------释放内存----------
    delete star;
    
    for (int i = 0; i<MAX_X; i++)
    {
        for (int j = 10; j<MAX_Y; j++)
        {
            delete map[i][j];
            map[i][j] = nullptr;
        }
    }
    
    return 0;
}