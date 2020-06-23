#ifndef VIEW_H
#define VIEW_H


class Point{
 private:
    int x;
    int y;

 public:
       Point();
       Point(int abs,int ord){x = abs; y = ord;}
      ~Point(){}
      int &getX(){return x;}
      int &getY(){return y;}
      void setX(int a){x=a;}
      void setY(int o){y=o;}
};

#endif
