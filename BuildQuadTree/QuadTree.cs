using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.IO;
using System.Text.RegularExpressions;//Để sử dụng được Regex


namespace BuildQuadTree
{
    public class Quadtree
    {

        private int MAX_OBJECTS = 2;
        private int MAX_LEVELS = 4;

        private int level, _idNode;
        public List<Rectangle> objects;
        public Rectangle bounds;
        public Quadtree[] nodes;

        //Constructor
        public Quadtree(int pLevel, int idNode, Rectangle pBounds)
        {
            level = pLevel;
            _idNode = idNode;
            objects = new List<Rectangle>();
            bounds = pBounds;
            nodes = new Quadtree[4];
        }
        public void clear()
        {
            objects.Clear();

            for (int i = 0; i < nodes.Length; i++)
            {
                if (nodes[i] != null)
                {
                    nodes[i].clear();
                    nodes[i] = null;
                }
            }
        }
        //Split thành 4 node con
        public void split()
        {
            int subWidth = (int)(bounds.getWidth() / 2);
            int subHeight = (int)(bounds.getHeight() / 2);
            int x = (int)bounds.getX();
            int y = (int)bounds.getY();

            nodes[0] = new Quadtree(level + 1, _idNode * 8 + 1, new Rectangle(x, y, subWidth, subHeight));
            nodes[1] = new Quadtree(level + 1, _idNode * 8 + 2, new Rectangle(x + subWidth, y, subWidth, subHeight));
            nodes[2] = new Quadtree(level + 1, _idNode * 8 + 3, new Rectangle(x, y + subHeight, subWidth, subHeight));
            nodes[3] = new Quadtree(level + 1, _idNode * 8 + 4, new Rectangle(x + subWidth, y + subHeight, subWidth, subHeight));
        }
        //Xác định vị trí của node chứa object
        public int getIndex(Rectangle pRect)
        {
            int index = -1;
            double verticalMidpoint = bounds.getX() + (bounds.getWidth() / 2);
            double horizontalMidpoint = bounds.getY() + (bounds.getHeight() / 2);

            // Object can completely fit within the top quadrants
            bool topQuadrant = (pRect.getY() < horizontalMidpoint);
            // Object can completely fit within the bottom quadrants
            bool bottomQuadrant = (pRect.getY() >= horizontalMidpoint);

            // Object can completely fit within the left quadrants
            if (pRect.getX() <= verticalMidpoint)
            {
                if (topQuadrant)
                {
                    index = 0;
                }
                else if (bottomQuadrant)
                {
                    index = 2;
                }
            }
            // Object can completely fit within the right quadrants
            else if (pRect.getX() > verticalMidpoint)
            {
                if (topQuadrant)
                {
                    index = 1;
                }
                else if (bottomQuadrant)
                {
                    index = 3;
                }
            }

            return index;
        }

        //Chèn dữ liệu vào quadtree
        public void insert(Rectangle pRect)
        {
            if (nodes[0] != null)
            {
                int index = getIndex(pRect);

                if (index != -1)
                {
                    nodes[index].insert(pRect);
                    return;
                }
            }

            objects.Add(pRect);

            if (objects.Count() > MAX_OBJECTS && level < MAX_LEVELS)
            {
                if (nodes[0] == null)
                {
                    split();
                }

                int i = 0;
                while (objects.Count() != 0)
                {
                    int index = getIndex(objects[0]);
                    if (index != -1)
                    {
                        Rectangle _item = objects[0];
                        objects.RemoveAt(0);
                        nodes[index].insert(_item);
                    }
                }
            }

        }

        //ReadFile GO lấy các số nguyên sử dụng fscanf
        public List<Object> _lsObject = new List<Object>();
        public void ReadFile(string _fileName)
        {
            using (StreamReader sr = new StreamReader(_fileName))
            {
                string line;
                // Read and display lines from the file until the end of 
                // the file is reached.
                //Lấy id , tọa độ x và y của object
                int[] _array = new int[4];

                while ((line = sr.ReadLine()) != null)
                {
                    Object _object = new Object();
                    int i = 0;
                    string[] numbers = Regex.Split(line, @"\D+");
                    foreach (string value in numbers)
                    {
                        if (!string.IsNullOrEmpty(value))
                        {
                            _array[i] = int.Parse(value);
                            i++;

                        }


                    }
                    _object._rect.setID(_array[0]);
                    _object._rect.setX(_array[2]);
                    _object._rect.setY(_array[3]);
                    _lsObject.Add(_object);
                }
                sr.Close();
            }
        }
        ////ReadFile

        public void AddNode(Quadtree _qNode, StreamWriter writer)
        {
            for (int j = 0; j < 4; j++)
            {
                if (_qNode.nodes[0] != null)
                {
                    writer.WriteLine();
                    writer.Write(_qNode.nodes[j]._idNode + "     " + _qNode.nodes[j].bounds.getX() + "     " + _qNode.nodes[j].bounds.getY() + "     " + _qNode.nodes[j].bounds.getWidth());
                    foreach (var item in _qNode.nodes[j].objects)
                    {
                        writer.Write("     " + item.getID());
                    }

                    for (int i = 0; i < 4; i++)
                        AddNode(_qNode.nodes[i], writer);
                }
            }
        }
        //Read
        public void WriteFile()
        {
            StreamWriter writer = new StreamWriter("Demo.txt");
            writer.WriteLine(_idNode + "     " + bounds.getX() + "     " + bounds.getY() + "     " + bounds.getWidth());
            AddNode(nodes[0], writer);
            writer.Close();
        }
    }
}
