/*
* date:2023/06/06
* autother: joker.mao
* function: shellMap
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <iostream>

#ifndef SHELLMAP_H
#define SHELLMAP_H

#define COLOR_START  "\033[;43m"
#define COLOR_IDLE   "\033[0m"
#define COLOR_END    "\033[;44m"
#define COLOR_BLOCK  "\033[;47m"
#define COLOR_PATH   "\033[;42m"
#define COLOR_CUR    "\033[;45m"
#define COLOR_OPEN   "\033[;44m"


enum PointSts : uint8_t {
    IDLE,
    START,
    END,
    PATH,
    BLOCK,
    OPEN,
    CUR,
    CLOSE,
};

struct Point
{
    int x;
    int y;

    Point(int _x, int _y) {
        x = _x;
        y = _y;
    };
    Point() {
        x = 0;
        y = 0;
    };
};


class ShellMap {
public:
    ShellMap(int w, int h) {
       GenMap(w, h);
    };
    ShellMap() {

    }
    ~ShellMap() {
        if (points_) delete [] points_;
    };
    void GenMap(int w, int h)
    {
        w_ = w;
        h_ = h;
        points_ = new PointSts[w * h];
        srand(time(NULL));
        for (auto _h = 0; _h < h; ++_h) {
            for (auto _w = 0; _w < w; ++_w) {
                if ((rand() % 5) == 0) {
                    points_[_h * w_ + _w] = BLOCK;
                } else {
                    points_[_h * w_ + _w] = IDLE;
                }
            }
        }
    }
    void SetStartEndPoint(Point s, Point e) {
        if (s_.x >= w_ || s_.y >= h_ || e.x >= w_ || e.y >= h_)
            return;
        s_ = s;
        e_ = e;
        if (points_) {
            points_[s.y * w_ + s.x] = START;
            points_[e.y * w_ + e.x] = END;
        }
    };

    void MarkOpenListPoint(Point p) {
        if (p.x >= w_ || p.y >= h_)
            return;
        

    }

    void ShowMap() {
        //std::cout << h_ << w_;
         for (auto _h = 0; _h < h_; ++_h) {
            for (auto _w = 0; _w < w_; ++_w) {
                std::cout << " - ";
            }
            std::cout << std::endl;
            for (auto _w = 0; _w < w_; ++_w) {
                switch (points_[_h * w_ + _w])
                {
                case IDLE:
                    std::cout << "|" << COLOR_IDLE << "  " << COLOR_IDLE;
                    break;
                case START:
                    std::cout << "|" << COLOR_START << "  " << COLOR_IDLE;
                    break;
                case BLOCK:
                    std::cout << "|" << COLOR_BLOCK << "  " << COLOR_IDLE;
                    break;
                case END:
                    std::cout << "|" << COLOR_END << "  " << COLOR_IDLE;
                    break;
                case PATH:
                    std::cout << "|" << COLOR_PATH << "  " << COLOR_IDLE;
                    break;
                case OPEN:
                    std::cout << "|" << COLOR_OPEN << "  " << COLOR_IDLE;
                    break;
                case CUR:
                    std::cout << "|" << COLOR_CUR << "  " << COLOR_IDLE;
                    break;
                default:
                    std::cout << "|" << COLOR_IDLE << "  " << COLOR_IDLE;
                    break;
                }
            }
            std::cout << "|" << std::endl;
        }
        for (auto _w = 0; _w < w_; ++_w) {
            std::cout << " - ";
        }
        std::cout << std::endl;
    };


    PointSts* GetMapPtr() {
        return points_;
    };
private:
    PointSts *points_ = nullptr;
    Point s_;
    Point e_;
    int w_;
    int h_;
};

#endif