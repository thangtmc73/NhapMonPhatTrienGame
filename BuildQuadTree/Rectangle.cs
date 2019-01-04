using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildQuadTree
{
   public class Rectangle
    {
        private int x, y, width, height, _id;
        public Rectangle(int _x, int _y, int _width, int _height)
        {
            x = _x;
            y = _y;
            width = _width;
            height = _height;
        }
        public Rectangle()
        { }
        public int getWidth()
        {
            return width;
        }
        public int getHeight()
        {
            return height;
        }
        public int getX()
        {
            return x;
        }
        public int getY()
        {
            return y;
        }
        public int getID()
        {
            return _id;
        }
        public void setWidth(int _width)
        {
            width = _width;
        }
        public void setHeight(int _height)
        {
            height = _height;
        }
        public void setX(int _x)
        {
            x = _x;
        }
        public void setY(int _y)
        {
            y = 480 - _y;//Có thể thay đổi 1920 tùy thuộc vào kích thước của màn hình. Vì quadtree chia theo viewport node 0 ở phía trên bên trái nên sẽ chuyển đối kích thước đối tượng theo viewport
        }
       //480 là kích thước chiều cao màn hình mà chúng ta lấy ban đầu. Có thể thay đổi theo kích thước màn hình
        public void setID(int id)
        {
            _id = id;
        }
       ~Rectangle()
        { }
    }
}
