using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildQuadTree
{
    class Program
    {
        static void Main(string[] args)
        {
            Quadtree quad = new Quadtree(0,0, new Rectangle(0, 0, 1920, 1920));
            List<Object> _listObject;
            Rectangle _rectBox;
            quad.ReadFile("Stage1_1GO.txt");
            _listObject = quad._lsObject;
            foreach( var item in _listObject)
            {
                _rectBox = item._rect;
                quad.insert(_rectBox);
            }
           
            quad.WriteFile();
        }
    }
}
