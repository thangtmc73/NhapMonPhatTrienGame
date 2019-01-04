using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildQuadTree
{
    public class Object
    {
        public int _idObject;
        public Rectangle _rect;
        public Object()
        {
            _rect = new Rectangle();
        }
        ~Object()
        { }
    }
}
